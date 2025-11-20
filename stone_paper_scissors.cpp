#include<iostream>
#include<cstdlib>
using namespace std;

enum enGame{stone = 1, paper = 2, scissores = 3};

int readPositiveNumber(string message){
	
	int num = 0;
	while (num <= 0){
		cout<<message;
		cin>>num;
	}
	
	return num;
}

int randomNumber(int from, int to){
	
		return rand() % (to - from + 1) + from;
}

string getChoiceText(int choice){

     switch (choice)
     {
     case enGame::stone:
        return "stone";
     case enGame::paper:
        return "paper";
     case enGame::scissores:
        return "scissores";
     
     default:
        return "wrong";
     }

}

string getWinner(int userChoice, int computerChoice, int winningTimes[3]){
    if(userChoice == computerChoice){
        winningTimes[0]++;
        return "[No Winner]\n";
    }
    else if(userChoice == enGame::paper and computerChoice == enGame::stone){
        winningTimes[1]++;
        return "[Player]\n";
    }
    else if(userChoice == enGame::stone and computerChoice == enGame::scissores){
        winningTimes[1]++;
        return "[Player]\n";
    }
    else if(userChoice == enGame::scissores and computerChoice == enGame::paper){
        winningTimes[1]++;
        return "[Player]\n";
    }
    else{
        winningTimes[2]++;
        return "[Computer]\n";
    }
}

void printRoundResult(int userChoice, int computerChoice, int round, int winningTimes[3]){
    cout<<"__________________Round["<<round<<"]__________________\n";
    cout<<"\tPlayer Choice: "<<getChoiceText(userChoice)<<endl;
    cout<<"\tComputer Choice: "<<getChoiceText(computerChoice)<<endl;
    cout<<"\tRound Winner: "<<getWinner(userChoice, computerChoice, winningTimes);
    cout<<"\t\n_____________________________________\n";
}

string finalWinner(int user, int computer){
    if(user>computer){
        return "[Player]";
    }else if(computer>user){
        return "[Computer]";
    }else{
        return "[Draw]";
    }
}

void printGameResults(int userChoices[100], int computerChoices[100],int length,int winningTimes[3]){

    cout<<"\t_______________________________________________________\n";
    cout<<"\t\t +++ Game Over +++\n";
    cout<<"\t_______________________________________________________\n";
    cout<<"\t_____________________[Game Results]_________________\n";

    cout<<"\tGame rounds: "<<length<<endl;
    cout<<"\tPlayer won times: "<<winningTimes[1]<<endl;
    cout<<"\tcomputer won times: "<<winningTimes[2]<<endl;
    cout<<"\tDraw times: "<<winningTimes[0]<<endl;
    cout<<"\tFinal winner is: "<<finalWinner(winningTimes[1], winningTimes[2])<<endl;
}
void readChoices(int userChoices[100],int computerChoices[100],int length, int winningTimes[3]){
    
    int userChoice;
    for(int i=0; i<length; i++){
        cout<<"  Round ["<<i + 1<<"] begins: \n";
        cout<<"Your choice: [1]:stone, [2]:paper [3]:scissores? ";
        cin>>userChoice;
        if(getChoiceText(userChoice) == "wrong"){
            i--;
            cout<<"wrong choice try again!\n";
            continue;
        }

        userChoices[i] = userChoice;
        computerChoices[i] = randomNumber(1,3);
        printRoundResult(userChoice, computerChoices[i], i+1, winningTimes);
    }
}

void startGame(){

    char playAgain = 'y';
    int length = 0, rounds = 0;
    int userChoices [100];
    int computerChoices [100];
    int winningTimes [3] = {0,0,0};
	
    do{
        rounds += length = readPositiveNumber("How many rounds the game will be: ");
        readChoices(userChoices, computerChoices, length, winningTimes);
        cout<<"Do you want to play again(y,n): ";
        cin>>playAgain;
    }
    while(playAgain == 'Y' || playAgain == 'y');
    printGameResults(userChoices, computerChoices, rounds, winningTimes);
}

int main(){
	srand((unsigned)time(NULL));

	startGame();

	return 0;
}
