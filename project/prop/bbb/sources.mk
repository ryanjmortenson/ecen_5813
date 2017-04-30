# Set up some directories for later use
ARM_PROP_INC_DIR=prop/bbb/inc
ARM_PROP_SRC_DIR=prop/bbb/src
ARM_PROP_OUT=prop/bbb/out

# Build a list of source
ARM_PROP_SRCS+=$(ARM_PROP_SRC_DIR)/spi.c

# Build a list of objects and dependencies
ARM_PROP_OBJS=$(subst src,out,$(patsubst %.S,%.o,$(patsubst %.c,%.o,$(ARM_PROP_SRCS))))
ARM_PROP_DEPS=$(patsubst %.o,%.d,$(ARM_PROP_OBJS))

# Build a list of things to clean
CLEAN+=$(ARM_PROP_OBJS) \
       $(ARM_PROP_DEPS) \
       $(ARM_PROP_OUT)
