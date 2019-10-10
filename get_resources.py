import os
import platform
import shutil

if platform.uname().system == 'Darwin':
    bossac_path = 'http://downloads.arduino.cc/tools/bossac-1.7.0-arduino3-osx.tar.gz'
    bossac_name = 'bossac-1.7.0-arduino3-osx.tar.gz'
    gcc_path = 'http://downloads.arduino.cc/gcc-arm-none-eabi-4.8.3-2014q1-mac.tar.gz'
    gcc_name = 'gcc-arm-none-eabi-4.8.3-2014q1-mac.tar.gz'
elif os.name == 'posix':
    bossac_path = 'http://downloads.arduino.cc/tools/bossac-1.7.0-arduino3-linux64.tar.gz'
    bossac_name = 'bossac-1.7.0-arduino3-linux64.tar.gz'
    gcc_path = 'http://downloads.arduino.cc/gcc-arm-none-eabi-4.8.3-2014q1-linux64.tar.gz'
    gcc_name = 'gcc-arm-none-eabi-4.8.3-2014q1-linux64.tar.gz'
else:
    raise NotImplementedError()

os.system("git clone https://github.com/Seeed-Studio/ArduPy")
os.system("git clone https://github.com/micropython/micropython/ -b v1.11")
os.system("wget https://downloads.arduino.cc/CMSIS-4.5.0.tar.bz2")
os.system("wget https://downloads.arduino.cc/CMSIS-Atmel-1.2.0.tar.bz2")
os.system("wget https://downloads.arduino.cc/cores/samd-1.8.3.tar.bz2")
os.system("wget %s" % gcc_path);
os.system("wget %s" % bossac_path)

if not os.path.exists("ArduPy/build"):
    os.makedirs("ArduPy/build")

if not os.path.exists("hardware/samd-1.8.3"):
    os.makedirs("hardware/samd-1.8.3")

if not os.path.exists("tools/CMSIS"):
    os.makedirs("tools/CMSIS")

if not os.path.exists("tools/CMSIS-Atmel"):
    os.makedirs("tools/CMSIS-Atmel")

os.system("tar -jxvf samd-1.8.3.tar.bz2 -C hardware/samd-1.8.3")
os.system("tar -jxvf CMSIS-4.5.0.tar.bz2 -C tools/CMSIS/")
os.system("tar -jxvf CMSIS-Atmel-1.2.0.tar.bz2 -C tools/CMSIS-Atmel/")
os.system("tar -zxvf %s -C ." % gcc_name)
os.system("tar -zxvf %s -C ." % bossac_name)
os.rename("tools/CMSIS/CMSIS", "tools/CMSIS/4.5.0")
os.rename("tools/CMSIS-Atmel/CMSIS-Atmel", "tools/CMSIS-Atmel/1.2.0")

cwd = os.getcwd()
core_path = os.path.join(cwd, 'hardware/samd-1.8.3/samd')
gcc_path = os.path.join(cwd, 'gcc-arm-none-eabi-4.8.3-2014q1/bin')
shutil.move("bin/bossac", "tools/bossac")
os.rmdir("bin/")
os.system("cd ArduPy/build && rm -rf * && cmake ../ -DARDUINO_CORE_PATH=%s  -DTOOLCHAIN=%s" % (core_path, gcc_path))


