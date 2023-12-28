#include <bits/stdc++.h>
using namespace std;

const int ALPHABET_SIZE = 26;
struct TrieNode {
	struct TrieNode* children[ALPHABET_SIZE];
	bool isEndOfWord;
};

struct TrieNode* getNode(void){
	struct TrieNode* pNode = new TrieNode;
	pNode->isEndOfWord = false;
	for (int i = 0; i < ALPHABET_SIZE; i++)
		pNode->children[i] = NULL;
	return pNode;
}

void insert(struct TrieNode* root, string key){
	struct TrieNode* pCrawl = root;
	for (int i = 0; i < key.length(); i++) {
		int index = key[i] - 'a';
		if (!pCrawl->children[index])
			pCrawl->children[index] = getNode();

		pCrawl = pCrawl->children[index];
	}

	pCrawl->isEndOfWord = true;
}

bool search(struct TrieNode* root, string key)
{
	struct TrieNode* pCrawl = root;

	for (int i = 0; i < key.length(); i++) {
		int index = key[i] - 'a';
		if (!pCrawl->children[index])
			return false;

		pCrawl = pCrawl->children[index];
	}

	return (pCrawl != NULL && pCrawl->isEndOfWord);
}

bool isEmpty(TrieNode* root)
{
	for (int i = 0; i < ALPHABET_SIZE; i++)
		if (root->children[i])
			return false;
	return true;
}

TrieNode* remove(TrieNode* root, string key, int depth = 0){
	if (!root)
		return NULL;

	if (depth == key.size()) {
		if (root->isEndOfWord)
			root->isEndOfWord = false;

		if (isEmpty(root)) {
			delete (root);
			root = NULL;
		}

		return root;
	}

	int index = key[depth] - 'a';
	root->children[index] = 
		remove(root->children[index], key, depth + 1);
	if (isEmpty(root) && root->isEndOfWord == false) {
		delete (root);
		root = NULL;
	}
	return root;
}

// Driver
int main()
{
	// Input keys (use only 'a' through 'z'
	// and lower case)
	string keys[] = { "the", "a", "there",
					"answer", "any", "by",
					"bye", "their", "hero", "heroplane" };
	int n = sizeof(keys) / sizeof(keys[0]);

	struct TrieNode* root = getNode();

	// Construct trie
	for (int i = 0; i < n; i++)
		insert(root, keys[i]);

	// Search for different keys
	search(root, "the") ? cout << "Yes\n" : cout << "No\n";
	search(root, "these") ? cout << "Yes\n" : cout << "No\n";

	remove(root, "heroplane");
	search(root, "hero") ? cout << "Yes\n" : cout << "No\n";
	return 0;
}
