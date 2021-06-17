
# Project Module 8 | Hybrid worlds | University of Twente
This repository will contain all software and instructions for our Module 8 project of Creative Technology at the University of Twente.



## The Project
We are making an installation to show the waterlevels and temperature in 5 cities in the Netherlands.
The installation consists of a model of a river next to a city. The user can select a city and a date. The water in the river will rise or fall to the height on that day. In the back, 5 tubes will show the waterlevels in all cities on that date.
LEDs in the river will show the water temperature on that day as well.

Users select a city by pouring water into their respective cups.
The date can be selected by rotating the three respective cogwheels. One for the year, one for the month, and one for the day.

### Hardware
The installation is controlled by a Raspberry Pi together with an Arduino Mega 2560.
The Pi stores the database, performs all calculations and presents the interface. The Arduino Mega only serves as a bridge between the Pi and all the sensors and actuators. They are connected using the USB port on the Arduino and a USB port on the Pi.
The Pi is powered by the USB C connector and the Arduino is powered using a 12V barrel connector.
#### Parts
##### Controllers
- Raspberry Pi (Model 4B 2GB) 1x
- Arduino Mega 2560 1x
##### Sensors
 - Distance sensor (HC-SR04) 5x
 - Water Flow sensor () 2x
 - Rotary Encoders () 3x
##### Actuators
- Water valves () 12x
- LED strips () 5x

### Software
The Pi runs Raspbian 5.10.
[FILL WITH CODE EXPLANATION]

### To do
For a comprehensive to do list, finished functionality and current additions, see the [Trello workspace](https://trello.com/b/8ndzsZBY/software).


## Contact
For more information about our project, you can contact Bas van der Steenhoven ([b.g.vandersteenhoven@student.utwente.nl](mailto:b.g.vandersteenhoven@student.utwente.nl)).

### Group Members:
#### Group Leaders
- Tale Nap
- Bas van der Steenhoven

#### Software Team
 - Stijn Brugman
 - David Lammers
 - Bas van der Steenhoven

#### Design Team
 - Alessia Bertana
 - Noor de Feber
 - Tale Nap

#### Building Team
 - Sofia Baltussen
 - Wonjun Jung
 - Froukje Temme
 - Myungwon Youn


## Special thanks
We want to thank Erik Faber and Champika Epa Ranasinghe for their feedback and help during this project. We want to thank Daniela van Meggelen for her guidance, help, feedback and role as our personal Teaching Assistant for this project.
