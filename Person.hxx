#ifndef Person_hxx__
#define Person_hxx__

#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <chrono>

#include "Card.hxx"

using namespace std;

//Abstract Person class, extended by Player and Dealer
class Person
{
  public:
		//Add card to players hand, pass in from the top of the deck
    void addCard(Card* card)
		{
			//Keep track if the added card is an ace
			if(card->isAce())
				++numberOfHardAces;
			hand.push_back(card);
		}

		//Return value of cards in hand, subtracting 10 if value is over 21 and there are available aces
		unsigned int handValue()
		{
			unsigned int handValue = 0;
			for(vector<Card*>::iterator i = hand.begin(); i != hand.end(); ++i)
				handValue += (*i)->getValue();
			return (handValue - 10*numberOfSoftAces);
		}

		//Used to remember how many hard aces are left and soft aces are used. A hard ace becomes a soft ace when a hand value of 21 is passed
		int softenAce()
		{
			if(numberOfHardAces > 0)
			{
				--numberOfHardAces;
				++numberOfSoftAces;
				return numberOfHardAces;
			}
			//return 0 if there are no aces left in the hand to be softened
			return -1;
		}

		void resetAces()
		{
			numberOfHardAces = 0;
			numberOfSoftAces = 0;
		}

		void discardHand()
		{
			hand.clear();
		}

		void clearScreen()
		{
			cout << "\033[2J";
			cout << "\033[0;0H";
		}

		virtual void printHand() const =0;

  protected:
		vector<Card*> hand;
		unsigned int numberOfHardAces;
		unsigned int numberOfSoftAces;
};

#endif // Person_hxx__

