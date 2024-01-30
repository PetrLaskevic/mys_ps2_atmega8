CPU=atmega8
DPART=ATmega8
OBJ=main.o mouse.o ioconfig.o ps2.o tdelay.o neco.o
PROJECT=mainMujMod
PARALELPORT=/dev/parport0

SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)
DEPENDS = $(SOURCES:.c=.d)

%.o: %.c
	avr-gcc -g -O0 -mmcu=$(CPU) -c $< -o $@

all: $(OBJECTS)
	avr-gcc -g -mmcu=$(CPU) -Wl,-Map,$(PROJECT).map -o $(PROJECT).elf $(OBJECTS)
	avr-objdump -h -S $(PROJECT).elf > $(PROJECT).lst
	avr-objcopy -j .text -j .data -O ihex $(PROJECT).elf $(PROJECT).hex

load:
	uisp -dlpt=$(PARALELPORT) -dprog=dapa -dpart=$(DPART) --erase --upload --verify if=$(PROJECT).hex -v=3 --hash=12

ldude:
	avrdude -c dapa -p m8 -e -U flash:w:$(PROJECT).hex

lusb:
	avrdude -c usbasp -p m8 -e -U flash:w:$(PROJECT).hex

rusb:
	avrdude -c usbasp -p m8

usbread:
	avrdude -c usbasp -p m8

usbload:
	avrdude -c usbasp -p m8 -e -U flash:w:$(PROJECT).hex

wfbusb:
	# krystal
	avrdude -c usbasp -p m8 -e -u -U lfuse:w:0xEF:m -U hfuse:w:0xD9:m

read:
	uisp -dlpt=$(PARALELPORT) -dprog=dapa --rd_fuses

wfb:
	# internal RC oscilator 1MHz (default z výroby)
	# uisp -dlpt=$(PARALELPORT) -dprog=dapa --wr_fuse_h=D9 --wr_fuse_l=E1

	# internal RC oscilator 8MHz
	# uisp -dlpt=$(PARALELPORT) -dprog=dapa --wr_fuse_h=D9 --wr_fuse_l=E4

	# krystal
	uisp -dlpt=$(PARALELPORT) -dprog=dapa --wr_fuse_h=D9 --wr_fuse_l=EF

clean:
	rm -f *.o *.map *.out


-include $(DEPENDS)
