# HFT106
HFT106 were pinpads produced by Hypercom (acquired by Verifone in 2011) based on Dallas DS5002FP protected microcontroller. As the software was kept in RAM, nowadays all prodused pinpads are out of order because the internal battery is completely discharged and the data are erased.
DS5002FP is a microcontroller with Intel 8051 architecture that is programmed with a "Microcontroller Toolkit" via UART.
As I don't know at all the functions of the pinpad's firmware, I've written a simple demo program that scans the keypad and shows the scancode on the display.
You can see the internals of this pinpad here:
http://www.nedopc.org/forum/viewtopic.php?f=65&t=19446&start=15
To enter in a programming mode, you should short two pins at the bottom of the terminal and establish a connection in the Microcontroller Toolkit.
