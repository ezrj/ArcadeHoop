#include <Adafruit_NeoPixel.h>
#define PIN        6
#define NUMPIXELS 256
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define MOTOR_DIRECTION_IN1 2
#define MOTOR_DIRECTION_IN2 3
#define MOTOR_ENABLE 4

#define HOOP_BUTTON 8

#define DELAYVAL 100
//https://www.arduino.cc/reference/en/language/functions/time/millis/

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
  /*0*/{0,1,1,1,1,1,1,1,
  0,1,0,0,0,1,0,1,
  0,1,0,0,1,0,0,1,
  0,1,0,1,0,0,0,1,
  0,1,1,1,1,1,1,1},

  /*1*/
  {0,1,0,0,0,1,0,0,
    0,1,0,0,0,0,1,0,
    0,1,1,1,1,1,1,1,
    0,1,0,0,0,0,0,0,
    0,1,0,0,0,0,0,0},

  /*2*/
  {0,1,0,0,0,1,1,0,
    0,1,1,0,0,0,0,1,
    0,1,0,1,0,0,0,1,
    0,1,0,0,1,1,1,1,
    0,0,0,0,0,0,0,0},

  /*3*/
  {0,0,1,0,0,0,1,0,
  0,1,0,0,0,0,0,1,
  0,1,0,0,1,0,0,1,
  0,0,1,1,1,1,1,0,
  0,0,0,0,0,0,0,0},

  /*4*/{0,0,0,0,1,1,1,1,
  0,0,0,0,1,0,0,0,
  0,0,0,0,1,0,0,0,
  0,1,1,1,1,1,1,1,
  0,0,0,0,0,0,0,0},

  /*5*/{0,0,1,0,1,1,1,1,
  0,1,0,0,1,0,0,1,
  0,1,0,0,1,0,0,1,
  0,0,1,1,0,0,0,1,
  0,0,0,0,0,0,0,0},

  /*6*/{0,1,1,1,1,1,1,1,
        0,1,0,0,1,0,0,1,
        0,1,0,0,1,0,0,1,
        0,1,0,0,1,0,0,1,
        0,1,1,1,1,0,0,1},

  /*7*/{0,1,0,0,0,0,0,1,
  0,0,1,0,0,0,0,1,
  0,0,0,1,0,0,0,1,
  0,0,0,0,1,0,0,1,
  0,0,0,0,0,1,1,1},

  /*8*/{0,1,1,1,1,1,1,1,
  0,1,0,0,1,0,0,1,
  0,1,0,0,1,0,0,1,
  0,1,0,0,1,0,0,1,
  0,1,1,1,1,1,1,1},

  /*9*/{0,0,0,0,1,1,1,1,
  0,0,0,0,1,0,0,1,
  0,0,0,0,1,0,0,1,
  0,0,0,0,1,0,0,1,
  0,1,1,1,1,1,1,1}};




bool newmatrix[19][40]  {
  //L
  {0,1,1,1,1,1,1,1,
  0,1,0,0,0,0,0,0,
  0,1,0,0,0,0,0,0,
  0,1,0,0,0,0,0,0,
  0,1,0,0,0,0,0,0},
  //E
  { 0,1,1,1,1,1,1,1,
  0,1,0,0,0,1,0,1,
  0,1,0,0,0,1,0,1,
  0,1,0,0,0,0,0,1,
  0,1,0,0,0,0,0,1 },
  //V
  {0,0,0,1,1,1,1,1,
  0,0,1,0,0,0,0,0,
  0,1,0,0,0,0,0,0,
  0,0,1,0,0,0,0,0,
  0,0,0,1,1,1,1,1},
  //G
  {0,1,1,1,1,1,1,1,
  0,1,0,0,0,0,0,1,
  0,1,0,0,1,0,0,1,
  0,1,0,0,1,0,0,1,
  0,1,1,1,1,0,0,1},
  //O
  {0,1,1,1,1,1,1,1,
  0,1,0,0,0,0,0,1,
  0,1,0,0,0,0,0,1,
  0,1,0,0,0,0,0,1,
  0,1,1,1,1,1,1,1},
  //H
  {0,1,1,1,1,1,1,1,
  0,0,0,0,1,0,0,0,
  0,0,0,0,1,0,0,0,
  0,0,0,0,1,0,0,0,
  0,1,1,1,1,1,1,1},
  //W
  {0,1,1,1,1,1,1,1,
  0,0,1,0,0,0,0,0,
  0,0,0,1,1,0,0,0,
  0,0,1,0,0,0,0,0,
  0,1,1,1,1,1,1,1},
  //D
  {0,1,1,1,1,1,1,1,
  0,1,0,0,0,0,0,1,
  0,1,0,0,0,0,0,1,
  0,0,1,0,0,0,1,0,
  0,0,0,1,1,1,0,0},
  //Y
  {0,0,0,0,0,0,1,1,
  0,0,0,0,0,1,0,0,
  0,1,1,1,1,0,0,0,
  0,0,0,0,0,1,0,0,
  0,0,0,0,0,0,1,1},

  /*0*/
  {0,1,1,1,1,1,1,1,
  0,1,0,0,0,1,0,1,
  0,1,0,0,1,0,0,1,
  0,1,0,1,0,0,0,1,
  0,1,1,1,1,1,1,1},

  /*1*/
  {0,1,0,0,0,1,0,0,
    0,1,0,0,0,0,1,0,
    0,1,1,1,1,1,1,1,
    0,1,0,0,0,0,0,0,
    0,1,0,0,0,0,0,0},

  /*2*/
  {0,1,0,0,0,1,1,0,
    0,1,1,0,0,0,0,1,
    0,1,0,1,0,0,0,1,
    0,1,0,0,1,1,1,1,
    0,0,0,0,0,0,0,0},

  /*3*/
  {0,0,1,0,0,0,1,0,
  0,1,0,0,0,0,0,1,
  0,1,0,0,1,0,0,1,
  0,0,1,1,1,1,1,0,
  0,0,0,0,0,0,0,0},

  /*4*/
  {0,0,0,0,1,1,1,1,
  0,0,0,0,1,0,0,0,
  0,0,0,0,1,0,0,0,
  0,1,1,1,1,1,1,1,
  0,0,0,0,0,0,0,0},

  /*5*/
  {0,0,1,0,1,1,1,1,
  0,1,0,0,1,0,0,1,
  0,1,0,0,1,0,0,1,
  0,0,1,1,0,0,0,1,
  0,0,0,0,0,0,0,0},

  /*6*/
  {0,1,1,1,1,1,1,1,
  0,1,0,0,1,0,0,1,
  0,1,0,0,1,0,0,1,
  0,1,0,0,1,0,0,1,
  0,1,1,1,1,0,0,1},

  /*7*/
  {0,1,0,0,0,0,0,1,
  0,0,1,0,0,0,0,1,
  0,0,0,1,0,0,0,1,
  0,0,0,0,1,0,0,1,
  0,0,0,0,0,1,1,1},

  /*8*/
  {0,1,1,1,1,1,1,1,
  0,1,0,0,1,0,0,1,
  0,1,0,0,1,0,0,1,
  0,1,0,0,1,0,0,1,
  0,1,1,1,1,1,1,1},

  /*9*/
  {0,0,0,0,1,1,1,1,
  0,0,0,0,1,0,0,1,
  0,0,0,0,1,0,0,1,
  0,0,0,0,1,0,0,1,
  0,1,1,1,1,1,1,1}};
//draws a letter in a sweeping from the right motion

void drawSpace(short num) {
  //sets T
    bool t = (num % 16 > 7) || (num % 16 < -7);
    //loops from 0-39
    for (unsigned char i=0; i<40; ++i) {
      unsigned char j = i;
      if ((t && (i % 16 > 7)) || (!t && (i % 16 < 8))) {
          j = 7 + (8 * (i / 8)) - i % 8;
      }
      pixels.setPixelColor(i + num, 0, 0, 0);
  }
}

void drawChar(short num, unsigned char a, unsigned char ir, unsigned char ig, unsigned char ib) {
  //sets T
  Serial.println("The character is 'a'");
  int index = 0;
  switch (a) {
  case 'L':
    Serial.println("The character is 'a'");
    index = 0;
    break;
  case 'E':
    index = 1;
    break;
  case 'V':
    index = 2;
    break;
  case 'G':
    index = 3;
    break;
  case 'O':
    index = 4;
    break;
  case 'H':
    index = 5;
    break;
  case 'W':
    index = 6;
    break;
  case 'D':
    index = 7;
    break;
  case 'Y':
    index = 8;
    break;
  case '0':
    index = 9;
    break;
  case '1':
    index = 10;
    break;
  case '2':
    index = 11;
    break;
  case '3':
    index = 12;
    break;
  case '4':
    index = 13;
    break;
  case '5':
    index = 14;
    break;
  case '6':
    index = 15;
    break;
  case '7':
    index = 16;
    break;
  case '8':
    index = 17;
    break;
  case '9':
    index = 18;
    break;
  default:
    index = 9;
    break;}
  
  bool t = (num % 16 > 7) || (num % 16 < -7);
    //loops from 0-39
  for (unsigned char i=0; i<40; ++i) {
    unsigned char j = i;
    if ((t && (i % 16 > 7)) || (!t && (i % 16 < 8))) {
        j = 7 + (8 * (i / 8)) - i % 8;
    }
    Serial.println("The character is 'a'");
    pixels.setPixelColor(i + num, pixels.Color(1 * newmatrix[index][j], 1 * newmatrix[index][j], 1 * newmatrix[index][j]));
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

// void drawChar(short num, int digit, unsigned char ir, unsigned char ig, unsigned char ib) {
//     bool t = (num % 16 > 7) || (num % 16 < -7);
//     for (unsigned char i=0; i<40; ++i) {
//       unsigned char j = i;
//       if ((t && (i % 16 > 7)) || (!t && (i % 16 < 8))) {
//           j = 7 + (8 * (i / 8)) - i % 8;
//       }
//       pixels.setPixelColor(i + num, pixels.Color(ir * numeric[digit][j], ig * numeric[digit][j], ib * numeric[digit][j]));
//   }
// }

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
    drawChar(0, '0' + TensTime, r, g2, b2);
    //seconds place for time
    drawChar(48, '0' + OnesTime, r, g2, b2);
    //tens place for score
    drawChar(144, '0' + TensScore, r, g, b);
    //seconds place for score
    drawChar(192, '0' + OnesScore, r, g, b);
  

  
    // Update the display to show the new scoreboard
    pixels.show();
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
    drawChar(i + 48 * 6, '1', 3, 3, 3);
    
    
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
    drawChar(i + 48 * 6, '2', 3, 3, 3);

    
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
    drawChar(i + 48 * 6, '3', 3, 3, 3);
    
    
    pixels.show();
    delay(DELAYVAL);
}}


void start()  {
  drawChar(48, 'G', 0, 9, 0);
  drawChar(144, '0', 3, 3, 3);
}

void onpress()  {

    for (int i = 0; i < 3; i++) {
        transition(i);
    }

    for (int i = 0; i < 6; i++)  {
        centerout();
    }


    for (int i = 0; i < 1; i++) {
        for (short i = 256; i > -255; i -= 8) {
            pixels.clear();

            drawChar(i, 'H', 9, 0, 0);
            drawChar(i + 32, 'O', 0, 9, 0);
            drawChar(i + 32 * 2, 'W', 0, 0, 9);
            drawChar(i + 32 * 3, 'D', 3, 3, 3);
            drawChar(i + 32 * 4, 'Y', 1, 4, 1);
            drawSpace(i + 32 * 5);


            pixels.show();
            delay(DELAYVAL);
        }
    }

    level1();
    // countdown();
}

void countdown()  {
    pixels.clear();
    pixels.show();
    drawChar(96, '3', 9, 9, 9);
    pixels.show();
    delay(1000);
    drawChar(96, '2', 9, 9, 9);
    pixels.show();
    delay(1000);
    drawChar(96, '1', 9, 9, 9);
    pixels.show();
    delay(1000);
}


int timesRun = 0;
void loop() {

  int i = 0;
  while (i < 61)  {
    int time = 60 - i;
    scoreboard(i, time);
    i++;
    delay(1000);

  }

  // countdown();
  
  

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