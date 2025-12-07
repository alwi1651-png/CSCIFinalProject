// Group Project With Alex Wilson and Mason Paprzycki
#include "Board.h"
#include "Character.h"
#include "Event.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>

using namespace std; 

vector<Character> rankPlayers(vector<Character> players) {
    int n = players.size();

    // Bubble sort players by Discovery Points (descending)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (players[j].convertTraitsToDiscoveryPoints() < players[j + 1].convertTraitsToDiscoveryPoints()) {
                swap(players[j], players[j + 1]);
            }
        }
    }

    return players;
}

int main() {
    std::cout << "Welcome to the Genome Quest!\n";
    std::cout << "Player One Registration:\n";
    Character player1(0); // create player one with player index 0
    std::cout << "Player Two Registration:\n";
    Character player2(1); // create player two with player index 1
    vector<Character> players = {player1, player2};
    
    srand(time(0)); // Makes sure the board is random
    vector<bool> isFellowship = {player1.getIsFellowship(), player2.getIsFellowship()};
    Board game(isFellowship); // set instance
    game.initializeBoard();
    game.displayBoard();
    cout << endl; 

    int turn = 0; // Player 1 
    int steps = 0;  
    bool player1Finished = false; 
    bool player2Finished = false; 
    bool playerOneTurn = true;
    int turnActions;

    while (!game.GameFinished()) { 

        if (playerOneTurn) {
            vector<int> statsDelta = game.playerTurn(
                player1.getPlayerIndex(),
                player1.getPlayerName(),
                player1.getCharacterName(),
                player1.getCharacterDiscoveryPoints(),
                player1.getCharacterInsight(),
                player1.getCharacterEfficiency(),                
                player1.getCharacterAccuracy(),
                player1.getCharacterExperience());

            // update player stats
            player1.addDiscoveryPoints(statsDelta[0]);
            player1.addInsight(statsDelta[1]);
            player1.addEfficiency(statsDelta[2]);
            player1.addAccuracy(statsDelta[3]);
            player1.addExperience(statsDelta[4]);

            playerOneTurn = !playerOneTurn;
        }
        else { 
            vector<int> statsDelta = game.playerTurn(
                player2.getPlayerIndex(),
                player2.getPlayerName(),
                player2.getCharacterName(),
                player2.getCharacterDiscoveryPoints(),
                player2.getCharacterInsight(),
                player2.getCharacterEfficiency(),
                player2.getCharacterAccuracy(),
                player2.getCharacterExperience());

            player2.addDiscoveryPoints(statsDelta[0]);
            player2.addInsight(statsDelta[1]);
            player2.addEfficiency(statsDelta[2]);
            player2.addAccuracy(statsDelta[3]);
            player2.addExperience(statsDelta[4]);

            playerOneTurn = !playerOneTurn;
        }
    }

    std::cout << "Both scientists have reached the Genome Conference" << endl;  
    std::cout << std::endl; 
    player1.printSummary();
    std::cout << std::endl; 
    player2.printSummary();
    std::cout << std::endl; 

    // Rank players and display leaderboard
    vector<Character> sortedPlayers = rankPlayers(players);

    cout << "\n--- Final Leaderboard ---\n";
    for (int i = 0; i < sortedPlayers.size(); i++) {
        cout << i + 1 << ". " 
             << sortedPlayers[i].getPlayerName() 
             << " (" << sortedPlayers[i].convertTraitsToDiscoveryPoints() 
             << " Discovery Points)\n";
    }

    cout << "\nLead Genomicist: " 
         << sortedPlayers[0].getPlayerName() 
         << " with " 
         << sortedPlayers[0].convertTraitsToDiscoveryPoints() 
         << " Discovery Points!\n";

    return 0;
}
