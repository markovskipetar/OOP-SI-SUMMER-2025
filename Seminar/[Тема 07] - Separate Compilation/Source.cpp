#include "GamePlatform.h"

int main()
{
	Game game1("Game1", 10, true);
	Game game2("Game2", 16, true);
	Game game3("Game3", 101, false);
	Game game4("Game4", 0, true);
	Game game5("Game5", 76, true);
	Game game6("Game6", 5, true);
	Game game7("Game7", 33, false);
	Game game8("Game8", 45, false);
	Game game9("Game9", 0, true);
	Game game10("Game10", 56, true);

	GamePlatform gp;
	gp.addGame(game1);
	gp.addGame(game2);
	gp.addGame(game3);
	gp.addGame(game4);
	gp.addGame(game5);
	gp.addGame(game6);
	gp.addGame(game7);
	gp.addGame(game8);
	gp.addGame(game9);
	gp.addGame(game10);

	gp.printGames();
	gp.printGameByIndex(7);
	gp.printAllFreeGames();
	gp.printMostExpensiveGame();
	gp.printCheapestGame();

	std::cout << std::endl;

	gp.removeGame(game1);
	gp.removeGame(3);
	gp.printGames();

	gp.writeToFile("result.dat");

	GamePlatform newGp;
	newGp.readFromFile("result.dat");
	newGp.printGames();

	return 0;
}