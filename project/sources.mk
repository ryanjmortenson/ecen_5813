
# Set up some directories for later use
APP_SRC_DIR=app/src
APP_INC_DIR=app/inc
APP_OUT=app/out

# Build the output names for the application
X86_APP_OUT=$(APP_OUT)/$(X86)
ARM_APP_OUT=$(APP_OUT)/$(ARM)
25Z_APP_OUT=$(APP_OUT)/$(25Z)

# Sources for the application
NON_MAIN_SRC+= \
	$(APP_SRC_DIR)/memory.c \
	$(APP_SRC_DIR)/data.c \
	$(APP_SRC_DIR)/circbuf.c \
	$(APP_SRC_DIR)/log_item.c \
	$(APP_SRC_DIR)/nordic.c \
	$(APP_SRC_DIR)/project1.c \
	$(APP_SRC_DIR)/project2.c \
	$(APP_SRC_DIR)/project3.c \
	$(APP_SRC_DIR)/log.c

APP_SRC+= \
	$(NON_MAIN_SRC) \
	$(APP_SRC_DIR)/main.c

TEST_SRC+= \
	$(NON_MAIN_SRC) \
	$(APP_SRC_DIR)/unit_tests.c \
	$(APP_SRC_DIR)/unit_data.c \
	$(APP_SRC_DIR)/unit_memory.c \
	$(APP_SRC_DIR)/unit_circbuf.c

# Make a src list without any directories to feed into the allasm/alli targets
SRC_LIST = $(subst $(APP_SRC_DIR)/,,$(APP_SRC))

# Build a list objects for each platform
X86_OBJS = $(subst src,out/$(X86),$(patsubst %.c,%.o,$(APP_SRC)))
ARM_OBJS = $(subst src,out/$(ARM),$(patsubst %.c,%.o,$(APP_SRC)))
25Z_OBJS = $(subst src,out/$(25Z),$(patsubst %.c,%.o,$(APP_SRC)))
X86_TEST_OBJS = $(subst src,out/$(X86),$(patsubst %.c,%.o,$(TEST_SRC)))
ARM_TEST_OBJS = $(subst src,out/$(ARM),$(patsubst %.c,%.o,$(TEST_SRC)))
25Z_TEST_OBJS = $(subst src,out/$(25Z),$(patsubst %.c,%.o,$(TEST_SRC)))

# Build a list of .d files to clean
APP_DEPS += $(patsubst %.o,%.d, $(OBJS) $(25Z_OBJS) $(ARM_OBJS))

# Add to List of items that need to be cleaned
CLEAN+=$(25Z_OBJS) \
       $(ARM_OBJS) \
       $(X86_OBJS) \
       $(APP_DEPS) \
       $(TEST_OBJS) \
       $(APP_OUT)
