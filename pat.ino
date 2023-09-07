
#include <ArduinoMqttClient.h>
#include <WiFiNINA.h>
//Based on MY board,I include the relevant Wi-Fi library.

//Deactivate your Wi-Fi login information

char ssid[] = "Galaxy M1149781";    
char pass[] = "987654321";   

int light = 6;

//Initialise the MQTT and Wi-Fi clients.

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

const char broker[] = "broker.mqttdashboard.com";
int        port     = 1883;
const char topic[]  = "brain ";
const unsigned long interval = 2000
unsigned long previousMillis = 0;
int count = 0;

// Flag to distinguish between "pat" and "wave"
bool isPat = false;

void setup() {
  // Setup serial communication initially for debugging

  Serial.begin(9600);
  // Create an output on the LED pin.



  while (!Serial);
    pinMode(light, OUTPUT);
  // Only necessary for native USB ports, wait for the serial port to open. 
    
  

// Join the wireless network

  Serial.print(" Connecting to a WPA SSID attempt: ");
  Serial.println(ssid);
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    
    Serial.print("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
    delay(2000);
  }

  Serial.println("You are linked to the internet");
  Serial.println();

  
//Join the MQTT broker here:

  Serial.print("Connection attempts to the MQTT broker: ");
  Serial.println(broker);

  if (!mqttClient.connect(broker, port)) {
    Serial.print("Connection to MQTT was lost! error number  ");
    Serial.println(mqttClient.connectError());
// Stop the programme if the MQTT connection fails.

    while (1);
  }

  Serial.println("You are now linked to the MQTT broker.");
  Serial.println();
// Join a particular MQTT topic.

  Serial.print("topic subscription ");
  Serial.println(topic);
  Serial.println();

  mqttClient.subscribe(topic);


  Serial.print("awaiting replies on the subject");
  Serial.println(topic);
  Serial.println();
}

void loop() {
  mqttClient.poll();
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    digitalWrite(light, LOW); //  by default lED is off
if (isPat) {
      // Handling thev "pat" differently
      digitalWrite(light, HIGH); // LED will be on  for "pat"
      delay(350); 
      digitalWrite(light, LOW); // LED will be off  for "pat"
    } else {
      // Handle "wave" differently
      digitalWrite(light, HIGH); 
      // LED will be on  for "pat"
      delay(350); 
      digitalWrite(light, LOW); 
      //LED will be off
      delay(350);
       Serial.println(); 
    }

    isPat = !isPat; 
    // Change the flag's state from "pat" to "wave"
  }

  int messageSize = mqttClient.parseMessage();
  if (messageSize) {
   
  }
}
 