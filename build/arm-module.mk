# This is the common makefile used to build all top-level modules
# It contains common recipes for bulding C/CPP/asm files to objects, and
# to combine those objects into libraries or elf files.
include $(COMMON_BUILD)/macros.mk

SOURCE_PATH ?= $(MODULE_PATH)

# import this module's symbols
include $(MODULE_PATH)/import.mk

# pull in the include.mk files from each dependency, and make them relative to
# the dependency module directory
DEPS_INCLUDE_SCRIPTS =$(foreach module,$(DEPENDENCIES),$(PROJECT_ROOT)/$(module)/import.mk)
include $(DEPS_INCLUDE_SCRIPTS)

include $(COMMON_BUILD)/arm-module-defaults.mk

include $(call rwildcard,$(MODULE_PATH)/,build.mk)

# add trailing slash
ifneq ("$(TARGET_PATH)","$(dir $(TARGET_PATH))")
TARGET_SEP = /
endif

TARGET_FILE_NAME ?= $(MODULE)

ifneq (,$(GLOBAL_DEFINES))
CDEFINES += $(addprefix -D,$(GLOBAL_DEFINES))
export GLOBAL_DEFINES
endif

# fixes build errors on ubuntu with arm gcc 5.3.1
# GNU_SOURCE is needed for isascii/toascii
# WINSOCK_H stops select.h from being used which conflicts with CC3000 headers
CFLAGS += -D_GNU_SOURCE -D_WINSOCK_H


# Collect all object and dep files
ALLOBJ += $(addprefix $(BUILD_PATH)/, $(CSRC:.c=.c.o))
ALLOBJ += $(addprefix $(BUILD_PATH)/, $(CPPSRC:.cpp=.cpp.o))
ALLOBJ += $(addprefix $(BUILD_PATH)/, $(INOSRC:.ino=.ino.o))
ALLOBJ += $(addprefix $(BUILD_PATH)/, $(ASRC:.S=.S.o))
ALLOBJ += $(addprefix $(BUILD_PATH)/, $(patsubst $(COMMON_BUILD)/%,%,$(ASRC_STARTUP:.S=.S.o)))

ALLDEPS += $(addprefix $(BUILD_PATH)/, $(CSRC:.c=.c.o.d))
ALLDEPS += $(addprefix $(BUILD_PATH)/, $(CPPSRC:.cpp=.cpp.o.d))
ALLDEPS += $(addprefix $(BUILD_PATH)/, $(INOSRC:.ino=.ino.o.d))
ALLDEPS += $(addprefix $(BUILD_PATH)/, $(ASRC:.S=.S.o.d))
ALLDEPS += $(addprefix $(BUILD_PATH)/, $(patsubst $(COMMON_BUILD)/%,%,$(ASRC_STARTUP:.S=.S.o.d)))


# All Target
all: $(MAKE_DEPENDENCIES) $(TARGET) postbuild

elf: $(TARGET_BASE).elf
bin: $(TARGET_BASE).bin
hex: $(TARGET_BASE).hex
lst: $(TARGET_BASE).lst

st-flash: $(TARGET_BASE).bin
	@echo Flashing $< using st-flash
ifeq ("$(MODULE)","bootloader")
	$(ST-FLASH) --reset write $< $(PLATFORM_BOOT_ADDR)
else
	$(ST-FLASH) --reset write $< $(PLATFORM_APP_ADDR)
endif

program-openocd: $(TARGET_BASE).bin
	@echo Flashing $< using openocd to address $(PLATFORM_APP_ADDR)
ifeq ("$(MODULE)","bootloader")
	$(OPENOCD) -f interface/stlink-v2.cfg -f target/stm32f4x.cfg  -c "init; reset halt"  -c "program $< $(PLATFORM_BOOT_ADDR) reset exit"
else
	$(OPENOCD) -f interface/stlink-v2.cfg -f target/stm32f4x.cfg  -c "init; reset halt"  -c "program $< $(PLATFORM_APP_ADDR) reset exit"
endif

# Program the core using dfu-util. The core should have been placed
# in bootloader mode before invoking 'make program-dfu'
program-dfu: $(TARGET_BASE).dfu
ifdef START_DFU_FLASHER_SERIAL_SPEED
# INTOROBOT_SERIAL_DEV should be set something like /dev/tty.usbxxxx and exported
#ifndef INTOROBOT_SERIAL_DEV
ifeq ("$(wildcard $(INTOROBOT_SERIAL_DEV))","")
	@echo Serial device INTOROBOT_SERIAL_DEV : $(INTOROBOT_SERIAL_DEV) not available
else
	@echo Entering dfu bootloader mode:
	$(UPLOAD-RESET) -p $(INTOROBOT_SERIAL_DEV) -b $(START_DFU_FLASHER_SERIAL_SPEED) -t 2000
endif
endif
	@echo Flashing using dfu:
	$(DFU) -d $(USBD_VID_INTOROBOT):$(USBD_PID_DFU) -a 0 -R -s $(PLATFORM_APP_ADDR)$(if $(PLATFORM_DFU_LEAVE),:leave) -D $<

program-serial: $(TARGET_BASE).bin
ifdef START_YMODEM_FLASHER_SERIAL_SPEED
# Program core/photon using serial ymodem flasher.
# Install 'sz' tool using: 'brew install lrzsz' on MAC OS X
# PARTICLE_SERIAL_DEV should be set something like /dev/tty.usbxxxx and exported
ifeq ("$(wildcard $(INTOROBOT_SERIAL_DEV))","")
	@echo Serial device PARTICLE_SERIAL_DEV : $(INTOROBOT_SERIAL_DEV) not available
else
	@echo Entering serial programmer mode:
	stty -f $(INTOROBOT_SERIAL_DEV) $(START_YMODEM_FLASHER_SERIAL_SPEED)
	sleep 1
	@echo Flashing using serial ymodem protocol:
# Got some issue currently in getting 'sz' working
	sz -b -v --ymodem $< > $(INTOROBOT_SERIAL_DEV) < $(INTOROBOT_SERIAL_DEV)
endif
endif

# Display size
size: $(TARGET_BASE).elf
	$(call,echo,'Invoking: ARM GNU Print Size')
	$(VERBOSE)$(SIZE) --format=berkeley $<
	$(call,echo,)

# create a object listing from the elf file
%.lst: %.elf
	$(call,echo,'Invoking: ARM GNU Create Listing')
	$(VERBOSE)$(OBJDUMP) -h -S $< > $@
	$(call,echo,'Finished building: $@')
	$(call,echo,)

# Create a hex file from ELF file
%.hex : %.elf
	$(call,echo,'Invoking: ARM GNU Create Flash Image')
	$(VERBOSE)$(OBJCOPY) -O ihex $< $@
	$(call,echo,)

# Create a DFU file from bin file
%.dfu: %.bin
	@cp $< $@
	$(DFUSUFFIX) -v $(subst 0x,,$(USBD_VID_INTOROBOT)) -p $(subst 0x,,$(USBD_PID_DFU)) -a $@

# Create a bin file from ELF file
%.bin : %.elf
	$(call echo,'Invoking: ARM GNU Create Flash Image')
	$(VERBOSE)$(OBJCOPY) -O binary $< $@

$(TARGET_BASE).elf : $(ALLOBJ) $(LIB_DEPS) $(LINKER_DEPS)
	$(call echo,'Building target: $@')
	$(call echo,'Invoking: ARM GCC C++ Linker')
	$(VERBOSE)$(MKDIR) $(dir $@)
	$(VERBOSE)$(CPP) $(ALLOBJ) --output $@ $(LDFLAGS)
	$(call echo,)

# Tool invocations
$(TARGET_BASE).a : $(ALLOBJ)
	$(call echo,'Building target: $@')
	$(call echo,'Invoking: ARM GCC Archiver')
	$(VERBOSE)$(MKDIR) $(dir $@)
	$(VERBOSE)$(AR) -cr $@ $^
	$(call echo,)

define build_C_file
	$(call echo,'Building file: $<')
	$(call echo,'Invoking: ARM GCC C Compiler')
	$(VERBOSE)$(MKDIR) $(dir $@)
	$(VERBOSE)$(CC) $(CDEFINES) $(CFLAGS) $(CINCLUDES) $(CONLYFLAGS) -c -o $@ $<
	$(call echo,)
endef

define build_CPP_file
	$(call echo,'Building file: $<')
	$(call echo,'Invoking: ARM GCC CPP Compiler')
	$(VERBOSE)$(MKDIR) $(dir $@)
	$(VERBOSE)$(CPP) $(CDEFINES) $(CFLAGS) $(CPPFLAGS) $(CINCLUDES) -c -o $@ $<
	$(call echo,)
endef

# C compiler to build .c.o from .c in $(BUILD_DIR)
$(BUILD_PATH)/%.c.o : $(SOURCE_PATH)/%.c
	$(build_C_file)

# CPP compiler to build .cpp.o from .cpp in $(BUILD_DIR)
# Note: Calls standard $(CC) - gcc will invoke g++ as appropriate
$(BUILD_PATH)/%.cpp.o : $(SOURCE_PATH)/%.cpp
	$(build_CPP_file)

define build_LIB_files
$(BUILD_PATH)/$(notdir $1)/%.c.o : $1/%.c
	$$(build_C_file)

$(BUILD_PATH)/$(notdir $1)/%.cpp.o : $1/%.cpp
	$$(build_CPP_file)
endef

# define rules for each library
# only the sources added for each library are built (so for libraries only files under "src" are built.)
$(foreach lib,$(MODULE_LIBS),$(eval $(call build_LIB_files,$(lib))))

# Assember to build .S.o from .S in $(BUILD_DIR)
$(BUILD_PATH)/%.S.o : $(SOURCE_PATH)/%.S
	$(call echo,'Building file: $<')
	$(call echo,'Invoking: ARM GCC Assembler')
	$(VERBOSE)$(MKDIR) $(dir $@)
	$(VERBOSE)$(CC) $(ASFLAGS) -c -o $@ $<
	$(call echo,)

# build start up
# Assember to build .S.o from .S in $(COMMON_BUILD)
$(BUILD_PATH)/%.S.o : $(COMMON_BUILD)/%.S
	$(call echo,'Building file: $<')
	$(call echo,'Invoking: ARM GCC Assembler')
	$(VERBOSE)$(MKDIR) $(dir $@)
	$(VERBOSE)$(CC) $(ASFLAGS) -c -o $@ $<
	$(call echo,)

# CPP compiler to build .ino.o from .ino in $(BUILD_DIR)
# Note: Calls standard $(CC) - gcc will invoke g++ as appropriate
$(BUILD_PATH)/%.ino.o : $(SOURCE_PATH)/%.ino
	$(call echo,'Building file: $<')
	$(call echo,'Invoking: ARM GCC CPP Compiler')
	$(VERBOSE)$(MKDIR) $(dir $@)
	$(VERBOSE)$(CPP) -x c++ -include $(INO_INCLUDE_HEADER) $(CDEFINES) $(CFLAGS) $(CPPFLAGS) $(CINCLUDES) -c -o $@ $<
	$(call echo,)

# Other Targets
clean: clean_deps
	$(VERBOSE)$(RM) $(ALLOBJ) $(ALLDEPS) $(TARGET)
	$(VERBOSE)$(RMDIR) $(BUILD_PATH)
	$(call,echo,)

.PHONY: all postbuild none elf bin hex size program-dfu program-openocd st-flash program-serial
.SECONDARY:

include $(COMMON_BUILD)/recurse.mk

# Include auto generated dependency files
ifneq ("MAKECMDGOALS","clean")
-include $(ALLDEPS)
endif

