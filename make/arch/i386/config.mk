ARCH_TRIPLET = i686-elf

# i686 elf compiler
export CC = $(ARCH_TRIPLET)-gcc
export LD = $(CC)

# Assembler
export AS = $(ARCH_TRIPLET)-as

# Archiver (for creating static libraries)
export AR = $(ARCH_TRIPLET)-ar