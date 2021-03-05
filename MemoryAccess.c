#include "MemoryAccess.h"

void findValue(FILE* fin, char c, char str[]){
	strcpy(str, "");
	while(c != '\n' && c != '/'){
		fscanf(fin, "%c", &c);
		if(c != ' ' && c != '\n' && c != '/')
			strncat(str, &c, 1);
	}
}


bool memoryAccess(FILE* fout, FILE* fin, char c, char str[]){
	if(strncmp(str, "push constant", 13) == 0){
		findValue(fin, c, str);
		fprintf(fout, "@%s\nD=A\n@SP\nA=M\nM=D\n", str);
		fprintf(fout, "@SP\nM=M+1\n");
	}
	else if(strncmp(str, "push static", 11) == 0){
		findValue(fin, c, str);
		fprintf(fout, "@STATIC_%s\nD=M\n@SP\nM=M+1\nA=M-1\nM=D\n", str);
	}
	else if(strncmp(str, "pop static", 10) == 0){
		findValue(fin, c, str);
		fprintf(fout, "@SP\nAM=M-1\nD=M\n@STATIC_%s\nM=D\n", str);
	}
	else if(strncmp(str, "push local", 10) == 0){
		findValue(fin, c, str);
		fprintf(fout, "@%s\nD=A\n@LCL\nA=M+D\nD=M\n@SP\nM=M+1\nA=M-1\nM=D\n", str);
	}
	else if(strncmp(str, "pop local", 9) == 0){
		findValue(fin, c, str);
		fprintf(fout, "@%s\nD=A\n@LCL\nD=D+M\n@13\nM=D\n@SP\nAM=M-1\nD=M\n@13\nA=M\nM=D\n", str);
	}
	else if(strncmp(str, "push argument", 13) == 0){
		findValue(fin, c, str);
		fprintf(fout, "@%s\nD=A\n@ARG\nA=M+D\nD=M\n@SP\nM=M+1\nA=M-1\nM=D\n", str);
	}
	else if(strncmp(str, "pop argument", 12) == 0){
		findValue(fin, c, str);
		fprintf(fout, "@%s\nD=A\n@ARG\nD=D+M\n@13\nM=D\n@SP\nAM=M-1\nD=M\n@13\nA=M\nM=D\n", str);
	}
    else{
        return false;
    }
   
	

    return true;
}