# 编译系统

目前firmware采取Make编译项目工程。

## 快速开始

运行

```
make PLATFORM=nut
```

对于IntoRobot-Nut，运行

```
make PLATFORM=nut
```

以编译IntoRobot-Nut为例，在项目顶层目录编译将生成设备Bootloader和应用固件程序，这些文件将输出在`build/target/`文件夹。

顶层目录编译主要用于生成Bootloader和应用固件程序，编译支持以下编译选项：

- `clean` : 强制编译整个工程
- `all`   : 默认，编译整个工程

[常用技巧](#)

## 编译组件

整个项目工程编译由不同编译组件构成，每个编译组件对应于一个文件夹，里面包括makfile等编译文件。

有两个主要的编译组件，用于生成设备执行程序：

- bootloader : 用于生成设备bootloader
- main       : 用于生成应用固件程序

其他编译组件主要用于生成主编译固件依赖的库。

编译固件时，建议您在`main`目录下编译，因为这个固件还提供其他扩展的功能。例如添加参数`esptool` 实现IntoRobot-Nut的程序烧录功能。


## 烧录固件

通常编译项目后需要烧录应用固件程序到设备，可通过如下操作进行：

- `cd main`
- `make PLATFORM=nut clean all esptool`
- 您可以添加`APP`/`APPDIR`/`TEST`编译参数用于编译一个指定的应用程序，具体可参考[编译变量](#)


# 概述

### 编译目标

- `all`: 默认编译目标，用于编译整个项目工程。
- `clean`: 删除所有编译临时文件，以便下次在清空状态下编译项目工程。
- `all program-dfu`: 编译和通过DFU工具往设备烧录应用可执行程序文件，适用于stm32方案设备。
- `all st-flash`: 编译和通过st-link工具往设备烧录应用可执行程序文件，适用于stm32方案设备。
- `all esptool`: 编译和通过esptool工具往设备烧录应用可执行程序文件，适用于esp8266/esp32方案设备。


### 编译选项

`make` 编译可以添加不同的选项，如下：

- `v` : 输出编译详细信息，1有效，默认有效。
- `PLATFORM`/`PLATFORM_ID` : 指定编译的硬件平台，可以为名称或者ID。
- `GCC_PREFIX`: 工具链工具前缀。用于指定工具链位置。工具链默认放在`tools`目录。


当在`main`目录编译，还可以添加如下选项:

- `APP` : 编译`user/application/$(APP)`目录下的应用。默认是编译`user/src`目录下的应用。
- `APPDIR`: 编译$(APPDIR)目录下的应用。目录因为firmware项目工作目录之外的目录。
- `APPLIBS`: 指定包括外部库的文件夹目录。
- `DEBUG_BUILD`: 具体参考[调试说明](debugging.md)
- `TARGET_NAME`: 设置最终生成的目标文件名称，例如添加`TARGET_NAME=whereyou`，
    生成的目标文件名称为`whereyou.bin`，默认目标文件名为`default-$(PLATFORM).bin`。
- `TARGET_DIR`: 设置存放目标文件的目录。


### PLATFORM/PLATFORM_ID

`PLATFORM_ID`为对应设备平台的编号，firmware支持的设备平台参考[platform-id.mk](../build/platform-id.mk)，具体如下：

| PLATFORM  | PLATFORM_ID | 硬件方案    |
|-----------|:-----------:|:-----------:|
| neutron   | 888002      | STM32F4     |
| nut       | 888003      | ESP8266     |
| atom      | 888004      | STM32F1     |
| fig       | 888005      | ESP32       |
| ant       | 868009      | STM32L1     |
| fox       | 878008      | STM32F4     |
| w67       | 888006      | ESP8266     |
| w323      | 888007      | ESP32       |
| l6        | 868010      | STM32L1     |
| gl2000    | 188002      | STM32F4     |
| gl2100    | 178003      | STM32F4     |

编译指定的设备平台，需在编译时添加如下选项：

```
PLATFORM_ID=<id>
```

或者

```
PLATFORM=name
```

例如编译nut的固件程序如下：

```
PLATFORM=nut
```

如果您不想每次编译都指定设备平台，您可以通过设置环境变量解决。

Linux/MacOS：

```
export PLATFORM=nut
```

Windows:

```
set PLATFORM=nut
```

因为已经设置设备平台环境变量，后面的示例不需要重复指定硬件平台。

### 清除编译结果

```
make clean
```

清除所有编译输出文件，保证下次编译重新编译所有文件。


## Specifying custom toolchain location

Custom compiler prefix can be used via an environment variable `GCC_PREFIX`.

For example when you have installed a custom toolchain under
`/opt/gcc-arm-embedded-bin` you can use invoke make using that toolchain
like this:

```
GCC_PREFIX="/opt/gcc-arm-embedded-bin/bin/arm-none-eabi-" make
```

The default value of `GCC_PREFIX` is `arm-none-eabi`, which uses the ARM
version of the GCC toolchain, assumed to be in the path.

Alternatively, a path for the tools can be specified separately as `GCC_ARM_PATH`,
which, if specified should end with a directory separator, e.g.

```
GCC_ARM_PATH="/opt/gcc-arm-embedded-bin/bin/" make
```

## Controlling Verbosity

By default the makefile is quiet - the only output is when an .elf file is produced to
show the size of the flash and RAM memory regions. To produce more verbose output, define
the `v` (verbose) variable, like this:

```
make v=1
```

## Building individual modules

The top-level makefile builds all modules. Each module can be built on its own
by executing the makefile in the module's directory. The make also builds any dependencies.

For example, executing

```
cd main
make
```

Will build the main firmware, and all the modules the main firmware depends on.


## Product ID

By default, the build system targets the Spark Core (Product ID 0). If
your product has been assigned product ID, you should pass this on the
command line to specifically target your product. For example:

```
make PRODUCT_ID=2
```

Builds the firmware for product ID 2.

Note that this method works only for the Core. On later platforms, the PRODUCT ID and version
is specified in your application code via the macros:

```
PRODUCT_ID(id);
```

and

```
PRODUCT_VERSION(version)
```


## Building an Application

To build a new application, first create a subdirectory under `user/applications/`.
You'll find the Tinker app is already there. Let's say we want to create a new
app, which we'll call `myapp/`

```
mkdir user/applications/myapp
```

Then add the files needed for your application to that directory. These can be named freely,
but should end with `.cpp`. For example, you might create these files:

```
myapplication.cpp
mylibrary.cpp
mylibrary.h
```

You can also add header files - your application subdirectory is on the include path.

To build this application, change directory to  `main` directory and run

```
make APP=myapp
```

This will build your application with the resulting `.bin` file available in
`build/target/main/platform-0/applications/myapp/myapp.bin`.

### Including Libraries in your Application

To include libraries in your application, copy or symblink the library sources
into your application folder.

To importing libraries from the WebIDE:
 - rename the `firmware` folder to the same name as the library
 - remove the examples folder

The library should then compile successfully



## Changing the Target Directory

If you prefer the output to appear somewhere else than in the `build/` directory
you can define the `TARGET_DIR` variable:

```
make APP=myapp TARGET_DIR=my/custom/output
```

This will place `main.bin` (and the other output files) in `my/custom/output` relative to the current directory.
The directory is created if it doesn't exist.


## Changing the Target File name

It's also possible to specify the name of the output file, e.g. to revert to the
old naming convention of `core-firmware.bin`, set `TARGET_FILE`
like this:

```
make APP=myapp TARGET_FILE=core-firmware
```

This will build the firmware with output as `core-firmware.bin` in `build/target/main/platform-0/applications/myapp`.

These can of course also be combined like so:

```
make APP=myapp TARGET_DIR=myfolder TARGET_FILE=core-firmware
```

Which will produce `myfolder/core-firmware.elf`


## Compiling an application outside the firmware source

If you prefer to separate your application code from the firmware code,
the build system supports this, via the `APPDIR` parameter.

```
make APPDIR=/path/to/application/source [TARGET_DIR=/path/to/applications/output] [TARGET_FILE=basename]
```

Parameters:

- `APPDIR`: The relative or full path to the directory containing the user application
- `TARGET_DIR`: the directory where the build output should go. If not defined,
    output files willb e placed under a `target` directory of the application sources.
- `TARGET_FILE`: the basename of the files created. If not defined,
defaults to the name of the application sources directory.

## Custom makefile

When using `APP` or `APPDIR` to build custom application sources, the build system
by default will build any `.c` and `.cpp` files found in the given directory
and it's subdirectories. You can override this and customize the build process by adding the file
a makefile to the root of the application sources.

The makefile should be placed in the root of the application folder. The default name for the file is:

- when building with `APP=myapp` the default name is `myapp.mk`
- when building with `APPDIR=` the default name is `build.mk`

The file should be a valid gnu make file.

To customize the build, append values to these variables:

- `CSRC`, `CPPSRC`: the c and cpp files in the build which are compiled and linked, e.g.
```
CSRC += $(call target_files,,*.c)
CPPSRC += $(call target_files,,*.cpp)
```
To add all files in the application directory and subdirectories.

- `INCLUDE_DIRS`: the include path. Paths are relative to the APPDIR folder.
- `LIB_DIRS`: the library search path
- `LIBS`: libraries to link (found in the library search path). Library names are given without the `lib` prefix and `.a` suffix.
- `LIB_DEPS`: full path of additional library files to include.

To use a different name/location for customization makefile file other than `build.mk`, define `USER_MAKEFILE` to point to
your custom build file. The value of `USER_MAKEFILE` is the location of your custom makefile relative to the application sources.

<a name='external_libs'>
## External Libraries
</a>

_Note that this is preliminary support for external libraries to bring some feature parity with Build. Over the coming weeks, full support for libraries will be added._

External Particle libraries can be compiled and linked with firmware. To add one or more external libraries:

1. download the library sources store it in a directory outside the firmware, e.g.`/particle/libs/neopixel` for the neopixel library. 

2. remove the `examples` directory if it exists
```
cd /particle/libs/neopixel
rm -rf firmware/examples
```

3. Rename `firmware` to be the same as the library name. 
```
mv firmware neopixel
```
This is so that includes like `#include "neopixel/neopixel.h"` will function correctly. 

4. Add the APPLIBS variable to the make command which lists the directories contianing libraries to use. 
```
make APPDIR=/particle/apps/myapp APPLIBS=/particle/libs/neopixel
```


## Default application.cpp integrated with firmware

In previous versions of the make system, the application code was integrated with the firmware code at `src/application.cpp`.
This mode of building is still supported, however the location has changed to: `user/src/application.cpp`.

To build the default application sources, just run `make`

```
make
```


## Platform Specific vs Platform Agnostic builds

Currently the low level hardware specific details are abstracted away in the HAL (Hardware Abstraction Layer) implementation.
By default the makefile will build for the Spark Core platform which will allow you to add direct hardware calls in your application firmware.
You should however try to make use of the HAL functions and methods instead of making direct hardware calls, which will ensure your code is more future proof!
To build the firmware as platform agnostic, first run `make clean`, then simply include `SPARK_NO_PLATFORM=y` in the make command.
This is also a great way to find all of the places in your code that make hardware specific calls, as they should generate an error when building as platform agnostic.

```
make APP=myapp SPARK_NO_PLATFORM=y
```

## Build Output Directory

The build system uses an `out of source` directory for all built artifacts. The
directory is `build/target/`. In previous versions of the build system, artifacts
were placed under a local `build` folder. If you would prefer to maintain this style of
working, you can create a symlink from `build/target/main/platform-0/` to `main/build/`.
Then after building `main`, the artifacts will be available in the `build/` subdirectory
as before.


## Flashing the firmware to the device via DFU

The `program-dfu` target can be used when building from `main/` to flash
the compiled `.bin` file to the device using dfu-util. For this to work, `dfu-util` should be
installed and in your PATH (Windows), and the device put in DFU mode (flashing yellow).

```
cd main
make program-dfu
```

### Enabling DFU Mode automatically

Normally, the device requires physical button presses to enter DFU mode. The build
also supports automatic DFU mode, where the device will automatically enter DFU
mode as part of running the `program-dfu` target. To enable this, define the environment variable
`PARTICLE_SERIAL_DEV` to point to the name of the serial device. E.g.

```
PARTICLE_SERIAL_DEV=/dev/tty.usbmodem12345 make all program-dfu
```

the device will then automatically enter DFU mode and flash the firmware.

(Tested on OS X. Should work on other platforms that provide the `stty` command.)


## Flashing the firmware to the device via ST-Link

The `st-flash` target can be used to flash all executable code (bootloader, main and modules)
to the device. The flash uses the `st-flash` tool, which should be in your system path.

# Debugging

To enable JTAG debugging, add this to the command line:

```
USE_SWD_JTAG=y
```

and perform a clean build.

To enable SWD debugging only (freeing up 2 pins) add:

```
USE_SWD=y
```

and perform a clean build. For more details on SWD-only debugging
see https://github.com/spark/firmware/pull/337

## Compilation without Cloud Support

[Core only]

To release more resources for applications that don't use the cloud, add
SPARK_CLOUD=n to the make command line. This requires a clean build.

After compiling, you should see a 3000 bytes reduction in statically allocated RAM and 35k reduction in flash use.


## Building the `develop` branch

Before the 0.4.0 firmware was released, we recommended the develop branch for early adopters to obtain the code. This is still fine for early adopters, and people that want the bleeding edge, although please keep in mind the code is untested and unreleased.

Pre-releases are available in `release/vx.x.x-rc.x` branches.  Default released firmware is available as `release/vx.x.x`, which is also then duplicated to `release/stable` and `master` branches.

To build the develop branch, follow these guidelines:

1. export the environment variable PARTICLE_DEVELOP=1
2. after pulling from the develop branch, be sure to build and flash the system firmware


## Recipes and Tips <span id = "tips"></span>

- The variables passed to make can also be provided as environment variables,
so you avoid having to type them out for each build. The environment variable value can be overridden
by passing the variable on the command line.
 - `PARTICLE_DEVELOP` can be set in the environment when building from the `develop` branch. (Caveats apply that this is bleeding edge!)
 - `PLATFORM` set in the environment if you mainly build for one platform, e.g. the Photon.

### Photon

Here are some common recipes when working with the photon. Note that `PLATFORM=photon` doesn't need to be present if you have `PLATFORM=photon` already defined in your environment.

```
# Complete rebuild and DFU flash of latest system and application firmware
firmware/modules$ make clean all program-dfu PLATFORM=photon

# Incremental build and flash of latest system and application firmware
firmware/modules$ make all program-dfu PLATFORM=photon

# Build system and application for use with debugger (Programmer Shield)
# APP/APPDIR can also be specified here to build the non-default application
firmware/modules$ make clean all program-dfu PLATFORM=photon USE_SWD_JTAG=y

# Incremental build and flash user application.cpp only (note the directory)
firmware/main$ make all program-dfu PLATFORM=photon

# Build an external application
firmware/modules$ make all PLATFORM=photon APPDIR=~/my_app
```

For system firmware developers:

```
# Rebuild and flash the primary unit test application
firmware/main$ make clean all program-dfu TEST=wiring/no_fixture PLATFORM=photon

# Build the compilation test (don't flash on device)
firmware/main$ make TEST=wiring/api PLATFORM=photon
```


### 编译应用



在firmware目录下，可以进行各个产品的编译。编译默认固件的命令主要如下：

```
make PLATFORM=neutron clean all APP=smartLight-default
make PLATFORM=nut clean all APP=smartLight-default
make PLATFORM=atom clean all APP=smartLight-default
make PLATFORM=fig clean all APP=smartLight-default
make PLATFORM=ant clean all APP=blink
make PLATFORM=fox clean all APP=smartLight-default

make PLATFORM=w67 clean all APP=smartLight-w67
make PLATFORM=w323 clean all APP=blink
make PLATFORM=l6 clean all APP=blink
```


其中，*PLATFORM=product_name*也可以替换成*PLATFORM_ID=product_id*.产品的名称和ID的关系如下表（详情请参见build/platform-id.mk）：

| 开发板       | PLATFORM_ID |
|--------------|:-----------:|
| neutron      | 888002      |
| nut          | 888003      |
| atom         | 888004      |
| fig          | 888005      |
| ant          | 868009      |
| fox          | 878008      |

| 模组         | PLATFORM_ID |
|--------------|:-----------:|
| w67          | 888006      |
| w323         | 888007      |
| l6           | 868010      |

| 网关         | PLATFORM_ID |
|--------------|:-----------:|
| gl1000       | 188001      |
| gl2000       | 188002      |
| gl2100       | 178003      |

| 其他产品     | PLATFORM_ID |
|--------------|:-----------:|
| gcc          | 208001      |
| neutron-net  | 208002      |
| anytest      | 208003      |

进入到main目录下，可以选择更多的编译选项，还可以进行烧录。
以下常用的编译及烧录命令：

```
make PLATFORM=atom clean all st-flash
make PLATFORM=atom clean all program-dfu

make PLATFORM=neutron clean all st-flash
make PLATFORM=neutron clean all program-dfu

make PLATFORM=ant clean all DEBUG_BUILD=y USE_SWD=y st-flash
make PLATFORM=ant clean all DEBUG_BUILD=y USE_SWD=y program-dfu

make PLATFORM=fox clean all DEBUG_BUILD=y USE_SWD=y st-flash
make PLATFORM=fox clean all DEBUG_BUILD=y USE_SWD=y program-dfu

make PLATFORM=nut clean all DEBUG_BUILD=y USE_SWD=y esptool

make PLATFORM=fig clean all DEBUG_BUILD=y USE_SWD=y esptool-py

make PLATFORM=w67 clean all DEBUG_BUILD=y USE_SWD=y esptool

make PLATFORM=w323 clean all DEBUG_BUILD=y USE_SWD=y esptool-py

make PLATFORM=l6 clean all DEBUG_BUILD=y USE_SWD=y st-flash
make PLATFORM=l6 clean all DEBUG_BUILD=y USE_SWD=y program-dfu

```

指定工程目录编译:
工程目录结构：
1. 工程目录/src  放用户代码
2. 工程目录/lib  放用户库

```
make PLATFORM=w67 all DEBUG_BUILD=y USE_SWD=y APPDIR=../project/loragateway

```

DEBUG_BUILD=y打开调试， st-flash program-dfu esptool分别选择相应的烧录工具。
