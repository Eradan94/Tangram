# Tangram
C++ Tangram game using [SFML](https://www.sfml-dev.org/index-fr.php) graphic library.

## Prerequisites
- In order to run `Tangram` you need to install SFML. [Here](https://www.sfml-dev.org/download-fr.php) are the link to download and install it.
- You will also need `CMake` in order to build the game. You can install it [here](https://cmake.org/download/).

## Installation
To install the game from Github, simply clone the repository and build the game using the following command :
```sh
git clone https://github.com/Eradan94/Tangram.git
cd Tangram
mkdir build
cd build
cmake ..
make
```

Then run the game using `./Tangram`.

## User instruction
The game is divided between two parts : creating a level and solving an existing one.

In the `Create` menu you can freely move the seven pieces and form whatever shape you want. You can the save the shape, under the file `save.txt`, located inside the folder `save`.

In the `Load` menu, you can load any level saved inside the `save` folder. You will have to form the shape using the tangram pieces. Once you managed to place the pieces, a screen will congrat you, and allow you to go back to the main menu.
