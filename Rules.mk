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

CFLAGS += -Wno-multichar -Wno-subobject-linkage -Wno-psabi

DEFINE += -DASIO_STANDALONE \
	  -DASIO_HEADER_ONLY \
	  -DASIO_DISABLE_THREADS \
	  -DASIO_DISABLE_SIGNAL \
	  -DASIO_DISABLE_SIGACTION \
	  -DASIO_DISABLE_STRING_VIEW \
	  -DASIO_DISABLE_SERIAL_PORT \
	  -D_POSIX_C_SOURCE=200809L \
	  -D_GNU_SOURCE \
	  -D__LINUX_ERRNO_EXTENSIONS__

INCLUDE += $(CIRCLE_STDLIB_INCLUDES) \
	   -I $(LINK_CIRCLE_HOME)/include \
	   -I $(LINK_HOME)/modules/asio-standalone/asio/include \
	   -I $(LINK_HOME)/include

LIBS += $(LINK_CIRCLE_HOME)/lib/libporting.a \
	$(CIRCLE_STDLIB_LIBS) \
	$(CIRCLEHOME)/addon/wlan/hostap/wpa_supplicant/libwpa_supplicant.a \
	$(CIRCLEHOME)/addon/wlan/libwlan.a

-include $(DEPS)
