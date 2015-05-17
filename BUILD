#!/bin/bash -e

if [ "$1" == "--pure" ]
then
    VIRTUAL_DEF='-DPURE_VIRTUAL'
fi

mkdir -p build
cd build

function compile {
    file=$1

    arm-none-eabi-g++ \
        -c \
        -g \
        -Os \
        -ffunction-sections \
        -fdata-sections \
        -nostdlib \
        --param max-inline-insns-single=500 \
        -fno-rtti \
        -fno-exceptions \
        $VIRTUAL_DEF \
        -mcpu=cortex-m0 \
        -mthumb \
        $file
}

compile ../demo.cpp
compile ../syscalls.c
compile ../reset.c

arm-none-eabi-g++ \
    -Os \
    -Wl,--gc-sections \
    -mcpu=cortex-m0 \
    -mthumb \
    -T../RBL_nRF51822.ld \
    -Wl,-Map,demo.map \
    -o demo.elf \
    -lm \
    -lgcc \
    -Wl,--cref \
    -Wl,--check-sections \
    -Wl,--gc-sections \
    -Wl,--entry=Reset_Handler \
    -Wl,--unresolved-symbols=report-all \
    -Wl,--warn-common \
    -Wl,--warn-section-align \
    -Wl,--warn-unresolved-symbols \
    -Wl,--start-group \
    syscalls.o \
    reset.o \
    demo.o \
    -Wl,--end-group

size=( $(size -A demo.elf | fgrep .text) )
echo ${size[1]}
