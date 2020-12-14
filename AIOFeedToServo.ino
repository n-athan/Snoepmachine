#include "AdafruitIO.h"
#include "AdafruitIO_WiFi.h"
#include "Servo.h"

#define IO_USERNAME  ""  // Your Adafruit IO Username
#define IO_KEY       ""   // Your Adafruit IO AIO Key
#define WIFI_SSID "" // Your local Wifi SSID
#define WIFI_PASS "" // Password for Wifi
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

// Servo that controls our feeder
Servo servo;  

// Create a feed object to send and get data
AdafruitIO_Feed *feed = io.feed(""); // Add the name of your AdafruitIO feed between ""
 
// Start-up code
void setup()
{
   // Initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

   // Serial bus initialization (Serial Monitor)
   Serial.begin(9600);
   while(!Serial);  // Wait for serial connection
   
   // Adafruit IO connection and configuration
   Serial.print("Connecting to Adafruit IO");
   io.connect();  // Connect to Adafruit IO service
   while(io.status() < AIO_CONNECTED) {
      Serial.print(".");
      delay(1000);  // Wait 1 second between checks
   }
   Serial.println();
   Serial.println(io.statusText());  // Print AIO connection status

   // Set up message handler that calls function when messages are received
   feed->onMessage(toDoMessageHandler);

   // Synchronize current state
   feed->get();  // request feed value from AIO

   // Start with LED off. 
   digitalWrite(LED_BUILTIN, HIGH);

   // Startup servo
   servo.attach(14); // Change pin according to your own circuit
   servo.write(0);
}
 
// Main loop
// Changes in the feed are handled by the message handler, so the main loop doesn't need to do much
void loop()
{
  io.run(); // Keep connection to Adafruit IO active
  delay(5000); // The Adafruit IO free plan only allows 30 calls per minute. The delay of 5 seconds prevents making too many calls.
}

// Handles feed messages received from AIO
void toDoMessageHandler(AdafruitIO_Data *data) {
   String value = data->toString();  // Capture feed value from AIO
   Serial.print("feed received -> ");  Serial.println(value);
   if (value == "1") { // If you sent other data to your feed, change this value.
     digitalWrite(LED_BUILTIN, LOW); 
     servo.write(90); // Open the candy machine 
     delay(100); // Adjust the timeout if you want more, or less, candy on activation.
     digitalWrite(LED_BUILTIN, HIGH);
     servo.write(0); // Close the candy machine
     feed->save(0); // Write 0 back to the feed to reset. If you sent other data to your feed, change this value or omit this line.
   }
}
