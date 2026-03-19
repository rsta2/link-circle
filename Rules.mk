#
# Rules.mk
#

LINK_CIRCLE_HOME ?= ../..

LINK_HOME ?= $(LINK_CIRCLE_HOME)/modules/link
CIRCLE_STDLIB_DIR ?= $(LINK_CIRCLE_HOME)/modules/circle-stdlib

include $(CIRCLE_STDLIB_DIR)/Config.mk

CIRCLEHOME ?= $(CIRCLE_STDLIB_DIR)/libs/circle
NEWLIBDIR ?= $(CIRCLE_STDLIB_DIR)/install/$(NEWLIB_ARCH)

include $(CIRCLEHOME)/Rules.mk

CFLAGS += -Wno-multichar

DEFINE += -DASIO_STANDALONE \
	  -DASIO_HEADER_ONLY \
	  -DASIO_DISABLE_THREADS \
	  -DASIO_DISABLE_SIGNAL \
	  -DASIO_DISABLE_SIGACTION \
	  -DASIO_DISABLE_SERIAL_PORT \
	  -D__LINUX_ERRNO_EXTENSIONS__

INCLUDE += -isystem $(LINK_CIRCLE_HOME)/c++-include \
	   -I $(LINK_CIRCLE_HOME)/include \
	   -I $(NEWLIBDIR)/include \
	   -I $(CIRCLE_STDLIB_DIR)/include \
	   -I $(LINK_HOME)/modules/asio-standalone/asio/include \
	   -I $(LINK_HOME)/include

LIBS =	$(LINK_CIRCLE_HOME)/lib/libporting.a \
	$(NEWLIBDIR)/lib/libm.a \
	$(NEWLIBDIR)/lib/libc.a \
	$(NEWLIBDIR)/lib/libcirclenewlib.a \
	$(CIRCLEHOME)/addon/SDCard/libsdcard.a \
	$(CIRCLEHOME)/lib/usb/libusb.a \
	$(CIRCLEHOME)/lib/input/libinput.a \
	$(CIRCLEHOME)/addon/fatfs/libfatfs.a \
	$(CIRCLEHOME)/lib/fs/libfs.a \
	$(CIRCLEHOME)/addon/wlan/hostap/wpa_supplicant/libwpa_supplicant.a \
	$(CIRCLEHOME)/addon/wlan/libwlan.a \
	$(CIRCLEHOME)/lib/net/libnet.a \
	$(CIRCLEHOME)/lib/sched/libsched.a \
	$(CIRCLEHOME)/lib/libcircle.a

-include $(DEPS)
