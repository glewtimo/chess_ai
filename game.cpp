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
#include <iostream>

using std::cout;

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

void Game::setCurrentTurn(Player* aPlayer) {
    currentTurn = aPlayer;
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

    //If piece moved is a king update tracker
    if (sourcePiece->isKing()) {
        if (player->isWhite()) {
            whiteKing = move->getEnd();
        }
        else {
            blackKing = move->getEnd();
        }
    }

    //If move leaves player's own king in check, move pieces back to original 
    //squares and return false
    if (player->isWhite()) {
        if (isWhiteCheck()) {
            move->getEnd()->setPiece(destPiece);
            move->getStart()->setPiece(sourcePiece);
            //If the source piece was the king, reset tracker
            if (sourcePiece->isKing()) {
                whiteKing = move->getStart();
            }
            free(move);
            return false;
        }
    }
    else {
        if (isBlackCheck()) {
            move->getEnd()->setPiece(destPiece);
            move->getStart()->setPiece(sourcePiece);
            //If the source piece was the king, reset tracker
            if (sourcePiece->isKing()) {
                blackKing = move->getStart();
            }
            free(move);
            return false;
        }
    }

    //Check if a piece was killed and update
    if (destPiece != nullptr) {
        destPiece->setDead();
        move->setPieceKilled(destPiece);
    }

    //Add move to list of moves
    moves.push_back(move);

    //Check if move creates checkmate or stalemate
    if (player->isWhite()) {
        isBlackCheckmate();
    }
    else {
        isWhiteCheckmate();
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
    Square* sourceSquare;
    Piece* sourcePiece;
    Square* destSquare;
    Piece* destPiece;

    //check each square to see if the piece is white and can make a valid move on the next turn
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            sourceSquare = board->getSquare(i, j);
            sourcePiece = sourceSquare->getPiece();

            //check first that a piece was selected to prevent read access violation on isWhite()
            if (sourcePiece != nullptr) {
                //check if piece is white
                if (sourcePiece->isWhite()) {
                    //if piece was selected and it's white, see if it can make any valid moves
                    for (int k = 0; k < 8; k++) {
                        for (int l = 0; l < 8; l++) {
                            destSquare = board->getSquare(k, l);
                            destPiece = destSquare->getPiece();
                            //Only proceed if proposed destination square is empty or contains a piece of the opposite color
                            if (destPiece == nullptr || sourcePiece->isWhite() != destPiece->isWhite()) {
                                if (sourcePiece->validMove(board, sourceSquare, destSquare)) {
                                    //If move is valid, move piece and see if king is still in check
                                    destSquare->setPiece(sourcePiece);
                                    sourceSquare->setPiece(nullptr);
                                    //If piece moved was king, update king location
                                    if (sourcePiece->isKing()) {
                                        whiteKing = destSquare;
                                    }
                                    //If the move takes the king out of check undo the move and return false
                                    if (!isWhiteCheck()) {
                                        sourceSquare->setPiece(sourcePiece);
                                        destSquare->setPiece(destPiece);
                                        if (sourcePiece->isKing()) {
                                            whiteKing = sourceSquare;
                                        }

                                        return false;
                                    }
                                    //If king is still in check, undo the move and continue to next iteration
                                    else {
                                        sourceSquare->setPiece(sourcePiece);
                                        destSquare->setPiece(destPiece);
                                        if (sourcePiece->isKing()) {
                                            whiteKing = sourceSquare;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    //If there are no valid moves, but the king isn't in check, stalemate, else Black wins
    if (!isWhiteCheck()) {
        setGameState(STALEMATE);
    }
    else {
        setGameState(BLACK_WIN);
    }

    //if no valid moves are found player is in checkmate, return true
    return true;
}

/** DESCRIPTION: return true if black is in checkmate else return false **/
bool Game::isBlackCheckmate() {
    Square* sourceSquare;
    Piece* sourcePiece;
    Square* destSquare;
    Piece* destPiece;

    //check each square to see if the piece is black and can make a valid move on the next turn
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            sourceSquare = board->getSquare(i, j);
            sourcePiece = sourceSquare->getPiece();

            //check first that a piece was selected to prevent read access violation on isWhite()
            if (sourcePiece != nullptr) {
                //check if piece is black
                if (!sourcePiece->isWhite()) {
                    //if piece was selected and it's black, see if it can make any valid moves
                    for (int k = 0; k < 8; k++) {
                        for (int l = 0; l < 8; l++) {
                            destSquare = board->getSquare(k, l);
                            destPiece = destSquare->getPiece();
                            //Only proceed if proposed destination square is empty or contains a piece of the opposite color
                            if (destPiece == nullptr || sourcePiece->isWhite() != destPiece->isWhite()) {
                                if (sourcePiece->validMove(board, sourceSquare, destSquare)) {
                                    //If move is valid, move piece and see if king is still in check
                                    destSquare->setPiece(sourcePiece);
                                    sourceSquare->setPiece(nullptr);
                                    //If piece moved was king, update king location
                                    if (sourcePiece->isKing()) {
                                        blackKing = destSquare;
                                    }
                                    //If the move takes the king out of check undo the move and return false
                                    if (!isBlackCheck()) {
                                        sourceSquare->setPiece(sourcePiece);
                                        destSquare->setPiece(destPiece);
                                        if (sourcePiece->isKing()) {
                                            blackKing = sourceSquare;
                                        }

                                        return false;
                                    }
                                    //If king is still in check, undo the move and continue to next iteration
                                    else {
                                        sourceSquare->setPiece(sourcePiece);
                                        destSquare->setPiece(destPiece);
                                        if (sourcePiece->isKing()) {
                                            blackKing = sourceSquare;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    //If there are no valid moves, but the king isn't in check, stalemate, else Black wins
    if (!isBlackCheck()) {
        setGameState(STALEMATE);
    }
    else {
        setGameState(WHITE_WIN);
    }

    //if no valid moves are found player is in checkmate, return true
    return true;
}


/** DESCRIPTION: prints gameState to screen **/
void Game::printGameState() {
    switch (gameState) {
    case 0: cout << "Game is active\n";
        break;
    case 1: cout << "White player wins!\n";
        break;
    case 2: cout << "Black player wins!\n";
        break;
    case 3: cout << "The game has been forfeited\n";
        break;
    case 4: cout << "Stalemate\n";
        break;
    }
}
