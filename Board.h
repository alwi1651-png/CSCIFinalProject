#ifndef BOARD_H
#define BOARD_H

#include "Tile.h"
#include "Character.h"
#include "Event.h"

class Board {
    private:
        std::vector<Event> events;
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
        
};
#endif
