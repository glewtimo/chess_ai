/**********************************************************************************
 * Program name: pieces.hpp
 * Author:       Tim Glew
 * Date:         12/18/2019
 * Desription:   This is the declaration of the parent class piece and children
 *               chess pieces. See below for member variables and member functions.
 *********************************************************************************/

#ifndef PIECES_HPP
#define PIECES_HPP

/* Forward Declarations */
class Board;
class Square;

/**********************************************************************************
 ************************* SECTION: Piece (Parent Class) **************************
 **********************************************************************************/
class Piece {
	protected:
		bool white;
		bool dead;
		bool king;
		char symbol;

	public:
		Piece();
		bool isWhite();
		bool isDead();
		bool isKing();
		char getSymbol();
		void setWhite();
		void setDead();
		void setKing();
		void setSymbol(char);
		virtual bool validMove(Board*, Square*, Square*) = 0;
};


/**********************************************************************************
 ************************* SECTION: Children of Piece *****************************
 **********************************************************************************/
class Pawn : public Piece {
	private:
		bool hasMoved;

	public:
		Pawn();
		bool isHasMoved();
		void setHasMoved(bool);
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