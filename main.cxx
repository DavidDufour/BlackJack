#include <iostream>
#include <string>

#include "BlackJack.hxx"

using namespace std;

void clearScreen()
{
  cout << "\033[2J";
  cout << "\033[0;0H";
}

int main(int argc, char* argv[])
{
	//if argv[1] == "debug", set debug = true, if debug cin >> card instead of card from deck
	bool debug = false;
	if(argc > 1 && string(argv[1]) == "debug")
		debug = true;

	unsigned int numberOfDecks = 0;
	unsigned int minimumBet = 0;
	
	//Get the number of decks, must be between 1 and 8
	while(numberOfDecks < 1 || numberOfDecks > 8)
	{
		clearScreen();
		cout << "Please enter the number of decks to be played with: ";
		if(!(cin >> numberOfDecks))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
	//Get the minimum bet, must be between 1 and 100
	while(minimumBet < 1 || minimumBet > 100)
	{
		clearScreen();
		cout << "Please enter the minimum bet in chips for this game: ";
		if(!(cin >> minimumBet))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}

	//Create and play blackjack game
	BlackJack game(numberOfDecks, minimumBet, debug);
	game.play();

	cout << "Thank you for playing, please gamble responsibly." << endl;

	return 0;
}
