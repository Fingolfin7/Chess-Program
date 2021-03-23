![Screenshot](https://github.com/Fingolfin7/Chess-Program/blob/master/italian%20game.png?raw=true)
# Chess-Program
A chess project I worked on. This is a simple two player console game with no A.I opponents. 
I really enjoyed doing this. And even though I know that this isn't the best chess program out there, 
it works and all the pieces move as they should. That's something.

## Getting Started
Visual Studio 2019 is recommended,

Start by cloning the repository or downloading the zip file.

Once downloaded, open folder and run the "GenerateProject.bat" file. This will create a Visual studio 2019 solution.

Alternatively, you can enter this command on the command prompt within the folder -> `premake5.exe vs2019`
You can generate solutions for vs2019, vs2017, vs2010 etc.

"ChessPrjct.h" is the header file containing the "piece", "square" and "chessboard" classes.
"ChessPrjct.cpp" is a cpp file with the definitions for the classes mentioned above as well as a few functions.
"main.cpp" contains the draw() function and the main game loop. 


### Things I've managed to implement:  

-> A "chessboard" class that contains an 8x8 array of "Square" objects
    
-> A generic "piece" class that allows us to create specific pieces. i.e Pawns, Rooks, Knights, Bishops, Queens and Kings
    
-> A move system. Making use of "from-to" coordinates, e.g: 7555 moves (row,col)=(7,5) to (row,col)=(5,5)
    
-> Move validation. Check to see if a given move is legal. Can that piece move like that?
    
-> And a Turn system. Check to see if it's black's or whites turn
    
-> Pawn promotions
    
-> Kings are always seperated from each other by at least one square in every direction.
    
-> Checks, and
    
-> Checkmate

### Things I have not managed to implement:

-> en-passant captures,
    
-> castling.

I might come back in the future and add in what's missing. 


Take a look, run the code, and contribute if you'd like!
