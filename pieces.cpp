/**********************************************************************************
 * Program name: pieces.cpp
 * Author:       Tim Glew
 * Date:         12/18/2019
 * Desription:   This is the implementation of the parent class piece and children
 *               chess pieces. See below for implementation source code.
 *********************************************************************************/

#include "pieces.hpp"


/**********************************************************************************************
 ******************************** SECTION: Piece (Parent Class) *******************************
 **********************************************************************************************/

/** Description: Piece (parent class) constructor */
Piece::Piece() {
	white = false;
	dead = false;
}

/** Description: return true if piece is white, else return false */
bool Piece::isWhite() {
	if (white) {
		return true;
	}
	else {
		return false;
	}
}

/** Description: return true if piece is dead, else return false */
bool Piece::isDead() {
	if (dead) {
		return true;
	}
	else {
		return false;
	}
}

/** Description: return the piece's symbol to print to board */
char Piece::getSymbol() {
	return symbol;
}

/** Description: set a piece to white (false by default) and change its
                 symbol to uppercase*/
void Piece::setWhite() {
	white = true;
	symbol -= 32;
}

/** Description: set a piece to dead (false by default) */
void Piece::setDead() {
	dead = true;
}

void Piece::setSymbol(char aChar) {
	symbol = aChar;
}


/**********************************************************************************************
 ********************************* SECTION: Children of Piece *********************************
 **********************************************************************************************/

/******************************************* Pawn *********************************************/
Pawn::Pawn() {
	setSymbol('p');
}

bool Pawn::validMove(Board* board, Square* start, Square* end) {
	return true;
}


/******************************************* King *********************************************/
King::King() {
	setSymbol('k');
}

bool King::validMove(Board* board, Square* start, Square* end) {
	return true;
}


/******************************************* Queen ********************************************/
Queen::Queen() {
	setSymbol('q');
}

bool Queen::validMove(Board* board, Square* start, Square* end) {
	return true;
}


/******************************************* Rook *********************************************/
Rook::Rook() {
	setSymbol('r');
}

bool Rook::validMove(Board* board, Square* start, Square* end) {
	return true;
}


/****************************************** Knight *********************************************/
Knight::Knight() {
	setSymbol('n');
}

bool Knight::validMove(Board* board, Square* start, Square* end) {
	return true;
}


/****************************************** Bishop ********************************************/
Bishop::Bishop() {
	setSymbol('b');
}

bool Bishop::validMove(Board* board, Square* start, Square* end) {
	return true;
}