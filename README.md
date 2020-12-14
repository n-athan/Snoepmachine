# Snoepmachine
Adafruit Huzzah powered candy machine that dispenses candy when an Adafruit AIO feed is updated. 
The basic construction is a funnel, closed by a piece of cardboard attached to a servo motor. When the servo is activated it moves sideways, letting the candy fall down, until the servo returns to it's original position. Closing the funnel to stop the candy from falling out of the machine.  
An example construction: 
 [machine.jpg](https://github.com/n-athan/snoepmachine/blob/main/machine.jpg?raw=true) 

## Adafruit IO feed
You can create an Adafruit IO account (both the free and premium plan will work) here: [Adafruit IO](https://io.adafruit.com/).  
Create a feed that the candy machine will listen to, and reference it in the AIODeedToServo.ino sketch. 
You can update the feed with manual input, with a dashboard on Adafruit IO, or by sending data to the API.  
See the Adafruit docs for more information.

## Circuit
It is important to connect the servo to the Adafruit Huzzah with 2 capacitors (100 nF and 100uF), as shown in the circuit schematic. This will prevent noise on the power line, when the servo operates.  
![circuit.png](https://github.com/n-athan/snoepmachine/blob/main/circuit.png?raw=true). 

## Programming the Adafruit Huzzah controller
You can program the controller with the Arduino IDE. For detailed instructions on connecting the Adafruit Huzzah I found this video tutorial very helpful: [SETUP Your Adafruit Feather HUZZAH ESP8266 on Windows for Arduino IDE](https://www.youtube.com/watch?v=vAhQrldaWIY). 