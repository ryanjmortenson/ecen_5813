########################################################
# This make file builds all 3 targets kl25z, linux-86,
# and linux-arm for beaglebone.  The make file from
# kinetis-ide was used for reference.
# #####################################################


# Some commands used for building
RM := rm -rf
MKDIR := mkdir -p

# Directory names used for building targets
outdir=out
kl25zdir=kl25z
linuxdir=linux-x86
bbbdir=linux-arm

# Map and output file name for built targets
outfile=main
mapfile=main.map

# Target names for the 3 build types
kl25z_target=$(outdir)/$(kl25zdir)/$(outfile)
linux_target=$(outdir)/$(linuxdir)/$(outfile)
bbb_target=$(outdir)/$(bbbdir)/$(outfile)

# List of map files used for cleaning
maps=$(subst elf,map,$(kl25z_target) $(linux_target) $(bbb_target))

# Call sub make files to build dependencies for each target
# TODO: Maybe make this sub make so the target passed is actually build and not all of them
-include sources.mk
-include prop/kl25z/subdir.mk

# Set kl25z flags
25Z_CFLAGS=-specs=nano.specs \
			     -specs=nosys.specs \
			     -mcpu=cortex-m0plus \
			     -mthumb -O0 \
			     -fmessage-length=0 \
			     -fsigned-char \
			     -ffunction-sections \
			     -fdata-sections \
			     -g3 \
			     -T "MKL25Z128xxx4_flash.ld" \
			     -Xlinker --gc-sections -L"./prop/kl25z/linker"

# Set CFLAGS used by every build type
CFLAGS=-I$(APP_INC_DIR) \
			 -I$(APP_SRC_DIR) \
			 -std=c99 

# Set compiler, flags, and objects based on platform type
ifeq ($(PLATFORM),kl25z)
	CC=arm-none-eabi-gcc
	CFLAGS+=$(25Z_CFLAGS)
	OBJS=$(25Z_OBJS) 
	APP_SRC+=$(C_SRCS) $(S_UPPER_SRCS)
else ifeq ($(PLATFORM),arm)
	CC=arm-linux-gnueabihf-gcc
	OBJS=$(ARM_OBJS)
	OUT_DIR=$(LINUX_ARM_OUT)
else 
	CC=x86_64-linux-gnu-gcc
	OBJS=$(X86_OBJS)
	OUT_DIR=$(LINUX_X86_OUT)
endif

.PHONY: build compile all debug allasm alli allo clean all-targets

build: $(OBJS)
	$(MAKE) project1

project1: $(OBJS)
	@echo "Building project1"
	$(CC) $(CFLAGS) -Wl,-Map,"$@.map" -o "$@" $(OBJS)

$(bbb_target): CC=arm-linux-gnueabihf-gcc
$(bbb_target): OBJS=$(ARM_OBJS)
$(bbb_target): $(ARM_OBJS)
	@echo "Building $@"
	$(CC) $(CFLAGS) -Wl,-Map,"$@.map" -o "$@" $(ARM_OBJS)

$(linux_target): CC=x86_64-linux-gnu-gcc
$(linux_target): OBJS=$(X86_OBJS)
$(linux_target): $(X86_OBJS)
	@echo "Building $@"
	$(CC) $(CFLAGS) -Wl,-Map,"$@.map" -o "$@" $(X86_OBJS)

$(kl25z_target): OBJS=$(25Z_OBJS)
$(kl25z_target): CC=arm-none-eabi-gcc
$(kl25z_target): CFLAGS+=$(25Z_CFLAGS)
$(kl25z_target): $(25Z_OBJS) $(KL25Z_OBJS)
	@echo "Building $@"
	$(CC) $(CFLAGS) -Wl,-Map,"$@.map" -o "$@" $(25Z_OBJS) $(KL25Z_OBJS)

compile-all: $(OBJS)

# Debug target is just used for debugging the make file
debug:
	@echo "Debug output"
	@echo $(OBJS)
	@echo $(SRC_LIST)
	@echo $(APP_SRC)

%.asm : $(APP_SRC_DIR)/%.c
	@echo 'Building target: $@'
	@echo 'Building with: $<'
	$(CC) -S $(CFLAGS) -c -o "$@" "$<"

allasm : 
	@echo "Building all asm files"
	$(MAKE) $(patsubst %.c,%.asm,$(SRC_LIST)) 

%.i : $(APP_SRC_DIR)/%.c
	@echo 'Building target: $@'
	@echo 'Building with: $<'
	$(CC) -E $(CFLAGS) -c -o "$@" "$<"

alli : 
	@echo "Building all i files"
	$(MAKE) $(patsubst %.c,%.i,$(SRC_LIST)) 

$(LINUX_ARM_OUT)/%.o $(LINUX_X86_OUT)/%.o $(KL25Z_OUT)/%.o %.o: $(APP_SRC_DIR)/%.c
	@echo 'Building target: $@'
	@echo 'Building with: $<'
	$(CC) $(CFLAGS) -c -o "$@" "$<"

%.map : $(APP_SRC_DIR)/%.c
	@echo 'Building target: $@'
	@echo 'Building with: $<'
	$(CC) $(CFLAGS) -c "$<"

# Clean should clean up all .elf, .map, .o, .d, and .S files created during build 
clean:
	-$(RM) $(25Z_OBJS) $(ARM_OBJS) $(X86_OBJS) $(DEPS) $(C_UPPER_DEPS) $(S_UPPER_DEPS) $(kl25z_target) $(linux_target) $(bbb_target) $(maps) *.i *.asm *.o project1*
