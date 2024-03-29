#include "pokemon.h"

int	terminate(char *str){
	if (str)
		puts(str);
	return 1;
}

char	fflush_and_getc(){
	char c;

	fflush(stdin);
	c = getc(stdin);
	return c;
}

/**
 * path status 0: default, 1:travel, 2: battle, 3: market, 4: bag
*/
void	print_gard(int status){
	FILE *fp;
	int c;
	char path[][30] = {"./GameData/ascii/gard", "./GameData/ascii/travel",\
		"./GameData/ascii/battle", "./GameData/ascii/market", "./GameData/ascii/bag"};

	OS == UNIX ? system("clear") : system("cls");
	fp = fopen(path[status], "r");
	while ((c = fgetc(fp)) != EOF) {
		printf(YELLOW"%c"DEFAULT, c);
  }
  fclose(fp);
}
