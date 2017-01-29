LINUXDIR=linux-x86
BBBDIR=linux-arm
KL25ZDIR=kl25z
APPOUTDIR=app/out
APPSRCDIR=app/src

ALL_SRCS := $(wildcard $(APPSRCDIR)/*.c)
C_SRCS += $(ALL_SRCS)
OBJS += $(patsubst %.c,%.o, $(subst src,out/$(LINUXDIR), $(ALL_SRCS)))
KL25Z_OBJS += $(patsubst %.c,%.o, $(subst src,out/$(KL25ZDIR), $(ALL_SRCS)))
ARM_OBJS += $(patsubst %.c,%.o, $(subst src,out/$(BBBDIR), $(ALL_SRCS)))
DEPS += $(patsubst %.o,%.d, $(OBJS) $(KL25Z_OBJS) $(ARM_OBJS))

$(APPOUTDIR)/$(KL25ZDIR)/%.o: $(APPSRCDIR)/%.c
	$(MKDIR) $(APPOUTDIR)/$(KL25ZDIR)
	@echo 'Invoking ARM Cross Compiler'
	@echo 'Building file: $<'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"./app/src" -I"./app/inc" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

$(APPOUTDIR)/$(LINUXDIR)/%.o: $(APPSRCDIR)/%.c
	$(MKDIR) $(APPOUTDIR)/$(LINUXDIR)
	@echo 'Building file: $<'
	@echo 'Invoking Linux x86 Compiler'
	gcc -I"./app/src" -I"./app/inc" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

$(APPOUTDIR)/$(BBBDIR)/%.o: $(APPSRCDIR)/%.c
	$(MKDIR) $(APPOUTDIR)/$(BBBDIR)
	@echo $(ARM_OBJS)
	@echo 'Building file: $<'
	@echo 'Invoking Linux ARM Cross Compiler'
	arm-linux-gnueabi-gcc -I"./app/src" -I"./app/inc" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
