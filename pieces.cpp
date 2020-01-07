/**********************************************************************************
 * Program name: pieces.cpp
 * Author:       Tim Glew
 * Date:         12/18/2019
 * Desription:   This is the implementation of the parent class piece and children
 *               chess pieces. See below for implementation source code.
 *********************************************************************************/

#include "pieces.hpp"
#include "square.hpp"
#include "board.hpp"

#include <cmath>


/**********************************************************************************************
 ******************************** SECTION: Piece (Parent Class) *******************************
 **********************************************************************************************/

/** Description: Piece (parent class) constructor */
Piece::Piece() {
	white = false;
	dead = false;
	king = false;
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

/** Description: return true if piece is a king, else return false */
bool Piece::isKing() {
	if (king) {
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

/** Description: set a piece to be a king (false by default) */
void Piece::setKing() {
	king = true;
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
	setHasMoved(false);
}

void Pawn::setHasMoved(bool aHasMoved) {
	hasMoved = aHasMoved;
}

bool Pawn::isHasMoved() {
	return hasMoved;
}

bool Pawn::validMove(Board* board, Square* start, Square* end) {
	/* Cast piece to Pawn pointer to access Pawn member functions */
	Pawn* pawn = dynamic_cast<Pawn*>(start->getPiece());

	/* Calculate change in row and col of move */
	int row = start->getRow() - end->getRow();
	int col = start->getCol() - end->getCol();

	/* If piece is black, flip row so a positive row still indicates forward
	   movement of the piece */
	if (!pawn->isWhite()) {
		row = abs(row);
	}

	/* If piece does not move forward move is not valid */
	if (row <= 0) {
		return false;
	}

	/* If piece moves more than 2 spaces forward move is not valid */
	if (row > 2) {
		return false;
	}

	/* If piece moves more than 1 space diagonally move is not valid */
	if (abs(col) > 1) {
		return false;
	}

	/* If piece moves 1 space diagonally it must capture an opposing piece */
	if (row == 1 && abs(col) == 1 && end->getPiece() == nullptr) {
		return false;
	}

	/* If piece moves 1 space forward, destination must be empty */
	if (row == 1 && abs(col) == 0 && end->getPiece() != nullptr) {
		return false;
	}

	/* If a piece is moving diagonally it cannot move forward more than 1 space */
	if (row == 2 && abs(col) == 1) {
		return false;
	}

	/* If piece moves 2 spaces forward, it must be pawn's 1st move and the space it
	   passes through and its destination must be empty */
	if (row == 2 && abs(col) == 0) {
		//Make sure pawn hasn't moved
		if (pawn->isHasMoved()) { 
			return false;
		}

		//Check space pawn will pass through on its way to destination and return false if occupied
		int spaceCheckCol = start->getCol();
		int spaceCheckRow = start->getRow();
		if (pawn->isWhite()) {
			spaceCheckRow -= 1;
		}
		else {
			spaceCheckRow += 1;
		}
		if (board->getSquare(spaceCheckRow, spaceCheckCol)->getPiece() != nullptr) {
			return false;
		}

		//Check destination square to make sure it is not occupied
		if (end->getPiece() != nullptr) {
			return false;
		}
		else {
			//Move was pawns 1st and spaces were empty, set hasMoved to true and return true
			pawn->setHasMoved(true);
			return true;
		}
	}

	/* If pawn's first move, update hasMoved before returning true */
	if (!pawn->isHasMoved()) {
		pawn->setHasMoved(true);
	}
	return true;
}


/******************************************* King *********************************************/
King::King() {
	setSymbol('k');
	setKing();
}

bool King::validMove(Board* board, Square* start, Square* end) {
	/* Calculate change in row and col of move */
	int row = abs(start->getRow() - end->getRow());
	int col = abs(start->getCol() - end->getCol());

	/* King can move one space vertically, horizontally, or diagonally */
	if (row > 1 || col > 1) {
		return false;
	}

	return true;
}


/******************************************* Queen ********************************************/
Queen::Queen() {
	setSymbol('q');
}

bool Queen::validMove(Board* board, Square* start, Square* end) {
	/* Calculate change in row and col of move */
	int row = abs(start->getRow() - end->getRow());
	int col = abs(start->getCol() - end->getCol());

	/* If Queen doesn't move diagonally, vertically or horizontally, return false */
	if (row != col && row > 0 && col > 0) {
		return false;
	}

	return true;
}


/******************************************* Rook *********************************************/
Rook::Rook() {
	setSymbol('r');
}

bool Rook::validMove(Board* board, Square* start, Square* end) {
	int startRow = start->getRow();
	int startCol = start->getCol();
	int endRow = end->getRow();
	int endCol = end->getCol();

	/* Calculate change in row and col of move */
	int row = abs(startRow - endRow);
	int col = abs(startCol - endCol);

	/* Rook can't move both rows and columns */
	if (row > 0 && col > 0) {
		return false;
	}

	/* If rook is moving vertically make sure it doesn't hit one of its own pieces or jump
	   over an enemy piece in traveling to its final space */
	if (row > 0) {
		//If piece is moving up the board
		if (startRow - endRow > 0) {
			for (int i = startRow - 1; i > endRow; i--) {
				if (board->getSquare(i, startCol)->getPiece() != nullptr) {
					return false;
				}
			}
		}

		//If piece is moving down the board
		if (startRow - endRow < 0) {
			for (int i = startRow + 1; i < endRow; i++) {
				if (board->getSquare(i, startCol)->getPiece() != nullptr) {
					return false;
				}
			}
		}
	}

	/* If rook is moving horizontally make sure it doesn't hit one of its own pieces or jump
       over an enemy piece in traveling to its final space */
	if (col > 0) {
		//If piece is moving left
		if (startCol - endCol > 0) {
			for (int i = startCol - 1; i > endCol; i--) {
				if (board->getSquare(startRow, i)->getPiece() != nullptr) {
					return false;
				}
			}
		}

		//If piece is moving right
		if (startCol - endCol < 0) {
			for (int i = startCol + 1; i < endCol; i++) {
				if (board->getSquare(startRow, i)->getPiece() != nullptr) {
					return false;
				}
			}
		}
	}

	return true;
}


/****************************************** Knight *********************************************/
Knight::Knight() {
	setSymbol('n');
}

bool Knight::validMove(Board* board, Square* start, Square* end) {
	/* Calculate change in row and col of move */
	int row = abs(start->getRow() - end->getRow());
	int col = abs(start->getCol() - end->getCol());

	/* Must move 2 spaces along row or col (and 1 in the opposite direction tested below */
	if (row != 2 && col != 2) {
		return false;
	}

	/* If knight moves 2 spaces along a row, must move 1 along column */
	if (row == 2 && col != 1) {
		return false;
	}

	/* If knight moves 2 spaces along a column, must move 1 along row */
	if (col == 2 && row != 1) {
		return false;
	}

	return true;
}


/****************************************** Bishop ********************************************/
Bishop::Bishop() {
	setSymbol('b');
}

bool Bishop::validMove(Board* board, Square* start, Square* end) {
	/* Calculate change in row and col of move */
	int row = abs(start->getRow() - end->getRow());
	int col = abs(start->getCol() - end->getCol());

	/* Bishop may only move diagonally */
	if (row != col) {
		return false;
	}

	return true;
}