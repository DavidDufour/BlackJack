#ifndef Player_hxx__
#define Player_hxx__

#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <chrono>

#include "Person.hxx"
#include "Card.hxx"

using namespace std;

class Player: public Person
{
  public:
    Player();
		Player(
   		unsigned int chips
    );

		unsigned int makeBet(unsigned int minimumBet);
		unsigned int doubleDown(unsigned int initialBet);
		void payPlayer(unsigned int winnings);

		void printHand() const;
		unsigned int getChips() const;

  private:
		unsigned int chips;
};

#endif // Player_hxx__

