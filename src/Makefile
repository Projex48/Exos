# Cross compiler
CC = i686-elf-gcc

# Flags
CFLAGS  = -std=gnu99 -ffreestanding -O2 -Wall -Wextra
LDFLAGS = -T linker.ld -ffreestanding -O2 -nostdlib
LIBS    = -lgcc

# === Source Files ===
C_SOURCES = kernel.c
ASM_SOURCES = boot.s

# === Object Files (auto-generated from source names) ===
C_OBJECTS   = $(C_SOURCES:.c=.o)
ASM_OBJECTS = $(ASM_SOURCES:.s=.o)
OBJS = $(C_OBJECTS) $(ASM_OBJECTS)

# Output
TARGET = exos

# Default target
all: $(TARGET)

# Link
$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

# Compile C files automatically
%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

# Assemble ASM files automatically
%.o: %.s
	$(CC) -c $< -o $@ $(CFLAGS)

# Clean
clean:
	rm -f *.o $(TARGET)

.PHONY: all clean