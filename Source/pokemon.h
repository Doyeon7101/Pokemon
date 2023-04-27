#ifndef _POKEMON_H
#define _POKEMON_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <limits.h>
#include <time.h>

/*os*/
#define UNIX 0
#define WINDOWS 1
#define OS UNIX

/*print color*/
#define DEFAULT "\033[0m"
#define RED     "\033[0;31m"
#define GREEN   "\033[0;32m"
#define YELLOW  "\033[0;33m"
#define BLUE    "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define CYAN    "\033[0;36m"

#define BAR "==============================================================\n"

/*item*/
#define MO 0
#define ME 1

typedef struct p_s{
    char        *name;
    char        *type;
    int         min_attack_power;
    int         min_HP;
    int         max_HP;
    struct p_s  *next;
} p_t;

typedef struct pokemon_list_s{
    p_t *head;
    p_t *cur;
    p_t *before;
    int numOfData;
} p_list_t;

typedef struct user_s{
    p_list_t    *list;
    p_t         *pokemon;
    int         item[2];
    int         money;
} user_t;

typedef enum status_s{
    S_DEFAULT,
    S_TRAVEL,
    S_BATTLE,
    S_MARKET,
    S_BAG
}status_t;

typedef enum type_e { NORMAL, FIRE, WATER, GRASS } type_t;

/*pokemon.c*/
void	set_console(int status, int newpage, char *str);

/*parse.c*/
bool    parse_and_validation(p_list_t *list);
void	init_user_data(user_t *user);
void	parse_user_data(FILE *fp, user_t *user);
void	set_default_pokemon(user_t *user);

/*linked_list.c*/
void    FInsert(p_list_t *plist, char *line);
void    ListInit(p_list_t  *plist);
void    print_node(p_t *node);
void    delete_node(p_list_t *plist, p_t *node);
void    pokemon_free_all(p_list_t *plist);

/*execution.c*/
int     start(p_list_t *list, user_t *user);

/*travel.c*/
void    travel(user_t *user, p_list_t *list);

/*market.c*/
void    market(user_t *user);

/*save.c*/
void    save_user_data(user_t *user);

/*utils.c*/
void    print_gard2(char *path);
void	print_gard(int status);
char	fflush_and_getc();
int     terminate(char *str);


#endif
