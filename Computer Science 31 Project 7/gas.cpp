// gas.cpp

// Portions you are to complete are marked with a TODO: comment.
// We've provided some incorrect return statements (so indicated) just
// to allow this skeleton program to compile and run, albeit incorrectly.
// The first thing you probably want to do is implement the trivial
// functions (marked TRIVIAL).  Then get City::display going.  That gives
// you more flexibility in the order you tackle the rest of the functionality.
// As you finish implementing each TODO: item, remove its TODO: comment.

#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
using namespace std;
#include <cassert>

#define CHECKTYPE(f, t) { (void)static_cast<t>(f); }


///////////////////////////////////////////////////////////////////////////
// Manifest constants
///////////////////////////////////////////////////////////////////////////

const int MAXROWS = 20;               // max number of rows in a city
const int MAXCOLS = 30;               // max number of columns in a city
const int MAXFLATULANS = 100;         // max number of Flatulans allowed

const int UP = 0;
const int DOWN = 1;
const int LEFT = 2;
const int RIGHT = 3;
const int NUMDIRS = 4;

///////////////////////////////////////////////////////////////////////////
// Type definitions
///////////////////////////////////////////////////////////////////////////

class City;  // This is needed to let the compiler know that City is a
			 // type name, since it's mentioned in the Flatulan declaration.

class Flatulan
{
public:
	// Constructor
	//constructing the flatulans
	Flatulan(City* cp, int r, int c);

	// Accessors
	//how to access the Flatulan
	int  row() const;
	int  col() const;

	// Mutators
	//what changes the Flatulans
	void move();
	bool possiblyGetConverted();

private:
	City* m_city;
	int   m_row;
	int   m_col;
};

class Player
{
public:
	// Constructor
	Player(City *cp, int r, int c); //creates one player

	// Accessors
	int  row() const;
	int  col() const;
	int  age() const;
	int  health() const;
	bool isPassedOut() const;

	// Mutators
	void  preach();
	void  move(int dir);
	void  getGassed();

private:
	City* m_city;
	int   m_row;
	int   m_col;
	int   m_age;
	int   m_health;
};

class City
{
public:
	// Constructor/destructor
	City(int nRows, int nCols);
	~City();

	// Accessors
	int     rows() const;
	int     cols() const;
	Player* player() const;
	int     flatulanCount() const;
	int     nFlatulansAt(int r, int c) const;
	bool    determineNewPosition(int& r, int& c, int dir) const;
	void    display() const;

	// Mutators
	bool  addFlatulan(int r, int c);
	bool  addPlayer(int r, int c);
	void  preachToFlatulansAroundPlayer();
	void  moveFlatulans();

private:
	int       m_rows;
	int       m_cols;
	Player  * m_player;
	Flatulan* m_flatulans[MAXFLATULANS];
	int       m_nFlatulans;

	// Helper functions
	bool isInBounds(int r, int c) const;
};

class Game
{
public:
	// Constructor/destructor
	Game(int rows, int cols, int nFlatulans);
	~Game();

	// Mutators
	void play();

private:
	City* m_city;
};

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function declarations
///////////////////////////////////////////////////////////////////////////

int decodeDirection(char dir);
int randInt(int min, int max);
void clearScreen();

///////////////////////////////////////////////////////////////////////////
//  Flatulan implementation
///////////////////////////////////////////////////////////////////////////

//the flatulan constructor, creates the flatulans
Flatulan::Flatulan(City* cp, int r, int c)
{
	//make sure the pointer is ponting to some city
	if (cp == nullptr)
	{
		cout << "***** A Flatulan must be created in some City!" << endl;
		exit(1);
	}
	//make sure it is created in bounds
	if (r < 1 || r > cp->rows() || c < 1 || c > cp->cols())
	{
		cout << "***** Flatulan created with invalid coordinates (" << r << ","
			<< c << ")!" << endl;
		exit(1);
	}
	m_city = cp;
	m_row = r;
	m_col = c;
}

int Flatulan::row() const
{
	return m_row;
}

int Flatulan::col() const
{
	return m_col;
}

void Flatulan::move()
{
	// Attempt to move in a random direction; if we can't move, don't move.
	// If the player is there, don't move.
	int dir = randInt(0, NUMDIRS - 1);// dir is now UP, DOWN, LEFT, or RIGHT
	int tempRow = row();
	int tempCol = col();
	//make sure it is inBounds etc.
	if (m_city->determineNewPosition(tempRow, tempCol, dir))
	{
		if (((m_city->player())->row() != tempRow) || ((m_city->player())->col() != tempCol))
		{
			m_row = tempRow;
			m_col = tempCol;
		}
	}
}

//if the player tries to preach there is a 2/3  probability of the flatulan converting
bool Flatulan::possiblyGetConverted()  // return true if converted
{
	int number = randInt(1, 3);
	if (number > 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

///////////////////////////////////////////////////////////////////////////
//  Player implementations
///////////////////////////////////////////////////////////////////////////

//creating/adding the player
Player::Player(City* cp, int r, int c)
{
	if (cp == nullptr)
	{
		cout << "***** The player must be created in some City!" << endl;
		exit(1);
	}
	if (r < 1 || r > cp->rows() || c < 1 || c > cp->cols())
	{
		cout << "**** Player created with invalid coordinates (" << r
			<< "," << c << ")!" << endl;
		exit(1);
	}
	m_city = cp;
	m_row = r;
	m_col = c;
	m_age = 0;
	//initialize the health
	m_health = 10;
}

int Player::row() const
{
	return m_row; 
}

int Player::col() const
{
	return m_col;
}

int Player::age() const
{
	return m_age;
}

int Player::health() const
{
	return m_health; 
}

//makes sure the player hasn't lost all lives yet
bool Player::isPassedOut() const
{
	if (m_health <= 0)
		return true;
	return false; 
}

//calls the preach to flatulans around player function in the city constructor
void Player::preach()
{
	m_age++;
	m_city->preachToFlatulansAroundPlayer();
}

//moves the player in an inputted direction
void Player::move(int dir)
{
	m_age++;
	int playerRow = m_row;
	int playerCol = m_col;
	m_city->determineNewPosition(playerRow, playerCol, dir);
	if (m_city->nFlatulansAt(playerRow, playerCol) == 0)
	{
		m_row = playerRow;
		m_col = playerCol;
	}
}
//if the player gets gassed they lose a life
void Player::getGassed()
{
	m_health--;
}

///////////////////////////////////////////////////////////////////////////
//  City implementations
///////////////////////////////////////////////////////////////////////////

//the city constructor
City::City(int nRows, int nCols)
{
	if (nRows <= 0 || nCols <= 0 || nRows > MAXROWS || nCols > MAXCOLS)
	{
		cout << "***** City created with invalid size " << nRows << " by "
			<< nCols << "!" << endl;
		exit(1);
	}
	m_rows = nRows;
	m_cols = nCols;
	m_player = nullptr;
	m_nFlatulans = 0;
}

//city destructor
City::~City()
{
	if (m_player != nullptr)
	{
		delete m_player;
	}
	for (int k = 0; k < m_nFlatulans; k++)
	{
		if (m_flatulans[k] != nullptr)
		{
			delete m_flatulans[k];
		}
	}
}

int City::rows() const
{
	return m_rows; 
}

int City::cols() const
{
	return m_cols;
}

Player* City::player() const
{
	return m_player;
}

int City::flatulanCount() const
{
	return m_nFlatulans;
}

//checks to see how man flatulans at a specific time 
int City::nFlatulansAt(int r, int c) const
{
	int counter = 0;
	for (int i = 0; i < flatulanCount(); i++)
	{
		if ((m_flatulans[i]->row() == r) && (m_flatulans[i]->col() == c))
		{
			counter++;
		}
	}
	return counter;
}
//determines the position once a player/flatulan is moved, makes sure is in bounds etc. 
bool City::determineNewPosition(int& r, int& c, int dir) const
{
	switch (dir)
	{
		case UP:
			if (isInBounds(r - 1, c))
				r--;
			break;
		case DOWN:
			if (isInBounds(r + 1, c))
				r++;
			break;
		case LEFT:
			if (isInBounds(r, c - 1))
				c--;
			break;
		case RIGHT:
			if (isInBounds(r,c + 1))
				c++;
			break;
		default:
			return false;
	}
	return true;
}

void City::display() const
{
	char grid[MAXROWS][MAXCOLS];
	int r, c;

	// Fill the grid with dots
	for (r = 0; r < rows(); r++)
		for (c = 0; c < cols(); c++)
			grid[r][c] = '.';

	//fills the grid with F, or a digit depending oon how many flatulans are at a point
	for (r = 0; r < rows(); r++)
	{
		for (c = 0; c < cols(); c++)
		{
			if (nFlatulansAt(r + 1, c + 1) == 1)
				grid[r][c] = 'F';
			else if (nFlatulansAt(r + 1, c + 1) >= 9)
				grid[r][c] = '9';
			else if (nFlatulansAt(r + 1, c + 1) > 1 && nFlatulansAt(r + 1, c + 1) < 9)
			{
				grid[r][c] = nFlatulansAt(r + 1, c + 1) + 48;
			}
		}
	}

	// Indicate player's position
	if (m_player != nullptr)
	{
		// Set the char to '@', unless there's also a Flatulan there
		// (which should never happen), in which case set it to '*'.
		char& gridChar = grid[m_player->row()- 1][m_player->col() - 1];
		if (gridChar == '.')
			gridChar = '@';
		else
			gridChar = '*';
	}

	// Draw the grid
	clearScreen();
	for (r = 0; r < rows(); r++)
	{
		for (c = 0; c < cols(); c++)
			cout << grid[r][c];
		cout << endl;
	}
	cout << endl;

	// Write message, Flatulan, and player info
	cout << "There are " << m_nFlatulans << " unconverted Flatulans remaining." << endl;
	if (m_player == nullptr)
		cout << "There is no player." << endl;
	else
	{
		if (m_player->age() > 0)
			cout << "The player has lasted " << m_player->age() << " steps." << endl;
		if (m_player->isPassedOut())
			cout << "The player has passed out." << endl;
		else
			cout << "The player's health level is " << m_player->health() << endl;
	}
}

//you add a flatulan at the generated position
bool City::addFlatulan(int r, int c)
{
	if (!isInBounds(r, c))
	{
		return false;
	}
	// Don't add a Flatulan on a spot with a player
	else if (m_player != nullptr  &&  (m_player->row()) == r  &&  (m_player->col()) == c)
	{
		return false;
	}
	else if (m_nFlatulans == MAXFLATULANS)
	{
		return false;
	}
	//creates new Flatulan at a position
	else
	{
		Flatulan *f1 = new Flatulan(this, r, c);
		m_flatulans[m_nFlatulans] = f1;
		//increments flatulan count
		m_nFlatulans++;
		return true;
	}
}


bool City::addPlayer(int r, int c)
{
	if (!isInBounds(r, c))
		return false;

	// Don't add a player if one already exists
	if (m_player != nullptr)
		return false;

	// Don't add a player on a spot with a Flatulan
	if (nFlatulansAt(r, c) > 0)
		return false;

	// Dynamically allocate a new Player and add it to the city
	m_player = new Player(this, r, c);
	return true;
}

//makes sure the player preaches to a Flatulan if it is in eight directions around the player and the players hits enter
void City::preachToFlatulansAroundPlayer()
{
	int tmp = m_nFlatulans;
	for (int k = 0; k < m_nFlatulans; k++)
	{
		int x = (m_flatulans[k]->col()) - (m_player->col());
		int y = (m_flatulans[k]->row()) - (m_player->row());
		//checks to see if it is one of the eight directions
		if (((x == 1) || (x == -1) ||(x == 0)) && ((y == 1)|| (y == 0) || (y == -1)))
		{
			//if the flatulan gets converted 
			if (m_flatulans[k]->possiblyGetConverted())
			{
				//delete the object that it was pointing to since it is destroyed
				delete m_flatulans[k];
				m_flatulans[k] = nullptr;
				tmp--;
			}
		}
	}
	for (int k = 0; k < m_nFlatulans; k++)
	{
		//assign the value to nullptr so it is not a dangling ptr
		if (m_flatulans[k] == nullptr)
		{
			//move everything up one position
			for (int j = k + 1; j < m_nFlatulans; j++)
			{
				if (m_flatulans[j] != nullptr)
				{
					m_flatulans[k] = m_flatulans[j];
					//assigns last pointer to NULL
					m_flatulans[j] = nullptr;
					break;
				}
			}
		}
	}
	//change the number of flatulans if one gets deleted
	m_nFlatulans = tmp;
}

//moves the flatulans in a randomly generated direction
void City::moveFlatulans()
{
	for (int k = 0; k < m_nFlatulans; k++)
	{
		m_flatulans[k]->move();
		//if the player is orthognal to the flatulans new position it gets gassed
		if (((m_flatulans[k]->row()) == (player()->row() + 1) && (m_flatulans[k]->col() == player()->col())) ||
			((m_flatulans[k]->row()) == (player()->row() - 1) && (m_flatulans[k]->col() == player()->col())) ||
			((m_flatulans[k]->row()) == (player()->row()) && (m_flatulans[k]->col() == player()->col() + 1))||
			((m_flatulans[k]->row()) == (player()->row()) && (m_flatulans[k]->col() == player()->col() - 1)))
		{
			player()->getGassed();
		}
	}
}

bool City::isInBounds(int r, int c) const
{
	return (r >= 1 && r <= m_rows  &&  c >= 1 && c <= m_cols);
}

///////////////////////////////////////////////////////////////////////////
//  Game implementations
///////////////////////////////////////////////////////////////////////////

Game::Game(int rows, int cols, int nFlatulans)
{
	if (nFlatulans < 0)
	{
		cout << "***** Cannot create Game with negative number of Flatulans!" << endl;
		exit(1);
	}
	if (nFlatulans > MAXFLATULANS)
	{
		cout << "***** Trying to create Game with " << nFlatulans
			<< " Flatulans; only " << MAXFLATULANS << " are allowed!" << endl;
		exit(1);
	}
	if (rows == 1 && cols == 1 && nFlatulans > 0)
	{
		cout << "***** Cannot create Game with nowhere to place the Flatulans!" << endl;
		exit(1);
	}

	// Create city
	m_city = new City(rows, cols);

	// Add player
	int rPlayer = randInt(1, rows);
	int cPlayer = randInt(1, cols);
	m_city->addPlayer(rPlayer, cPlayer);

	// Populate with Flatulans
	while (nFlatulans > 0)
	{
		int r = randInt(1, rows);
		int c = randInt(1, cols);
		// Don't put a Flatulan where the player is
		if (r == rPlayer  &&  c == cPlayer)
			continue;
		m_city->addFlatulan(r, c);
		nFlatulans--;
	}
}



Game::~Game()
{
	delete m_city;
}

void Game::play()
{
	m_city->display();
	Player* p = m_city->player();
	if (p == nullptr)
		return;

	while (!p->isPassedOut() && m_city->flatulanCount() > 0)
	{
		cout << "Move (u/d/l/r//q): ";
		string action;
		getline(cin, action);
		if (action.size() == 0)  // player preaches
			p->preach();
		else
		{
			switch (action[0])
			{
			default:   // if bad move, nobody moves
				cout << '\a' << endl;  // beep
				continue;
			case 'q':
				return;
			case 'u':
			case 'd':
			case 'l':
			case 'r':
				p->move(decodeDirection(action[0]));
				break;
			}
		}
		m_city->moveFlatulans();
		m_city->display();
	}
	if (p->isPassedOut())
		cout << "You lose." << endl;
	else
		cout << "You win." << endl;
}

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function implementations
///////////////////////////////////////////////////////////////////////////

int decodeDirection(char dir)
{
	switch (dir)
	{
	case 'u':  return UP;
	case 'd':  return DOWN;
	case 'l':  return LEFT;
	case 'r':  return RIGHT;
	}
	return -1;  // bad argument passed in!
}

// Return a random int from min to max, inclusive
int randInt(int min, int max)
{
	if (max < min)
		swap(max, min);
	static random_device rd;
	static mt19937 generator(rd());
	uniform_int_distribution<> distro(min, max);
	return distro(generator);
}
void thisFunctionWillNeverBeCalled()
{
	// If the student deleted or changed the interfaces to the public
	// functions, this won't compile.  (This uses magic beyond the scope
	// of CS 31.)

	Flatulan(static_cast<City*>(0), 1, 1);
	CHECKTYPE(&Flatulan::row, int  (Flatulan::*)() const);
	CHECKTYPE(&Flatulan::col, int  (Flatulan::*)() const);
	CHECKTYPE(&Flatulan::move, void (Flatulan::*)());
	CHECKTYPE(&Flatulan::possiblyGetConverted, bool (Flatulan::*)());

	Player(static_cast<City*>(0), 1, 1);
	CHECKTYPE(&Player::row, int  (Player::*)() const);
	CHECKTYPE(&Player::col, int  (Player::*)() const);
	CHECKTYPE(&Player::age, int  (Player::*)() const);
	CHECKTYPE(&Player::health, int  (Player::*)() const);
	CHECKTYPE(&Player::isPassedOut, bool (Player::*)() const);
	CHECKTYPE(&Player::preach, void (Player::*)());
	CHECKTYPE(&Player::move, void (Player::*)(int));
	CHECKTYPE(&Player::getGassed, void (Player::*)());

	City(1, 1);
	CHECKTYPE(&City::rows, int     (City::*)() const);
	CHECKTYPE(&City::cols, int     (City::*)() const);
	CHECKTYPE(&City::player, Player* (City::*)() const);
	CHECKTYPE(&City::flatulanCount, int     (City::*)() const);
	CHECKTYPE(&City::nFlatulansAt, int     (City::*)(int, int) const);
	CHECKTYPE(&City::determineNewPosition, bool    (City::*)(int&, int&, int) const);
	CHECKTYPE(&City::display, void    (City::*)() const);
	CHECKTYPE(&City::addFlatulan, bool    (City::*)(int, int));
	CHECKTYPE(&City::addPlayer, bool    (City::*)(int, int));
	CHECKTYPE(&City::preachToFlatulansAroundPlayer, void (City::*)());
	CHECKTYPE(&City::moveFlatulans, void    (City::*)());

	Game(1, 1, 1);
	CHECKTYPE(&Game::play, void (Game::*)());
}

void doBasicTests()
{
	{
		City walk(10, 20);
		assert(walk.addPlayer(2, 6));
		Player* pp = walk.player();
		assert(pp->row() == 2 && pp->col() == 6 && !pp->isPassedOut());
		pp->move(UP);
		assert(pp->row() == 1 && pp->col() == 6 && !pp->isPassedOut());
		pp->move(UP);
		assert(pp->row() == 1 && pp->col() == 6 && !pp->isPassedOut());
		for (int k = 1; k <= 9; k++)
			pp->getGassed();
		assert(!pp->isPassedOut());
		pp->getGassed();
		assert(pp->isPassedOut());
	}
	{
		City ofAngels(2, 2);
		assert(ofAngels.addPlayer(1, 1));
		assert(ofAngels.addFlatulan(2, 2));
		Player* pp = ofAngels.player();
		ofAngels.moveFlatulans();
		assert(!pp->isPassedOut());
		for (int k = 0; k < 1000 && !pp->isPassedOut(); k++)
			ofAngels.moveFlatulans();
		assert(pp->isPassedOut());
	}
	{
		City ousDarth(2, 2);
		assert(ousDarth.addPlayer(1, 1));
		for (int k = 0; k < 50; k++)
		{
			assert(ousDarth.addFlatulan(1, 2));
			assert(ousDarth.addFlatulan(2, 2));
		}
		ousDarth.preachToFlatulansAroundPlayer();
		assert(ousDarth.nFlatulansAt(1, 1) == 0);
		assert(ousDarth.nFlatulansAt(2, 1) == 0);
		for (int r = 1; r <= 2; r++)
		{	   // .9999 probability that between 5 and 29 out of 50 are
			   // unconverted
			int n = ousDarth.nFlatulansAt(r, 2);
			assert(n >= 5 && n <= 29);
		}
		int m = ousDarth.nFlatulansAt(1, 2);
		ousDarth.addFlatulan(1, 2);
		assert(ousDarth.nFlatulansAt(1, 2) == m + 1);
	}
	cout << "Passed all basic tests" << endl;
}




///////////////////////////////////////////////////////////////////////////
//  main()
///////////////////////////////////////////////////////////////////////////
int main()
{
	doBasicTests(); // Remove this line after completing test.
	return 0;       // Remove this line after completing test.
	// Create a game
	// Use this instead to create a mini-game:   Game g(3, 4, 2);
	Game g(7, 8, 25);
	

	// Play the game
	g.play();
}

///////////////////////////////////////////////////////////////////////////
//  clearScreen implementation
///////////////////////////////////////////////////////////////////////////

// DO NOT MODIFY OR REMOVE ANY CODE BETWEEN HERE AND THE END OF THE FILE!!!
// THE CODE IS SUITABLE FOR VISUAL C++, XCODE, AND g++ UNDER LINUX.

// Note to Xcode users:  clearScreen() will just write a newline instead
// of clearing the window if you launch your program from within Xcode.
// That's acceptable.  (The Xcode output window doesn't have the capability
// of being cleared.)

#ifdef _MSC_VER  //  Microsoft Visual C++

#include <windows.h>

void clearScreen()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	COORD upperLeft = { 0, 0 };
	DWORD dwCharsWritten;
	FillConsoleOutputCharacter(hConsole, TCHAR(' '), dwConSize, upperLeft,
		&dwCharsWritten);
	SetConsoleCursorPosition(hConsole, upperLeft);
}

#else  // not Microsoft Visual C++, so assume UNIX interface

#include <iostream>
#include <cstring>
#include <cstdlib>

void clearScreen()  // will just write a newline in an Xcode output window
{
	static const char* term = getenv("TERM");
	if (term == nullptr || strcmp(term, "dumb") == 0)
		cout << endl;
	else
	{
		static const char* ESC_SEQ = "\x1B[";  // ANSI Terminal esc seq:  ESC [
		cout << ESC_SEQ << "2J" << ESC_SEQ << "H" << flush;
	}
}

#endif

