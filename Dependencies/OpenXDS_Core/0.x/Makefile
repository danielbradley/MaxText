all: build

build:
	cd libopenxds_base;     build --force --all
	cd libopenxds_provider; build --force --all
	cd libopenxds_threads;  build --force --all
	cd libopenxds_adt;      build --force --all
	cd libopenxds_adt_std;  build --force --all
	cd libopenxds_io;       build --force --all

clean:
	rm -rf libopenxds_core_base/{obj,lib}
	rm -rf libopenxds_core_provider/{obj,lib}
	rm -rf libopenxds_core_threads/{obj,lib}
	rm -rf libopenxds_core_adt/{obj,lib}
	rm -rf libopenxds_core_atd_std/{obj,lib}
	rm -rf libopenxds_core_io/{obj,lib}
