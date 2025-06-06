#include<iostream>
#include<string>
#include<cstring>
#include<conio.h>
#include<stdio.h>
#include<Windows.h>
#include"EndodingDecoding.h"
#include"TrieTree.h"
#include<iomanip>
using namespace std;

int maxxcoordinates()
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD xy;


	CONSOLE_SCREEN_BUFFER_INFO cbsi;

	if (GetConsoleScreenBufferInfo(hOut, &cbsi))
		xy = cbsi.dwMaximumWindowSize;

	return xy.X;
}
void getcursorposition(int &x,int &y)
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD xy;

	CONSOLE_SCREEN_BUFFER_INFO cbsi;

	if (GetConsoleScreenBufferInfo(hOut, &cbsi))
		xy = cbsi.dwCursorPosition;

	x = xy.X;
	y = xy.Y;
}
void gotoxy(int x, int y)
{
	COORD c;
	c.X = x;
	c.X++;
	c.Y = y;

	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE), c);
}

bool givesuggestions(string& sugg, trie*& t, int &ccount)
{

	for (int i = 0; i < sugg.length(); i++)
	{
		if (sugg[i] >= 'A' && sugg[i] <= 'Z')
			return false;
	}

	bool again = false;
	vector<vector<string>> v;
	string input, search;
	search = sugg;
	char option;
	int level = 0, k = 0, count = 0;
	char str[20];

	/*trie* t = new trie();
	ifstream File;*/
	/*file.open("sample.txt");
	if (!file) {
		cout << "error while creating the file";
	}
	else {
		cout << "file found";
	}
	while (!file.eof())
	{
		file >> input;
		t->insert_word(input);
	}
	cout << endl;*/

	string arrs[11];

	/*cout << "Enter Search Element : ";
	cin >> search;*/

	v = t->get_suggestion(search);
	int x = search.length();
	for (auto row_obj : v)
	{
		if (count == 9)
		{
			break;
		}
		for (auto elem : row_obj)
		{
			string str1 = elem;
			int i = 0;
			for (int j = 0; j < search.length(); j++)
			{
				i++;
				if (search[j] == str1[j])
				{
					if (i == x)
					{
						arrs[k] = elem;
						if (k >= 10)
						{
							break;
						}
						k++;
					}
				}
				else {
					break;
				}
			}
		}
		count++;
	}
	
	int c = 0;

	int xaxis, yaxis;
	getcursorposition(xaxis, yaxis);
	cout << endl;
	cout << endl;

	for (int i = 1; i < 11; i++)
	{
		if (arrs[i] == "")
			break;

		c++;

		if (i != 0)
			cout << endl;

		cout << arrs[i];
		
	}

	int x2, y2;
	getcursorposition(x2, y2);

	gotoxy(xaxis, yaxis);

		cout << '\b';

	for (int i = 0; i < 11; i++)
	{
		
		if (arrs[i] == "")
			continue;

		int x3, y3;

		for (int i = 0; i < sugg.length(); i++)
			cout << "\b" << " " << "\b";

		if (ccount + arrs[i].length() - sugg.length() >= maxxcoordinates() - 2) //118
		{
			cout << endl;
			ccount = 0;
		}

		cout << arrs[i];

		option = _getch();

		if (option == '/')
		{
			option = ' ';
		}
		else if (option == ';')
		{
			search = arrs[i];
			break;
		}
		else if ((option >= 'a' && option <= 'z') || (option >= 'A' && option <= 'B') || option == ' ')
		{
			if (option != ' ')
				again = true;

			if (ccount + 1 >= maxxcoordinates() - 2) //118
			{
				cout << endl;
				ccount = 0;
			}

			for (int j = 0; j < arrs[i].length() - sugg.length(); j++)
				cout << "\b" << " " << "\b";

			sugg = sugg + option;
			search = sugg;

			cout << option;
			xaxis++;

			break;
		}

		for (int j = 0; j < arrs[i].length() - sugg.length(); j++)
			cout << "\b" << " " << "\b";

		if (!((option >= 'a' && option <= 'z') || (option >= 'A' && option <= 'Z') || option == ' '))
			break;
	}

	gotoxy(x2, y2);
	cout << '\b';


	for (int j = c; j >= 0 ; j--)
	{
		for (int k = 0; k < arrs[j].length(); k++)
		{
			cout << "\b" << " " << "\b";
		}
		y2--;
	
		if (j > 0)
			gotoxy(arrs[j - 1].length() - 1, y2);
	}

	int len = search.length() - sugg.length();


	if (ccount == 0)
	{
		xaxis = sugg.length();
		yaxis++;
		ccount = search.length();
	}

	gotoxy(xaxis + len, yaxis);
	cout << "\b";
	sugg = search;

	return again;
}
int main()
{
	int press = 0;
	linkedlist file;
	string sen = "";
	int ccount = 0;
	cout << "1. Continue Editing(Load Previous File)\n\n";
	cout << "2. Create New File\n\n";

	cin >> press;
	
	if (press == 1)
	{
		if (!file.readdatafromfile())
			cout << "\nData Failed To Read\n";

		if (!file.decoding(sen))
		{
			cout << "Decoding Failed";
			return 0;
		}
	}

	system("cls");
	int x;
	string input;
	ifstream File;

	File.open("sample.txt");

	trie* t = new trie();

	/*while (!File.eof())
	{
		File >> input;
		t->insert_word(input);      //insertion from dictionary file
	}

	t->savetofile();*/

	t->readfromfile();   //reading trie tree from file

	//input in running tring start

	string sugg = "";
	char ch = '\0';
	linkedlist l;
	cout << sen;
	int a,b;
	getcursorposition(a, b);
	ccount = a;

	while (ch != '|')
	{
		if (ccount >= maxxcoordinates() - 2 && sugg.length() <= 10) //118
		{
			ccount = 0;
			
			for (int i = 0; i < sugg.length(); i++)
				cout << '\b' << " " << "\b";
			cout << endl;

			cout << sugg;
			ccount = sugg.length();

		}
		else if (ccount >= maxxcoordinates() - 2 && sugg.length() >= 10)  //118
		{
			ccount = 0;
			cout << endl;
		}

		
		if (ch != '*')
			ch = _getch();   //

		if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || ch == ' ')
			cout << ch;

		else if (ch != '*')    //
		{
			cout << " ";
			cout << '\b';

			if (ch == '|')
			{
				sen = sen + sugg;
			}

			continue;
		}
		ccount++;

		if (ch != '*')   //
			sugg = sugg + ch;

		if (ch == ' ')
		{
			sen = sen + sugg;

			sugg = "";
		}

		if (sugg.length() < 2)
			continue;

		string temp = sugg;

		if (givesuggestions(sugg, t, ccount))   //
		{
			ch = '*';
			continue;
		}
		else
		{
			ch = '\0';
		}

		ccount = ccount - temp.length() + sugg.length();

		int len = sugg.length() - 1;

		if (sugg[len] == ' ')  
		{
			sen = sen + sugg;
			sugg = "";
		}
	}

	//econding 

	/*cout << endl << endl;
	cout << sen;*/

	int arr[27];


	for (int i = 0; i < 27; i++)
		arr[i] = 0;

	for (int i = 0; i < sen.length(); i++)
	{
		if (sen[i] == ' ')
		{
			arr[26]++;
			continue;
		}
		if (sen[i] >= 'A' && sen[i] <= 'Z')
			sen[i] = sen[i] + 32;
		int index = int(sen[i]) - 97;
		arr[index]++;
	}

	for (int i = 0; i < 26; i++)
	{
		if (arr[i] == 0)
			continue;
		char c = char(i + 97);
		l.insertcharacter(c, arr[i]);
	}

	if (arr[26] != 0)
		l.insertcharacter(' ', arr[26]);

	l.maketree();
	if (!l.savetofile())
		cout << "\nSaving Huffiman Tree Unsucessfull";

	if (!l.encoding(sen))
		cout << "\nEncoding Unsucessful\n";
	else
		cout << "\n\nData Encoded Sucessfully";

	return 0;
}