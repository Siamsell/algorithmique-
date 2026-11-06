# Compile tous les programmes dans le dossier build/

CC  = gcc
CXX = g++
CFLAGS   = -Wall -Wextra -std=c11
CXXFLAGS = -Wall -Wextra -std=c++11

C_SRC   := $(wildcard */*.c)
CPP_SRC := $(wildcard */*.cpp)
BINS    := $(patsubst %.c,build/%,$(C_SRC)) $(patsubst %.cpp,build/%,$(CPP_SRC))

all: $(BINS)

build/%: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

build/%: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -rf build

.PHONY: all clean
