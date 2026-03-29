#
# Makefile
#

LINK_CIRCLE_HOME = ..

OBJS	= ioctl.o

libporting.a: $(OBJS)
	@echo "  AR    $@"
	@rm -f $@
	@$(AR) cr $@ $(OBJS)

include $(LINK_CIRCLE_HOME)/Rules.mk
