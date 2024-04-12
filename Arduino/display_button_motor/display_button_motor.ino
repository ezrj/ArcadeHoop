#include <Adafruit_NeoPixel.h>
#define PIN        6
#define NUMPIXELS 256
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#include <RotaryEncoder.h>
#define MOTOR_DIRECTION_IN1 2
#define MOTOR_DIRECTION_IN2 3
#define MOTOR_ENABLE 4
#define MOTOR_ENCODER_IN1 A0
#define MOTOR_ENCODER_IN2 A1
RotaryEncoder *encoder = nullptr;

int motor_encoder_position = 0;
int motor_position_min;
int motor_position_max;

#define HOOP_BUTTON 8


#define ARCADE_BUTTON1 9
#define ARCADE_BUTTON2 10

#define DELAYVAL 100



void motorMove() {
  // Move to left while ARCADE_BUTTON1 held, right with ARCADE_BUTTON2 held
  unsigned int count = 0;
  while (1) {
    if (digitalRead(ARCADE_BUTTON1) == HIGH && digitalRead(ARCADE_BUTTON2) == LOW) {
      digitalWrite(MOTOR_DIRECTION_IN1, 1);
      digitalWrite(MOTOR_DIRECTION_IN2, 0);
      analogWrite(MOTOR_ENABLE, 10);
    } else if (digitalRead(ARCADE_BUTTON1) == LOW && digitalRead(ARCADE_BUTTON2) == HIGH) {
      digitalWrite(MOTOR_DIRECTION_IN1, 0);
      digitalWrite(MOTOR_DIRECTION_IN2, 1);
      analogWrite(MOTOR_ENABLE, 10);
    } else {
      digitalWrite(MOTOR_DIRECTION_IN1, 0);
      digitalWrite(MOTOR_DIRECTION_IN2, 0);
      analogWrite(MOTOR_ENABLE, 0);
      ++count;
    }
    delay(20)

    // Return if button hasn't been pressed for 5 seconds
    if (count >= 250) {
      return;
    }
  }
}

// Choose left and rightmost position for the hoop to prevent causing damage
void calibrateMotor() {
  // Choose leftmost position
  motorMove();
  encoder->tick();
  motor_position_min = encoder->getPosition();

  // Choose rightmost position
  motorMove();
  encoder->tick();
  motor_position_max = encoder->getPosition();
}

void setup() {
  pixels.begin();
  pinMode(MOTOR_DIRECTION_IN1, OUTPUT);
  pinMode(MOTOR_DIRECTION_IN2, OUTPUT);
  pinMode(MOTOR_ENABLE, OUTPUT);
  pinMode(HOOP_BUTTON, INPUT);
  digitalWrite(MOTOR_DIRECTION_IN1, LOW);
  digitalWrite(MOTOR_DIRECTION_IN2, HIGH);
  analogWrite(MOTOR_ENABLE, 255);

  // Attach motor encoder interrupts
  attachInterrupt(digitalPinToInterrupt(MOTOR_ENCODER_IN1), checkMotorPosition, CHANGE);
  attachInterrupt(digitalPinToInterrupt(MOTOR_ENCODER_IN2), checkMotorPosition, CHANGE);

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


// Light up the entire board with a given color
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
                pixels.setPixelColor(pixelIndex, pixels.Color(8, 0, 0)); 
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
                    pixels.setPixelColor(pixelIndex, pixels.Color(9, 0, 0)); // can we get a maroon
                }
                else  {
                    pixels.setPixelColor(pixelIndex, pixels.Color(9, 9, 9)); 
                }
            }
            if (rightColumn < maxWidth) { //light up the right side
                int pixelIndex = row * maxWidth + rightColumn;
                if (timesRun % 2 == 0) {
                    pixels.setPixelColor(pixelIndex, pixels.Color(9, 0, 0)); 
                }
                else  {
                    pixels.setPixelColor(pixelIndex, pixels.Color(9, 9, 9)); 
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
                pixels.setPixelColor(pixelIndex, pixels.Color(5, 5, 5)); 
            }

            if (bottomRow < maxHeight) { //light up the bottom side
                int pixelIndex = bottomRow * 32 + col;
                pixels.setPixelColor(pixelIndex, pixels.Color(5, 5, 5)); 
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
    drawChar(0, TensTime, r, g2, b2);
    //seconds place for time
    drawChar(32, OnesTime, r, g2, b2);
    //tens place for score
    drawChar(32 * 2, TensScore, r, g, b);
    //seconds place for score
    drawChar(32 * 3, OnesScore, r, g, b);



    // Update the display to show the new scoreboard
    pixels.show();
}

void runthrough() {
    // unsigned char r = 0, g = 255, b = 0;
    // //drawChar(32, 6, r, g ,b);
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

    for (short i = 256; i > -300; i -= 8) {
        pixels.clear();

        drawChar(i, 'L', 9, 0, 0);
        drawChar(i + 32, 'E', 0, 9, 0);
        drawChar(i + 32 * 2, 'V', 0, 0, 9);
        drawChar(i + 32 * 3, 'E', 3, 3, 3);
        drawChar(i + 32 * 4, 'L', 1, 4, 1);
        drawSpace(i + 32 * 5);
        drawChar(i + 32 * 6, 'O', 3, 3, 3);
        drawChar(i + 32 * 7, 'N', 3, 3, 3);
        drawChar(i + 32 * 8, 'E', 3, 3, 3);


        pixels.show();
        delay(DELAYVAL);
    }
    delay(1000);}

void level2() {

        for (short i = 256; i > -300; i -= 8) {
            pixels.clear();

            drawChar(i, 'L', 9, 0, 0);
            drawChar(i + 32, 'E', 0, 9, 0);
            drawChar(i + 32 * 2, 'V', 0, 0, 9);
            drawChar(i + 32 * 3, 'E', 3, 3, 3);
            drawChar(i + 32 * 4, 'L', 1, 4, 1);
            drawSpace(i + 32 * 5);
            drawChar(i + 32 * 6, 'T', 3, 3, 3);
            drawChar(i + 32 * 7, 'W', 3, 3, 3);
            drawChar(i + 32 * 8, 'O', 3, 3, 3);


            pixels.show();
            delay(DELAYVAL);
        }}


void level3() {

    for (short i = 256; i > -300; i -= 8) {
        pixels.clear();

        drawChar(i, 'L', 9, 0, 0);
        drawChar(i + 32, 'E', 0, 9, 0);
        drawChar(i + 32 * 2, 'V', 0, 0, 9);
        drawChar(i + 32 * 3, 'E', 3, 3, 3);
        drawChar(i + 32 * 4, 'L', 1, 4, 1);
        drawSpace(i + 32 * 5);
        drawChar(i + 32 * 6, 'T', 3, 3, 3);
        drawChar(i + 32 * 7, 'H', 3, 3, 3);
        drawChar(i + 32 * 8, 'R', 3, 3, 3);
        drawChar(i + 32 * 9, 'E', 3, 3, 3);
        drawChar(i + 32 * 10, 'E', 3, 3, 3);


        pixels.show();
        delay(DELAYVAL);
    }}

gameover()  {
  for (short i = 256; i > -300; i -= 8) {
        pixels.clear();

        drawChar(i, 'G', 9, 0, 0);
        drawChar(i + 32, 'A', 0, 9, 0);
        drawChar(i + 32 * 2, 'M', 0, 0, 9);
        drawChar(i + 32 * 3, 'E', 3, 3, 3);
        drawSpace(i + 32 * 4);
        drawChar(i + 32 * 5, 'O', 3, 3, 3);
        drawChar(i + 32 * 6, 'V', 3, 3, 3);
        drawChar(i + 32 * 7, 'E', 3, 3, 3);
        drawChar(i + 32 * 8, 'R', 3, 3, 3);


        pixels.show();
        delay(DELAYVAL);
}


void start()  {
    drawChar(0, 'S', 9, 0, 0);
    drawChar(32, 'T', 0, 9, 0);
    drawChar(32 * 2, 'A', 0, 0, 9);
    drawChar(32 * 3, 'R', 3, 3, 3);
    drawChar(32 * 4, 'T', 3, 3, 3);
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
    drawChar(96, 3, 9, 9, 9);
    pixels.show();
    delay(1000);
    drawChar(96, 2, 9, 9, 9);
    pixels.show();
    delay(1000);
    drawChar(96, 1, 9, 9, 9);
    pixels.show();
    delay(1000);
}

void empty(){};
//mySerial.println("Hello, world?");

int timesRun = 0;
void loop() {

    // Check motor position (every 560 ticks is one rotation)
    encoder->tick(); // Checks current encoder state
    int motor_encoder_position_new = encoder->getPosition(); // Gets position in ticks (16-bit signed integer)
    if (motor_encoder_position_new != motor_encoder_position) {
        // Handle logic for changing hoop direction/speed
    }

    if (digitalRead(START_BUTTON) == HIGH) {
        
      onpress();
      countdown();
      int i = 60;
      int score = 0;
      while (i > -1)  {
      
        for(int i = 0; i < 4; i++)  {
        scoreboard(i, score);
        if (digitalRead(START_BUTTON) == HIGH) {
          score += 1;
      }
        }
        i--;}
    
    //level 2
    if (score > 35) {
      level2();
      delay(1000);
      i = 30
      while (i > -1)  {

      for(int i = 0; i < 4; i++)  {
        scoreboard(i, score);
        if (digitalRead(START_BUTTON) == HIGH) {
          score += 1;
      }
        i--;}
    }
    gameover();
    pixels.clear();
    pixels.show();


    }

    //   delay(DELAYVAL);

    // digitalWrite(MOTOR_DIRECTION_IN1, !digitalRead(MOTOR_DIRECTION_IN1));
    // digitalWrite(MOTOR_DIRECTION_IN2, !digitalRead(MOTOR_DIRECTION_IN2));

}