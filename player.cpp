/**********************************************************************************
 * Program name: player.cpp
 * Author:       Tim Glew
 * Date:         12/19/2019
 * Desription:   This is the implementation of the class Player which represents a
 *				 player (human or computer) who is playing chess.
 *               See below for implementation source code.
 *********************************************************************************/

#include "player.hpp"
#include "helpers.hpp"
#include "board.hpp"
#include "pieces.hpp"
#include "square.hpp"
#include "game.hpp"
#include <iostream>
#include <string>
#include <cstdlib>

using std::cout;
using std::cin;


 /**********************************************************************************
  ************************* SECTION: Player (Parent Class) *************************
  **********************************************************************************/

bool Player::isWhite() {
    return white;
}

bool Player::isHuman() {
    return human;
}

void Player::setWhite(bool isWhite) {
    white = isWhite;
}

void Player::setHuman(bool isHuman) {
    human = isHuman;
}


/**********************************************************************************
 ************************* SECTION: Children of Player ****************************
 **********************************************************************************/
Human::Human(bool isWhite) {
    setWhite(isWhite);
    setHuman(true);
}

void Human::getMove(int& startRow, int& endRow, char& startCol, char& endCol, Board* board, Game* game) {
    cout << "Which piece would you like to move (e.g. a (enter) 4)?\n";
    cin >> startCol;
    startCol = inputColConverter(startCol);
    cin >> startRow;
    startRow = inputRowConverter(startRow);
    cout << "Where would you like to move it (e.g. b (enter) 6)?\n";
    cin >> endCol;
    endCol = inputColConverter(endCol);
    cin >> endRow;
    endRow = inputRowConverter(endRow);
}

Computer::Computer(bool isWhite) {
    setWhite(isWhite);
    setHuman(false);
}

void Computer::getMove(int& startRow, int& endRow, char& startCol, char& endCol, Board* board, Game* game) {
    int rows[50];
    int cols[50];
    int numMoves;
    Piece* sourcePiece = nullptr;
    Piece* destPiece = nullptr;
    Square* sourceSquare = nullptr;
    Square* destSquare = nullptr;
    int maxValue = -300000; //Track board values
    int currValue; //Track value of a single move
    /* Check max board state produced by moving each piece */
    for (int i = 0; i < 16; i++) {
        //Select piece
        sourcePiece = board->getBlackPiece(i);

        //If it is not dead
        if (!sourcePiece->isDead()) {
            //Grab all potential moves
            sourcePiece->getPossibleMoves(rows, cols, numMoves, board);
            //Check if each move is valid, calc score of board
            for (int j = 0; j < numMoves; j++) {
                sourceSquare = board->getSquare(sourcePiece->getRow(), sourcePiece->getCol());
                destSquare = board->getSquare(rows[j], cols[j]);
                destPiece = destSquare->getPiece();

                //Check if piece was moved onto a piece of the same color
                if (destPiece == nullptr || sourcePiece->isWhite() != destPiece->isWhite()) {

                    if (sourcePiece->validMove(board, sourceSquare, destSquare)) {
                        //Move piece from source square to destination square and clear source square
                        destSquare->setPiece(sourcePiece);
                        sourceSquare->setPiece(nullptr);

                        //Only moving black pieces so if its a king update tracker
                        if (sourcePiece->isKing()) {
                            game->setBlackKing(destSquare);
                        }

                        //Check if a piece was killed and update
                        if (destPiece != nullptr) {
                            destPiece->setDead();
                        }

                        //Calculate board value after move
                        if (game->isBlackCheck()) {
                            currValue = -300001; //if move puts black in check disallow it to be returned
                        }
                        else {
                            currValue = board->calcBoardValue();
                        }

                        //Compare board value to max of previous moves and update if greater
                        if (currValue > maxValue) {
                            maxValue = currValue;
                            startRow = sourcePiece->getRow();
                            startCol = sourcePiece->getCol();
                            endRow = destSquare->getRow();
                            endCol = destSquare->getCol();
                        }

                        //After evaluating move, return pieces to their spaces
                        //Unkill a piece if it was killed
                        if (destPiece != nullptr) {
                            destPiece->setAlive();
                        }
                        //If king was moved, update his tracker
                        if (sourcePiece->isKing()) {
                            game->setBlackKing(sourceSquare);
                        }
                        //Move pieces back to their squares
                        destSquare->setPiece(destPiece);
                        sourceSquare->setPiece(sourcePiece);
                    }
                }
            }
        }
    }
}













//OLD GETMOVE FOR CPU
/* Pick a random black piece that is alive */
//    bool foundPiece = false;
//    int randNum;
//    Piece* randPiece = NULL;
//    while (!foundPiece) {
//        randNum = rand() % 16;
//        randPiece = board->getBlackPiece(randNum);
//        if (!randPiece->isDead()) {
//            foundPiece = true;
//        }
//    }

    /* Get pieces starting location */
//    startRow = randPiece->getRow();
//    startCol = randPiece->getCol();

    /* Pick a random ending location */
//    endRow = rand() % 8;
//    endCol = rand() % 8;