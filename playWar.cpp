#include "card.h"
#include "dealer.h"
#include <iostream>
#include <deque>

using namespace std;
using namespace warCardGame;

/*
	War Card Game

*/

const int NUMBER_OF_PLAYERS   = 2;
const int NUMBER_OF_WAR_CARDS = 3;
const int MAX_BUFFER 		  = 1024;



bool play         (deque<Card>& player, deque<Card>& cpu, deque<deque<Card>>& table);
void checkCards   (deque<Card>& player, deque<Card>& cpu, deque<deque<Card>>& table);
void war          (deque<Card>& player, deque<Card>& cpu, deque<deque<Card>>& table);
void collectCards (deque<Card>& player, deque<Card>& cpu, deque<deque<Card>>& table, bool isCPUwinner);
void displayTable (deque<deque<Card>>& table);
void clearTable   (deque<deque<Card>>& table);






int main () {
	
	Dealer dealer; //create a dealer to generate and split the deck
	deque<deque<Card>> player_and_cpu = dealer.dealCards(); //retrieve the cards

	deque<Card> player = player_and_cpu[0];
	deque<Card> cpu    = player_and_cpu[1];
	deque<deque<Card>> table(NUMBER_OF_PLAYERS); //table[0] is player's cards
							  	 				 //table[1] is cpu's cards
	
	//play the game
	if (play(player, cpu, table)) {

		cout << "\tYou Win!"  << endl << "\tThanks for playing!"    << endl;

		for (int i = 0; i < player.size(); i++) {

			cout << player[i].toString() << endl;

		}

	} else {

		cout << "\tYou Lose!" << endl << "\tBetter luck next time!" << endl;

		for (int i = 0; i < cpu.size(); i++) {

			cout << cpu[i].toString() << endl;

		}

	}

	return 0;

}






//returns true if the player has won the game, false otherwise
bool play (deque<Card>& player, deque<Card>& cpu, deque<deque<Card>>& table) {

	cout << "Player's deck size: " << player.size() << endl;
	cout << "CPU's deck size: " << cpu.size() << endl;

	if (cpu.size() < 1) return true;
	if (player.size() < 1) return false;

	cout << "\n\nPress Enter to flip card... \n\n" << endl; 
	char enter = '\0';
	enter = cin.get();

	while (enter != '\n') {

		cin.clear();
		cin.ignore(MAX_BUFFER, '\n'); //1024 is the max buffer that this program will handle
		enter = cin.get();

	}

	table[0].push_back(player[0]); //place the player's first card on the table
	player.pop_front(); 		   //remove the card the player placed

	table[1].push_back(cpu[0]);    //place the cpu's first card on the table
	cpu.pop_front();			   //remove the card the cpu played

	displayTable(table);
	checkCards(player, cpu, table);
	clearTable(table);

	return play(player, cpu, table);

}






//compares the cards against each other to determine the winner of the round, or if war is necessary
void checkCards (deque<Card>& player, deque<Card>& cpu, deque<deque<Card>>& table) {

	if (table[0][0] > table[1][0]) { //player's card is higher than cpu's

		collectCards(player, cpu, table, false);

		clearTable(table);

	} else if (table[0][0] < table[1][0]) { //cpu's card is higher than player's

		cout << "CPU wins this round!" << endl;

		collectCards(player, cpu, table, true);

		clearTable(table);

	} else {

		cout << "This means war!" << endl;
		war(player, cpu, table);
		clearTable(table);

	}

	clearTable(table);

}






//checks if there are enough cards for war, then places three and draws a fourth to play war
void war (deque<Card>& player, deque<Card>& cpu, deque<deque<Card>>& table) {

	if (player.size() <= NUMBER_OF_WAR_CARDS){ 	//if a player doesn't have enough
											    //cards for war they lose
		cout << "You don't have enough cards for war!" << endl;
		cout << "Adding the rest of your cards to their deck." << endl;
		collectCards(player, cpu, table, true);

		while (player.size() > 0) {

			cpu.push_back(player.front());
			player.pop_front();

		}

	} else if (cpu.size() <= NUMBER_OF_WAR_CARDS) {

		cout << "CPU doesn't have enough cards for war!" << endl;
		cout << "Adding the rest of their cards to your deck." << endl;
		collectCards(player, cpu, table, false);

		while (cpu.size() > 0) {

			player.push_back(cpu.front());
			cpu.pop_front();

		}

	} else {

		for (int i = 0; i < NUMBER_OF_WAR_CARDS; i++) {

			table[0].push_back(player.front()); //place 3 cards each for player
			player.pop_front();
			table[1].push_back(cpu.front());    //and cpu on to the table.
			cpu.pop_front();

		}

		table[0].push_front(player.front()); //place the next card at 
		player.pop_front();
		table[1].push_front(cpu.front());	 //the front of the table.
		cpu.pop_front();

		displayTable(table);
		checkCards(player, cpu, table);

	}

}






void collectCards (deque<Card>& player, deque<Card>& cpu, deque<deque<Card>>& table, bool isCPUwinner) {

	//We need this bool value to determine what to print to the console for the 
	//player to understand where the cards came from and where they are going.
	//The reason it is named 'isCPUwinner' is because CPU is referred to as '1', 
	//and player is referred to as '0' in the table deque. To adhere to this convention 
	//I leveraged the C++ interpretation of bool values as '0' == false, '1' == true.
	if (isCPUwinner) {

		for (int i = 0; i < table[1].size(); i++) {

			cout << "Returning the " << table[1][i].toString() << " to their deck." << endl;
			cpu.push_back(table[1][i]); //cpu's card(s) is returned to cpu's deck

		}

		for (int i = 0; i < table[0].size(); i++) {

			cout << "Adding the "  << table[0][i].toString() << " to their deck."  << endl;
			cpu.push_back(table[0][i]); //player's card(s) is added to cpu's deck
		
		}

	} else {

		for (int i = 0; i < table[0].size(); i++) {

			cout << "Returning the " << table[0][i].toString() << " to your deck." << endl;
			player.push_back(table[0][i]); //player's card(s) is returned to player's deck

		}

		for (int i = 0; i < table[1].size(); i++) {

			cout << "Adding the "  << table[1][i].toString() << " to your deck."  << endl;
			player.push_back(table[1][i]); //cpu's card(s) is added to player's deck
		
		}

	}

}






//Displays the cards to the console
void displayTable (deque<deque<Card>>& table) {

	cout << "You played a " << table[0][0].toString() << " VS. "
		 << "the CPU's " << table[1][0].toString() << endl;

}






//clears the table to be ready for the next round
void clearTable (deque<deque<Card>>& table) {

	table[0].clear();
	table[1].clear();

}

