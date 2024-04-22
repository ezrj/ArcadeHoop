#include <Arduino.h>

#include <Adafruit_NeoPixel.h>
#define PIN        6
#define BUZZER_PIN 13
#define NUMPIXELS 256
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#include <RotaryEncoder.h>
#define MOTOR_DIRECTION_IN1 4
#define MOTOR_DIRECTION_IN2 5
#define MOTOR_ENABLE 7
#define MOTOR_ENCODER_IN1 2  // Must be digital 2 & 3
#define MOTOR_ENCODER_IN2 3
RotaryEncoder *encoder = nullptr;

bool moveMotor = false;
int level = 1;


void checkMotorPosition() {
  static int motor_encoder_position = 0;

  encoder->tick();

  int newPos = encoder->getPosition();
  if (motor_encoder_position != newPos) {
    Serial.print("pos:");
    Serial.print(newPos);
    Serial.print(" dir:");
    Serial.println((int)(encoder->getDirection()));
    motor_encoder_position = newPos;

    if (moveMotor) {
      if (newPos < -250) {
	digitalWrite(MOTOR_DIRECTION_IN1, HIGH);
	digitalWrite(MOTOR_DIRECTION_IN2, LOW);
      }
      else if (newPos > 250) {
	digitalWrite(MOTOR_DIRECTION_IN1, LOW);
	digitalWrite(MOTOR_DIRECTION_IN2, HIGH);
      }
    } else {
      if (newPos > -35 && newPos < 35) {
	digitalWrite(MOTOR_DIRECTION_IN1, LOW);
	digitalWrite(MOTOR_DIRECTION_IN2, LOW);
      }
      else if (newPos < -35) {
	digitalWrite(MOTOR_DIRECTION_IN1, HIGH);
	digitalWrite(MOTOR_DIRECTION_IN2, LOW);
      }
      else if (newPos > 35) {
	digitalWrite(MOTOR_DIRECTION_IN1, LOW);
	digitalWrite(MOTOR_DIRECTION_IN2, HIGH);
      }
    }
  }
}


#include <PinChangeInterrupt.h>
#define HOOP_BUTTON 9
#define GAME_BUTTON_1 10
#define GAME_BUTTON_2 11
unsigned int score = 0;
unsigned long lastScoreTime = 0;
bool startGameEasy = false;
bool startGameHard = false;
bool extraPoints = false;


void buttonInterrupt() {
  if (digitalRead(HOOP_BUTTON) && (millis() - lastScoreTime > 500)) {
    score += extraPoints ? 3 : 2;
    if (score > 99) score = 99;
    lastScoreTime = millis();
    playScoreSound(BUZZER_PIN);
  } else if (digitalRead(GAME_BUTTON_1)) {
    startGameEasy = true;
  } else if (digitalRead(GAME_BUTTON_2)) {
    startGameHard = true;
  }
}

#define BRIGHTNESS 5

#define DELAYVAL 100
unsigned long startTime;  //some global variables available anywhere in the program
unsigned long currentTime;
//https://www.arduino.cc/reference/en/language/functions/time/millis/

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  pixels.begin();
  pinMode(MOTOR_DIRECTION_IN1, OUTPUT);
  pinMode(MOTOR_DIRECTION_IN2, OUTPUT);
  pinMode(MOTOR_ENABLE, OUTPUT);
  pinMode(HOOP_BUTTON, INPUT);
  digitalWrite(MOTOR_DIRECTION_IN1, LOW);
  digitalWrite(MOTOR_DIRECTION_IN2, LOW);
  digitalWrite(MOTOR_ENABLE, 1);
  startTime= millis();

  // Attach button interrupts
  attachPCINT(digitalPinToPCINT(HOOP_BUTTON), buttonInterrupt, CHANGE);
  attachPCINT(digitalPinToPCINT(GAME_BUTTON_1), buttonInterrupt, CHANGE);
  attachPCINT(digitalPinToPCINT(GAME_BUTTON_2), buttonInterrupt, CHANGE);


  // Attach motor encoder interrupts
  pinMode(MOTOR_ENCODER_IN1, OUTPUT);
  pinMode(MOTOR_ENCODER_IN2, OUTPUT);
  encoder = new RotaryEncoder(MOTOR_ENCODER_IN1, MOTOR_ENCODER_IN2, RotaryEncoder::LatchMode::TWO03);
  attachInterrupt(digitalPinToInterrupt(MOTOR_ENCODER_IN1), checkMotorPosition, CHANGE);
  attachInterrupt(digitalPinToInterrupt(MOTOR_ENCODER_IN2), checkMotorPosition, CHANGE);
}


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
      0,1,1,1,1,1,1,1}
    //A
    // {0,1,1,1,1,1,1,0,
    // 0,0,0,0,1,0,0,1,
    // 0,0,0,0,1,0,0,1,
    // 0,0,0,0,1,0,0,1,
    // 0,1,1,1,1,1,1,0},
    // //M
    // {0,1,1,1,1,1,1,1,
    // 0,0,0,0,0,0,1,0,
    // 0,0,0,0,1,1,0,0,
    // 0,0,0,0,0,0,1,0,
    // 0,1,1,1,1,1,1,1},
    // //R
    // {0,1,1,1,1,1,1,1,
    // 0,0,0,0,1,1,0,1,
    // 0,0,0,1,0,1,0,1,
    // 0,0,1,0,0,1,1,1,
    // 0,1,0,0,0,0,0,0}
    };
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
    case 'A':
      index = 19;
      break;
    case 'M':
      index = 20;
      break;
    case 'R':
      index = 21;
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
    pixels.setPixelColor(i + num, pixels.Color(ir * newmatrix[index][j], ig * newmatrix[index][j], ib * newmatrix[index][j]));
  }
}

//ight up the entire board with a given color
void lightUpBoard() {
  for(int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, 9, 0, 0);
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
	pixels.setPixelColor(pixelIndex, pixels.Color(BRIGHTNESS, 0, 0));
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
	  pixels.setPixelColor(pixelIndex, pixels.Color(BRIGHTNESS, 0, 0)); // can we get a maroon
	}
	else  {
	  pixels.setPixelColor(pixelIndex, pixels.Color(BRIGHTNESS, BRIGHTNESS, BRIGHTNESS));
	}
      }
      if (rightColumn < maxWidth) { //light up the right side
	int pixelIndex = row * maxWidth + rightColumn;
	if (timesRun % 2 == 0) {
	  pixels.setPixelColor(pixelIndex, pixels.Color(BRIGHTNESS, 0, 0));
	}
	else  {
	  pixels.setPixelColor(pixelIndex, pixels.Color(BRIGHTNESS, BRIGHTNESS, BRIGHTNESS));
	}
      }
    }


    pixels.show();


    timer(50);
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
	pixels.setPixelColor(pixelIndex, pixels.Color(BRIGHTNESS, BRIGHTNESS, BRIGHTNESS));
      }

      if (bottomRow < maxHeight) { //light up the bottom side
	int pixelIndex = bottomRow * 32 + col;
	pixels.setPixelColor(pixelIndex, pixels.Color(BRIGHTNESS, BRIGHTNESS, BRIGHTNESS));
      }

    }
    pixels.show();


    timer(100);
  }
}

void scoreboard(int score, int time, int goal) {
  // Clear the previous display
  int progress = 0;
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

  else if (time >= 10)  {
    OnesTime = time % 10;
    int timetemp = (time - OnesTime)/10;
    TensTime = timetemp;
  }

  // Define the colors for "SCORE" and the number
  unsigned char r = 0, g = BRIGHTNESS * 2, b = BRIGHTNESS; // Green color
  unsigned char r2 = BRIGHTNESS, g2 = BRIGHTNESS, b2 = BRIGHTNESS;

  if (time < 10)  {

    r2 = 9;
    g2 = 0; 
    b2 = 0;
  }
  if (score < goal) {
    r = 9;
    g = 0; 
    b = 0;
  }
  //tens places for time
  drawChar(24, '0' + TensTime, r2, g2, b2);
  //seconds place for time
  drawChar(72, '0' + OnesTime, r2, g2, b2);
  //tens place for score
  drawChar(144, '0' + TensScore, r, g, b);
  //seconds place for score
  drawChar(192, '0' + OnesScore, r, g, b);

  progress = (32 * score) / goal;
  progress = progress / 2;
//score = 10
//goal = 20
//progress = 16

  int index = 7;
  if (score > 0)  {
  for (int i = 0; i < progress; i++)  {
    pixels.setPixelColor(index, 0, 9, 0);
    index += 1;
    pixels.setPixelColor(index, 0, 9, 0);
    index += 15;
  }}
  




  // Update the display to show the new 
  pixels.show();
}


void level1() {
  level = 1;
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
    timer(50);
  }
  pixels.clear();
}

void level2() {
  level = 2;
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
    timer(50);
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
    timer(50);
  }}


void start()  {

  drawChar(48, 'G', 0, 9, 0);
  drawChar(144, '0', 3, 3, 3);
  pixels.show();
}

void onpressEasy()  {

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
      drawChar(i + 48, 'O', 0, 9, 0);
      drawChar(i + 48 * 2, 'W', 0, 0, 9);
      drawChar(i + 48 * 3, 'D', 3, 3, 3);
      drawChar(i + 48 * 4, 'Y', 1, 4, 1);
      pixels.show();
      timer(50);
    }
  }

  //level one
  level1();
  timer(700);
  countdown();
  score = 0;

  start();
  timer(1000);
  int i = 0;
  int j = 0;
  for (i = 0; i < 61; ++i)  {
    int time = 60 - i;
    for (j = 0; j < 9; ++j) {
      scoreboard(score, time, 10);
      timer(100);
    }
    extraPoints = (time <= 10) ? true : false;
  }

  //level 2
  if (score >= 10) {
    timer(3000);
    level2();
    timer(700);
    countdown();

    start();
    timer(1000);
    int i = 0;
    int j = 0;
    for (i = 0; i < 31; ++i)  {
      int time = 30 - i;
      for (j = 0; j < 9; ++j) {
	scoreboard(score, time, 25);
	timer(100);
      }
      extraPoints = (time <= 10) ? true : false;}
  }

  //level 3
  if (score >= 25) {
    timer(3000);
    level3();
    timer(700);
    countdown();

    start();
    timer(1000);
    int i = 0;
    int j = 0;
    for (i = 0; i < 16; ++i)  {
      int time = 15 - i;
      for (j = 0; j < 9; ++j) {
	scoreboard(score, time, 100);
	timer(100);
      }
      extraPoints = (time <= 10) ? true : false;}
  }

  gameover();
  pixels.clear();
  pixels.show();
  timer(10000);

}

void onpressHard()  {

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
      drawChar(i + 48, 'O', 0, 9, 0);
      drawChar(i + 48 * 2, 'W', 0, 0, 9);
      drawChar(i + 48 * 3, 'D', 3, 3, 3);
      drawChar(i + 48 * 4, 'Y', 1, 4, 1);
      pixels.show();
      timer(50);
    }
  }

  //level one
  level1();
  timer(700);
  countdown();
  score = 0;

  moveMotor = true;
  digitalWrite(MOTOR_DIRECTION_IN1, LOW);
  digitalWrite(MOTOR_DIRECTION_IN2, HIGH);

  start();
  timer(1000);
  int i = 0;
  int j = 0;
  for (i = 0; i < 61; ++i)  {
    int time = 60 - i;
    for (j = 0; j < 9; ++j) {
      scoreboard(score, time, 20);
      timer(100);
    }
    extraPoints = (time <= 10) ? true : false;
  }

  //level 2
  if (score >= 20) {
    timer(3000);
    level2();
    timer(700);
    countdown();

    moveMotor = true;
    digitalWrite(MOTOR_DIRECTION_IN1, LOW);
    digitalWrite(MOTOR_DIRECTION_IN2, HIGH);

    start();
    timer(1000);
    int i = 0;
    int j = 0;
    for (i = 0; i < 31; ++i)  {
      int time = 30 - i;
      for (j = 0; j < 9; ++j) {
	scoreboard(score, time, 40);
	timer(100);
      }
      extraPoints = (time <= 10) ? true : false;}
  }

  //level 3
  if (score >= 40) {
    level = 3;
    timer(3000);
    level3();
    timer(700);
    countdown();

    moveMotor = true;
    digitalWrite(MOTOR_DIRECTION_IN1, LOW);
    digitalWrite(MOTOR_DIRECTION_IN2, HIGH);

    start();
    timer(1000);
    int i = 0;
    int j = 0;
    for (i = 0; i < 16; ++i)  {
      int time = 15 - i;
      for (j = 0; j < 9; ++j) {
	  scoreboard(score, time, 100);

	timer(100);
      }
      extraPoints = (time <= 10) ? true : false;}
  }
  
  gameover();
  moveMotor = false;
  pixels.clear();
  pixels.show();
  timer(10000);
  //7,8, 15, 23,

}


void countdown()  {
  pixels.clear();
  pixels.show();
  drawChar(96, '3', 9, 9, 9);
  pixels.show();
  timer(1000);
  drawChar(96, '2', 9, 9, 9);
  pixels.show();
  timer(1000);
  drawChar(96, '1', 9, 9, 9);
  pixels.show();
  timer(1000);
  pixels.clear();
}

void timer(int ms) {
  unsigned long startTime = millis();  // Record the start time
  while (millis() - startTime < ms) {
    currentTime = millis();
  }
}

void playScoreSound(int buzzerPin) {
  const int scoreMelody[] = {6000, 4000};

  const int noteDuration = 100;

  for (int i = 0; i < sizeof(scoreMelody) / sizeof(scoreMelody[0]); i++) {
    tone(buzzerPin, scoreMelody[i], noteDuration);
    delay(noteDuration);
  }
}

void playEasyModeSound(int buzzerPin) {
  tone(buzzerPin, 5000, 300);
  // const int melody[] = {300, 400, 500, 600, 700};
  // const int noteDuration = 200;

  // for (int i = 0; i < sizeof(melody) / sizeof(melody[0]); i++) {
  //   tone(buzzerPin, melody[i], noteDuration);
  //   delay(noteDuration);
  // }
}

void playHardModeSound(int buzzerPin) {
  tone(buzzerPin, 1000, 300);
//   int melody[] = {
//   196, 185, 175, 165, 156, 147, 139, 131
// };

//   int noteDurations[] = {
//     200, 200, 200, 200, 200, 200, 200, 200
//   };

//   for (int i = 0; i < 8; i++) {
//     tone(buzzerPin, melody[i], noteDurations[i]);
//     delay(noteDurations[i] * 1.3);
//   }
}



void playGameOverSound(int buzzerPin) {
  const unsigned int BASE_FREQUENCY = 262;
  const unsigned int NOTE_DURATION = 300;
  const unsigned int PAUSE_DURATION = 100;

  const int8_t gameOverMelody[] = {7, 6, 5, 4, 3, 2, 1, 0, -1, -2, -12};

  for (uint8_t i = 0; i < sizeof(gameOverMelody) / sizeof(gameOverMelody[0]); i++) {
    int8_t note = gameOverMelody[i];
    unsigned int frequency = BASE_FREQUENCY;
    
    if (note > 0) {
      frequency *= pow(1.059463094359, note); // 1.059463094359 is the 12th root of 2. This is the factor to increase the frequency by one semitone (half step)
    } else if (note < 0) {
      frequency /= pow(1.059463094359, -note);
    }

    tone(buzzerPin, frequency, NOTE_DURATION);
    delay(NOTE_DURATION + PAUSE_DURATION);
  }

  noTone(buzzerPin);
}

void gameover() {
  lightUpBoard();
  playGameOverSound(BUZZER_PIN);
  pixels.clear();
}


int timesRun = 0;

void loop() {
  // Main game
  //onpress();
  timer(300);
  if (timesRun < 255) {
    pixels.setPixelColor(timesRun, 0, 9, 0);
    pixels.show();
    timesRun += 1;
  }
  if (timesRun == 255)  {
    pixels.clear();
    pixels.show();
    timesRun = 0;
  }

  if (startGameEasy || startGameHard) {
    if (startGameEasy == true)  {
      playEasyModeSound(BUZZER_PIN);
      onpressEasy();
      startGameEasy = false;
    }
    else if (startGameHard == true)  {
      playHardModeSound(BUZZER_PIN);
      onpressHard();
      startGameHard = false;
    }
    startGameHard = false;
    startGameEasy = false;
    timesRun = 0;
  }
}
