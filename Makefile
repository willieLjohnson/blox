# Simple helper Makefile to run CMake commands from root of project.

NAME = blox
SRC = main.cpp
CMAKELIST = ./CMakeLists.txt

all: run

build/$(NAME): $(SRC) | build
	cmake -S . -B build
	make -C build
	
build:
	mkdir -p $@

run: $(SRC) | build/$(NAME)
	make -C build
	./build/blox
	
