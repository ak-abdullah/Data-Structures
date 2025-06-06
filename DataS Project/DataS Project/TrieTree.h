#pragma once
#include<iostream>
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
class trie_node
{
public:
	char data;
	trie_node* child[26];
	bool is_terminal;

	trie_node(char ch)
	{
		data = ch;
		for (int i = 0; i < 26; i++)
		{
			child[i] = NULL;
		}
		is_terminal = false;
	}

	trie_node()
	{
		/*is_terminal = false;
		data = '\0';*/
	}
};

class trie
{
public:
	trie_node* root;

	trie()
	{
		root = new trie_node('\0');
	}

	void insert(trie_node* root, string word);
	void insert_word(string word);
	void savtrietree(fstream&, trie_node*);
	void savetofile();
	trie_node* readtrietree(fstream&, trie_node*);
	void readfromfile();
	void print_suggestions(trie_node* curr, vector<string>& temp, string prefix);
	vector<vector<string>> get_suggestion(string str);
};

