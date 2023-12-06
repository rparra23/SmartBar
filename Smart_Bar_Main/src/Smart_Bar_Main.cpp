/* 
 * Project Smart_Bar_Main
 * Author: Rudy Parra
 * Date: Nov 30th 2023
 * 
 * Description: This code will help the deivce dispense the appropriate amounts of liquids to make a
 * perfect cocktail. Alont with providing the capabilities to remotley start the device to make you, your
 * choice of cocktail.
 * 
 */

// Including Necessary Libraries 
#include "Particle.h"
#include "math.h"
#include "IoTClassroom_CNM.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#include <Adafruit_MQTT.h>
#include "Adafruit_MQTT/Adafruit_MQTT_SPARK.h"
#include "Adafruit_MQTT/Adafruit_MQTT.h"
#include "HX711.h"
#include "credentials.h"
#include <Encoder.h>
#include "Button.h"
#include "Stepper.h"
#include <neopixel.h>

//******** SETTING INTS & OBJECTS FOR ALL CONNECTED DEVICES ************//

  // Setting NEOPIXEL Variables
    int numPixels = 16;
    Adafruit_NeoPixel pixel(numPixels, SPI1, WS2812B); // Use D6 for NeoPixels (SPI1)

  // Setting Pump Ints
    int pump1 = D19;
    int pump2 = D14;
    int pump3 = D13;
    int pump4 = D12;
  
  //Setting Encoder PINS
    int PINA = D17;
    int PINB = D18;
    const int REDLED = D8;
    const int GREENLED = D9;
    const int BLUELED = D15;
    const int BUTTONPIN = D16;
      //Setting Class Encoder
        class Encoder myEnc(PINA,PINB);
      //Setting Button
        Button button(BUTTONPIN);

  //Setting Time Varibales
    unsigned long startTime;
    String DateTime, TimeOnly, DateOnly;

  //Setting OLED Display Objects
    Adafruit_SSD1306 display(-1);


//******* SETTING UP WIRELESS CONNECTION PROTOCOLS *******//
SYSTEM_MODE(AUTOMATIC);

//****** ESTABLISHING FUNCTIONS *******//
void cocktailSelector();
void cocktailDispenser();
void condimentDispenser();

  void setup() {
    //Setting up Serial Monitor
    Serial.begin (9600); //Enable Serial Monitor
    waitFor(Serial.isConnected,10000); //waits for Serial Monitor
    Serial.println("Ready to Go"); //Prints that Serial Monitor is Ready to go
    

    //Setting Time Millis
    startTime = millis(); //get the current time;
    Time.zone(-7);        //MST = -7, MDT = -6
    Particle.syncTime();  //Sync time with Particle Cloud

    //Setting OLED DISPLAY Parameters
    display.begin(SSD1306_SWITCHCAPVCC, 0x3D);
    display.display();
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    //display.setCursor(0, 0);
    display.display();

    //Setting Encoder LEDs
    //pinMode(BUTTONPIN, INPUT_PULLDOWN);
    pinMode(GREENLED, OUTPUT);
    pinMode(REDLED, OUTPUT);
    pinMode(BLUELED, OUTPUT);

    //Pump Setup
    pinMode(pump1, OUTPUT);
    pinMode(pump2, OUTPUT);
    pinMode(pump3, OUTPUT);
    pinMode(pump4, OUTPUT);


  }

  void loop() {
    digitalWrite(pump1, HIGH); //Testing Pump
    digitalWrite(pump2, HIGH); //Testing Pump
    digitalWrite(pump3, HIGH); //Testing Pump
    digitalWrite(pump4, HIGH); //Testing Pump
    cocktailSelector();
    cocktailDispenser();
  }

  void cocktailSelector(){
    // Decarling Integers
    static int prevEnc;
    static int position;
    int i;
    int j;

    // Decalring Time Parameters
    DateTime = Time.timeStr();    //Current Date and Time from Particle Time Class
    TimeOnly = DateTime.substring(11,19); //Extract the time from the DateTime String
    DateOnly = DateTime.substring(0,10); //Extracts the date from the DateTIme

    // Setting the Encoder Default Light
    digitalWrite(GREENLED, HIGH); // Set the green LED to ON
    digitalWrite(REDLED, LOW);  // Set the red LED to OFF
    digitalWrite(BLUELED, LOW);  // Set the red LED to OFF

    //Setting NeoPixel Status Ring
    //for (i = 0; i<numPixels; i++) {
      pixel.setPixelColor(j, 255, 255, 255);
      pixel.setBrightness(30);
      pixel.show();
    //}
  
    position = myEnc.read(); // Reading Encoder Position
    Serial.printf("position: %i\n",position);// Print Position on Serial Monitor

    //if (position != prevEnc) {
    prevEnc = position;
    switch (position) {
      case 4:
        display.clearDisplay();
        display.printf("Margarita");
        display.setCursor(0, 25);
        display.display();
          if ((position == 4) && (button.isClicked())){
            digitalWrite(GREENLED, HIGH);
            digitalWrite(REDLED, HIGH);  
            digitalWrite(BLUELED, LOW);
            Serial.printf("Button Clicked on \n");
            delay(1000);

            //cocktailDispenser();

            digitalWrite(pump1, HIGH); //Testing Pump
            delay(2000);
            digitalWrite(pump1, LOW); //Testing Pump

            condimentDispenser();
            digitalWrite(GREENLED, LOW); 
            digitalWrite(REDLED, HIGH);  
            digitalWrite(BLUELED, HIGH);
            delay(1000);

          } 
        break;
      case 8:
        display.clearDisplay();
        display.printf("Tequila \nSunrise");
        display.setCursor(0, 25);
        display.display();
          if ((position == 8) && (button.isClicked())){
              digitalWrite(GREENLED, HIGH);
              digitalWrite(REDLED, HIGH);  
              digitalWrite(BLUELED, LOW);
              Serial.printf("Button Clicked on \n");
              delay(1000);

              digitalWrite(pump2, HIGH); //Testing Pump
              delay(2000);
              digitalWrite(pump2, LOW); //Testing Pump

              condimentDispenser();
              digitalWrite(GREENLED, LOW); 
              digitalWrite(REDLED, HIGH);  
              digitalWrite(BLUELED, HIGH);
              delay(1000);
          }
        break;
      case 12:
        display.clearDisplay();
        display.printf("Screw \nDriver");
        display.setCursor(0, 25);
        display.display();
          if ((position == 12) && (button.isClicked())){
            digitalWrite(GREENLED, HIGH);
            digitalWrite(REDLED, HIGH);  
            digitalWrite(BLUELED, LOW);
            Serial.printf("Button Clicked on \n");
            delay(1000);

            digitalWrite(pump3, HIGH); //Testing Pump
            delay(2000);
            digitalWrite(pump3, LOW); //Testing Pump

            condimentDispenser();
            digitalWrite(GREENLED, LOW); 
            digitalWrite(REDLED, HIGH);  
            digitalWrite(BLUELED, HIGH);
            delay(1000);
          }
        break;
      case 16:
        display.clearDisplay();
        display.printf("Vodka \nCranberry");
        display.setCursor(0, 25);
        display.display();
          if ((position == 16) && (button.isClicked())){
            digitalWrite(GREENLED, HIGH);
            digitalWrite(REDLED, HIGH);  
            digitalWrite(BLUELED, LOW);
            Serial.printf("Button Clicked on \n");
            delay(1000);

            digitalWrite(pump4, HIGH); //Testing Pump
            delay(2000);
            digitalWrite(pump4, LOW); //Testing Pump


            condimentDispenser();
            digitalWrite(GREENLED, LOW); 
            digitalWrite(REDLED, HIGH);  
            digitalWrite(BLUELED, HIGH);
            delay(1000);
          }
        break;
      default:
        display.clearDisplay();
        display.printf("%s\n%s",DateOnly.c_str(), TimeOnly.c_str());
        display.setCursor(0, 15);
        display.display();
      }
  //}
  }

  void cocktailDispenser() {
    // Setting Pump Ints
    int pump1 = D19;

    // Setting Scale Ints
    unsigned int last;
    int DT = D2;
    int CLK = D0;

      // Activating Pump
      digitalWrite(pump1, HIGH); //Testing Pump
      delay(2000);
      digitalWrite(pump1, LOW); //Testing Pump

      // Activating Condiment Dispenser
      condimentDispenser();

      // Activating Encoder Status LEDs
      digitalWrite(GREENLED, LOW); 
      digitalWrite(REDLED, HIGH);  
      digitalWrite(BLUELED, HIGH);
      delay(1000);
  }

  void condimentDispenser(){
      // Setting Steppers Parameters and Variables
      int speed = 15;
      int twoRotation = -4096;
      int spr = 2048;
      int IN1 = D3;
      int IN2 = D4;
      int IN3 = D5;
      int IN4 = D6;
      Stepper myStepper (spr, IN1, IN3, IN2, IN4);
      myStepper.setSpeed(speed);

      // Running the Stepper Motor
      myStepper.step(twoRotation);
  }
