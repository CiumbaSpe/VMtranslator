#include "ProgramFlow.h"
#include "MemoryAccess.h" // in order to use the function findValue

bool programFlow(FILE* fout, FILE* fin, char c, char *str){
    if(strncmp(str, "label", 5) == 0){
		findValue(fin, c, str); // function findValue situata in MemoryAccess.h
        fprintf(fout, "(%s)\n", str);
	}
    else if(strncmp(str, "goto", 4) == 0){
		findValue(fin, c, str);
        fprintf(fout, "@%s\n0;JMP\n", str);
    }
    else if(strncmp(str, "if-goto", 7) == 0){
        findValue(fin, c, str);
        fprintf(fout, "@SP\nAM=M-1\nD=M\n@%s\nD;JNE\n", str);
    }
    else{
        return false;
    }
    return true;
}
