#include "ratings.h"
#include "cards.h"
#include <string>
#include <algorithm>

using namespace std;

ratings::ratings(cards** combination) {

	playedHand = new cards*[5];
	extraCards = new cards*[2]; 

	for (int i = 0; i < 7; i++) {
		if (i < 5) {
			playedHand[i] = combination[i];
		}
		else {
			extraCards[i-5] = combination[i];
		}
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4 - i; j++) {
			if (playedHand[j]->CompareTo(playedHand[j+1]) > 0) {
				cards* temp = playedHand[j];
				playedHand[j] = playedHand[j+1];
				playedHand[j+1] = temp;
			}
		}
	}

	score = getScore(playedHand);
	tiebreak = getTiebreak(playedHand, score);
}

ratings::~ratings() {
	delete[] playedHand;
	delete[] extraCards;
	delete[] tiebreak;
}

int ratings::getScore(cards** playable) {

	int score = 0;

	if (isAscending(playable) && isFlush(playable) && (playable[0]->value == 10)){
		score = 10;
	}
	else if (isAscending(playable) && isFlush(playable)) {
		score = 9;
	}
	else if (numDuplicates("four of a kind", playable)) {
		score = 8;
	}
	else if (numDuplicates("full house", playable)) {
		score = 7;
	}
	else if (isFlush(playable)) {
		score = 6;
	}
	else if (isAscending(playable)) {
		score = 5;
	}
	else if (numDuplicates("three of a kind", playable)) {
		score = 4;
	}   
	else if (numDuplicates("two pair", playable)) {
		score = 3;
	}
	else if (numDuplicates("pair", playable)) {
		score = 2;
	}
	else {
		score = 1;
	}
	return score;
}

int* ratings::getTiebreak(cards** playable, int score) {

	int* tiebreak = new int[5]{0, 0, 0, 0, 0};
	int index = 0;

	switch (score) {
		case 10:
			tiebreak[0] = cardStrength(playable[4]);
			break;
		case (9):
		case (5):
			if (playable[4]->value == 14 && playable[0]->value == 2) {
				tiebreak[0] = cardStrength(playable[3]);
			}
			else {
				tiebreak[0] = cardStrength(playable[4]);
			}
			break;

		case (8): {
				  int fourValue = playable[2]->value;

				  for (int i = 4; i >= 0; i--) {
					  if (playable[i]->value == fourValue) {
						  tiebreak[index] = cardStrength(playable[i]);
						  index++;
					  }
				  }
				  for (int i = 4; i >= 0; i--) {
					  if (playable[i]->value != fourValue) {
						  tiebreak[index] = cardStrength(playable[i]);
						  break;
					  }
				  }
				  break;
			  }

		case (7): {
				  int threeValue = playable[2]->value;

				  for (int i = 4; i >= 0; i--) {
					  if (playable[i]->value == threeValue) {
						  tiebreak[index] = cardStrength(playable[i]);
						  index++;
					  }
				  }

				  if (tiebreak[0] < tiebreak[1]) { int t = tiebreak[0]; tiebreak[0] = tiebreak[1]; tiebreak[1] = t; }
				  if (tiebreak[1] < tiebreak[2]) { int t = tiebreak[1]; tiebreak[1] = tiebreak[2]; tiebreak[2] = t; }
				  if (tiebreak[0] < tiebreak[1]) { int t = tiebreak[0]; tiebreak[0] = tiebreak[1]; tiebreak[1] = t; }

				  for (int i = 4; i >= 0; i--) {
					  if (playable[i]->value != threeValue) {
						  tiebreak[index] = cardStrength(playable[i]);
						  index++;
					  }
				  }

				  if (tiebreak[3] < tiebreak[4]) { int t = tiebreak[3]; tiebreak[3] = tiebreak[4]; tiebreak[4] = t; }
				  break;
			  }


		case (6):
			  for (int i = 4; i >= 0; i--) {
				  tiebreak[index] = cardStrength(playable[i]);
				  index++;
			  }
			  break;

		case 4: {
				int tripValue = playable[2]->value;

				for (int i = 4; i >= 0; i--) {
					if (playable[i]->value == tripValue) {
						tiebreak[index] = cardStrength(playable[i]);
						index++;
					}
				}

				if (tiebreak[0] < tiebreak[1]) { int t = tiebreak[0]; tiebreak[0] = tiebreak[1]; tiebreak[1] = t; }
				if (tiebreak[1] < tiebreak[2]) { int t = tiebreak[1]; tiebreak[1] = tiebreak[2]; tiebreak[2] = t; }
				if (tiebreak[0] < tiebreak[1]) { int t = tiebreak[0]; tiebreak[0] = tiebreak[1]; tiebreak[1] = t; }

				for (int i = 4; i >= 0; i--) {
					if (playable[i]->value != tripValue) {
						tiebreak[index] = cardStrength(playable[i]);
						index++;
					}
				}

				if (tiebreak[3] < tiebreak[4]) { int t = tiebreak[3]; tiebreak[3] = tiebreak[4]; tiebreak[4] = t; }
				break;
			}

		case (3): {
				  int highPair = playable[3]->value;
				  int lowPair = playable[1]->value;

				  for (int i = 4; i >= 0; i--) {
					  if (playable[i]->value == highPair) {
						  tiebreak[index] = cardStrength(playable[i]);
						  index++;
					  }
				  }

				  if (tiebreak[0] < tiebreak[1]) { int t = tiebreak[0]; tiebreak[0] = tiebreak[1]; tiebreak[1] = t; }

				  for (int i = 4; i >= 0; i--) {
					  if (playable[i]->value == lowPair) {
						  tiebreak[index] = cardStrength(playable[i]);
						  index++;
					  }
				  }

				  if (tiebreak[2] < tiebreak[3]) { int t = tiebreak[2]; tiebreak[2] = tiebreak[3]; tiebreak[3] = t; }

				  for (int i = 4; i >= 0; i--) {
					  if (playable[i]->value != highPair && playable[i]->value != lowPair) {
						  tiebreak[index] = cardStrength(playable[i]);
						  index++;
						  break;
					  }
				  }
				  break;
			  }

		case (2): {
				  int pairValue = 0;

				  for (int i = 0; i < 4; i++) {
					  if (playable[i]->value == playable[i + 1]->value) {
						  pairValue = playable[i]->value;
						  break;
					  }
				  }

				  for (int i = 4; i >= 0; i--) {
					  if (playable[i]->value == pairValue) {
						  tiebreak[index] = cardStrength(playable[i]);
						  index++;
					  }
				  }

				  if (tiebreak[0] < tiebreak[1]) { int t = tiebreak[0]; tiebreak[0] = tiebreak[1]; tiebreak[1] = t; }

				  for (int i = 4; i >= 0; i--) {
					  if (playable[i]->value != pairValue) {
						  tiebreak[index] = cardStrength(playable[i]);
						  index++;
					  }
				  }
				  break;
			  }

		case (1):
		default:
			  for (int i = 4; i >= 0; i--) {
				  tiebreak[index] = cardStrength(playable[i]);
				  index++;
			  }
			  break;
	}

	return tiebreak;
}

int ratings::cardStrength(cards* card) {
	return card->value * 10 + getSuitLevel(card->suit);
}

int ratings::getSuitLevel(string suit) {
	if (suit == "D") return 1;
	if (suit == "C") return 2;
	if (suit == "H") return 3;
	if (suit == "S") return 4;
	return 0;
}

bool ratings::isAscending(cards** playable) {
	bool normalStraight = true;

	for (int i = 0; i < 4; i++){
		if ((playable[i]->getValue()+1) != (playable[i+1]->getValue())) {
			normalStraight = false;
		}
	}
	if (normalStraight) {
		return true;
	}

	if (playable[4]->getValue() == 14 && playable[0]->getValue() == 2 && 
			playable[1]->getValue() == 3 && playable[2]->getValue() == 4 && 
			playable[3]->getValue() == 5) {
		return true;
	}

	return false;
}

int ratings::sumUp(cards** playable){
	int sum = 0;
	for (int i = 0; i < 5; i++){
		sum += playable[i]->getValue();
	}
	return sum;
}

bool ratings::isFlush(cards** playable) {
	for (int i = 0; i < 4; i++){
		if (!((playable[i]->getSuit() == (playable[i+1]->getSuit())))) {
			return false;
		}
	}
	return true;
}

bool ratings::numDuplicates(string handtype, cards** playable) {
	int duplicates[15] = {0};
	for (int i = 0; i < 5; i++){
		int currentValue = playable[i]->getValue();
		duplicates[currentValue]++;
	}

	sort(duplicates, duplicates + 15);

	int highest = duplicates[14];
	int secondHighest = duplicates[13];

	if (handtype == "pair") {
		return highest == 2 && secondHighest == 1;
	}
	else if (handtype == "two pair") {
		return highest == 2 && secondHighest == 2;
	}
	else if (handtype == "three of a kind") {
		return highest == 3 && secondHighest == 1;
	}
	else if (handtype == "four of a kind") {
		return highest >= 4;
	}
	else if (handtype == "full house") {
		return highest == 3 && secondHighest == 2;
	}

	return false;
}

string ratings::convertScoreToHand(int score) {
	switch(score) {
		case 1: return "High Card";
		case 2: return "Pair";
		case 3: return "Two Pair";
		case 4: return "Three of a Kind";
		case 5: return "Straight";
		case 6: return "Flush";
		case 7: return "Full House";
		case 8: return "Four of a Kind";
		case 9: return "Straight Flush";
		case 10: return "Royal Straight Flush";
		default: return "Could not determine score";
	}
}

int ratings::CompareTo(ratings* other) {
	if (this->score != other->score) {
		return (other->score < this->score) ? -1 : ((other->score > this->score) ? 1 : 0);
	}
	for (int i = 0; i < 5; i++) {
		if (this->tiebreak[i] != other->tiebreak[i]) {
			return (other->tiebreak[i] < this->tiebreak[i]) ? -1 : ((other->tiebreak[i] > this->tiebreak[i]) ? 1 : 0);
		}
	}
	return 0;
}

