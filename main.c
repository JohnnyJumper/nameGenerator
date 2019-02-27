#include "genName.h"

int main(int argc, char **argv) {

    int     amount;
    int     size;
    char    *rule;
    t_alphabet alphabet;
    t_options *options;

    if (argc == 1) {
        printf("usage: genName [nameRule] [size] [amount]\n");
        return(1);
    }

    srand(time(NULL));
    initialize_alphabet(&alphabet);
    amount = (argc == 4) ? atoi(argv[3]) : 1;  
    size = (argc >= 3) ? atoi(argv[2]) : 5;
    if (amount) {;}
    rule = strdup(argv[1]);
    options = generateOptions(rule);
    generateName(&alphabet, options, amount, size);
    freeOptions(&options);
    free(rule);
    return (0);
}