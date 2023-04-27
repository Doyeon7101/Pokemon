#include "pokemon.h"

void lounge(p_list_t *list, user_t *user){
	char	c;

	while (1){
		set_console(0, 1, "여행을 떠나시겠습니까?\n1. 네    2. 아니요    3. 상점 가기\n");
		c = fflush_and_getc();
		if (c == '1')
			travel(user, list);
		else if (c == '2'){
			while (1){
				set_console(0, 1, "저장하시겠습니까? (y/n) \n0. 돌아가기\n");
				c = fflush_and_getc();
				if (c == 'y') save_user_data(user), set_console(0, 1, "다음에 또 만나요!\n"), exit(0);
				else if (c == 'n') set_console(0, 1, "다음에 또 만나요!\n"), exit(0);
				else if (c == '0') break;
				else set_console(0, 1, "다시 입력해주세요.\n"), fflush_and_getc();
			}
		}
		else if (c == '3')
			market(user);
	}
}

int	start(p_list_t *list, user_t *user){
    FILE    *fp;
    char	c;

	fp = fopen("./GameData/UserData", "r");
	if (fp){ //데이터가 있을 경우
		while (1){
			set_console(0, 1, "새로하기: 1, 이어하기: 2\n");
			c = fflush_and_getc();
			if (c == '1') {init_user_data(user); break;}
			else if (c == '2') {parse_user_data(fp, user); break;}
			else set_console(0, 1, "잘못된 입력입니다.\n"), fflush_and_getc();
		}
	}
	else init_user_data(user); //데이터가 없을 경우
	if (user->list->numOfData == 0)
		set_default_pokemon(user);
	fclose(fp);
	lounge(list, user);
    return 1;
}
