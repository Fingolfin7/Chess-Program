#include <iostream>
#include "ChessPrjct.h"

void draw(const ChessBoard &myChessBoard){
	system("cls");

	std::cout<<"\t    "<<"  1     2     3     4     5     6     7     8   " << std::endl;
	std::cout<<"\t    "<<"_____ _____ _____ _____ _____ _____ _____ _____ " << std::endl;	
	
	for (int i = 0; i < 8; i++) {

		std::cout << "\t   |" << "     |     |     |     |     |     |     |     |" << std::endl;
		std::cout << "\t" << i + 1 << "  |";

		for (int j = 0; j < 8; j++) {

			if (myChessBoard.boardSquare[i][j].hasPiece) {
				std::cout << "  " << myChessBoard.boardSquare[i][j].occupyingPiece.symbol << "  |";
			}
			else {
				std::cout << "  " << " " << "  |";
			}
		}

		std::cout << "  " << i + 1;
		std::cout << std::endl;
		std::cout << "\t   |" << "_____|_____|_____|_____|_____|_____|_____|_____|";
		std::cout << std::endl;
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

	std::cout << "* Simple Chess Program" << std::endl << std::endl;
	std::cout << "* 2 players, no computer opponent." << std::endl;
	std::cout << "* Start game as white.\n" << std::endl;
	std::cout << "Input format is from-to coordinates, e.g: 7555 moves (row,col)=(7,5) to (row,col)=(5,5)" << std::endl;
	std::cout << "Enter 'moveList'or 'list' to see a list of all the possible moves for the current turn." << std::endl;
	std::cout << "Enter 'q' or 'Q' to exit." << std::endl;
	std::cout << "\n>";
	std::cin.get();
	
	
	while(!gameOver){//ends upon checkmate
	
		try{
			draw(myChessBoard);
			if (myChessBoard.isInCheck() && !myChessBoard.Checkmate()) {
				std::cout << "*Check*" << std::endl;
			}

			if (!myChessBoard.Checkmate()) {
				std::cout << "Enter move: " << std::endl;
				std::cout << ">";
				std::getline(std::cin, playerMove);

				if (playerMove == "q" || playerMove == "Q") {
					system("cls");
					std::cout << "\t\t" << "***Game Exited***" << std::endl;
					std::cout << "\n>";
					std::cin.get();
					myChessBoard.recordGame();
					break;
				}
				else if (playerMove == "moveList" || playerMove == "list") {
					std::cout << std::endl;
					std::vector<std::array<int, 4>> possibleMoves = myChessBoard.getPossibleMoves();

					for (int i = 0; i < possibleMoves.size() - 4; i += 3) {
						for (int j = 0; j < 3; j++) {
							std::cout << possibleMoves[i + j][0] << possibleMoves[i + j][1]
								<< possibleMoves[i + j][2] << possibleMoves[i + j][3] << ", ";
						}
						std::cout << std::endl;
					}

					std::cout << std::endl << std::endl;
					std::cout << "Enter move: " << std::endl;
					std::cout << ">";
					std::getline(std::cin, playerMove);
				}

				parsedMove = parseInput(playerMove);

				myChessBoard.move(parsedMove[0], parsedMove[1], parsedMove[2], parsedMove[3]);

				playerMove.clear();
			}

			else {
				char winnerColour = ' ';
				std::string winner = " ";

				winnerColour = myChessBoard.checkTurn();
				winnerColour == 'W' ? winner = "Black" : winner = "White"; //we are setting the winner to the opposite of WinnerColour because the mate would have been delivered in the previous turn
				std::cout << "\n\nCheckmate! " << winner << " is victorious!" << std::endl;
				std::cin.get();

				gameOver = true;
				myChessBoard.recordGame();
			}
		}
			
		catch(...){//to handle invalid inputs
			std::cout<<"\nInvalid Input!\n";
			std::cout<<"Input format is from-to coordinates, e.g: 7555 moves (row,col)=(7,5) to (row,col)=(5,5)\n";
			std::cin.get();
		}
	}
	
	return 0;
}
