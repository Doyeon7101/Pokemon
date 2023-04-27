#include "pokemon.h"

void    print_node(p_t *node){
    printf("name: %s, type: %s, min_attack_power: %d, min_HP: %d\n", node->name, node->type, node->min_attack_power, node->min_HP);
    return;
}

void    ListInit(p_list_t  *plist){
    plist->head = (p_t *)malloc(sizeof(p_t));
    plist->head->next = NULL;
    plist->numOfData = 0;
}

void    FInsert(p_list_t *plist, char *line){
    p_t* newNode = (p_t*)malloc(sizeof(p_t));

    newNode->name = strndup(line, strchr(line, '|') - line - 1);
    line = strchr(line, '|') + 2;
    newNode->type = strndup(line, strchr(line, '|') - line - 1);
    line = strchr(line, '|') + 2;
    newNode->min_attack_power = atoi(line);
    line = strchr(line, '|') + 2;
    newNode->min_HP = atoi(line);
    line = strchr(line, '|') + 2;
    newNode->max_HP = atoi(line);
    newNode->next = plist->head->next;  //  항상 head는 dummyNode를 가리키고 있다.
    plist->head->next = newNode;
    (plist->numOfData)++;
}

void    delete_node(p_list_t *plist, p_t *node){
    p_t *tmp = plist->head;

    if(plist->numOfData == 1){
        free(node->name);
        free(node->type);
        free(node);
        plist->head->next = NULL;
        (plist->numOfData)--;
        return;
    }
    while (tmp->next != node)
        tmp = tmp->next;
    tmp->next = node->next;
    free(node->name);
    free(node->type);
    free(node);
    (plist->numOfData)--;
}

/**
 * 기본(최초) 포켓몬을 제외한 모든 포켓몬을 삭제한다.
*/
void    pokemon_free_all(p_list_t *plist){
    p_t *tmp = plist->head->next;
    p_t *tmp2;

    while (plist->numOfData != 1){
        tmp2 = tmp->next;
        delete_node(plist, tmp);
        tmp = tmp2;
    }
}