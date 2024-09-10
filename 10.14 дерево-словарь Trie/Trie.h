#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <vector>

using namespace std;

const int ALPHABET_SIZE = 26;

struct TrieNode {
    TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;
};

TrieNode* getNewNode();
void insert(TrieNode* root, const string& word);
vector<string> autoComplete(TrieNode* root, const string& prefix);
void collectWords(TrieNode* node, const string& prefix, vector<string>& suggestions);

#endif // TRIE_H
