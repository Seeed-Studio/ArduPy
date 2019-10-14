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

***Only for Beta User***

# Develop Ardupy
## install depend software
make sure those follow utils installed in your linux machine.
#### debian or ubuntu
```shell
sudo apt update
sudo apt install git wget cmake python
```
#### macOS
```shell
brew update
brew install git wget cmake python
```

## Get all of the source code
run the follow script 
```shell
mkdir workspace
cd workspace
wget https://raw.githubusercontent.com/Seeed-Studio/ArduPy/master/get_resources.py
python get_source.py
```

## Make firmware
```shell
cd Ardupy/build && make -j
```

## Flashing
please make sure you use the correct tty device name.

### Check the USB device

```shell
ls /dev/ttyACM*
```

### Replace ttyACM* with the actual device name
#### macOS
```shell
stty -f /dev/ttyACM0 1200 # set baud rate to 1200(flashing mode)
tools/bossac -i -d --port=ttyACM0 -U true -i -e -w -v Ardupy/build/Ardupy.bin -R
```
#### debian or ubuntu
```shell
stty -F /dev/ttyACM0 1200 # set baud rate to 1200(flashing mode)
tools/bossac -i -d --port=ttyACM0 -U true -i -e -w -v Ardupy/build/Ardupy.bin -R
```

## We highly recommend that you start your creation with mu-editor with seeed mode 
- [Mu Editor(version seeed)](https://seeed-studio.github.io/ArduPy/mu-editor)
- Coding
- Automatically update firmware and library
- Experience on-board python


## Example code
- [Seeed Grove Libraries](https://github.com/Seeed-Studio/Seeed_Ardupy_Sketchbook)

## Contributing
If you have any good suggestions or comments, you can send issues or PR us.
