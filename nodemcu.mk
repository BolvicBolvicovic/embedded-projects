BUILD_DIR		= ./build
SRC_DIR			= .
FQBN			= esp8266:esp8266:nodemcuv2

# To list boards and find the correct serial: arduino-cli board list
# On wsl, you might need to first attach the usb port to wsl:
# usbipd list
# usbipd bind --busid 1-2
# usbipd attach --wsl --busid 1-2
SERIAL			= /dev/ttyUSB0
SERIAL_BAUD		= 115200
ESP8266_CORE	= $(HOME)/.arduino15/packages/esp8266/hardware/esp8266/3.1.2

all: compile upload serial

attach:
	arduino-cli board attach -p $(SERIAL) --fqbn $(FQBN)

ctags:
	@arduino-ctags -f tags.cpp $(shell find . -name "*.cpp" -o -name "*.h")
	@arduino-ctags -f tags.ino --langmap=c++:.ino $(shell find . -name "*.ino")
	@ctags -R --c++-kinds=+p --fields=+iaS --extras=+q \
		-f tags.core \
		$(ESP8266_CORE)/cores/esp8266 \
		$(ESP8266_CORE)/libraries
	@cat tags.cpp tags.ino tags.core > tags
	@sort -u tags -o tags
	@rm -f tags.cpp tags.ino tags.core

compile:
	arduino-cli compile --fqbn $(FQBN) --build-path $(BUILD_DIR) $(SRC_DIR)

upload:
	arduino-cli upload --fqbn $(FQBN) --input-dir $(BUILD_DIR) $(SRC_DIR)

serial:
	arduino-cli monitor -p $(SERIAL) -c baudrate=$(SERIAL_BAUD)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: ctags
