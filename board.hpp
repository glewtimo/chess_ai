/**********************************************************************************
 * Program name: board.hpp
 * Author:       Tim Glew
 * Date:         12/18/2019
 * Desription:   This is the declaration of the class Board which represents the
 *				 8x8 game Board made up of Squares.
 *               See below for member variables and member functions.
 *********************************************************************************/

#ifndef BOARD_HPP
#define BOARD_HPP

/* Forward Declaration */
class Square;
class Piece;

class Board {
	private:
		Square* grid[8][8];
		Piece* whitePieces[16];
		Piece* blackPieces[16];

	public:
		Board();
		void resetBoard();
		Square* getSquare(int, int);
		void printBoard();
		Piece* getWhitePiece(int);
		Piece* getBlackPiece(int);
		int calcBoardValue();
};


#endif 
