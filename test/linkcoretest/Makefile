#
# Makefile
#

LINK_CIRCLE_HOME = ../..

LINK_HOME = $(LINK_CIRCLE_HOME)/modules/link

TEST_HOME = $(LINK_HOME)/src/ableton

TESTS = $(TEST_HOME)/tst_Link.o \
	$(TEST_HOME)/link/tst_Beats.o \
	$(TEST_HOME)/link/tst_ClientSessionTimelines.o \
	$(TEST_HOME)/link/tst_Controller.o \
	$(TEST_HOME)/link/tst_HostTimeFilter.o \
	$(TEST_HOME)/link/tst_LinearRegression.o \
	$(TEST_HOME)/link/tst_Measurement.o \
	$(TEST_HOME)/link/tst_Median.o \
	$(TEST_HOME)/link/tst_NodeId.o \
	$(TEST_HOME)/link/tst_Phase.o \
	$(TEST_HOME)/link/tst_PingResponder.o \
	$(TEST_HOME)/link/tst_StartStopState.o \
	$(TEST_HOME)/link/tst_Tempo.o \
	$(TEST_HOME)/link/tst_Timeline.o \
	$(TEST_HOME)/link/tst_TripleBuffer.o
	#$(TEST_HOME)/link/tst_Peers.o
	#$(TEST_HOME)/link/tst_PeerState.o

OBJS	= main.o kernel.o $(TESTS)

EXTRACLEAN += $(TEST_HOME)/*.d $(TEST_HOME)/*.o \
	      $(TEST_HOME)/link/*.d $(TEST_HOME)/link/*.o

DEFINE += -DCATCH_CONFIG_NO_POSIX_SIGNALS

INCLUDE += -I $(LINK_HOME)/third_party/catch

include $(LINK_CIRCLE_HOME)/Rules.mk
