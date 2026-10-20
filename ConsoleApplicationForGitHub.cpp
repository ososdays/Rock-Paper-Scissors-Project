#include <iostream>
using namespace std;
enum enGameChoice { Stone = 1, Paper = 2, Scissor = 3 };
enum enWinner { Player1 = 1, Computer = 2, Draw = 3 };
struct stGameResults
{
	short GameRounds = 0;
	short Player1WinTimes = 0;
	short ComputerWinTimes = 0;
	short DrawTimes = 0;
	enWinner GameWinner;
	string WinnerName;
};
struct stRoundInfo
{
	short RoundNumber = 0;
	enGameChoice Player1Choice;
	enGameChoice ComputerChoice;
	enWinner RoundWinner;
	string WinnerName = "";

};
int RandomNumber(int From, int To)
{
	int Number = rand() % (To - From + 1) + From;
	return Number;
}
int ReadHowManyRounds()
{
	int Rounds = 1;
	do
	{
		cout << "Enter How many rounds [1-10] ? ";
		cin >> Rounds;
	} while (Rounds < 1 || Rounds>10);
	return Rounds;
}
enGameChoice ReadPlayer1Choice()
{
	int ChoiceNumber = 0;
	cout << "Your choice [1] Stone [2] Paper [3] Scissor ? ";
	cin >> ChoiceNumber;
	return enGameChoice(ChoiceNumber);
}
enGameChoice GetComputerChoice()
{
	return enGameChoice(RandomNumber(1, 3));
}
enWinner WhoWinTheRound(stRoundInfo RoundInfo)
{
	if (RoundInfo.Player1Choice == RoundInfo.ComputerChoice)
		return enWinner::Draw;

	switch (RoundInfo.Player1Choice)
	{
	case enGameChoice::Paper:
		if (RoundInfo.ComputerChoice == enGameChoice::Stone)
		{
			return enWinner::Player1;
		}
		break;
	case enGameChoice::Scissor:
		if (RoundInfo.ComputerChoice == enGameChoice::Paper)
		{
			return enWinner::Player1;
		}
		break;
	case enGameChoice::Stone:
		if (RoundInfo.ComputerChoice == enGameChoice::Scissor)
		{
			return enWinner::Player1;
		}
		break;
	}
	return enWinner::Computer;
}
string WinnerName(enWinner Winner)
{
	string ArrWinnerName[3] = { "Player1","Computer","Draw" };
	return ArrWinnerName[Winner - 1];
}
string ChoiceName(enGameChoice GameChoice)
{
	string Arr[3] = { "Stone","Paper","Scissor" };
	return Arr[GameChoice - 1];
}
void ChangeScreenColor(enWinner Winner)
{
	switch (Winner)
	{
	case enWinner::Player1:
		system("color 2f");
		break;
	case enWinner::Computer:
		system("color 4f");
		cout << "\a";
		break;
	case enWinner::Draw:
		system("color 6f");
		break;
	}

}
void PrintRoundResult(stRoundInfo RoundInfo)
{
	cout << "\n__________Round [" << RoundInfo.RoundNumber << "] ____________\n\n";
	cout << "Player1 Choice  : " << ChoiceName(RoundInfo.Player1Choice) << endl;
	cout << "Computer Choice : " << ChoiceName(RoundInfo.ComputerChoice) << endl;
	cout << "Round Winner    : " << RoundInfo.WinnerName << endl;
	cout << "_________________________________________\n";
	ChangeScreenColor(RoundInfo.RoundWinner);
}
enWinner WhoWinTheGame(stGameResults GameResults)
{
	if (GameResults.Player1WinTimes > GameResults.ComputerWinTimes)
		return enWinner::Player1;
	else if (GameResults.Player1WinTimes < GameResults.ComputerWinTimes)
		return enWinner::Computer;
	else return enWinner::Draw;
}
stGameResults FillGameResults(int HowManyRounds, int Player1WinTimes, int ComputerWinTimes, int DrawTimes)
{
	stGameResults GameResults;
	GameResults.GameRounds = HowManyRounds;
	GameResults.Player1WinTimes = Player1WinTimes;
	GameResults.ComputerWinTimes = ComputerWinTimes;
	GameResults.DrawTimes = DrawTimes;
	GameResults.GameWinner = WhoWinTheGame(GameResults);
	GameResults.WinnerName = WinnerName(GameResults.GameWinner);
	return GameResults;
}
stGameResults PlayGame(int HowManyRounds)
{
	stRoundInfo RoundInfo;
	int Player1WinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;
	for (int Round = 1;Round <= HowManyRounds;Round++)
	{
		cout << "\nRound [" << Round << "] begains : \n\n";
		RoundInfo.RoundNumber = Round;
		RoundInfo.Player1Choice = ReadPlayer1Choice();
		RoundInfo.ComputerChoice = GetComputerChoice();
		RoundInfo.RoundWinner = WhoWinTheRound(RoundInfo);
		RoundInfo.WinnerName = WinnerName(RoundInfo.RoundWinner);


		if (RoundInfo.RoundWinner == enWinner::Player1)
			Player1WinTimes++;
		else if (RoundInfo.RoundWinner == enWinner::Computer)
			ComputerWinTimes++;
		else
			DrawTimes++;
		PrintRoundResult(RoundInfo);

	}
	return FillGameResults(HowManyRounds, Player1WinTimes, ComputerWinTimes, DrawTimes);


}
string Tabs(int N)
{
	string t = "";
	for (int i = 0;i < N;i++)
	{
		t += "\t";
	}
	return t;
}

void ShowGameOverScreen()
{
	cout << endl << Tabs(3) << "______________________________________________________________\n";
	cout << Tabs(3) << "                    +++ Game Over +++ \n";
	cout << Tabs(3) << "______________________________________________________________\n\n";

}
void ShowGameResults(stGameResults GameResults)
{
	cout << Tabs(3) << "_____________________[ Game Results ]_________________________\n";
	cout << Tabs(3) << "Game Rounds        : " << GameResults.GameRounds << endl;
	cout << Tabs(3) << "Player1 Won Times  : " << GameResults.Player1WinTimes << endl;
	cout << Tabs(3) << "Computer Won Times : " << GameResults.ComputerWinTimes << endl;
	cout << Tabs(3) << "Draw Times         : " << GameResults.DrawTimes << endl;
	cout << Tabs(3) << "Final Winner       : " << GameResults.WinnerName << endl;
	cout << Tabs(3) << "______________________________________________________________\n";

}
void ResetScreen()
{
	system("cls");
	system("color 0f");
}
void StartGame()
{
	char PlayMore = 'Y';
	do
	{
		ResetScreen();
		stGameResults GameResults = PlayGame(ReadHowManyRounds());
		ShowGameOverScreen();
		ShowGameResults(GameResults);
		cout << Tabs(3) << "do you want to play again [Y/N] ? ";
		cin >> PlayMore;
	} while (PlayMore == 'y' || PlayMore == 'Y');


}
int main()
{
	srand((unsigned)time(NULL));
	StartGame();






	return 0;
}