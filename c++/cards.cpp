#include "cards.h"
#include "ratings.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <random>
#include <algorithm>

using namespace std;

cards::cards(string card, int value, string suit){
	this->card = card;
	this->value = value;
	this->suit = suit;
}

cards::cards() {
	this->card = "";
	this->value = 0;
	this->suit = "";
}

int cards::CompareTo(cards* other) {
	if (this->value != other->value) {
		return (this->value < other->value) ? -1 : 1; 
	}
	int thisSuit = getSuitLevel(this->suit);
	int otherSuit = getSuitLevel(other->suit);
	return (thisSuit > otherSuit) ? -1 : ((thisSuit < otherSuit) ? 1 : 0);
}

int cards::getValue() {
	return this->value;
}

string cards::getSuit() {
	return this->suit;
}

cards** cards::getMyHand() {
	return this->myHand;
}

int cards::getSuitLevel(string suit) {
	if (suit == "D") return 1;
	if (suit == "C") return 2;
	if (suit == "H") return 3;
	if (suit == "S") return 4;
	return 0;
}

cards** cards::initializeStack(){
	string cardStrings[CARDS_IN_DECK] = {" 2H", " 3H", " 4H", " 5H", " 6H", " 7H", " 8H", " 9H", "10H", " JH", " QH", " KH", " AH", 
		" 2D", " 3D", " 4D", " 5D", " 6D", " 7D", " 8D", " 9D", "10D", " JD", " QD", " KD", " AD", 
		" 2C", " 3C", " 4C", " 5C", " 6C", " 7C", " 8C", " 9C", "10C", " JC", " QC", " KC", " AC", 
		" 2S", " 3S", " 4S", " 5S", " 6S", " 7S", " 8S", " 9S", "10S", " JS", " QS", " KS", " AS"
	};

	cards** myStack = new cards*[CARDS_IN_DECK];
	for (int i = 0; i < CARDS_IN_DECK; i++){
		int value = 0;
		if (cardStrings[i].substr(0,2) == " J") {
			value = 11;
		}
		else if (cardStrings[i].substr(0,2) == " Q") {
			value = 12;
		}
		else if (cardStrings[i].substr(0,2) == " K") {
			value = 13;
		}
		else if (cardStrings[i].substr(0,2) == " A") {
			value = 14;
		}
		else if (cardStrings[i].substr(0,2) == "10") {
			value = 10;
		}
		else {
			value = stoi(cardStrings[i].substr(1,1));
		}
		myStack[i] = new cards(cardStrings[i], value, cardStrings[i].substr(2));
	}
	return myStack;
}

cards** cards::shuffleStack(cards** myStack) {
	cards** myShuffledStack = new cards*[CARDS_IN_DECK];
	for (int i = 0; i < CARDS_IN_DECK; i++) {
		myShuffledStack[i] = nullptr;
	}

	srand(time(nullptr));
	for (int i = 0; i < CARDS_IN_DECK; i++){
		while (true){
			int newPos = (rand() % 52);
			if (myShuffledStack[newPos] == nullptr){
				myShuffledStack[newPos] = myStack[i];
				break;
			}
		}
	}
	return myShuffledStack;
}

cards** cards::drawHand(cards** myStack) {

	cards** myHand = new cards*[CARDS_DRAWN];

	for (int i = 0; i < CARDS_DRAWN; i++) {
		myHand[i] = myStack[i];
	}
	return myHand;
}

void cards::printStack(cards** myStack){

	cout << "        ✦✦✦ Shuffled " << CARDS_IN_DECK << " card deck: ✦✦✦" << endl;
	for (int i = 0; i < CARDS_IN_DECK; i++) {
		cout << myStack[i]->card << " ";
		if ((i+1)%9 == 0) { cout << endl; }
	}
	cout << "\n✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦" << endl;
}

void cards::printHand(cards** myHand){

	cout << "\n✦✦✦✦✦✦✦✦✦✦✦✦✦✦ Your Hand: ✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦" << endl;
	for (int i = 0; i < CARDS_DRAWN; i++) {
		cout << myHand[i]->card << " ";
	}
	cout << "\n✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦" << endl;
}

void cards::deliverStackandHand(){

	cards** myStack = initializeStack();
	myStack = shuffleStack(myStack);
	myHand = drawHand(myStack);
	printStack(myStack);
	printHand(myHand);
}

void cards::evaluateHand(cards** myHand) {
	cards*** myCombinations = getCombinations(myHand);
	printCombinations(myCombinations);

	ratings** handRatings = new ratings*[NUM_COMBINATIONS];
	for (int i = 0; i < NUM_COMBINATIONS; i++) {
		handRatings[i] = new ratings(myCombinations[i]);
	}

	for (int i = 0; i < NUM_COMBINATIONS - 1; i++) {
		for (int j = 0; j < NUM_COMBINATIONS - i - 1; j++) {
			if (handRatings[j]->CompareTo(handRatings[j+1]) > 0) {
				ratings* temp = handRatings[j];
				handRatings[j] = handRatings[j+1];
				handRatings[j+1] = temp;
			}
		}
	}

	cout << "\n✦✦✦✦✦✦✦✦✦✦✦✦✦HIGH HAND ORDER✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦" << endl;
	for (int i = 0; i < NUM_COMBINATIONS; i++) {

		for (int j = 0; j < 5; j++) {
			cout << handRatings[i]->playedHand[j]->card << " ";
		}
		cout << " | "  << handRatings[i]->extraCards[0]->card << " " << handRatings[i]->extraCards[1]->card;
		string Hand = handRatings[i]->convertScoreToHand(handRatings[i]->score);
		cout << " --- " << Hand;
		cout << endl;
	}

	cout << "\n✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦" << endl;
}

cards*** cards::getCombinations(cards** myHand) {

	cards*** myCombinations = new cards**[NUM_COMBINATIONS];
	for (int i = 0; i < NUM_COMBINATIONS; i++) {
		myCombinations[i] = new cards*[CARDS_DRAWN];
	}

	int combination = 0;

	for (int i = 0; i < CARDS_DRAWN; i++) {
		for (int j = i + 1; j < CARDS_DRAWN; j++) {

			int index = 0;

			for (int k = 0; k < CARDS_DRAWN; k++) {
				if (k != i && k != j) {
					myCombinations[combination][index] = myHand[k];
					index++;
				}
			}

			myCombinations[combination][5] = myHand[i];
			myCombinations[combination][6] = myHand[j];

			combination++;
		}
	}

	return myCombinations;
}

void cards::printCombinations(cards*** myCombinations) {

	cout << "\n✦✦✦✦✦✦✦✦✦✦ Hand Combinations: ✦✦✦✦✦✦✦✦✦✦✦✦✦" << endl;
	for (int i = 0; i < NUM_COMBINATIONS; i++) {
		for (int j = 0; j < CARDS_DRAWN; j++) {
			cout << myCombinations[i][j]->card << " ";
			if (j == 4) {
				cout << " | ";
			}
		}
		cout << endl;
	}
}
