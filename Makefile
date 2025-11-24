# ----- PROJECT INFO -----

PROJ_NAME := libver
VER := 1.1

# ----- COMPILER CONFIGURATION -----

CC := gcc
CC_OPTS := \
	-Wall \
	-Werror \
	-fpic \
	-g

CC_LIBS := \
	-lcast \
	-lcalen \
	-lchbuf \
	-lerr \
	-lfileio \
	-lmem

# ----- REAL TARGETS -----

build/lib/libver.so: build/obj/ver.o
	@mkdir -p build/lib
	@${CC} -shared -o $@ $< ${CC_LIBS}
	@echo "Built target $@"

build/obj/ver.o: ver.c ver.h Makefile
	@mkdir -p build/obj
	@${CC} ${CC_OPTS} -c -o $@ $<
	@echo "Built target $@"

# ----- PHONY TARGETS -----

.PHONY: \
	all \
	clean \
	install \
	uninstall

all: build/lib/libver.so
	@echo "Built ${PROJ_NAME} version ${VER}"

clean:
	@rm -rf build
	@echo "All build artifacts removed"

install: build/lib/libver.so
	@cp ver.h /usr/local/include/ver.h
	@echo "Copied ver.h"
	@cp build/lib/libver.so /usr/local/lib/libver.so
	@echo "Copied libver.so"
	@echo "${PROJ_NAME} version ${VER} successfully installed"

uninstall:
	@rm /usr/local/include/ver.h
	@echo "Deleted ver.h"
	@rm /usr/local/lib/libver.so
	@echo "Deleted libver.so"
	@echo "${PROJ_NAME} successfully uninstalled"

