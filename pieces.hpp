/**********************************************************************************
 * Program name: pieces.hpp
 * Author:       Tim Glew
 * Date:         12/18/2019
 * Desription:   This is the declaration of the parent class piece and children
 *               chess pieces. See below for member variables and member functions.
 *********************************************************************************/

#ifndef PIECES_HPP
#define PIECES_HPP

//Forward declarations of Board and Square classes
class Board;
class Square;

class Piece {
	protected:
		bool white;
		bool dead;
		char symbol;

	public:
		Piece();
		bool isWhite();
		bool isDead();
		char getSymbol();
		void setWhite();
		void setDead();
		void setSymbol(char);
		virtual bool validMove(Board*, Square*, Square*) = 0;
};

class Pawn : public Piece {
	public:
		Pawn();
		bool validMove(Board*, Square*, Square*);
};

class King : public Piece {
	public:
		King();
		bool validMove(Board*, Square*, Square*);
};

class Queen : public Piece {
	public:
		Queen();
		bool validMove(Board*, Square*, Square*);
};

class Rook : public Piece {
	public:
		Rook();
		bool validMove(Board*, Square*, Square*);
};

class Knight : public Piece {
	public:
		Knight();
		bool validMove(Board*, Square*, Square*);
};

class Bishop : public Piece {
	public:
		Bishop();
		bool validMove(Board*, Square*, Square*);
};


#endif