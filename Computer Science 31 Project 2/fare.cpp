#include <iostream>
#include <string>
using namespace std;
int main()
{
	cout << "Age of rider: ";
	int ageOfRider;
	cin >> ageOfRider;
	cin.ignore(10000, '\n');
	if (ageOfRider < 0)
	{
		cout << " The age must not be negative" << endl;//making sure the entered age makes sense
		cin >> ageOfRider;
	}
	
	cout << "Student? (y/n): ";
	string answer;
	getline(cin, answer);
	if (answer != "y" && answer != "n")//making sure they enter a valid yes or no answer
	{
		cout << "You must enter y or n " << endl;
		getline(cin, answer);
	}
	cout << "Destination: ";//defining the rider's destination
	string destination;
	getline(cin, destination);
	if (destination == "")//making sure that a destination is enter to evaluate the fair
	{
		cout << "You must enter a destination "<<endl;
		getline(cin, destination);
	}
	cout << "Number of boundary zones crossed: ";//defining the number of boundary zones crossed in the journey
	int boundaryZones;
	cin >> boundaryZones;
	if (boundaryZones < 0)//making sure the boundary zones aren't negative because that's invalid
	{
		cout << "The number of zone boundaries crossed must not be negative" << endl;
		cin >> boundaryZones;
	}
	cout << "---" << endl;
	
	double fare;//begin defining fare and its different discounts for groups of people
	if (ageOfRider < 18 && boundaryZones>= 0 && boundaryZones <= 1)//This is for riders under 18 who are traveling across 0-1 boundary zones
	{
		fare = 0.65;
	}
	else if (ageOfRider < 65 && answer == "y" && boundaryZones>= 0 && boundaryZones<= 1)//This is for riders who are students and are traveling across 0-1 boundary zones
	{
		fare = 0.65;
	}
	else if (ageOfRider >= 65 && boundaryZones > 1)//This is for riders who are 65 and older and are traveling across more than one boundary zone
	{
		fare = 0.55 + (boundaryZones * 0.25);
	}
	else if (ageOfRider >= 65 && boundaryZones == 1)//This is for riders who are above the age of 65, but they are students and get a discount since it is only one boundary zone
	{
		fare = 0.65;
	}
	else if (ageOfRider >= 65 && boundaryZones == 0)//This is for riders who are 65 and older and are traveling across 0 boundary zones
	{
		fare = 0.45;
	}
	else //This is for bus riders who recieve no discounts (above 18, not a student, younger than 65)
	{
		fare = 1.35 + (boundaryZones * 0.55);
	}
	cout << "The fare to " << destination << " is $" << fare << endl;//ending statement*/
}