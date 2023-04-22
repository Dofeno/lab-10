#include <stdio.h>
#include<string.h>
#include <stdlib.h>
// Lab 10: Implement Trie


// Struct
struct Trie {

    struct Trie* next[26]; // Pointer to all characters
    int occurrence; // Counter for occurrences
};



// FUNCTION: Insert New Word Pathway
void insert(struct Trie **ppTrie, char *word) {

    // Struct Pointer
    struct Trie *pTrie = *ppTrie;

    // If Empty Initialize New Node
    if(!pTrie) {
        pTrie = (struct Trie*)calloc(1, sizeof(struct Trie));
        *ppTrie = pTrie;
    }

    // Add To Connecting Nodes To Complete Word Path
    for(int i = 0; word[i] != '\0'; i++) {
        char c = word[i];
        if(c >= 'a' && c <= 'z') {
            c -= 'a';

            if(!pTrie -> next[c]) {
                pTrie -> next[c] = (struct Trie*)calloc(1, sizeof(struct Trie));
            }

            pTrie = pTrie -> next[c];
        }
    }
    pTrie -> occurrence++;
}


// FUNCTION: Return Occurrences Of Desired Word
int numberOfOccurrences(struct Trie *pTrie, char *word) {

    // Check If Empty
    if (!pTrie) {
        return 0;
    }

    // Searching and Retrieving Number Of Occurrences From Last Node Of Word
    for (int i = 0; word[i] != '\0'; i++) {
        char c = word[i];
        if (c >= 'a' && c <= 'z') {
            c -= 'a';
            pTrie = pTrie->next[c];
            if (!pTrie) {
                return 0;
            }
        }
    }

    // Return Occurrence Count
    return pTrie -> occurrence;
}


// FUNCTION: Used To Deallocate Tree Memory
struct Trie* deallocateTrie(struct Trie* pTrie) {

    if(!pTrie) {
        return NULL;
    }

    // Search and Free Each Index
    for(int i = 0; i < 26; i++) {
        pTrie -> next[i] = deallocateTrie(pTrie -> next[i]);
    }

    free(pTrie);
    return NULL;
}



// Main Driver
int main() {

    // Initiate Dictionary
    struct Trie* myTrie = NULL;
    // Iteration Variable
    int i;

    // Added Words To Trie
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};

    // Inserting Words To Dictionary
    for(i = 0; i < 5; i++ ) {
        insert(&myTrie, pWords[i]);
    }

    // Print Dictionary 7 Number Of Occurrences
    for(i = 0; i < 5; i++) {
        printf("\t%s: %d\n", pWords[i], numberOfOccurrences(myTrie, pWords[i]));
    }

    // Deallocate Trie
    myTrie = deallocateTrie(myTrie);

    if(myTrie != NULL) {
        printf("\n\nThere is an error in the program");
    }
    return 0;
}
