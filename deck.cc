#include "deck.h"

Deck::Deck (unsigned seed) : seed{seed} {
	char currSuit = 'C';
	for (int i = 0; i < 4; i++) {
		if (i == 1) {
			currSuit = 'D';
		}
		else if (i == 2) {
			currSuit = 'H';
		}
		else if (i == 3) {
			currSuit = 'S';
		}
		allCards.emplace_back(new Card('A',currSuit,1));
		for (int j = 2; j < 10; j++) {
			allCards.emplace_back(new Card('0'+j,currSuit,j));
		}
		allCards.emplace_back(new Card('T',currSuit,10));
		allCards.emplace_back(new Card('J',currSuit,11));
		allCards.emplace_back(new Card('Q',currSuit,12));
		allCards.emplace_back(new Card('K',currSuit,13));
	}
}

void Deck::shuffle() {
	std::default_random_engine rng{seed};
	std::shuffle(allCards.begin(), allCards.end(), rng);
}

void Deck::print() {
	auto it = allCards.begin();
	for (int i = 0; i < 4; i++) {
		(*it)->print();
		it++;
		for (int j = 0; j < 12; j++) {
			std::cout << " ";
			(*it)->print();
			it++;
		}	
		std::cout << std::endl;
	}
}
