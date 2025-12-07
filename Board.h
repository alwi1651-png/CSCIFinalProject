#ifndef BOARD_H
#define BOARD_H

#include "Tile.h"
#include "Character.h"
#include "Event.h"
#include "Riddle.h"

class Board {
    private:
        std::vector<Event> events;
        std::vector<Riddle> riddles; 

        static const int _BOARD_SIZE = 52;
        static const int _MAX_PLAYERS = 2;
 

        Tile _tiles[2][_BOARD_SIZE];

        int _player_count;
        int _player_position[_MAX_PLAYERS];
        int _player_advisor[_MAX_PLAYERS];

        // 0 = training fellowship board, 1 = lab position board
        int _player_board_assignment[_MAX_PLAYERS];

        void initializeTiles(int player_index);
        bool isPlayerOnTile(int player_index, int pos);
        void displayTile(int board_index, int player_index, int pos);
        int spinner();
        bool playerOnePath;
        bool playerTwoPath;
        std::string advisorAbilities[5] = {
            "avoiding contamination",
            "improving efficiency streamlining pipelines",
            "identifying rare genetic variants",
            "debugging code",
            "learning equipment"
        };

    


    public:
        std::string getAdvisorAbilities(int advisorID) {
            if (advisorID >= 0 && advisorID < 5) {
                return advisorAbilities[advisorID];
            }
            return "No Advisor";
        }

        Board(std::vector<bool> is_fellowship);  // Constructor declaration
        void initializeBoard();
        void displayTrack(int player_index);
        void displayBoard();
        bool movePlayer(int player_index, int steps);
        int getPlayerPosition(int player_index);

        // role: "fellowship" -> board 0, "lab" -> board 1

        // retrieves board index player is mapped to
        int getPlayerBoard(int player_index) {
            return _player_board_assignment[player_index];
        }
        //returns change in players discovery points, insight, efficiency, accurace and experience
        std::vector<int> playerTurn(int player_index, std::string playerName,std::string characterName, int discoveryPoints, int insight, int efficiency, int accuracy, int experience);

        bool playerFinished(int player_index) {
            int playerPosition = getPlayerPosition(player_index);
            return playerPosition == 51;
        }
        bool GameFinished(){
            bool finished= false;
            for (int indx =0; indx < _MAX_PLAYERS; indx++){
                    finished = playerFinished(indx);
            }
            return finished;
        }
        int greenTileTurn(int player_index);
        
        double strandSimilarity(std::string strandOne, std::string strandTwo) {
            if (strandOne.length() != strandTwo.length()) return 0.0;
            int matches = 0;
            for (int i = 0; i < (int)strandOne.length(); i++) {
                if (strandOne[i] == strandTwo[i]) matches++;
            }
            return (double)matches / strandOne.length();
        }

        int bestStrandMatch(std::string input_strand, std::string target_strand) {
            std::string longStr = input_strand.length() >= target_strand.length() ? input_strand : target_strand;
            std::string shortStr = input_strand.length() < target_strand.length() ? input_strand : target_strand;
            double maxScore = 0.0;
            int indexOfMaxSimilarity = 0;

            for (int i = 0; i <= (int)(longStr.length() - shortStr.length()); i++) {
                int matches = 0;
                for (int j = 0; j < (int)shortStr.length(); j++) {
                    if (shortStr[j] == longStr[i+j]) matches++;
                }
                double score = (double)matches / shortStr.length();
                if (score > maxScore) { 
                    maxScore = score;
                    indexOfMaxSimilarity = i;
                }
            }
            return indexOfMaxSimilarity;
        }

        void identifyMutations(std::string input_strand, std::string target_strand) {
            int indexOfMaxSimilarity = bestStrandMatch(input_strand, target_strand);
            std::cout << "Mutation report:\n";

            std::string longStr = input_strand.length() >= target_strand.length() ? input_strand : target_strand;
            std::string shortStr = input_strand.length() < target_strand.length() ? input_strand : target_strand;
            int len = shortStr.length();

            // Determine whether input_strand was the long one
            bool inputIsLong = (input_strand.length() >= target_strand.length());

            // Substitutions
            for (int i = 0; i < len; i++) {
                if (longStr[i + indexOfMaxSimilarity] != shortStr[i]) {
                    int inputPos;
                    if (inputIsLong) {
                        inputPos = i + indexOfMaxSimilarity;               // input is longStr
                    } else {
                        inputPos = i;                                      // input is shortStr
                    }
                    std::cout << "Substitution at position "
                            << (inputPos + 1) << ": "
                            << (inputIsLong ? longStr[indexOfMaxSimilarity+i] : shortStr[i])
                            << " -> "
                            << (inputIsLong ? shortStr[i] : longStr[indexOfMaxSimilarity+i])
                            << "\n";
                }
            }

            // Insertions and deletions happen when there is extra characters
            if (longStr.length() > shortStr.length()) {

                // left side extra characters 
                int leftExtraCount = indexOfMaxSimilarity;
                if (leftExtraCount > 0) {
                    for (int k = 0; k < leftExtraCount; k++) {
                        char c = longStr[k];

                        // Convert longStr position to input-strand coordinate
                        int inputPos = inputIsLong ? k : -1;   // input shortStr has no left-side bases

                        if (inputIsLong) {
                            std::cout << "Deletion at position "
                                    << (inputPos + 1) << ": " << c << "\n";
                        } else {
                            // insertion relative to input: insert before position 1
                            std::cout << "Insertion at position "
                                    << 1 << ": " << c << "\n";
                        }
                    }
                }

                // right side extras 
                int rightStart = indexOfMaxSimilarity + len;
                int rightExtraCount = longStr.length() - rightStart;

                if (rightExtraCount > 0) {
                    for (int k = 0; k < rightExtraCount; k++) {

                        int pos = rightStart + k;
                        char c = longStr[pos];

                        int inputPos;
                        if (inputIsLong) {
                            inputPos = pos;                        // direct mapping into input strand
                        } else {
                            inputPos = input_strand.length();      // insert at end of input strand
                        }

                        if (inputIsLong) {
                            std::cout << "Deletion at position "
                                    << (inputPos + 1) << ": " << c << "\n";
                        } else {
                            std::cout << "Insertion at position "
                                    << (inputPos + 1) << ": " << c << "\n";
                        }
                    }
                }
            }
        }

        void transcribeDNAtoRNA(std::string strand) {
            for (int i = 0; i < (int)strand.length(); i++) {
            if (strand[i] == 'T') strand[i] = 'U';
            }
            std::cout << "RNA transcript: " << strand << std::endl;
        }

        int handleRiddle() {
            Riddle riddle = riddles[rand()% riddles.size()];
            std::cout << "Riddle challenge! Solve correctly to gain 500 Insight Points.\n";
            std::cout << riddle.getQuestion() << std::endl;
            std::string answer;
            std::cin>>  answer;
            if (answer == riddle.getAnswer()){
                return 500;
            }
            else{
                return 0;
            }
        }
};
#endif
