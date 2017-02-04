APP_SRC_DIR=app/src
APP_INC_DIR=app/inc
APP_OUT=app/out
X86_APP_OUT=$(APP_OUT)/$(X86)
ARM_APP_OUT=$(APP_OUT)/$(ARM)
25Z_APP_OUT=$(APP_OUT)/$(25Z)

APP_SRC += \
$(APP_SRC_DIR)/main.c \
$(APP_SRC_DIR)/memory.c \
$(APP_SRC_DIR)/data.c \
$(APP_SRC_DIR)/project1.c 

APP_INC = $(subst src,inc,$(patsubst %.c,%.h,$(APP_SRC)))
SRC_LIST = $(subst $(APP_SRC_DIR)/,,$(APP_SRC))
X86_OBJS = $(subst src,out/$(X86),$(patsubst %.c,%.o,$(APP_SRC)))
ARM_OBJS = $(subst src,out/$(ARM),$(patsubst %.c,%.o,$(APP_SRC)))
25Z_OBJS = $(subst src,out/$(25Z),$(patsubst %.c,%.o,$(APP_SRC)))
DEPS += $(patsubst %.o,%.d, $(OBJS) $(25Z_OBJS) $(ARM_OBJS))
