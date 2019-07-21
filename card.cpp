#include "card.h"
#include <iostream>
#include <string>
#include <cassert>

namespace warCardGame{

	Card::Card(int val, int s){
		assert(val >= 2 && val <= 14); //from 2 to Ace
		assert(s >= 0 && s <= 3); //four values for suits
		rank = val;
		switch(s){
			case 0: suit = "Spades"; break;
			case 1: suit = "Diamonds"; break;
			case 2: suit = "Clubs"; break;
			case 3: suit = "Hearts"; break;
		}
	}

	int Card::getRank(){
		return rank;
	}

	std::string Card::getSuit(){
		return suit;
	}

	std::string Card::toString(){
		std::string val;

		switch(getRank()){
			case 11: val = "Jack"; break;
			case 12: val = "Queen"; break;
			case 13: val = "King"; break;
			case 14: val = "Ace"; break;
			default: val = std::to_string(getRank()); break;
		}

		return val + " of " + getSuit();
	}

	bool operator==(const Card& left, const Card& right){
		return(left.rank == right.rank);
	}

	bool operator<(const Card& left, const Card& right){
		return(left.rank < right.rank);
	}

	bool operator>(const Card& left, const Card& right){
		return(left.rank > right.rank);
	}

}





/*


 -----------
 | 5       |
 |         |
 |   <3    |
 |         |
 |       5 |
-------------




*/