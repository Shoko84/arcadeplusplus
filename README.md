# arcade++
### _A flexible arcade game platform in C++_

## Description
### Dynamic libraries
Yes, this project is much based on __dynamic libraries *(.so)*__, which make this extremely _flexible_ and _customizable_ !  
_More in this part to come.._

## Compilation
Simple as ever, just `make` at the root of this repository to compile all current games and graphic libraries !

## Usage
After the compilation is successfully, the `./arcade++` binary is waiting an argument, which is the __graphic dynamic library__ at launch.  
All graphic libraries are located into the `lib` folder and games libraries into the `games` folder.

#### Example
`./arcade++ ./lib/lib_arcade_sfml.so` will launch the program with the SFML library.

__/!\ If you have any problems when compiling graphic libs, then install on your machine the appropriate library, I will fix up this soon !__  
_The reason is that you may have missing dependencies for the library you can't compile and I've put in the local dependencies some important files so, yeah, that's a lil' fucked up._

_For now it's a little empty so yeah, I'll try to fill this up.._  

_Made by Maxime Cauvin with **<3**_

> Special thanks to Enguerrand Allamel who "works" with me on this project :)
