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
Square::Square(Piece* aPiece, int aX, int aY) {
	setPiece(aPiece);
	setX(aX);
	setY(aY);
}

Piece* Square::getPiece() {
	return piece;
}

int Square::getX() {
	return x;
}

int Square::getY() {
	return y;
}

void Square::setPiece(Piece* aPiece) {
	piece = aPiece;
}

void Square::setX(int aX) {
	x = aX;
}

void Square::setY(int aY) {
	y = aY;
}