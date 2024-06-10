#include <Adafruit_CircuitPlayground.h>
#include <AsyncDelay.h>

int score;
int pin = A5;
volatile int greenCap;
volatile int redCap;
volatile int ylwCap;
volatile int blueCap;
int randomPixel;
long chooseColor;
AsyncDelay delay_2s;
bool colorChosen;
bool needRandomPixel = false;
bool redChosen = false;
bool greenChosen = false;
bool ylwChosen = false;
bool blueChosen = false;

/////////////////////////
//  BUTTONS
//  PIXEL 1 / A5
//  PIXEL 3 / A7
//  PIXEL 6 / A1 GREEN
//  PIXEL 8 / A2 RED
/////////////////////////

void setup() {
  CircuitPlayground.setBrightness(20);
  randomSeed(analogRead(1));
  // put your setup code here, to run once:
  delay_2s.start(2500, AsyncDelay::MILLIS);  // start counting
  CircuitPlayground.begin(9600);
  // "loading animation"
  for (int i = 0; i < 10; i++) {
    CircuitPlayground.setPixelColor(i, 255, 255, 255);
    delay(50);
    CircuitPlayground.clearPixels();
  };
}

void loop() {
  CircuitPlayground.setBrightness(20);
  gameFunct();
  // Serial.println("Green:");
  //Serial.println(greenCap);
  //Serial.println("Red:");
  //Serial.println(redCap);
  //greenCap = CircuitPlayground.readCap(A1); // value > 1000 is the threashhold
  // redCap = CircuitPlayground.readCap(A2); // value > 1000 is the threashhold
};
// color choosing function
void randomColor() {
  if (colorChosen == false) {
    CircuitPlayground.clearPixels();
    chooseColor = random(0, 4);
    colorChosen = true;
  };
  if (chooseColor == 0 && colorChosen == true) {  // choose red
    delay(25);
    CircuitPlayground.clearPixels();
    CircuitPlayground.setPixelColor(randomPixel, 255, 0, 0);
    Serial.println("choose red");
    redChosen = true;
  } else if (chooseColor == 1 && colorChosen == true) {  // choose green
    delay(25);
    CircuitPlayground.clearPixels();
    CircuitPlayground.setPixelColor(randomPixel, 0, 255, 0);
    Serial.println("choose green");
    greenChosen = true;
  } else if (chooseColor == 2 && colorChosen == true) {  // choose blue
    delay(25);
    CircuitPlayground.clearPixels();
    blueChosen = true;
    CircuitPlayground.setPixelColor(randomPixel, 0, 0, 255);
    Serial.println("choose blue");
  } else if (chooseColor == 3 && colorChosen == true) {  // choose yellow
    delay(25);
    CircuitPlayground.clearPixels();
    CircuitPlayground.setPixelColor(randomPixel, 255, 255, 0);
    Serial.println("choose yellow");
    ylwChosen = true;
  } else {
    chooseColor = 0;
  }
};
// end color choose function

void choosePixel() {
  if (needRandomPixel == true) {
    randomPixel = random(0, 4);
    needRandomPixel = false;
  };
  if (randomPixel == 0) {
    CircuitPlayground.clearPixels();
    randomPixel = 6;
    needRandomPixel = false;

  } else if (randomPixel == 1) {
    CircuitPlayground.clearPixels();
    randomPixel = 8;
    needRandomPixel = false;

  } else if (randomPixel == 2) {
    CircuitPlayground.clearPixels();
    randomPixel = 3;
    needRandomPixel = false;
  } else if (randomPixel == 3) {
    CircuitPlayground.clearPixels();
    randomPixel = 1;
    needRandomPixel = false;
  };
};



void gameFunct() {
  redReading();
  blueReading();
  ylwReading();
  greenReading();
  randomColor();
  choosePixel();
  // if(!(delay_2s.isExpired())){
  if (greenChosen == true) {
    if (greenCap > 1000) {
      clearClips();
      needRandomPixel = true;
      colorChosen = false;
      greenChosen = false;
      score++;
      delay_2s.restart();
      //Serial.println("Score:");
      //Serial.println(score);
    } else if (redCap > 1000 || ylwCap > 1000 || blueCap > 1000) {  // end green cap > 1000
      Serial.println("Wrong cliph hit, green Chosen!");
      greenChosen = false;
      gameOver();
    };  // end else if when green is chosen

  };  // end if greenChosen is true
  if (redChosen == true) {
    if (redCap > 1000) {
      clearClips();
      needRandomPixel = true;
      colorChosen = false;
      redChosen = false;
      score++;
      delay_2s.restart();
      //Serial.println("Score:");
      //Serial.println(score);
    } else if (greenCap > 1000 || ylwCap > 1000 || blueCap > 1000) {  // end redCap > 1000
      Serial.println("Wrong cliph hit, red Chosen!");
      redChosen = false;
      gameOver();
    };  // end else if, green cap >1000
  };    // end red chosen
  if (ylwChosen == true) {
    if (ylwCap > 1000) {
      clearClips();
      needRandomPixel = true;
      colorChosen = false;
      ylwChosen = false;
      score++;
      delay_2s.restart();
      //Serial.println("Score:");
      //Serial.println(score);
    } else if (greenCap > 1000 || redCap > 1000 || blueCap > 1000) {  // end redCap > 1000
      Serial.println("Wrong cliph hit, ylw Chosen!");
      ylwChosen = false;
      gameOver();
    };  // end else if, green cap >1000
  };    // end ylw chosen
  if (blueChosen == true) {
    if (blueCap > 1000) {
      clearClips();
      needRandomPixel = true;
      colorChosen = false;
      blueChosen = false;
      score++;
      delay_2s.restart();
      //Serial.println("Score:");
      //Serial.println(score);
    } else if (greenCap > 1000 || redCap > 1000 || ylwCap > 1000) {  // end redCap > 1000
      Serial.println("Wrong cliph hit, blue Chosen!");
      blueChosen = false;
      gameOver();
    };  // end else if, green cap >1000
  };
  //} else { //end not expired
  // Serial.println("Timer ran out");
  //  blueChosen = false;
  //  gameOver();
  //  }; // end else if delay IS expired

};  //end score system


void redReading() {
  redCap = CircuitPlayground.readCap(9);  // value > 1000 is the threashhold
  delay(20);
};
void greenReading() {
  greenCap = CircuitPlayground.readCap(6);  // value > 1000 is the threashhold
  delay(20);
};
void ylwReading() {
  ylwCap = CircuitPlayground.readCap(A5);
  delay(20);
};
void blueReading() {
  blueCap = CircuitPlayground.readCap(A6);
  delay(20);
};

void clearClips() {
  redCap = 0;
  greenCap = 0;
  ylwCap = 0;
  blueCap = 0;
};

// game over loop
void gameOver() {
  needRandomPixel = true;
  colorChosen = false;
  score = 0;
  for (int i = 0; i < 10; i++) {
    CircuitPlayground.setPixelColor(i, 255, 0, 0);
  };
  delay(500);
  CircuitPlayground.clearPixels();
  delay(500);
  for (int i = 0; i < 10; i++) {
    CircuitPlayground.setPixelColor(i, 255, 0, 0);
  };
  delay(1500);
  CircuitPlayground.clearPixels();
  for (int i = 0; i < 10; i++) {
    CircuitPlayground.setPixelColor(i, 255, 255, 255);
    delay(50);
    CircuitPlayground.clearPixels();
  };
  delay_2s.restart();
};
