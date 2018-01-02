#include <iostream>
#include <string>
#include <cctype>
#include <cassert>
using namespace std;

bool hasCorrectSyntax(string song)
{
	//Identifies the characters valid in the song string, anything other than these is false
	string noteLetter = "ABCDEFG#b0123456789/";
	//Identifies that if the song string is empty it is not valid
	if (song == "")
	{
		return false;
	}
	//Identifies that the last character of the song has to be '/' and that the first character of the string cannot be '#' or 'b'
	else if (song[song.size() - 1] != '/' || song[0] == '#' || song[0] == 'b')
	{
		return false;
	}

	else
	{
		//makes sure to go through each character of the string
		for (int i = 0; i < song.size(); i++)
		{
			bool letter = false;
			//Identifies that if the noteletter is a letter or a # or a b it cannot be preceded by a # or b  
			if (i != 0 && (song[i] == 'A' || song[i] == 'B' || song[i] == 'C' || song[i] == 'D' || song[i] == 'E' || song[i] == 'F' || song[i] ==
				'G' || song[i] == '#' || song[i] == 'b') && song[i - 1] == '#' && (song[i - 2] == '/'))
			{
				letter = false;
			}
			//identifies that two digits 0-9 cannot follow each other in a song
			else if (i != 0 && isdigit(song[i]) && isdigit(song[i - 1]))
			{
				letter = false;
			}
			//identifies that a note letter can have a sharp, but also have an octave
			else if (i > 1 && isdigit(song[i]) && song[i - 1] == '#' && (song[i - 2] == 'A' || song[i - 2] == 'B'
				|| song[i - 2] == 'C' || song[i - 2] == 'D' || song[i - 2] == 'E' || song[i - 2] == 'F' || song[i - 2] == 'G'))
			{
				letter = true;
			}
			//identifies that a note letter can have a flat, but also have an octave
			else if (i > 1 && isdigit(song[i]) && song[i - 1] == 'b' && (song[i - 2] == 'A' || song[i - 2] == 'B'
				|| song[i - 2] == 'C' || song[i - 2] == 'D' || song[i - 2] == 'E' || song[i - 2] == 'F' || song[i - 2] == 'G'))
			{
				letter = true;
			}
			//identifies that a flat cannot come before a noteletter unless it is following a Letter
			else if (i != 0 && (song[i + 1] == 'A' || song[i] == 'B' || song[i] == 'C' || song[i] == 'D' || song[i] == 'E' || song[i] == 'F' || song[i] ==
				'G') && (song[i] == 'b') && ((song[i - 1] == '/') || (song[i - 1] == isdigit(song[i]))))
			{
				letter = false;
			}
			//identifies that a sharp cannot come directly after a flat and vice versa and that there cannot be a sharp pr a flat directly after a '/'
			else if (i != 0 && (song[i] == '#' && song[i + 1] == 'b') || (song[i] == 'b' && song[i + 1] == '#') || (song[i] == '#' && song[i + 1] == '#')
				|| (song[i] == 'b' && song[i + 1] == 'b') || (song[i] == '#' && song[i - 1] == '/') || (song[i] == 'b' && song[i - 1] == '/'))
			{
				letter = false;
			}
			else
			{
				//identifies that each of the characters is checked and is valid
				for (int j = 0; j < noteLetter.size(); j++)
				{
					if (song[i] == noteLetter[j])
					{
						letter = true;
						break;
					}
				}
			}
			if (letter == false)
			{
				//if the string doesn't follow these guideline it will automatically come up as false
				return false;
			}
		}
		//in order to return 0
		return true;
	}
}
//*************************************
//  encodeNote
//*************************************

// Given an octave number, a note letter, and an accidental sign, return
// the character that the indicated note is encoded as if it is playable.
// Return a space character if it is not playable.
//
// First parameter:   the octave number (the integer 4 is the number of the
//                    octave that starts with middle C, for example).
// Second parameter:  an upper case note letter, 'A' through 'G'
// Third parameter:   '#', 'b', or ' ' (meaning no accidental sign)
//
// Examples:  encodeNote(4, 'A', ' ') returns 'Q'
//            encodeNote(4, 'A', '#') returns '%'
//            encodeNote(4, 'H', ' ') returns ' '

char encodeNote(int octave, char noteLetter, char accidentalSign)
{
	//A#3A2/Ab2/B/
	// This check is here solely to report a common CS 31 student error.
	if (octave > 9)
	{
		cerr << "********** encodeNote was called with first argument = "
			<< octave << endl;
	}

	// Convert Cb, C, C#/Db, D, D#/Eb, ..., B, B#
	//      to -1, 0,   1,   2,   3, ...,  11, 12

	int note;
	switch (noteLetter)
	{
	case 'C':  note = 0; break;
	case 'D':  note = 2; break;
	case 'E':  note = 4; break;
	case 'F':  note = 5; break;
	case 'G':  note = 7; break;
	case 'A':  note = 9; break;
	case 'B':  note = 11; break;
	default:   return ' ';
	}
	switch (accidentalSign)
	{
	case '#':  note++; break;
	case 'b':  note--; break;
	case ' ':  break;
	default:   return ' ';
	}

	// Convert ..., A#1, B1, C2, C#2, D2, ... to
	//         ..., -2,  -1, 0,   1,  2, ...

	int sequenceNumber = 12 * (octave - 2) + note;

	string keymap = "Z1X2CV3B4N5M,6.7/A8S9D0FG!H@JK#L$Q%WE^R&TY*U(I)OP";
	if (sequenceNumber < 0 || sequenceNumber >= keymap.size())
		return ' ';
	return keymap[sequenceNumber];
}
//this function defines wether or not a note in the song string is playable
bool playableNumberNote(string song, int a)
{
	//identifies the always valid octaves
	if (song[a] == '3' || song[a] == '4' || song[a] == '5')
		return true;
	//shows how the octave #2 isn't valid for a specific condition
	if (song[a] == '2')
		if (song[a - 1] == 'b' && song[a - 2] == 'C')
		{
			return false;
		}
		else
		{
			return true;
		}
	//enforces that octave 1 is only valid in B#1
	if (song[a] == 1 && song[a - 1] == '#' && song[a - 2] == 'B')
	{
		return true;
	}
	//enforces that octave 6 is onl valid in Cb6 or C6
	if (song[a] == 6 && song[a - 1] == 'b' && song[a - 2] == 'C')
	{
		return true;
	}
	if (song[a] == 6 && song[a - 1] == 'C')
	{
		return true;
	}
	//if a note is something other than the conditions described above it is false
	else
	{
		return false;
	}
}


int encodeSong(string song, string& instructions, int& badBeat)
{
	//if the syntax is incorrect then the function returns 1
	if (!hasCorrectSyntax(song))
	{
		return 1;
	}
	//sets the number of initial beats to 0
	int beatCounter = 0;
	//allows us to check each character of the song string to see if it is the start of a new beat or a note
	for (int i = 0; i < song.size(); i++)
	{
		//means it is a new beat
		if (song[i] == '/')
		{
			beatCounter++;
		}
		//tests to see if it is a playable note
		if (isdigit(song[i]))
		{
			if (!playableNumberNote(song, i))
			{
				//if it is not a playle note badBeat is set to the beat number of the unplayable note and function returns 2
				badBeat = beatCounter + 1;
				return 2;
			}
		}
	}
	instructions = "";
	//identifies the initial note amount in a song string if there are letters
	int noteCounter = 1;

	for (int i = 0; i < song.size() -1; i++)
	{
		//initializes as a space
		char enNote = ' ';
		
		// identifies what to do if there is an empty note
		if (song[i] == '/' && song[i + 1] == '/')
		{
			//octave set to four, noteLetter to space and accidental sign to space
			enNote = encodeNote(4, ' ',' ');
			i = i + 1;
			instructions += enNote;
		}
		//identifies what to do when there are to consective notes or a letter is automatically followed by a slash
		else if (isalpha(song[i]) && (isalpha(song[i + 1]) || song[i + 1] == '/')) // e.g. AA
		{
			//the octave is 4, the note letter is the letter entered, and the accidental sign is a space
			enNote = encodeNote(4, song[i],' ');
			if (isalpha(song[i + 1]))
			{
				//if a beat has more than one note than it has brackets
				if (noteCounter == 1)
				{
					instructions += "[";
				}
				instructions += enNote;
				//notecounter increases if a letter is followed by a letter
				noteCounter++;
			}
			else
			{
				//if noteCounter is greater than 1 there will be brackets around the beat
				if (noteCounter > 1 ) {
					instructions += enNote;
					instructions +=  "]";
					noteCounter = 1;
				} else {
					instructions += enNote;
				}
			}
		}
		//if the note has an upper case leter a octave and is followed by a slash or another letter
		else if (isalpha(song[i]) && isdigit(song[i + 1]) && (isalpha(song[i + 2]) || song[i + 2] == '/')) // e.g A6A/
		{
			//have to do this or else the octave number will be added to 48
			int octaveNumber = (int)song[i + 1] - 48;
			//octaveNumber is now defined
			enNote = encodeNote(octaveNumber, song[i],' ');

			//once again if i + 2 is a letter then the noteCounter increases
			if (isalpha(song[i + 2]))
			{
				//makes sure there are brackets around the beat if the beat has more than one note
				if (noteCounter == 1)
				{
					instructions += "[";
				}
				instructions += enNote;
				noteCounter++;
			}
			else
			{
				if (noteCounter > 1 ) {
					instructions += enNote;
					instructions +=  "]";
					noteCounter = 1;
				} else {
					instructions += enNote;
				}
			}
			i = i + 1;
		}
		//identifies what happens if an accidental sign is also entered
		else if (isalpha(song[i]) && (song[i + 1] == 'b' || song[i + 1] == '#') && (isalpha(song[i + 2])|| song [i + 2] == '/')) // e.g A#A or AbA 
		{
			//assigns octave as 4, noteletter as whatever is entered and the accidental as wha comes after the noteletter
			enNote = encodeNote(4, song[i], song[i + 1]);
			//brackets around beat if noteCounter > 1
			if (isalpha(song[i + 2]))
			{
				if (noteCounter == 1)
				{
					instructions += "[";
				}
				instructions += enNote;
				noteCounter++;
			}
			else
			{
				if (noteCounter > 1 ) {
					instructions += enNote;
					instructions +=  "]";
					noteCounter = 1;
				} else {
					instructions += enNote;
				}
			}
			i = i + 1;

		}
		//identifies what happens when all three variables are entered by the user
		else if (isalpha(song[i]) && (song[i + 1] == 'b' || song[i + 1] == '#') && isdigit(song[i + 2]) && (isalpha(song[i + 3]) || song[i + 3] == '/')) // e.g A#6A 
		{
			//must do to ensure octave number!= to 48 + octaveNumber entered
			int octaveNumber = (int)song[i + 2] - 48;
			enNote = encodeNote(octaveNumber, song[i], song[i + 1]);
			//add brackets around beat if there is more than one note
			if (isalpha(song[i + 3]))
			{
				if (noteCounter == 1)
				{
					instructions += "[";
				}
				instructions += enNote;
				noteCounter++;
			}
			else
			{
				if (noteCounter > 1 ) {
					instructions += enNote;
					instructions +=  "]";
					noteCounter = 1;
				} else {
					instructions += enNote;
				}
			}
			i = i + 2;
		}
	}
	return 0;
}


int main()
{
	assert(hasCorrectSyntax("D5//D/"));
	assert(!hasCorrectSyntax("D5//Z/"));
	string instrs;
	int badb;
	instrs = "xxx"; badb = -999; // so we can detect whether these get changed
	assert(encodeSong("D5//D/", instrs, badb) == 0 && instrs == "R H"  &&  badb == -999);
	instrs = "xxx"; badb = -999; // so we can detect whether these get changed
	assert(encodeSong("D5//Z/", instrs, badb) == 1 && instrs == "xxx"  &&  badb == -999);
	assert(encodeSong("D5//D8/", instrs, badb) == 2 && instrs == "xxx"  &&  badb == 3);
		cerr << "All tests succeeded" << endl;
}

