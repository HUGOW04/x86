# Compiler and flags
NASM = nasm
GCC = gcc
LD = ld

NASMFLAGS = -f elf
GCCFLAGS = -ffreestanding -m32 -march=i386 -mpreferred-stack-boundary=2 -m32 -nostdlib -fno-pie -fno-stack-protector
LDFLAGS = -melf_i386 -Ttext 0x1000 --oformat binary

# Directories
SRC_DIR = .
OBJ_DIR = obj
BOOT_DIR = $(SRC_DIR)/boot
KERNEL_DIR = $(SRC_DIR)/kernel
DRIVERS_DIR = $(SRC_DIR)/drivers
CPU_DIR = $(SRC_DIR)/cpu
LIBC_DIR = $(SRC_DIR)/libc

# Source files
BOOT_ASM_FILES = $(wildcard $(BOOT_DIR)/*.asm)
KERNEL_ASM_FILES = $(wildcard $(KERNEL_DIR)/*.asm)
KERNEL_C_FILES = $(wildcard $(KERNEL_DIR)/*.c)
KERNEL_H_FILES = $(wildcard $(KERNEL_DIR)/*.h)
DRIVERS_C_FILES = $(wildcard $(DRIVERS_DIR)/*.c)
DRIVERS_H_FILES = $(wildcard $(DRIVERS_DIR)/*.h)
CPU_ASM_FILES = $(wildcard $(CPU_DIR)/*.asm)
CPU_C_FILES = $(wildcard $(CPU_DIR)/*.c)
CPU_H_FILES = $(wildcard $(CPU_DIR)/*.h)
LIBC_C_FILES = $(wildcard $(LIBC_DIR)/*.c)
LIBC_H_FILES = $(wildcard $(LIBC_DIR)/*.h)

# Object files
BOOT_OBJS = $(patsubst $(BOOT_DIR)/%.asm, $(OBJ_DIR)/%.o, $(BOOT_ASM_FILES))
KERNEL_OBJS = $(patsubst $(KERNEL_DIR)/%.asm, $(OBJ_DIR)/%.o, $(KERNEL_ASM_FILES)) \
              $(patsubst $(KERNEL_DIR)/%.c, $(OBJ_DIR)/%.o, $(KERNEL_C_FILES))
DRIVERS_OBJS = $(patsubst $(DRIVERS_DIR)/%.c, $(OBJ_DIR)/%.o, $(DRIVERS_C_FILES))
CPU_OBJS = $(patsubst $(CPU_DIR)/%.asm, $(OBJ_DIR)/%.o, $(CPU_ASM_FILES)) \
              $(patsubst $(CPU_DIR)/%.c, $(OBJ_DIR)/%.o, $(CPU_C_FILES))
LIBC_OBJS = $(patsubst $(LIBC_DIR)/%.c, $(OBJ_DIR)/%.o, $(LIBC_C_FILES))
# Targets
all: run

$(OBJ_DIR)/kernel.bin: $(KERNEL_OBJS) $(DRIVERS_OBJS) $(CPU_OBJS) $(LIBC_OBJS)
	$(LD) $(LDFLAGS) -e _start -o $@ $^

$(OBJ_DIR)/%.o: $(BOOT_DIR)/%.asm
	$(NASM) $(NASMFLAGS) -o $@ $<

$(OBJ_DIR)/%.o: $(KERNEL_DIR)/%.asm
	$(NASM) $(NASMFLAGS) -o $@ $<

$(OBJ_DIR)/%.o: $(CPU_DIR)/%.asm
	$(NASM) $(NASMFLAGS) -o $@ $<

$(OBJ_DIR)/%.o: $(KERNEL_DIR)/%.c $(KERNEL_H_FILES)
	$(GCC) $(GCCFLAGS) -c -o $@ $<

$(OBJ_DIR)/%.o: $(DRIVERS_DIR)/%.c $(DRIVERS_H_FILES)
	$(GCC) $(GCCFLAGS) -c -o $@ $<

$(OBJ_DIR)/%.o: $(CPU_DIR)/%.c $(CPU_H_FILES)
	$(GCC) $(GCCFLAGS) -c -o $@ $<

$(OBJ_DIR)/%.o: $(LIBC_DIR)/%.c $(LIBC_H_FILES)
	$(GCC) $(GCCFLAGS) -c -o $@ $<

$(OBJ_DIR)/bootsect.bin: $(BOOT_DIR)/bootsect.asm
	$(NASM) -f bin -o $@ $<

$(OBJ_DIR)/os-image.bin: $(OBJ_DIR)/bootsect.bin $(OBJ_DIR)/kernel.bin
	cat $^ > $@

run: $(OBJ_DIR)/os-image.bin
	qemu-system-i386 -drive format=raw,file=$<

clear:
	rm -f $(OBJ_DIR)/*.bin
	rm -f $(OBJ_DIR)/*.o