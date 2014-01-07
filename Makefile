# System configuration
ARDUINO_DIR   = /usr/share/arduino
ARDMK_DIR     = arduino-makefile
AVR_TOOLS_DIR = /usr

# Arduino config
BOARD_TAG          = atmega168  # use "make show_boards" to list all
ARDUINO_PORT       = /dev/ttyUSB0
ARDUINO_SKETCHBOOK = sketchbook
ARDUINO_LIBS       = Wire Adafruit_Motorshield
MONITOR_BAUDRATE   = 9600

# Filesystem config
LOCAL_C_SRCS   ?= $(wildcard src/*.c)
LOCAL_CPP_SRCS ?= $(wildcard src/*.cpp)
LOCAL_CC_SRCS  ?= $(wildcard src/*.cc)
LOCAL_PDE_SRCS ?= $(wildcard src/*.pde)
LOCAL_INO_SRCS ?= $(wildcard src/*.ino)
LOCAL_AS_SRCS  ?= $(wildcard src/*.s)

include arduino-makefile/arduino-mk/Arduino.mk
