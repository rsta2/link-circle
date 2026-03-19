#
# Makefile
#

LINK_CIRCLE_HOME = ..

OBJS	= if.o inet.o ioctl.o pause.o

libporting.a: $(OBJS)
	@echo "  AR    $@"
	@rm -f $@
	@$(AR) cr $@ $(OBJS)

include $(LINK_CIRCLE_HOME)/Rules.mk
