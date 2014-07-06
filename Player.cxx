#include "Player.hxx"

using namespace std;

//Load default player with 100 chips
Player::Player()
  : chips(100)
{
}

//Load player with given number of chips
Player::Player(unsigned int chips)
  : chips(chips)
{
}

//Prompt user to make a bet
unsigned int Player::makeBet(unsigned int minimumBet)
{
	unsigned int bet = -1;

	cout << "Please enter the amount of chips you would like to bet this hand (you may quit by making a bet of 0 chips): ";
	//Bet must be above the minimum bet and within the number of chips they have
	while(bet < minimumBet || bet > chips)
	{
		if(!(cin >> bet))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			bet = -1;
		}

		clearScreen();

		//Betting 0 allows the user to leave the game
		if(bet == 0)
			return 0;
		else if(bet < minimumBet)
			cout << "Minimum bet is " << minimumBet << " chips, please enter bet in chips above or equal to " << minimumBet << ": ";
		else if(bet > chips)
			cout << "Insufficient chips, please enter bet in chips below or equal to " << chips << ": ";
	}

	//Remove bet from chips the player has
	chips -= bet;
	
	return bet;
}

//Double down option for player
unsigned int Player::doubleDown(unsigned int initialBet)
{
	unsigned int bet = -1;

	//Player may choose a bet between 0 and the amounter of the original bet.
	cout << "Please enter the amount of additional chips you would like to bet: ";
	if(!(cin >> bet))
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	//Prompting for legal bet
	while(bet > chips || bet > initialBet || bet < 0)
	{
		clearScreen();
		cout << "Please make a bet between 0 and " << ( initialBet < chips ? initialBet : chips) << " chips: ";
		if(!(cin >> bet))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}

	//Remove double down bet from chips
	chips -= bet;
	
	return bet;
}

//Add winnings from hand to players chips
void Player::payPlayer(unsigned int winnings)
{
	chips += winnings;
}

//Print cards in players hand
void Player::printHand() const
{
	unsigned int totalValue = 0;

	for(vector<Card*>::const_iterator i = hand.begin(); i != hand.end(); ++i)
		totalValue += (*i)->getValue();

	cout << "Player's hand with value " << (totalValue - 10*numberOfSoftAces) << ": " << endl;
	for(vector<Card*>::const_iterator i = hand.begin(); i != hand.end(); ++i)
		cout << (*i)->getRank() << " of " << (*i)->getSuit() << endl;

	cout << endl;
}

//Return amount of chips player has
unsigned int Player::getChips() const
{
	return chips;
}
