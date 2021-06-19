# straights
A C++ text-based card game

Objective:
Straights is a four-player game. The objective is to get the fewest number of points among the players. The game ends when
one player accumulates 80 points or more, and the player with the lowest score is declared the winner. If the lowest score is a
tie, then all players with that score win.

Rules:
Ace is the lowest card (rank 1), while the Kind is the highest card (rank 13).

At the start of the game each player is dealt 13 cards at the beginning of each round. 
Immediately following the deal, the player with the 7 of spades goes first. This player must play the 7 of spades in the centre
of the table. After the 7 of spades, the players take turns to play cards on the table. At this point, the players must play cards
that constitute legal plays. 
The following cards are legal:
- A 7 of any suit. This card starts a new pile on the table.
- A card with the same suit and adjacent rank as another card that has already been played. It must be played on the pile
of the appropriate suit.

For example, if the 7 of spades is the only card on the table, then the legal plays are: the 7 of diamonds, the 7 of hearts,
the 7 of clubs, the 8 of spades, and the 6 of spades. Once the 8 of spades is played, the next legal plays are: the 9 of spades,
the 6 of spades, the 7 of diamonds, the 7 of hearts, and the 7 of clubs. In this way, you can add cards to either end of the suit
“pile” so long as there are no gaps.

When a player has no legal plays, they must then choose a card in their hand, and place it face down in front of them. This is a
discard. Note that if a player has at least one legal play in their hand, then they must make a legal play; they may not discard
in this case.

The round ends when all the cards have either been played or discarded. For each player, their score for the round is the sum
of all the ranks of the players discards. Jacks, Queens, and Kings count as 11, 12, and 13 points, respectively. For example, if
a player discarded an Ace, a Six, and a King, the number of points would be 1 + 6 + 13 = 20.
Each player’s game score is of the sum of their scores in each round. If no player has accumulated 80 or more points at
the end of a round, then the deck is reshuffled and another round begins.

Commands:
1. play 'card' which will play the specified card written with format 'rank''suit' e.g. "7C"
2. discard 'card' which will discard the card from your hand
3. ragequit which will replace the current player with a computer
4. quit which will terminate the program
