BUILD=libexec/Build/build/bin/build9
CXXFLAGS="-std=c++98 -Wno-deprecated"
OSNAME=$(shell uname)

default:
	@echo "make all # to build maxtext"

all: maxtext-$(OSNAME) symlink

maxtext-Darwin: $(BUILD)
	BUILD_PATH=../Dependencies CXXFLAGS=$(CXXFLAGS) $(BUILD) --force --all

maxtext-Linux: $(BUILD)
	OSTYPE=linux-gnu BUILD_PATH=../Dependencies CXXFLAGS=$(CXXFLAGS) $(BUILD) --force --all

symlink:
	mkdir -p bin/$(OSNAME)
	ln -sf ../../bin/maxtext bin/$(OSNAME)/maxtext
	ln -sf ../../bin/maxtext bin/$(OSNAME)/max2html

#
#	libexec dependencies
#

$(BUILD):
	make -C libexec build_build
