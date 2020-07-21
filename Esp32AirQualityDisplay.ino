
// You can use any (4 or) 5 pins
#define SCLK_PIN 18
#define MOSI_PIN 23
#define DC_PIN   17
#define CS_PIN   5
#define RST_PIN  4

#include "lcdgfx.h"

#include "Adafruit_CCS811.h"
#include "display.h"

Adafruit_CCS811 ccs;
DisplaySSD1351_128x128x16_SPI display(RST_PIN,{-1, CS_PIN, DC_PIN, 0,-1,-1});
NanoEngine16<DisplaySSD1351_128x128x16_SPI> engine( display );

// constants won't change. They're used here to set pin numbers:
const uint8_t buttonPin = 16;     // the number of the pushbutton pin

// variables will change:
volatile int modeCounter = 0;
bool clearDisplay = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(buttonPin), changeMode, FALLING);
  
  display.begin();
  display.fill( 0x0000 );
  display.setFixedFont(ssd1306xled_font8x16);
  display.getInterface().setRotation(3);

  if(!ccs.begin()){
    Serial.println("Failed to start sensor! Please check your wiring.");
    while(1);
  }

  // Wait for the sensor to be ready
  while(!ccs.available());
  //calibrate temperature sensor
  float temp = ccs.calculateTemperature();
  ccs.setTempOffset(temp - 23.0);
}

void loop() {
  if(ccs.available()){
    if(!ccs.readData()){
      int co2 = ccs.geteCO2();
      int tvoc = ccs.getTVOC();
      float temperature = ccs.calculateTemperature();
      printData(co2, tvoc, temperature);
      selectMode(co2, tvoc, temperature);
    }
    else{
      Serial.println("ERROR!");
      while(1);
    }
  }
}

void selectMode(int co2, int tvoc, float temperature) {
  switch (modeCounter) {
    case 0:
      displayTvocLevel(display, tvoc);
      break;
    case 1:
      displayCo2Level(display, co2);
      break;
    case 2:
      displayTemperature(display, temperature);
      break;
    default:
      displayTvocLevel(display, tvoc);
      break;
  }
  
  if(modeCounter > 2) modeCounter = 0;
  
  if(clearDisplay) {
    display.fill(0);
    clearDisplay = false;
  }
}

void printData(int co2, int tvoc, float temperature) { 
  Serial.print("CO2: ");
  Serial.print(co2);
  Serial.print("ppm, TVOC: ");
  Serial.println(tvoc);
  Serial.print("temperature : ");
  Serial.print(temperature);
  Serial.println("C");
  Serial.print("mode counter : ");
  Serial.println(modeCounter);
}

void changeMode() {
  clearDisplay = !clearDisplay;
  modeCounter++;
}
