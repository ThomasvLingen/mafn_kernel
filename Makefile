SILENT = @

# Set project root, which will be used by recursive make calls
PROJECT_ROOT = $(CURDIR)
export PROJECT_ROOT

# Determine $ARCH
include $(PROJECT_ROOT)/config.mk
# Include architecture specific config (for compiler, linker and assembler)
include $(PROJECT_ROOT)/make/arch/$(ARCH)/config.mk

# Submodule paths
KERNEL_ROOT = $(PROJECT_ROOT)/src/kernel
KERNEL_BIN = $(KERNEL_ROOT)/build/mafn_kernel.bin
LIBC_ROOT = $(PROJECT_ROOT)/src/libc

# Build path
BUILD_PATH = $(PROJECT_ROOT)/build
IMAGE_PATH = $(PROJECT_ROOT)/image

ISO_PATH = $(BUILD_PATH)/mafn_kernel.iso

# Misc
QEMU_LOG_PATH = ./LOG_mafn_kernel
QEMU_CMD = qemu-system-i386 -kernel $(KERNEL_BIN) -m 1024 -serial file:$(QEMU_LOG_PATH)

ifeq ($(ARCH),)
$(error ARCH not set (does config.mk make sense?))
endif

all : mafn_kernel

libc :
	@make -C $(LIBC_ROOT)

mafn_kernel : libc
	@make -C $(KERNEL_ROOT)
	cp $(KERNEL_BIN) $(PROJECT_ROOT)

qemu_run : mafn_kernel
	$(QEMU_CMD)

qemu_debug : mafn_kernel
	$(QEMU_CMD) -s -S &
	gdb -tui $(KERNEL_BIN) -ex "target remote localhost:1234"

iso: mafn_kernel $(ISO_PATH)

$(BUILD_PATH):
	mkdir -p $(BUILD_PATH)

$(IMAGE_PATH):
	mkdir -p $(IMAGE_PATH)/boot/grub

$(ISO_PATH): $(BUILD_PATH) $(IMAGE_PATH)
	@echo "Building .iso"
	cp grub.cfg $(IMAGE_PATH)/boot/grub/
	cp mafn_kernel.bin $(IMAGE_PATH)/boot/
	grub-mkrescue -o $(ISO_PATH) $(IMAGE_PATH)

.PHONY: clean
clean:
	@echo "Cleaning build"
	@make clean -C $(KERNEL_ROOT)
	@make clean -C $(LIBC_ROOT)
	rm -rf $(BUILD_PATH)
	rm -rf $(IMAGE_PATH)
	rm -rf $(QEMU_LOG_PATH)
	rm ./*.bin
