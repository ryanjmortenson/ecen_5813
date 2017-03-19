
# Set up some directories for later use
KL25Z_PROP_INC_DIR=prop/kl25z/inc
KL25Z_PROP_SRC_DIR=prop/kl25z/src
KL25Z_PROP_OUT=prop/kl25z/out

# Build a list of source
KL25Z_PROP_SRCS+= \
	$(KL25Z_PROP_SRC_DIR)/spi.c \
	$(KL25Z_PROP_SRC_DIR)/startup_MKL25Z4.S \
	$(KL25Z_PROP_SRC_DIR)/system_MKL25Z4.c \
	$(KL25Z_PROP_SRC_DIR)/memory_dma.c \
	$(KL25Z_PROP_SRC_DIR)/uart.c

# Build a list of objects and dependencies
KL25Z_PROP_OBJS=$(subst src,out,$(patsubst %.S,%.o,$(patsubst %.c,%.o,$(KL25Z_PROP_SRCS))))
KL25Z_PROP_DEPS=$(patsubst %.o,%.d,$(KL25Z_PROP_OBJS))

# Build a list of things to clean
CLEAN+=$(KL25Z_PROP_OBJS) \
       $(KL25Z_PROP_DEPS) \
       $(KL25Z_PROP_OUT)
