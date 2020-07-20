#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

static const int ALPHABET_SIZE = 26;
static const int MAX_LENGTH_OF_WORD = 20;

struct TrieNode {
    TrieNode* children[ALPHABET_SIZE];
    int wordsWithThisPrefix;
    
    TrieNode() {
        for (auto i = 0; i < ALPHABET_SIZE; i++) {
            this->children[i] = nullptr;
        }
        this->wordsWithThisPrefix = 0;
    }
};

class Trie {
private:
    TrieNode* root;
    
    void insert(TrieNode* root, char* word) {
        TrieNode* currChar = root;
        
        for (auto i = 0; word[i] != '\0'; i++) {
            int index = word[i] - 'a';
            if(!currChar->children[index]) {
                currChar->children[index] = new TrieNode();
            }
            currChar->wordsWithThisPrefix++;
            currChar = currChar->children[index];
        }
        
        currChar->wordsWithThisPrefix++;
    }
    
    int search(TrieNode* root, char* word) 
    { 
        TrieNode* currChar = root; 

        for (auto i = 0; i < word[i] != '\0'; i++) 
        { 
            int index = word[i] - 'a';
            if(!currChar->children[index]) {
                return 0;
            }
            currChar = currChar->children[index];
        } 

        return currChar->wordsWithThisPrefix; 
    }  
public:
    Trie() {
        root = new TrieNode();
    }
    
    void insert(char* word) {
        insert(root, word);
    }
    
    int search(char* prefix) {
        return search(root, prefix);
    }
    
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
    
    int n, q;
    cin >> n >> q;
    
    Trie trie;
    
    for (auto i = 0; i < n; i++) {
        char* wordToInsert = new char [MAX_LENGTH_OF_WORD];
        cin >> wordToInsert;
        trie.insert(wordToInsert);
    }
    
    for (auto i = 0; i < q; i++) {
        char* prefixToFind = new char [MAX_LENGTH_OF_WORD];
        cin >> prefixToFind;
        cout << trie.search(prefixToFind) << endl;
    }
    return 0;
}
