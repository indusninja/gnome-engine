========================================================================================
				CONSOLE APPLICATION : MiniGolf Game Project Overview
========================================================================================

This is a demo application for the GnomeEngine4 (OpenGL engine), including source 
code of the MiniGolf Game, which is primarily the game logic.

This file contains a summary of what you will find in some of the files that
make up the MiniGolf application along with directions for use and interaction 
with the application.

\Game\game.cpp
    	This is the main application source file. The file contains delegates for OpenGL
    	rendering and input handling.
    
Directions to run Application
	The Engine compiled code and the source project file have been built in 
	Visual Studio 2008. To look at the source code, open the project file. To
	run the application use command prompt, by typing the following command
	syntax from the "\<root>\<ReleaseName>" folder:
		<application name> <datafile name>
		
	where <application name> is the name of the binary (in the included package, 
	thats "GnomeEngine3.exe"),
	<datafile name> is the name of the plain text file containing course data.
	
	The render scene represents the tiles by grass patches. The level is bordered in black
	to illustrate the edges. A cup is represented by a black circle on the level with a flag, 
	whereas a tee is the start position of the ball.
	
Interactivity
	- The Debug build of the application shows debug information about the level data in 
	  the console window explaining the various tiles in the data file.
	
	- The application implements a third-person camera, meaning the user always looks over 
	  the ball towards the direction where the arrow is pointing.
	
	- Pressing 'left arrow' rotates the input direction arrow in the anti-clockwise 
	  direction about the y-axis of the 3D space.
	
	- Pressing 'right arrow' rotates the input direction arrow in the clockwise 
	  direction about the y-axis of the 3D space.
		  
	- Pressing 'SpaceBar' will move the ball in the direction the arrow is pointing in 
	  with the power represented by the power meter in the top-left of the screen.
	  NOTE: The velocity of the ball needs to be low enough to putt into the cup. If the 
	  velocity is too high, the ball will pass through without "putting".
	  
	- Pressing 'F1' function key toggles Full Screen functionality (by default the app 
	  will start in windowed mode).
	
	- Pressing 'Esc' terminates the application.
	
	- Pressing 't'/'T' will move the ball in the upwards (this is only a debug functionality 
	  to test if the ball bouncing works)
	  NOTE: the ball bounce is very low. This is intentional to replicate real Golf Balls.
	  
	- Pressing 'm'/'M' will emulate spacebar behavious with the added feature of higher power 
	  in shot and also adding a vertical acceleration (this is only a debug functionality to 
	  test if the ball bouncing works)
	  NOTE: the ball bounce is very low. This is intentional to replicate real Golf Balls.