# This file is a makefile included from the top level makefile which
# defines the sources built for the target.

# Define the prefix to this directory.
# Note: The name must be unique within this build and should be
#       based on the root of the project

TARGET_INTOROBOT_SRC_PATH = $(TARGET_INTOROBOT_PATH)/src

# C source files included in this build.
CSRC += $(call target_files,$(TARGET_INTOROBOT_SRC_PATH)/,*.c)

# C++ source files included in this build.
CPPSRC += $(call target_files,$(TARGET_INTOROBOT_SRC_PATH)/,*.cpp)

# ASM source files included in this build.
ASRC +=

