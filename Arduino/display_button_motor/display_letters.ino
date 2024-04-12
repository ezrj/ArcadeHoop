#include <Adafruit_NeoPixel.h>
#define PIN        6
#define NUMPIXELS 256
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 100

void setup() {
  pixels.begin();

}

bool alpha[][24]{
  {0,0,1,1,1,1,0,0, // A
   0,0,0,1,0,1,0,0,
   0,0,1,1,1,1,0,0},
  {0,0,1,1,1,1,0,0, // B
   0,0,1,0,1,1,0,0,
   0,0,1,1,1,0,0,0},
  {0,0,1,1,1,1,0,0, // C
   0,0,1,0,0,1,0,0,
   0,0,1,0,0,1,0,0},
  {0,0,1,1,1,1,0,0, // D
   0,0,1,0,0,1,0,0,
   0,0,0,1,1,0,0,0},
  {0,0,1,1,1,1,0,0, // E
   0,0,1,0,1,1,0,0,
   0,0,1,0,0,1,0,0},
  {0,0,1,1,1,1,0,0, // F
   0,0,0,1,0,1,0,0,
   0,0,0,0,0,1,0,0},
  {0,0,1,1,1,1,0,0, // G
   0,0,1,0,0,1,0,0,
   0,0,1,1,0,1,0,0},
  {0,0,1,1,1,1,0,0, // H
   0,0,0,0,1,0,0,0,
   0,0,1,1,1,1,0,0},
  {0,0,1,0,0,1,0,0, // I
   0,0,1,1,1,1,0,0,
   0,0,1,0,0,1,0,0},
  {0,0,1,0,0,1,0,0, // J
   0,0,1,1,1,1,0,0,
   0,0,0,0,0,1,0,0},
  {0,0,1,1,1,1,0,0, // K
   0,0,0,1,1,0,0,0,
   0,0,1,0,0,1,0,0},
  {0,0,1,1,1,1,0,0, // L
   0,0,1,0,0,0,0,0,
   0,0,1,0,0,0,0,0},
  {0,0,1,1,1,1,0,0, // M
   0,0,0,1,1,1,0,0,
   0,0,1,1,1,1,0,0},
  {0,0,1,1,1,1,0,0, // N
   0,0,0,0,0,1,0,0,
   0,0,1,1,1,1,0,0},
  {0,0,1,1,1,1,0,0, // O
   0,0,1,0,0,1,0,0,
   0,0,1,1,1,1,0,0},
  {0,0,1,1,1,1,0,0, // P
   0,0,0,1,0,1,0,0,
   0,0,0,1,1,1,0,0},
  {0,0,0,1,1,1,0,0, // Q
   0,0,0,1,0,1,0,0,
   0,0,1,1,1,1,0,0},
  {0,0,1,1,1,1,0,0, // R
   0,0,0,1,1,1,0,0,
   0,0,1,0,1,1,0,0},
  {0,0,1,0,1,1,0,0, // S
   0,0,1,1,0,1,0,0,
   0,0,1,1,0,1,0,0},
  {0,0,0,0,0,1,0,0, // T
   0,0,1,1,1,1,0,0,
   0,0,0,0,0,1,0,0},
  {0,0,1,1,1,1,0,0, // U
   0,0,1,0,0,0,0,0,
   0,0,1,1,1,1,0,0},
  {0,0,0,1,1,1,0,0, // V
   0,0,1,0,0,0,0,0,
   0,0,0,1,1,1,0,0},
  {0,0,1,1,1,1,0,0, // W
   0,0,1,1,1,0,0,0,
   0,0,1,1,1,1,0,0},
  {0,0,1,0,1,1,0,0, // X
   0,0,0,1,1,0,0,0,
   0,0,1,1,0,1,0,0},
  {0,0,0,0,1,1,0,0, // Y
   0,0,1,1,1,0,0,0,
   0,0,0,0,1,1,0,0},
  {0,0,1,1,0,1,0,0, // Z
   0,0,1,0,1,1,0,0,
   0,0,1,0,1,1,0,0},
  {0,0,1,1,1,1,0,0, // 0
   0,0,1,0,0,1,0,0,
   0,0,1,1,1,1,0,0},
  {0,0,0,0,0,1,0,0, // 1
   0,0,1,1,1,1,0,0,
   0,0,0,0,0,0,0,0},
  {0,0,1,1,0,1,0,0, // 2
   0,0,1,1,0,1,0,0,
   0,0,1,0,1,1,0,0},
  {0,0,1,0,0,1,0,0, // 3
   0,0,1,0,1,1,0,0,
   0,0,1,1,1,1,0,0},
  {0,0,0,1,1,1,0,0, // 4
   0,0,0,1,0,0,0,0,
   0,0,1,1,1,1,0,0},
  {0,0,1,0,1,1,0,0, // 5
   0,0,1,0,1,1,0,0,
   0,0,1,1,0,1,0,0},
  {0,0,1,1,1,1,0,0, // 6
   0,0,1,1,0,1,0,0,
   0,0,1,1,0,0,0,0},
  {0,0,0,0,0,1,0,0, // 7
   0,0,0,1,0,1,0,0,
   0,0,1,1,1,1,0,0},
  {0,0,1,1,1,1,0,0, // 8
   0,0,1,0,1,1,0,0,
   0,0,1,1,1,1,0,0},
  {0,0,1,0,1,1,0,0, // 9
   0,0,1,0,1,1,0,0,
   0,0,1,1,1,1,0,0},
};

// Draw a single character
void drawChar(short position, unsigned char character, unsigned char ir, unsigned char ig, unsigned char ib) {
  // Change digits to characters after main alphabet
  if (character < 10) {
    character += 91;
  }
  // Determine which lines of the character need to be flipped vertically based on the start position (even or odd column)
  //bool flipcolumn = (position % 16 > 7) || (position % 16 < -7);
  bool flipcolumn = (position % 16 > 7) || (position % 16 < -7);

  // Loop through pixels in character and set color
  //for (unsigned char location=0; location<40; ++location) {
  for (unsigned char location=0; location<24; ++location) {
    unsigned char pixel = location;

    // Flip lines vertically based on start position and current location
    if ((flipcolumn && (location % 16 > 7)) || (!flipcolumn && (location % 16 < 8))) {
        pixel = 7 + (8 * (location / 8)) - location % 8;
    }

    // Set pixel color. Convert character to corresponding entry in array by subtracting ascii value of 'A'
    pixels.setPixelColor(position + location, pixels.Color(ir * alpha[character - 65][pixel], ig * alpha[character - 65][pixel], ib * alpha[character - 65][pixel]));
  }
}

void drawSpace(short position) {
  for (unsigned char i=0; i<40; ++i) {
    unsigned char j = i;
    pixels.setPixelColor(i + position, 0, 0, 0);
  }
}

int timesRun = 0;
void loop() {
  pixels.clear();
  pixels.show();
  for (unsigned short i = 65; i < (65 + 26); ++i) {
    pixels.clear();
    drawChar(8, i, 9, 0, 0);
    pixels.show();
    delay(1000);
  }
  for (unsigned short i = 0; i < 10; ++i) {
    pixels.clear();
    drawChar(8, i, 0, 9, 0);
    pixels.show();
    delay(1000);
  }
  pixels.clear();
  pixels.show();
  delay(1000);
}
