// 
// Author: Milos Nikic
// Date: 14.4.2020.
// Project: Escape Room Magic Map
// 
//
// Schematic: 
//            Arduino and MFRC522
//          SDA   -->   Digital 10
//          SCK   -->   Digital 13
//          MOSI  -->   Digital 11
//          MISO  -->   Digital 12
//          IRQ   -->   UNCONNECTED
//          GND   -->   GND
//          RST   -->   Digital 9
//          3.3V  -->   3.3V
//
//            Arduino and WS2812B
//          5v    -->   External Power supply
//          DIn   -->   Digital 7
//          GND   -->   External Power supply (GND) & Arduino GND
//

#include <FastLED.h>
#include <SPI.h>
#include <MFRC522.h>

// Pins for RFID to work
#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

// How many leds in your strip?
#define NUM_LEDS 106

// Total number of LEDs is 106
// First 73 are used to represent way
// Next 18 is used for fist (true) bottle
// And last 16 are used for second (false) bottle

#define DATA_PIN 7

// Define the array of leds
CRGB leds[NUM_LEDS];

// C O L O R S
// Green = 255, 0, 0
int green[3] = {255, 0, 0}; 
// Red = 0, 255, 0
int red[3] = {0, 255, 0};
// Blue = 0, 0, 255
int blue [3]= {0, 0, 255};
// BrightBlue = 46, 176, 172
int brightBlue [3] = {46, 176, 172};
// Yellow = 194, 201, 52
int yellow [3] = {194, 201, 52};


int wayStart = 0;
int wayEnd = 72;
int trueBottleStart = 72;
int trueBottleEnd = 90;
int falseBottleStart = 90; 
int falseBottleEnd = 106;
//Delay time in miliseconds 
int delayTime = 500;
int noDelay = 0;
int slightDelay = 200;
// Signal to show map
int signalToProceed = 0;

// RFID INFORMATION
// CARD UID = CD D5 EB 73


void setup() {    
     SPI.begin();      // Initiate  SPI bus
     mfrc522.PCD_Init();   // Initiate MFRC522
     
     FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical
     
     //Turning all LEDs off
     // Starting from 0, ending at 80, r = 0, g = 0, b = 0, without delay;
     turnOn(wayStart,NUM_LEDS,0,0,0,noDelay);
     
     // FIRST BOTTLE THAT IS T R U E BOTTLE
     // ---------------------------------
     // From 60 to 70 leds should be RED and on signal to change color to purple
     turnOn(trueBottleStart,trueBottleEnd,red[0],red[1],red[2],noDelay);

     // SECOND BOTTLE THAT IS F A L S E BOTTLE
     // ---------------------------------
     // From 70 to 80 leds should be BLUE and on signal to change color to bright blue
     turnOn(falseBottleStart, falseBottleEnd, blue[0],blue[1],blue[2],noDelay);
  }

void loop() { 
  // So on proper signal, first (true) bottle leds should be turned into purple color
  // and false bottle leds should be turned into bright blue color
  // and after that way should appear;
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  // Read UID
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  
  // This part is executed when card is approximated to RFID and we get access
  if (content.substring(1) == "CD D5 EB 73") {
    // changeColor First Bottle
    turnOn(trueBottleStart,trueBottleEnd, green[0],green[1],green[2],noDelay);
    // changeColor Second Bottle
    turnOn(falseBottleStart,falseBottleEnd, brightBlue[0],brightBlue[1],brightBlue[2],noDelay);
    // Turn map LEDs on
    turnOn(wayStart,wayEnd, yellow[0],yellow[1],yellow[2],delayTime);
  }
}

void turnOn(int start, int end, int r, int g, int b,int delayTime){
  for(int i = start; i < end; i++){
    leds[i] = CRGB(r,g,b);
    FastLED.show();
    delay(delayTime);
  }
}
