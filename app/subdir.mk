########################################################
# This make file builds the object files for all 3 
# targets kl25z, linux-86, and linux-arm for beaglebone.
# Map files are also created.  The output for the 
# object files is in out/$(TARGET)
# #####################################################


# Directories used for build
LINUXDIR=linux-x86
BBBDIR=linux-arm
KL25ZDIR=kl25z
APPOUTDIR=app/out
APPSRCDIR=app/src

# Get a list of the sources in the src directory
ALL_SRCS := $(wildcard $(APPSRCDIR)/*.c)
C_SRCS += $(ALL_SRCS)

# Do a subst on all sources to create the set of .o files that need to be created
OBJS += $(patsubst %.c,%.o, $(subst src,out/$(LINUXDIR), $(ALL_SRCS)))
KL25Z_OBJS += $(patsubst %.c,%.o, $(subst src,out/$(KL25ZDIR), $(ALL_SRCS)))
ARM_OBJS += $(patsubst %.c,%.o, $(subst src,out/$(BBBDIR), $(ALL_SRCS)))

# Create a list of .d files to pass remove on clean
DEPS += $(patsubst %.o,%.d, $(OBJS) $(KL25Z_OBJS) $(ARM_OBJS))

# KL25Z target
$(APPOUTDIR)/$(KL25ZDIR)/%.o: $(APPSRCDIR)/%.c
	$(MKDIR) $(APPOUTDIR)/$(KL25ZDIR)
	@echo 'Invoking ARM Cross Compiler'
	@echo 'Building file: $<'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"./app/src" -I"./app/inc" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

# Linux-x86 target 
$(APPOUTDIR)/$(LINUXDIR)/%.o: $(APPSRCDIR)/%.c
	$(MKDIR) $(APPOUTDIR)/$(LINUXDIR)
	@echo 'Building file: $<'
	@echo 'Invoking Linux x86 Compiler'
	gcc -g3 -I"./app/src" -I"./app/inc" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

# Linux-arm target 
$(APPOUTDIR)/$(BBBDIR)/%.o: $(APPSRCDIR)/%.c
	$(MKDIR) $(APPOUTDIR)/$(BBBDIR)
	@echo $(ARM_OBJS)
	@echo 'Building file: $<'
	@echo 'Invoking Linux ARM Cross Compiler'
	arm-linux-gnueabihf-gcc -g3 -I"./app/src" -I"./app/inc" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
