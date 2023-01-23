BUILD    := libexec/Build/build/bin/build9
CXXFLAGS := "-std=c++98 -Wno-deprecated"
OSNAME   := $(shell uname)
CPU      := $(shell uname -m)

default:
	@echo "make all # to build maxtext"

all: maxtext-$(OSNAME) copy

maxtext-Darwin: $(BUILD)
	BUILD_PATH=../Dependencies CXXFLAGS=$(CXXFLAGS) $(BUILD) --force --all

maxtext-Linux: $(BUILD)
	OSTYPE=linux-gnu BUILD_PATH=../Dependencies CXXFLAGS=$(CXXFLAGS) $(BUILD) --force --all

copy:
	mkdir -p bin/$(OSNAME)-$(CPU)
	cp bin/maxtext bin/$(OSNAME)-$(CPU)/maxtext 
	cp bin/maxtext bin/$(OSNAME)-$(CPU)/max2html
 
#       
#       libexec dependencies
#

$(BUILD):
	make -C libexec build_build
