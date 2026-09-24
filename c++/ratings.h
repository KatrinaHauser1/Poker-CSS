#ifndef RATINGS_H
#define RATINGS_H

#include <string>

class cards;

class ratings {

public:
        cards** playedHand;
        cards** extraCards;
        int score;
        int* tiebreak;

        ratings(cards** combination);
        ~ratings();

        int getScore(cards** playable);
        int* getTiebreak(cards** playable, int score);
        int cardStrength(cards* card);
        int getSuitLevel(std::string suit);
        bool isAscending(cards** playable);
        int sumUp(cards** playable);
        bool isFlush(cards** playable);
        bool numDuplicates(std::string handtype, cards** playable);
        std::string convertScoreToHand(int score);
        int CompareTo(ratings* other);
};

#endif

