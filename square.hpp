/**********************************************************************************
 * Program name: square.hpp
 * Author:       Tim Glew
 * Date:         12/18/2019
 * Desription:   This is the declarations of the class Square which represents one
 *				 square on an 8x8 game Board and can also contain a chess piece.
 *               See below for member variables and member functions.
 *********************************************************************************/

#ifndef SQUARE_HPP
#define SQUARE_HPP

#include "pieces.hpp"

class Square {
	private:
		Piece* piece;
		int x;
		int y;

	public:
		Square(Piece*, int, int);
		Piece* getPiece();
		int getX();
		int getY();
		void setPiece(Piece*);
		void setX(int);
		void setY(int);
};


#endif
