#
# Makefile
#

all:
	$(MAKE) -C modules/circle-stdlib
	$(MAKE) -C lib

clean:
	$(MAKE) -C lib clean
	$(MAKE) -C modules/circle-stdlib mrproper

patch:
	@echo Patching is not necessary any more.

unpatch:
	@echo Patching is not necessary any more.

submodules:
	cd modules && git submodule update --init link circle-stdlib
	cd modules/link/modules && git submodule update --init asio-standalone
	cd modules/circle-stdlib/libs && git submodule update --init circle circle-newlib
	cd modules/circle-stdlib/libs/circle && git submodule update --init addon/wlan/hostap
