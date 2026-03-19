#
# Makefile
#

all:
	$(MAKE) -C modules/circle-stdlib
	$(MAKE) -C lib
	$(MAKE) -C examples/linkhut

clean:
	$(MAKE) -C examples/linkhut clean
	$(MAKE) -C lib clean
	$(MAKE) -C modules/circle-stdlib mrproper

patch:
	cd modules/circle-stdlib/libs/circle-newlib && \
	git apply --quiet ../../../circle-newlib.patch

unpatch:
	cd modules/circle-stdlib/libs/circle-newlib && git restore .

submodules:
	cd modules && git submodule update --init asio-standalone circle-stdlib
	cd modules/circle-stdlib/libs && git submodule update --init circle circle-newlib
	cd modules/circle-stdlib/libs/circle && git submodule update --init addon/wlan/hostap
