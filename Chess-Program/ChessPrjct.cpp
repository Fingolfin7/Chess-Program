#include <iostream>
#include <string>
#include <math.h>
#include "ChessPrjct.h"

ChessBoard::ChessBoard(){
	
	turn = 1; //start with white
	
	//create the pieces
	
	for(int i = 0; i < 8; i++){//white pawns
		boardSquare[6][i].hasPiece = true;
		boardSquare[6][i].occupyingPiece.set('P', 'W');
	}
	
	//white pieces on the 1st rank
	boardSquare[7][7].occupyingPiece.set('R', 'W');//rook h1
	boardSquare[7][6].occupyingPiece.set('N', 'W');//knight g1
	boardSquare[7][5].occupyingPiece.set('B', 'W');//bishop f1
	boardSquare[7][4].occupyingPiece.set('K', 'W');//king on e1
	boardSquare[7][3].occupyingPiece.set('Q', 'W');// queen on d1
	boardSquare[7][2].occupyingPiece.set('B', 'W');//bishop c1
	boardSquare[7][1].occupyingPiece.set('N', 'W');//knight b1
	boardSquare[7][0].occupyingPiece.set('R', 'W');// rook a1
	
	for(int i = 0; i < 8; i++){
		boardSquare[7][i].hasPiece = true;
	}
	
	
	for(int i = 0; i < 8; i++){//black pawns
		boardSquare[1][i].hasPiece = true;
		boardSquare[1][i].occupyingPiece.set('p', 'B');
	}
	
	//black  pieces on the 8th rank
	boardSquare[0][7].occupyingPiece.set('r', 'B');//rook h1
	boardSquare[0][6].occupyingPiece.set('n', 'B');//knight g1
	boardSquare[0][5].occupyingPiece.set('b', 'B');//bishop f1
	boardSquare[0][4].occupyingPiece.set('k', 'B');// king on e1
	boardSquare[0][3].occupyingPiece.set('q', 'B');// queen on d1
	boardSquare[0][2].occupyingPiece.set('b', 'B');//bishop c1
	boardSquare[0][1].occupyingPiece.set('n', 'B');//knight b1
	boardSquare[0][0].occupyingPiece.set('r', 'B');// rook a1
	
	for(int i = 0; i < 8; i++){
		boardSquare[0][i].hasPiece = true;
	}
}

char ChessBoard::checkTurn(){
	char checked;
	
	if (turn % 2 == 1){
		checked = 'W';
	}
	else{
		checked = 'B';
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

			if (isInCheck()) {// is the king in check? if so, undo the last move
				boardSquare[fromRow][fromCol].occupyingPiece = boardSquare[toRow][toCol].occupyingPiece;
				boardSquare[fromRow][fromCol].hasPiece = true;

				boardSquare[toRow][toCol].occupyingPiece = temp;
				boardSquare[toRow][toCol].hasPiece = false;

				std::cout << "Illegal move! King is in Check!" << std::endl;
				std::cin.get();
			}

			else {
				if (boardSquare[toRow][toCol].occupyingPiece.symbol == 'P' && toRow == 0) {//promotion (white pawns)
					std::string promote;
					std::cout << "Promote. Enter 'Q' (white queen), 'N'(white knight), 'R'(white rook) or 'B'(white bishop) to select piece.\n>";
					std::getline(std::cin, promote);
					if (promote[0] == 'Q' || promote[0] == 'N' || promote[0] == 'R' || promote[0] == 'B') {
						boardSquare[toRow][toCol].occupyingPiece.symbol = promote[0];
					}
					else {
						boardSquare[toRow][toCol].occupyingPiece.symbol = 'Q';//default promotion
					}
				}
				if (boardSquare[toRow][toCol].occupyingPiece.symbol == 'p' && toRow == 7) {//promotion (black pawns)
					std::string promote;
					std::cout << "Promote. Enter 'q' (black queen), 'n'(black knight), 'r'(black rook) or 'b'(black bishop) to select piece.\n>";
					std::getline(std::cin, promote);
					if (promote[0] == 'q' || promote[0] == 'n' || promote[0] == 'r' || promote[0] == 'b') {
						boardSquare[toRow][toCol].occupyingPiece.symbol = promote[0];
					}
					else {
						boardSquare[toRow][toCol].occupyingPiece.symbol = 'q';//default promotion
					}
				}

				turn++;//next turn
				moveList.push_back({ fromRow, fromCol, toRow, toCol }); //adds legal move to the moveList vector
			}
			
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

bool ChessBoard::checkAfterMove(int fromRow, int fromCol, int toRow, int toCol, ChessBoard copyBoard, int currentTurn) {
	Piece temp;
	bool stillCheck = false;
	copyBoard.turn = currentTurn;

	//make move
	copyBoard.boardSquare[toRow][toCol].occupyingPiece = boardSquare[fromRow][fromCol].occupyingPiece;
	copyBoard.boardSquare[toRow][toCol].hasPiece = true;

	copyBoard.boardSquare[fromRow][fromCol].occupyingPiece = temp;
	copyBoard.boardSquare[fromRow][fromCol].hasPiece = false;

	if (copyBoard.isInCheck()) {// is the king still in check?
		stillCheck = true;
	}

	return stillCheck;
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

			int eighthRank[5][2] = {
									{1,0},//row above, same col
									{1,1},//row above, next col
									{1,-1},//row above, previous col

									{0,1},//same row, next col
									{0,-1},//same row, previous col
			};

			int firstRank[5][2] = {
									{0,1},//same row, next col
									{0,-1},//same row, previous col

									{-1,0},//row below, same col
									{-1,1},//row below, next col
									{-1,-1}//row below, previous col
			};

			int eighthFile[5][2] = {
									{1,0},//row above, same col
									{1,-1},//row above, previous col
									{0,-1},//same row, previous col

									{-1,0},//row below, same col
									{-1,-1}//row below, previous col
			};

			int firstFile[5][2] = {
									{1,0},//row above, same col
									{1,1},//row above, next col

									{0,1},//same row, next col

									{-1,0},//row below, same col
									{-1,1},//row below, next col
			};
			
			if (toRow > 0 && toRow < 7 && toCol > 0 && toCol < 7) {
				for (int i = 0; i < 8; i++) {
					if (colour == 'W' && cBoard->boardSquare[toRow + seperation[i][0]][toCol + seperation[i][1]].hasPiece && cBoard->boardSquare[toRow + seperation[i][0]][toCol + seperation[i][1]].occupyingPiece.symbol == 'k') {
						isLegal = false;
					}
					else if (colour == 'B' && cBoard->boardSquare[toRow + seperation[i][0]][toCol + seperation[i][1]].hasPiece && cBoard->boardSquare[toRow + seperation[i][0]][toCol + seperation[i][1]].occupyingPiece.symbol == 'K') {
						isLegal = false;
					}
				}
			}
			else if (toRow == 0) {//seperation checking on the 8th rank
				for (int i = 0; i < 5; i++) {
					if (colour == 'W' && cBoard->boardSquare[toRow + eighthRank[i][0]][toCol + eighthRank[i][1]].hasPiece && cBoard->boardSquare[toRow + eighthRank[i][0]][toCol + eighthRank[i][1]].occupyingPiece.symbol == 'k') {
						isLegal = false;
					}
					else if (colour == 'B' && cBoard->boardSquare[toRow + eighthRank[i][0]][toCol + eighthRank[i][1]].hasPiece && cBoard->boardSquare[toRow + eighthRank[i][0]][toCol + eighthRank[i][1]].occupyingPiece.symbol =='K') {
						isLegal = false;
					}
				}
			}
			else if (toRow == 7) {//seperation checking on the 1st rank
				for (int i = 0; i < 5; i++) {
					if (colour == 'W' && cBoard->boardSquare[toRow + firstRank[i][0]][toCol + firstRank[i][1]].hasPiece && cBoard->boardSquare[toRow + firstRank[i][0]][toCol + firstRank[i][1]].occupyingPiece.symbol == 'k') {
						isLegal = false;
					}
					else if (colour == 'B' && cBoard->boardSquare[toRow + firstRank[i][0]][toCol + firstRank[i][1]].hasPiece && cBoard->boardSquare[toRow + firstRank[i][0]][toCol + firstRank[i][1]].occupyingPiece.symbol == 'K') {
						isLegal = false;
					}
				}
			}
			else if (toCol == 7) {//seperation checking on the 8th file
				for (int i = 0; i < 5; i++) {
					if (colour == 'W' && cBoard->boardSquare[toRow + eighthFile[i][0]][toCol + eighthFile[i][1]].hasPiece && cBoard->boardSquare[toRow + eighthFile[i][0]][toCol + eighthFile[i][1]].occupyingPiece.symbol == 'k') {
						isLegal = false;
					}
					else if (colour == 'B' && cBoard->boardSquare[toRow + eighthFile[i][0]][toCol + eighthFile[i][1]].hasPiece && cBoard->boardSquare[toRow + eighthFile[i][0]][toCol + eighthFile[i][1]].occupyingPiece.symbol == 'K') {
						isLegal = false;
					}
				}
			}
			
			else if (toCol == 0) {//seperation checking on the 8th file
				for (int i = 0; i < 5; i++) {
					if (colour == 'W' && cBoard->boardSquare[toRow + firstFile[i][0]][toCol + firstFile[i][1]].hasPiece && cBoard->boardSquare[toRow + firstFile[i][0]][toCol + firstFile[i][1]].occupyingPiece.symbol == 'k') {
						isLegal = false;
					}
					else if (colour == 'B' && cBoard->boardSquare[toRow + firstFile[i][0]][toCol + firstFile[i][1]].hasPiece && cBoard->boardSquare[toRow + firstFile[i][0]][toCol + firstFile[i][1]].occupyingPiece.symbol == 'K') {
						isLegal = false;
					}
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

bool ChessBoard::isInCheck() {
	char kingColour = checkTurn();
	char kingSymbol = ' ';
	int pos[2] = { 0, 0 };
	bool isInCheck = false;

	kingColour == 'W' ? kingSymbol = 'K' : kingSymbol = 'k';
	
	//get the position of the king
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (boardSquare[i][j].hasPiece && boardSquare[i][j].occupyingPiece.symbol == kingSymbol) {
				pos[0] = i;
				pos[1] = j;
			}
		}
	}

	//loop through all the pieces to see which ones can capture the king on the next move
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (boardSquare[i][j].hasPiece && boardSquare[i][j].occupyingPiece.colour != kingColour) {//only check enemy pieces
				if (boardSquare[i][j].occupyingPiece.moveIsLegal(i, j, pos[0], pos[1], this)) {//check if that piece can mover from it's position to the king
					isInCheck = true;
				}
			}
		}
	}

	return isInCheck;
}

bool ChessBoard::isInCheck(int posRow, int posCol) {
	char kingColour = checkTurn();
	char kingSymbol = ' ';
	bool isInCheck = false;

	kingColour == 'W' ? kingSymbol = 'K' : kingSymbol = 'k';

	//loop through all the pieces to see which ones can capture the king on the next move
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (boardSquare[i][j].hasPiece && boardSquare[i][j].occupyingPiece.colour != kingColour) {//only check enemy pieces
				if (boardSquare[i][j].occupyingPiece.moveIsLegal(i, j, posRow, posCol, this)) {//check if that piece can mover from it's position to the king
					isInCheck = true;
				}
			}
		}
	}

	return isInCheck;
}

bool ChessBoard::Checkmate() {
	char kingColour = checkTurn();
	bool isCheckmate = true;// if the king is in check, assume checkmate and then check if that is true later

	//make every possible move and check if the king is still in check after each of them
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (boardSquare[i][j].hasPiece) {
				for (int k = 0; k < 8; k++) {
					for (int l = 0; l < 8; l++) {
						if (boardSquare[i][j].hasPiece && boardSquare[i][j].occupyingPiece.colour == kingColour 
							&& boardSquare[i][j].occupyingPiece.moveIsLegal(i, j, k, l, this)) {
							if (checkAfterMove(i, j, k, l, *this, turn) == false) {
								isCheckmate = false;
							}
						}
					}
				}
			}
		}
	}
	

	return isCheckmate;
}

std::vector<std::array<int, 4>> ChessBoard::getPossibleMoves() {
	std::array<int, 4> move;
	std::vector<std::array<int, 4>>possibleMoves;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (boardSquare[i][j].hasPiece) {
				for (int k = 0; k < 8; k++) {
					for (int l = 0; l < 8; l++) {
						if (boardSquare[i][j].hasPiece && boardSquare[i][j].occupyingPiece.colour == checkTurn()
							&& boardSquare[i][j].occupyingPiece.moveIsLegal(i, j, k, l, this)) {
							move = { i + 1,j + 1,k + 1,l + 1 };
							possibleMoves.push_back(move);
						}
					}
				}
			}
		}
	}

	return possibleMoves;
}

void ChessBoard::recordGame() {
	time_t rawtime;
	struct tm* timeinfo;
	char buffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, sizeof(buffer), "%d-%m-%Y", timeinfo);
	std::string date(buffer);

	std::string saveFile = date + " (" + std::to_string(moveList.size()) + " moves).txt";
	std::ofstream writer(saveFile);
	if (writer.is_open()) {
		for (std::array<int, 4>gameMove : moveList) {
			writer << gameMove[0] << gameMove[1] << gameMove[2] << gameMove[3] << std::endl;
		}
	}
	else {
		std::cout << "Error! Failed to save game!" << std::endl;
		std::cin.get();
	}
}