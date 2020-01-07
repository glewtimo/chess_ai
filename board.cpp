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
#include <iostream>

using std::cout;

/** Description: Board constructor */
Board::Board() {
	resetBoard();
}

/** Description: resets board to opening configuration */
void Board::resetBoard() {
	//Place black pieces
	grid[0][0] = new Square(new Rook(), 0, 0);
	grid[0][1] = new Square(new Knight(), 0, 1);
	grid[0][2] = new Square(new Bishop(), 0, 2);
	grid[0][3] = new Square(new King(), 0, 3);
	grid[0][4] = new Square(new Queen(), 0, 4);
	grid[0][5] = new Square(new Bishop(), 0, 5);
	grid[0][6] = new Square(new Knight(), 0, 6);
	grid[0][7] = new Square(new Rook(), 0, 7);
	for (int i = 1; i < 2; i++) {
		for (int j = 0; j < 8; j++) {
			grid[i][j] = new Square(new Pawn(), i, j);
		}
	}

	//Place white pieces
	Piece* rook = new Rook();
	rook->setWhite();
	Piece* knight = new Knight();
	knight->setWhite();
	Piece* bishop = new Bishop();
	bishop->setWhite();
	Piece* king = new King();
	king->setWhite();
	Piece* queen = new Queen();
	queen->setWhite();
	Piece* rook2 = new Rook();
	rook2->setWhite();
	Piece* knight2 = new Knight();
	knight2->setWhite();
	Piece* bishop2 = new Bishop();
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
			Pawn* temp = new Pawn();
			temp->setWhite(); 
			grid[i][j] = new Square(temp, i, j);
		}
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
		cout << i + 1 << " ";
		for (int j = 0; j < 8; j++) {
			cout << "|";
			if (getSquare(i, j)->getPiece() != nullptr) {
				cout << " " << getSquare(i, j)->getPiece()->getSymbol() << " ";
			}
			else {
				cout << "   ";
			}
		}
		cout << "| " << i+1;
		cout << "\n";
	}
	cout << "  ---------------------------------\n";
	cout << "    a   b   c   d   e   f   g   h\n";

}