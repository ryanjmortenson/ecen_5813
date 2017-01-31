APP_SRC_DIR=app/src
APP_INC_DIR=app/inc
LINUX_X86=linux-x86
LINUX_ARM=linux-arm
KL25Z=kl25z
APPOUTDIR=app/out

APP_SRC += \
main.c \
data.c \
project_1.c \
memory.c 

APP_INC = $(subst src,inc,$(patsubst %.c,%.h,$(APP_SRC)))
X86_OBJS = $(subst src,out/$(LINUX_X86),$(patsubst %.c,%.o,$(APP_SRC)))
ARM_OBJS = $(subst src,out/$(LINUX_ARM),$(patsubst %.c,%.o,$(APP_SRC)))
25Z_OBJS = $(subst src,out/$(KL25Z),$(patsubst %.c,%.o,$(APP_SRC)))
					 
DEPS += $(patsubst %.o,%.d, $(OBJS) $(KL25Z_OBJS) $(ARM_OBJS))
