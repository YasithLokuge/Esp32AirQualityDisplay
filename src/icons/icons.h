#include "lcdgfx.h"

struct icon {
  unsigned int x;
  unsigned int y;
  unsigned int width;
  unsigned int height;
  uint8_t *image;
};

// icons
extern const icon check PROGMEM;
extern const icon warning PROGMEM;
extern const icon thermometer PROGMEM;
extern const icon flask PROGMEM;
extern const icon cloud PROGMEM;

// levels
extern const icon levelRed PROGMEM;
extern const icon levelOrange PROGMEM;
extern const icon levelYellow PROGMEM;
extern const icon levelGreen PROGMEM;

// carets
extern const icon caretRed PROGMEM;
extern const icon caretOrange PROGMEM;
extern const icon caretYellow PROGMEM;
extern const icon caretGreen PROGMEM;

extern const icon caretSmallRed PROGMEM;
extern const icon caretSmallOrange PROGMEM;
extern const icon caretSmallYellow PROGMEM;
extern const icon caretSmallGreen PROGMEM;
