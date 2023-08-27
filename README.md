# sokoban
need FLTK to run, documentation: https://www.fltk.org

Linux:
$ sudo apt install libfltk1.3-dev

Mac:
$ brew install fltk

then just type make to compile in your terminal and ./main to run.

In the game the blue square is the player, the light blue squares are teleporters, the red are crate the player can move them and the green are target (the player have to move the crate on the target so they turn yellow).

We use manual pointer so there is some issue with memory access, but we'll (maybe one day) change it to unique pointer.
