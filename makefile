################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf
MKDIR := mkdir -p
outdir = out
kl25zdir = kl25z
linuxdir = linux
bbbdir = bbb
outfile = main.elf
mapfile = main.map

-include prop/$(kl25zdir)/subdir.mk
-include app/subdir.mk


# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(outdir)/$(kl25zdir)/$(outfile) $(outdir)/$(linuxdir)/$(outfile) secondary-outputs
#all: stuff

stuff:
	@echo $(OBJS)
	@echo $(test)

# Tool invocations
$(outdir)/$(kl25zdir)/$(outfile): $(KL25Z_OBJS) $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross ARM C++ Linker'
	@echo 'Creating out directory'
	-$(MKDIR) $(outdir)/$(kl25zdir) 
	arm-none-eabi-g++ -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -T "MKL25Z128xxx4_flash.ld" -Xlinker --gc-sections -L"./prop/kl25z/linker" -Wl,-Map,"$(outdir)/$(kl25zdir)/$(mapfile)" -specs=nano.specs -specs=nosys.specs -o "$(outdir)/$(kl25zdir)/$(outfile)" $(KL25Z_OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

$(outdir)/$(linuxdir)/$(outfile): $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking native Linker'
	@echo 'Creating out directory'
	-$(MKDIR) $(outdir)/$(linuxdir) 
	gcc -Xlinker -Map="$(outdir)/$(linuxdir)/$(mapfile)" -o "$(outdir)/$(linuxdir)/$(outfile)" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
# Other Targets
#
clean:
	-$(RM) $(C++_DEPS)$(OBJS)$(C_DEPS)$(ASM_DEPS)$(CC_DEPS)$(CPP_DEPS)$(CXX_DEPS)$(C_UPPER_DEPS)$(S_UPPER_DEPS) $(outdir)/$(kl25zdir)/$(outfile)
	-@echo ' '

secondary-outputs:

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
