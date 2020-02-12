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

void Human::getMove(int& startRow, int& endRow, char& startCol, char& endCol, Board* board) {
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

void Computer::getMove(int& startRow, int& endRow, char& startCol, char& endCol, Board* board) {
    /* Pick a random black piece that is alive */
    bool foundPiece = false;
    int randNum;
    Piece* randPiece = NULL;
    while (!foundPiece) {
        randNum = rand() % 16;
        randPiece = board->getBlackPiece(randNum);
        if (!randPiece->isDead()) {
            foundPiece = true;
        }
    }
    
    /* Get pieces starting location */
    startRow = randPiece->getRow();
    startCol = randPiece->getCol();

    /* Pick a random ending location */
    endRow = rand() % 8;
    endCol = rand() % 8;
}