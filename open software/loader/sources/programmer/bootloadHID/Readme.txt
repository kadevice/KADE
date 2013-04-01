This is the README file for bootloadHID.

BootloadHID is a USB boot loader for AVR microcontrollers. It can be used on
all AVRs with at least 2 kB of boot loader section, e.g. the popular ATMega8.
The firmware is flashed into the upper 2 kB of the flash memory and takes
control immediately after reset. If a certain hardware condition is met
(this condition can be configured, e.g. a jumper), the boot loader waits for
data on the USB interface and loads it into the remaining part of the flash
memory. If the condition is not met, control is passed to the loaded firmware.

This boot loader is similar to Thomas Fischl's avrusbboot, except that it
is built on top of the HID device class. This implementation is more user
friendly on Windows, since no kernel level drivers need to be installed.


FILES IN THE DISTRIBUTION
=========================
Readme.txt ........ The file you are currently reading.
firmware .......... Source code of the controller firmware.
firmware/usbdrv ... USB driver -- See Readme.txt in that directory for info
commandline ....... Source code of the host software (downloader).
License.txt ....... Public license (GPL2) for all contents of this project.
Changelog.txt ..... Logfile documenting changes in soft-, firm- and hardware.


BUILDING AND INSTALLING
=======================
This project can be built on Unix (Linux, FreeBSD or Mac OS X) or Windows.

For all platforms, you must first describe your hardware in the file
"firmware/bootloaderconfig.h". See the documentation in the example provided
with this distribution for details. Then edit "firmware/Makefile" to reflect
the target device, the device's boot loader address and fuse bit values. Our
examples are for an ATMega8.

Building on Windows:
You need WinAVR for the firmware and MinGW and MSYS for the host software.
Visual C++ instead of MinGW might work as well, but we prefer free development
environments. The packages can be downloaded from:
    WinAVR: http://winavr.sourceforge.net/
    MinGW and MSYS: http://www.mingw.org/
Install the packages in any order and follow the installation instructions
of the respective package. Hint: Use the big ready-made archives for MinGW
and MSYS, not the individual packages. You can identify these by their file
size.

To build the firmware with WinAVR, change into the "firmware" directory,
check whether you need to edit the "Makefile" (e.g. change the ISP upload
tool) and type "make" to compile the source code. Before you upload the code
to the device with "make flash", you should set the fuses with "make fuse".
To protect the boot loader from overwriting itself, set the lock bits with
"make lock" after uploading the firmware.

In order to build the command line tool, change to the "commandline" directory
and edit the "Makefile". Comment out the definitions which are for Unix only
and uncomment those for Windows. Then type "make" to build "bootloadHID.exe".
Alternatively, if everything is installed in the default locations, you
can type "make -f Makefile.windows".

Building on Unix (Linux, FreeBSD and Mac):
You need the GNU toolchain and avr-libc for the firmware and libusb for the
command line tool. The packages can be downloaded from:
    GNU toolchain and avr-libc: See
        http://www.nongnu.org/avr-libc/user-manual/install_tools.html
    libusb: http://libusb.sourceforge.net/
Install the packages in any order and follow the instructions for the
respective package.

To build the firmware, change to the "firmware" directory, edit "Makefile"
to use the programmer of your choice and type "make" to compile the source
code. Before you upload the code to the device with "make flash", you
should set the fuses with "make fuse". Then protect the boot loader firmware
with "make lock".

In order to build the application, make sure that the command 'libusb-config'
is in your search path. Then change directory to "commandline", check whether
you need to edit "Makefile" (should not be necessary on Unix) and type "make"
to build the "bootloadHID" tool.


WORKING WITH THE BOOT LOADER
============================
The boot loader is quite easy to use. Set the jumper (or whatever condition
you have configured) for boot loading on the target hardware, connect it to
the host computer and (if not bus powered) issue a Reset on the AVR.

The firmware can now be flashed with the "bootloadHID" tool. It accepts only
one parameter: an Intel-Hex file containing the code to be loaded.


USING THE USB DRIVER FOR YOUR OWN PROJECTS
==========================================
This project is not intended as a reference implementation. If you want to
use AVR-USB in your own projects, please see
   * PowerSwitch for the most basic example,
   * Automator for an HID example or
   * AVR-Doper for a very complex example on how to simulate a serial
     interface (virtual COM port).
All these projects can be downloaded from http://www.obdev.at/avrusb/


ABOUT THE LICENSE
=================
It is our intention to make our USB driver and this demo application
available to everyone. Moreover, we want to make a broad range of USB
projects and ideas for USB devices available to the general public. We
therefore want that all projects built with our USB driver are published
under an Open Source license. Our license for the USB driver and demo code is
the GNU General Public License Version 2 (GPL2). See the file "License.txt"
for details.

If you don't want to publish your source code under the GPL2, you can simply
pay money for AVR-USB. As an additional benefit you get USB PIDs for free,
licensed exclusively to you. See the file "CommercialLicense.txt" for details.


MORE INFORMATION
================
For more information about Objective Development's firmware-only USB driver
for Atmel's AVR microcontrollers please visit the URL

    http://www.obdev.at/products/avrusb/

A technical documentation of the driver's interface can be found in the
file "firmware/usbdrv/usbdrv.h".


--
(c) 2007 by OBJECTIVE DEVELOPMENT Software GmbH.
http://www.obdev.at/
