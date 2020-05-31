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

cd build && cmake ../ -DARDUINO_CORE_PATH=$HOME/.arduino15/packages/Seeeduino/hardware/samd/$COREVER -DTOOLCHAIN=$HOME/.arduino15/packages/Seeeduino/tools/arm-none-eabi-gcc/7-2017q4/bin -DBOARD=seeeduino_m0 -DARDUINO_VERIANT=XIAO_m0 
make install DESTDIR=$tmp_dir

mv ${tmp_dir}/usr/local/* ${work_pwd}/deploy
mv  ${work_pwd}/deploy/ArduPy/lib/libmicropython.a   ${work_pwd}/deploy/ArduPy/lib/libmicropython-cortexm0plus.a
mkdir -p  ${work_pwd}/deploy/Seeeduino/tools/samd21
mv  ${work_pwd}/deploy/Seeeduino/tools/genhdr/* ${work_pwd}/deploy/Seeeduino/tools/samd21
mv ${work_pwd}/deploy/Seeeduino/tools/samd21 ${work_pwd}/deploy/Seeeduino/tools/genhdr
mv  ${work_pwd}/deploy/ArduPy/boards/seeeduino_m0 ${work_pwd}/deploy/ArduPy/boards/samd21


rm -rf *
cmake ../ -DARDUINO_CORE_PATH=$HOME/.arduino15/packages/Seeeduino/hardware/samd/$COREVER -DTOOLCHAIN=$HOME/.arduino15/packages/Seeeduino/tools/arm-none-eabi-gcc/7-2017q4/bin -DBOARD=wio_terminal -DARDUINO_VERIANT=wio_terminal
rm -rf $tmp_dir 

make install DESTDIR=$tmp_dir


cp $tmp_dir/usr/local/ArduPy/lib/libmicropython.a ${work_pwd}/deploy/ArduPy/lib/libmicropython-cortexm4lf.a
mkdir -p ${work_pwd}/deploy/Seeeduino/tools/genhdr/samd51
cp -rf $tmp_dir/usr/local/Seeeduino/tools/genhdr/* ${work_pwd}/deploy/Seeeduino/tools/genhdr/samd51
mv  ${work_pwd}/deploy/ArduPy/boards/wio_terminal ${work_pwd}/deploy/ArduPy/boards/samd51


cd ${work_pwd}/deploy/
tar -jcf  ardupy-core-${version}.tar.bz2 ArduPy  Seeeduino

rm -rf ArduPy  Seeeduino
