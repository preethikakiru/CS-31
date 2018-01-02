#define _CRT_SECURE_NO_DEPRECATE
#include "utilities.h"
#include <iostream>
#include <cctype>
#include <cstring>
using namespace std;

//checks to see if the character was already declared to be a star or a planet
bool isInArray(int array[], int n, int a)
{
	for (int i = 0; i < n; i++)
	{
		if (array[i] == a)
			return true;
	}
	return false;
}

int runOneRound(const char words[][MAXWORDLEN + 1], int nWords, int wordnum)
{
	//makes sure the number of words isn't less than 0
	if (nWords < 0)
	{
		return -1;
	}
	//makes sure the position isn't less than 0 or greater than/ equal to the number of words
	if ((wordnum < 0) || (wordnum >= nWords))
	{
		return -1;
	}

	int score = 1;
	//infintely asks the user for a probe word until they get the right answer
	for (;;)
	{
		char probeWord[100] = { 0 };
		cout << "Probe word: ";
		cin.getline(probeWord, 100);

		//if the length of the entered probe word is less than 4 or greater than 6 return this message
		if (strlen(probeWord) < 4 || strlen(probeWord) > 6)
		{
			cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;
			continue;
		}
		//declare a bool to check whether all the characters are all lowercase or not
		bool notLower = false;
		//go through the whole probeword to make sure they are all lower case
		for (int i = 0; i < strlen(probeWord); i++)
		{
			//if a character is not a lower case then it is false
			if (!islower(probeWord[i]))
			{
				cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;
				notLower = true;
				break;
			}
		}
		if (notLower)
		{
			continue;
		}
		//declare another bool to check to see if the probe word is in the array
		bool found = false;
		for (int i = 0; i < nWords; i++)
		{
			if (!strcmp(words[i], probeWord))
			{
				found = true;
			}
		}
		//if it is false that means it is not in the array and it returns false
		if (found == false)
		{
			cout << "I don't know that word." << endl;
			continue;
		}
		//if the probeWord is equal to the secret word return the score
		if (strcmp(probeWord, words[wordnum]) == 0)
		{
			return score;
		}
		//if the probe word is not equal to the secret word
		if (strcmp(probeWord, words[wordnum]) > 0 || strcmp(probeWord, words[wordnum]) < 0)
		{
			int stars = 0;
			int planets = 0;
			//declare two arrays
			int positionOfSecret[MAXWORDLEN] = { -1, -1, -1, -1, -1, -1 };
			int positionOfProbe[MAXWORDLEN] = { -1, -1, -1, -1, -1, -1 };
			//declare an integer
			int x = 0;
			//finds the stars
			for (int i = 0; i < strlen(probeWord); i++)
			{
				if (probeWord[i] == words[wordnum][i])
				{
					stars++;
					positionOfSecret[x] = i;
					positionOfProbe[x] = i;
					x++;
				}
			}
			//find the planets
			//go through the secret word
			for (int k = 0; k < strlen(words[wordnum]); k++)
			{
				//goes through the probe word
				for (int j = 0; j < strlen(probeWord); j++)
				{
					//checks to see if planets are valid
					if (probeWord[j] == words[wordnum][k])
					{
						if (isInArray(positionOfProbe, MAXWORDLEN, j) || isInArray(positionOfSecret, MAXWORDLEN, k))
							continue;
						else
						{
							//declares the planets
							planets++;
							positionOfSecret[x] = k;
							positionOfProbe[x] = j;
							x++;
						}
					}
				}
			}
			//score goes up everytime you attempt to enter a valid probe word
			score++;
			//return number of stars and planets
			cout << "Stars: " << stars << ", ";
			cout << "Planets: " << planets << endl;
		}
	}
}



//declares global constants
const char WORDFILENAME[] = "words.txt";
const int MAXWORDS = 9000; 

int main()
{
	//declares each element of the array as being able to hold a C string of length up to 6 letters
	char wordList[MAXWORDS][MAXWORDLEN + 1];
	// get words from the file
	int nActualWords = getWords(wordList, 9000, WORDFILENAME);  

	//if the words in the file are less than 1 then return 0
	if (nActualWords < 1)
	{
		cout << "No words were loaded, so I can't play the game." << endl;
		return 0;
	}
	
	//asks the user how many rounds they want to play
	cout << "How many rounds do you want to play? ";
	int numberOfRounds;
	cin >> numberOfRounds;
	cin.ignore(10000, '\n');

	//if the entered rounds is less than 0 then leave game
	if (numberOfRounds <= 0)
	{
		cout << "The number of rounds must be positive." << endl;
		return 0;
	}
	
	double scoreOfRounds = 0;
	//goes through the first round
	cout << endl;
	cout << "Round 1" << endl;
	//finds position of the secret word in the entered array
	int posOfRandomWord = randInt(0, nActualWords - 1);
	cerr << wordList[posOfRandomWord];
	//tells the user how long the secret word array is
	cout << "The secret word is " << strlen(wordList[posOfRandomWord]) << " letters long." << endl;
	//intializes a variable as equivalent to the return value of the runOneRound function
	int scoreOfOneRound = runOneRound(wordList, nActualWords, posOfRandomWord);
	//finds the total of all the rounds
	scoreOfRounds += scoreOfOneRound;
	//for one round it only has one score so it is just equivalent to the score of the first round
	double average = scoreOfRounds;
	int minimum = scoreOfOneRound;
	int maximum = scoreOfOneRound;
	if (scoreOfOneRound == 1)
	{
		cout << "You got it in " << scoreOfOneRound << " try." << endl;
	}
	if (scoreOfOneRound > 1)
	{
		cout << "You got it in " << scoreOfOneRound << " tries." << endl;
	}
	cout.precision(2);
	cout << fixed << "Average: " << average;
	cout.precision(0);
	cout << fixed << ", minimum: " << minimum << ", maximum: " << maximum << endl;

	//goes through the rounds after round 1
	for (int i = 1; i < numberOfRounds; i++)
	{
		cout << endl;
		cout << "Round " << i + 1 << endl;
		//returns the position of the secret word
		int posOfRandomWord = randInt(0, nActualWords - 1);
		cerr << wordList[posOfRandomWord];
		int lenOfSecretWord = strlen(wordList[posOfRandomWord]); 
		cout << "The secret word is " << lenOfSecretWord << " letters long." << endl;
		int scoreOfOneRound = runOneRound(wordList, nActualWords, posOfRandomWord); 
		if (scoreOfOneRound <= minimum)
		{
			minimum = scoreOfOneRound;
		}
		if (scoreOfOneRound > maximum)
		{
			maximum = scoreOfOneRound;
		}
		if (scoreOfOneRound == 1)
		{
			cout << "You got it in " << scoreOfOneRound << " try." << endl;
		}
		else if (scoreOfOneRound > 1)
		{
			cout << "You got it in " << scoreOfOneRound << " tries." << endl;
		}
		//states that scoreOfRounds is equal to the total scores of all of the rounds
		scoreOfRounds += scoreOfOneRound;
		//declares how to find the average
		average = scoreOfRounds/ (i + 1);
		cout.precision(2);
		cout << fixed << "Average: " << average;
		cout.precision(0);
		cout<< fixed << ", minimum: " << minimum << ", maximum: " << maximum << endl;
	}
}




