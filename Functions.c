#include "Functions.h"

void findFunctionValues(FILE* fin, char c, char str[], bool wait){
	strcpy(str, "");
	if(wait) { fscanf(fin, "%c", &c); }
	while(c != '\n' && c != '/' && (c != ' ' || wait)){
		fscanf(fin, "%c", &c);
		if(c != ' ' && c != '\n' && c != '/')
			strncat(str, &c, 1);
		wait = false;
	}
}

bool functions(FILE* fout, FILE* fin, char c, char str[], int* cnt){
    
    if(strncmp(str, "function", 8) == 0){
		char fName[30];
		char fLcl[30];
		findFunctionValues(fin, c, str, true);
		strcpy(fName, str);
		findFunctionValues(fin, c, str, false);
		strcpy(fLcl, str);
		
		fprintf(fout, "(%s)\n", fName);
		fprintf(fout, "@R15\nM=0\n"); // counter for popping local
		fprintf(fout, "@%s\nD=A\n@R14\nM=D\n", fLcl); // using R14 as a counter
		fprintf(fout, "(PUSH_LCL_LOOP_%d)\n@R14\nD=M\n", *cnt); // condition in D
		fprintf(fout, "@END_PUSH_LCL_LOOP_%d\nD;JEQ\n", *cnt);  // condition
		fprintf(fout, "@0\nD=A\n@SP\nM=M+1\nA=M-1\nM=D\n"); // initialize all lcl to 0
		fprintf(fout, "@R15\nA=M\nD=A\n@LCL\nD=D+M\n@R13\nM=D\n@SP\nAM=M-1\nD=M\n@R13\nA=M\nM=D\n"); // pop local RAM[R15]
		fprintf(fout, "@R15\nM=M+1\n"); // incrementing local counter
		fprintf(fout, "@R14\nM=M-1\n"); // decrementing the counter
		fprintf(fout, "@PUSH_LCL_LOOP_%d\n0;JMP\n(END_PUSH_LCL_LOOP_%d)\n", *cnt, *cnt);
		*cnt += 1;
	}
	else if(strncmp(str, "call", 4) == 0){
		char fName[30];
		char fArg[30];
		findFunctionValues(fin, c, str, true);
		strcpy(fName, str);
		findFunctionValues(fin, c, str, false);
		strcpy(fArg, str);

		fprintf(fout, "@cont_address_%d\nD=A\n", *cnt);
		fprintf(fout, "@SP\nM=M+1\nA=M-1\nM=D\n");
		fprintf(fout, "@LCL\nD=M\n");
		fprintf(fout, "@SP\nM=M+1\nA=M-1\nM=D\n");
		fprintf(fout, "@ARG\nD=M\n");
		fprintf(fout, "@SP\nM=M+1\nA=M-1\nM=D\n");
		fprintf(fout, "@THIS\nD=M\n");
		fprintf(fout, "@SP\nM=M+1\nA=M-1\nM=D\n");
		fprintf(fout, "@THAT\nD=M\n");
		fprintf(fout, "@SP\nM=M+1\nA=M-1\nM=D\n");
		fprintf(fout, "@SP\nD=M\n@5\nD=D-A\n@%s\n", fArg);
		fprintf(fout, "D=D-A\n@ARG\nM=D\n@SP\nD=M\n@LCL\nM=D\n@%s\n0;JMP\n", fName);
		fprintf(fout, "(cont_address_%d)\n", *cnt);
		*cnt += 1;
	}
	else if(strncmp(str, "return", 6) == 0){
		fprintf(fout, "@LCL\nD=M\n@R13\nM=D\n@5\nD=D-A\nA=D\nD=M\n@R14\nM=D\n");
		fprintf(fout, "@SP\nAM=M-1\nD=M\nM=0\n");
		fprintf(fout, "@ARG\nA=M\nM=D\nD=A+1\n@SP\nM=D\n@R13\nA=M-1\nD=M\n@THAT\nM=D\n@2\n");
		fprintf(fout, "D=A\n@R13\nD=M-D\nA=D\nD=M\n");
		fprintf(fout, "@THIS\nM=D\n@3\n");
		fprintf(fout, "D=A\n@R13\nD=M-D\nA=D\nD=M\n");
		fprintf(fout, "@ARG\nM=D\n@4\n");
		fprintf(fout, "D=A\n@R13\nD=M-D\nA=D\nD=M\n");
		fprintf(fout, "@LCL\nM=D\n@R14\nA=M\n0;JMP\n");
	}
	else{
		return false;
	}

    return true;
}


