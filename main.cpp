/* This program uses the STL map to implement a
reverse phone lookup.
@assignment  STL Map Reverse Phone Lookup
@author  Daniel Targonski
@date  12/7/2020
@file  main.cpp
*/

#include<iostream>
#include<map>
#include<fstream>
#include<sstream>
#include<string>

using namespace std;

//Pass name of file from command line
int main(int argc, const char* argv[])
{
	int i{};
	string phoneNumber{};
	ifstream inData(argv[1]);
	bool _continue{ true };
	if (inData.fail())
	{
		cerr << "File failed to open.\n";
		exit(-1);
	}

	char nextChar{};
	map<string, string> phoneDirectory;

	// This loop cycles through each line in the passed file from command line
	// and instantiates all the needed data variables to process through a line at a time.
	while (!inData.eof())
	{
		string nextLine{}, number{}, nextWord{};
		i = 0;
		getline(inData, nextLine);
		bool hitADigit{ false };
		int j{};

		// This loop concatenates each char in the line to a string until it hits a digit.
		// Once a digit is hit, it will start adding the digits to a seperate string.
		// Then these two strings will be added to a map STL object named "phoneDirectory".
		while (i < nextLine.length())
		{
			nextChar = nextLine[i];
			if (!isdigit(nextChar) && hitADigit == false)
				nextWord += nextChar;
			else
			{
				if (isdigit(nextChar))
				{
					number += nextLine[i];
					hitADigit = true;
				}
			}
			i++;
		}
		// This if statement checks to make sure its not inputting an empty key and element
		if (nextWord.length() > 1)
			phoneDirectory.insert(pair<string, string>(number, nextWord));
	}

	i = 1;
	cout << "The phone directory is: \n";
	for (auto&& x : phoneDirectory)
	{
		cout << i << ") " << x.first << " -> " << x.second << endl;
		i++;
	}

	// Prompts the user to search for names by entering phone numbers while user does not
	// input 'x'.
	while (_continue)
	{
		cout << "\n\n" << "Enter a phone number to lookup or enter 'x' to exit: ";
		cin >> phoneNumber;
		if (phoneNumber == "x")
			break;
		// Checks to see if the phone number exists first. If the value is not found then
		// the find method returns the end of the map.
		if (phoneDirectory.find(phoneNumber) != phoneDirectory.end())
			cout << "That number belongs to: " << phoneDirectory.at(phoneNumber);
		else
			cout << "That phone number does not exist in this directory.";
	}

	return 0;
}