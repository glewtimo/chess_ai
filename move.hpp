/**********************************************************************************
 * Program name: move.hpp
 * Author:       Tim Glew
 * Date:         12/19/2019
 * Desription:   This is the declaration of the class Move which represents one
 *				 game move made by a player.
 *               See below for member variables and member functions.
 *********************************************************************************/

#ifndef MOVE_HPP
#define MOVE_HPP

/* Forward Declarations */
class Player;
class Square;
class Piece;

class Move {
    private:
        Player* player;
        Square* start;
        Square* end;
        Piece* pieceMoved;
        Piece* pieceKilled;

    public:
        Move(Player*, Square*, Square*);
        Square* getStart();
        Square* getEnd();
        void setPieceKilled(Piece*);
};


#endif
