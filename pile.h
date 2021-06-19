#ifndef __PILE_H__
#define __PILE_H__

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include "card.h"

class Card;

class Pile {
	public:
	std::vector<std::shared_ptr<Card>> playedCards;
	char suit;
	int max;
	int min;

	Pile(char suit);
	private:	
	struct cardCompare {
		bool operator()(std::shared_ptr<Card> &a, std::shared_ptr<Card> &b) { return (a->score < b->score);}
	};
	public:
	void sortPile();
	void print();
	void reset();
};

#endif
