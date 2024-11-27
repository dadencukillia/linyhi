.DEFAULT_GOAL := all

configure:
	cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

configure_release:
	cmake -S . -B build -DCMAKE_BUILD_TYPE=Release

compile:
	cmake --build build

exe:
	./build/linyhi

all: configure compile exe

release: configure_release compile

test: configure compile
	ctest -V --test-dir ./build
