# Color Match Game


## Objective
The objective of this game is to match the displayed color on a randomly chosen LED to the correct color-coded alligator clip. The game utilizes the capacitance values of the alligator clips to detect touch. The LEDs and colors are randomized in order to throw the player off. The player can lose if 2.5 seconds pass after a color is displayed or if the wrong color alligator clip is pressed. 

![image](https://github.com/ShadyLitten/ENGR103_ColorMemoryGame/assets/25358185/f369a5c8-fa86-472a-8cb8-601fa363486e)


## Inputs
- A1 : **"Green"** -- Green alligator clip detecting touch
- A2 : **"Red"** -- Red alligator clip detecting touch
- A5 : **"Yellow"** -- Yellow alligator clip detecting touch
- A6 : **"Blue"** -- Blue alligator clip detecting touch

## Outputs 
- **Speaker** -- The speaker is utilized to play a beep whenever the player scores, and play a disgruntled low tone whenever the player loses. 
- **LED** 1, 3, 6, and 8. -- These 4 LEDS are corresponding to the positions of the 4 alligator clips. They are randomly generated using the random function as well as their chosen colors. 


## Rules
- The player has 2 seconds to press the correct color alligator clip corresponding to the correct LED color displayed.
- The player must not hit the wrong alligator clip, or else they lose.
- The player's objective is to get the highest score possible without messing up.
