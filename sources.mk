APP_SRC_DIR=app/src
APP_INC_DIR=app/inc
LINUX_X86=linux-x86
LINUX_ARM=linux-arm
KL25Z=kl25z
APP_OUT=app/out
LINUX_X86_OUT=$(APP_OUT)/$(LINUX_X86)
LINUX_ARM_OUT=$(APP_OUT)/$(LINUX_ARM)
KL25Z_OUT=$(APP_OUT)/$(KL25Z)

APP_SRC += \
$(APP_SRC_DIR)/main.c \
$(APP_SRC_DIR)/memory.c \
$(APP_SRC_DIR)/data.c \
$(APP_SRC_DIR)/project1.c 

APP_INC = $(subst src,inc,$(patsubst %.c,%.h,$(APP_SRC)))
SRC_LIST = $(subst $(APP_SRC_DIR)/,,$(APP_SRC))
X86_OBJS = $(subst src,out/$(LINUX_X86),$(patsubst %.c,%.o,$(APP_SRC)))
ARM_OBJS = $(subst src,out/$(LINUX_ARM),$(patsubst %.c,%.o,$(APP_SRC)))
25Z_OBJS = $(subst src,out/$(KL25Z),$(patsubst %.c,%.o,$(APP_SRC)))
DEPS += $(patsubst %.o,%.d, $(OBJS) $(KL25Z_OBJS) $(ARM_OBJS))
