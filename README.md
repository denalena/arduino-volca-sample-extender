#Volca Sample Extender  

![Photo of a breadboard version of the Volca Sample Extender](http://i.imgur.com/uyWQOWH.jpg)

This program extends the Korg Volca Sample's MIDI functionality. By default the first 10 channels control the sample slots but there is only one channel per sample and without any pitch modification. So it's pretty useless if you want to use a MIDI keyboard. There are already similar projects like this available but I wanted to make my own. Also this uses a self written MIDI library, you have been warned. 

## Features
* Play samples chromatically in a 4 octave range (MIDI channel 1-10)
* Play all the samples via notes on one channel from C-AS (MIDI channel 16)
* Pitch bend is translated to control the EG INT pitch parameter

## Installation
* Clone/download this repository
* Clone/download the [BACH1 library](https://github.com/derdogan/bach1) to lib/bach1
* Compile and upload to Arduino Uno (with the default IDE or PlatformIO)

## Parts:
* 2x female MIDI jack
* 1x diode
* 1x optocoupler IC, e.g. the 6N138
* resistors
  * 2x 220 Ohm
  * 1x 480 Ohm
  * 1x 10k Ohm

## Schematics
### MIDI IN  -> RX (digital pin 0)
Connect the MIDI input to an optocoupler to prevent ground loops.

![MIDI Input schematics](http://i.imgur.com/Ew5b6qE.jpg)


### MIDI OUT  -> TX (digital pin 1)
The output is simpler: All you need is an 220 Ohm resistor.

![MIDI Input schematics](http://i.imgur.com/fK5Aqsk.jpg)

## Todo
- [ ] Polyphonic mode

## Credits
Special thanks to
* Mauricio Maisterrena for the idea and his [code](https://github.com/mmaisterrena/Volca_Simple).
* amandaghassaei for the MIDI I/O schematics and [this instructables page](http://www.instructables.com/id/Send-and-Receive-MIDI-with-Arduino/?ALLSTEPS) about the Arduino and MIDI.
