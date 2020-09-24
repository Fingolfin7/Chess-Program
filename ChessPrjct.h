#pragma once
#include <iostream>
#include <array>

class ChessBoard{
	private:
		struct Piece{
				char symbol;
				char colour;
				bool moveIsLegal(int formRow, int fromCol, int toRow, int toCol, const ChessBoard *cBoard);
		};
					
		struct Square{
				bool hasPiece;
				Piece occupyingPiece;
		};
		
	public:	
		int turn;
		std::array<std::array<Square, 8>, 8> boardSquare;//this would have been fine too -> Square boardSqaure[8][8] 
		
		ChessBoard();
		char checkTurn();
		void move(int formRow, int fromCol, int toRow, int toCol);

		
};


