#ifndef BlackJack_hxx__
#define BlackJack_hxx__

#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <chrono>

#include "Player.hxx"
#include "Dealer.hxx"
#include "Card.hxx"

class BlackJack
{
  public:
    BlackJack();
    BlackJack(
   		unsigned int numberOfDecks,
			unsigned int minimumBet,
			bool debug
    );

    void play();
		void shuffleShoe(vector<Card>::iterator shuffleFrom, vector<Card>::iterator shuffleTo);
		bool dealCard(Person* person);
		void clearScreen() const;

  private:
		unsigned int numberOfDecks;
		unsigned int minimumBet;

		Player player;
		Dealer dealer;

		vector<Card> shoe;
		vector<Card> discard;

		unsigned int bet;
		unsigned int decision;

		vector<Card>::iterator topCard;
		vector<Card>::iterator discardEnd;

		bool debug;
};

#endif // BlackJack_hxx__

