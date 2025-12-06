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
Board::Board(bool p1, bool p2)
    : playerOnePath(p1), playerTwoPath(p2){

    _player_count = _MAX_PLAYERS;

    for (int i = 0; i < _player_count; i++) {
        _player_position[i] = 0;
        _player_board_assignment[i] = 0;   // default
    }

    initializeBoard();
}


//We looked up how to do this
int Spinner() {
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
    setPlayerRole(0, playerOnePath);
    setPlayerRole(1, playerTwoPath);
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

void greenTileTurn(const std::string filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::vector<Event> events;
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        Event e;
        std::string token;

        if (!std::getline(ss, token, '|')) continue;
        e.description = token;

        if (!std::getline(ss, token, '|')) continue;
        e.pathType = std::stoi(token);

        if (!std::getline(ss, token, '|')) continue;
        e.advisor = std::stoi(token);

        if (!std::getline(ss, token, '|')) continue;
        e.discoveryPoints = std::stoi(token);

        events.push_back(e);
    }

    std::cout << "Read " << events.size() << " events from " << filename << std::endl;
}


void Board::playerTurn(int player_index, std::string playerName) {
    if (playerFinished(player_index)) {
        std::cout << playerName << " has reached the Genome Conference!" << std::endl;
        return;
    }

    // Roll dice
    int steps = Spinner();
    movePlayer(player_index, steps);
    std::cout << playerName << " rolled a " << steps << std::endl;

    // Get current position
    int position = getPlayerPosition(player_index);
    int board_index = _player_board_assignment[player_index];

    std::cout << playerName << " is on square " << position << std::endl;

    // Check tile color
    char tile_color = _tiles[board_index][position].color;

    if (tile_color == 'G') { // Green tile
        // 50-50 chance for an event
        if (rand() % 2 == 0) {
            std::cout << "Green tile event triggered!\n";

            // Read events from file
            std::vector<Event> events = greenTileTurn("riddles.txt");
            if (!events.empty()) {
                int idx = rand() % events.size();       // Pick random event
                Event e = events[idx];
                std::cout << "Event: " << e.description 
                          << " | Discovery Points: " << e.discoveryPoints << std::endl;

                // Update player discovery points
                // Assuming Character has addDiscoveryPoints(int)
                if (player_index == 0) {
                    _player_one_obj.addDiscoveryPoints(e.discoveryPoints);
                } else {
                    _player_two_obj.addDiscoveryPoints(e.discoveryPoints);
                }
            }
        } else {
            std::cout << "Nothing happens on this green tile.\n";
        }
    }

    

    // Display board after move
    displayBoard();
}


