/* This is the console executable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame class.
*/
#pragma once

#include <iostream>
#include <string>	
#include "FBullCowGame.h"

//Unreal friendly names
using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; // new game instance

// entry point
int main()
{
	setlocale(LC_ALL, "pl_PL");
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);

	return 0; // exit app
}


// introduction
void PrintIntro()
{
	std::cout << "Witaj w g�siach i kaczkach! Fantastycznej grze s�ownej.\n";
	std::cout << std::endl;
	std::cout << "               ..  " << std::endl;
	std::cout << "              ( '`<" << std::endl;
	std::cout << "               )(               ,_" << std::endl;
	std::cout << "        ( ----'  '.     ,      ( o <" << std::endl;
	std::cout << "        (         ;    {`'=, ___) (" << std::endl;
	std::cout << "         (_______,'     \  ,_.-   )" << std::endl;
	std::cout << "    ~^~^~^~^~^~^~^~^~^~^~~^~^~^~^~^~^~^~" << std::endl;
	std::cout << "Czy b�dziesz godzien do��czy� do stada i odgadniesz wyraz sk�adaj�cy si� z " << BCGame.GetHiddenWordLength();
	std::cout << " liter?\n";
	std::cout << std::endl;
	return;
}

// plays a single complete game
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loop asking for guesses while the game is NOT won
	// and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		FText Guess = GetValidGuess();

		// submit valid guess to the game, receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "G�si = " << BullCowCount.Bulls;
		std::cout << " || Kaczki = " << BullCowCount.Cows << "\n\n";
	}

	PrintGameSummary();
	return;
}

// loop until the user gives a valid guess
FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		// get player's guess
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Pr�ba " << CurrentTry << " z " << BCGame.GetMaxTries();
		std::cout << " Wpisz swoj� propozycj�: ";

		std::getline(std::cin, Guess);

		// check status and give feedback
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Nie umiesz liczy�? Wstaw " << BCGame.GetHiddenWordLength() << " literowe s�owo.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "PATA�ACHU! Litery w s�owie nie mog� si� powtarza�.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "BEBOKU! Pisz ma�ymi literami!\n\n";
			break;
		default:
			// assume the guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK); // keep looping until we get no errors
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Chcesz spr�bowa� ponownie? (t/n) ";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 't') || (Response[0] == 'T');
}

void PrintGameSummary() {
	if (BCGame.IsGameWon()) {
		std::cout << "GRATULACJE! Mo�esz by� cz�ci� stada! Prawdziwy z Ciebie indyk!\n";
	}
	else {
		std::cout << "Pff... Jeste� tylko zwyk�� kur�...\n";
		std::cout << "     _   m" << std::endl;
		std::cout << "   ,`.} /'>" << std::endl;
		std::cout << "   (` }<_/" << std::endl;
		std::cout << "     `<<" << std::endl;
	}
}