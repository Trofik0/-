#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Trie.h"

using namespace std;

int main() {
    TrieNode* root = getNewNode();

    // Добавляем слова из словаря в Trie
    vector<string> dictionary = {"apple", "ape", "application", "april", "banana", "bell", "book"};
    for (const string& word : dictionary) {
        insert(root, word);
    }

    while (true) {
        cout << "Enter a word prefix: ";
        string prefix;
        cin >> prefix;

        // Находим все слова, которые начинаются с введенного префикса
        vector<string> suggestions = autoComplete(root, prefix);

        if (suggestions.empty()) {
            cout << "No suggestions found." << endl;
        } else {
            cout << "Suggestions:" << endl;
            for (const string& word : suggestions) {
                cout << "- " << word << endl;
            }
        }

        cout << endl;
    }

    return 0;
}
