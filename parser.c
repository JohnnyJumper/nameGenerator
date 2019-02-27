#include "genName.h"


t_options   *createOptions(char firstLetter, char lastLetter,
                           t_rule *vowelRule, t_rule *consonantRule) {

    t_options   *fresh;

    fresh = malloc(sizeof(t_options));
    fresh->firstLetter = firstLetter;
    fresh->lastLetter = lastLetter;
    fresh->vowelRule = vowelRule;
    fresh->consonantRule = consonantRule;

    return (fresh);
}

void        freeOptions(t_options **optionsAddr) {
    free((*optionsAddr)->consonantRule);
    (*optionsAddr)->consonantRule = NULL;
    free((*optionsAddr)->vowelRule);
    (*optionsAddr)->vowelRule = NULL;
    free(*optionsAddr);
    *optionsAddr = NULL;
}

t_rule  *createRule(char *rule) {
    t_rule *fresh;
    bool vowelRule;
    int length;


    fresh = malloc(sizeof(t_rule));
    fresh->letter = *rule++;
    while(*rule) {
        switch(*rule) {
            case '|':
                rule++;
                continue;
            case 'c': 
                vowelRule = false;
                break;
            case 'v':
                vowelRule = true;
                break;
        };
        if (*(rule + 1) && *(rule + 1) == '?' && *(rule + 2)) {
            length = atoi(rule + 2);
        }
        if (vowelRule) 
            fresh->vowelChainLength = length;
        else
            fresh->consonantChainLength = length;
        rule += 3;
    }
    return (fresh);
}



char        getFirstLetter(char **rule) {
    char    letter;
    if (**rule == '[' ) *rule += 1;
    letter = **rule;
    *rule += 2;
    return (letter);
}

char        *parseRule(char **rule) {
    char *singleRule;
    char *str;
    int length;

    length = 0;
    if (**rule == '[') *rule += 1;
    str = *rule;
    while (*str != ']') {
        length++;
        str += 1;
    }
    singleRule = malloc(sizeof(char) * length + 1);
    bzero(singleRule, length + 1);
    strncpy(singleRule, *rule, length);
    *rule = str + 1;   
    return singleRule;
}


t_options   *generateOptions(char *rule) {
    t_options   *options;
    char        firstLetter;
    char        lastLetter;
    t_rule      *vowelRule;
    t_rule      *consonantRule;
    char        *singleRule;

    firstLetter = getFirstLetter(&rule);
    singleRule = parseRule(&rule);
    vowelRule = createRule(singleRule);
    free(singleRule);
    singleRule = parseRule(&rule);
    consonantRule = createRule(singleRule);
    free(singleRule);
    lastLetter = getFirstLetter(&rule);
    options = createOptions(firstLetter, lastLetter, vowelRule, consonantRule);
    return options;
}