#include <iostream>
#include <string>
#ifndef CARD_H
#define CARD_H

namespace warCardGame{
	class Card{
		public:

			Card(int val, int s);
			int getRank();
			std::string getSuit();
			std::string toString();

			friend bool operator==(const Card& left, const Card& right);
			friend bool operator>(const Card& left, const Card& right);
			friend bool operator<(const Card& left, const Card& right);

		private:

			int rank;
			std::string suit;

	};

}

#endif