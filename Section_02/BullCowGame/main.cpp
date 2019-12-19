/* This is the console executable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame class.
*/

#include <iostream>
#include <string>	
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();

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
	std::cout << "Czy bêdziesz godzien do³¹czyæ do stada i odgadniesz wyraz sk³adaj¹cy siê z " << BCGame.GetHiddenWordLength();
	std::cout << " liter?\n";
	std::cout << std::endl;
	return;
}


void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loop for the number of turns asking for guesses
	for (int32 count = 1; count <= MaxTries; count++) { // TODO change from FOR to WHILE
		FText Guess = GetValidGuess();

		// submit valid guess to the game, receive counts
		FBullCowCount BullCowCount = BCGame.SubmitGuess(Guess);

		std::cout << "Gêsi = " << BullCowCount.Bulls;
		std::cout << "|| Kaczki = " << BullCowCount.Cows << "\n\n";
	}

	// TODO summarise game
}

// loop until the user gives a valid guess
FText GetValidGuess()
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		// get player's guess
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Próba " << CurrentTry << ". Wstaw swoj¹ propozycjê: ";
		FText Guess = "";
		std::getline(std::cin, Guess);

		// check status and give feedback
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Nie umiesz liczyæ? Wstaw " << BCGame.GetHiddenWordLength() << " literowe s³owo.\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "PATA£ACHU! Litery w s³owie nie mog¹ siê powtarzaæ.\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "BEBOKU! Pisz ma³ymi literami!\n";
			break;
		default:
			return Guess;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK); // keep looping until we get no errors
}

bool AskToPlayAgain()
{
	std::cout << "Jesteœ tylko zwyk³¹ kur¹... Nie jesteœ godzien do³¹czyæ do stada. Chcesz spróbowaæ ponownie? (t/n) ";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 't') || (Response[0] == 'T');
}