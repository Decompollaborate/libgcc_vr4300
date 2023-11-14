MAKEFLAGS += --no-builtin-rules

# Ensure the build fails if a piped command fails
SHELL = /bin/bash
.SHELLFLAGS = -o pipefail -c

# Valid options are:
# o32
# n32
# o64
# n64
TARGET_ABI ?= o32

ifneq ($(TARGET_ABI),$(filter $(TARGET_ABI), o32 n32 o64 n64 eabi32 eabi64))
$(error Need to invoke make with a valid TARGET_ABI variable, like `make TARGET_ABI=o32`. Valid ABIs: o32, n32, o64, n64, eabi32, eabi64)
endif


# Output

BUILD_DIR       ?= build/$(TARGET_ABI)
TARGET          ?= libgcc_vr4300


CROSS           ?= mips-linux-gnu-


## Main targets

all: static

clean:
	$(RM) -rf $(BUILD_DIR)

distclean: clean
	$(RM) -rf build

static: $(BUILD_DIR)/$(TARGET).a


.PHONY: all clean distclean static
.DEFAULT_GOAL := all
.SECONDARY:


# Programs
CC              := $(CROSS)gcc
AS              := $(CROSS)as
AR              := $(CROSS)ar
OBJDUMP         := $(CROSS)objdump
OBJCOPY         := $(CROSS)objcopy


# objdump arguments
OBJDUMP_FLAGS   ?= --disassemble --reloc --disassemble-zeroes


# C compiler arguments
CSTD            ?= -std=c11
MIPS_VERSION    ?= -mips3
ENDIAN          ?= -EB
OPTFLAGS        ?= -Os -ffast-math -fno-unsafe-math-optimizations
INC             ?= include
DEP_FLAGS       ?= -MMD -MP
WARNINGS        ?= -Wall -Wextra -Wpedantic
CFLAGS          ?= -march=vr4300 -mfix4300 -G0 -fno-PIC -mno-abicalls -nostdinc -Wa,-no-pad-sections -mdivide-breaks -fno-toplevel-reorder -ffreestanding

ifeq ($(TARGET_ABI),o32)
ABI             := -mabi=32
OBJDUMP_FLAGS   += -Mreg-names=32
else ifeq ($(TARGET_ABI),n32)
ABI             := -mabi=n32
OBJDUMP_FLAGS   += -Mreg-names=n32
else ifeq ($(TARGET_ABI),o64)
ABI             := -mabi=o64
OBJDUMP_FLAGS   += -Mreg-names=64
else ifeq ($(TARGET_ABI),n64)
ABI             := -mabi=64
OBJDUMP_FLAGS   += -Mreg-names=64
else ifeq ($(TARGET_ABI),eabi32)
ABI             := -mabi=eabi -mgp32 -mfp32
else ifeq ($(TARGET_ABI),eabi64)
ABI             := -mabi=eabi -mgp64 -mfp64
endif


## Autogenerated based on $(INC)
IINC            ?= $(foreach f, $(INC), -I $(f))


# Paths and file finding
SRC_DIRS        := $(shell find src -type d)

C_FILES         := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
S_FILES         := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.s))
O_FILES         := $(foreach f,$(S_FILES:.s=.o),$(BUILD_DIR)/$f) \
                   $(foreach f,$(C_FILES:.c=.o),$(BUILD_DIR)/$f)

D_FILES         := $(O_FILES:.o=.d)


# Create build directories
$(shell mkdir -p $(foreach dir,$(SRC_DIRS),$(BUILD_DIR)/$(dir)))


## Recipes

$(BUILD_DIR)/%.a: $(O_FILES)
	$(AR) rcs $@ $^

$(BUILD_DIR)/%.o: %.c
	$(CC) $(ABI) -c $(CSTD) $(MIPS_VERSION) $(ENDIAN) $(OPTFLAGS) $(IINC) $(DEP_FLAGS) $(WARNINGS) $(CFLAGS) -o $@ $<
	$(OBJCOPY) --set-section-alignment ".text*=4" --set-section-alignment ".data*=8" --set-section-alignment ".rodata=8" --set-section-alignment ".bss*=8" $@
	@$(OBJDUMP) $(OBJDUMP_FLAGS) $@ > $(@:.o=.dump.s)

$(BUILD_DIR)/%.o: %.s
	$(CC) $(ABI) -x assembler-with-cpp -c $(CSTD) $(MIPS_VERSION) $(ENDIAN) $(OPTFLAGS) $(IINC) $(DEP_FLAGS) $(WARNINGS) $(CFLAGS) -o $@ $<
	$(OBJCOPY) --set-section-alignment ".text*=4" --set-section-alignment ".data*=8" --set-section-alignment ".rodata=8" --set-section-alignment ".bss*=8" $@
	@$(OBJDUMP) $(OBJDUMP_FLAGS) $@ > $(@:.o=.dump.s)


-include $(D_FILES)

# Print target for debugging
print-% : ; $(info $* is a $(flavor $*) variable set to [$($*)]) @true
