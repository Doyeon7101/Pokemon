#include "pokemon.h"

/**
 * @param status 0: default, 1:travel, 2: attack, 3: market
*/
void	set_console(int status, int newpage, char *str){
	print_gard(status);
	if (!str)
		str = "================== press enter key to start ==================\n\
			made by dpark\n";
	if (newpage) printf(YELLOW"%s"DEFAULT, BAR);
	printf(BLUE"%s"DEFAULT, str);
	printf(YELLOW"%s"DEFAULT, BAR);
	write(1, "> ", 2);
}

int main(void){
	p_list_t	list;
	user_t		user;

	user.list = (p_list_t *)malloc(sizeof(p_list_t));
	ListInit(user.list);
	if (!parse_and_validation(&list))
		return (terminate("유효성 검사 실패, 초기 데이터를 확인하세요."));
	set_console(0, 1, 0), getc(stdin);
	start(&list, &user);
	return 0;
}
