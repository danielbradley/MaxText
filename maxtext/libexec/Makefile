OSTYPE=$(shell uname)

default:
	@echo "make all # to build for $(OSTYPE)"

all: build_build

build_build: Build/build/bin/build9

Build/build/bin/build9: Build
	cd Build/build; ./compile

Build:
	git clone https://github.com/danielbradley/Build.git
