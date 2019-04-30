//Jonathan Pham
//CS4280 P3
//04/29/19

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"
#include "node.h"
#include "testTree.h"
#include "identifierStack.h"

char *tokenNames[] = {
                "BEGINTk", "ENDTk", "LOOPTk", "VOIDTk", "INTTk", "RETURNTk", "READTk", "OUTPUTTk", "PROGRAMTk", "IFFTk", "THENTk", "LETTk",



"EOFTk", "IDTk", "INTEGERTk", "EQTk", "LESSTk", "GREATERTk", "COLTk", "PLUSTk", "MINUSTk",
                "MULTTk", "DIVTk", "MODTk", "DOTTk", "LPARENTk", "RPARENTk", "COMMATk", "LEFTBRACETk",
                "RIGHTBRACETk", "SEMICOLTk", "LBRACKTk", "RBRACKTk"

};
static char *labelNames[] = {
    "PROGRAM", "BLOCK", "VARS", "EXPR", "A", "N", "M", "R", "STATS", "MSTAT", "STAT", "IN", "OUT", "IF", "LOOP", "ASSIGN", "RO"
};

node * createNode(nodeType label) {
    node *newNode = (node *) malloc(sizeof(node));

    newNode->label = label;

    token tk1 = { .type = NULLtk, .instance = "", .lineNum = 0 };
    token tk2 = { .type = NULLtk, .instance = "", .lineNum = 0 };
    newNode->token1 = tk1;
    newNode->token2 = tk2;

    newNode->child1 = NULL;
    newNode->child2 = NULL;
    newNode->child3 = NULL;
    newNode->child4 = NULL;
    return newNode;
}

void traversePreorder(node *n, int depth) {
    if (n != NULL) {
        visitNode(n, depth);
        traversePreorder(n->child1, depth+1);
        traversePreorder(n->child2, depth+1);
        traversePreorder(n->child3, depth+1);
        traversePreorder(n->child4, depth+1);
    }
}

void visitNode(node *n, int depth) {
    printf("%*s%s", depth*2, "", labelNames[n->label]);

    if (n->token1.type != NULLtk) {
        printf(" {%s, %s, %d}", tokenNames[n->token1.type], n->token1.instance, n->token1.lineNum);
    }
    if (n->token2.type != NULLtk) {
        printf(" {%s, %s, %d}", tokenNames[n->token2.type], n->token2.instance, n->token2.lineNum);
    }

    printf("\n");
}

void staticSemantics(node *n, int *varCount) {
    if (n != NULL) {
        if (n->label == BLOCKnd || n->label == PROGRAMnd) {
            int i;
            int *varCount = (int *) malloc(sizeof(int));
            *varCount = 0;

            preorder(n, varCount);

            for (i = 0; i < *varCount; i++) {
                pop();
            }

            free(varCount);
        }
        else {
            preorder(n, varCount);
        }
    }
}

void preorder(node *n, int *varCount) {
    if (n != NULL) {
        verifyNode(n, varCount);
        staticSemantics(n->child1, varCount);
        staticSemantics(n->child2, varCount);
        staticSemantics(n->child3, varCount);
        staticSemantics(n->child4, varCount);
    }
}

void verifyNode(node *n, int *varCount) {
    if (n->label == VARSnd) {
        if (n->token1.type == IDtk) {
            if (*varCount > 0) {
                find(n->token1, 1);  // set error reporting to type 1
            }
            push(n->token1);
            (*varCount)++;
        }
    }
    else if (n->label == Rnd || n->label == INnd || n->label == ASSIGNnd) {
        if (n->token1.type == IDtk) {
            find(n->token1, 2);  // set error reporting to type 2
        }
    }
}
