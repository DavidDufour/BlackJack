#ifndef Dealer_hxx__
#define Dealer_hxx__

#include <algorithm>
#include <vector>
#include <random>
#include <chrono>

#include "Person.hxx"
#include "Card.hxx"

using namespace std;

class Dealer: public Person
{
  public:
    Dealer();

		void printHand() const;
		void showHand() const;

  private:
};

#endif // Dealer_hxx__

