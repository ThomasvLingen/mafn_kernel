SILENT = @

# This Makefile assumes the following environment_variable is set:
# - PROJECT_ROOT

# Compiler flags
C_INCLUDE = -Iinclude/
C_FLAGS = -Wall -Wextra -std=gnu99 -ffreestanding $(C_INCLUDE)

# Archiver flags
AR_FLAGS = rcs

# Files to compile
SRC_PATH = .
LIBK_C_FILES = $(shell find $(SRC_PATH) -name '*.c')
LIBK_ASM_FILES = $(shell find $(SRC_PATH) -name '*.s')

LIBK_H_FILES = $(shell find $(SRC_PATH) -name '*.h')
LIBK_ALL_FILES = $(LIBK_C_FILES) $(LIBK_ASM_FILES) $(LIBK_H_FILES)
LIBK_OBJ_FILES = $(LIBK_C_FILES:.c=.o) $(LIBK_ASM_FILES:.s=.o)

# Path for the resulting file
BUILD_PATH = build/
LIBK_NAME = libk.a
LIBK_EXEC = $(BUILD_PATH)$(LIBK_NAME)

# Targets
all : libk
libk : $(LIBK_EXEC)

# Compile stuff
%.o : %.s
	@echo AS $<
	$(SILENT) $(AS) $< -o $@

%.o : %.c
	@echo CC $<
	$(SILENT) $(CC) -c $< -o $@ $(C_FLAGS)

$(LIBK_EXEC) : $(LIBK_OBJ_FILES)
	@echo
	mkdir -p $(BUILD_PATH)
	@echo AR $@
	$(SILENT) $(AR) $(AR_FLAGS) $(LIBK_EXEC) $(LIBK_OBJ_FILES)
	@echo

# Utility rules
search_for_tabs: $(SRC_PATH)
	grep -r '	' $(SRC_PATH)

tabs_to_spaces: $(ALL_FILES)
	sed -i 's/	/    /g' $(ALL_FILES)

check_vars:
	echo $(PROJECT_ROOT)

.PHONY: clean
clean:
	@echo "Cleaning build"
	rm -rf $(shell find $(SRC_PATH) -name '*.o')
	rm -rf $(BUILD_PATH)
