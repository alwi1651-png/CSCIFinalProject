#include "Board.h"
#include "Characters.h"
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

void LoadCharacters(string filename, Characters characters[],int size){
        ifstream file(filename);
        if(file.fail()){
            cout << "File could not open" << endl;
        }
        string line;
        getline(file,line); //skips the first line
        for(int i = 0; i < size; i++){
        string _name, _exp, _acc, _eff, _ins, _dps;
        getline(file, _name, '|');
        getline(file, _exp, '|');
        getline(file, _acc, '|');
        getline(file, _eff, '|');
        getline(file, _ins, '|');
        getline(file, _dps); // end of line
int exp = stoi(_exp);
int acc = stoi(_acc);
int eff = stoi(_eff);
int ins = stoi(_ins);
int dps = stoi(_dps);

characters[i] = Characters(_name, exp, acc,eff,ins,dps);
        }
        file.close();
    }
int main() {
    srand(time(0)); // Makes sure the board is random
    Board game; // set instance
    game.initializeBoard();
    game.displayBoard();
    cout << endl; 
    Characters characters[5]; 
    LoadCharacters("characters.txt", characters, 5); 
     for (int i = 0; i < 5; i++) {
        cout << characters[i].getplayerName() << endl;
        cout << "Experience: " << characters[i].getExperience() << endl;
        cout << "Accuracy: " << characters[i].getAccuracy() << endl;
        cout << "Efficiency" << characters[i].getEfficiency() << endl;
        cout << "Insight: " << characters[i].getInsight() << endl;
        cout << "Discovery Points: " << characters[i].getDiscoveryPoints() << endl;
        cout << endl;
    }
    string player1, player2;
cout << "Player 1: Choose a Character:" << endl;
getline(cin, player1);
cout << endl; 
cout << "Player 2: Choose a Character:" << endl;
getline(cin, player2);
if(player1 == player2){
    cout << "That Character is Already Taken. Please Select a New Character." << endl;
    getline(cin, player2);
}
cout << "Choose 0 for the Training Fellowship Track" << endl;
cout << "Choose 1 for Direct Lab Assignment" << endl; 
int player1track, player2track;
cout << player1 << " Choose your Track:"; 
cin >> player1track; 
if(player1track < 0 || player1track > 1){
    cout << "Choose a Valid Track" << endl;
    cin >> player1track;
}
cout << player2 << " Choose your Track:"; 
cin >> player2track;

if(player2track < 0 || player2track > 1){
    cout << "Choose a Valid Track" << endl;
    cin >> player2track;
}

cout << player1 << " is on Track " << player1track << endl; 
cout << player2 << " is on Track " << player2track << endl; 

game.displayTrack(player1track);
game.displayTrack(player2track);


int turn = 0; //Player 1 
int steps = 0;  
bool player1Finished = false; 
bool player2Finished = false; 
while(!GameEnd(game.getPlayerPosition(0)) || !GameEnd(game.getPlayerPosition(1))){ 
    if(turn == 0){
        if(player1Finished == true){
            cout << player1 << " has reached the Genome Conference" << endl; 
        }
    else{
    steps = Spinner();
    game.movePlayer(turn, steps);
    int position = game.getPlayerPosition(turn);
    game.displayBoard();
    cout << endl; 
        if(game.getPlayerPosition(0) == 51){
            cout << player1 << " has reach the Genome Conference" << endl; 
        }
        else{ cout << player1 << " is on square " << game.getPlayerPosition(0) << endl;

        }
    }
}
    if(turn == 1){
        if(player2Finished == true){
            cout << player2 << " has reached the Genome Conference" << endl; 
        }
    else{
    steps = Spinner();
    game.movePlayer(turn, steps);
    int position = game.getPlayerPosition(turn);
    game.displayBoard();
    cout << endl; 
        if(game.getPlayerPosition(1) == 51){
            cout << player2 << " has reach the Genome Conference" << endl; 
        }
        else{
            cout << player2 << " is on square " << game.getPlayerPosition(1) << endl;
        }
    }
}
    turn = (turn + 1) % 2; 
    } 
cout << "Both scientists have reached the Genome Conference"; 

return 0;

}
