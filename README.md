# ASCIIJump
A clone of Geometry Dash in plain text. This is the 3DS version.

## Features
* Beautiful main menu
* Coming soon message for unmade levels, not just junk
* R & L buttons work on the menu as well as Circle-and-D-Pads
* Speed is the same as Geometry Dash (11 squares per second)
* Jump is the same as Geometry Dash (3*4 jump area)
* Easy level implementation in the code with simple ASCII characters and a define function
* Blocks included:
  * Square Cube (B)
  * Lined Cube (D)
  * Small Spike (x)
  * Big Spike (X)
  * Spike Grid (s)
  * Top half-cube (-) and bottom half-cube (_)
  * Slopes (/ and \) (does not have collision detection ATM)
  * C means not complete
  * F means level end
  * Space means air block
* Percentage scores (they do not save to the scores file, though)
* New: Cube customization
 * Press Y to access the menu
 * The icon previews look disgusting right now, but don't worry, the real ones are better!
 * You can't save the cube you have, so you have to change it each play

#### Non-features
* Music (the code is not working)
* Saving high scores or cube
* Practice mode
* Different play modes (ship, UFO, ball)
* Importing custom levels (soon)
* Cool death, high score, and finish screens

## Setup
Drop the 3dsx/cia/elf file into the destination, and place the data folder next to your executable. If there is no data folder, make it like specified below. Here is the directory structure:
* Main folder for ASCIIJump
  * ASCIIJump3DS.<3dsx/elf/cia>
  * (ASCIIJump3DS.smdh)
  * data/
    * scores.txt
    * cube.txt
    * (background-loop.bin)
    * (level<x>.bin)
