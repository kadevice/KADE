#!/bin/bash

FIRMWARE_DIRS=(
    'kade-gen'
    'kade-icade'
    'kade-key-custom'
    'kade-keymouse'
    'kade-led-demo'
    'kade-mame'
    'kade-mame-2p'
    'kade-mame-custom'
    'kade-mame-extended'
    'kade-matrix'
    'kade-pin-custom'
    'kade-program'
    'kade-ps3-custom'
    'kade-psx-custom'
    'kade-rotary-custom'
    'kade-wii'
    'kade-xbox-custom'
    'tests/minimus'
)
working_dir=$(pwd)

for dir in ${FIRMWARE_DIRS[@]}; do
    cd "$working_dir/$dir"
    make clean
done
