#include <iostream>
#include <string>

using namespace std;

void PrintIntro();
string GetGuessAndPrintBack();

//entry point
int main()
{
	PrintIntro();

	// looping turns
	constexpr int NUMBER_OF_TURNS = 5;
	for (int count = 1; count <= NUMBER_OF_TURNS; count++)
	{
		GetGuessAndPrintBack();
		cout << endl;
	}

	return 0;
}

void PrintIntro() 
{
	constexpr int WORD_LENGTH = 5;
	cout << "Welcome to Bulls and Cows, a fun word game.\n";
	cout << "Can you guess the " << WORD_LENGTH;
	cout << " letter isogram I'm thinking of?\n";
	cout << endl;
	return;
}

//player's guess
string GetGuessAndPrintBack() 
{
	//introduction
	cout << "Enter your guess: ";
	string Guess = "";
	getline(cin, Guess);

	//print guess back to player
	cout << "Your guess was: " << Guess << endl;
	return Guess;
}