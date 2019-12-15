#include <iostream>
#include <string>

using namespace std;

void PrintIntro();
string GetGuessAndPrintBack();

// entry
int main()
{
	PrintIntro();

	//loop for the numbers of turns
	constexpr int NUMBER_OF_TURNS = 5;
	for (int count = 1; count <= NUMBER_OF_TURNS; count++)
	{
		GetGuessAndPrintBack();
		cout << endl;
	}

	cout << endl;
	return 0;
}

//introduction
void PrintIntro() {
	constexpr int WORD_LENGHT = 9;
	cout << "Witaj w Bykach i Krowach, zabawnej grze s�ownej.\n";
	cout << "Czy odgadniesz s�owo, na " << WORD_LENGHT;
	cout << "liter, izogram, o kt�rym my�l�?\n";
	cout << endl;
	return;
}


string GetGuessAndPrintBack();
{
	//player's guess
	cout << "Wpisz swoj� propozycj� ";
	string Guess = " ";
	getline(cin, Guess);

	//print the guess back
	cout << "Twoja odpowied�: " << Guess << endl;
	return Guess;
}