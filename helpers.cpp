/**********************************************************************************
 * Program name: helpers.cpp
 * Author:       Tim Glew
 * Date:         12/20/2019
 * Desription:   These are function implementations for functions to help carry out
 *               the logic of a game of chess.
 *********************************************************************************/

#include "helpers.hpp"

/** DESCRIPTION: returns the array index equivalent of a user input chess row */
int inputRowConverter(int aRow) {
    return aRow - 1;
}

/** DESCRIPTION: returns the array index equivalent of a user input chess col */
int inputColConverter(char aCol) {
    return aCol - 97;
}