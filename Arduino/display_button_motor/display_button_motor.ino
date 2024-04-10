#include <Adafruit_NeoPixel.h>
#define PIN        6
#define NUMPIXELS 256
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define MOTOR_DIRECTION_IN1 2
#define MOTOR_DIRECTION_IN2 3
#define MOTOR_ENABLE 4

#define HOOP_BUTTON 8

#define DELAYVAL 100

void setup() {
  pixels.begin();
  pinMode(MOTOR_DIRECTION_IN1, OUTPUT);
  pinMode(MOTOR_DIRECTION_IN2, OUTPUT);
  pinMode(MOTOR_ENABLE, OUTPUT);
  pinMode(HOOP_BUTTON, INPUT);
  digitalWrite(MOTOR_DIRECTION_IN1, LOW);
  digitalWrite(MOTOR_DIRECTION_IN2, HIGH);
  analogWrite(MOTOR_ENABLE, 255);
}

bool numeric[10][40] = {
  /*0*/ {0,1,1,1,1,1,1,1,
         0,1,0,0,0,1,0,1,
         0,1,0,0,1,0,0,1,
         0,1,0,1,0,0,0,1,
         0,1,1,1,1,1,1,1},

  /*1*/ {0,1,0,0,0,1,0,0,
         0,1,0,0,0,0,1,0,
         0,1,1,1,1,1,1,1,
         0,1,0,0,0,0,0,0,
         0,1,0,0,0,0,0,0},

  /*2*/ {0,1,0,0,0,1,1,0,
         0,1,1,0,0,0,0,1,
         0,1,0,1,0,0,0,1,
         0,1,0,0,1,1,1,1,
         0,0,0,0,0,0,0,0},

  /*3*/ {0,0,1,0,0,0,1,0,
         0,1,0,0,0,0,0,1,
         0,1,0,0,1,0,0,1,
         0,0,1,1,1,1,1,0,
         0,0,0,0,0,0,0,0},

  /*4*/ {0,0,0,0,1,1,1,1,
         0,0,0,0,1,0,0,0,
         0,0,0,0,1,0,0,0,
         0,1,1,1,1,1,1,1,
         0,0,0,0,0,0,0,0},

  /*5*/ {0,0,1,0,1,1,1,1,
         0,1,0,0,1,0,0,1,
         0,1,0,0,1,0,0,1,
         0,0,1,1,0,0,0,1,
         0,0,0,0,0,0,0,0},

  /*6*/ {0,1,1,1,1,1,1,1,
         0,1,0,0,1,0,0,1,
         0,1,0,0,1,0,0,1,
         0,1,0,0,1,0,0,1,
         0,1,1,1,1,0,0,1},

  /*7*/ {0,1,0,0,0,0,0,1,
         0,0,1,0,0,0,0,1,
         0,0,0,1,0,0,0,1,
         0,0,0,0,1,0,0,1,
         0,0,0,0,0,1,1,1},

  /*8*/ {0,1,1,1,1,1,1,1,
         0,1,0,0,1,0,0,1,
         0,1,0,0,1,0,0,1,
         0,1,0,0,1,0,0,1,
         0,1,1,1,1,1,1,1},

  /*9*/ {0,0,0,0,1,1,1,1,
         0,0,0,0,1,0,0,1,
         0,0,0,0,1,0,0,1,
         0,0,0,0,1,0,0,1,
         0,1,1,1,1,1,1,1}};

bool alpha[26][40] = {
  /*A*/ {0,1,1,1,1,1,1,0,
         0,0,0,0,1,0,0,1,
         0,0,0,0,1,0,0,1,
         0,0,0,0,1,0,0,1,
         0,1,1,1,1,1,1,0},

  /*B*/ {0,1,1,1,1,1,1,1,
         0,1,0,0,1,0,0,1,
         0,1,0,0,1,0,0,1,
         0,1,0,0,1,0,0,1,
         0,1,1,1,0,1,1,1},

  /*C*/ {0,0,1,1,1,1,1,0,
         0,1,0,0,0,0,0,1,
         0,1,0,0,0,0,0,1,
         0,1,0,0,0,0,0,1,
         0,1,0,0,0,0,0,1},

  /*D*/ {0,1,1,1,1,1,1,1,
         0,1,0,0,0,0,0,1,
         0,1,0,0,0,0,0,1,
         0,0,1,0,0,0,1,0,
         0,0,0,1,1,1,0,0},

  /*E*/ {0,1,1,1,1,1,1,1,
         0,1,0,0,0,1,0,1,
         0,1,0,0,0,1,0,1,
         0,1,0,0,0,0,0,1,
         0,1,0,0,0,0,0,1 },

  /*F*/ {0,1,1,1,1,1,1,1,
         0,0,0,0,1,0,0,1,
         0,0,0,0,1,0,0,1,
         0,0,0,0,0,0,0,1,
         0,0,0,0,0,0,0,1},

  /*G*/ {0,1,1,1,1,1,1,1,
         0,1,0,0,0,0,0,1,
         0,1,0,0,1,0,0,1,
         0,1,0,0,1,0,0,1,
         0,1,1,1,1,0,0,1},

  /*H*/ {0,1,1,1,1,1,1,1,
         0,0,0,0,1,0,0,0,
         0,0,0,0,1,0,0,0,
         0,0,0,0,1,0,0,0,
         0,1,1,1,1,1,1,1},

  /*I*/ {0,1,0,0,0,0,0,1,
         0,1,0,0,0,0,0,1,
         0,1,1,1,1,1,1,1,
         0,1,0,0,0,0,0,1,
         0,1,0,0,0,0,0,1},

  /*J*/ {0,1,1,1,0,0,0,1,
         0,1,0,0,0,0,0,1,
         0,1,1,1,1,1,1,1,
         0,0,0,0,0,0,0,1,
         0,0,0,0,0,0,0,1},

  /*K*/ {0,1,1,1,1,1,1,1,
         0,0,0,0,1,0,0,0,
         0,0,0,1,0,1,0,0,
         0,0,1,0,0,0,1,0,
         0,1,0,0,0,0,0,1},

  /*L*/ {0,1,1,1,1,1,1,1,
         0,1,0,0,0,0,0,0,
         0,1,0,0,0,0,0,0,
         0,1,0,0,0,0,0,0,
         0,1,0,0,0,0,0,0},

  /*M*/ {0,1,1,1,1,1,1,1,
         0,0,0,0,0,0,1,0,
         0,0,0,0,1,1,0,0,
         0,0,0,0,0,0,1,0,
         0,1,1,1,1,1,1,1},

  /*N*/ {0,1,1,1,1,1,1,1,
         0,0,0,0,0,0,1,0,
         0,0,0,0,0,1,0,0,
         0,0,0,0,1,0,0,0,
         0,1,1,1,1,1,1,1},

  /*O*/ {0,1,1,1,1,1,1,1,
         0,1,0,0,0,0,0,1,
         0,1,0,0,0,0,0,1,
         0,1,0,0,0,0,0,1,
         0,1,1,1,1,1,1,1},

  /*P*/ {0,1,1,1,1,1,1,1,
         0,0,0,0,1,0,0,1,
         0,0,0,0,1,0,0,1,
         0,0,0,0,1,0,0,1,
         0,0,0,0,0,1,1,1},

  /*Q*/ {0,0,1,1,1,1,1,1,
         0,0,1,0,0,0,0,1,
         0,0,1,1,0,0,0,1,
         0,0,1,1,1,1,1,1,
         0,1,0,0,0,0,0,0},

  /*R*/ {0,1,1,1,1,1,1,1,
         0,0,0,0,1,1,0,1,
         0,0,0,1,0,1,0,1,
         0,0,1,0,0,1,1,1,
         0,1,0,0,0,0,0,0},

  /*S*/ {0,0,1,0,0,0,1,0,
         0,1,0,0,0,1,0,1,
         0,1,0,0,0,1,0,1,
         0,1,0,0,0,1,0,1,
         0,0,1,1,1,0,0,1 },

  /*T*/ {0,0,0,0,0,0,0,1,
         0,0,0,0,0,0,0,1,
         0,1,1,1,1,1,1,1,
         0,0,0,0,0,0,0,1,
         0,0,0,0,0,0,0,1 },

  /*U*/ {0,1,1,1,1,1,1,1,
         0,1,0,0,0,0,0,0,
         0,1,0,0,0,0,0,0,
         0,1,0,0,0,0,0,0,
         0,1,1,1,1,1,1,1},

  /*V*/ {0,0,0,1,1,1,1,1,
         0,0,1,0,0,0,0,0,
         0,1,0,0,0,0,0,0,
         0,0,1,0,0,0,0,0,
         0,0,0,1,1,1,1,1},

  /*W*/ {0,1,1,1,1,1,1,1,
         0,0,1,0,0,0,0,0,
         0,0,0,1,1,0,0,0,
         0,0,1,0,0,0,0,0,
         0,1,1,1,1,1,1,1},

  /*X*/ {0,1,1,0,0,0,1,1,
         0,0,0,1,0,1,0,0,
         0,0,0,0,1,0,0,0,
         0,0,0,1,0,1,0,0,
         0,1,1,0,0,0,1,1},

  /*Y*/ {0,0,0,0,0,0,1,1,
         0,0,0,0,0,1,0,0,
         0,1,1,1,1,0,0,0,
         0,0,0,0,0,1,0,0,
         0,0,0,0,0,0,1,1},

  /*Z*/ {0,1,1,0,0,0,0,1,
         0,1,0,1,0,0,0,1,
         0,1,0,0,1,0,0,1,
         0,1,0,0,0,1,0,1,
         0,1,0,0,0,0,1,1}
};

// Draws a series of letters and spaces on the matrix.
void drawCharString(short position, char *string, unsigned char a, unsigned char ir, unsigned char ig, unsigned char ib) {
  for (unsigned short i; string[i] != '\0'; ++i) {
    if (string[i] >= 48 && string[i] <= 57) {
      drawNumber(position + i * 48, string[i] - 48, ir, ig, ib);
    if (string[i] != ' ') {
      drawChar(position + i * 48, string[i], ir, ig, ib);
    } else {
      drawSpace(position + i * 48)
    }
  }
}

// Draw a single character
void drawChar(short position, unsigned char character, unsigned char ir, unsigned char ig, unsigned char ib) {
  // Determine which lines of the character need to be flipped vertically based on the start position (even or odd column)
  bool flipcolumn = (position % 16 > 7) || (position % 16 < -7);

  // Loop through pixels in character and set color
  for (unsigned char location=0; location<40; ++i) {
    unsigned char pixel = location;

    // Flip lines vertically based on start position and current location
    if ((flipcolumn && (location % 16 > 7)) || (!flipcolumn && (location % 16 < 8))) {
        pixel = 7 + (8 * (location / 8)) - location % 8;
    }

    // Set pixel color. Convert character to corresponding entry in array by subtracting ascii value of 'A'
    pixels.setPixelColor(position + location, pixels.Color(ir * alpha[character - 65][pixel], ig * alpha[character - 65][pixel], ib * alpha[character - 65][pixel]));
  }
}

// Draw a single digit
void drawNumber(short position, int digit, unsigned char ir, unsigned char ig, unsigned char ib) {
    bool t = (position % 16 > 7) || (position % 16 < -7);
    for (unsigned char i=0; i<40; ++i) {
      unsigned char j = i;
      if ((t && (i % 16 > 7)) || (!t && (i % 16 < 8))) {
          j = 7 + (8 * (i / 8)) - i % 8;
      }
      pixels.setPixelColor(i + position, pixels.Color(ir * numeric[digit][j], ig * numeric[digit][j], ib * numeric[digit][j]));
  }
}

void drawSpace(short position) {
  for (unsigned char i=0; i<40; ++i) {
    unsigned char j = i;
    pixels.setPixelColor(i + position, 0, 0, 0);
  }
}

//ight up the entire board with a given color
void lightUpBoard(uint8_t r, uint8_t g, uint8_t b) {
    for(int i = 0; i < NUMPIXELS; i++) {
        pixels.setPixelColor(i, pixels.Color(r, g, b));
    }
    pixels.show(); //has its own show
}

//fun little design
void symmetrical() {
  for(int i = 0; i < 8; i++) {
    for (int j = 0; j < 32; j++)  {
      int pixelIndex = i * 32 +j;
      if ((i % 2 == 0) && (j % 2 != 0)) {
        pixels.setPixelColor(pixelIndex, pixels.Color(0, 0, 0)); 
      }
      else if ((i % 2 != 0) && (pixelIndex % 2 == 0)) {
        pixels.setPixelColor(pixelIndex, pixels.Color(80, 0, 0)); 
      }
    
  }}
  pixels.show(); 

}

void transition(int timesRun) {
    int centerColumn = 15; 
    int maxWidth = 32; 

    int maxDistance = max(centerColumn, maxWidth - centerColumn - 1);

    for (int distance = 0; distance <= maxDistance; distance++) {
        pixels.clear();

        int leftColumn = centerColumn - distance;
        int rightColumn = centerColumn + distance;


        leftColumn = max(leftColumn, 0);
        rightColumn = min(rightColumn, maxWidth - 1);

        for (int row = 0; row < 8; row++) {
            if (leftColumn >= 0) { //light up the left side
                int pixelIndex = row * maxWidth + leftColumn;
                if (timesRun % 2 == 0) {
                  pixels.setPixelColor(pixelIndex, pixels.Color(128, 0, 0)); // can we get a maroon
                }
                else  {
                  pixels.setPixelColor(pixelIndex, pixels.Color(128, 128, 128)); 
                }
            }
            if (rightColumn < maxWidth) { //light up the right side
                int pixelIndex = row * maxWidth + rightColumn;
                if (timesRun % 2 == 0) {
                  pixels.setPixelColor(pixelIndex, pixels.Color(128, 0, 0)); 
                }
                else  {
                  pixels.setPixelColor(pixelIndex, pixels.Color(128, 128, 128)); 
                }
            }
        }


        pixels.show();


        delay(50); 
    }
}

void centerout()  {
    int centerTopRow = 3;
    int centerBottomRow = 4;
    int maxHeight = 8; // Total height of the matrix

    //determine the maximum distance from the center rows to the top/bottom
    int maxDistance = max(centerTopRow, maxHeight - centerBottomRow - 1);

    for (int distance = 0; distance <= maxDistance; distance++) {
        pixels.clear();

        int topRow = centerTopRow - distance;
        int bottomRow = centerBottomRow + distance;

        topRow = max(topRow, 0);
        bottomRow = min(bottomRow, maxHeight - 1);

        for (int col = 0; col < 32; col++) {
            if (topRow >= 0) { //light up the top side
                int pixelIndex = topRow * 32 + col;
                  pixels.setPixelColor(pixelIndex, pixels.Color(128, 128, 128)); 
                }
            
            if (bottomRow < maxHeight) { //light up the bottom side
                int pixelIndex = bottomRow * 32 + col;
                  pixels.setPixelColor(pixelIndex, pixels.Color(128, 128, 128)); 
            }
            
        }
        pixels.show();

        //delay to visually see the filling effect
        delay(100); 
    }
}

void scoreboard(int score, int time) {
    // Clear the previous display
    pixels.clear();
    int OnesScore = 0;
    int TensScore = 0;
    int TensTime = 0;
    int OnesTime = 0;

    //set score
    if (score > 0 && score < 10)  {
      OnesScore = score % 10;
    }

    else if (score >= 10)  {
      OnesScore = score % 10;
      int temp = (score - OnesScore)/10;
      TensScore = temp;
    }

    //set time
    if (time > 0 && time < 10)  {
      OnesTime = time % 10;
    }

    else if (time > 10)  {
      OnesTime = time % 10;
      int timetemp = (time - OnesTime)/10;
      TensTime = timetemp;
    }
  
    // Define the colors for "SCORE" and the number
    unsigned char r = 255, g = 0, b = 0; // Green color
    unsigned char g2 = 255, b2 = 255;

    //tens places for time
    drawNumber(0, TensTime, r, g2, b2);
    //seconds place for time
    drawNumber(48, OnesTime, r, g2, b2);
    //tens place for score
    drawNumber(144, TensScore, r, g, b);
    //seconds place for score
    drawNumber(192, OnesScore, r, g, b);
  

  
    // Update the display to show the new scoreboard
    pixels.show();
}

void runthrough() {
      // unsigned char r = 0, g = 255, b = 0;
    // //drawNumber(48, 6, r, g ,b);
    // for (int i = 0; i < 3; i++) {
    // symmetrical();
    // delay(500);
    // pixels.clear();
    // pixels.show();
    // delay(500);}
    // pixels.clear();
    // pixels.show();

    // for (int i = 0; i < 3; i++) {
    // transition(1);
    // // delay(200);
    // // pixels.clear();
    // // pixels.show();
    // transition(2);
    
    // }
    // pixels.clear();
    // pixels.show();
    // for (int i = 0; i < 3; i++) {
    // centerout();
    // centerout();
    // }
}

void level1() {
  
  for (short i = 256; i > -255; i -= 8) {
    pixels.clear();

    drawChar(i, 'L', 9, 0, 0);
    drawChar(i + 48, 'E', 0, 9, 0);
    drawChar(i + 48 * 2, 'V', 0, 0, 9);
    drawChar(i + 48 * 3, 'E', 3, 3, 3);
    drawChar(i + 48 * 4, 'L', 3, 3, 3);
    drawSpace(i + 48 * 5);
    drawChar(i + 48 * 6, 'O', 3, 3, 3);
    drawChar(i + 48 * 7, 'N', 3, 3, 3);
    drawChar(i + 48 * 8, 'E', 3, 3, 3);
    
    
    pixels.show();
    delay(DELAYVAL);
}}

void level2() {
  
  for (short i = 256; i > -255; i -= 8) {
    pixels.clear();

    drawChar(i, 'L', 9, 0, 0);
    drawChar(i + 48, 'E', 0, 9, 0);
    drawChar(i + 48 * 2, 'V', 0, 0, 9);
    drawChar(i + 48 * 3, 'E', 3, 3, 3);
    drawChar(i + 48 * 4, 'L', 3, 3, 3);
    drawSpace(i + 48 * 5);
    drawChar(i + 48 * 6, 'T', 3, 3, 3);
    drawChar(i + 48 * 7, 'W', 3, 3, 3);
    drawChar(i + 48 * 8, 'O', 3, 3, 3);
    
    
    pixels.show();
    delay(DELAYVAL);
}}


void level3() {
  
  for (short i = 256; i > -255; i -= 8) {
    pixels.clear();

    drawChar(i, 'L', 9, 0, 0);
    drawChar(i + 48, 'E', 0, 9, 0);
    drawChar(i + 48 * 2, 'V', 0, 0, 9);
    drawChar(i + 48 * 3, 'E', 3, 3, 3);
    drawChar(i + 48 * 4, 'L', 3, 3, 3);
    drawSpace(i + 48 * 5);
    drawChar(i + 48 * 6, 'T', 3, 3, 3);
    drawChar(i + 48 * 7, 'H', 3, 3, 3);
    drawChar(i + 48 * 8, 'R', 3, 3, 3);
    drawChar(i + 48 * 9, 'E', 3, 3, 3);
    drawChar(i + 48 * 10, 'E', 3, 3, 3);
    
    
    pixels.show();
    delay(DELAYVAL);
}}


void start()  {
  drawChar(0, 'S', 9, 0, 0);
  drawChar(48, 'T', 0, 9, 0);
  drawChar(96, 'A', 0, 0, 9);
  drawChar(144, 'R', 3, 3, 3);
  drawChar(192, 'T', 3, 3, 3);
}


int timesRun = 0;
void loop() {

  pixels.clear();
  pixels.show();

  //   // if (digitalRead(HOOP_BUTTON) == HIGH) {
  //   //     for (unsigned char i = 0; i < 255; ++i) {
  //   //       if (i % 8 == 0) {
  //   //         pixels.setPixelColor(i, pixels.Color(20, 0, 0));
  //   //       }
  //   //     }
  //   // }
    
  //   pixels.show();
  //   delay(DELAYVAL);
  
  // digitalWrite(MOTOR_DIRECTION_IN1, !digitalRead(MOTOR_DIRECTION_IN1));
  // digitalWrite(MOTOR_DIRECTION_IN2, !digitalRead(MOTOR_DIRECTION_IN2));

}
