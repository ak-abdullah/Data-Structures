#include"TrieTree.h"
using namespace std;

void trie::insert(trie_node* root, string word)
{
	if (word.length() == 0)
	{
		root->is_terminal = true;
		return;
	}
	int index = word[0] - 'a';
	trie_node* children;
	if (root->child[index] != NULL)
	{
		children = root->child[index];
	}
	else {
		children = new trie_node(word[0]);
		root->child[index] = children;
	}

	insert(children, word.substr(1));
}

void trie::insert_word(string word)
{
	insert(root, word);
}

void trie::print_suggestions(trie_node* curr, vector<string>& temp, string prefix)
{
	if (curr->is_terminal)
	{
		temp.push_back(prefix);
	}

	for (char ch = 'a'; ch <= 'z'; ch++)
	{
		trie_node* next = curr->child[ch - 'a'];
		if (next != NULL)
		{
			prefix.push_back(ch);
			print_suggestions(next, temp, prefix);
			prefix.pop_back();
		}
	}
}

vector<vector<string>> trie::get_suggestion(string str)
{
	trie_node* pre = root;
	vector<vector<string>> output;
	string prefix = "";
	for (int i = 0; i < str.length(); i++)
	{
		char lastch = str[i];
		prefix.push_back(lastch);

		trie_node* curr = pre->child[lastch - 'a'];

		if (curr == NULL)
		{
			break;
		}

		vector <string> temp;
		print_suggestions(curr, temp, prefix);
		output.push_back(temp);
		temp.clear();
		pre = curr;
	}
	return output;
}

void trie::savetofile()
{
	fstream myfile;
	myfile.open("trietree.txt", ios::out);

	savtrietree(myfile, root);
}

void trie:: savtrietree(fstream& myfile, trie_node* root)
{
	if (root == NULL)
	{
		myfile << "#";
		myfile << " ";
		return;
	}

	myfile << root->data;
	myfile << root->is_terminal;
	myfile << " ";

	for (int i = 0; i < 26; i++)
	{
		savtrietree(myfile, root->child[i]);
	}
}
trie_node* trie::readtrietree(fstream& myfile,trie_node *root)
{
	char alph;
	bool terminal;

	myfile >> alph;

	if (!((alph >= 'a' && alph <= 'z') || alph == '\0' || alph == '#'))
		return NULL;

	if (alph == '#')
		return NULL;

	myfile >> terminal;

	if (!(terminal == true || terminal == false))
	{
		cout << terminal;
		return NULL;
	}


	root = new trie_node;
	root->data = alph;
	root->is_terminal = bool(terminal);

	for (int i = 0; i < 26; i++)
		root->child[i] = NULL;

	for (int i = 0; i < 26; i++)
		root->child[i] = readtrietree(myfile, root->child[i]);

	return root;
}

void trie::readfromfile()
{
	fstream myfile;
	myfile.open("trietree.txt", ios::in);

	root = readtrietree(myfile, root);
}