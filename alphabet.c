#include "genName.h"

bool isVowel(char letter) {
    if ((letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z'))
        return (letter == 'a' || letter == 'e' || letter == 'i' || letter == 'o' || letter =='u');
    return (false);
}

bool isConsonant(char letter) {
    return !isVowel(letter);
}



void initialize_alphabet(t_alphabet *alphabet) {
    int counter;
    char letter = 'a';

    // fill all letters
    for (counter = 0; counter < 26; counter++) {
        alphabet->letters[counter] = letter++;
    }
    alphabet->letters[26] = '\0';
    // fill just the vowels
    alphabet->vowels[0] = 'a';
    alphabet->vowels[1] = 'e';
    alphabet->vowels[2] = 'i';
    alphabet->vowels[3] = 'o';
    alphabet->vowels[4] = 'u';
    alphabet->vowels[5] = '\0';
    letter = 'b';
    // fill all 
    for (counter = 0; counter < 21; counter++) {
        while(isVowel(letter)) letter++;
        alphabet->consonants[counter] = letter++;
    }
    alphabet->consonants[21] = '\0';
}

