#include <iostream>
#include <string>
#include "ChessPrjct.h"

void draw(const ChessBoard &myChessBoard){
	system("cls");
	
	std::cout<<"\t    "<<"  1     2     3     4     5     6     7     8   " << std::endl;
	std::cout<<"\t    "<<"_____ _____ _____ _____ _____ _____ _____ _____ " << std::endl;	
	
	for(int i = 0; i < 8; i++){
		
		 std::cout<<"\t   |"<<"     |     |     |     |     |     |     |     |" << std::endl;
		 std::cout<<"\t" << i+1 << "  |";
		 
		for(int j = 0; j < 8; j++){	
		
			if(myChessBoard.boardSquare[i][j].hasPiece){
				 std::cout<< "  " << myChessBoard.boardSquare[i][j].occupyingPiece.symbol << "  |";
			}
			else{
				std::cout<< "  " << " " <<"  |";
			}
		}
		
		std::cout<<"  " << i+1;
		std::cout<< std::endl;
		std::cout<<"\t   |"<<"_____|_____|_____|_____|_____|_____|_____|_____|";
		std::cout<< std::endl;
	}
	
	std::cout<<std::endl;
	std::cout<<"\t    "<<"  1     2     3     4     5     6     7     8   " << std::endl;
}

std::array<int,4> parseInput(const std::string& playerMove){
	std::array<int, 4>move;
	
	for(int i = 0; i < 4; i++){
		move.at(i) = std::stoi(playerMove.substr(i,1)) - 1; //subtracting one because the actual coordinates are 0-7 not 1-8.
		//move[i] = std::stoi(playerMove.substr(i,1)) - 1;
	}
	
	return move;
}

int main(){
	ChessBoard myChessBoard;
	std::string playerMove;
	std::array<int, 4> parsedMove;
	bool gameOver = false;
	
	//draw(myChessBoard);
	
	while(!gameOver){//ends upon checkmate
	
		try{
			draw(myChessBoard);
			if (myChessBoard.isInCheck()) {
				std::cout << "*Check*" << std::endl;
				//std::cin.get();
			}

			if (!myChessBoard.Checkmate()) {
				std::cout << "Enter move: " << std::endl;
				std::cout << ">";
				std::getline(std::cin, playerMove);

				parsedMove = parseInput(playerMove);

				myChessBoard.move(parsedMove[0], parsedMove[1], parsedMove[2], parsedMove[3]);

				
				//draw(myChessBoard);

				playerMove.clear();
			}

			else {
				char winnerColour = ' ';
				std::string winner = " ";

				winnerColour = myChessBoard.checkTurn();
				winnerColour == 'W' ? winner = "Black" : winner = "White"; //we are setting the winner to the opposite of WinnerColour because the mate would have been delivered in the previous turn
				std::cout << "Checkmate! " << winner << " is victorious!" << std::endl;
				std::cin.get();

				gameOver = true;
			}
		}
			
		catch(...){//to handle invalid inputs
			std::cout<<"\nInvalid Input!\n";
			std::cout<<"Input format is from-to coordinates, e.g: 7555 moves (row,col)=(7,5) to (row,col)=(5,5)\n";
			std::cin.get();
			//system("cls");
		}
	}
	
	//std::cin.get();
	return 0;
}
