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
	std::cout << "Witaj w gêsiach i kaczkach! Fantastycznej grze s³ownej.\n";
	std::cout << std::endl;
	std::cout << "               ..  " << std::endl;
	std::cout << "              ( '`<" << std::endl;
	std::cout << "               )(               ,_" << std::endl;
	std::cout << "        ( ----'  '.     ,      ( o <" << std::endl;
	std::cout << "        (         ;    {`'=, ___) (" << std::endl;
	std::cout << "         (_______,'     \  ,_.-   )" << std::endl;
	std::cout << "    ~^~^~^~^~^~^~^~^~^~^~~^~^~^~^~^~^~^~" << std::endl;
	std::cout << "Czy bêdziesz godzien do³¹czyæ do stada i odgadniesz wyraz sk³adaj¹cy siê z " << BCGame.GetHiddenWordLength();
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

		std::cout << "Gêsi = " << BullCowCount.Bulls;
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
		std::cout << "Próba " << CurrentTry << " z " << BCGame.GetMaxTries();
		std::cout << " Wpisz swoj¹ propozycjê: ";

		std::getline(std::cin, Guess);

		// check status and give feedback
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Nie umiesz liczyæ? Wstaw " << BCGame.GetHiddenWordLength() << " literowe s³owo.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "PATA£ACHU! Litery w s³owie nie mog¹ siê powtarzaæ.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "BEBOKU! Pisz ma³ymi literami!\n\n";
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
	std::cout << "Chcesz spróbowaæ ponownie? (t/n) ";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 't') || (Response[0] == 'T');
}

void PrintGameSummary() {
	if (BCGame.IsGameWon()) {
		std::cout << "GRATULACJE! Mo¿esz byæ czêœci¹ stada! Prawdziwy z Ciebie indyk!\n";
	}
	else {
		std::cout << "Pff... Jesteœ tylko zwyk³¹ kur¹...\n";
		std::cout << "     _   m" << std::endl;
		std::cout << "   ,`.} /'>" << std::endl;
		std::cout << "   (` }<_/" << std::endl;
		std::cout << "     `<<" << std::endl;
	}
}