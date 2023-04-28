#include "pokemon.h"
char	print_menu(int money){
	print_gard(3);
	printf(YELLOW"%s"DEFAULT, BAR);
	printf(BLUE"%s"DEFAULT, "상점에 오신 것을 환영합니다.\n0. 나가기\n1. 몬스터볼	1000\n2. 포션	 	2000\n");
	printf(BLUE"					   보유 금액: %d\n"DEFAULT, money);
	printf(YELLOW"%s"DEFAULT, BAR);
	write(1, "> ", 2);
	return (fflush_and_getc());
}

void	market(user_t *user){
	char	c;
	int		cnt;
	int		item[2] = {1000, 2000};

	while(1){
		cnt = 0;
		c = print_menu(user->money);
		if (c == '1' || c == '2'){
			while (cnt < 1 || cnt > 9){
				set_console(S_MARKET, 1, "몇개를 구매하시겠습니까?\n1~9 사이의 값을 입력하세요\n");
				cnt = fflush_and_getc() - '0';
			}
			if (user->money < item[c - '1'] * cnt)
				set_console(S_MARKET, 1, "돈이 부족하다.\n"), fflush_and_getc();
			else{
				user->money -= item[c - '1'] * cnt;
				user->item[c - '1'] += cnt;
				set_console(S_MARKET, 1, c == '1' ? "몬스터볼을 구매하였다!\n" : "포션을 구매하였다!\n"), fflush_and_getc();
			}
		}
		else if (c == '0') break;
	}
}