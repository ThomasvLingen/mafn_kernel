SILENT = @

# Compiler
CC = i686-elf-gcc 
LD = $(CC)

# Assembler
AS = i686-elf-as

# Compiler flags
# Wall = all warnings
# Wextra = extra warnings
INCLUDE_PATHS = -Isrc/ 
COMPILER_FLAGS = -Wall -Wextra -std=gnu99 -ffreestanding $(INCLUDE_PATHS)

# Linker script
LINKER_SCRIPT = linker.ld

# Linker flags
LINKER_FLAGS = -T $(LINKER_SCRIPT) -nostdlib -lgcc

# Files to compile
SRC_PATH = src/
SRC_C_FILES = $(shell find $(SRC_PATH) -name '*.c')
SRC_ASM_FILES = $(shell find $(SRC_PATH) -name '*.s')

H_FILES = $(shell find $(SRC_PATH) -name '*.h')
ALL_FILES = $(SRC_C_FILES) $(SRC_ASM_FILES) $(H_FILES)
OBJ_FILES = $(SRC_C_FILES:.c=.o) $(SRC_ASM_FILES:.s=.o)

# Path for the resulting file
BUILD_PATH = build/
PROGRAM_NAME = mafn_kernel.bin
EXEC = $(BUILD_PATH)$(PROGRAM_NAME)

# Compile stuff
%.o : %.s
	@echo AS $<
	$(SILENT) $(AS) $< -o $@

%.o : %.c
	@echo CC $<
	$(SILENT) $(CC) -c $< $(COMPILER_FLAGS) -o $@

$(EXEC) : $(OBJ_FILES)
	@echo
	mkdir -p $(BUILD_PATH)
	@echo LD $@
	$(SILENT) $(LD) $(COMPILER_FLAGS) $(OBJ_FILES) $(LINKER_FLAGS) -o $(EXEC)
	@echo

all : $(EXEC)

qemu_run : $(EXEC)
	qemu-system-i386 -kernel $(EXEC)

search_for_tabs: $(SRC_PATH)
	grep -r '	' $(SRC_PATH)

tabs_to_spaces: $(ALL_FILES)
	sed -i 's/	/    /g' $(ALL_FILES)

.PHONY: clean
clean:
	@echo "Cleaning build"
	rm -rf $(shell find $(SRC_PATH) -name '*.o')
	rm -rf $(BUILD_PATH)*
