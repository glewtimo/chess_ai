/**********************************************************************************
 * Program name: player.cpp
 * Author:       Tim Glew
 * Date:         12/19/2019
 * Desription:   This is the implementation of the class Player which represents a
 *				 player (human or computer) who is playing chess.
 *               See below for implementation source code.
 *********************************************************************************/

#include "player.hpp"

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

Computer::Computer(bool isWhite) {
    setWhite(isWhite);
    setHuman(false);
}

