ECEN-5013 Embedded Software Fundamentals
========================================

[ECEN-5013 Embedded Software Fundamentals](https://ecee.colorado.edu/academics/courses/ECEN_5013.html)

Repository Contents
-------------------

* **/app** - Platform independent source.
* **/prop** - Proprietary platform dependent source.
* **/scripts** - Helpful scripts for the project.
* **makefile** - Main make file for the project.
* **sources.mk** - List of sources for the platform independent source.
* **README.md** - This readme.

Device Documentation
--------------

* **[Beagle Bone Black](https://beagleboard.org/black)** - Bealge Bone Black used for in class projects and homework.
* **[FRDM-KL25Z](http://www.nxp.com/products/software-and-tools/hardware-development-tools/freedom-development-boards/freedom-development-platform-for-kinetis-kl14-kl15-kl24-kl25-mcus:FRDM-KL25Z?tid=vanFRDM-KL25Z)** - FRDM-KL25Z used for in class projects and homework.
* **[NRF24L01](https://www.nordicsemi.com/eng/Products/2.4GHz-RF/nRF24L01-Evaluation-Kit)** - Wireless module for final project.

Make instructions
------------

This project requires the following tool-chains to be able to build all targets:

* **gcc-arm-linux-gnueabihf** - Used to build project for Beagle Bone Black.
* **gcc-arm-none-eabi** - Used to build the project for FRDM-KL25Z.
* **gcc** - Used to build the project for your development workstation.

There are different targets in the make file that can be built.  When no
platform is supplied with the PLATFORM=*platform* option the build will use
the host machines compiler.

* **make** - Will build the current project for the host.
* **make *c_file*.asm** - Output an assembly file for the source file specified.
* **make allasm** - Output all assembly files for the project.
* **make *c_file*.i** - Output a preprocessor file for the source file specified.
* **make alli** - Output all preprocessor files for the project.
* **make *c_file*.o** - Output an object file for the source file specified.
* **make compile-all** - Output all object files project.
* **make *c_file*.map** - Output a map file for the source file specified.
* **make test** - Create the unit tests for host.
* **make build-lib** - Create a static library for the project.
* **make clean** - Clean all files for the project.
* **make super-clean** - Clean all files for the project and the cmocka out directory.

There are three types for the PLATFORM option:

* **host** - X86_64 Linux
* **frdm** - FRDM-KL25Z
* **bbb** - ARM Linux

To build different use PROJECT=*project_number* e.g. PROJECT=2:

* **1** - Project demonstrating data/memory manipulation and build systems. 
* **2** - Project using UART and stdio to implement logging with circular buffer.
* **3** - Project using SPI to communicate with a nordic module, DMA for UART and fast memory transfers, and profiling with timer.h (BBB) and TPM module (frdm).
* **4** - Project using command structures passed over UART to control features of the FRDM including the RGB LED, system reset, and RTC Timestamp.  Also implement SPI on BBB.
* **5** - Project using the control library functionality from Project 4 and the Nordic library from Project 3 to send command instructions wirelessly using the Nordic NRF24L01.

  There are 5 different LOGGER options to build them use LOGGER=*logger_type* e.g. LOGGER=TEXT:
  * **INTERRUPTS** - Binary logger using interrupts and circular buffer
  * **BINARY** - Binary logger using circular buffer
  * **CIRCBUF** - Text logging with circular buffer
  * **TEXT** - Text logging using interrupts and circular buffer
  * **TEXTDMA** - Text logging DMA circular buffer
