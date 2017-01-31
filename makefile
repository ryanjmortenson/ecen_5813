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
outfile=main.elf
mapfile=main.map

# Target names for the 3 build types
kl25z_target=$(outdir)/$(kl25zdir)/$(outfile)
linux_target=$(outdir)/$(linuxdir)/$(outfile)
bbb_target=$(outdir)/$(bbbdir)/$(outfile)

# List of map files used for cleaning
maps=$(subst elf,map,$(kl25z_target) $(linux_target) $(bbb_target))

# Call sub make files to build dependencies for each target
# TODO: Maybe make this sub make so the target passed is actually build and not all of them
-include app/subdir.mk
-include sources.mk
-include prop/$(kl25zdir)/subdir.mk

ifeq ($(PLATFORM),kl25z)
	CC=arm-none-eabi-gcc
	CFLAGS=-specs=nano.specs 
	CFLAGS+=-specs=nosys.specs
else ifeq ($(PLATFORM),arm)
	CC=arm-linux-gnueabihf-gcc
else 
	CC=gcc
endif

# All Target
all: $(kl25z_target) $(linux_target) $(bbb_target)

# Debug target is just used for debugging the make file
debug:
	@echo $(APP_SRC_DIR)
	@echo $(APP_INC_DIR)
	@echo $(APP_SRC)
	@echo $(APP_INC)
	@echo $(25Z_OBJS)
	@echo $(X86_OBJS)
	@echo $(25Z_OBJS)
	@echo $(DEPS)
	@echo $(PLATFORM)
	@echo $(test)

%.asm : $(APP_SRC_DIR)/%.c
	@echo 'Building target: $@'
	@echo 'Building with: $<'
	$(CC) -S $(CFLAGS) -I"./app/src" -I"./app/inc" -std=c99 -c -o "$@" "$<"

allasm : 
	@echo "Building all asm files"
	$(MAKE) $(patsubst %.c,%.asm,$(APP_SRC)) 

%.i : $(APP_SRC_DIR)/%.c
	@echo 'Building target: $@'
	@echo 'Building with: $<'
	$(CC) -E -I"./app/src" -I"./app/inc" -std=c99 -c -o "$@" "$<"

alli : 
	@echo "Building all asm files"
	$(MAKE) $(patsubst %.c,%.i,$(APP_SRC)) 

# The KL25Z target takes the KL25Z_OBJS for object files and places binary in out/kl25z
$(kl25z_target) : $(KL25Z_OBJS) $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Cross Linker'
	@echo 'Creating out directory'
	-$(MKDIR) $(outdir)/$(kl25zdir)
	arm-none-eabi-g++ -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -T "MKL25Z128xxx4_flash.ld" -Xlinker --gc-sections -L"./prop/kl25z/linker" -Wl,-Map,"$(subst elf,map,$(kl25z_target))" -specs=nano.specs -specs=nosys.specs -o $(kl25z_target)  $(KL25Z_OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# The linux target uses OBJS for a list of object files and places binary in out/linux-x86
$(linux_target) : $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking Linux-x86 Linker'
	@echo 'Creating out directory'
	-$(MKDIR) $(outdir)/$(linuxdir)
	gcc -g3 -Xlinker -Map=$(subst elf,map,$(linux_target)) -o $(linux_target) $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# The bbb target uses ARM_OBJS for a list of object files and places binary in out/linux-arm
$(bbb_target) : $(ARM_OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking Linux-ARM Cross Linker'
	@echo 'Creating out directory'
	-$(MKDIR) $(outdir)/$(bbbdir)
	arm-linux-gnueabihf-gcc -g3 -Xlinker -Map=$(subst elf,map,$(bbb_target)) -o $(bbb_target) $(ARM_OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Clean should clean up all .elf, .map, .o, .d, and .S files created during build 
clean:
	-$(RM) $(OBJS) $(KL25Z_OBJS) $(ARM_OBJS) $(DEPS) $(C_UPPER_DEPS) $(S_UPPER_DEPS) $(kl25z_target) $(linux_target) $(bbb_target) $(maps) *.i *.asm *.o
