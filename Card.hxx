#ifndef Card_hxx__
#define Card_hxx__

#include <ostream>
#include <string>

using namespace std;

class Card
{
  public:
    Card();
    Card(
      string suit,
			string rank,
   		unsigned int value
    );
    Card(Card const& card);
    Card& operator =(Card const& card);

    unsigned int const& getValue() const;
    string const& getSuit() const;
    string const& getRank() const;
		bool isAce() const;

  private:
		string suit;
		string rank;
    unsigned int value;
};

// Comparison...
bool operator ==(Card const& a, Card const& b);
bool operator !=(Card const& a, Card const& b);
bool operator <(Card const& a, Card const& b);
bool operator <=(Card const& a, Card const& b);
bool operator >(Card const& a, Card const& b);
bool operator >=(Card const& a, Card const& b);

// Determine total of two cards
unsigned int operator +(Card const& a, Card const& b);

// Read/Write Card...
std::ostream& operator <<(std::ostream& os, Card& card);

#endif // Card_hxx__

