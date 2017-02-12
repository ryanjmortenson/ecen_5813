##############################################################################
# This project requires the following tool-chains to be able to build all
# targets:
#
# * **gcc-arm-linux-gnueabihf** - Used to build project for Beagle Bone Black.
# * **gcc-arm-none-eabi** - Used to build the project for FRDM-KL25Z.
# * **gcc** - Used to build the project for your development workstation.
#
# There are different targets in the make file that can be built.  When no
# platform is supplied with the PLATFORM=<platform> option the build will use
# the host machines compiler.
#
# * **make** - Will build the current project for the host.
# * **make <c_file>.asm** - Output an assembly file for the source file
#                           specified.
# * **make allasm** - Output all assembly files for the project.
# * **make <c_file>.i** - Output a preprocessor file for the source file
# 												specified.
# * **make alli** - Output all preprocessor files for the project.
# * **make <c_file>.o** - Output an object file for the source file
# 												specified.
# * **make compile-all** - Output all object files project.
# * **make <c_file>.map** - Output a map file for the source file specified.
# * **make clean** - Clean all files for the project
#
# There are three types for the PLATFROM option:
#
# * **host** - X86_64 Linux
# * **frdm** - FRDM-KL25Z
# * **bbb** - ARM Linux
##############################################################################

# Some commands used for building
RM:=rm -rf
MK_DIR:=mkdir -p

# Directory names used for building targets
OUT=out
25Z=kl25z
X86=linux-x86
ARM=linux-arm

# Export variables to use in submake
export $(25Z)
export $(X86)
export $(ARM)
export $(MK_DIR)

# Map and output file name for built targets
OUT_FILE=main
MAP_FILE=main.map

# Target out directories when building
25Z_OUT_DIR=$(OUT)/$(25Z)
X86_OUT_DIR=$(OUT)/$(X86)
ARM_OUT_DIR=$(OUT)/$(ARM)

# Target names for 3 built types
25Z_OUT=$(25Z_OUT_DIR)/$(OUT_FILE)
ARM_OUT=$(ARM_OUT_DIR)/$(OUT_FILE)
X86_OUT=$(X86_OUT_DIR)/$(OUT_FILE)

# List of map files used for cleaning
MAPS=$(25Z_OUT_DIR)/$(MAP_FILE) \
		 $(X86_OUT_DIR)/$(MAP_FILE) \
		 $(ARM_OUT_DIR)/$(MAP_FILE)

# Call sub make files to build dependencies for each target
-include sources.mk

# Call this when building for kl25z
-include prop/kl25z/subdir.mk

# Set CFLAGS used by every build type
CFLAGS=-I$(APP_INC_DIR) \
			 -Wall \
			 -Werror \
			 -O0 \
			 -std=c99

# Set a map flag to be added CFLAGS for certain targets
MAP_FLAG=-Wl,-Map,"$@.map"

# Set of 3 compilers use
ARM_CC=arm-linux-gnueabihf-gcc
X86_CC=x86_64-linux-gnu-gcc
25Z_CC=arm-none-eabi-gcc

# Set compiler, flags, and objects based on platform type
ifeq ($(PLATFORM),frdm)
	CC=$(25Z_CC)
	CFLAGS+=$(KL25Z_CFLAGS) \
					-I$(KL25Z_PROP_INC_DIR)
	OBJS=$(25Z_OBJS) \
			 $(KL25Z_PROP_OBJS)
else ifeq ($(PLATFORM),bbb)
	CC=$(ARM_CC)
	OBJS=$(ARM_OBJS)
	OUT_DIR=$(LINUX_ARM_OUT)
else ifneq ($(findstring arm,$(shell uname -a)),)
	CC=gcc
	OBJS=$(ARM_OBJS)
	OUT_DIR=$(LINUX_ARM_OUT)
else ifeq ($(PLATFORM),host)
	CC=$(X86_CC)
	OBJS=$(X86_OBJS)
	OUT_DIR=$(LINUX_X86_OUT)
else
	CC=gcc
	OBJS=$(X86_OBJS)
	OUT_DIR=$(LINUX_X86_OUT)
endif

# On BBB the size binary isn't called arm-linux-gnueabihf-size so set it
# to size
ifeq ($(findstring arm,$(shell uname -a)),)
	SIZE=size
else
	SIZE=$(subst gcc,size,$(CC))
endif

ifeq ($(findstring arm,$(shell uname -a)),)
	AR=ar
else
	ar=$(subst gcc,ar,$(CC))
endif

# If release isn't specfied build with debug symbols
ifneq ($(TYPE),release)
	CFLAGS+=-g3
endif

# Set a compile time flag if it is prvovided or set to current project
ifneq ($(FLAG),)
	CFLAGS+=-D $(FLAG)
else
	CFLAGS+=-D PROJECT1
endif

# Setup some build strings
BUILD_TARGET=@echo "Building Target $@"
BUILD_WITH=@echo "Building with $<"

# Set PHONY for all targets that don't have outputs for tracking
.PHONY: build compile-all debug allasm alli clean

# Build will build project1
build: $(OBJS)
	$(MAKE) project1

# Build will build project1
build-lib: $(OBJS)
	$(MAKE) libproject1.a

# Debug target is just used for debugging the make file
debug:
	@echo "Debug output"
	@echo $(25Z_PROP_OUT)
	@echo $(25Z_PROP_SRCS)
	@echo $(OUT_FILE)
	@echo $(SIZE)
	@echo $(OBJS)

# Compiles the project into project1 binary which can be executed with ./project1
project1: CFLAGS+=$(MAP_FLAG)
project1: $(OBJS)
	@echo "Building project1"
	$(CC) $(CFLAGS) -o "$@" $(OBJS)
	$(SIZE) $@

libproject1.a: $(OBJS)
	$(AR) cr $@ $(OBJS)

# Builds all objects files but doesn't link
compile-all: $(OBJS)

# Builds an asm file
%.asm : $(APP_SRC_DIR)/%.c
	$(BUILD_TARGET)
	$(BUILD_WITH)
	$(CC) -S $(CFLAGS) -c -o "$@" "$<"

# Build all asm files
allasm :
	@echo "Building all asm files"
	$(MAKE) $(patsubst %.c,%.asm,$(SRC_LIST))

# Build and i file
%.i : $(APP_SRC_DIR)/%.c
	$(BUILD_TARGET)
	$(BUILD_WITH)
	$(CC) -E $(CFLAGS) -c -o "$@" "$<"

# Build all i files
alli :
	@echo "Building all i files"
	$(MAKE) $(patsubst %.c,%.i,$(SRC_LIST))

# Builds .o file when a .c file is specified by command line
%.o: $(APP_SRC_DIR)/%.c
	$(BUILD_TARGET)
	$(BUILD_WITH)
	$(CC) $(CFLAGS) -c -o "$@" "$<"

# Builds .o files from .c files
$(X86_APP_OUT)/%.o $(ARM_APP_OUT)/%.o $(25Z_APP_OUT)/%.o: CFLAGS+=-MD -MP
$(X86_APP_OUT)/%.o $(ARM_APP_OUT)/%.o $(25Z_APP_OUT)/%.o: $(APP_SRC_DIR)/%.c
	$(BUILD_TARGET)
	$(BUILD_WITH)
	$(shell $(MK_DIR) $(ARM_APP_OUT))
	$(shell $(MK_DIR) $(X86_APP_OUT))
	$(shell $(MK_DIR) $(25Z_APP_OUT))
	$(CC) $(CFLAGS) -c -o "$@" "$<"

# List of items that need to be cleaned
CLEAN+=$(25Z_OUT) \
			 $(X86_OUT) \
			 $(ARM_OUT) \
			 $(MAPS) \
			 *.i \
			 *.asm \
			 *.o \
			 project1* \
			 libproject1.a

# Clean should clean up all .elf, .map, .o, .d, and .S files created during
# build
clean:
	$(RM) $(CLEAN)

# The following targets are specifically made so all 3 targets can be built and
# placed in seperate directories.  I prefer for the output binaries to be in
# their corresponding platform directory.  Putting a project* binary in the top
# level directory may cause confusion when loading binaries on platforms.

# Build the arm binary and places it in out/linux-arm/main
$(ARM_OUT): CC=$(ARM_CC)
$(ARM_OUT): CFLAGS+=$(MAP_FLAG)
$(ARM_OUT): $(ARM_OBJS)
	$(BUILD_TARGET)
	$(shell $(MK_DIR) $(ARM_APP_OUT))
	$(shell $(MK_DIR) $(ARM_OUT_DIR))
	$(CC) $(CFLAGS) -o "$@" $(ARM_OBJS)
	$(SIZE) $@

# Build the x86 binary and places it in out/linux-x86/main
$(X86_OUT): CC=$(X86_CC)
$(X86_OUT): CFLAGS+=$(MAP_FLAG)
$(X86_OUT): $(X86_OBJS)
	$(BUILD_TARGET)
	$(shell $(MK_DIR) $(X86_APP_OUT))
	$(shell $(MK_DIR) $(X86_OUT_DIR))
	$(CC) $(CFLAGS)  -o "$@" $(X86_OBJS)
	$(SIZE) $@

# Build the 25z binary and places it in out/kl25z/main
$(25Z_OUT): CC=$(25Z_CC)
$(25Z_OUT): CFLAGS+=$(KL25Z_CFLAGS) $(MAP_FLAG) -I$(KL25Z_PROP_INC_DIR)
$(25Z_OUT): $(25Z_OBJS) $(KL25Z_PROP_OBJS)
	$(BUILD_TARGET)
	$(shell $(MK_DIR) $(25Z_APP_OUT))
	$(shell $(MK_DIR) $(25Z_OUT_DIR))
	$(CC) $(CFLAGS) -o "$@" $(25Z_OBJS) $(KL25Z_PROP_OBJS)
	$(SIZE) $@
