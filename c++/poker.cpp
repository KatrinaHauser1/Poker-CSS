#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "cards.h"

using namespace std;

void printIntro(int argc, char* argv[]) {

        cout << "✦✦✦✦✦ POKER ✦✦✦✦✦ HAND ✦✦✦✦✦ ANALYZER ✦✦✦✦✦\n";
        if (argc == 1) {
                cout << "\n✦✦✦✦✦ USING ✦✦✦✦ RANDOMIZED ✦✦✦✦ DECK ✦✦✦✦✦\n";
        }

        else {
                cout << "✦✦✦✦✦✦ File - " + string(argv[1]) + " ✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦\n";
                cout << "\n✦✦✦✦✦ USING ✦✦✦✦✦ TEST ✦✦✦✦✦✦✦ DECK ✦✦✦✦✦\n";
        }
}

cards** testDeck(char* argv[]) {

        cards** testHand = new cards*[7];
        string testFile = argv[1];
        ifstream file(testFile);

        if (file.good()) {
                vector<string> teststrings;
                string fileContents;
                
                getline(file, fileContents, '\0');
                while (!fileContents.empty() && (fileContents.back() == '\r' || fileContents.back() == '\n')) {
                        fileContents.pop_back();
                }

                stringstream ss(fileContents);
                string token;
                while (getline(ss, token, ',')) {
                        teststrings.push_back(token);
                }

                if (teststrings.size() != 7) {
                        cout << "\nError: File contains too many/not enough cards\n";
                        exit(0);
                }

                for (size_t i = 0; i < teststrings.size(); i++) {
                        if (teststrings[i].length() != 3) {
                                cout << "\nError: Incorrect Card Format\n";
                                exit(0);
                        }
                        int value = 0;
                        string suitCheck = teststrings[i].substr(0, 2);
                        if (suitCheck == " J") {
                                value = 11;
                        }
			else if (suitCheck == " Q") {
                                value = 12;
                        }
			else if (suitCheck == " K") {
                                value = 13;
                        }
			else if (suitCheck == " A") {
                                value = 14;
                        }
			else if (suitCheck == "10") {
                                value = 10;
                        }
			 else {
                                value = stoi(teststrings[i].substr(1, 1));
                        }
                        testHand[i] = new cards(teststrings[i], value, teststrings[i].substr(2));
                }

                cout << "\n✦✦✦✦✦✦✦✦✦✦✦✦✦✦ Your Hand: ✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦\n";
                for (int h = 0; h < 7; h++) {
                        cout << testHand[h]->card << " ";
                }
                cout << "\n✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦✦\n";

                vector<cards> tempHand;

                for (int i = 0; i < 7; i++) {
                        tempHand.push_back(*testHand[i]);
                }

                sort(tempHand.begin(), tempHand.end());
                for (size_t k = 0; k < tempHand.size() - 1; k++) {
                        if ((tempHand[k].card) == tempHand[k + 1].card) {
                                cout << "\nError: Duplicate found in Hand\n";
                                cout << "DUPLICATE: " << tempHand[k].card << "\n";
                                exit(0);
                        }
                }
        }
        else {
                cout << "\nError: File not found\n";
                exit(0);
        }
        return testHand;
}

int main(int argc, char* argv[]) {
        cards myCards("", 0, "");
        printIntro(argc, argv);

        cards**  activeHand;

        if (argc == 1) {
                myCards.deliverStackandHand();
                activeHand = myCards.getMyHand();
        }
        else {
                activeHand = testDeck(argv);
        }
        myCards.evaluateHand(activeHand);

        return 0;
}

