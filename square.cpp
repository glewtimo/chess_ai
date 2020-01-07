/**********************************************************************************
 * Program name: square.cpp
 * Author:       Tim Glew
 * Date:         12/18/2019
 * Desription:   This is the implementation of the class Square which represents one
 *				 square on an 8x8 game Board and can also contain a chess piece. 
 *			     See below for implementation source code.
 *********************************************************************************/

#include "square.hpp"
#include "pieces.hpp"

 /** Description: Square constructor */
Square::Square(Piece* aPiece, int aRow, int aCol) {
	setPiece(aPiece);
	setRow(aRow);
	setCol(aCol);
}

Piece* Square::getPiece() {
	return piece;
}

int Square::getRow() {
	return row;
}

int Square::getCol() {
	return col;
}

void Square::setPiece(Piece* aPiece) {
	piece = aPiece;
}

void Square::setRow(int aRow) {
	row = aRow;
}

void Square::setCol(int aCol) {
	col = aCol;
}