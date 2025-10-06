#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char label[20], opcode[20], operand[20];
    char code[20], mnemonic[3];
    int locctr = 0, start = 0, length;

    // Open all required files
    FILE *input = fopen("input3.txt", "r");       // Source program
    FILE *optab = fopen("optab3.txt", "r");       // Opcode table
    FILE *symtab = fopen("symtab3.txt", "w");     // Symbol table
    FILE *intermediate = fopen("intermediate3.txt", "w"); // Intermediate file
    FILE *lengthFile = fopen("length3.txt", "w"); // Program length

    if (!input || !optab || !symtab || !intermediate || !lengthFile) {
        printf("Error opening files.\n");
        return 1;
    }

    // Read first line of source program
    fscanf(input, "%s %s %s", label, opcode, operand);

    // Handle START directive
    if (strcmp(opcode, "START") == 0) {
        start = atoi(operand);
        locctr = start;
        fprintf(intermediate, "\t%s\t%s\t%s\n", label, opcode, operand);
        fscanf(input, "%s %s %s", label, opcode, operand);
    }

    // Process instructions and directives until END
    while (strcmp(opcode, "END") != 0) {
        fprintf(intermediate, "%d\t%s\t%s\t%s\n", locctr, label, opcode, operand);

        // Add label to symbol table if it exists
        if (strcmp(label, "**") != 0) {
            fprintf(symtab, "%s\t%d\n", label, locctr);
        }

        // Check if opcode exists in OPTAB
        rewind(optab); // Start reading OPTAB from beginning
        int found = 0;
        while (fscanf(optab, "%s %s", code, mnemonic) != EOF) {
            if (strcmp(opcode, code) == 0) {
                locctr += 3; // SIC machine instruction = 3 bytes
                found = 1;
                break;
            }
        }

        // Handle assembler directives if opcode not in OPTAB
        if (!found) {
            if (strcmp(opcode, "WORD") == 0)
                locctr += 3;
            else if (strcmp(opcode, "RESW") == 0)
                locctr += 3 * atoi(operand);
            else if (strcmp(opcode, "RESB") == 0)
                locctr += atoi(operand);
            else if (strcmp(opcode, "BYTE") == 0)
                locctr += 1; // 1 byte
        }

        // Read next line from input
        fscanf(input, "%s %s %s", label, opcode, operand);
    }

    // Write END line in intermediate file
    fprintf(intermediate, "%d\t%s\t%s\t%s\n", locctr, label, opcode, operand);

    // Calculate program length
    length = locctr - start;
    fprintf(lengthFile, "%d", length);
    printf("Program length: %d\n", length);

    // Close all files
    fclose(input);
    fclose(optab);
    fclose(symtab);
    fclose(intermediate);
    fclose(lengthFile);

    return 0;
}
                 
                 
                 
                 
                 
                 
                 
                 ** START 1000
** LDA ALPHA
** STA BETA
** LDCH CHAR1
** STCH CHAR2
** END **
ALPHA RESW 1
BETA RESW 1
CHAR1 RESB 1
CHAR2 RESB 1





LDA 00
STA 23
LDCH 15
STCH 18









ALPHA   1012
BETA    1015
CHAR1   1018
CHAR2   1019








        START   1000
1000    **      LDA     ALPHA
1003    **      STA     BETA
1006    **      LDCH    CHAR1
1009    **      STCH    CHAR2
1012    ALPHA   RESW    1
1015    BETA    RESW    1
1018    CHAR1   RESB    1
1019    CHAR2   RESB    1
1020    **      END     **







20

                 
                 
                 
                 
                 
                 
                 
                 
                 
                 
                 
                 
                 
                 
                 
                 
                 
                 
                 
                 
                 
