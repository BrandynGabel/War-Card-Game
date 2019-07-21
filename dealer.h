#include "card.h"
#include <iostream>
#include <string>
#include <deque>
#include <random>
#ifndef DEALER_H
#define DEALER_H

namespace warCardGame {

	class Dealer {

		public:

			static const int DECK_SIZE = 52;
			Dealer();
			std::deque<std::deque<Card>> dealCards();

		private:

			std::deque<Card> deck;
			unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
			std::default_random_engine randomEngine = std::default_random_engine (seed);
	
	};
	
}

#endif