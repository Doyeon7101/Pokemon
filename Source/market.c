#include "pokemon.h"
char	print_menu(int money){
	OS == UNIX ? system("clear") : system("cls"); print_gard(3);
	printf(YELLOW"%s"DEFAULT, BAR);
	printf(BLUE"%s"DEFAULT, "상점에 오신 것을 환영합니다.\n0. 나가기\n1. 몬스터볼	1000\n2. 포션	 	2000\n");
	printf(BLUE"					   보유 금액: %d\n"DEFAULT, money);
	printf(YELLOW"%s"DEFAULT, BAR);
	write(1, "> ", 2);
	return (fflush_and_getc());
}

void market(user_t *user){
	char	c;
	int		cnt; 

	while(1){
		cnt = 0;
		c = print_menu(user->money);
		if (c == '1'){
			while (cnt < 1 || cnt > 9){
				set_console(S_MARKET, 1, "몇개를 구매하시겠습니까?\n 1~9 사이의 값을 입력하세요\n");
				cnt = fflush_and_getc() - '0';
			}
			if (user->money < 1000 * cnt)
				set_console(S_MARKET, 1, "돈이 부족하다.\n"), fflush_and_getc();
			else{
				user->money -= 1000 * cnt;
				user->item[MO] += cnt;
				set_console(S_MARKET, 1, "몬스터볼을 구매하였다!\n"), fflush_and_getc();
			}
		}
		else if (c == '2'){
			while (cnt < 1 || cnt > 9){
				set_console(S_MARKET, 1, "몇개를 구매하시겠습니까?\n 1~9 사이의 값을 입력하세요\n");
				cnt = fflush_and_getc() - '0';
			}
			if (user->money < 2000 * cnt)
				set_console(S_MARKET, 1, "돈이 부족하다.\n"), fflush_and_getc();
			else{
				user->money -= 2000 * cnt;
				user->item[ME] += cnt;
				set_console(S_MARKET, 1, "포션을 구매하였다!\n"), fflush_and_getc();
			}
		}
		else if (c == '0') break;
	}
}
