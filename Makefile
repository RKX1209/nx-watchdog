ifeq ($(strip $(DEVKITARM)),)
$(error "Please set DEVKITARM in your environment. export DEVKITARM=<path to>devkitARM")
endif

CC = $(DEVKITARM)/bin/arm-none-eabi-gcc
LD = $(DEVKITARM)/bin/arm-none-eabi-ld
OBJCOPY = $(DEVKITARM)/bin/arm-none-eabi-objcopy

TARGET := ipl
BUILD := build_ipl
SOURCEDIR := ipl
OBJS = $(addprefix $(BUILD)/, \
	start.o \
	main.o \
	btn.o \
	clock.o \
	cluster.o \
	fuse.o \
	gpio.o \
	heap.o \
	hos.o \
	i2c.o \
	kfuse.o \
	lz.o \
	max7762x.o \
	mc.o \
	nx_emmc.o \
	sdmmc.o \
	sdmmc_driver.o \
	sdram.o \
	sdram_lp0.o \
	tui.o \
	util.o \
	di.o \
	gfx.o \
	pinmux.o \
	pkg1.o \
	pkg2.o \
	se.o \
	tsec.o \
	uart.o \
	ini.o \
)
OBJS += $(addprefix $(BUILD)/, diskio.o ff.o ffunicode.o)

ARCH := -march=armv4t -mtune=arm7tdmi -mthumb -mthumb-interwork
CFLAGS = $(ARCH) -Os -nostdlib -ffunction-sections -fdata-sections -fomit-frame-pointer -fno-inline -std=gnu11# -Wall
LDFLAGS = $(ARCH) -nostartfiles -lgcc -Wl,--nmagic,--gc-sections

.PHONY: all clean

all: $(BUILD) $(BUILD)/$(TARGET)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(BUILD)/$(TARGET).elf
	@rm -rf $(BUILD)/$(TARGET)

$(BUILD):
	mkdir -p $(BUILD)

$(BUILD)/$(TARGET): $(BUILD)/$(TARGET).elf
	$(OBJCOPY) -S -O binary $< $@

$(BUILD)/$(TARGET).elf: $(OBJS)
	$(CC) $(LDFLAGS) -T ipl/link.ld $^ -o $@

$(BUILD)/%.o: $(SOURCEDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/%.o: $(SOURCEDIR)/%.S
	$(CC) $(CFLAGS) -c $< -o $@
