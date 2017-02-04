C_SRCS += \
./prop/kl25z/startup/system_MKL25Z4.c 

S_UPPER_SRCS += \
./prop/kl25z/startup/startup_MKL25Z4.S 

KL25Z_OBJS += \
./prop/kl25z/out/startup_MKL25Z4.o \
./prop/kl25z/out/system_MKL25Z4.o 

C_DEPS += \
./prop/kl25z/out/system_MKL25Z4.d 

S_UPPER_DEPS += \
./prop/kl25z/out/startup_MKL25Z4.d 

# Each subdirectory must supply rules for building sources it contributes
./prop/kl25z/out/%.o: ./prop/kl25z/startup/%.S
	@echo 'Building file: $<'
	mkdir -p ./prop/kl25z/out
	@echo 'Invoking: Cross ARM GNU Assembler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

./prop/kl25z/out/%.o: ./prop/kl25z/startup/%.c
	@echo 'Building file: $<'
	mkdir -p ./prop/kl25z/out
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"./prop/kl25z/src" -I"./prop/kl25z/inc" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
