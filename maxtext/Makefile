BUILD=libexec/Build/build/bin/build9

default:
	@echo "make all # to build maxtext"

all: maxtext

maxtext: $(BUILD)
	BUILD_PATH=../Dependencies $(BUILD) --force --all

quick: $(BUILD)
	BUILD_PATH=../Dependencies $(BUILD)

#
#	libexec dependencies
#

$(BUILD):
	make -C libexec build_build
