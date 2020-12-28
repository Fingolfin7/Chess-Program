#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <array>

class ChessBoard{
	private:
		struct Piece{
			char symbol;
			char colour;

			Piece() //default constructor
				:symbol(' '), colour(' ')
				{}

			Piece(char pieceSymbol, char pieceColour)
				:symbol(pieceSymbol), colour(pieceColour)
			{}

			void operator=(const Piece& piece) {//overloading the '=' assignment operator
				this->symbol = piece.symbol;
				this->colour = piece.colour;
			}

			void operator=(const Piece* piece) {//overloading the '=' assignment operator
				this->symbol = piece->symbol;
				this->colour = piece->colour;
			}


			void set(char pieceSymbol, char pieceColour) {
				symbol = pieceSymbol;
				colour = pieceColour;
			}
				
			bool moveIsLegal(int formRow, int fromCol, int toRow, int toCol, const ChessBoard *cBoard);
		};
					
		struct Square{
				bool hasPiece;
				Piece occupyingPiece;

				Square()
					:hasPiece(false)
				{}
		};
		
	public:	
		int turn;
		std::array<std::array<Square, 8>, 8> boardSquare;//this would have been fine too -> Square boardSqaure[8][8] 
		std::vector<std::array<int, 4>> moveList;
		
		ChessBoard();
		char checkTurn();
		bool isInCheck();
		bool isInCheck(int posRow, int posCol);
		bool Checkmate();
		void move(int formRow, int fromCol, int toRow, int toCol);
		bool checkAfterMove(int fromRow, int fromCol, int toRow, int toCol, ChessBoard copyBoard, int currentTurn);//checks to see if the king will be in check aftera given move
		std::vector<std::array<int, 4>> getPossibleMoves();//returns a list of all the possible moves
		void recordGame();
};


