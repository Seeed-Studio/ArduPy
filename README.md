
cmake ../ -DARDUINO_CORE_PATH=/home/baozhu/.arduino15/packages/arduino/hardware/samd/1.6.21 -DBOARD=arduino_zero -DTOOLCHAIN=/opt/gcc-arm-none-eabi-8.2/bin

cmake ../ -DARDUINO_CORE_PATH=/home/baozhu/.arduino15/packages/arduino/hardware/samd/1.6.21 -DBOARD=arduino_zero -DMICROPYTHON=1  -DTOOLCHAIN=/opt/gcc-arm-none-eabi-8.2/bin

 sudo stty -F /dev/ttyACM0 1200
/home/baozhu/.arduino15/packages/arduino/tools/bossac/1.7.0/bossac -i -d --port=ttyACM0 -U true -i -e -w -v Arduino.bin -R 

 sudo stty -F /dev/ttyACM0 1200
/home/baozhu/.arduino15/packages/arduino/tools/bossac/1.7.0/bossac -i -d --port=ttyACM0 -U true -i -e -w -v Grovepy.bin -R 