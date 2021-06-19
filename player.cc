#include "player.h"

Player::Player(int pNumber, char type)
	: score{0},
	  pNumber{pNumber},
	  type{type}

{}

std::shared_ptr<Card> Player::findCard(std::string in) {
	for (auto it = hand.begin(); it != hand.end(); it++) {
		if ((*it)->value == in[0] && (*it)->suit == in[1]) {
			return *it;
		}
	}
	return nullptr;
}

bool Player::legalPlay(std::vector<std::shared_ptr<Pile>> suitPiles, std::shared_ptr<Card> in) {
	if (in->score == 7) {
		return true;
	}
	for (auto it = suitPiles.begin(); it != suitPiles.end(); it++) {
		if (in->suit == (*it)->suit) {
			if (((*it)->max)+1 == in->score || ((*it)->min)-1 == in->score) {
				return true;
			}
		}
	}
	return false;
}

void Player::printLegal(std::vector<std::shared_ptr<Pile>> suitPiles) {
	std::cout << "Legal plays:";
	
	if (findCard("7S") != nullptr) {
		std::cout << " 7S" << std::endl;
	}
	else {
		for (auto it = hand.begin(); it != hand.end(); it++) {
			if (legalPlay(suitPiles, (*it))) {
				std::cout << " ";
		       	(*it)->print();
			}
		}
		std::cout << std::endl;
	}
}

void Player::discardCard(std::string in) {
	for (auto it = hand.begin(); it != hand.end(); it++) {
		if ((*it)->value == in[0] && (*it)->suit == in[1]) {
			std::cout << "Player" << pNumber << " discards ";
			(*it)->print();
			std::cout << "." << std::endl;
			discard.push_back(*it);
			hand.erase(it);
			if (hand.size() < 1) {
				break;
			}
		}
	}
}

std::shared_ptr<Card> Player::playCard(std::string in) {
	for (auto it = hand.begin(); it != hand.end(); it++) {
		if ((*it)->value == in[0] && (*it)->suit == in[1]) {
			auto temp = (*it);
			hand.erase(it);
			return temp;
		}
	}
	return nullptr;
}

void Player::printHand() {
	std::cout << "Your hand:";
	for (auto it = hand.begin(); it != hand.end(); it++) {
		std::cout << " ";
		(*it)->print();
	}
	std::cout << std::endl;
}

int Player::sumDiscard() {
	int sum = 0;
	for (auto it = discard.begin(); it != discard.end(); it++) {
		sum += (*it)->score; 
	}
	return sum;
}

void Player::printDiscard() {
	std::cout << "Player" << pNumber << "'s discards:";
	for (auto it = discard.begin(); it != discard.end(); it++) {
		std::cout << " ";
		(*it)->print();
	}
	std::cout << std::endl;
}

void Player::resetPlayer() {
	hand.erase(hand.begin(), hand.end());
	discard.erase(discard.begin(), discard.end());
}
