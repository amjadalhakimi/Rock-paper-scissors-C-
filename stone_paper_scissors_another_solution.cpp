#include<iostream>
#include<cstdlib>
using namespace std;

enum enGameChoice {Stone = 1, Paper = 2, Scissores = 3};

enum enWinner {Player = 1, Computer = 2, Draw = 3};

struct stRoundInfo{
    short RoundNumber = 0;
    enGameChoice PlayerChoice;
    enGameChoice ComputerChoice;
    enWinner Winner;
    string WinnerName;
};

struct stGameResults{

    short GameRounds = 0;
    short PlayerWinTimes = 0;
    short ComputerWinTimes = 0;
    short DrawTimes = 0;
    
    enWinner GameWinner;
    string WinnerName = "";
};

void ResetScreen(){
    system("cls");
    system("color 0F");
}

enGameChoice ReadPlayerChoice(){
    short Choice = 1;

    do{
        cout<<"\nYour Choice: [1]:Stone, [2]:Paper, [3]Scissores? ";
        cin>>Choice;

    }while(Choice < 1 || Choice > 3);

    return (enGameChoice) Choice;
}

int randomNumber(int from, int to){
	
		return rand() % (to - from + 1) + from;
}

enGameChoice ReadComputerChoice(){
    
    return (enGameChoice) randomNumber(1,3);
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo){
    if(RoundInfo.PlayerChoice == RoundInfo.ComputerChoice){
        return enWinner::Draw;
    }
    switch (RoundInfo.PlayerChoice)
    {
    case enGameChoice::Stone:
        if(RoundInfo.ComputerChoice == enGameChoice::Paper)
        return enWinner::Computer;
    case enGameChoice::Paper:
        if(RoundInfo.ComputerChoice == enGameChoice::Scissores)
        return enWinner::Computer;
    case enGameChoice::Scissores:
        if(RoundInfo.ComputerChoice == enGameChoice::Stone)
        return enWinner::Computer;
    
    default:
        return enWinner::Player;
    }
}

string WinnerName(enWinner Winner){
    string arrWinnerName[3] = {"Player", "Computer", "No Winner"};
    return arrWinnerName[Winner -1];
}

string ChoiceName(enGameChoice Choice){
    string arrGameChoices[3] = {"Stone", "Paper", "Scissores"};
    return arrGameChoices[Choice -1];
}

void PrintRoundResults(stRoundInfo RoundInfo){

    cout<<"__________________Round["<<RoundInfo.RoundNumber<<"]__________________\n";
    cout<<"\tPlayer Choice: "<<ChoiceName(RoundInfo.PlayerChoice)<<endl;
    cout<<"\tComputer Choice: "<<ChoiceName(RoundInfo.ComputerChoice)<<endl;
    cout<<"\tRound Winner: "<<RoundInfo.WinnerName;
    cout<<"\n_________________________\n"<<endl;
}

enWinner WhoWonTheGame(short PlayerWinTimes, short ComputerWinTimes){
    if(PlayerWinTimes > ComputerWinTimes){
        return enWinner::Player;
    }else if(ComputerWinTimes > PlayerWinTimes){
        return enWinner::Computer;
    }else{
        return enWinner::Draw;
    }
}

stGameResults FillGameResults(short rounds, short PlayerWinTimes, short ComputerWinTimes, short DrawTimes){
    
    stGameResults GameResults;

    GameResults.GameRounds = rounds;
    GameResults.PlayerWinTimes = PlayerWinTimes;
    GameResults.ComputerWinTimes = ComputerWinTimes;
    GameResults.DrawTimes = DrawTimes;
    GameResults.GameWinner = WhoWonTheGame(PlayerWinTimes, ComputerWinTimes);
    GameResults.WinnerName = WinnerName(GameResults.GameWinner);

    return GameResults;
}

stGameResults PlayGame(short rounds){

    stRoundInfo RoundInfo;
    short PlayerWinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0; 

    for(short GameRound = 1; GameRound <= rounds; GameRound++){
        cout<<"\nRound["<<GameRound<<"] begins:\n";
        RoundInfo.RoundNumber = GameRound;
        RoundInfo.PlayerChoice = ReadPlayerChoice();
        RoundInfo.ComputerChoice = ReadComputerChoice();
        RoundInfo.Winner = WhoWonTheRound(RoundInfo);
        RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

        if(RoundInfo.Winner == enWinner::Player){
            PlayerWinTimes++;
        }else if(RoundInfo.Winner == enWinner::Computer){
            ComputerWinTimes++;
        }else{
            DrawTimes++;
        }

        PrintRoundResults(RoundInfo);
    }
    return FillGameResults(rounds, PlayerWinTimes, ComputerWinTimes, DrawTimes);
}

short ReadHowManyRounds(){
    short GameRounds = 0;
    do{
        cout<<"How many rounds 1 to 10? ";
        cin>>GameRounds;
    }while(GameRounds < 1 || GameRounds > 10);

    return GameRounds;
}

string Tabs(short NumberOfTabs){
    string t = "";
    for(int i=1; i<=NumberOfTabs; i++){
        t += "\t";
    }

    return t;
}

void ShowGameOverScreen(){
    cout<<Tabs(2)<<"_______________________________________________________\n";
    cout<<Tabs(2)<<"                  +++ Game Over +++\n";
    cout<<Tabs(2)<<"_______________________________________________________\n";
}

void SetWinnerScreenColor(enWinner Winner){
    switch (Winner)
    {
    case enWinner::Player:
        system("color 2F");
    case enWinner::Computer:
        system("color 4F");
        cout<<"\a";
    default:
        system("color 6F");
    }
}

void ShowFinalGameResults(stGameResults GameResults){

    cout<<Tabs(2)<<"_____________________[Game Results]_________________\n\n";
    cout<<Tabs(2)<<"Game Rounds         :"<<GameResults.GameRounds<<endl;
    cout<<Tabs(2)<<"Player Won Times    :"<<GameResults.PlayerWinTimes<<endl;
    cout<<Tabs(2)<<"Computer Won Times  :"<<GameResults.ComputerWinTimes<<endl;
    cout<<Tabs(2)<<"Draw Times          :"<<GameResults.DrawTimes<<endl;
    cout<<Tabs(2)<<"Final Winner        :"<<GameResults.WinnerName<<endl;
    cout<<Tabs(2)<<"____________________________________________________\n\n";

    SetWinnerScreenColor(GameResults.GameWinner);    
}

void StartGame(){
    char PlayAgain = 'Y';
    do{
        ResetScreen();
        stGameResults GameResults = PlayGame(ReadHowManyRounds());
        ShowGameOverScreen();
        ShowFinalGameResults(GameResults);

        cout<<endl<<Tabs(3)<<"Do you want to play again? Y/N? ";
        cin>>PlayAgain;
    }while(PlayAgain == 'Y' || PlayAgain == 'y');
}

int main(){

    StartGame();
    return 0;
}
