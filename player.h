#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <string>
#include <memory>
#include <vector>
#include <iostream>
#include "card.h"
#include "pile.h"

class Card;

class Pile;

class Player {
	public:
	int score;
	int pNumber;
	char type;
	std::vector<std::shared_ptr<Card>> hand;
	std::vector<std::shared_ptr<Card>> discard;

	Player(int pNumber, char type);
	std::shared_ptr<Card> findCard(std::string in);
	bool legalPlay(std::vector<std::shared_ptr<Pile>> suitPiles, std::shared_ptr<Card> in);
	void printLegal(std::vector<std::shared_ptr<Pile>> suitPiles);
	void discardCard(std::string in);
	std::shared_ptr<Card> playCard(std::string in);
	void printHand();
	int sumDiscard();
	void printDiscard();
	void resetPlayer();
};


#endif
