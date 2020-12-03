BUILD=libexec/Build/build/bin/build9
CXXFLAGS="-std=c++98 -Wno-deprecated"

default:
	@echo "make all # to build maxtext"

all: maxtext

maxtext: $(BUILD)
	BUILD_PATH=../Dependencies CXXFLAGS=$(CXXFLAGS) $(BUILD) --force --all

quick: $(BUILD)
	BUILD_PATH=../Dependencies CXXFLAGS=$(CXXFLAGS) $(BUILD)

#
#	libexec dependencies
#

$(BUILD):
	make -C libexec build_build
