################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf
MKDIR := mkdir -p
outdir = out
kl25zdir = kl25z
bbbdir = bbb
outfile = main.elf
mapfile = main.map

-include prop/$(kl25zdir)/subdir.mk
-include src/subdir.mk

# All of the sources participating in the build are defined here
# -include sources.mk
# -include Sources/subdir.mk
# -include Project_Settings/Startup_Code/subdir.mk
# -include subdir.mk
# -include objects.mk
# 
# ifneq ($(MAKECMDGOALS),clean)
# ifneq ($(strip $(C++_DEPS)),)
# -include $(C++_DEPS)
# endif
# ifneq ($(strip $(C_DEPS)),)
# -include $(C_DEPS)
# endif
# ifneq ($(strip $(ASM_DEPS)),)
# -include $(ASM_DEPS)
# endif
# ifneq ($(strip $(CC_DEPS)),)
# -include $(CC_DEPS)
# endif
# ifneq ($(strip $(CPP_DEPS)),)
# -include $(CPP_DEPS)
# endif
# ifneq ($(strip $(CXX_DEPS)),)
# -include $(CXX_DEPS)
# endif
# ifneq ($(strip $(C_UPPER_DEPS)),)
# -include $(C_UPPER_DEPS)
# endif
# ifneq ($(strip $(S_UPPER_DEPS)),)
# -include $(S_UPPER_DEPS)
# endif
# endif
# 
# -include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: kl25z-main secondary-outputs

# Tool invocations
kl25z-main: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross ARM C++ Linker'
	@echo 'Creating out directory'
	-$(MKDIR) $(outdir)/$(kl25zdir) 
	arm-none-eabi-g++ -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -T "MKL25Z128xxx4_flash.ld" -Xlinker --gc-sections -L"./prop/kl25z/linker" -Wl,-Map,"$(outdir)/$(kl25zdir)/$(mapfile)" -specs=nano.specs -specs=nosys.specs -o "$(outdir)/$(kl25zdir)/$(outfile)" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C++_DEPS)$(OBJS)$(C_DEPS)$(ASM_DEPS)$(CC_DEPS)$(CPP_DEPS)$(CXX_DEPS)$(C_UPPER_DEPS)$(S_UPPER_DEPS) $(outdir)/$(kl25zdir)/$(outfile)
	-@echo ' '

secondary-outputs:

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
