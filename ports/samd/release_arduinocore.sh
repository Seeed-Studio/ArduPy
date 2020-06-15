#!/bin/bash

arduino-cli board listall --additional-urls  https://files.seeedstudio.com/arduino/package_seeeduino_boards_index.json
COREVER=$(arduino-cli core list | grep Seeeduino | awk '{print $2}')
tmp_dir=$(mktemp -d -t ardupy-XXXXXXXXXX)
rm -rf build || true
mkdir -p build
version=$(date +%F)
work_pwd=$(pwd)
rm -rf deploy || true
mkdir -p deploy

cd build && cmake ../ -DARDUINO_CORE_PATH=$HOME/.arduino15/packages/Seeeduino/hardware/samd/$COREVER -DTOOLCHAIN=$HOME/.arduino15/packages/Seeeduino/tools/arm-none-eabi-gcc/7-2017q4/bin -DBOARD=xiao -DARDUINO_VERIANT=XIAO_m0 
make install DESTDIR=$tmp_dir -j4

mv ${tmp_dir}/usr/local/* ${work_pwd}/deploy

rm -rf *
cmake ../ -DARDUINO_CORE_PATH=$HOME/.arduino15/packages/Seeeduino/hardware/samd/$COREVER -DTOOLCHAIN=$HOME/.arduino15/packages/Seeeduino/tools/arm-none-eabi-gcc/7-2017q4/bin -DBOARD=wio_terminal -DARDUINO_VERIANT=wio_terminal
rm -rf $tmp_dir 

make install DESTDIR=$tmp_dir -j4


cp -rf $tmp_dir/usr/local/core/ArduPy/boards/wio_terminal/libmicropython.a ${work_pwd}/deploy/core/ArduPy/boards/wio_terminal/
cp -rf $tmp_dir/usr/local/tools/genhdr/wio_terminal ${work_pwd}/deploy/tools/genhdr/wio_terminal/
cp -rf $tmp_dir/usr/local/core/ArduPy/boards/wio_terminal ${work_pwd}/deploy/core/ArduPy/boards/wio_terminal/


cd ${work_pwd}/deploy/
tar -jcf  ardupy-core-${version}.tar.bz2 core  tools
#rm -rf core  tools
