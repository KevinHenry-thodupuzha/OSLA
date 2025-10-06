#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    int start = 0, length = 0, temp;                
    char locctr[20], label[20], opcode[20], operand[20]; // LOCCTR instead of addr
    char code[10], mnemonic[10];                   
    char symbol[20], symaddr[20];                 

    // Open files
    FILE *inter = fopen("intermediate3.txt", "r");  
    FILE *optab = fopen("optab3.txt", "r");        
    FILE *symtab = fopen("symtab3.txt", "r");      
    FILE *asml = fopen("asml3.txt", "w");          
    FILE *objc = fopen("objc3.txt", "w");          
    FILE *lengthFile = fopen("length3.txt", "r");  

    if (!inter || !optab || !symtab || !asml || !objc || !lengthFile) {
        printf("Error opening files.\n");
        return 1;
    }

    // Read program length
    fscanf(lengthFile, "%d", &length);

    // Read first line of intermediate file
    fscanf(inter, "%s %s %s %s", locctr, label, opcode, operand);

    // Handle START
    if (strcmp(opcode, "START") == 0) {
        start = atoi(operand);
        fprintf(asml, "%s %s %s %s\n", locctr, label, opcode, operand);
        fprintf(objc, "H^%s^%06X^%06X\n", label, start, length);
        fscanf(inter, "%s %s %s %s", locctr, label, opcode, operand);
    }

    fprintf(objc, "T^%06X^", start);

    // Process instructions until END
    while (strcmp(opcode, "END") != 0) {
        int found = 0;
        rewind(optab);

        while (fscanf(optab, "%s %s", code, mnemonic) != EOF) {
            if (strcmp(opcode, code) == 0) {
                found = 1;
                rewind(symtab);
                int symfound = 0;
                while (fscanf(symtab, "%s %s", symbol, symaddr) != EOF) {
                    if (strcmp(symbol, operand) == 0) {
                        fprintf(objc, "%s%s^", mnemonic, symaddr);
                        fprintf(asml, "%s %s %s %s %s%s\n", locctr, label, opcode, operand, mnemonic, symaddr);
                        symfound = 1;
                        break;
                    }
                }
                if (!symfound) {
                    fprintf(objc, "%s0000^", mnemonic);
                    fprintf(asml, "%s %s %s %s %s0000\n", locctr, label, opcode, operand, mnemonic);
                }
                break;
            }
        }

        // Handle assembler directives
        if (!found) {
            if (strcmp(opcode, "WORD") == 0) {
                temp = atoi(operand);
                fprintf(objc, "%06X^", temp);
                fprintf(asml, "%s %s %s %s %06X\n", locctr, label, opcode, operand, temp);
            } else if (strcmp(opcode, "BYTE") == 0) {
                char objcode[50] = "";
                for (int i = 2; i < strlen(operand)-1; i++) {
                    char temphex[3];
                    sprintf(temphex, "%02X", operand[i]);
                    strcat(objcode, temphex);
                    fprintf(objc, "%s", temphex); // write object code to file
                }
                fprintf(objc, "^");
                fprintf(asml, "%s %s %s %s %s\n", locctr, label, opcode, operand, objcode);
            } else {
                fprintf(asml, "%s %s %s %s\n", locctr, label, opcode, operand);
            }
        }

        // Read next line
        fscanf(inter, "%s %s %s %s", locctr, label, opcode, operand);
    }

    // Print END line
    fprintf(asml, "%s %s %s %s\n", locctr, label, opcode, operand);
    fprintf(objc, "\nE^%06X\n", start);

    fclose(inter); fclose(optab); fclose(symtab);
    fclose(asml); fclose(objc); fclose(lengthFile);

    printf("Pass 2 completed.\n");
    return 0;
}

inter
1000 ** START 1000
1000 ** LDA ALPHA
1003 ** STA BETA
1006 ALPHA RESW 1
1009 BETA RESW 1
1012 ** END **

optab
LDA 00
STA 0C
LDCH 50
STCH 54
 symtab
 ALPHA 1006
BETA 1009

length =16
asml
1000 ** START 1000
1000 ** LDA ALPHA 0000
1003 ** STA BETA 0C1009
1006 ALPHA RESW 1
1009 BETA RESW 1
1012 ** END **

objcode
H^**^001000^000010
T^001000^000000^0C1009^
E^001000
