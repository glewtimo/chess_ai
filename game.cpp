/**********************************************************************************
 * Program name: game.cpp
 * Author:       Tim Glew
 * Date:         12/19/2019
 * Desription:   This is the implementation of the class Game which represents a
 *				 game of Chess and facilitates the execution of a game.
 *               See below for implementation source code.
 *********************************************************************************/

#include "game.hpp"
#include "player.hpp"
#include "board.hpp"
#include "square.hpp"

/* Game constructor */
Game::Game(Player* p1, Player* p2, Board* aBoard) {
    player1 = p1;
    player2 = p2;
    if (p1->isWhite()) {
        currentTurn = p1;
    }
    else {
        currentTurn = p2;
    }
    board = aBoard;
    gameState = ACTIVE;
}

bool Game::isActive() {
    if (gameState == ACTIVE) {
        return true;
    }
    else {
        return false;
    }
}

GameState Game::getGameState() {
    return gameState;
}

Board* Game::getBoard() {
    return board;
}

Player* Game::getCurrentTurn() {
    return currentTurn;
}

void Game::setGameState(GameState aGameState) {
    gameState = aGameState;
}

/** DESCRIPTION: creates a proposed move by a player and carries it out/returns
 **              true if the move is valid, else deletes the move and returns 
 **              false through call to makeMove*/
bool Game::playerMove(Player* player, int startRow, int startCol, int endRow, int endCol) {
    Square* startSquare = board->getSquare(startRow, startCol);
    Square* endSquare = board->getSquare(endRow, endCol);
    Move* move = new Move(player, startSquare, endSquare);
    return makeMove(player, move);
}

/** DESCRIPTION: if a move is valid, carry out the move, add it to list of moves 
 **              and return true, else delete the move and return false */
bool Game::makeMove(Player* player, Move* move) {
    Piece* sourcePiece = move->getStart()->getPiece();
    Piece* destPiece = move->getEnd()->getPiece();
    
    //Check that a piece was selected
    if (sourcePiece == nullptr) {
        free(move);
        return false;
    }

    //Check piece belongs to player
    if (sourcePiece->isWhite() != player->isWhite()) {
        free(move);
        return false;
    }

    //Check if piece was moved onto a piece of the same color
    if (destPiece != nullptr && sourcePiece->isWhite() == destPiece->isWhite()) {
        free(move);
        return false;
    }

    //Check if the move was valid per movement rules of a given piece
    if (!sourcePiece->validMove(board, move->getStart(), move->getEnd())) {
        free(move);
        return false;
    }

    //Check if a piece was killed and update
    if (destPiece != nullptr) {
        destPiece->setDead();
        move->setPieceKilled(destPiece);
    }

    //Add move to list of moves
    moves.push_back(move);

    //Move piece from source square to destination swuare and clear source
    //square
    move->getEnd()->setPiece(sourcePiece);
    move->getStart()->setPiece(nullptr);

    //Check to see if king was captured
    if (destPiece != nullptr && destPiece->isKing()) {
        if (player->isWhite()) {
            setGameState(WHITE_WIN);
        }
        else {
            setGameState(BLACK_WIN);
        }
    }

    //Set turn to the other player
    if (currentTurn == player1) {
        currentTurn = player2;
    }
    else {
        currentTurn = player1;
    }

    return true;
}