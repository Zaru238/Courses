#! /usr/bin/make -f

.DEFAULT_GOAL = all

release-dir = _build-release
debug-dir = _build-debug

release:
	mkdir -p $(release-dir)
	cmake -B$(release-dir) -DCMAKE_BUILD_TYPE=RELWITHDEBINFO
	make -C $(release-dir)

debug:
	mkdir -p $(debug-dir)
	cmake -B$(debug-dir) -DCMAKE_BUILD_TYPE=DEBUG
	make -C $(debug-dir)

all: release debug

relTest: release
	$(release-dir)/testrunner

debTest: debug
	$(debug-dir)/testrunner

test: debTest

clean:
	rm -rf $(release-dir) $(debug-dir)

.PHONY: clean
