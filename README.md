# ModeDetector
Single-mode laser radiation detector
The principle of operation is based on detecting beats between different radiation modes.

The detected signal level is digitized by the internal ADC of the LPC2148 microcontroller.

The other channel of the ADC microcontroller digitizes the signal proportional to the average power of the laser radiation.

Then these two levels are compared and the result is output to the led line and via the USB port in the PC.

/HardWare - pcad2006 circuit аnd printed board.

/Soft  - sources and the KEIL uVision project for the LPC2148 microcontroller
