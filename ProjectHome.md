[На русском](intro_ru.md)

This is walkgeek, another portable music player based upon STM32F4-Discovery
board hardware, which contains STM32F407VGT6 microcontroller and CS43L22 audio
codec. For now, it can play MP3 and [Opus](http://opus-codec.org) files.

The goal of this project is to create a fully functional yet very simple
portable player, optimized for easy navigation across a lot of pretty long audio
files (podcasts).

# Latest news #

_July 23, 2013_: Now this project is powered by [FreeRTOS](http://www.freertos.org). Only N1100 port is working. If you need an old OS-less version, take a look at a [legacy](https://code.google.com/p/walkgeek/source/browse/?name=legacy) branch.

_June 12, 2013_: STM32F4Discovery board port.

_June 7, 2013_: PC simulator port.

_May 30, 2013_: Now we can play [Opus](http://opus-codec.org) files.

_Apr 20, 2013_: Just finished PCB for new upcoming v1.0. It will fit into Nokia 1100 cellphone case.

_Jan 22, 2013_: Draft of schematics and hw/sw bring-up instructions added.

_Jan 16, 2013_: First source code commit. Plays mp3 and wav 16 bit from SD card. Schematics and installation instructions will be released soon.

# Hardware #

There are 2 pretty similar HW platforms supported (or rather variations of a
one platform) called N1100 and F4DISCOVERY.

## F4DISCOVERY ##

This platform is represented by STM32F4-Discovery board. It gives you an easy
way to try out and develop walkgeek. No HW modifications are necessary in a very
basic case. You only need to put some audio files supported by walkgeek on a USB
Flash drive and attach in to the USB Micro connector (CN5). User interface is
limited to a on-board "User" button which acts as button "3", and 4 leds:
  * Red means no Flash drive connected;
  * Green means Flash drive has enumerated and Player is started;
  * Orange means Player is stopped or loading current track;
  * Blue (blinking) means Player is playing current track.

You can download .hex firmware for it [here](http://code.google.com/p/m4-player/downloads/detail?name=walkgeek-v1.1-stm32f4discovery-with-mp3.hex&can=2&q=#makechanges).

http://m4-player.googlecode.com/files/walkgeek-discovery-small.JPG

## N1100 ##

There is also a more portable HW version that fits into Nokia 1100 cell phone
case. Design resources for it are also available in a pcb/ directory of this
project in EAGLE CAD format.

http://m4-player.googlecode.com/files/walkgeek-mp3-small.JPG


---


Feel free to [checkout](https://code.google.com/p/walkgeek/source/checkout) the latest revision or [browse source online](https://code.google.com/p/walkgeek/source/browse/).

For additional details, please refer to [README](https://code.google.com/p/walkgeek/source/browse/README).

