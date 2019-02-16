# Gnome Engine
A basic game engine (OpenGL 3.x) designed for games with physics for balls.

## Core Engine Components
The general functionality for the engine is arranged in to the following areas:
- Camera
- Level Definition and Management
- Math Library
- Menu/HUD System
- Other Utilities

## MiniGolf
This is a sample game for the engine. The game is laid out as a series of holes with the par score that the player needs to achieve.

The main application source is in the `Game\game.cpp` file. The file contains delegates for OpenGL rendering and input handling.
	  
## Pool
This is another sample game for the engine, and has a 15-ball pool table layout.

The main application source is in the `Game\game.cpp` file. The file contains delegates for OpenGL rendering and input handling.

## How to build and run
The solution and projects work with Visual Studio 2017. Simply open the solution and build to generate the binaries, which will show up in the root folder under `build`.

[MiniGolf](#minigolf) and [Pool](#pool) each needs a data file (which contains the level definition) as an argument to run. Hence, to run [MiniGolf](#minigolf), execute the following command:
```bash
MiniGolf Data/course.db
```

And to run [Pool](#pool), execute the following command:
```bash
Pool Data/course.db
```
	
## How to play
The games use a third-person camera to allow the player to look over the ball towards the direction where the arrow is pointing.
	
- <kbd>&leftarrow;</kbd> & <kbd>&rightarrow;</kbd> to rotate the input arrow's direction.
- <kbd>Space</kbd> will shoot the ball in the direction the arrow, with the power represented by the power meter in the top-left of the screen.
- <kbd>F1</kbd> toggles Full Screen functionality (by default the app will start in windowed mode).
- <kbd>Esc</kbd> to show the main menu.
- <kbd>t</kbd>/<kbd>T</kbd> will move the ball in the upwards. This is only for debugging if the ball bouncing works.
- <kbd>m</kbd>/<kbd>M</kbd> will replicate the <kbd>Space</kbd> behavior, but also adds vertical impulse to the ball. Again, this is only for debugging if the ball bouncing works.