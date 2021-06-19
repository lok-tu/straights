#include "table.h"

Table::Table(unsigned seed) 
	: currPlayer{0},
	  cardsPlayed{0}
{
	deck = std::make_unique<Deck>(seed);

	suitPiles.emplace_back(new Pile('C'));
	suitPiles.emplace_back(new Pile('D'));
	suitPiles.emplace_back(new Pile('H'));
	suitPiles.emplace_back(new Pile('S'));
	
	char temp;
	for (int i = 1; i <= 4; i++) {
		std::cout << "Is Player" << i << " a human (h) or a computer (c)?" << std::endl;
		std::cin >> temp;
		players.emplace_back(new Player(i, temp));
	}
}

void Table::deal() {
	auto iter = deck->allCards.begin();
	for (auto it = players.begin(); it != players.end(); it++) {
		for (int i = 0; i < 13; i++) {
			(*it)->hand.push_back(*iter);
			iter++;
		}
	}
}

void Table::printDeck() {
	deck->print();
}

void Table::calcStartPlayer() {
	for (auto it = players.begin(); it != players.end(); it++) {
		if ((*it)->findCard("7S") != nullptr) {
			currPlayer = (*it)->pNumber;
		}
	}
}

void Table::startTurn() {
	std::cout << "------------------------------------------------" << std::endl;
	std::cout << "Cards on the table:" << std::endl;
	printPiles();
	auto it = players.begin() + (currPlayer-1);
	(*it)->printHand();
	(*it)->printLegal(suitPiles);

	if ((*it)->type == 'c') {
		autoTurn();
	}
}

void Table::startGame() {
	std::cout << "------------------------------------------------" << std::endl;
	deck->shuffle();
	deal();
	calcStartPlayer();
	std::cout << "A new round begins. It's Player" << currPlayer << "'s turn to play." << std::endl;
	startTurn();
}

void Table::endGame() {
	resetPiles();
	suitPiles.erase(suitPiles.begin(), suitPiles.end());
	for (auto it = players.begin(); it != players.end(); it++) {
		(*it)->resetPlayer();
	}
	players.erase(players.begin(), players.end());
	deck->allCards.erase(deck->allCards.begin(), deck->allCards.end());
}

void Table::printPiles() {
	for (auto it = suitPiles.begin(); it != suitPiles.end(); it++) {
		(*it)->print();
	}
}

void Table::resetPiles() {
	for (auto it = suitPiles.begin(); it != suitPiles.end(); it++) {
		(*it)->reset();
	}
}

void Table::rageQuit() {
	std::cout << "Player" << currPlayer << " ragequits. A computer will now take over." << std::endl;
	auto it = players.begin() + (currPlayer-1);
	(*it)->type = 'c';
	autoTurn();
}

void Table::calcScores() {
	int newScore = 0;
	bool end = false;
	int min = 80;
	std::vector<int> winners;
	std::cout << "------------------------------------------------" << std::endl;
	for (auto it = players.begin(); it != players.end(); it++) {
		newScore = (*it)->sumDiscard();
		(*it)->printDiscard();
		std::cout << "Player" << (*it)->pNumber << "'s score: ";
		std::cout << (*it)->score << " + " << newScore << " = ";
		(*it)->score = (*it)->score + newScore;
		if ((*it)->score >= 80) {
			end = true;
		}
		std::cout << (*it)->score << std::endl;
		(*it)->resetPlayer();
	}

	if (end) {
		for (auto it = players.begin(); it != players.end(); it++) {
			if ((*it)->score < min) {
				min = (*it)->score;
			}		
		}

		for (auto it = players.begin(); it != players.end(); it++) {
			if ((*it)->score == min) {
				winners.push_back((*it)->pNumber);
			}
		}

		for (auto it = winners.begin(); it != winners.end(); it++) {
			std::cout << "Player" << (*it) << " wins!" << std::endl;
		}

		endGame();
	}
	else {
		cardsPlayed = 0;
		resetPiles();
		startGame();
	}
}

void Table::takeTurn(std::string cmd, std::string in) {
	auto cPlayer = players.begin() + (currPlayer-1);
	if (cmd == "play") {
		auto currCard = (*cPlayer)->playCard(in);
		if ((*cPlayer)->legalPlay(suitPiles, currCard)) {
			for (auto it = suitPiles.begin(); it != suitPiles.end(); it++) {
				if ((*it)->suit == currCard->suit) {
					if (currCard->score > (*it)->max || (*it)->max == -1) {
						(*it)->max = currCard->score;
					}
					if (currCard->score < (*it)->min || (*it)->min == -1) {
						(*it)->min = currCard->score;
					}
					std::cout << "Player" << currPlayer << " plays ";
					currCard->print();
					std::cout << "." << std::endl;
					(*it)->playedCards.push_back(currCard);
					(*it)->sortPile();
				}
			}

			cardsPlayed++;
			if (currPlayer == 4) {
				currPlayer = 1;
			}
			else {
				currPlayer++;
			}

			if (cardsPlayed == 52) {
				calcScores();
			}
			else {
				startTurn();
			}
		}
		else {
			std::cout << "This is not a legal play." << std::endl;
		}
	}
	else {
		bool canPlay = false;
		for (auto it = (*cPlayer)->hand.begin(); it != (*cPlayer)->hand.end(); it++) {
			if ((*cPlayer)->legalPlay(suitPiles, (*it))) {
				canPlay = true;
			}
		}

		if (canPlay) {
			std::cout << "You have a legal play. You may not discard." << std::endl;
		}
		else {
			(*cPlayer)->discardCard(in);

			cardsPlayed++;
			if (currPlayer == 4) {
				currPlayer = 1;
			}
			else {
				currPlayer++;
			}

			if (cardsPlayed == 52) {
				calcScores();
			}
			else {
				startTurn();
			}
		}
	}
}

void Table::autoTurn() {
	bool canPlay = false;
	std::string in = "AA";
	auto cPlayer = players.begin() + (currPlayer-1); 
	for (auto it = (*cPlayer)->hand.begin(); it != (*cPlayer)->hand.end(); it++) {
		if ((*cPlayer)->legalPlay(suitPiles, (*it))) {
			canPlay = true;
			in[0] = (*it)->value;
			in[1] = (*it)->suit;
			break;
		}
	}
	
	if (cardsPlayed == 0) {
		auto currCard = (*cPlayer)->playCard("7S");
		for (auto it = suitPiles.begin(); it != suitPiles.end(); it++) {
			if ((*it)->suit == currCard->suit) {
				if (currCard->score > (*it)->max || (*it)->max == -1) {
					(*it)->max = currCard->score;
				}
				if (currCard->score < (*it)->min || (*it)->min == -1) {
					(*it)->min = currCard->score;
				}
				std::cout << "Player" << currPlayer << " plays ";
				currCard->print();
				std::cout << "." << std::endl;
				(*it)->playedCards.push_back(currCard);
				(*it)->sortPile();
			}
		}
	}
	else if (canPlay) {
		auto currCard = (*cPlayer)->playCard(in);
		for (auto it = suitPiles.begin(); it != suitPiles.end(); it++) {
			if ((*it)->suit == currCard->suit) {
				if (currCard->score > (*it)->max || (*it)->max == -1) {
					(*it)->max = currCard->score;
				}
				if (currCard->score < (*it)->min || (*it)->min == -1) {
					(*it)->min = currCard->score;
				}
				
				std::cout << "Player" << currPlayer << " plays ";
				currCard->print();
				std::cout << "." << std::endl;
				(*it)->playedCards.push_back(currCard);
				(*it)->sortPile();
			}
		}
	}
	else {
		auto currCard = (*cPlayer)->hand.begin();
		in[0] = (*currCard)->value;
		in[1] = (*currCard)->suit;
		(*cPlayer)->discardCard(in);
	}
	
	cardsPlayed++;
	if (currPlayer == 4) {
		currPlayer = 1;
	}
	else {
		currPlayer++;
	}

	if (cardsPlayed == 52) {
		calcScores();
	}
	else {
		startTurn();
	}
}




















