LINUXDIR = linux
KL25ZDIR = kl25z
APPOUTDIR = app/out
APPSRCDIR = app/src

ALL_SRCS := $(wildcard $(APPSRCDIR)/*.c)
C_SRCS += $(ALL_SRCS)
OBJS += $(patsubst %.c,%.o, $(subst src,out/$(LINUXDIR), $(ALL_SRCS)))
KL25Z_OBJS += $(patsubst %.c,%.o, $(subst src,out/$(KL25ZDIR), $(ALL_SRCS)))
C_DEPS += $(patsubst %.c,%.d, $(subst src,out, $(ALL_SRCS))) 

$(APPOUT)/$(KL25ZDIR)/%.o: app/src/%.c
	$(MKDIR) $(APPOUTDIR)/$(KL25ZDIR)
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"./app/src" -I"./app/inc" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

app/out/$(LINUXDIR)/%.o: app/src/%.c
	$(MKDIR) $(APPOUTDIR)/$(LINUXDIR)
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	gcc -I"./app/src" -I"./app/inc" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
