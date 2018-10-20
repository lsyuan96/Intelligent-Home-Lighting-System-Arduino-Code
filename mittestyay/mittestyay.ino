#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

//Shing Yuans wifi
const char* ssid = "lsyua";   // Your network details
const char* password = "Azeraf01";  // Your network details


//Kamals wifi
//const char* ssid = "AndroidAP";   // Your network details
//const char* password = "12345678";  // Your network details

const int GPIO_1 = 0;
int min_bright = 0;
int max_bright = 602;
int flag = 0;
int freq = 33.5;
//PWM brightness
int brightness;
//For normal LEDs Low = off while high = bright, 0 = off, 1023 = max brightness
//However, this is flipped for the LED Downbecause of nlights -type mosfets

WiFiServer server(80);
//please change last two digit for different ESP8266 modules
//Device 1 
//IPAddress ip(192, 168, 43, 10);            // Static IP address of device

//Device 2
//IPAddress ip(192, 168, 43, 20);

//Device 3
//IPAddress ip(192, 168, 43, 30);

//Device 4
IPAddress ip(192, 168, 43, 40);

//IPAddress gateway(192,185,45,1);           // gateway of your network
IPAddress gateway(192, 168, 43, 1);
//192.168.43.1
IPAddress subnet(255, 255, 255, 0);       // subnet mask of your network


void setup()
{
  pinMode(GPIO_1, OUTPUT);
  digitalWrite(GPIO_1, HIGH);  //For Downlight
  //digitalWrite(GPIO_1, LOW);  //For LED
  Serial.begin(115200);
  WiFi.config(ip, gateway, subnet);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();         //Server started
  Serial.println("HTTP server started");
}


void loop()
{
  WiFiClient client = server.available();
  if (!client)
  {
    return;
  }
  while (!client.available())
  {
    delay(1);
  }
  String request = client.readStringUntil('\r');
  client.flush();

  
  int value = HIGH;

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// ON OFF CONTROL //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  if (request.indexOf("/LED=ON") != -1)
  {
    //For LED
    //digitalWrite(GPIO_1, HIGH);
    //value = HIGH;

    //For Downlight
    digitalWrite(GPIO_1, LOW);
    value = LOW;
  }

  if (request.indexOf("/LED=OFF") != -1)
  {
    //For LED
    //digitalWrite(GPIO_1, LOW);
    //value = LOW;

    //For Downlight
    digitalWrite(GPIO_1, HIGH);
    value = LOW;
  }

  if (request.indexOf("/LED=BLINK") != -1)
  {
    digitalWrite(GPIO_1, LOW);
    value = LOW;

    delay(500);

    digitalWrite(GPIO_1, HIGH);
    value = HIGH;

    delay(500);

    digitalWrite(GPIO_1, LOW);
    value = LOW;

    delay(500);

    digitalWrite(GPIO_1, HIGH);
    value = HIGH;

    delay(500);

    digitalWrite(GPIO_1, LOW);
    value = LOW;

    delay(500);

    digitalWrite(GPIO_1, HIGH);
    value = HIGH;

    delay(500);

    digitalWrite(GPIO_1, LOW);
    value = LOW;

    delay(500);

    digitalWrite(GPIO_1, HIGH);
    value = HIGH;
  }
 
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// BRIGHTNESS CONTROL ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  if (request.indexOf("/BRIGHT=LOW") != -1)
  {
    brightness = 900; //127,255,511,1023
    analogWrite(GPIO_1, brightness);
    value = brightness;
  }

  if (request.indexOf("/BRIGHT=MEDIUM") != -1)
  {
    //brightness = 511; //For LED
    brightness = 600; //For downlight
    analogWrite(GPIO_1, brightness);
    value = brightness;
  }

  if (request.indexOf("/BRIGHT=HIGH") != -1)
  {
    //brightness = 1023; //For LED
    brightness = 0  ;//For Downlight
    analogWrite(GPIO_1, brightness);
    value = brightness;

  }

  if (request.indexOf("/POWERSAVE=5") != -1)
  {
    //For LED
    //    digitalWrite(GPIO_1, HIGH);
    //    value = HIGH;
    //    delay(5000);
    //    digitalWrite(GPIO_1, LOW);
    //    value = LOW;

    //For Downlights
    brightness = 600; //127,255,511,1023
    analogWrite(GPIO_1, brightness);
    value = brightness;
    delay(5000);
    digitalWrite(GPIO_1, HIGH);
    value = HIGH;
  }

 
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// SPIN FUNCTION /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
  if (request.indexOf("/SPIN1") != -1)
  {
    //For Downlights
    
    digitalWrite(GPIO_1, LOW);
    value = LOW;

    delay(1000);

    digitalWrite(GPIO_1, HIGH);
    value = HIGH;

  }

  if (request.indexOf("/SPIN2") != -1)
  {
    //For Downlights
    delay(1000);
    
    digitalWrite(GPIO_1, LOW);
    value = LOW;

    delay(1000);

    digitalWrite(GPIO_1, HIGH);
    value = HIGH;

  }

  if (request.indexOf("/SPIN3") != -1)
  {
    //For Downlights
    delay(2000);
    
    digitalWrite(GPIO_1, LOW);
    value = LOW;

    delay(1000);

    digitalWrite(GPIO_1, HIGH);
    value = HIGH;

  }

  if (request.indexOf("/SPIN4") != -1)
  {
    //For Downlights
    delay(3000);
    
    digitalWrite(GPIO_1, LOW);
    value = LOW;

    delay(1000);

    digitalWrite(GPIO_1, HIGH);
    value = HIGH;

  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// WAVE ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


  if (request.indexOf("/LED=WAVE") != -1)
  {

    int lightbright = 1023;    // how bright the LED is
    int fadeAmount = 5;    // how many points to fade the LED by

    while(lightbright >= 0)
    {
      analogWrite(GPIO_1, lightbright);
      
      // change the brightness for next time through the loop:
      lightbright = lightbright - fadeAmount;
    
      // reverse the direction of the fading at the ends of the fade:

      delay(50);
    }
    // wait for 50 milliseconds to see the dimming effect
    
    digitalWrite(GPIO_1, HIGH);
    value = HIGH;

  }

 

  
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// ID DISPLAY //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  //1 - 1000
  //2 - 1010
  //3 - 1100
  //4 - 1111
 

  if (request.indexOf("/ID=1") != -1)
  {
    //1 - 1000
    int j = 0;
    
    while (j!=10)
    {

      if (flag == 0) {
      analogWrite(GPIO_1, max_bright);
      flag = 1;
      delay(7.5*freq);
      }
      if (flag == 1){
      analogWrite(GPIO_1, min_bright);
       flag = 0;
      delay(2.5*freq);
  
      j = j+1;
    }
    digitalWrite(GPIO_1, HIGH);
    value = HIGH;
  }
  }

  //2 - 1010

  if (request.indexOf("/ID=2") != -1)
  {
    //1 - 1000
    int j = 0;
    
    while (j!=20)
    {

      if (flag == 0) {
      analogWrite(GPIO_1, max_bright);
      flag = 1;
      delay(2.5*freq);
      }
      if (flag == 1){
      analogWrite(GPIO_1, min_bright);
       flag = 0;
      delay(2.5*freq);
  
      j = j+1;
    }
    digitalWrite(GPIO_1, HIGH);
    value = HIGH;
  }
  }

  //3 - 1100

  
  if (request.indexOf("/ID=3") != -1)
  {
    //1 - 1000
    int j = 0;
    
    while (j!=10)
    {

      if (flag == 0) {
      analogWrite(GPIO_1, max_bright);
      flag = 1;
      delay(5*freq);
      }
      if (flag == 1){
      analogWrite(GPIO_1, min_bright);
       flag = 0;
      delay(5*freq);
  
      j = j+1;
    }
    digitalWrite(GPIO_1, HIGH);
    value = HIGH;
  }
  }

  //4 - 1111

//  if (request.indexOf("/ID=4") != -1)
//  {
//    //1 - 1000
//    int j = 0;
//    
//    while (j!=10)
//    {
//
//      if (flag == 0) {
//      analogWrite(GPIO_1, max_bright);
//      flag = 0;
//      delay(10*freq);
//       
//      j = j+1;
//      }
// 
//    }
//    digitalWrite(GPIO_1, HIGH);
//    value = HIGH;
//  }

  
  
  delay(1);

  }
 
 
