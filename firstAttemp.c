#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <strings.h>
#include <ctype.h>

typedef struct s_alphabet {
    char letters[27];
    char vowels[6];
    char consonants[22];
} t_alph;

// After consonant maybe only vowel
// after vowel maybe another vowel only and only if previous letter is not a vowel. i.e. baa is fine but aaa is not. 
// Name can start with any leter;

bool isVowel(char letter) {
    if ((letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z'))
        return (letter == 'a' || letter == 'e' || letter == 'i' || letter == 'o' || letter =='u');
    return (false);
}

bool isConsonant(char letter) {
    return !isVowel(letter);
}

void initialize_alphabet(t_alph *alphabet) {
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

void generateName(t_alph alphabet, int size) {
    int randomNumber;
    int currentLetter;
    char    *name;

    if (size == 0) size = 6;
    name = malloc(sizeof(char) * size + 1);
    bzero(name, size +1); // null out 
    currentLetter = 0;
    while(currentLetter < size) {
        randomNumber = rand() % 25; // between 0 and 25;
        if (currentLetter == 0) { //pick any first letter
            name[currentLetter++] = toupper(alphabet.letters[randomNumber]);
            continue ;
        }
        // if prev letter is consonant pick any vowel
        if (isConsonant(name[currentLetter - 1])) {
            randomNumber %= 5;
            name[currentLetter++] = alphabet.vowels[randomNumber];
            continue ;
        // if prev letter is vowel check if letter before it isnot a vowel then pick any letter.
        } else if (currentLetter != 1 && isConsonant(name[currentLetter -2])) {
            name[currentLetter++] = alphabet.letters[randomNumber];
            continue ;
        // else pick any consonant
        } else {
            randomNumber %= 21;
            name[currentLetter++] = alphabet.consonants[randomNumber];
        }
    }
    printf("%s\n", name);
    free(name);
}


int main(int argc, char **argv) {
    t_alph alphabet;
    int size;
    int amount;

    if (argc < 2) printf("usage: genName [length] [amount]\nby default length = 6 and amount = 1 \n");
    // initialize time for random number generator
    srand((unsigned) time(NULL));
    size = (argc < 2) ? 6 : atoi(argv[1]);
    amount = (argc < 3) ? 1 : atoi(argv[2]);
    initialize_alphabet(&alphabet);
    while(amount--) {
        generateName(alphabet, size);
    }
    return(0);
}



// Be able to parse a file to get a new schema for name generation. schema in my case was :
 
// After consonant maybe only vowel
// after vowel maybe another vowel only and only if previous letter is not a vowel. i.e. baa is fine but aaa is not. 
// Name can start with any leter;
// regex ?? nope
// schema rules should be based around vowes or const something
// schema devites with these categories
// 1. First letter : v (for vowel only) c (for consonants) a (for any)
// 2. What can go after vowels : (v for vowels) c (for consonants) a(for any) v?N ( for vowels with addition rule vowels chain can be max N letters.) 
// 3. What can go after consonants : v (for vowels)  c (for consonants) a (for any) c?N(for consonants with addition rule consonants chain can be max N letters)
// 4. Last Letter : v (for vowel only) c (for consonants) a (for any)

// steps are going to be separated by []

// example of schema used above: [a][a?2][v][a] 
// posiblle addition is [a|v?2|c?2] means can be either v or c but if it is vowel make sure that previous 2 letters are not vowel same for c

// Get args, send them to parser to fill the sruct options

// struct options {
//   char firstLetter; // can be 'a' or 'c' or 'v'
//   struct rule *vowelRule;
//   struct rule *consonantRule;
//   char lastLetter;
// }

// struct rule {
//   char letter; // can be 'a' or 'c' or 'v'
//   int vowelChainLength; // can be obtain from a?N or v?N  (N is our number)
//   int consonantsChainLength; // can be obtain from a?N or c?N (N is our number)   
// }



// send the options to generate name


// getFirstLetter
// Get letter
// check if letter is vowel or consonant
// if vowel -> use vowelRule from options
// if consonant -> use consonantRule from options
// What to check? if rule.letter works can be 'a' or respectively 'c' 'v' respectively check Chain rule
// if yes return letter
// if no repeat