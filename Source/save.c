#include "pokemon.h"

void    save_user_data(user_t *user){
    FILE        *fp;
    p_list_t    *list = user->list;

    list->cur = list->head->next;
    fp = fopen("./GameData/UserData", "w");
    fprintf(fp, "P(NAME|TYPE|ATK|HP|MAXHP)\n");
    while (list->cur){
        fprintf(fp, "%s | %s | %d | %d | %d\n", list->cur->name, list->cur->type, list->cur->min_attack_power, list->cur->min_HP, list->cur->max_HP);
        list->cur = list->cur->next;
    }
    fprintf(fp, "```\n");
    fprintf(fp, "I\n");
    fprintf(fp, "MO|%d\n", user->item[MO]);
    fprintf(fp, "ME|%d\n", user->item[ME]);
    fprintf(fp, "```\n");
    fprintf(fp, "M\n");
    fprintf(fp, "%d\n", user->money);
}