#include "lcdgfx.h"
#include "src/icons/icons.h"

void displayGauge(DisplaySSD1351_128x128x16_SPI &display);
void displayTemperature(DisplaySSD1351_128x128x16_SPI &display, float temperature);
void displayCo2Level(DisplaySSD1351_128x128x16_SPI &display, int co2);
void displayTvocLevel(DisplaySSD1351_128x128x16_SPI &display, int tvoc);
void displayWarning(DisplaySSD1351_128x128x16_SPI &display);
void displayCheck(DisplaySSD1351_128x128x16_SPI &display);
void displayLevel(DisplaySSD1351_128x128x16_SPI &display, int high, int low, int value);
