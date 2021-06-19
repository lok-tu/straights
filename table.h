#ifndef __TABLE_H__
#define __TABLE_H__

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include "deck.h"
#include "pile.h"
#include "player.h"

class Deck;

class Pile;

class Table {
	public:
	int currPlayer;
	int cardsPlayed;
	std::vector<std::shared_ptr<Pile>> suitPiles;
	std::unique_ptr<Deck> deck;
	std::vector<std::unique_ptr<Player>> players;

	
	Table(unsigned seed);
	void deal();
	void printDeck();
	void calcStartPlayer();
	void startGame();
	void endGame();
	void startTurn();
	void printPiles();
	void resetPiles();
	void rageQuit();
	void calcScores();
	void takeTurn(std::string cmd, std::string in);
	void autoTurn();
};

#endif
