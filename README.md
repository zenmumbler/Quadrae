Quadrae
=======

A game with falling 4-tiled shapes. This is my [One Game A Month](http://onegameamonth.com/zenmumbler) entry for February 2013, which I made into a more reasonable game in March.
The goal of the game is to fill horizontal bars with the oddly shaped pieces so that those lines disappear.

As you make progress the speed of the game increases until, inevitably, the blocks will reach the top of the screen and you will lose. Have a nice day.

For more info [visit my website](http://logic-dream.com/)<br>
Contact me [on twitter](http://twitter.com/zenmumbler)


Keys
----

### Title screen

Left, Right, Up, Down: select starting level, higher is faster<br>
Return: start game, skip opening animation

### Game screen

Left, Right: move current piece left and right<br>
Down: accelerate drop speed for current piece<br>
A, Z: rotate current piece left or right, resp.<br>
Return: toggle pause<br>
Esc: exit current game


Building and Running
--------------------

Quadrae currently includes project files for Xcode and Code::Blocks.
Xcode is used to make the Mac versions Code::Blocks is used for
Windows builds. There should be no direct problems with creating a
Linux build but I have not done so as of yet.

Quadrae uses the [SFML 1.6 framework](http://sfml-dev.org/download.php)
which you will have to download and build separately. Add or change the
references to the frameworks/libraries in your project and compile.

The Xcode project has a Bundle target that will create the full
.app bundle and will also update the app binary to link to the frameworks
contained within the bundle. However, you may need to modify / amend that
build phase as it is all absolute paths and other horribleness.

For non-bundle versions of the app you will have to have the frameworks
accessible (any of your Frameworks folders) and the libraries next to the
app or in a folder in your (DY)LD_LIBRARY_PATH depending on your OS.

Additionaly, the stand-alone binaries need the data folder with the
textures and sound files to be in the same directory. The non-Mac versions
also need the Arial.ttf file included in the data folder.


Legal
-----

The code for this game is (c) 2013 Arthur Langereis (@zenmumbler).
Game concept, design and look and feel are (c) 1985-2013 Tetris Holding.
Original game concept and design by Alexey Pazhitnov.

This game is a technical experiment and a homage to the original game.
The game Quadrae and its author are not affiliated with or endorsed by
Tetris Holding or The Tetris Company and no such affiliation or endorsement
shall be inferred.

The compiled game or derivatives thereof may not be made available on
physical media or via download. At no time may the compiled game be included
in any public or commercial software collection. No commercial gain may
be made directly or indirectly from the compiled game and/or the game
source code.

If you like Quadrae, please visit
[the official Tetris website](http://tetris.com/) and find a game to play there.

The background and piece textures were taken from: [http://www.vectortiles.com/tetris-seamless-tiles/]()
