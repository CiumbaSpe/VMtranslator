#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Arithmetic.h"
#include "MemoryAccess.h"
#include "ProgramFlow.h"
#include "Functions.h"

void scanTesto(FILE *fin, FILE *fout){

	fprintf(fout, "@256\nD=A\n@SP\nM=D\n\n");
	
	int cont_f_decl = 0; 	  // serve per avere nomi diversi nei label per le f declaration
	int cont_gt_lt_eq = 0;    // serve per avere nomi diversi nei label per verificare se gl lt eq
	char c;				 		// raccoglie lettera per lettera con fscanf
	char str[40] = "";			// c viene concatenato in str per fare i confronti

	// ciclo dove avviene lo scan
	while(!feof(fin)){

		fscanf(fin, "%c", &c);

		if(strncmp(&c, "/", 1) == 0){			// checking for comment
			while(strncmp(&c, "\n", 1) != 0)
			fscanf(fin, "%c", &c);
			strcpy(str, "");
		}
		else{
			if(strncmp(&c, "\n", 1) != 0){
				
				strncat(str, &c, 1);
				
				if(arithmetic(fout, c, str, &cont_gt_lt_eq) || memoryAccess(fout, fin, c, str) || programFlow(fout, fin, c, str) || functions(fout, fin, c, str, &cont_f_decl)){
					strcpy(str, "");
					fprintf(fout, "\n");
				}
				
			}
			else { strcpy(str, ""); }
		}
	}

}


int main(int argc, char* argv[]){

	if(argc != 3){ 
		printf("ERRORE: parametri inseriti scorretti\n");
		printf("inserire nome.vm e nome.asm\n");
	}
    else{

		FILE* fin;
		fin = fopen(argv[1], "r");
	
		FILE* fout;
		fout = fopen(argv[2], "w");

		scanTesto(fin, fout);

		fclose(fin);
		fclose(fout);
	}

	return 0;
}

