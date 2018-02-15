Graphics Assignment 1
=====================

Pacman Killer 2D game in OpenGL 3.

Sayak Kundu - 20161035
=======================

### Controls

- **Mousewheel** - Zoom
- **A**, **S**, **W**, **D** / **Mouse drag** - Pan (when zoomed)
- **Up**, **Right**, **Left** - Player ball movement


### Extra features

- Colourful background
- Score
- 3 Lives. Lives lost when the ball touches porcupine
- Zooming/panning using both mouse and keyboard
- Modularity
- Added audio to the game


### Scoring

- ​Touching the porcupine will make you lose your life and deducts 50 points.
- Touching the enemy ball without plank will increase score by 2.
- Touching the enemy ball with plank will increase score by 1.


### Run the game

- You can run it using Qt Creator. Just go to *Open Project* then select the *CMakeLists.txt*. Then *Ctrl+R* to run it.

**OR**

- Via Terminal - Go to *build* folder. Then run *cmake ..*. After that run *make*. Then execute *./graphics_asgn1*.
