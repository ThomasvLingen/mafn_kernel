SILENT = @

# This Makefile assumes the following environment_variable is set:
# - PROJECT_ROOT

# Arch dir
ARCH_DIR = arch/$(ARCH)

# Libk
LIBK_PATH = $(PROJECT_ROOT)/src/libc
LIBK_HEADERS = $(LIBK_PATH)/include
LIBK_LIB = $(LIBK_PATH)/build

# Compiler flags
INCLUDE_PATHS = -Iinclude -I$(LIBK_HEADERS)
COMPILER_FLAGS = -g -Wall -Wextra -std=gnu99 -ffreestanding $(INCLUDE_PATHS)

# Linker script
LINKER_SCRIPT = $(ARCH_DIR)/linker.ld

# Linker flags
LINKER_PATH = -L$(LIBK_LIB)
LINKER_FLAGS = $(LINKER_PATH) -T $(LINKER_SCRIPT) -nostdlib -lgcc -lk

# Files to compile
SRC_PATH = .
# Architecture agnostic files
KERNEL_C_FILES = $(shell find $(SRC_PATH) -name '*.c' -not -path "./arch/*")
KERNEL_ASM_FILES = $(shell find $(SRC_PATH) -name '*.s' -not -path "./arch/*")
# Then architecture specific files
KERNEL_C_FILES += $(shell find $(ARCH_DIR) -name '*.c')
KERNEL_ASM_FILES += $(shell find $(ARCH_DIR) -name '*.s')

KERNEL_OBJ_FILES = $(KERNEL_C_FILES:.c=.o) $(KERNEL_ASM_FILES:.s=.o)

# Path for the resulting file
BUILD_PATH = build/
KERNEL_NAME = mafn_kernel.bin
KERNEL_EXEC = $(BUILD_PATH)$(KERNEL_NAME)

# Targets
all : kernel
kernel : $(KERNEL_EXEC)

# Compile stuff
%.o : %.s
	@echo AS $<
	$(SILENT) $(AS) $< -o $@

%.o : %.c
	@echo CC $<
	$(SILENT) $(CC) -c $< $(COMPILER_FLAGS) -o $@

$(KERNEL_EXEC) : $(KERNEL_OBJ_FILES)
	@echo
	mkdir -p $(BUILD_PATH)
	@echo LD $@
	$(SILENT) $(LD) $(COMPILER_FLAGS) $(KERNEL_OBJ_FILES) $(LINKER_FLAGS) -o $(KERNEL_EXEC)
	@echo

.PHONY: clean
clean:
	@echo "Cleaning build"
	rm -rf $(shell find $(SRC_PATH) -name '*.o')
	rm -rf $(BUILD_PATH)
