// libraries
#include <Adafruit_CircuitPlayground.h>
#include <AsyncDelay.h>

// global variables
int score; // var to save the score
volatile int greenCap; // stores capactiance of green clip
volatile int redCap; // stores capacitance of red clip
volatile int ylwCap; // stores capacitance of yellow clip
volatile int blueCap; // stores capacitance of blue clip
int generateRandomPixel; // stores random # 0-3 that is used to pick a pixel from 1,3,6,8
int randomPixelChosen; // var that stores that stores the 1,3,6 or 8
int chooseColor; // var that stores 0-3 that then chooses a random color from R, G, B, or Y
AsyncDelay delay_2s; // create 2s timer using the library
bool colorChosen;  // flag that tells the function that generates 0-3 (that is then assigned to a color) to run or not 
bool needRandomPixel = true; // generate a random pixel in the random function
bool redChosen = false; // set to true when red is picked in color function, then is used to run in the game function the part that deems red as the correct color to set as "correct" and the others as "wrong"
bool greenChosen = false;  // set to true when grn is picked in color function, then is used to run in the game function the part that deems red as the correct color to set as "correct" and the others as "wrong"
bool ylwChosen = false;  // set to true when ylw is picked in color function, then is used to run in the game function the part that deems red as the correct color to set as "correct" and the others as "wrong"
bool blueChosen = false;  // set to true when blue is picked in color function, then is used to run in the game function the part that deems red as the correct color to set as "correct" and the others as "wrong"
bool randomPixel = false; // flag that is used when the function has picked a random pixel but the score hasnt increased; makes sure the pixel that lights up doesnt change until the score increases and the flag is false

// for reference:
/////////////////////////
//  BUTTONS            //
//  PIXEL 1 / A5 BLUE  //
//  PIXEL 3 / A7 YLW   //
//  PIXEL 6 / A1 GREEN //
//  PIXEL 8 / A2 RED   //
/////////////////////////

void setup() {
  CircuitPlayground.setBrightness(20); // change brightness for sake of eyes
  randomSeed(analogRead(1)); // generate a random seed using an analog pin's input that isnt otherwise being used for the program
  delay_2s.start(2000, AsyncDelay::MILLIS);  // 2 second timer
  CircuitPlayground.begin(9600); // begin serial terminal
  // "loading animation"
  for (int i = 0; i < 10; i++) {
    CircuitPlayground.setPixelColor(i, 255, 255, 255);
    delay(50);
    CircuitPlayground.clearPixels();
  };
  generateRandomPixel = random(0,4); // generate a random pixel to randomize before game begins
}

void loop() {
  CircuitPlayground.setBrightness(20); // keep brightness low
  gameFunct(); // whole game contained here 
};
// color choosing function
void randomColor() {
  if (colorChosen == false) { // color chosen is a flag that is set to false each time the score increases and true when the function runs, so it randomly generates a number 0-4 once and waits for the flag to generate another color
    CircuitPlayground.clearPixels(); // clear any colors that are on
    chooseColor = random(0, 4); // actual random select using the random seed
    colorChosen = true; // turn on flag so function doesnt run again until needed
  };
  // decision area
  if (chooseColor == 0 && colorChosen == true) {  // choose red; only runs  when the flag is turned on and uses the random function to then choose a color
    delay(25); // quick delay to make sure other parts of game are not running after color is generated
    CircuitPlayground.clearPixels(); // clear pixels to make sure no other color is shown
    CircuitPlayground.setPixelColor(randomPixelChosen, 255, 0, 0); // using randomPixelChosen in later part of function, set that random chosen pixel to red
    redChosen = true; // flag to run redChosen in main game to ensure red is "correct"
  } else if (chooseColor == 1 && colorChosen == true) {  // choose green; only rujns when the colorChosen flag is turned on and uses the random # from chooseColor to then assign the chosen pixel to red
    delay(25); // quick delay to make sure other parts of game are not running after color is generated
    CircuitPlayground.clearPixels(); // clear pixels to make sure no other color is shown
    CircuitPlayground.setPixelColor(randomPixelChosen, 0, 255, 0); // using randomPixelChosen in later part of function, set that random chosen pixel to green
    greenChosen = true; // flag to run greenChosen in main game to ensure green is "correct"
  } else if (chooseColor == 2 && colorChosen == true) {  // choose blue; only rujns when the colorChosen flag is turned on and uses the random # from chooseColor to then assign the chosen pixel to blue
    delay(25); // quick delay to make sure other parts of game are not running after color is generated
    CircuitPlayground.clearPixels(); // clear pixels to make sure no other color is shown
    CircuitPlayground.setPixelColor(randomPixelChosen, 0, 0, 255);  // using randomPixelChosen in later part of function, set that random chosen pixel to blue
    blueChosen = true;  // flag to run blueChosen in main game to ensure blue is "correct"
  } else if (chooseColor == 3 && colorChosen == true) {  // choose yellow; only rujns when the colorChosen flag is turned on and uses the random # from chooseColor to then assign the chosen pixel to blue
    delay(25); // quick delay to make sure other parts of game are not running after color is generated
    CircuitPlayground.clearPixels();
    CircuitPlayground.setPixelColor(randomPixelChosen, 255, 255, 0);
    ylwChosen = true; // flag to run ylwChosen in main game to ensure ylw is "correct"
  } else {
    chooseColor = 0; // failsafe to make sure a color is chosen
  }
};
// end color choose function

void choosePixel() { // function that determines which of the 4 pixels gets chosen
  if (needRandomPixel == true) { // utilizing a flag that is set to true each time the score goes up that generates a number 0-3 once and waits to be turned on again
    generateRandomPixel = random(0,4); // random function that uses randomSeed in intro to not generate the same colors each game
    needRandomPixel = false; // set flag to false so function runs once
    randomPixel = false;  // randomPixel is the flag that is used below to determine when to filter randomPixelChosen into one of the 4 game pixels (6, 8, 1, 3)
  }; // end randomize function
  if (generateRandomPixel == 0 && randomPixel == false) { // waits for the randomPixel flag and uses the random function 
    CircuitPlayground.clearPixels(); // clear pixels so no other light is on
    randomPixelChosen = 6; // LED 6 corresponding to the position of an alligator clip
    needRandomPixel = false; // make sure this flag is false so it waits for the score to increase before running again
    randomPixel = true; // turns to true because randomPixel has been generated. this ensures the color doesnt turn on and off over and over again and only runs once.
  } else if (generateRandomPixel == 1 && randomPixel == false) { // waits for the randomPixel flag and uses the random function 
    CircuitPlayground.clearPixels(); // clear pixels to ensure nothing else is on
    randomPixelChosen = 8; // LED 8 corresponding to the position of an alligator clip
    needRandomPixel = false; // make sure this flag is false so it waits for the score to increase before running again
    randomPixel = true; // turns to true because randomPixel has been generated. this ensures the color doesnt turn on and off over and over again and only runs once.
  } else if (generateRandomPixel == 2 && randomPixel == false) {
    CircuitPlayground.clearPixels(); // clear pixels to ensure nothing else is on
    randomPixelChosen = 3;  // LED 3 corresponding to the position of an alligator clip
    needRandomPixel = false; // make sure this flag is false so it waits for the score to increase before running again
    randomPixel = true;  // turns to true because randomPixel has been generated. this ensures the color doesnt turn on and off over and over again and only runs once.
  } else if (generateRandomPixel == 3 && randomPixel == false) {
    CircuitPlayground.clearPixels(); // clear pixels to ensure nothing else is on
    randomPixelChosen = 1; // LED 1 corresponding to the position of an alligator clip
    needRandomPixel = false; // make sure this flag is false so it waits for the score to increase before running again
    randomPixel = true;  // turns to true because randomPixel has been generated. this ensures the color doesnt turn on and off over and over again and only runs once.
  };
}; // end of random pixel number generator



void gameFunct() { // main game function
  redReading(); // function that reads the capacticance of the red alligator clip, threashold is > 1000. has a slight delay to prevent accidental loss
  blueReading(); // function that reads the capacticance of the blue alligator clip, threashold is > 1000. has a slight delay to prevent accidental loss
  ylwReading(); // function that reads the capacticance of the ylw alligator clip, threashold is > 1000. has a slight delay to prevent accidental loss 
  greenReading(); // function that reads the capacticance of the green alligator clip, threashold is > 1000. has a slight delay to prevent accidental loss 
  randomColor(); // generate a random color on bootup
  choosePixel(); // generate a random pixel on bootup
if(!(delay_2s.isExpired())){ // main timer function, main game only runs when the delay is NOT expired
  if (greenChosen == true) { // flags from color function, this is when the color chosen is green
    if (greenCap > 1000) { // checks if green has been touched
      clearClips(); // sets capactiance of all clips to 0 to ensure no accidental game over
      needRandomPixel = true; // flag that indicates a new random pixel needs to be chosen
      colorChosen = false; // flag that indicates a new color needs to be picked
      greenChosen = false; // turn off red being correct so color function chooses new color
      score++; // increase score
      CircuitPlayground.playTone(440, 100); // play tone to indicate correct choice
      delay_2s.restart(); // restart timer
      Serial.println("Score:"); //print the score
      Serial.println(score);
    } else if (redCap > 1000 || ylwCap > 1000 || blueCap > 1000) {  // end green cap > 1000 
    // this checks if the capactiance of any of the other 3 colors is above 1000, indicating a wrong color choice
      Serial.println("Wrong clip hit, green Chosen!");
      greenChosen = false;  // ensures that when another color is chosen it'll get filtered to the correct "__Chosen" part of the game so that the score and lights correspond with score
      gameOver(); // play game over screens and sounds
    };  // end else if, anything but green > 1000

  };  // end if greenChosen is true
  if (redChosen == true) { // set to true when red is chosen; makes red the correct choice
    if (redCap > 1000) { // checks if red has been touched
      clearClips(); // sets capactiance of all clips to 0 to ensure no accidental game over
      needRandomPixel = true; // flag that indicates a new random pixel needs to be chosen
      colorChosen = false; // flag that indicates a new color needs to be picked
      redChosen = false; // turn off red being correct so color function chooses new color
      score++; // increase score
      CircuitPlayground.playTone(440, 100); // play tone to indicate correct choice
      delay_2s.restart(); // restart timer
      Serial.println("Score:"); // print the score
      Serial.println(score);
    } else if (greenCap > 1000 || ylwCap > 1000 || blueCap > 1000) {  // end redCap > 1000
    // this checks if the capactiance of any of the other 3 colors is above 1000, indicating a wrong color choice
      Serial.println("Wrong clip hit, red Chosen!"); // notifies player the wrong clip was hit and what was chosen
      redChosen = false; // turn off red chosen so new color can be chosen
      gameOver(); // play game over screens and sounds
    };  // end else if, anything but red > 1000
  };    // end red chosen
  if (ylwChosen == true) { // set to true when yellow is chosen; makes yellow the correct choice
    if (ylwCap > 1000) { // checks if yellow has been touched
      clearClips(); // sets capacitance of all clips to 0 to ensure no accidental game over
      needRandomPixel = true; // flag that indicates new pixel needs to be chosen
      colorChosen = false; // flag that indicates a new color needs to be picked
      ylwChosen = false; // turn off yellow being the correct color so the color function chooses new color
      score++; // increase score
      CircuitPlayground.playTone(440, 100); // play tone to indicate correct choice
      delay_2s.restart(); // restart timer
      Serial.println("Score:"); // print score
      Serial.println(score);
    } else if (greenCap > 1000 || redCap > 1000 || blueCap > 1000) {  // checks if any other color but yellow has been pressed
      Serial.println("Wrong clip hit, ylw Chosen!"); // notifies player the wrong clip was hit and what was chosen
      ylwChosen = false; // turn off flag so new color is chosen
      gameOver(); // run game over screens and sounds
    };  // end else if, anything but yellow > 1000
  };    // end ylw chosen
  if (blueChosen == true) { // set to true when blue is chosen in color function; makes blue the correct choice
    if (blueCap > 1000) { // checks if blue clip has been touched
      clearClips(); // sets capacitance of all clips to 0 to ensure no accidental game over
      needRandomPixel = true; // flag that indicates new pixel needs to be chosen
      colorChosen = false; // flag that indicates a new color needs to be picked
      blueChosen = false; // turn off blue being the correct color so color function chooses new color
      score++; // increases the score
      CircuitPlayground.playTone(440, 100); // play tone that indicates the player made the correct choice
      delay_2s.restart(); // restart 2s timer
      Serial.println("Score:"); // display score in serial monitor
      Serial.println(score);
    } else if (greenCap > 1000 || redCap > 1000 || ylwCap > 1000) {  // end blueCap >1000;
    // checks if any other color but blue has been pressed
      Serial.println("Wrong clip hit, blue Chosen!"); // tells the player they made the wrong choice
      blueChosen = false; // turn off blueChosen flag so color function generates new color
      gameOver(); // run game over
    };  // end else if, anything but blue > 1000
  }; // end blue chosen
  } else { //end not expired
  // begin Timer Expired
   Serial.println("Timer ran out"); // tell the player they ran out of time
    blueChosen = false; //  ensures no matter what color was chosen, the flag is false so new game starts at score of 0
    ylwChosen = false; // above
    redChosen = false; // above
    greenChosen = false; // above
    gameOver();
    }; // end else if delay IS expired

};  //end score system


void redReading() { // function that reads the red clip on input 9
  redCap = CircuitPlayground.readCap(9);  // capacitance value > 1000 is the threashhold. this is roughly the value when it will be touched
  delay(30); // slight delay before reading it again to avoid accidental loss
};
void greenReading() {
  greenCap = CircuitPlayground.readCap(6);  // capacitance value > 1000 is the threashhold. this is roughly the value when it will be touched
  delay(30); // slight delay before reading it again to avoid accidental loss
};
void ylwReading() {
  ylwCap = CircuitPlayground.readCap(A5); // capacitance value > 1000 is the threashhold. this is roughly the value when it will be touched
  delay(30); // slight delay before reading it again to avoid accidental loss
};
void blueReading() {
  blueCap = CircuitPlayground.readCap(A6); // capacitance value > 1000 is the threashhold. this is roughly the value when it will be touched
  delay(30); // slight delay before reading it again to avoid accidental loss
};

void clearClips() { // sets the value of all clip capactiance to 0 in order to avoid accidental loss
  redCap = 0;
  greenCap = 0;
  ylwCap = 0;
  blueCap = 0;
};

// game over loop
void gameOver() { 
  CircuitPlayground.playTone(100, 500); // low drawn out beep to indicate loss
  needRandomPixel = true; // generate new pixel for start of next game
  colorChosen = false; // generate new color for start of next game
  score = 0; // reset score
  for (int i = 0; i < 10; i++) { // turn all leds red
    CircuitPlayground.setPixelColor(i, 255, 0, 0);
  };
  delay(500); // hold the red
  CircuitPlayground.clearPixels(); // clear the red
  delay(500); // hold the clear
  for (int i = 0; i < 10; i++) { // turn all leds red
    CircuitPlayground.setPixelColor(i, 255, 0, 0);
  };
  delay(1500); // hold the red
  CircuitPlayground.clearPixels(); // clear the colors
  for (int i = 0; i < 10; i++) { //  loading animation to indicate the game is about to restart
    CircuitPlayground.setPixelColor(i, 255, 255, 255);
    delay(50);
    CircuitPlayground.clearPixels();
  };
  delay_2s.restart(); // restart the timer and start the game over
};
