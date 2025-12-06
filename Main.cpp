#include "Board.h"
#include "Character.h"
#include "Event.h"
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
    int turnActions;

while(!game.GameFinished()){ 
     if(playerOneTurn){
        cout << player1.getPlayerName() << " Choose 0 to see character summary" << endl; 
        cout << player1.getPlayerName() << " Choose 1 to roll the dice" << endl; 
        cin >>  turnActions; 
        if(turnActions == 0){
         player1.printSummary();
         cout << player1.getPlayerName() << " Choose 1 to roll the dice" << endl;
            cin >> turnActions;  
    }
        if(turnActions == 1){
            game.playerTurn(player1.getPlayerIndex(), player1.getPlayerName());
    
        
        }
    playerOneTurn = !playerOneTurn;
    }
        //player two turn
    else { // Player 2 turn
    cout << player2.getPlayerName() << " Choose 0 to see character summary" << endl; 
    cout << player2.getPlayerName() << " Choose 1 to roll the dice" << endl; 
    int turnActions;
    cin >> turnActions;
    if(turnActions == 0){
        player2.printSummary();
        cout << player2.getPlayerName() << " Choose 1 to roll the dice" << endl;
        cin >> turnActions;
    }
    if(turnActions == 1){
        game.playerTurn(player2.getPlayerIndex(), player2.getPlayerName());
    }
    playerOneTurn = !playerOneTurn;
}

}
    std::cout << "Both scientists have reached the Genome Conference" << endl;  
    player1.convertTraitsToDiscoveryPoints(); 
    player2.convertTraitsToDiscoveryPoints();

    if(player1.convertTraitsToDiscoveryPoints() > player2.convertTraitsToDiscoveryPoints()){
        cout << player1.getPlayerName() << " is your Lead Genomicist with " << player1.convertTraitsToDiscoveryPoints() << " Discovery Points" << endl;
        player1.printSummary();
    }
    else{
        cout << player2.getPlayerName() << " is your Lead Genomicist with " <<  player2.convertTraitsToDiscoveryPoints() << " Discovery Points" << endl;
       
    }
    return 0;

}