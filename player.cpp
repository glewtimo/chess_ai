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

void Human::getMove(int& startRow, int& endRow, char& startCol, char& endCol) {
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

void Computer::getMove(int& startRow, int& endRow, char& startCol, char& endCol) {
    /* Generate random move input*/
    startRow = rand() % 8 + 1;
    endRow = rand() % 8 + 1;
    startCol = rand() % 8 + 97;
    endCol = rand() % 8 + 97;

    /* Convert input as if it was human entered */
    startCol = inputColConverter(startCol);
    startRow = inputRowConverter(startRow);
    endCol = inputColConverter(endCol);
    endRow = inputRowConverter(endRow);
}