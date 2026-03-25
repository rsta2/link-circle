#
# Makefile
#

LINK_CIRCLE_HOME = ../..

LINK_AUDIO_HOME ?= $(LINK_CIRCLE_HOME)/examples/linkaudio

OBJS	= main.o kernel.o linkhut.o \
	  $(LINK_AUDIO_HOME)/AudioEngine.o \
	  $(LINK_AUDIO_HOME)/AudioPlatform_Circle.o

EXTRACLEAN += $(LINK_AUDIO_HOME)/*.d $(LINK_AUDIO_HOME)/*.o

DEFINE += -DLINKHUT_AUDIO_PLATFORM_CIRCLE
#DEFINE += -DLINKHUT_AUDIO_PLATFORM_DUMMY

include $(LINK_CIRCLE_HOME)/Rules.mk

INCLUDE += -I $(LINK_AUDIO_HOME)

LIBS	+= $(CIRCLEHOME)/lib/sound/libsound.a
