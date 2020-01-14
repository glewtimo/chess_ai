/**********************************************************************************
 * Program name: game.hpp
 * Author:       Tim Glew
 * Date:         12/19/2019
 * Desription:   This is the declaration of the class Game which represents a
 *				 game of Chess and facilitates the execution of a game.
 *               See below for member variables and member functions.
 *********************************************************************************/

#ifndef GAME_HPP
#define GAME_HPP

#include "move.hpp"
#include <list>

/* Forward Declarations */
class Player;
class Board;
class Square;

/* Game States */
enum GameState {
    ACTIVE,
    WHITE_WIN,
    BLACK_WIN,
    FORFEIT,
    STALEMATE
};

class Game {
    private:
        Player* player1;
        Player* player2;
        Player* currentTurn;
        Board* board;
        GameState gameState;
        Square* whiteKing;
        Square* blackKing;
        std::list <Move*> moves;

    public:
        Game(Player*, Player*, Board*);
        bool isActive();
        GameState getGameState();
        Board* getBoard();
        Player* getCurrentTurn();
        void setGameState(GameState);
        bool playerMove(Player*, int, int, int, int);
        bool makeMove(Player*, Move*);
        bool isWhiteCheck();
        bool isBlackCheck();
        bool isWhiteCheckmate();
        bool isBlackCheckmate();
        void printGameState();

};

#endif