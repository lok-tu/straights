#include "card.h"

Card::Card(char value, char suit, int score)
	: value{value},
	  suit{suit},
	  score{score}
{}

void Card::print() {
	std::cout << value << suit;
}
