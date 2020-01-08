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
    whiteKing = board->getSquare(7, 4);
    blackKing = board->getSquare(0, 4);
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

    //Move piece from source square to destination square and clear source
    //square
    move->getEnd()->setPiece(sourcePiece);
    move->getStart()->setPiece(nullptr);

    //If move leaves player's own king in check, move pieces back to original 
    //squares and return false
    if (player->isWhite()) {
        if (isWhiteCheck()) {
            move->getEnd()->setPiece(destPiece);
            move->getStart()->setPiece(sourcePiece);
            free(move);
            return false;
        }
    }
    else {
        if (isBlackCheck()) {
            move->getEnd()->setPiece(destPiece);
            move->getStart()->setPiece(sourcePiece);
            free(move);
            return false;
        }
    }

    //Check if a piece was killed and update
    if (destPiece != nullptr) {
        destPiece->setDead();
        move->setPieceKilled(destPiece);
    }

    //If piece moved is a king update tracker
    if (sourcePiece->isKing()) {
        if (player->isWhite()) {
            whiteKing = move->getEnd();
        }
        else {
            blackKing = move->getEnd();
        }
    }

    //Add move to list of moves
    moves.push_back(move);

    //If move puts opponent in checkmate end game
    if (player->isWhite()) {
        if (isBlackCheckmate()) {
            setGameState(WHITE_WIN);
        }
    }
    else {
        if (isWhiteCheckmate()) {
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

/** DESCRIPTION: return true if white king is in check else return false **/
bool Game::isWhiteCheck() {
    Square* checkSquare;
    Piece* checkPiece;

    //check each square to see if the piece is black and can capture white king
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            checkSquare = board->getSquare(i, j);
            checkPiece = checkSquare->getPiece();
            //check first that a piece was selected to prevent read access violation on isWhite()
            if (checkPiece != nullptr) {
                //check if piece is black
                if (!checkPiece->isWhite()) {
                    if (checkPiece->validMove(board, checkSquare, whiteKing)) {
                        return true;
                    }
                }
            }
        }
    }
    //return false if no black pieces can capture white king
    return false;
}

/** DESCRIPTION: return true if black king is in check else return false **/
bool Game::isBlackCheck() {
    Square* checkSquare;
    Piece* checkPiece;

    //check each square to see if the piece is white and can capture black king
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            checkSquare = board->getSquare(i, j);
            checkPiece = checkSquare->getPiece();
            //check first that a piece was selected to prevent read access violation on isWhite()
            if (checkPiece != nullptr) {
                //check if piece is white
                if (checkPiece->isWhite()) {
                    if (checkPiece->validMove(board, checkSquare, blackKing)) {
                        return true;
                    }
                }
            }
        }
    }
    //return false if no white pieces can capture black king
    return false;
}

/** DESCRIPTION: return true if white is in checkmate else return false **/
bool Game::isWhiteCheckmate() {
    Square* checkSquare;
    Piece* checkPiece;

    //check each square to see if the piece is white and can make a valid move on the next turn
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            checkSquare = board->getSquare(i, j);
            checkPiece = checkSquare->getPiece();
            //check first that a piece was selected to prevent read access violation on isWhite()
            if (checkPiece != nullptr) {
                //check if piece is white
                if (checkPiece->isWhite()) {
                    //if piece was selected and it's white, see if it can make any valid moves
                    for (int k = 0; k < 8; k++) {
                        for (int l = 0; l < 8; l++) {
                            //return false is a valid move is found (player is not in checkmate)
                            if (checkPiece->validMove(board, checkSquare, board->getSquare(k,l))) {
                                if (!isWhiteCheck()) {
                                    return false;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    //if no valid moves are found player is in checkmate, return true
    return true;
}

/** DESCRIPTION: return true if black is in checkmate else return false **/
bool Game::isBlackCheckmate() {
    Square* checkSquare;
    Piece* checkPiece;

    //check each square to see if the piece is black and can make a valid move on the next turn
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            checkSquare = board->getSquare(i, j);
            checkPiece = checkSquare->getPiece();
            //check first that a piece was selected to prevent read access violation on isWhite()
            if (checkPiece != nullptr) {
                //check if piece is black
                if (!checkPiece->isWhite()) {
                    //if piece was selected and it's black, see if it can make any valid moves
                    for (int k = 0; k < 8; k++) {
                        for (int l = 0; l < 8; l++) {
                            //return false is a valid move is found (player is not in checkmate)
                            if (checkPiece->validMove(board, checkSquare, board->getSquare(k, l))) {
                                if (!isBlackCheck()) {
                                    return false;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    //if no valid moves are found player is in checkmate, return true
    return true;
}