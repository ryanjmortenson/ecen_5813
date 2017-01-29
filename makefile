RM := rm -rf
MKDIR := mkdir -p
outdir=out
kl25zdir=kl25z
linuxdir=linux-x86
bbbdir=linux-arm
outfile=main.elf
mapfile=main.map
kl25z_target=$(outdir)/$(kl25zdir)/$(outfile)
linux_target=$(outdir)/$(linuxdir)/$(outfile)
bbb_target=$(outdir)/$(bbbdir)/$(outfile)
maps=$(subst elf,map,$(kl25z_target) $(linux_target) $(bbb_target))

-include prop/$(kl25zdir)/subdir.mk
-include app/subdir.mk

# All Target
all: $(kl25z_target) $(linux_target) $(bbb_target)

debug:
	@echo $(OBJS)
	@echo $(KL25Z_OBJS)
	@echo $(ARM_OBJS)
	@echo $(C_SRCS)
	@echo $(DEPS)
	@echo $(ALL_SRCS)

# Tool invocations
$(kl25z_target) : $(KL25Z_OBJS) $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Cross Linker'
	@echo 'Creating out directory'
	-$(MKDIR) $(outdir)/$(kl25zdir)
	arm-none-eabi-g++ -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -T "MKL25Z128xxx4_flash.ld" -Xlinker --gc-sections -L"./prop/kl25z/linker" -Wl,-Map,"$(subst elf,map,$(kl25z_target))" -specs=nano.specs -specs=nosys.specs -o $(kl25z_target)  $(KL25Z_OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

$(linux_target) : $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking Linux-x86 Linker'
	@echo 'Creating out directory'
	-$(MKDIR) $(outdir)/$(linuxdir)
	gcc -Xlinker -Map=$(subst elf,map,$(linux_target)) -o $(linux_target) $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

$(bbb_target) : $(ARM_OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking Linux-ARM Cross Linker'
	@echo 'Creating out directory'
	-$(MKDIR) $(outdir)/$(bbbdir)
	arm-linux-gnueabihf-gcc -Xlinker -Map=$(subst elf,map,$(bbb_target)) -o $(bbb_target) $(ARM_OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS) $(KL25Z_OBJS) $(ARM_OBJS) $(DEPS) $(C_UPPER_DEPS) $(S_UPPER_DEPS) $(kl25z_target) $(linux_target) $(bbb_target) $(maps)
