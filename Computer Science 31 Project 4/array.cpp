#include <iostream>
#include <string>
#include <cassert>
#include <algorithm>
#include <cstdlib>
using namespace std;

//Append value to the end of each of the n elements of the array and return n.
int appendToAll(string a[], int n, string value)
{
	if (n < 0)//if the n value is negative the function returns -1
	{
		return -1;
	}
	for (int b = 0; b < n ; b++)
	{
		a[b] += value;  //for each element in the array add value
	}
	return n;//returns the number of elements
}

//Return the position of a string in the array that is equal to target
int lookup(const string a[], int n, string target)
{
	if (n < 0)
	{
		return -1;
	}
	for (int j = 0; j < n; j++)
	{
		if (a[j] == target) //if an element in the array is eequivalent to the target than return the index number
			return j;
	}
	return -1;
}

//Return the position of a string in the array such that that string is >= every string in the array.
int positionOfMax(const string a[], int n)
{
	int great = 0;              //initializes a variable
	if (n <= 0)      //if n is less than or equal to zero return -1
		return -1;
	for (int k = 0; k < n; k++)
	{
		if (a[k] > a[great]) //if it is the string is greater at k 
		{
			great = k;//reaassigns value to the current k 
		}
	}
	return great;//returns the position that is greater than all of them
}

//Eliminate the item at position pos by copying all elements after it one place to the left
int rotateLeft(string a[], int n, int pos)
{
	if (n <= 0) //if number of elements is negative or equal to zero return -1
	{
		return -1;
	}
	if (pos < 0)
	{
		return -1;
	}
	string place = a[pos];  //assigns the intial a[pos] to a string so it can be stored
	for (int i = pos; i < n - 1; i++) // moves everything from pos to one ahead
	{
		a[i] = a[i + 1];
	}
	a[n - 1] = place;  //accounts for the fact that a[n-1] isn't addressed in the above loop and needs to be placed at the end of the array
	return pos;
}

//Return the number of sequences of one or more consecutive identical items in a.
int countRuns(const string a[], int n)
{
	if (n < 0) //if the number of elements is less than zero return -1
	{
		return -1;
	}
	int sequenceNumber = 1;   //initialize sequence number, will store the number of sequences in the array
	if (n == 0)
		return 0;
	for (int i = 0; i < n - 1; i++)
	{
		if (a[i] != a[i + 1])  //if an element isn't equal to the element right after it 
		{
			sequenceNumber = sequenceNumber + 1; //add one to the sequenceNumber variable
		}
	}
	return sequenceNumber; //return the final sequenceNumber
}

//Reverse the order of the elements of the array and return n
int flip(string a[], int n)
{
	string reverse = ""; //initializes the string
	if (n < 0) //if the number of elements is less than 0 return -1
	{
		return -1;
	}
	if (n == 0)
	{
		return 0;
	}
	for (int j = 0; j < n; j++)
	{
		if (j < ((n - 1) - j))  //to make sure the string isn't flipped back once the loop goes to the middle elements
		{
			//Does a swap between the values
			reverse = a[j]; //make reverse equivalent to the inital value to store it
			a[j] = a[(n - 1) - j]; //make this position of the string now equivalent to its position going in the reverse direction
			a[(n - 1) - j] = reverse;//make the position from the reverse direction equal to the initial value of a[j]
		}
	}
	return n;//return the elements entered into the parameters
}


//return the position of the first corresponding elements of a1 and a2 that are not equal
int differ(const string a1[], int n1, const string a2[], int n2)
{
	if (n1 < 0 || n2 < 0) //if the length is negative then return -1
	{
		return -1;
	}
	int small = 0; //declare a variable
	if (n1 == 0 || n2 == 0) //if length is equal to zero return 0 since they will automatically be equal 
		return 0;
	if (n1 < n2) //assigning the smaller value to small
	{
		small = n1;
	}
	else if (n2 < n1)
	{
		small = n2;
	}
	else if (n1 == n2) //if they are equal assign small to either one since it doesn't matter
	{
		small = n1;
	}

	for (int i = 0; i < small; i++)//runs through the index of the arrays
	{
		if (a1[i] != a2[i]) //shows when they differ from each other
			return i; //returns position number
	}
	return small; //returns the smaller length
}


//If all n2 elements of a2 appear in a1, consecutively and in the same order, then return the position in a1 where that subsequence begins
int subsequence(const string a1[], int n1, const string a2[], int n2)
{
	if (n1 < 0 || n2 < 0) //if either is negative its -1
	{
		return -1;
	}
	if (n2 > n1)  //n2 cannot be greater n1 since there cant be the subsequence cant be larger than the sequence
		return -1;
	if (n2 == 0) //if the subsequence is equal to 0 then return 0
	{
		return 0;
	}
	int startPosition = -1; //initialize the startPosition as a number
	for (int k = 0; k < n1; k++)
	{
		if (a1[k] == a2[0]) //if a string in the initial array is the first string in the array then go through the loop to make sure 
		{
			startPosition = k; //make startPosition equal to the position of k 
			for (int j = 1; j < n2; j++)
			{
				if (a2[j] == a1[k + 1]) //compare each string in second array to the first array to makee sure its consecutive
				{
					k++; //k is increased so you can keep checking for other parts of the array
				}
				else if (a2[j] != a1[k + 1]) //if its not equal to then return -1
				{
					return -1;
				}
				else
					break;
			}

		}
	}
	return startPosition; //return the position where the k begins
}

int lookupAny(const string a1[], int n1, const string a2[], int n2)
{
	if (n1 < 0 || n2 < 0) //if n is negative then return -1
	{
		return -1;
	}
	for (int k = 0; k < n1; k++) //go through the first array
	{
		for (int i = 0; i < n2; i++) //go through the second array 
		{
			if (a1[k] == a2[i]) //if it is found return the position of the common element
				return k;
		}
	}
	return -1;
}


//Rearrange the elements of the array so that all the elements whose value is < splitter come 
int split(string a[], int n, string splitter)
{
	if (n < 0) //if the length is negative then return -1
	{
		return -1;
	}
	if (n == 0) //if the length is equal 0 then return 0
	{
		return 0;
	}
	string right = ""; //initialize a string
	string left = "";//initialize a string
	for (int i = 0; i < n; i++) //go through the string
	{
		//categorized it based of splitter
		if (a[i] < splitter)
			left += i;
		else 
			right += i;
	}
	//add the two strings together after the strings are sorted
	string full = left + right; 
	if (right == "")
	{
		return left.size(); //if the right is empty just return the size of the left to show the position
	}
	for (int j = 0; j < full.size(); j++)//does a swap between the newly sorted array and the old one
	{
		string temp = a[j]; 
		a[j] = a[(int)full[j]];
		a[(int)full[j]] = temp;
	}
	return left.size(); //return the left size to show the position of the right side
}

/*int main()
{
	string h[7] = { "selina", "reed", "diana", "tony", "", "logan", "peter" };
	
	assert(lookup(h, 7, "logan") == 5);
	assert(lookup(h, 7, "diana") == 2);
	assert(lookup(h, 2, "diana") == -1);
	assert(positionOfMax(h, 7) == 3);
	

	string g[6] = { "selina", "reed", "peter", "sue", "sue", "william" };
	assert(differ(h, 4, g, 4) == 2);
	assert(appendToAll(g, 6, "?") == 6 && g[0] == "selina?" && g[5] == "william?");   
	assert(rotateLeft(g, 4, 1) == 1 && g[1] == "peter?" && g[3] == "reed?");

	string e[4] = { "diana", "tony", "", "logan" };
	assert(subsequence(h, 7, e, 4) == 2);

	string d[5] = { "reed", "reed", "reed", "tony", "tony" };
	assert(countRuns(d, 5) == 2);

	string f[3] = { "peter", "diana", "steve" };
	assert(lookupAny(h, 7, f, 3) == 2);
	assert(flip(f, 3) == 3 && f[0] == "steve" && f[2] == "peter");

	assert(split(h, 7, "peter") == 3);

	//my own cases:
	string a[10] = { "brian", "steven", "timothy", "sean" ,"sean", "linda", "sarah","sarah", "megan", "jade" };
	assert(countRuns(a, 10) == 8);
	assert(appendToAll(a, 4, "?") == 4 && a[0] == "brian?" && a[3] == "sean?");
	assert(appendToAll(a, -3, "?") == -1);
	assert(flip(a, 10) == 10 && a[0] == "jade" && a[9] == "brian?");
	string b[7] = { "ally", "blake", "leyna", "sarah", "zahra", "jacob", "shannon" };
	string c[4] = { "blake", "leyna", "joseph", "shannon" };
	string s[3] = { "sarah", "zahra", "jacob" };
	assert(lookup(b, 7, "ally") == 0);
	assert(lookup(b, 7, "jacob") == 5);
	assert(lookup(c, 3, "will") == -1);
	assert(lookup(c, -2, "leyna") == -1);
	assert(lookupAny(b, 7, c, 4) == 1);
	assert(lookupAny(a, 10, c, 4) == -1);
	assert(lookupAny(a, -1, c, 4) == -1);
	assert(subsequence(b, 7, s, 3) == 3);
	assert(subsequence(b, 7, c, 4) == -1);
	assert(subsequence(b, -2, c, 4) == -1);

	string z[4] = { "nithika", "harshita", "likhita", "preethika" };
	string r[2] = { "nithika", "harshita" };
	string t[3] = { "dawn", "summer", "autumn" };
	assert(differ(z, 4, r, 2) == 2);
	assert(differ(z, 0, r, 2) == 0);
	assert(differ(z, -1, r, 2) == -1);
	assert(positionOfMax(z, 4) == 3);
	assert(positionOfMax(r, -2) == -1);
	assert(countRuns(z, 4) == 4);
	assert(rotateLeft(z, 4, 1) == 1 && z[1] == "likhita" && z[3] == "harshita");
	assert(rotateLeft(s, 3, 1) == 1 && s[0] == "sarah" && s[2] == "zahra");
	assert(rotateLeft(s, 3, -2) == -1);
	assert(rotateLeft(s, -2, 1) == -1);
	assert(split(t, 3, "jolly") == 2);
	assert(split(r, 2, "apple") == 0);
	assert(split(r, -1, "open") == -1);
	assert(split(r, 2, "zebra") == 2);
	assert(split(r, 2, "king") == 1);
	cout << "All tests succeeded" << endl;*/
string c[6] = {
	"alpha", "beta", "beta", "delta", "gamma", "gamma"
};

bool splitcheck(const string a[], int n, int p, string splitter)
{
	for (int k = 0; k < p; k++)
		if (a[k] >= splitter)
			return false;
	for (; p < n && a[p] == splitter; p++)
		;
	for (int k = p; k < n; k++)
		if (a[k] <= splitter)
			return false;
	string b[100];
	copy(a, a + n, b);
	sort(b, b + n);
	return equal(b, b + n, c);
}

void testone(int n)
{
	const int N = 6;

	// Act as if  a  were declared:
	//   string a[N] = {
	//       "alpha", "beta", "gamma", "gamma", "beta", "delta"
	//   };
	// This is done in a way that will probably cause a crash if
	// a[-1] or a[N] is accessed:  We place garbage in those positions.
	string aa[1 + N + 1] = {
		"", "alpha", "beta", "gamma", "gamma", "beta", "delta", ""
	};
	string* a = &aa[1];
	string* z = aa;
	a[-1].string::~string();
	a[N].string::~string();
	fill_n(reinterpret_cast<char*>(&a[-1]), sizeof(a[-1]), 0xEF);
	fill_n(reinterpret_cast<char*>(&a[N]), sizeof(a[N]), 0xEF);

	string b[N] = {
		"alpha", "beta", "gamma", "delta", "beta", "delta"
	};

	string d[9] = {
		"alpha", "beta",  "beta", "beta", "alpha",
		"alpha", "delta", "beta", "beta"
	};

	switch (n)
	{
	case  1: {
		assert(appendToAll(z, -1, "rho") == -1 && a[0] == "alpha");
	} break; case  2: {
		assert(appendToAll(z, 0, "rho") == 0 && a[0] == "alpha");
	} break; case  3: {
		assert(appendToAll(a, 1, "rho") == 1 && a[0] == "alpharho" &&
			a[1] == "beta");
	} break; case  4: {
		assert(appendToAll(a, 6, "rho") == 6 && a[0] == "alpharho" &&
			a[1] == "betarho" && a[2] == "gammarho" &&
			a[3] == "gammarho" && a[4] == "betarho" &&
			a[5] == "deltarho");
	} break; case  5: {
		assert(lookup(z, -1, "alpha") == -1);
	} break; case  6: {
		assert(lookup(z, 0, "alpha") == -1);
	} break; case  7: {
		assert(lookup(a, 1, "alpha") == 0);
	} break; case  8: {
		assert(lookup(a, 6, "delta") == 5);
	} break; case  9: {
		assert(lookup(a, 6, "beta") == 1);
	} break; case 10: {
		assert(lookup(a, 6, "zeta") == -1);
	} break; case 11: {
		assert(positionOfMax(z, -1) == -1);
	} break; case 12: {
		assert(positionOfMax(z, 0) == -1);
	} break; case 13: {
		assert(positionOfMax(a, 1) == 0);
	} break; case 14: {
		assert(positionOfMax(a, 3) == 2);
	} break; case 15: {
		assert(positionOfMax(a, 6) == 2);
	} break; case 16: {
		assert(positionOfMax(a + 3, 3) == 0);
	} break; case 17: {
		a[0] = "";
		a[1] = " ";
		a[2] = "";
		assert(positionOfMax(a, 3) == 1);
	} break; case 18: {
		assert(rotateLeft(z, -1, 0) == -1 &&
			a[0] == "alpha" && a[1] == "beta");
	} break; case 19: {
		assert(rotateLeft(a, 6, -1) == -1 &&
			a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
			a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
	} break; case 20: {
		assert(rotateLeft(a, 6, 6) == -1 &&
			a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
			a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
	} break; case 21: {
		assert(rotateLeft(z, 0, 0) == -1 &&
			a[0] == "alpha" && a[1] == "beta");
	} break; case 22: {
		assert(rotateLeft(a, 1, 0) == 0 &&
			a[0] == "alpha" && a[1] == "beta");
	} break; case 23: {
		assert(rotateLeft(a, 6, 0) == 0 &&
			a[0] == "beta" && a[1] == "gamma" && a[2] == "gamma" &&
			a[3] == "beta" && a[4] == "delta" && a[5] == "alpha");
	} break; case 24: {
		assert(rotateLeft(a, 6, 5) == 5 &&
			a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
			a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
	} break; case 25: {
		assert(rotateLeft(a, 6, 3) == 3 &&
			a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
			a[3] == "beta" && a[4] == "delta" && a[5] == "gamma");
	} break; case 26: {
		assert(rotateLeft(a, 5, 3) == 3 &&
			a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
			a[3] == "beta" && a[4] == "gamma" && a[5] == "delta");
	} break; case 27: {
		assert(countRuns(z, -1) == -1);
	} break; case 28: {
		assert(countRuns(z, 0) == 0);
	} break; case 29: {
		assert(countRuns(a, 1) == 1);
	} break; case 30: {
		assert(countRuns(a, 3) == 3);
	} break; case 31: {
		assert(countRuns(a, 4) == 3);
	} break; case 32: {
		assert(countRuns(a + 2, 4) == 3);
	} break; case 33: {
		assert(countRuns(d, 9) == 5);
	} break; case 34: {
		assert(flip(z, -1) == -1 && a[0] == "alpha");
	} break; case 35: {
		assert(flip(z, 0) == 0 && a[0] == "alpha");
	} break; case 36: {
		assert(flip(a, 1) == 1 && a[0] == "alpha" &&
			a[1] == "beta");
	} break; case 37: {
		assert(flip(a, 2) == 2 && a[0] == "beta" &&
			a[1] == "alpha" && a[2] == "gamma");
	} break; case 38: {
		assert(flip(a, 5) == 5 && a[0] == "beta" &&
			a[1] == "gamma" && a[2] == "gamma" && a[3] == "beta" &&
			a[4] == "alpha" && a[5] == "delta");
	} break; case 39: {
		a[2] = "zeta";
		assert(flip(a, 6) == 6 && a[0] == "delta" && a[1] == "beta" &&
			a[2] == "gamma" && a[3] == "zeta" && a[4] == "beta" &&
			a[5] == "alpha");
	} break; case 40: {
		assert(differ(z, -1, b, 6) == -1);
	} break; case 41: {
		assert(differ(a, 6, z, -1) == -1);
	} break; case 42: {
		assert(differ(z, 0, b, 0) == 0);
	} break; case 43: {
		assert(differ(a, 3, b, 3) == 3);
	} break; case 44: {
		assert(differ(a, 3, b, 2) == 2);
	} break; case 45: {
		assert(differ(a, 2, b, 3) == 2);
	} break; case 46: {
		assert(differ(a, 6, b, 6) == 3);
	} break; case 47: {
		assert(subsequence(z, -1, b, 6) == -1);
	} break; case 48: {
		assert(subsequence(a, 6, z, -1) == -1);
	} break; case 49: {
		assert(subsequence(z, 0, b, 6) == -1);
	} break; case 50: {
		assert(subsequence(a, 6, z, 0) == 0);
	} break; case 51: {
		assert(subsequence(a, 6, b, 1) == 0);
	} break; case 52: {
		assert(subsequence(a, 6, b + 4, 2) == 4);
	} break; case 53: {
		assert(subsequence(a, 6, b + 3, 1) == 5);
	} break; case 54: {
		assert(subsequence(a, 6, b + 3, 2) == -1);
	} break; case 55: {
		assert(subsequence(a, 6, b + 2, 2) == -1);
	} break; case 56: {
		assert(subsequence(a, 6, a, 6) == 0);
	} break; case 57: {
		assert(lookupAny(a, 6, z, -1) == -1);
	} break; case 58: {
		assert(lookupAny(z, -1, b, 6) == -1);
	} break; case 59: {
		assert(lookupAny(z, 0, b, 1) == -1);
	} break; case 60: {
		assert(lookupAny(a, 6, z, 0) == -1);
	} break; case 61: {
		assert(lookupAny(a, 1, b, 1) == 0);
	} break; case 62: {
		assert(lookupAny(a, 6, b + 3, 3) == 1);
	} break; case 63: {
		assert(lookupAny(a, 4, b + 3, 3) == 1);
	} break; case 64: {
		assert(lookupAny(a, 2, b + 2, 2) == -1);
	} break; case 65: {
		assert(split(z, -1, "beta") == -1 &&
			a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
			a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
	} break; case 66: {
		assert(split(z, 0, "beta") == 0 &&
			a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
			a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
	} break; case 67: {
		assert(split(a, 1, "aaa") == 0 &&
			a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
			a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
	} break; case 68: {
		assert(split(a, 1, "alpha") == 0 &&
			a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
			a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
	} break; case 69: {
		assert(split(a, 1, "zeta") == 1 &&
			a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
			a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
	} break; case 70: {
		assert(split(a, 2, "aaa") == 0 &&
			splitcheck(a, 2, 0, "aaa") && a[2] == "gamma" &&
			a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
	} break; case 71: {
		assert(split(a, 2, "alpha") == 0 &&
			splitcheck(a, 2, 0, "alpha") && a[2] == "gamma" &&
			a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
	} break; case 72: {
		assert(split(a, 2, "beta") == 1 &&
			splitcheck(a, 2, 1, "beta") && a[2] == "gamma" &&
			a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
	} break; case 73: {
		assert(split(a, 2, "zeta") == 2 &&
			splitcheck(a, 2, 2, "zeta") && a[2] == "gamma" &&
			a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
	} break; case 74: {
		assert(split(a, 6, "aaa") == 0 && splitcheck(a, 6, 0, "aaa"));
	} break; case 75: {
		assert(split(a, 6, "alpha") == 0 &&
			splitcheck(a, 6, 0, "alpha"));
	} break; case 76: {
		assert(split(a, 6, "beta") == 1 &&
			splitcheck(a, 6, 1, "beta"));
	} break; case 77: {
		assert(split(a, 6, "delta") == 3 &&
			splitcheck(a, 6, 3, "delta"));
	} break; case 78: {
		assert(split(a, 6, "gamma") == 4 &&
			splitcheck(a, 6, 4, "gamma"));
	} break; case 79: {
		assert(split(a, 6, "zeta") == 6 &&
			splitcheck(a, 6, 6, "zeta"));
	} break; case 80: {
		a[2] = "mu";
		c[5] = "mu";
		assert(split(a, 6, "mu") == 5 && splitcheck(a, 6, 5, "mu"));
	} break; case 81: {
		assert(split(a, 6, "chi") == 3 && splitcheck(a, 6, 3, "chi"));
	} break; case 82: {
		// To earn the bonus point for rotateLeft, this and all other
		// rotateLeft tests must pass, and that function must not
		// use any additional arrays.
		const int BIG = 500;
		string h[BIG];
		for (int k = 0; k < BIG; k++)
			h[k] = (k % 2 == 0 ? "alpha" : "beta");
		h[BIG - 2] = "gamma";
		h[BIG - 1] = "delta";
		rotateLeft(h, BIG, 0);
		assert(h[BIG - 3] == "gamma"  &&  h[BIG - 2] == "delta");
	} break; case 83: {
		// To earn the bonus point for flip, this and all other
		// flip tests must pass, and that function must not
		// use any additional arrays.
		const int BIG = 500;
		string h[BIG];
		for (int k = 0; k < BIG; k++)
			h[k] = (k % 2 == 0 ? "alpha" : "beta");
		h[0] = "gamma";
		h[BIG - 1] = "delta";
		flip(h, BIG);
		assert(h[0] == "delta"  &&  h[BIG - 1] == "gamma");
	} break; case 84: {
		// To earn the bonus point for split, this and all other
		// split tests must pass, and that function must not
		// use any additional arrays.
		const int BIG = 500;
		string h[BIG];
		string i[3] = { "alpha", "beta", "gamma" };
		for (int k = 0; k < BIG; k++)
			h[k] = i[k % 3];
		split(h, BIG, "beta");
		int m = 0;
		for (m = 0; m < (BIG + 2) / 3; m++)
			assert(h[m] == "alpha");
		for (; m < (BIG + 1) / 3; m++)
			assert(h[m] == "beta");
		for (; m < BIG / 3; m++)
			assert(h[m] == "gamma");
	} break;
	}

	new (&a[-1]) string;
	new (&a[N]) string;
}

int main()
{
	cout << "Enter a test number (1 to 84): ";
	int n;
	cin >> n;
	if (n < 1 || n > 84)
	{
		cout << "Bad test number" << endl;
		return 1;
	}
	testone(n);
	cout << "Passed test " << n << endl;
}
