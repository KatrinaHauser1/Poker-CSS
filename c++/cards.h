#ifndef CARDS_H
#define CARDS_H

#include <string>

class cards {
public:
        static const int CARDS_IN_DECK = 52;
        static const int CARDS_DRAWN = 7;
        static const int NUM_COMBINATIONS = 21;

        std::string card;
        int value;
        std::string suit;
        cards** myHand;

        cards(std::string card, int value, std::string suit);
        cards();

        int CompareTo(cards* other);
        int getValue();
        std::string getSuit();
        cards** getMyHand();
        int getSuitLevel(std::string suit);
        cards** initializeStack();
        cards** shuffleStack(cards** myStack);
        cards** drawHand(cards** myStack);
        void printStack(cards** myStack);
        void printHand(cards** myHand);
        void deliverStackandHand();
        void evaluateHand(cards** myHand);
        cards*** getCombinations(cards** myHand);
        void printCombinations(cards*** myCombinations);

	bool operator<(cards& other) {
        	return this->CompareTo(&other) < 0;
	}
};

#endif

