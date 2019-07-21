#include "card.h"
#include "dealer.h"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <deque>

namespace warCardGame{
	Dealer::Dealer(){

		//create the cards and add them to the deck
		for (int i = 2; i < 15; i++) {

			deck.push_back(Card(i, 0));//spades
			deck.push_back(Card(i, 1));//diamonds
			deck.push_back(Card(i, 2));//clubs
			deck.push_back(Card(i, 3));//hearts

		}

		//shuffle the deck
		std::shuffle(deck.begin(), deck.end(), randomEngine);
		
	}







	std::deque<std::deque<Card>> Dealer::dealCards() {
									   //create two deques
		std::deque<Card> playerCards;  //one for player's cards
		std::deque<Card> cpuCards;     //a second for cpu's cards

		std::deque<std::deque<Card>> player_and_cpu; //a third deque to store both deques
		
	
		//push cards to the deques representing the player & CPU hand
		//alternating. Increment the counter after each push
		for (int i = 0; i < Dealer::DECK_SIZE; ) {

			playerCards.push_back(deck.at(i++)); //increment after each deal
			cpuCards.push_back(deck.at(i++));    //increment after each deal

		}

		cpuCards.shrink_to_fit(); //get rid of empty space
		playerCards.shrink_to_fit();
											   //add the player and cpu deques
											   //to the compound deque
		player_and_cpu.push_back(playerCards); //player's cards come first
		player_and_cpu.push_back(cpuCards);    //cpu's cards come second
		player_and_cpu.shrink_to_fit();        //get rid of empty space
		
		//return the compound deque containing both hands
		return player_and_cpu;
		
	}

}