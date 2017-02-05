########################################################
# This make file builds all 3 targets kl25z, linux-86,
# and linux-arm for beaglebone.  The make file from
# kinetis-ide was used for reference.
# #####################################################


# Some commands used for building
RM:=rm -rf
MKDIR:=mkdir -p

# Directory names used for building targets
OUT=out
25Z=kl25z
X86=linux-x86
ARM=linux-arm

# Export variables to use in submake
export $(25Z)
export $(X86) export $(ARM)

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
MAPS=$(25Z_OUT_DIR)/$(MAP_FILE) $(X86_OUT_DIR)/$(MAP_FILE) $(ARM_OUT_DIR)/$(MAP_FILE)

# Call sub make files to build dependencies for each target
-include sources.mk
-include prop/kl25z/subdir.mk

# Set kl25z flags
25Z_CFLAGS=-specs=nano.specs \
			     -specs=nosys.specs \
			     -mcpu=cortex-m0plus \
			     -mthumb \
			     -fmessage-length=0 \
			     -fsigned-char \
			     -ffunction-sections \
			     -fdata-sections \
			     -T "MKL25Z128xxx4_flash.ld" \
			     -Xlinker --gc-sections -L"./prop/kl25z/linker"

# Set CFLAGS used by every build type
CFLAGS=-I$(APP_INC_DIR) \
			 -I$(APP_SRC_DIR) \
			 -Wall \
			 -Werror \
			 -O0 \
			 -std=c99 \
			 -MMD \
			 -MP \
			 -MF"$(subst .o,,$@).d"

# Set a map flag to be added CFLAGS for certain targets
MAP_FLAG=-Wl,-Map,"$@.map"

# Set of 3 compilers use
ARM_CC=arm-linux-gnueabihf-gcc
X86_CC=x86_64-linux-gnu-gcc
25Z_CC=arm-none-eabi-gcc

# Set compiler, flags, and objects based on platform type
ifeq ($(PLATFORM),frdm)
	CC=$(25Z_CC)
	CFLAGS+=$(25Z_CFLAGS)
	OBJS=$(25Z_OBJS)
	APP_SRC+=$(C_SRCS) $(S_UPPER_SRCS)
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
	CC=$(X86_CC)
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

# List of items that need to be cleaned
CLEAN=$(25Z_OBJS) \
			$(ARM_OBJS) \
			$(X86_OBJS) \
			$(DEPS) \
			$(C_UPPER_DEPS) \
			$(S_UPPER_DEPS) \
			$(25Z_OUT) \
			$(X86_OUT) \
			$(ARM_OUT) \
			$(KL25Z_OBJS) \
			$(C_DEPS) \
			$(OUT) \
			$(APP_OUT) \
			*.i \
			*.asm \
			*.o \
			project1*

# Setup some build strings
BUILD_TARGET=@echo "Building Target $@"
BUILD_WITH=@echo "Building with $<"

# Set PHONY for all targets that don't have outputs for tracking
.PHONY: build compile-all debug allasm alli allo clean

# Build will build project1
build: $(OBJS)
	$(MAKE) project1

# Debug target is just used for debugging the make file
debug:
	@echo "Debug output"
	@echo $(25Z_OUT)
	@echo $(OUT_FILE)
	@echo $(SIZE)

# Compiles the project into project1 binary which can be executed with ./project1
project1: CFLAGS+=$(MAP_FLAG)
project1: $(OBJS)
	@echo "Building project1"
	$(CC) $(CFLAGS) -o "$@" $(OBJS)
	$(SIZE) $@

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

# Builds .o files from .c files
$(X86_APP_OUT)/%.o $(ARM_APP_OUT)/%.o $(25Z_APP_OUT)/%.o %.o: $(APP_SRC_DIR)/%.c
	$(BUILD_TARGET)
	$(BUILD_WITH)
	$(shell $(MKDIR) $(ARM_APP_OUT))
	$(shell $(MKDIR) $(X86_APP_OUT))
	$(shell $(MKDIR) $(25Z_APP_OUT))
	$(CC) $(CFLAGS) -c -o "$@" "$<"

# Builds a map file
%.map : $(APP_SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c "$<"

# Clean should clean up all .elf, .map, .o, .d, and .S files created during
# build
clean:
	$(RM) $(CLEAN)

# The following targets are specifically made so all 3 targets can be built and
# placed in a seperate directory

# Build the arm binary and places it in out/linux-arm/main
$(ARM_OUT): CC=$(ARM_CC)
$(ARM_OUT): OBJS=$(ARM_OBJS)
$(ARM_OUT): CFLAGS+=$(MAP_FLAG)
$(ARM_OUT): $(ARM_OBJS)
	$(BUILD_TARGET)
	$(shell $(MKDIR) $(ARM_OUT_DIR))
	$(CC) $(CFLAGS) -o "$@" $(ARM_OBJS)
	$(SIZE) $@

# Build the x86 binary and places it in out/linux-x86/main
$(X86_OUT): CC=$(X86_CC)
$(X86_OUT): OBJS=$(X86_OBJS)
$(X86_OUT): CFLAGS+=$(MAP_FLAG)
$(X86_OUT): $(X86_OBJS)
	$(BUILD_TARGET)
	$(shell $(MKDIR) $(X86_OUT_DIR))
	$(CC) $(CFLAGS)  -o "$@" $(X86_OBJS)
	$(SIZE) $@

# Build the 25z binary and places it in out/kl25z/main
$(25Z_OUT): OBJS=$(25Z_OBJS)
$(25Z_OUT): CC=$(25Z_CC)
$(25Z_OUT): CFLAGS+=$(25Z_CFLAGS) $(MAP_FLAG)
$(25Z_OUT): $(25Z_OBJS) $(KL25Z_OBJS)
	$(BUILD_TARGET)
	$(shell $(MKDIR) $(25Z_OUT_DIR))
	$(CC) $(CFLAGS) -o "$@" $(25Z_OBJS) $(KL25Z_OBJS)
	$(SIZE) $@
