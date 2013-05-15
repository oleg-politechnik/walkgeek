cd Build/

set confirm off
set pagination off

target remote localhost:10000
symbol-file walkgeek.elf
load walkgeek.elf

set remote hardware-watchpoint-limit 4
set remote hardware-breakpoint-limit 6

tb System_Init
c

set debug_mode=1
set msc=1

c
