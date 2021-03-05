#include "Arithmetic.h"

bool arithmetic(FILE* fout, char c, char str[], int* cnt){

    if(strncmp(str, "add", 3) == 0){
    	fprintf(fout, "@SP\nM=M-1\nA=M\nD=M\nA=A-1\nM=M+D\n");
    }
    else if(strncmp(str, "sub", 3) == 0){
    	fprintf(fout, "@SP\nM=M-1\nA=M\nD=M\nA=A-1\nM=M-D\n");
    }
    else if(strncmp(str, "not", 3) == 0){
    	fprintf(fout, "@SP\nA=M-1\nM=!M\n");
    }
    else if(strncmp(str, "or", 2) == 0){
    	fprintf(fout, "@SP\nM=M-1\nA=M\nD=M\nA=A-1\nM=M|D\n");
    }
    else if(strncmp(str, "and", 3) == 0){
    	fprintf(fout, "@SP\nM=M-1\nA=M\nD=M\nA=A-1\nM=M&D\n");
    }
    else if(strncmp(str, "neg", 3) == 0){
    	fprintf(fout, "@SP\nA=M-1\nM=-M\n");
    }
    else if(strncmp(str, "eq", 2) == 0){
    	fprintf(fout, "@SP\nM=M-1\nA=M\nD=M\nA=A-1\nM=M-D\nD=M\n@EQ%d\nD;JEQ\n@SP\nA=M-1\nM=0\n@END_EQ%d\n0;JMP\n(EQ%d)\n@SP\nA=M-1\nM=-1\n(END_EQ%d)\n", *cnt, *cnt, *cnt, *cnt);
    }
    else if(strncmp(str, "gt", 2) == 0){
    	fprintf(fout, "@SP\nM=M-1\nA=M\nD=M\nA=A-1\nM=M-D\nD=M\n@GT%d\nD;JGT\n@SP\nA=M-1\nM=0\n@END_GT%d\n0;JMP\n(GT%d)\n@SP\nA=M-1\nM=-1\n(END_GT%d)\n", *cnt, *cnt, *cnt, *cnt);
    }
    else if(strncmp(str, "lt", 2) == 0){
    	fprintf(fout, "@SP\nM=M-1\nA=M\nD=M\nA=A-1\nM=M-D\nD=M\n@LT%d\nD;JLT\n@SP\nA=M-1\nM=0\n@END_LT%d\n0;JMP\n(LT%d)\n@SP\nA=M-1\nM=-1\n(END_LT%d)\n",  *cnt, *cnt, *cnt, *cnt);
	}
    else{
        return false;
    }

    *cnt += 1;
    return true;
}

