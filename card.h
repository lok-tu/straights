#ifndef __CARD_H__
#define __CARD_H__

#include <iostream>

class Card {
	public:
	char value;
	char suit;
	int score;
	Card(char value, char suit, int score);

	void print();	
};

#endif
