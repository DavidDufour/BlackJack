//use deal card to read from cin next card when in debug mode and then have cin also read player input from the same file

#include "BlackJack.hxx"

using namespace std;

//Default blackjack game wth 2 decks and a minimum bet of 1
BlackJack::BlackJack()
{
	BlackJack(2, 1, false);
}

//Create blackjack game with a shoe filled with 52 cards from each deck
BlackJack::BlackJack(unsigned int numberOfDecks, unsigned int minimumBet, bool debug)
  : numberOfDecks(numberOfDecks), minimumBet(minimumBet), debug(debug)
{
	if(debug)
	{
		unsigned int numberOfCards;
		cin >> numberOfCards;

		string suit, rank;
		unsigned int value;

		for(unsigned int i = 0; i < numberOfCards; ++i)
		{
			cin >> suit >> rank >> value;
			shoe.push_back(Card(suit, rank, value));
		}
	}
	else
	{
		vector<string> suits{"Spades", "Hearts", "Clubs", "Diamonds"};
		vector<string> ranks{"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
		vector<unsigned int> values{2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};
		for(unsigned int d = 0; d < numberOfDecks; ++d)
			for(unsigned int s = 0; s < 4; ++s)
				for(unsigned int r = 0; r < 13; ++r)
					shoe.push_back(Card(suits[s],ranks[r],values[r]));
	}
}

//Game loop
void BlackJack::play()
{
	clearScreen();

	//Create player and dealer
	player = Player();	
	cout << "Player starts with " << player.getChips() << " chips." << endl << endl;
	dealer = Dealer();

	//Shuffle the shoe and point to the top card
	if(!debug)
		shuffleShoe(shoe.begin(), shoe.end());
	
	topCard = shoe.begin();
	discardEnd = topCard;
	
	//While the player still has enough chips to make the minimum bet
	while(player.getChips() > minimumBet)
	{
		//If less than 25% of the cards are left or the deck ran out of cards last hand, shuffle the deck
		if(distance(topCard, shoe.end()) < 0.25*numberOfDecks*52
		   || distance(topCard, discardEnd) > 0)
		{
			if(!debug)
			{
				shuffleShoe(shoe.begin(), shoe.end());
				topCard = shoe.begin();
			}
		}
		discardEnd = topCard;

		//Prompt player to make a bet
		bet = player.makeBet(minimumBet);
		
		//Player leaves the game when a bet of 0 chips is made
		if(bet == 0)
		{
			cout << "Player decides to walk away with " << player.getChips() << " chips." << endl << endl;
			return;
		}

		player.resetAces();
		dealer.resetAces();
		//Deal two cards to the dealer and the player
		for(int i = 0; i < 2; ++i)
		{
			if(!dealCard(&player)) return;
			if(!dealCard(&dealer)) return;
		}

		//Checking for player decision between 1 and 4
		decision = 0;
		while(decision < 1 || decision > 4)
		{
			clearScreen();

			//Display the hands to the user
			player.printHand();
			dealer.printHand();

			//If the player has a blackjack but the dealer doesn't
			if(player.handValue() == 21 && dealer.handValue() != 21)
			{
				//Pay the player 3:2
				player.payPlayer(floor(2.5*(double)bet));
				cout << "Blackjack! Player recieves " << floor(2.5*(double)bet) << " chips and now has " << player.getChips() << " chips." << endl;
				break;
			}
			//If both the dealer and the player have blackjack
			else if(player.handValue() == 21 && dealer.handValue() == 21)
			{
				clearScreen();

				player.printHand();
				dealer.showHand();

				//Return players bet
				player.payPlayer(bet);
				cout << "Blackjack! Player has tied the dealer and now has " << player.getChips() << " chips." << endl;
				break;
			}
			//If dealer has blackjack and the player doesn't
			else if(player.handValue() != 21 && dealer.handValue() == 21)
			{
				clearScreen();

				player.printHand();
				dealer.showHand();

				cout << "The dealer has hit a blackjack! Player loses and now has " << player.getChips() << " chips." << endl;
				break;
			}

			//If no blackjacks occurred, prompt the user for action
			cout << "What would you like to do? Please enter a number corresponding to an action." << endl;
			cout << "(1) Hit" << endl;
			cout << "(2) Stand" << endl;
			cout << "(3) Double down" << endl;
			cout << "(4) Surrender" << endl;
			if(!(cin >> decision))
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		}

		switch(decision)
		{
			//Player hit's
			case 1: decision = 0;
							while(decision != 2)
							{
								//Deal a card o the player
								if(!dealCard(&player)) return;
								
								if(player.handValue() < 21)
								{
									//Get decision on whether to hit or stand
									while(decision < 1 || decision > 2)
									{
										clearScreen();
										player.printHand();
										dealer.printHand();

										cout << "What would you like to do? Please enter a number corresponding to an action." << endl;
										cout << "(1) Hit" << endl;
										cout << "(2) Stand" << endl;
										if(!(cin >> decision))
										{
											cin.clear();
											cin.ignore(numeric_limits<streamsize>::max(), '\n');
										}
									}
								}

								//Leave the hit loop on stand or bust
								if((decision == 2) || (player.handValue() >= 21))
									break;
								
								decision = 0;
							}
			//Player stands (possibly after hitting)
			case 2: clearScreen();
							player.printHand();

							//Deal cards to dealer until hand total is above 16
							while(dealer.handValue() < 17)
								if(!dealCard(&dealer)) return;

							//Show resulting dealers hand
							dealer.showHand();

							//Player has busted
							if(player.handValue() > 21)
							{
								cout << "Player busts and now has " << player.getChips() << " chips." << endl;
								break;
							}
							//Player wins
							else if(player.handValue() > dealer.handValue() || dealer.handValue() > 21)
							{
								player.payPlayer(2*bet);
								cout << "Player wins and recieves " << 2*bet << " chips and now has " << player.getChips() << " chips." << endl;
								break;
							}
							//Player losers
							else if(player.handValue() < dealer.handValue())
							{
								cout << "Dealer wins and the player now has " << player.getChips() << " chips." << endl;
								break;
							}
							//Hands have same value and a tie occurs
							else
							{
								player.payPlayer(bet);
								cout << "Player has tied the dealer and stays at " << player.getChips() << " chips." << endl;
							}
							break;
			//Player double's down and increases bet
			case 3: bet += player.doubleDown(bet);
							if(!dealCard(&player)) return;

							clearScreen();
							player.printHand();
	
							//Deal cards to dealer until hand total is above 16
							while(dealer.handValue() < 17)
								if(!dealCard(&dealer)) return;

							dealer.showHand();
							if(player.handValue() > 21)
							{
								cout << "Player busts and now has " << player.getChips() << " chips." << endl;
								break;
							}
							else if(player.handValue() > dealer.handValue() || dealer.handValue() > 21)
							{
								player.payPlayer(2*bet);
								cout << "Player wins and recieves " << 2*bet << " chips and now has " << player.getChips() << " chips." << endl;
								break;
							}
							else if(player.handValue() < dealer.handValue())
							{
								cout << "Dealer wins and the player now has " << player.getChips() << " chips." << endl;
								break;
							}
							else
							{
								player.payPlayer(bet);
								cout << "Player has tied the dealer and stays at " << player.getChips() << " chips." << endl;
							}
							break;
				//Player surrenders half their bet to leave hand
				case 4: player.payPlayer(floor((double)bet/2));
								cout << "Player chooses to surrender and receives " << floor((double)bet/2) << " chips and now has " << player.getChips() << " chips." << endl;
							break;
		}
	
		player.discardHand();
		dealer.discardHand();
	}
	cout << "Player does not have enough chips to make the minimum bet of " << minimumBet << " chips." << endl;
	return;
}

//Shuffle cards in the shoe between two cards, usually the whole shoe or unused cards when cards run out midgame
void BlackJack::shuffleShoe(vector<Card>::iterator shuffleFrom, vector<Card>::iterator shuffleTo)
{
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

  shuffle(shuffleFrom, shuffleTo, std::default_random_engine(seed));

	cout << "The deck has been shuffled." << endl << endl;
}

//Deal a card from the shoe to a person
bool BlackJack::dealCard(Person* person)
{
	//If there are no cards in the shoe, shuffle discarded cards and deal from the front of the shoe
	if(topCard == shoe.end())
	{
		shuffleShoe(shoe.begin(), discardEnd);
		topCard = shoe.begin();
	}
	
	//If there are no cards in the shoe and no discarded cards left, something has gone wrong
	if((topCard+1) == discardEnd)
	{
		player.payPlayer(bet);
		cout << "The deck has run out of cards, a pit boss will be with the table shortly. Player has " << player.getChips() << " chips." << endl << endl;
		return false;
	}

	//Give card to person and point to next card in shoe
	person->addCard(&(*topCard));
	++topCard;

	//If adding the card puts the person over 21, soften an ace if it's available
	if(person->handValue() > 21)
		person->softenAce();

	return true;
}

void BlackJack::clearScreen() const
{
  cout << "\033[2J";
  cout << "\033[0;0H";
}
