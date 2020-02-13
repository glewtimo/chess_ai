/**********************************************************************************
 * Program name: board.cpp
 * Author:       Tim Glew
 * Date:         12/18/2019
 * Desription:   This is the implementation of the class Board which represents the
 *				 8x8 game Board made up of Squares.
 *               See below for implementation source code.
 *********************************************************************************/

#include "board.hpp"
#include "square.hpp"
#include "pieces.hpp"
#include <iostream>

using std::cout;

/** Description: Board constructor */
Board::Board() {
	resetBoard();
}

/** Description: resets board to opening configuration */
void Board::resetBoard() {
	//Place black pieces
	grid[0][0] = new Square(new Rook(0, 0), 0, 0);
	grid[0][1] = new Square(new Knight(0, 1), 0, 1);
	grid[0][2] = new Square(new Bishop(0, 2), 0, 2);
	grid[0][3] = new Square(new Queen(0, 3), 0, 3);
	grid[0][4] = new Square(new King(0, 4), 0, 4);
	grid[0][5] = new Square(new Bishop(0, 5), 0, 5);
	grid[0][6] = new Square(new Knight(0, 6), 0, 6);
	grid[0][7] = new Square(new Rook(0, 7), 0, 7);
	for (int i = 1; i < 2; i++) {
		for (int j = 0; j < 8; j++) {
			grid[i][j] = new Square(new Pawn(i, j), i, j);
		}
	}

	//Put black pieces into tracker array
	int row, col;
	for (int i = 0; i < 16; i++) {
		row = i / 8;
		col = i % 8;
		blackPieces[i] = grid[row][col]->getPiece();
	}

	//Place white pieces
	Piece* rook = new Rook(7, 0);
	rook->setWhite();
	Piece* knight = new Knight(7, 1);
	knight->setWhite();
	Piece* bishop = new Bishop(7, 2);
	bishop->setWhite();
	Piece* king = new King(7, 4);
	king->setWhite();
	Piece* queen = new Queen(7, 3);
	queen->setWhite();
	Piece* rook2 = new Rook(7, 7);
	rook2->setWhite();
	Piece* knight2 = new Knight(7, 6);
	knight2->setWhite();
	Piece* bishop2 = new Bishop(7, 5);
	bishop2->setWhite();

	grid[7][0] = new Square(rook, 7, 0);
	grid[7][1] = new Square(knight, 7, 1);
	grid[7][2] = new Square(bishop, 7, 2);
	grid[7][3] = new Square(queen, 7, 3);
	grid[7][4] = new Square(king, 7, 4);
	grid[7][5] = new Square(bishop2, 7, 5);
	grid[7][6] = new Square(knight2, 7, 6);
	grid[7][7] = new Square(rook2, 7, 7);

	for (int i = 6; i < 7; i++) {
		for (int j = 0; j < 8; j++) {
			Pawn* temp = new Pawn(i, j);
			temp->setWhite(); 
			grid[i][j] = new Square(temp, i, j);
		}
	}

	//Put white pieces into tracker array and invert their values so
	//black pieces have positive value and white have negative
	for (int i = 0; i < 16; i++) {
		row = i / 8 + 6;
		col = i % 8;
		whitePieces[i] = grid[row][col]->getPiece();
		whitePieces[i]->invertValue();
	}

	//Set remaining spaces to null
	for (int i = 2; i < 6; i++) {
		for (int j = 0; j < 8; j++) {
			grid[i][j] = new Square(nullptr, i, j);
		}
	}
}

Square* Board::getSquare(int aRow, int aCol) {
	return grid[aRow][aCol];
}

/** Description: Print current state of the board */
void Board::printBoard() {
	cout << "    a   b   c   d   e   f   g   h\n";
	for (int i = 0; i < 8; i++) {
		cout << "  ---------------------------------\n";
		cout << abs(i - 8) << " ";
		for (int j = 0; j < 8; j++) {
			cout << "|";
			if (getSquare(i, j)->getPiece() != nullptr) {
				cout << " " << getSquare(i, j)->getPiece()->getSymbol() << " ";
			}
			else {
				cout << "   ";
			}
		}
		cout << "| " << abs(i - 8);
		cout << "\n";
	}
	cout << "  ---------------------------------\n";
	cout << "    a   b   c   d   e   f   g   h\n";

}

/** Takes an int and returns the white piece at that position in the piece array */
Piece* Board::getWhitePiece(int pos) {
	return whitePieces[pos];
}

/** Takes an int and returns the black piece at that position in the piece array */
Piece* Board::getBlackPiece(int pos) {
	return blackPieces[pos];
}

/** Calculates the value of the board, positive is good for black and negative good for white */
int Board::calcBoardValue() {
	int value = 0;
	Piece* piece = NULL;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			piece = grid[i][j]->getPiece();
			if (piece != NULL && !piece->isDead()) {
				value += piece->getValue();
			}
		}
	}

	return value;
}