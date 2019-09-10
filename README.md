# Introduction
## What's Ardupy?
Ardupy is an embedded python running environment with arduino as hardware abstraction layer and micropython as interpreter.

## Characteristic & Function
- Ardupy can experience complete python3 on embedded devices with limited resources
- Support for simple file systems
- Support for automatic running of boot.py when reset
- Support serial terminal interaction
- Support i2c, uart, one wire, spi, gpio built-in python library
- Rich third part library

## Resources
- [Mu Editor](https://seeed-studio.github.io/ArduPy/mu-editor)
- [Micropython](https://github.com/micropython/micropython)
- [Seeed Grove Libraries](https://github.com/Seeed-Studio/Seeed_Ardupy_Sketchbook)

# Build Ardupy
## Notice
make sure those follow utils installed in your linux machine.
- git
- wget
- cmake
- python

## Initial
run the follow script by python

### Content
- Ardupy
- micropython
- hardware
- tools

```python
import os
import shutil

os.system("git clone  https://github.com/Seeed-Studio/ArduPy")
os.system("git clone  https://github.com/micropython/micropython/")
os.system("wget https://downloads.arduino.cc/CMSIS-4.5.0.tar.bz2")
os.system("wget https://downloads.arduino.cc/CMSIS-Atmel-1.2.0.tar.bz2")
os.system("wget https://downloads.arduino.cc/cores/samd-1.8.3.tar.bz2")
os.system("wget http://downloads.arduino.cc/tools/bossac-1.7.0-arduino3-linux64.tar.gz")

if not os.path.exists("Ardupy/build"):
    os.makedirs("Ardupy/build")

if not os.path.exists("hardware/samd-1.8.3"):
    os.makedirs("hardware/samd-1.8.3", )

if not os.path.exists("tools/CMSIS"):
    os.makedirs("tools/CMSIS")

if not os.path.exists("tools/CMSIS-Atmel"):
    os.makedirs("tools/CMSIS-Atmel")

os.system("tar -jxvf samd-1.8.3.tar.bz2 -C hardware/samd-1.8.3")
os.system("tar -jxvf CMSIS-4.5.0.tar.bz2 -C tools/CMSIS/")
os.system("tar -jxvf CMSIS-Atmel-1.2.0.tar.bz2 -C tools/CMSIS-Atmel/")
os.system("tar -zxvf gcc-arm-none-eabi-4.8.3-2014q1-linux32.tar.gz -C .")
os.system("tar -zxvf bossac-1.7.0-arduino3-linux64.tar.gz -C .")
os.rename("tools/CMSIS/CMSIS", "tools/CMSIS/4.5.0")
os.rename("tools/CMSIS-Atmel/CMSIS-Atmel", "tools/CMSIS-Atmel/1.2.0")
cwd = os.getcwd()
core_path = os.path.join(cwd, 'hardware/samd-1.8.3/samd')
gcc_path = os.path.join(cwd, 'gcc-arm-none-eabi-4.8.3-2014q1/bin')
shutil.move("bin/bossac", "tools/bossac")
os.rmdir("bin/")
os.system("cd Ardupy/build && rm -rf * && cmake ../ -DARDUINO_CORE_PATH=%s  -DTOOLCHAIN=%s" % (core_path, gcc_path))
```

## Make firmware
open terminal in current folder and run this command to build a Ardupy firmware.

```shell
cd Ardupy/build && make -j
```

## Flashing
please make sure you use the correct tty device name.

### Which ttyACM indicated my board?
disconnect the board from your linux
```shell
ls /dev/tty
```
Press tab twice in a row, you will find a list of tty
then connect the board to your linux, repeat the previous command and press tab twice in a row again.
the new added device is the wanted target.

### Replace ttyACM0 with the actual device name
```shell
stty -F /dev/ttyACM0 1200 # set baud rate to 1200(flashing mode)
tools/bossac -i -d --port=ttyACM0 -U true -i -e -w -v Ardupy/build/Ardupy.bin -R
```

## We highly recommend that you start your creation with mu-editor with seeed mode
- [Mu Editor(version seeed)](https://seeed-studio.github.io/ArduPy/mu-editor)
- Coding
- Automatically update firmware and library
- Experience on-board python

## Contributing
If you have any good suggestions or comments, you can send issues or PR us.

