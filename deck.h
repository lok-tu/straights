#ifndef __DECK_H__
#define __DECK_H__

#include <memory>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include <string>
#include "card.h"

class Card;

class Deck {
	public:
	std::vector<std::shared_ptr<Card>> allCards;
	unsigned seed;

	Deck(unsigned seed);
	void shuffle();
	void print();
};

#endif
