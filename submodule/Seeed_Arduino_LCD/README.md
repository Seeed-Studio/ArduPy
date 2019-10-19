# Seeed-Arduino-LCD

### Introduction

This library fork form [TFT_eSPI](https://github.com/Bodmer/TFT_eSPI). It is used to drive LCD screen.

### Start
You need to configure User_Setup.h to make your board work with LCD.
For example, if you use the LCD screen of ILI9341, then you uncomment #define ILI9341_DRIVER to make it support.
And you need to specify the pins of the connection. Here is the default configuration。
##### SAMD21
 TFT   | PIN
 :-:   | :-:
 TFT_CS |  5 
 TFT_DC |  6  
 TFT_RST | -1  
##### K210 PI
  TFT   | PIN
 :-:   | :-:
 TFT_CS |  29 
 TFT_DC |  25 
 TFT_RST | 33
 
 You can change pin definitions according to your needs.
 

### Boards
  - kendryte k210
  - SAMD21

### Note
  You can get more information [here](https://github.com/Bodmer/TFT_eSPI). 

