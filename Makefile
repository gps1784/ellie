# We shouldn't need to modify these directory variables,
# but I will leave the option to do so here.
BIN   := bin
BUILD := build
INC   := include
LIB   := lib
SRC   := src
TEST  := test

# Change the compiler and flags as you see fit
# LANG should match your programming language
LANG     := .cc
COMPILE   = $(COMPILE$(LANG))
CC       := g++
CXX      := g++
CFLAGS   := -Wall
CPPFLAGS := -I $(INC)
LDFLAGS  := $(CPPFLAGS)
LDLIBS   :=

# "Special" settings for Windows,
# but this makefile is only tested with Windows 10
ifeq ($(OS), Windows_NT)
  EXE     := .exe
  #LDFLAGS += -lmingw32
  ifeq ($(findstring debug, $(MAKECMDGOALS)),)
    #LDFLAGS += -mwindows
  endif
endif

# Alter the target name to match the src/example.c
TARGET_NAME := example
TARGET_SRC  := $(BIN)/$(SRC)/$(TARGET_NAME)
TARGET_TEST := $(BIN)/$(TEST)/$(TARGET_NAME)
TARGET_SRC_EXE  := $(TARGET_SRC)$(EXE)
TARGET_TEST_EXE := $(TARGET_TEST)$(EXE)

# Both src/ and test/ have an example.cc file  -> ..._CORE
# Anything under src/example/ or test/example/ -> ..._ALL
# ..._CODE_... includes source (.c/.cpp/.cc/etc) files
# ..._OBJ_...  includes object files under build/
# ..._DEP_...  includes autogenerated dependency files for each object file
SRC_CODE_CORE := $(SRC)/$(TARGET_NAME)$(LANG)
SRC_OBJ_CORE  := $(addprefix $(BUILD)/, $(SRC_CODE_CORE:$(LANG)=.o))
SRC_DEP_CORE  := $(addprefix $(BUILD)/, $(SRC_CODE_CORE:$(LANG)=.d))

SRC_CODE_ALL := $(shell find $(SRC)/$(TARGET_NAME) -type f -name '*$(LANG)')
SRC_OBJ_ALL  := $(addprefix $(BUILD)/, $(SRC_CODE_ALL:$(LANG)=.o))
SRC_DEP_ALL  := $(addprefix $(BUILD)/, $(SRC_CODE_ALL:$(LANG)=.d))
SRC_DEPS     := $(SRC_DEP_CORE) $(SRC_DEP_ALL)

TEST_CODE_CORE := $(TEST)/$(TARGET_NAME)$(LANG)
TEST_OBJ_CORE  := $(addprefix $(BUILD)/, $(TEST_CODE_CORE:$(LANG)=.o))
TEST_DEP_CORE  := $(addprefix $(BUILD)/, $(TEST_CODE_CORE:$(LANG)=.d))

TEST_CODE_ALL := $(shell find $(TEST)/$(TARGET_NAME) -type f -name '*$(LANG)')
TEST_OBJ_ALL  := $(addprefix $(BUILD)/, $(TEST_CODE_ALL:$(LANG)=.o))
TEST_DEP_ALL  := $(addprefix $(BUILD)/, $(TEST_CODE_ALL:$(LANG)=.d))
TEST_DEPS     := $(TEST_DEP_CORE) $(TEST_DEP_ALL)

# A list of directories, used to ensure directory creation before file creation
BIN_DIRS        := $(sort $(dir $(TARGET_SRC) $(TARGET_TEST)))
BUILD_SRC_DIRS  := $(sort $(dir $(SRC_OBJ_CORE) $(SRC_OBJ_ALL)))
BUILD_TEST_DIRS := $(sort $(dir $(TEST_OBJ_CORE) $(TEST_OBJ_ALL)))

all: exec-src
run: exec-src
	$(TARGET_SRC_EXE)
test: exec-test
	$(TARGET_TEST_EXE)
debug:    CFLAGS   += -g
debug:    CXXFLAGS += -g
pedantic: CFLAGS   += -Wextra -Wpedantic
pedantic: CXXFLAGS += -Wextra -Wpedantic
clean:
	$(RM) -rf $(BIN) $(BUILD)

# If .cc (c++) files are being used, attach googletest (GTEST)
# GTEST has associated creation, cleanup, and libraries
ifeq ($(LANG), .cc)
  GTEST         := $(LIB)/googletest/googletest
  GTEST_OBJ_ALL := $(GTEST)/make/gtest-all.o
  CPPFLAGS      += -I $(GTEST)/include
  LDFLAGS       += -L $(GTEST)/make
  exec-test: LDLIBS += -l:gtest_main.a
  exec-test: build-googletest
  build-googletest:
		$(MAKE) -C $(GTEST)/make gtest_main.a
  clean: clean-googletest
  clean-googletest:
		$(MAKE) -C $(GTEST)/make clean
endif

# Build the directories, *THEN* populate with obj/executables
build-src:  | $(BUILD_SRC_DIRS)
build-src:  $(SRC_DEPS) $(SRC_OBJ_CORE) $(SRC_OBJ_ALL)
build-test: | $(BUILD_TEST_DIRS)
build-test: $(TEST_DEPS) $(TEST_OBJ_CORE) $(TEST_OBJ_ALL)
exec-src exec-test: | $(BIN_DIRS)
exec-src:   build-src $(TARGET_SRC)
exec-test:  build-src build-test $(TARGET_TEST)

$(BUILD_SRC_DIRS) $(BUILD_TEST_DIRS) $(BIN_DIRS):
	@mkdir -p $@

# bin/src/example should *NOT* touch Main() in test/example.cc
# bin/test/example should *NOT* touch Main() in src/example.cc
# Therefore, we exclude SRC_OBJ_CORE from bin/src and vice-versa
$(TARGET_SRC): $(SRC_OBJ_CORE)
$(TARGET_TEST): $(TEST_OBJ_CORE) $(TEST_OBJ_ALL)
$(TARGET_SRC) $(TARGET_TEST): $(SRC_OBJ_ALL)
	$(LINK.o) $^ $(LOADLIBES) $(LDLIBS) -o $@

# Autogenerate dependencies based on the C preprocessor's needed files
$(BUILD)/%.d: %$(LANG) Makefile
	@mkdir -p $(@D)
	$(CPP) $(CPPFLAGS) -M '$<' -MF '$@' -MT '$(BUILD)/$*.o' -MT '$@'

# In the end, we will hijack make's built-in $(COMPILE.x) variables
# to do whatever we might need. We can just use the existing compiler flags,
# pre-assembled by make.
$(BUILD)/%.o: %$(LANG)
	$(COMPILE) $(OUTPUT_OPTION) $<

# Do *NOT* include the dependencies if we are "clean"ing on this pass.
# This corrects the behavior in case you type `make clean rebuild all`
ifeq ($(findstring clean, $(MAKECMDGOALS)),)
  include $(SRC_DEPS) $(TEST_DEPS)
endif

.PHONY: all run test debug pedantic clean
.PHONY: build-src build-test build-googletest
.PHONY: exec-src exec-test
.PHONY: clean-googletest