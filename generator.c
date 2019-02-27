#include "genName.h"

int checkRule(t_rule *rule, char **name, int *length, char letter) {
    bool vowel = false;
    if (rule->letter != 'a' && (rule->letter == 'c' && isVowel(letter)) ) return (0);
    if (rule->letter != 'a' && (rule->letter == 'v' && isConsonant(letter))) return(0);
    if (rule->letter == 'v') vowel = true;

    if ((vowel && isVowel(letter)) || (!vowel && isConsonant(letter)) || (rule->letter == 'a'))  {
        **name = letter;
        *length += 1;
        *name += 1;
        return (1);
    }
    return (0);
}

int generateFirstLetter(t_options *options, t_alphabet *alphabet) {
    int dice;

    if (options->firstLetter == 'v') dice = 1;
    else if (options->firstLetter == 'c') dice = 0;
    else dice = rand() % 2;

    if (dice) return alphabet->vowels[rand() % 5];
    return alphabet->consonants[rand() % 21];
}

char    *getName(t_alphabet *alphabet, t_options *options, int size) {
    char    *name;
    char    *strIt;
    char    letter;
    int length;

    name = malloc(sizeof(char) * size + 1);
    bzero(name, size + 1);
    strIt = name;
    *strIt++ = generateFirstLetter(options, alphabet);
    length = 1;
    while (length < size) {
        letter = alphabet->letters[rand() % 25];
        if (isVowel(letter)) checkRule(options->vowelRule, &strIt, &length, letter);
        else checkRule(options->consonantRule, &strIt, &length, letter);
    }
    return (name);
}



void generateName(t_alphabet *alphabet, t_options *options, int amount, int size) {
    char    *name;
    while(amount--) {
        name = getName(alphabet, options, size);
        printf("%s\n", name);
        free(name);
    }
}

