# SoldierArmuino
Small project developed as a commission for the [Caserma Gamerra historical museum](https://www.esercito.difesa.it/storia/musei/Museo-Storico-delle-Aviotruppe).

This repo is intended to document the work done by me and @TommyTokk, the project was actually developed in 2019 starting from september but we managed to retrieve the code only now.

## The project
The project consists in the realization of small electrical mannequin that simulates a wounded soldier when people enter the room it is placed in.

The movements are done with a servo motor while to detect people enterig the room we used a PIR sensor. 
Along with movements we have put in place a small audio speaker with a custom made sound simulating war noises outside a tent, made by @Mitra98t.

### the circuit
![circuit image](images/immagine.png)

This is the schematic of the circuit we used.

The .ino file present is used on the arduino to handle both sensor signals and motor movement.

### components
The main components are:
- DFrobotPlayerMini
- arduino nano
- PIR sensor
- generic audio speaker

Our project was made using a perforboard where both music player and arduino were soldered.

## how it works 
We have constant poll to the PIR sensor from the arduino whenever a movement occurs in front of the sensor the arduino detects fires the signal to the player to play the sound and moves the motor.

## usage
The motor is placed inside the mannequin arm to move it while the PIR sensor is pointed toward the room entry, a aux adapter was used to connect a generic audio speaker and place it near the mannequin but you can use other types (as shown in the image).

## final notes

This repo is intended for the commissioner as a manual and documentation of our work, we where inexperienced during the realization but managed to create a solid working implementation.
