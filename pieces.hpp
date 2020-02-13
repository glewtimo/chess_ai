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
		bool pawn;
		char symbol;
		int row;
		int col;
		int value;

	public:
		Piece(int, int);
		bool isWhite();
		bool isDead();
		bool isKing();
		bool isPawn();
		void setWhite();
		void setDead();
		void setAlive();
		void setKing();
		void setPawn();
		void setSymbol(char);
		void setRow(int);
		void setCol(int);
		void setValue(int);
		void invertValue();
		int getRow();
		int getCol();
		int getValue();
		char getSymbol();
		virtual bool validMove(Board*, Square*, Square*) = 0;
		virtual void getPossibleMoves(int*, int*, int&) = 0;

};


/**********************************************************************************
 ************************* SECTION: Children of Piece *****************************
 **********************************************************************************/
class Pawn : public Piece {
	private:
		bool hasMoved;

	public:
		Pawn(int, int);
		bool isHasMoved();
		void setHasMoved(bool);
		bool validMove(Board*, Square*, Square*);
		void getPossibleMoves(int*, int*, int&);
};

class King : public Piece {
	public:
		King(int, int);
		bool validMove(Board*, Square*, Square*);
		void getPossibleMoves(int*, int*, int&);
};

class Queen : public Piece {
	public:
		Queen(int, int);
		bool validMove(Board*, Square*, Square*);
		void getPossibleMoves(int*, int*, int&);
};

class Rook : public Piece {
	public:
		Rook(int, int);
		bool validMove(Board*, Square*, Square*);
		void getPossibleMoves(int*, int*, int&);
};

class Knight : public Piece {
	public:
		Knight(int, int);
		bool validMove(Board*, Square*, Square*);
		void getPossibleMoves(int*, int*, int&);
};

class Bishop : public Piece {
	public:
		Bishop(int, int);
		bool validMove(Board*, Square*, Square*);
		void getPossibleMoves(int*, int*, int&);
};


#endif