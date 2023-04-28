#include "pokemon.h"

void duplication(FILE *fp){
	FILE	*fp2 = fopen("./GameData/UserData", "w");
	char	line[100];

	if (!(fp = fopen("./GameData/DefaultUserData", "r")))
		set_console(0, 1, "기본 데이터를 찾을 수 없습니다. 프로그램을 재설치 하세요.\n");
	while (fgets(line, 100, fp) != NULL){
		fputs(line, fp2);
	}
	fclose(fp2);
}

void	set_default_pokemon(user_t *user){
	char	c;

	while (1){
		set_console(0, 1, "기본 포켓몬을 선택하세요.\n1. 파이리	2. 꼬부기	3. 이상해씨\n");
		c = fflush_and_getc();
		if (c == '1') {FInsert(user->list, "파이리 | 불 | 1000 | 3000 | 3000"); break;}
		else if (c == '2') {FInsert(user->list, "꼬부기 | 물 | 1000 | 3000 | 3000"); break;}
		else if (c == '3') {FInsert(user->list, "이상해씨 | 풀 | 1000 | 3000 | 3000"); break;}
	}
}

/**
 * @brief Initializes user data and parses it according to the user structure.
 * 		  If the data is basic, the default Pokemon is set. 
 * @param user User data structure
 * @return void
 */
void	init_user_data(user_t *user){
	FILE	*fp;

	user->item[MO] = 0;
	user->item[ME] = 0;
	user->money = 10000;
	if (!(fp = fopen("./GameData/DefaultUserData", "r"))){
		set_console(0, 1, "기본 데이터를 찾을 수 없습니다. 프로그램을 재설치 하세요.\n");
		exit(1);
	}
	duplication(fp);
}

/**
 * @brief Parses user data and saves it in the user structure.
 * @param fp File pointer about user data
 * @param user User data structure
 * @return void
 */
void	parse_user_data(FILE *fp, user_t *user){
	char line[100] = {};

	ListInit(user->list);
	while (fgets(line, 100, fp) != NULL){
		if (line[0] == 'I'){
			fgets(line, 100, fp);
			if (line[1] == 'O')
				user->item[MO] = atoi(line + 3);
			fgets(line, 100, fp);
			if (line[1] == 'E')
				user->item[ME] = atoi(line + 3);
		}
		else if (line[0] == 'M'){
			fgets(line, 100, fp);
			user->money = atoi(line);
		}
		else if (line[0] == 'P'){
			while (fgets(line, 100, fp) && line[0] != '`')
				FInsert(user->list, line);
		}
	}
}

bool parse_and_validation(p_list_t *list){
	FILE	*fp;
	char	line[100];

	if (!(fp = fopen("./GameData/pokemon_list", "r"))){
		return false;
	}
	ListInit(list);
	while (fgets(line, 100, fp) != NULL)
		FInsert(list, line);
	fclose(fp);
	return true;
}
