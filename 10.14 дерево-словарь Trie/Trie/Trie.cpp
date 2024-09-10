#include "Trie.h"

TrieNode* getNewNode() {
    TrieNode* node = new TrieNode;
    node->isEndOfWord = false;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        node->children[i] = nullptr;
    }
    return node;
}

void insert(TrieNode* root, const string& word) {
    TrieNode* node = root;
    for (char c : word) {
        int index = c - 'a';
        if (!node->children[index]) {
            node->children[index] = getNewNode();
        }
        node = node->children[index];
    }
    node->isEndOfWord = true;
}

vector<string> autoComplete(TrieNode* root, const string& prefix) {
    TrieNode* node = root;
    vector<string> suggestions;
    for (char c : prefix) {
        int index = c - 'a';
        if (!node->children[index]) {
            return suggestions;
        }
        node = node->children[index];
    }
    collectWords(node, prefix, suggestions);
    return suggestions;
}

void collectWords(TrieNode* node, const string& prefix, vector<string>& suggestions) {
    if (node->isEndOfWord) {
        suggestions.push_back(prefix);
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i]) {
            char c = 'a' + i;
            collectWords(node->children[i], prefix + c, suggestions);
        }
    }
}
