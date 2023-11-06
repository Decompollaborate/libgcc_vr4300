MAKEFLAGS += --no-builtin-rules

# Ensure the build fails if a piped command fails
SHELL = /bin/bash
.SHELLFLAGS = -o pipefail -c


# Output

BUILD_DIR       ?= build
TARGET          ?= libgcc_vr4300


CROSS           ?= mips-linux-gnu-


## Main targets

all: static

clean:
	$(RM) -rf $(BUILD_DIR)

static: $(BUILD_DIR)/$(TARGET).a


.PHONY: all static clean
.DEFAULT_GOAL := all
.SECONDARY:


# Programs
CC              := $(CROSS)gcc
AS              := $(CROSS)as
AR              := $(CROSS)ar
OBJDUMP         := $(CROSS)objdump

# C compiler arguments
CSTD            ?= -std=c11
MIPS_VERSION    ?= -mips3
OPTFLAGS        ?= -Os -ffast-math -fno-unsafe-math-optimizations
INC             ?= include
DEP_FLAGS       ?= -MMD -MP
WARNINGS        ?= -Wall -Wextra -Wpedantic
CFLAGS          ?= -nostdinc -march=vr4300 -mfix4300 -mdivide-breaks -fno-zero-initialized-in-bss -fno-toplevel-reorder -ffreestanding -fno-common -fno-merge-constants -mno-explicit-relocs -mno-split-addresses -funsigned-char
CFLAGS          += -G0 -mabi=32 -mno-abicalls

## Autogenerated based on $(INC)
IINC            ?= $(foreach f, $(INC), -I $(f))


# objdump arguments
OBJDUMP_FLAGS   ?= --disassemble --reloc --disassemble-zeroes -Mreg-names=32



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
	$(CC) -c $(CSTD) $(MIPS_VERSION) $(OPTFLAGS) $(IINC) $(DEP_FLAGS) $(WARNINGS) $(CFLAGS) -o $@ $<
	@$(OBJDUMP) $(OBJDUMP_FLAGS) $@ > $(@:.o=.dump.s)

$(BUILD_DIR)/%.o: %.s
	$(CC) -x assembler-with-cpp -c $(CSTD) $(MIPS_VERSION) $(OPTFLAGS) $(IINC) $(DEP_FLAGS) $(WARNINGS) $(CFLAGS) -o $@ $<
	@$(OBJDUMP) $(OBJDUMP_FLAGS) $@ > $(@:.o=.dump.s)


-include $(D_FILES)

# Print target for debugging
print-% : ; $(info $* is a $(flavor $*) variable set to [$($*)]) @true
