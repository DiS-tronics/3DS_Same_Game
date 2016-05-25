# 3DS Same Game

This is a homebrew game for the 3DS.

### Description of the game itself:
A game where blocks with different colors are ordered randomly to form a field. 
Blocks which have at least one neighbor with the same color could be deleted. 
If blocks are deleted the remaining blocks always move up to the left bottom corner 
of the game board. The goal of the Same Game is to delete all blocks of the field.

### Playing instructions:
The game is very simple to play, just use the touch-screen as input. After the game 
is finished press A or tap the touch-screen to play again. Just press the START button 
at any time to exit. Of course one can use the home button to pause the game.

### Build instructions:
Some batch files are added that ease the building process. The create_banner.bat has to
be used first, then build.bat can be executed. 

##### In addition to devkitPro some more tools are needed to build this application:
- For the picture conversion like in many other 3DS homebrew projects Imagemagick is used, 
see the following link for more information: [Imagemagick](http://www.imagemagick.org/script/index.php)
- To create the banner and icon needed for a proper cia file the 3DS_Banner_Maker tool 
from AlbertoSONIC is used, see: [3DS_Banner_Maker](https://github.com/AlbertoSONIC/3DS_Banner_Maker)
- For trying out the game on the PC the emulator [Citra](https://citra-emu.org/) is a nice tool, 
therefore the play.bat file may be used to directly start the game with Citra.

