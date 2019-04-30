//Jonathan Pham
//CS4280 P3
//04/29/19

#ifndef IDENTIFIERSTACK_H
#define IDENTIFIERSTACK_H

#include "token.h"

#define SIZE 9 // LENGTH + 1

typedef struct identifierElement {
    token tk;
    struct identifierElement *next;
} identifierElement;

typedef struct {
    int size;
    identifierElement *top;
} identifierStack;

void push(token);
void pop();
void find(token, int);

#endif
