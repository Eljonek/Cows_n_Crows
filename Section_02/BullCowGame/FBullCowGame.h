#pragma once
#include <string>

class FBullCowGame
{
public:
	int GetMaxTries() const;
	int GetCurrentTry() const;
	bool IsGameWon() const;

	void Reset(); // TODO
	bool CheckGuessValidity(std::string); // TODO



// Ignore
private:
	int MyCurrentTry = 1;
	int MyMaxTries = 5;
};