/**********************************************************************************
 * Program name: player.hpp
 * Author:       Tim Glew
 * Date:         12/19/2019
 * Desription:   This is the declaration of the class Player which represents a
 *				 player (human or computer) who is playing chess.
 *               See below for member variables and member functions.
 *********************************************************************************/

#ifndef PLAYER_HPP
#define PLAYER_HPP

class Board;

 /**********************************************************************************
  ************************* SECTION: Player (Parent Class) *************************
  **********************************************************************************/
class Player {
    private:
        bool white;
        bool human;

    public:
        bool isWhite();
        bool isHuman();
        void setWhite(bool);
        void setHuman(bool);
        virtual void getMove(int&, int&, char&, char&, Board*) = 0;
};


/**********************************************************************************
 ************************* SECTION: Children of Player ****************************
 **********************************************************************************/
class Human: public Player {
    public:
        Human(bool);
        void getMove(int&, int&, char&, char&, Board*);
};

class Computer: public Player {
    public:
        Computer(bool);
        void getMove(int&, int&, char&, char&, Board*);
};

#endif