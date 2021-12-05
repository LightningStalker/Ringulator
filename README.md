# Ringulator
Arduino Coil and transformer tester and ring detector

## Requirements
Libraries: Latest FreqCount dev version https://github.com/PaulStoffregen/FreqCount (required for v1.1 and later) Version downloadable through Arduino IDE is too old as of this writing

Display: Default is the 'Seed Grove-LCD RGB Backlight' since one was on hand, other LCD and 7seg LED displays can be substituted

MCU: Tested with Atmega 328 (Uno) @16MHz

Analog frontend: danyk wrote a short article and video with details, and provided some inspiration. http://danyk.cz

## What version is right for me?
Development has taken 2 different paths based on different needs and availability of GPIOs. The v1.0 release is interrupt driven and can make use of any pin capable of triggering interrupts. This makes it more flexible, however at the cost of missing some pulses at higher frequencies. It is also at the mercy of other interrupts. This is generally not a huge problem most of the time.

The current development tree now uses the counter peripheral to offload the task of counting every single pulse. Counting frequencies up to about 6MHz without missing pulses is possible with this method. Unfortunately it comes at a price since only a single path exists to the external. Therefore it must use a specific pin that is MCU dependent. There is also an increase in program memory usage. Still I would recommend this over the other if the necessary resources are available. Additional pulses are detected in many cases, even at lower frequencies.
