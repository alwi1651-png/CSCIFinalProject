#include "Board.h"
#include "Character.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std; 

int Spinner(){
    return rand() % 6 + 1;
}

bool GameEnd(int playerPosition){
   return playerPosition == 51;
}


int main() {
    std::cout << "Welcome to the Genome Quest!\n";
    std::cout << "Player One Registration:\n";
    Character player1;
    std::cout << "Player Two Registration:\n";
    Character player2; 
   
    srand(time(0)); // Makes sure the board is random
    Board game; // set instance
    game.initializeBoard();
    game.displayBoard();
    cout << endl; 

    int turn = 0; //Player 1 
    int steps = 0;  
    bool player1Finished = false; 
    bool player2Finished = false; 
    
    while(!GameEnd(game.getPlayerPosition(0)) || !GameEnd(game.getPlayerPosition(1))){ 
        if(turn == 0){
            if(player1Finished == true){
                cout << player1.getPlayerName() << " has reached the Genome Conference" << endl; 
            }
        else{
        steps = Spinner();
        game.movePlayer(turn, steps);
        int position = game.getPlayerPosition(turn);
        game.displayBoard();
        cout << endl; 
            if(game.getPlayerPosition(0) == 51){
                cout << player1.getPlayerName() << " has reach the Genome Conference" << endl; 
            }
            else{ cout << player1.getPlayerName() << " is on square " << game.getPlayerPosition(0) << endl;

            }
        }
    }
        if(turn == 1){
            if(player2Finished == true){
                cout << player2.getPlayerName()<< " has reached the Genome Conference" << endl; 
            }
        else{
        steps = Spinner();
        game.movePlayer(turn, steps);
        int position = game.getPlayerPosition(turn);
        game.displayBoard();
        cout << endl; 
            if(game.getPlayerPosition(1) == 51){
                cout << player2.getPlayerName() << " has reach the Genome Conference" << endl; 
            }
            else{
                cout << player2.getPlayerName() << " is on square " << game.getPlayerPosition(1) << endl;
            }
        }
    }
        turn = (turn + 1) % 2; 
        } 
    cout << "Both scientists have reached the Genome Conference"; 

    return 0;

}
