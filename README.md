
# Project Module 8 | Hybrid worlds | University of Twente
This repository will contain all software for our Module 8 project of Creative Technology at the University of Twente.



## The Project
We are making an installation to show the waterlevels and temperature in 5 cities in the Netherlands.
The installation consists of a model of a river next to a city. The user can select a city and a date. The water in the river will rise or fall to the height on that day. In the back, 5 tubes will show the waterlevels in all cities on that date.
LEDs in the river will show the water temperature on that day as well.

Users select a city by pouring water into their respective cups.
The date can be selected by rotating the three respective cogwheels. One for the year, one for the month, and one for the day.

## Hardware
The installation is controlled by a Raspberry Pi 4.
The RPi checks the input from the user. Every city has their own CSV file with historical data. After selecting a city, the data will be extracted from the CSV file. The RPi will send all data to an Arduino, which controls the switches for all pumps. The pumps will be activated to add water to the river and the tubes.
When water has to be drained, the Arduino will control the drainage valves.
The RPi will control the LEDs that have to light up.

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
