#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <iso646.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

/* May use only ENGLISH capital letters and symbols: + and = */

void read_msg();
void print_table();
void print_result();
void make_alphabet();

float start;
char msg[100];
int stats[256 + 10] = { 0 };
char alphabet[20];
int count_words = 0, count_let = 0;
char words[50][50];
int index_result = 0;
short vec_result[10];
bool used[10];
int numbers[10] = { 0 };

int result = 0;
int lens[10];

void brec(int pos) {

    if (pos == count_let) {
        
        for(int i = 0; i <= count_words; i++) {

            for(int j = 0; j < lens[i]; j++) {

                for(int q = 0; q < count_let; q++) {

                    if(words[i][j] == alphabet[q]) {
                        if(vec_result[q] == 0 and j == 0)
                            numbers[i] = 10;
                        else
                            numbers[i] = numbers[i] * 10 + vec_result[q];
                    }
                }

            }
        }

        for(int i = 0; i <= count_words - 1; i++) {
            result += numbers[i];
        }

        if(result == numbers[count_words]) {
           //print_result();

           printf("Time:\n\t%f sec\n", (clock() - start) / CLOCKS_PER_SEC);

           for(int i = 0; i < count_words; i++) {
            printf("+%d", numbers[i]);
           }

           printf("=%d", numbers[count_words]);

           exit(0);
        }

        memset(&result, 0, 4);

        memset(numbers, 0, 40);

        return;
    }

    for (int i = 0; i < 10; i++) {
        
        if (!used[i]) {

            used[i] = true;

            vec_result[pos] = i;
 
            brec(pos + 1);
     
            vec_result[pos] = 0;
            
            used[i] = false;
        }
    }
}

int main() {

    read_msg();

    srand(time(NULL));

    start = clock();

    //print_table();

    make_alphabet();

    brec(0);

    //printf("No solutions\n");

    printf("Time:\n\t%f sec\n", (clock() - start) / CLOCKS_PER_SEC);

    return -1;
}

void read_msg() {

    scanf("%[A-Z, ,+,=]", msg);

    int len_word = 0;

    int len_msg = strlen(msg);

    for(int i = 0; i < len_msg; i++) {

        if(isalpha(msg[i])) {
            words[count_words][len_word] = msg[i];
            stats[msg[i]]++;
            len_word++;
        }
        else if (msg[i] == '+') {
            lens[count_words] = len_word;
            count_words++;
            len_word = 0;
        }
        else if (msg[i] == '=') {
            lens[count_words] = len_word;
            count_words++;
            len_word = 0;
            index_result = i + 1;
        }
    }

    words[count_words][len_word] = '\0';

    assert(count_words <= 7 and count_words != 0);

    assert(index_result != 0);
}

void print_table() {

    printf("Task:\n");

    for(int i = 0; i <= count_words; i++) {
        if(i == count_words / 2) 
            printf("\t+ %s\n", words[i]);
        else if(i == count_words - 1)
            printf("\t  -----\n\t  %s\n", words[i]);
        else
            printf("\t  %s\n", words[i]);
    }
}

void make_alphabet() {

    for(int i = 0; i < 256; i++) {
        if(stats[i] > 0) {
            alphabet[count_let] = i;
            count_let++;
        }
    }

    assert(count_let <= 10);
}

void print_result() {

    printf("Solution:\n");

    for(int i = 0; i <= count_words; i++) {
        if(i == count_words / 2) 
            printf("\t+ %d\n", numbers[i]);
        else if(i == count_words - 1)
            printf("\t  -----\n\t  %d\n", numbers[i]);
        else
            printf("\t  %d\n", numbers[i]);
    }
}
