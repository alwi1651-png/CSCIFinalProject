#include "Board.h"
#include "Character.h"
#include "Event.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <random>

#define ORANGE "\033[48;2;230;115;0m"
#define GREY   "\033[48;2;128;128;128m"
#define GREEN  "\033[48;2;34;139;34m"
#define BLUE   "\033[48;2;10;10;230m"
#define PINK   "\033[48;2;255;105;180m"
#define BROWN  "\033[48;2;139;69;19m"
#define RED    "\033[48;2;230;10;10m"
#define PURPLE "\033[48;2;128;0;128m"
#define RESET  "\033[0m"

using namespace std;

//constructor
Board::Board(std::vector<bool> isFellowship){
    int _MAX_PLAYERS = isFellowship.size();



    for (int i = 0; i < _MAX_PLAYERS; i++) {
        _player_position[i] = 0;
        if (isFellowship[i]){
            _player_board_assignment[i] = 0; 
        }
        else {
            _player_board_assignment[i] = 1; 
        }
    }
    ifstream eventFile("random_events.txt");
    string line;
    // Skip header
    getline(eventFile, line);   
    while (getline(eventFile, line)) {
        if (line.empty()) continue;
        Event e(line);
        events.push_back(e);
    }
    initializeBoard();
}


//We looked up how to do this
int Board::spinner() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int> dist(1, 6);
    return dist(gen);
}


void Board::initializeTiles(int board_index) {
    Tile tile;
    int green_count = 0;
    int total_tiles = _BOARD_SIZE;

    for (int i = 0; i < total_tiles; i++) {

        if (i == total_tiles - 1) {
            tile.color = 'O';
        }
        else if (i == 0) {
            tile.color = 'Y';
        }
        else if (green_count < 30 &&
                 (rand() % (total_tiles - i) < 30 - green_count)) {
            tile.color = 'G';
            green_count++;
        }
        else {
            // Adjust weighting based on board
            int color_choice;

            if (board_index == 0) {
                //doubles chance of getting purple tile which corresponds to discoveries
                //you get more discoveries on fellowship board because of mentorship
                //Purple leads to a riddle and an opportunity for bonus points
                color_choice = rand() % 7;
                switch (color_choice) {
                    case 0: 
                    case 1: tile.color = 'G'; break;
                    case 2: tile.color = 'B'; break;  
                    case 3: tile.color = 'P'; break;
                    case 4: tile.color = 'T'; break;
                    case 5: tile.color = 'R'; break;
                    case 6: tile.color = 'U'; break;
                }
            }
            else {
                //triples the chance of getting red tile which corresponds to discoveries
                //you get more discoveries on fellowship board because of mentorship
                color_choice = rand() % 8;
                switch (color_choice) {
                    case 0: 
                    case 1:
                    case 2: tile.color = 'B'; break;
                    case 3: tile.color = 'G'; break;  
                    case 4: tile.color = 'P'; break;
                    case 5: tile.color = 'T'; break;
                    case 6: tile.color = 'R'; break;
                    case 7: tile.color = 'U'; break;
                }
            }
        }

        _tiles[board_index][i] = tile;
    }
    int greens_needed = 20 - green_count;
    while (greens_needed > 0) {
        int pos = rand() % total_tiles;
        if (_tiles[board_index][pos].color != 'G' && pos != 0 && pos != total_tiles - 1) {
        _tiles[board_index][pos].color = 'G';
        greens_needed--;
        }
    }

}

bool Board::isPlayerOnTile(int player_index, int pos) {
    return (_player_position[player_index] == pos);
}

void Board::displayTile(int board_index, int player_index, int pos) {

    string color = "";
    char c = _tiles[board_index][pos].color;

    switch(c) {
        case 'O': color = ORANGE; break;
        case 'Y': color = GREY; break;
        case 'G': color = GREEN; break;
        case 'B': color = BLUE; break;
        case 'P': color = PINK; break;
        case 'T': color = BROWN; break;
        case 'R': color = RED; break;
        case 'U': color = PURPLE; break;
    }

    bool player_here = false;

    // Only display a player if they belong to this board
    if (_player_board_assignment[player_index] == board_index &&
        _player_position[player_index] == pos)
    {
        player_here = true;
    }

    if (player_here) {
        cout << color << "|" << (player_index + 1) << "|" << RESET;
    } else {
        cout << color << "| |" << RESET;
    }
}

void Board::initializeBoard() {
    for (int i = 0; i < 2; i++) {
        initializeTiles(i);
    }
  
}

void Board::displayTrack(int board_index) {

    for (int pos = 0; pos < _BOARD_SIZE; pos++) {

        // Draw the tile, checking both players
        displayTile(board_index, 0, pos);
        displayTile(board_index, 1, pos);
    }
    cout << endl;
}


void Board::displayBoard() {
    for (int board_index = 0; board_index < 2; board_index++) {
        displayTrack(board_index);
        cout << endl;
    }
}

bool Board::movePlayer(int player_index, int steps) {
    _player_position[player_index] += steps;

    if (_player_position[player_index] >= _BOARD_SIZE - 1) {
        _player_position[player_index] = _BOARD_SIZE - 1;
        return true;
    }
    return false;
}

//returns change in players discover points 
int Board::greenTileTurn(int player_index) {
    if (rand() % 2 == 0) {
        cout << "Green tile event triggered!\n";
        int index = rand() % events.size();
        Event e = events[index];
        if (e.getPathType() == _player_board_assignment[player_index] ){
            cout << "Event: " << e.getDescription() << endl;
            if (_player_board_assignment[player_index] == 0){
                if (e.getAdvisor() == _player_advisor[player_index]){
                        cout << "Advisor match! You have been protected from the event\n";
                        return 0;
                }
                else {
                    cout << "Fellowship path. Applying event effects.\n" << " Your discovery Points have changed by " << e.getDiscoveryPoints() << endl;
                    return e.getDiscoveryPoints();
                }
            }
            else {
                cout << "Lab Assignment path. Applying event effects.\n" << " Your discovery Points have changed by " << e.getDiscoveryPoints() << endl;
                return e.getDiscoveryPoints();
            }
            }
        else {
            cout << "Event does not match path type.\n";
        }
        return 0;
    }
    return 0;
}
//returns change in players discovery points, insight, efficiency, accurace and experience
vector<int> Board::playerTurn(int player_index, std::string playerName, std::string characterName, int discoveryPoints, int insight, int efficiency, int accuracy, int experience) {
    double strandSimilarity(std::string s1, std::string s2) {
        if (s1.length() != s2.length()) return 0.0;
        int matches = 0;
        for (int i = 0; i < (int)s1.length(); i++) {
        if (s1[i] == s2[i]) matches++;
        }
        return (double)matches / s1.length();
    }

    double strandSimilarityUnequal(std::string s1, std::string s2) {
        std::string longStr = s1.length() >= s2.length() ? s1 : s2;
        std::string shortStr = s1.length() < s2.length() ? s1 : s2;
        double maxScore = 0.0;

        for (int i = 0; i <= (int)(longStr.length() - shortStr.length()); i++) {
            int matches = 0;
            for (int j = 0; j < (int)shortStr.length(); j++) {
                if (shortStr[j] == longStr[i+j]) matches++;
            }
            double score = (double)matches / shortStr.length();
            if (score > maxScore) maxScore = score;
        }
        return maxScore;

    }

void identifyMutations(std::string input_strand, std::string target_strand) {
    std::cout << "Mutation report:\n";
    int len = (int)std::min(input_strand.length(), target_strand.length());
    for (int i = 0; i < len; i++) {
        if (input_strand[i] != target_strand[i]) {
            std::cout << "Substitution at position " << i << ": " << input_strand[i] << " -> " << target_strand[i] << "\n";
        }
    }

    if (input_strand.length() < target_strand.length()) {
        std::cout << "Insertion detected at position " << len << ": " << target_strand.substr(len) << "\n";
    } else if (input_strand.length() > target_strand.length()) {
        std::cout << "Deletion detected at position " << len << ": " << input_strand.substr(len) << "\n";
    }
}

void transcribeDNAtoRNA(std::string strand) {
    for (int i = 0; i < (int)strand.length(); i++) {
    if (strand[i] == 'T') strand[i] = 'U';
    }
    std::cout << "RNA transcript: " << strand << std::endl;
}

int handleRiddle(int player_index) {
    std::cout << "Riddle challenge! Solve correctly to gain 500 Insight Points.\n";
    // Placeholder: assume player always answers correctly
    return 500;
}



if (playerFinished(player_index)) {
    std::cout << playerName << " has reached the Genome Conference!" << std::endl;
    return vector<int>{0, 0, 0, 0, 0};
}

int deltaDiscovery = 0, deltaInsight = 0, deltaEfficiency = 0, deltaAccuracy = 0, deltaExperience = 0;
bool turnComplete = false;

while (!turnComplete) {
    std::cout << "\n--- " << playerName << "'s Turn ---\n";
    std::cout << "1) Check Player Progress\n";
    std::cout << "2) Review Character\n";
    std::cout << "3) Check Position\n";
    std::cout << "4) Review your Advisor\n";
    std::cout << "5) Move Forward\n";
    std::cout << "Choose an option (1-5): ";

    int choice;
    std::cin >> choice;

    switch (choice) {
        case 1: { // Check Player Progress
            std::cout << "1) Review Discovery Points\n";
            std::cout << "2) Review Trait stats\n";
            int subchoice;
            std::cin >> subchoice;
            if (subchoice == 1) {
                std::cout << "Discovery Points: " << discoveryPoints << std::endl;
            } else if (subchoice == 2) {
                std::cout << "Traits - Insight: " << insight
                          << ", Efficiency: " << efficiency
                          << ", Accuracy: " << accuracy << std::endl;
            }
            break;
        }
        case 2: { // Review Character
            std::cout << "Character Name: " << characterName
                      << ", Experience: " << experience << std::endl;
            break;
        }
        case 3: { // Check Position
            displayBoard();
            break;
        }
        case 4: { // Review Advisor
            std::cout << "1) Display Advisor Abilities\n";
            std::cout << "2) Use Abilities for Challenge\n";
            int subchoice;
            std::cin >> subchoice;
            if (subchoice == 1) {
                std::cout << "Advisor Abilities: " << getAdvisorAbilities(_player_advisor[player_index]) << std::endl;
            } else if (subchoice == 2) {
                std::cout << "Using advisor abilities for current challenge...\n";
                // Implement ability effect here
            }
            break;
        }
        case 5: { // Move Forward
            int steps = spinner();
            movePlayer(player_index, steps);
            std::cout << playerName << " rolled a " << steps << std::endl;

            int position = getPlayerPosition(player_index);
            int board_index = _player_board_assignment[player_index];
            char tile_color = _tiles[board_index][position].color;
            std::cout << playerName << " is on square " << position << std::endl;

            if (tile_color == 'G') { // Green tile
                if (rand() % 2 == 0) {
                    std::cout << "Green tile event triggered!\n";
                    deltaDiscovery += greenTileTurn(player_index);
                } else {
                    std::cout << "No event on this green tile.\n";
                }
            } else if (tile_color == 'B') { // Blue tile
                std::string s1, s2;
                std::cout << "DNA Task 1 - Enter two DNA strands of equal length:\n";
                std::cin >> s1 >> s2;
                deltaDiscovery += static_cast<int>(strandSimilarity(s1, s2) * 100);
                deltaInsight += 10;
            } else if (tile_color == 'P') { // Pink tile
                std::string s1, s2;
                std::cout << "DNA Task 2 - Enter two DNA strands (unequal lengths allowed):\n";
                std::cin >> s1 >> s2;
                deltaDiscovery += static_cast<int>(strandSimilarityUnequal(s1, s2) * 100);
                deltaInsight += 10;
            } else if (tile_color == 'R') { // Red tile
                std::string s1, s2;
                std::cout << "DNA Task 3 - Enter input and target DNA strands:\n";
                std::cin >> s1 >> s2;
                identifyMutations(s1, s2);
                deltaAccuracy += 5;
                deltaDiscovery += 20;
            } else if (tile_color == 'T') { // Brown tile
                std::string s1;
                std::cout << "DNA Task 4 - Enter DNA strand to transcribe to RNA:\n";
                std::cin >> s1;
                transcribeDNAtoRNA(s1);
                deltaEfficiency += 10;
                deltaDiscovery += 10;
            } else if (tile_color == 'U') { // Purple tile
                deltaInsight += handleRiddle(player_index);
                deltaExperience += 50;
            }

            displayBoard();
            turnComplete = true;
            break;
        }
        default:
            std::cout << "Invalid choice, try again.\n";
    }
}

return vector<int>{deltaDiscovery, deltaInsight, deltaEfficiency, deltaAccuracy, deltaExperience};
}



int Board::getPlayerPosition(int player_index)  {
    return _player_position[player_index];
}



