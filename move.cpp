/**********************************************************************************
 * Program name: move.cpp
 * Author:       Tim Glew
 * Date:         12/19/2019
 * Desription:   This is the implementation of the class Move which represents one
 *				 game move made by a player.
 *               See below for implementation source code.
 *********************************************************************************/

#include "move.hpp"
#include "square.hpp"

/** DESCRIPTION: constructor for Move */
Move::Move(Player* aPlayer, Square* aStart, Square* aEnd) {
    player = aPlayer;
    start = aStart;
    end = aEnd;
    pieceMoved = aStart->getPiece();
}

Square* Move::getStart() {
    return start;
}

Square* Move::getEnd() {
    return end;
}

void Move::setPieceKilled(Piece* piece) {
    pieceKilled = piece;
}

