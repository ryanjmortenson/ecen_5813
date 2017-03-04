
# Include proprieatry kl25z sources
-include prop/kl25z/sources.mk

# Set kl25z flags
KL25Z_CFLAGS=-specs=nosys.specs \
             -mcpu=cortex-m0plus \
             -mthumb \
             -T "MKL25Z128xxx4_flash.ld" \
             -Xlinker --gc-sections -L"./prop/kl25z/linker"

# Set up rules for proprietary kl25z targets
$(KL25Z_PROP_OUT)/%.o: CFLAGS+=-MD -MP
$(KL25Z_PROP_OUT)/%.o: $(KL25Z_PROP_SRC_DIR)/%.c
	$(BUILD_TARGET)
	$(BUILD_WITH)
	$(shell $(MK_DIR) $(KL25Z_PROP_OUT))
	$(CC) $(CFLAGS) -c -o "$@" "$<"

$(KL25Z_PROP_OUT)/%.o: $(KL25Z_PROP_SRC_DIR)/%.S
	$(BUILD_TARGET)
	$(BUILD_WITH)
	$(shell $(MK_DIR) $(KL25Z_PROP_OUT))
	$(CC) $(CFLAGS) -c -o "$@" "$<"

