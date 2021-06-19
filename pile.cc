#include "pile.h"

Pile::Pile(char suit)
	 : suit{suit},
	   max{-1},
	   min{-1}
{}

void Pile::sortPile() {
	std::sort(playedCards.begin(), playedCards.end(), cardCompare());
}


void Pile::print() {
	std::string fullSuit;
	if (suit == 'C') {
		fullSuit = "Clubs";
	}
	else if (suit == 'D') {
		fullSuit = "Diamonds";
	}
	else if (suit == 'H') {
		fullSuit = "Hearts";
	}
	else {
		fullSuit = "Spades";
	}

	std::cout << fullSuit + ":";
	for (auto it = playedCards.begin(); it != playedCards.end(); it++) {
		std::cout << " " << (*it)->value;
	}
	std::cout << std::endl;
}

void Pile::reset() {
	playedCards.erase(playedCards.begin(), playedCards.end());
	max = -1;
	min = -1;
}
