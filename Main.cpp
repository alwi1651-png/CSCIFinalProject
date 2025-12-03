#include "Board.h"
#include "Character.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>

using namespace std; 

int main() {
    std::cout << "Welcome to the Genome Quest!\n";
    std::cout << "Player One Registration:\n";
    Character player1(0); //create player one with player index 0
    std::cout << "Player Two Registration:\n";
    Character player2(1); //create player two with player index 1
    vector<Character> players = {player1, player2};
   
    srand(time(0)); // Makes sure the board is random
    Board game(player1.getIsFellowship(),player2.getIsFellowship()); // set instance
    game.initializeBoard();
    game.displayBoard();
    cout << endl; 

    int turn = 0; //Player 1 
    int steps = 0;  
    bool player1Finished = false; 
    bool player2Finished = false; 
    bool playerOneTurn =true;

    while(!game.GameFinished()){ 
        if(playerOneTurn){
            game.playerTurn(player1.getPlayerIndex(), player1.getPlayerName());
            playerOneTurn = !playerOneTurn;
        
        }
        //player two turn 
        else{
            game.playerTurn(player2.getPlayerIndex(), player2.getPlayerName());
            playerOneTurn = !playerOneTurn;
        }
    }
    std::cout << "Both scientists have reached the Genome Conference"; 
    return 0;
}