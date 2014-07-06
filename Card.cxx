#include "Card.hxx"

using namespace std;

//Test card, ace of spades
Card::Card()
  : suit("Spades"), rank("Ace"), value(11)
{
}

//Card with suit, rank and it's corresponding value
Card::Card(string suit,	string rank, unsigned int value)
  : suit(suit), rank(rank), value(value)
{
}

//Using a cards information to make a new card
Card::Card(Card const& card)
  : suit(card.suit), rank(card.rank), value(card.value)
{
}

//Allowing a card to equal another card
Card& Card::operator =(Card const& card)
{
  this->suit = card.suit;
  this->rank = card.rank;
  this->value = card.value;
  return *this;
}

unsigned int const& Card::getValue() const
{
  return value;
}

string const& Card::getSuit() const
{
  return suit;
}

string const& Card::getRank() const
{
  return rank;
}

//Check if the card is an ace
bool Card::isAce() const
{
	return (value == 11);
}

// Comparison...
bool operator ==(Card const& a, Card const& b)
{
  return a.getValue() == b.getValue();
}

bool operator !=(Card const& a, Card const& b)
{
  return a.getValue() != b.getValue();
}

bool operator <(Card const& a, Card const& b)
{
  return a.getValue() < b.getValue();
}

bool operator <=(Card const& a, Card const& b)
{
  return a.getValue() <= b.getValue();
}

bool operator >(Card const& a, Card const& b)
{
  return a.getValue() > b.getValue();
}

bool operator >=(Card const& a, Card const& b)
{
  return a.getValue() >= b.getValue();
}

//Add two cards together, used for calculating hand values
unsigned int operator +(Card const& a, Card const& b)
{
  return a.getValue() + b.getValue();
}

//Printing out card
std::ostream& operator <<(std::ostream& os, Card& card)
{
  std::ios::fmtflags save = os.flags();
  os << card.getRank() << " of " << card.getSuit();
  os.flags(save);
  return os;
}

