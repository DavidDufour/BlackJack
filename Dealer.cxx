#include "Dealer.hxx"

using namespace std;

//Create dealer
Dealer::Dealer()
{
}

//Print dealer's hand with hidden second card
void Dealer::printHand() const
{
	cout << "Dealer's hand with value " << hand[0]->getValue() << ": " << endl;
	cout << hand[0]->getRank() << " of " << hand[0]->getSuit() << endl;
	cout << "Dealer has a card of unknown value" << endl;
	cout << endl;
}

//Show all cards in dealers hand
void Dealer::showHand() const
{
	unsigned int totalValue = 0;

	for(vector<Card*>::const_iterator i = hand.begin(); i != hand.end(); ++i)
		totalValue += (*i)->getValue();

	cout << "Dealer's hand with value " << (totalValue - 10*numberOfSoftAces) << ": " << endl;
	for(vector<Card*>::const_iterator i = hand.begin(); i != hand.end(); ++i)
		cout << (*i)->getRank() << " of " << (*i)->getSuit() << endl;

	cout << endl;
}
