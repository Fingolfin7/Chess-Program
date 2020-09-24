#include <iostream>
#include <string>
#include <math.h>
#include "ChessPrjct.h"

ChessBoard::ChessBoard(){
	
	turn = 1; //start with white
	
	//make an empty board
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			boardSquare[i][j].hasPiece = false;
		}
	}
	
	//create the pieces
	Piece myPawn;
	myPawn.symbol = 'P';
	
	Piece myKing;
	myKing.symbol = 'K';
	
	Piece myQueen;
	myQueen.symbol = 'Q';
	
	Piece myRook;
	myRook.symbol = 'R';
	
	Piece myKnight;
	myKnight.symbol = 'N';
	
	Piece myBishop;
	myBishop.symbol = 'B';
	
	//making them white
	myKing.colour = 'W';
	myPawn.colour = 'W';
	myQueen.colour = 'W';
	myKnight.colour = 'W';
	myRook.colour = 'W';
	myBishop.colour ='W';
	
	for(int i = 0; i < 8; i++){//white pawns
		boardSquare[6][i].hasPiece = true;
		boardSquare[6][i].occupyingPiece = myPawn;
	}
	
	//white pieces on the 1st rank
	boardSquare[7][7].occupyingPiece = myRook;//rook h1
	boardSquare[7][6].occupyingPiece = myKnight;//knight g1
	boardSquare[7][5].occupyingPiece = myBishop;//bishop f1
	boardSquare[7][4].occupyingPiece = myKing;//king on e1
	boardSquare[7][3].occupyingPiece = myQueen;// queen on d1
	boardSquare[7][2].occupyingPiece = myBishop;//bishop c1
	boardSquare[7][1].occupyingPiece = myKnight;//knight b1
	boardSquare[7][0].occupyingPiece = myRook;// rook a1
	
	for(int i = 0; i < 8; i++){
		boardSquare[7][i].hasPiece = true;
	}
	
	//making them  black
	myKing.colour = 'B';
	myKing.symbol = 'k';
	
	myPawn.colour = 'B';
	myPawn.symbol = 'p';
	
	myQueen.colour = 'B';
	myQueen.symbol = 'q';
	
	myKnight.colour = 'B';
	myKnight.symbol = 'n';
	
	myRook.colour = 'B';
	myRook.symbol = 'r';
	
	myBishop.colour ='B';
	myBishop.symbol = 'b';
	
	for(int i = 0; i < 8; i++){//black pawns
		boardSquare[1][i].hasPiece = true;
		boardSquare[1][i].occupyingPiece = myPawn;
	}
	
	//black  pieces on the 8th rank
	boardSquare[0][7].occupyingPiece = myRook;//rook h1
	boardSquare[0][6].occupyingPiece = myKnight;//knight g1
	boardSquare[0][5].occupyingPiece = myBishop;//bishop f1
	boardSquare[0][4].occupyingPiece = myKing;// king on e1
	boardSquare[0][3].occupyingPiece = myQueen;// queen on d1
	boardSquare[0][2].occupyingPiece = myBishop;//bishop c1
	boardSquare[0][1].occupyingPiece = myKnight;//knight b1
	boardSquare[0][0].occupyingPiece = myRook;// rook a1
	
	for(int i = 0; i < 8; i++){
		boardSquare[0][i].hasPiece = true;
	}
}

char ChessBoard::checkTurn(){
	char checked;
	
	if (turn % 2 == 1){
		checked = 'W';
	}
	else if(turn % 2 == 0){
		checked = 'B';
	}
	else{
		checked = 'r';
	}
	
	return checked;
}

void ChessBoard::move(int fromRow, int fromCol, int toRow, int toCol){
	Piece temp;//empty piece
	
	if(boardSquare[fromRow][fromCol].occupyingPiece.colour == checkTurn()){//check turn
		if(boardSquare[fromRow][fromCol].occupyingPiece.moveIsLegal(fromRow, fromCol, toRow, toCol, this)){//is the move a legal one?
			boardSquare[toRow][toCol].occupyingPiece = boardSquare[fromRow][fromCol].occupyingPiece;
			boardSquare[toRow][toCol].hasPiece = true;
		
			boardSquare[fromRow][fromCol].occupyingPiece = temp;
			boardSquare[fromRow][fromCol].hasPiece = false;
			turn++;//next turn
		}
		else{
			std::cout << "Illegal move!" << std::endl;
			std::cin.get();
		}
	}
	
	else{
		std::string whosTurn;
		checkTurn() == 'W' ?  whosTurn = "white" : whosTurn = "black";
		std::cout << "It's " << whosTurn << "'s turn!" << std::endl;
		std::cin.get();
	}
	
}

bool ChessBoard::Piece::moveIsLegal(int fromRow, int fromCol, int toRow, int toCol, const ChessBoard *cBoard){
	bool isLegal = false;
	
	if(fromRow == toRow && fromCol == toCol){
		isLegal = false;
	}
	
	if(symbol == 'N' || symbol == 'n'){//knights
		if(abs(fromRow - toRow) == 2 && abs(fromCol - toCol) == 1){
			
			if(cBoard->boardSquare[toRow][toCol].hasPiece && cBoard->boardSquare[toRow][toCol].occupyingPiece.colour != colour){//capture
				isLegal = true;
			}
			else if(cBoard->boardSquare[toRow][toCol].hasPiece && cBoard->boardSquare[toRow][toCol].occupyingPiece.colour == colour){
				isLegal = false;
			}
			
			else if(!cBoard->boardSquare[toRow][toCol].hasPiece){
				isLegal = true;
			}
		}
		
		else if(abs(fromRow - toRow) == 1 && abs(fromCol - toCol) == 2){
			
			if(cBoard->boardSquare[toRow][toCol].hasPiece && cBoard->boardSquare[toRow][toCol].occupyingPiece.colour != colour){//capture
				isLegal = true;
			}
			else if(cBoard->boardSquare[toRow][toCol].hasPiece && cBoard->boardSquare[toRow][toCol].occupyingPiece.colour == colour){
				isLegal = false;
			}
			
			else if(!cBoard->boardSquare[toRow][toCol].hasPiece){
				isLegal = true;
			}
		}	
	}
	
	if(symbol == 'P' || symbol == 'p'){//pawns
		
		//white pawns
		if(colour == 'W' && (fromRow - toRow) == 1 && (fromCol - toCol) == 0 && !(cBoard->boardSquare[toRow][toCol].hasPiece) ){//one sqaure jump
			isLegal = true;
		}
		else if(colour == 'W' && (fromRow - toRow) == 2 && fromRow == 6 && (fromCol - toCol) == 0 && !(cBoard->boardSquare[toRow][toCol].hasPiece) ){//double square jump. only when startin for the 2nd rank
			isLegal = true;
		}
		else if(colour == 'W' && (fromRow - toRow) == 1 && abs(fromCol - toCol) == 1 && cBoard->boardSquare[toRow][toCol].hasPiece && cBoard->boardSquare[toRow][toCol].occupyingPiece.colour != 'W'){//capturing a piece diagonally
			isLegal = true;
		}
		if(colour == 'W' && toRow == 0){//promotion
			char promote;
			std::cout<<"Promote. Enter 'Q' (white queen), 'N'(white knight), 'R'(white rook) or 'B'(white bishop) to select piece.\n>";
			std::cin >> promote;
			if(promote == 'Q' || promote == 'N' || promote == 'R' || promote == 'B'){
				symbol = promote;
			}
			else{
				isLegal = false;
			}
		}
		
		//black pawns
		if(colour == 'B' && (fromRow - toRow) == -1 && (fromCol - toCol) == 0 && !(cBoard->boardSquare[toRow][toCol].hasPiece) ){
			isLegal = true;
		}
		else if(colour == 'B' && (fromRow - toRow) == -2 && fromRow == 1 && (fromCol - toCol) == 0 && !(cBoard->boardSquare[toRow][toCol].hasPiece) ){
			isLegal = true;
		}
		else if(colour == 'B' && (fromRow - toRow) == -1 && abs(fromCol - toCol) == 1 && cBoard->boardSquare[toRow][toCol].hasPiece && cBoard->boardSquare[toRow][toCol].occupyingPiece.colour != 'B'){//capturing a piece diagonally
			isLegal = true;
		}
		if(colour == 'B' && toRow == 0){//promotion
			char promote;
			std::cout<<"Promote. Enter 'q' (black queen), 'n'(black knight), 'r'(black rook) or 'b'(black bishop) to select piece.\n>";
			std::cin >> promote;
			if(promote == 'q' || promote == 'n' || promote == 'r' || promote == 'b'){
				symbol = promote;
			}
			else{
				isLegal = false;
			}
		}
	}
	
	if(symbol == 'R' || symbol == 'r'){//rooks
		if(fromRow != toRow && fromCol == toCol && fromRow < toRow){//if the rows are changing but the col(s) aren't
			isLegal = true;
			for(int i = fromRow+1; i < toRow; i++){
				if(cBoard->boardSquare[i][toCol].hasPiece){//check for any pieces in between the start and end points
					isLegal = false;// if a piece is found, set isLegal to false
				}
			}
		}
		
		else if(fromRow != toRow && fromCol == toCol && fromRow > toRow){
			isLegal = true;
			for(int i = fromRow-1; i > toRow; i--){
				if(cBoard->boardSquare[i][toCol].hasPiece){
					isLegal = false;
				}
			}
		}
		
		else if(fromRow == toRow && fromCol != toCol && fromCol < toCol){//if the cols are changing but the row(s) aren't
			isLegal = true;
			for(int i = fromCol+1; i < toCol; i++){
				if(cBoard->boardSquare[toRow][i].hasPiece){
					isLegal = false;
				}
			}
		}
		
		else if(fromRow == toRow && fromCol != toCol && fromCol > toCol){
			isLegal = true;
			for(int i = fromCol-1; i > toCol; i--){
				if(cBoard->boardSquare[toRow][i].hasPiece){
					isLegal = false;
				}
			}
		}
		
		if(cBoard->boardSquare[toRow][toCol].hasPiece && cBoard->boardSquare[toRow][toCol].occupyingPiece.colour == colour){//can't capture your own piece
			isLegal = false;
		}
	}	
	
	if(symbol == 'K' || symbol == 'k'){//kings no checks or checkmate yet
		if(abs(fromRow - toRow) <= 1 && abs(fromCol - toCol) <= 1){
			isLegal = true;
			
			//kings need to be seperated by at least one square
			int seperation[8][2] = {//add these values to the current position to check that the kings are seperate
									{1,0},//row above, same col
									{1,1},//row above, next col
									{1,-1},//row above, previous col
									
									{0,1},//same row, next col
									{0,-1},//same row, previous col
									
									{-1,0},//row below, same col
									{-1,1},//row below, next col
									{-1,-1}//row below, previous col
								 };
			
			for(int i = 0; i < 8; i++){
				if(colour == 'W' && cBoard->boardSquare[toRow + seperation[i][0]][toCol + seperation[i][1]].hasPiece && cBoard->boardSquare[toRow + seperation[i][0]][toCol + seperation[i][1]].occupyingPiece.symbol == 'k'){
					isLegal = false;
				}
				else if(colour == 'B' && cBoard->boardSquare[toRow + seperation[i][0]][toCol + seperation[i][1]].hasPiece && cBoard->boardSquare[toRow + seperation[i][0]][toCol + seperation[i][1]].occupyingPiece.symbol == 'K'){
					isLegal = false;
				}
			}
			
			if(cBoard->boardSquare[toRow][toCol].hasPiece && cBoard->boardSquare[toRow][toCol].occupyingPiece.colour == colour){
				isLegal = false;
			}
		}
	}
	
	if(symbol == 'B' || symbol == 'b'){//bishops
		if(abs(fromRow - toRow) == abs(fromCol - toCol)){//moving diagonally
			
			if( ((fromRow - toRow) > 0) && ((fromCol - toCol) > 0)){
				int j = fromCol -1;
				isLegal = true;
				for(int i = fromRow-1; i > toRow; i--){//moving up and left
					if(cBoard->boardSquare[i][j].hasPiece){
						isLegal = false;
				}
			}
	}
	
		else if( ((fromRow - toRow) > 0) && ((fromCol - toCol) < 0) ){
				int j = fromCol + 1;
				isLegal = true;
				for(int i = fromRow-1; i > toRow; i--){//moving up and right
					if(cBoard->boardSquare[i][j].hasPiece){
						isLegal = false;
					}
					j++;
				}
			}
			
		else if( ((fromRow - toRow) > 0) && ((fromCol - toCol) > 0) ){
				int j = fromCol - 1;
				isLegal = true;
				for(int i = fromRow-1; i > toRow; i--){//moving down and left (from the top half of the board)
					if(cBoard->boardSquare[i][j].hasPiece){
						isLegal = false;
				}
				j--;
			}
	}
	
	else if( ((fromRow - toRow) < 0) && ((fromCol - toCol) > 0) ){
				int j = fromCol - 1;
				isLegal = true;
				for(int i = fromRow+1; i < toRow; i++){//moving down and left (from the bottom half of the board)
					if(cBoard->boardSquare[i][j].hasPiece){
						isLegal = false;
				}
				j--;
			}
	}
	
		else if( ((fromRow - toRow) < 0) && ((fromCol - toCol) < 0) ){
				int j = fromCol + 1;
				isLegal = true;
				for(int i = fromRow+1; i < toRow; i++){//moving down and right
					if(cBoard->boardSquare[i][j].hasPiece){
						isLegal = false;
				}
				j++;
			}
		}
		
		if(cBoard->boardSquare[toRow][toCol].hasPiece && cBoard->boardSquare[toRow][toCol].occupyingPiece.colour == colour){
			isLegal = false;
		}
	}
}
	
	if(symbol == 'Q' || symbol == 'q'){//queens
			//rook functionality
			if(fromRow != toRow && fromCol == toCol && fromRow < toRow){//if the rows are changing but the col(s) aren't
			isLegal = true;
			for(int i = fromRow+1; i < toRow; i++){
				if(cBoard->boardSquare[i][toCol].hasPiece){//check for any pieces in between the start and end points
					isLegal = false;// if a piece is found, set isLegal to false
				}
			}
		}
		
		else if(fromRow != toRow && fromCol == toCol && fromRow > toRow){
			isLegal = true;
			for(int i = fromRow-1; i > toRow; i--){
				if(cBoard->boardSquare[i][toCol].hasPiece){
					isLegal = false;
				}
			}
		}
		
		else if(fromRow == toRow && fromCol != toCol && fromCol < toCol){//if the cols are changing but the row(s) aren't
			isLegal = true;
			for(int i = fromCol+1; i < toCol; i++){
				if(cBoard->boardSquare[toRow][i].hasPiece){
					isLegal = false;
				}
			}
		}
		
		else if(fromRow == toRow && fromCol != toCol && fromCol > toCol){
			isLegal = true;
			for(int i = fromCol-1; i > toCol; i--){
				if(cBoard->boardSquare[toRow][i].hasPiece){
					isLegal = false;
				}
			}
		}
		//bishop functionality
		if(abs(fromRow - toRow) == abs(fromCol - toCol)){//moving diagonally
			
			if( ((fromRow - toRow) > 0) && ((fromCol - toCol) > 0)){
				int j = fromCol -1;
				isLegal = true;
				for(int i = fromRow-1; i > toRow; i--){//moving up and left
					if(cBoard->boardSquare[i][j].hasPiece){
						isLegal = false;
				}
				j--;
			}
	}
	
		else if( ((fromRow - toRow) > 0) && ((fromCol - toCol) < 0) ){
				int j = fromCol + 1;
				isLegal = true;
				for(int i = fromRow-1; i > toRow; i--){//moving up and right
					if(cBoard->boardSquare[i][j].hasPiece){
						isLegal = false;
					}
					j++;
				}
			}
			
		else if( ((fromRow - toRow) > 0) && ((fromCol - toCol) > 0) ){
				int j = fromCol - 1;
				isLegal = true;
				for(int i = fromRow-1; i > toRow; i--){//moving down and left (from the top half of the board)
					if(cBoard->boardSquare[i][j].hasPiece){
						isLegal = false;
				}
				j--;
			}
	}
	
	else if( ((fromRow - toRow) < 0) && ((fromCol - toCol) > 0) ){
				int j = fromCol - 1;
				isLegal = true;
				for(int i = fromRow+1; i < toRow; i++){//moving down and left (from the bottom half of the board)
					if(cBoard->boardSquare[i][j].hasPiece){
						isLegal = false;
				}
				j--;
			}
	}
	
		else if( ((fromRow - toRow) < 0) && ((fromCol - toCol) < 0) ){
				int j = fromCol + 1;
				isLegal = true;
				for(int i = fromRow+1; i < toRow; i++){//moving down and right
					if(cBoard->boardSquare[i][j].hasPiece){
						isLegal = false;
				}
				j++;
			}
		}
	}
		if(cBoard->boardSquare[toRow][toCol].hasPiece && cBoard->boardSquare[toRow][toCol].occupyingPiece.colour == colour){//can't capture your own piece
			isLegal = false;
		}
	}
	
	return isLegal;
}
