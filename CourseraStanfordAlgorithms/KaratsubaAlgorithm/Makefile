#! /usr/bin/make -f

.DEFAULT_GOAL := all

bin_dir := _build

program: | $(bin_dir)
	cmake -B$(bin_dir)
	make -C $(bin_dir) program

testrunner: | $(bin_dir)
	cmake -B$(bin_dir)
	make -C $(bin_dir) testrunner

$(bin_dir):
	mkdir -p $(bin_dir)

all: program testrunner

run: program
	$(bin_dir)/program/program

test: testrunner
	$(bin_dir)/testrunner/testrunner

clean:
	rm -rf $(bin_dir)

.PHONY: clean program testrunner all test
