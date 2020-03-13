/**********************************************************************************
 * Program name: helpers.cpp
 * Author:       Tim Glew
 * Date:         12/20/2019
 * Desription:   These are function implementations for functions to help carry out
 *               the logic of a game of chess.
 *********************************************************************************/

#include "helpers.hpp"
#include <cstdlib>


/** DESCRIPTION: returns the array index equivalent of a user input chess row */
int inputRowConverter(int aRow) {
    return abs(aRow - 8);
}

/** DESCRIPTION: returns the array index equivalent of a user input chess col */
int inputColConverter(char aCol) {
    return aCol - 97;
}
