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
		move.at(i) = std::stoi(playerMove.substr(i,1)) - 1; //subtracting one because the actual coordinates are from 0-7 not 1-8. You know, cause of how arrays work
		// move[i] = std::atoi(playerMove.substr(i,1).c_str()) - 1; <-this would be fine too
	}
	
	return move;
}

int main(){
	ChessBoard myChessBoard;
	std::string playerMove;
	std::array<int, 4> parsedMove;
	
	//draw(myChessBoard);
	
	while(playerMove.length() != -1){//basically an infinit loop
	
		try{
			draw(myChessBoard);
			std::cout<<"Enter move: " << std::endl;
			std::cout<<">";
			std::getline(std::cin, playerMove);
		
			parsedMove = parseInput(playerMove);
			
			myChessBoard.move(parsedMove[0],parsedMove[1],parsedMove[2],parsedMove[3]);
			
			//draw(myChessBoard);
			
			playerMove.clear();
		}
			
		catch(...){//to handle invalid inputs
			std::cout<<"\nInvalid Input!\n";
			std::cout<<"Input format is from-to coordinates, e.g: 7555 moves (row,col)=(7,5) to (row,col)=(5,5)\n";
			std::cin.get();
			//system("cls");
		}
	}
	
	std::cin.get();
	return 0;
}
