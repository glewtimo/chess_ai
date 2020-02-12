#include "board.hpp"
#include "pieces.hpp"
#include "square.hpp"
#include "player.hpp"
#include "move.hpp"
#include "game.hpp"
#include "helpers.hpp"
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

using std::cout;
using std::cin;

int main() {
	/* Set seed for rand */
	srand(time(NULL));

	/* Create board, players, and game */
	Board* board = new Board();
	Player* p1 = new Human(true);
	Player* p2 = new Computer(false);
	Game* game = new Game(p1, p2, board);

	/* Declare variables to be used while carrying out a turn*/
	bool validMove;
	int startRow, endRow;
	char startCol, endCol;
	std::string turn = "White"; //Initialize first turn to be white
	
	/* While game is ACTIVE carry out a turn */
	while (game->getGameState() == 0) {
		validMove = false;
		while (!validMove) {
			/*Print turn and the state of the board*/
			game->getBoard()->printBoard();
			cout << "\nIt is " << turn << "'s turn\n";

			if (turn == "White") {
				p1->getMove(startRow, endRow, startCol, endCol, game->getBoard());
			}
			else {
				p2->getMove(startRow, endRow, startCol, endCol, game->getBoard());
			}
			
			/* playerMove() carries out move and returns true if move was valid */
			validMove = game->playerMove(game->getCurrentTurn(), startRow, startCol, endRow, endCol);
			
			system("CLS");
		}

		/* Update turn after successful move */
		if (turn == "White") {
			turn = "Black";
		}
		else {
			turn = "White";
		}
	}

	game->printGameState();
}