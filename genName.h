#ifndef GENNAME
# define GENNAME

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct s_alphabet {
    char letters[27];
    char vowels[6];
    char consonants[22];

} t_alphabet;

typedef struct s_rule {
    char letter; // can be 'a' or 'c' or 'v'
    int vowelChainLength;
    int consonantChainLength;
} t_rule;


typedef struct s_options {
    char firstLetter;
    char lastLetter;
    t_rule *vowelRule;
    t_rule *consonantRule;
} t_options;

t_options   *generateOptions(char *rule);
void        generateName(t_alphabet *alphabet, t_options *options, int amount, int size);
void        freeOptions(t_options **optionsAddr);
void        initialize_alphabet(t_alphabet *alphabet);
bool        isVowel(char letter);
bool        isConsonant(char letter);


#endif