#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); } //default constructor

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const {
	TMap<int32, int32> WordLengthToMaxTries{ {3,6}, {4,8}, {5,10}, {6,12}, {7,14} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "jab³ko";
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}


EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) { // guess is not an isogram
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess)) { // guess is not lowercase
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength()) { // wrong guess length 
		return EGuessStatus::Wrong_Length;
	}
	else {
		return EGuessStatus::OK;
	}
}


// receives a VALID guess, increments turn and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	// increment the turn #
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // assuming same length as guess

	// loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
		// compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++) {
			// if they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
				if (MHWChar == GChar) { // if they're in the same place
					BullCowCount.Bulls++; // increment bulls
				}
				else {
					BullCowCount.Cows++; // must be a cow
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength) { 
		bGameIsWon = true; 
	}
	else { 
		bGameIsWon = false; 
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const {

	// treat 0/1 letter words isograms
	if (Word.length() <= 1) { return true; }
	
	TMap<char, bool> LetterSeen; // setup the map
	for (auto Letter : Word) {   // for all letters of the word
		Letter = tolower(Letter);	// handle mixed cases
		if (LetterSeen[Letter]) {	// if the letter is in the map
			return false;			// we DON'T have isogram
		}
		else {
			LetterSeen[Letter] = true;		//add the letter to the map
		}
	}

	return true; //in case /0 is entered
}

bool FBullCowGame::IsLowercase(FString Word) const {
	for (auto Letter : Word) {
		if (!islower(Letter)) { //if not a lowercase
			return false;
		}
	}
	return true;
}