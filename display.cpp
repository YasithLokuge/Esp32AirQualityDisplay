#include "display.h"

struct unit {
  unsigned int valueX;
  unsigned int valueY;
  unsigned int labelX;
  unsigned int labelY;
  unsigned int highValue;
  unsigned int lowValue;
};

const unit tvocU = { 56, 8, 48, 97, 100, 10};
const unit co2U = { 56, 8, 48, 97, 100, 10};
const unit temperatureU = { 56, 8, 48, 97, 100, 10};

void displayGauge(DisplaySSD1351_128x128x16_SPI &display) {
  display.drawBitmap16(levelRed.x, levelRed.y, levelRed.width, levelRed.height, levelRed.image);
  display.drawBitmap16(levelOrange.x, levelOrange.y, levelOrange.width, levelOrange.height, levelOrange.image);
  display.drawBitmap16(levelYellow.x, levelYellow.y, levelYellow.width, levelYellow.height, levelYellow.image);
  display.drawBitmap16(levelGreen.x, levelGreen.y, levelGreen.width, levelGreen.height, levelGreen.image);
}

void displayTemperature(DisplaySSD1351_128x128x16_SPI &display, float temperature) {
  displayGauge(display);
  displayLevel(display, temperatureU.highValue, temperatureU.lowValue, (int) temperature);
  display.drawBitmap16(thermometer.x, thermometer.y, thermometer.width, thermometer.height, thermometer.image);
  display.setColor(RGB_COLOR16(255,255,255));
  display.printFixed(temperatureU.valueX,  temperatureU.valueY, (char*) (String(temperature) + "C").c_str() , STYLE_NORMAL);
  display.printFixed(temperatureU.labelX,  temperatureU.labelY, "TEMP", STYLE_BOLD);
}

void displayCo2Level(DisplaySSD1351_128x128x16_SPI &display, int  co2){
  displayGauge(display);
  displayLevel(display, co2U.highValue, co2U.lowValue, co2);
  display.drawBitmap16(cloud.x, cloud.y, cloud.width, cloud.height, cloud.image);
  display.setColor(RGB_COLOR16(255,255,255));
  display.printFixed(co2U.valueX,  co2U.valueY, (char*) (String(co2) + "ppm").c_str() , STYLE_NORMAL);
  display.printFixed(co2U.labelX,  co2U.labelY, "CO2", STYLE_BOLD);
}

void displayTvocLevel(DisplaySSD1351_128x128x16_SPI &display, int  tvoc){
  displayGauge(display);
  displayLevel(display, tvocU.highValue, tvocU.lowValue, tvoc);
  display.drawBitmap16(flask.x, flask.y, flask.width, flask.height, flask.image);
  display.setColor(RGB_COLOR16(255,255,255));
  display.printFixed(tvocU.valueX,  tvocU.valueY, (char*) String(tvoc).c_str() , STYLE_NORMAL);
  display.printFixed(tvocU.labelX,  tvocU.labelY, "TVOC", STYLE_BOLD);
}

void displayWarning(DisplaySSD1351_128x128x16_SPI &display) {
  display.drawBitmap16(warning.x, warning.y, warning.width, warning.height, warning.image);
  display.drawBitmap16(caretSmallRed.x, caretSmallRed.y, caretSmallRed.width, caretSmallRed.height, caretSmallRed.image);
}

void displayCheck(DisplaySSD1351_128x128x16_SPI &display) {
  display.drawBitmap16(check.x, check.y, check.width, check.height, check.image);
  display.drawBitmap16(caretSmallGreen.x, caretSmallGreen.y, caretSmallGreen.width, caretSmallGreen.height, caretSmallGreen.image);
}

void displayLevel(DisplaySSD1351_128x128x16_SPI &display, int high, int low, int value) {
  if(value >= high) {
    displayWarning(display);
  } else {
    displayCheck(display);
  }
}
