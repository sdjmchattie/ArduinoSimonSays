# Arduino Simon Says

A Simon Says game built with Arduino.  This is my personal project to build a Simon Says game using Arduino, four coloured buttons, each surrounded by LEDs of the same colour.  Any number of LEDs could be used for each button, but the resistance of the circuit should be carefully controlled to avoid damaging your LEDs.  To control a large number of LEDs that require more than the 30 or so mA that the digital pins of the arduino can supply, it is recommended to use an NPN transistor for each set of LEDs that can use the 5V supply from the Arduino through a 10k ohm resistor to activate a higher voltage and current for the LEDs.

If you don't know what Simon Says is, it's a memory game where the electronics present you with a sequence of flashing lights/buttons and then waits for you to repeat the sequence.  If you get the sequence wrong or take too long to press the buttons of the sequence, you lose the game.  If you complete the sequence though, it is repeated again with another new colour on the end of the sequence, extending it by one each time.  For more information, see [Wikipedia](https://en.wikipedia.org/wiki/Simon_(game)).

This project is a Platform IO project.  To be able to work on it and build it, Platform IO should be installed in your preferred IDE.  Work by the original author (Stuart McHattie) was performed in Visual Studio Code and built on an Arduino Nano clone from Hobby Components.
