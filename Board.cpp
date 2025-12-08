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
Board::Board(vector<bool> isFellowship){
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

    ifstream riddleFile("riddles.txt");
    getline(riddleFile, line);  // skips header

    while (getline(riddleFile, line)) {
        if (line.empty()) continue;  // skip empty lines
        Riddle r(line);
        riddles.push_back(r);
    }


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
                //doubles chance of getting green tile
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
                //triples the chance of getting blue tile
         
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
    


if (playerFinished(player_index)) {
    cout << playerName << " has reached the Genome Conference!" << std::endl;
    return vector<int>{0, 0, 0, 0, 0};
}

int deltaDiscovery = 0, deltaInsight = 0, deltaEfficiency = 0, deltaAccuracy = 0, deltaExperience = 0;
bool turnComplete = false;

while (!turnComplete) {
    cout << "\n--- " << playerName << "'s Turn ---\n";
    cout << "1) Check Player Progress\n";
    cout << "2) Review Character\n";
    cout << "3) Check Position\n";
    cout << "4) Review your Advisor\n";
    cout << "5) Move Forward\n";
    cout << "Choose an option (1-5): ";

    int choice;
    cin >> choice;
    if (cin.fail() || ((choice<1) || (choice>5)) ){
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cout << "Invalid input. Please enter a number between 1 and 5.\n";
    continue;
    }

    switch (choice) {
        case 1: { // Check Player Progress
            cout << "1) Review Discovery Points\n";
            cout << "2) Review Trait stats\n";
            int subchoice;
            cin >> subchoice;
            if (subchoice == 1) {
                cout << "Discovery Points: " << discoveryPoints << std::endl;
            } else if (subchoice == 2) {
                cout << "Traits - Insight: " << insight
                          << ", Efficiency: " << efficiency
                          << ", Accuracy: " << accuracy << std::endl;
            }
            turnComplete =true;
            break;
        }
        case 2: { // Review Character
            cout << "Character Name: " << characterName
                      << ", Experience: " << experience << std::endl;
            turnComplete =true;
            break;
        }
        case 3: { // Check Position
            displayBoard();
            turnComplete=true;
            break; 
        }
        
        case 4: { // Review Advisor
            cout << "1) Display Advisor Abilities\n";
            cout << "2) Use Abilities for Challenge\n";
            int subchoice;
            cin >> subchoice;
            if (subchoice == 1) {
                cout << "Advisor Abilities: " << getAdvisorAbilities(_player_advisor[player_index]) << std::endl;
            } else if (subchoice == 2) {
                cout << "Using advisor abilities for current challenge...\n";
                // Implement ability effect here
            }
            turnComplete =true;
            break;
        }
        case 5: { // Move Forward
            int steps = spinner();
            movePlayer(player_index, steps);
            cout << playerName << " rolled a " << steps << std::endl;

            int position = getPlayerPosition(player_index);
            int board_index = _player_board_assignment[player_index];
            char tile_color = _tiles[board_index][position].color;
            cout << playerName << " is on square " << position << std::endl;

            if (tile_color == 'G') { // Green tile
                deltaDiscovery +=  greenTileTurn(player_index);
            } else if (tile_color == 'B') { // Blue tile
                string s1, s2;
                cout << "DNA Task 1 - Enter two DNA strands of equal length:\n";
                cin >> s1 >> s2;
                deltaDiscovery += static_cast<int>(strandSimilarity(s1, s2) * 1000);
                deltaInsight += 100;
                cout << "Discovery Points Increase: " << deltaDiscovery <<endl;
                cout << "Insight Increase: " << deltaInsight << endl;; 
            } else if (tile_color == 'P') { // Pink tile
                string s1, s2;
                cout << "DNA Task 2 - Enter two DNA strands (unequal lengths allowed):\n";
                cin >> s1 >> s2;
                deltaDiscovery += static_cast<int>(bestStrandMatch(s1, s2) * 1000);
                deltaInsight += 100;
                cout << "Discovery Points Increase: " << deltaDiscovery <<endl;
                cout << "Insight Increase: " << deltaInsight << endl;
            } else if (tile_color == 'R') { // Red tile
                string s1, s2;
                cout << "DNA Task 3 - Enter input and target DNA strands:\n";
                cin >> s1 >> s2;
                identifyMutations(s1, s2);
                deltaAccuracy += 5;
                deltaDiscovery += 20;
                cout << "Accuracy Increase: " << deltaAccuracy <<endl;
                cout << "Discovery Increase: " << deltaDiscovery << endl;
            } else if (tile_color == 'T') { // Brown tile
                string s1;
                cout << "DNA Task 4 - Enter DNA strand to transcribe to RNA:\n";
                cin >> s1;
                transcribeDNAtoRNA(s1);
                deltaEfficiency += 10;
                deltaDiscovery += 10;
                cout << "Accuracy Increase: " << deltaAccuracy <<endl;
                cout << "Discovery Increase: " << deltaDiscovery << endl;
            } else if (tile_color == 'U') { // Purple tile
                deltaInsight += handleRiddle();
                deltaExperience += 50;
            }

            displayBoard();
            turnComplete = true;
            break;
        }
      
        
    }
}

return vector<int>{deltaDiscovery, deltaInsight, deltaEfficiency, deltaAccuracy, deltaExperience};
}

int Board::getPlayerPosition(int player_index)  {
    return _player_position[player_index];
}

