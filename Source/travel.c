#include "pokemon.h"

int get_type(char *type){
    if (strcmp(type, "불") == 0)
        return FIRE;
    else if (strcmp(type, "물") == 0)
        return WATER;
    else if (strcmp(type, "풀") == 0)
        return GRASS;
    return 0;
}

/**
 * @brief compare two type
 * @return 0 if same or normal type, 1 if a is strong, -1 if a is weak
 * FIRE < WATER < GRASS < FIRE 
*/
double  get_weight(int a, int b){
    if ((a == GRASS && b == FIRE) || (a == FIRE && b == GRASS))
        return b - a > 0 ? 1.5 : 0.5;
    return a - b > 0 ? 1.5 : 0.5;
}

p_t *pick_player_pokemon(p_list_t *list){
    char    c;
    p_t     *tmp;

    while (1){
        tmp = list->head->next;
        print_gard(2);
        printf(BLUE"포켓몬을 선택하세요\n"DEFAULT);
        for (int i = 0; i < list->numOfData; i++){
            printf(CYAN"%d. %s   %s   %d/%d\n"DEFAULT, i+1, tmp->name, tmp->type, tmp->min_HP, tmp->max_HP);
            tmp = tmp->next;
        }
        printf(YELLOW"%s\n> "DEFAULT, BAR);
        c = fflush_and_getc();
        if (c >= '1' && c <= list->numOfData + '0')
            break;
    }
    tmp = list->head->next;
    for (int i = 0; i < list->numOfData + 1; i++){
        if (c == i + '1') break;
        tmp = tmp->next;
    }
    return tmp;
}

void    print_status(p_t *enemy, p_t *player){
    print_gard(2);
    printf(RED"[%s]: %d/%d\n"DEFAULT, enemy->name, enemy->min_HP, enemy->max_HP);
    printf(CYAN"[%s]: %d/%d\n"DEFAULT, player->name, player->min_HP, player->max_HP);
    printf(YELLOW"%s\n> "DEFAULT, BAR);
    fflush_and_getc();
}

/**
 * @brief get random pokemon from list
 * @return random pokemon
 * @bug pokemon is not freed
*/
p_t     *get_rand_pokemon(p_list_t *list, int index){
    p_t     *pokemon = (p_t *)malloc(sizeof(p_t));
    p_t     *tmp = list->head;

    for (int i = 0; i < index; i++)
        tmp = tmp->next;
    pokemon->name = strdup(tmp->name);
    pokemon->type = strdup(tmp->type);
    pokemon->min_attack_power = tmp->min_attack_power;
    pokemon->min_HP = tmp->min_HP;
    pokemon->max_HP = tmp->max_HP;
    pokemon->next = NULL;
    return pokemon;
}

double get_success_rate(int enemy_hp, int *hp_range, double *run_prob, int n){
    double success_rate = 0;

    for (int i = 0; i < n; i++) 
        if (enemy_hp <= hp_range[i]) success_rate = run_prob[i];
    return success_rate;
}

int monsterball(user_t *user, p_t *enemy, int *status){
    p_list_t *list = user->list;
    int hp_range[] = { 10, 30, 50 };
    double catch_prob[] = { 0.9, 0.6, 0.3 };

    if (enemy->min_HP >= enemy->max_HP * 0.5){
        set_console(4, 0, "몬스터의 체력이 너무 강력하다. 나중에 다시 도전하자.\n"); fflush_and_getc();
        return 0;
    }
    set_console(4, 0, "가랏 몬스터볼!\n"); fflush_and_getc();
    user->item[MO]--;
    if (get_success_rate(enemy->min_HP, hp_range, catch_prob, 3) < ((double)rand() / RAND_MAX)){
        set_console(4, 0, "잡았다!\n"); fflush_and_getc();
        *status = 3;
        enemy->next = list->head->next;
        list->head->next = enemy;
        list->numOfData++;
        return 1;
    }
    set_console(4, 0, "앗 몬스터볼이 깨졌다...\n"); fflush_and_getc();
    return 0;
}

char    print_bag(user_t *user){
    print_gard(4);
    puts(BLUE"어떤 아이템을 사용하시겠습니까?"DEFAULT);
    printf(BLUE"0. 나가기\n");
    printf(BLUE"1. 몬스터볼:       x%d\n"DEFAULT, user->item[MO]);
    printf(BLUE"2. 회복 물약:      x%d\n"DEFAULT, user->item[ME]);
    printf(YELLOW"%s\n> "DEFAULT, BAR);
    return fflush_and_getc();
}

void    end_game_and_ask_for_travel(user_t *user, int *status){
    char    c;

    pokemon_free_all(user->list);
    *status = 3;
    while(1){
        set_console(4, 0, "넌 이제 내꺼야! 여행을 떠나볼까?(Y/N)\n"); c = fflush_and_getc();
        if (c == 'N'){
            pokemon_free_all(user->list);
            save_user_data(user);
            set_console(4, 0, "저장완료!\n"); fflush_and_getc();
            set_console(4, 0, "다음에 또 만나자!\n"); fflush_and_getc();
            exit(0);
        }
        else if (c == 'Y'){ pokemon_free_all(user->list); return; }
    }
}

int bag(user_t *user, p_t *player, p_t *enemy, int *status){
    char    c;

    if (user->item[MO] == 0 && user->item[ME] == 0){
        set_console(4, 0, "가방이 비어있다.\n"); fflush_and_getc();
        return -1;
    }
    while(1){
        c = print_bag(user);
        if (c == '0') return -1;
        else if ((c == '1' || c == '2') && user->item[c-'1'] == 0){
            set_console(4, 0, "해당 아이템이 존재하지 않습니다.\n"); fflush_and_getc();
        }
        else if (c == '1'){
            monsterball(user, enemy, status);
            if (user->list->numOfData == 6){
                end_game_and_ask_for_travel(user, status);
            }
            return 1;
        }
        else if (c == '2'){
            user->item[ME]--;
            player->min_HP += player->max_HP * (((double)rand() / RAND_MAX) * 0.2 + 0.1);
            set_console(4, 0, "회복 물약을 사용했다!\n"); fflush_and_getc();
            return 1;
        }
        else set_console(4, 1, "올바른 값을 다시 입력해주세요.\n");
    }
}


void    run_away(p_t *enemy, int *status) {
    double  run_prob[] = { 0.9, 0.7, 0.4, 0.1 };
    int     hp_range[] = { 25, 50, 100, 9999 };
    double  success_rate = get_success_rate(enemy->min_HP, hp_range, run_prob, 4);
    double  rand_num = (double)rand() / RAND_MAX;

    srand(time(NULL));
    if (rand_num < success_rate) {
        set_console(S_BATTLE, 0, "도망에 성공했다!\n");
        *status = 2;
    }
    else set_console(S_BATTLE, 0, "도망에 실패했다!\n");
    fflush_and_getc();
}

/**
 * 상성: 불 < 물 < 풀 < 불
 * 포켓몬을 선택하고, 적과의 상성을 비교하여 공격력를 계산한다.
 * @param damage = 공격력 * 상성에따른 가중치
*/
void    attack(int item, p_t *player, p_t *enemy){
    double  damage;

    (void)item;
    damage = get_weight(get_type(player->type), get_type(enemy->type));
    damage >= 1 ? set_console(2, 0, "효과는 굉장했다!\n") : set_console(2, 0, "효과는 별로인 듯 하다.\n");
    fflush_and_getc();
    damage *= player->min_attack_power;
    enemy->min_HP -= damage;
    print_status(enemy, player);
}

void    player_turn(user_t *user, p_t *player, p_t *enemy, int *status){
    char    c;

    while (1){
        set_console(2, 0, CYAN"1. 공격  2. 도망치기  3. 가방열기\n"DEFAULT);
        c = fflush_and_getc();

        if (c == '1'){
            set_console(2, 0, "플레이어의 공격!\n");
            attack(0, player, enemy); break; }
        else if (c == '2'){ run_away(enemy, status); break; }
        else if (c == '3'){
            if (bag(user, player, enemy, status) == 1) break;}
        else set_console(2, 1, "올바른 값을 다시 입력해주세요.\n");
    }
    if (enemy->min_HP <= 0 && !(*status)){
        set_console(2, 0, enemy->min_HP == 0 ? "앗... 포켓몬이 도망가버렸다...\n" : "포켓몬을 쓰러트렸다!\n");
        fflush_and_getc();
        *status = 2;
    }
}

/**
 * 적의 턴
 * 공격, 0보다 작으면 포켓몬 사망 후 다른 포켓몬 pick
 * 만약 모든 포켓몬이 사망하면(2), 로비로 진입
 * 플레이어가 살아있으면 status는 0
*/
void    enemy_turn(user_t *user, p_t *player, p_t *enemy, int *status){
    set_console(S_BATTLE, 0, "적의 공격!\n"); fflush_and_getc();
    attack(0, enemy, player);
    if (player->min_HP <= 0){
        set_console(S_BATTLE, 0, "패배했다...\n"); fflush_and_getc();
        if (user->list->numOfData == 1){
            set_console(S_BATTLE, 0, "눈 앞이 캄캄해졌다...\n"); fflush_and_getc();
            *status = 3;
            set_console(S_BATTLE, 0, RED"기본 포켓몬이 체력을 회복하였습니다.\n"DEFAULT); fflush_and_getc();
            player->min_HP = player->max_HP;
        }
        else{
            delete_node(user->list, player);
            player = pick_player_pokemon(user->list);
        }
    }
}

void    free_node(int status, p_t *enemy, p_t *player, p_list_t *list){
    if (status == 1) delete_node(list, player);
    else if (status == 2){
        free(enemy->name);
        free(enemy->type);
        free(enemy);
    }
}

void    battle(user_t *user, p_list_t *list){
    int status = 0;
    p_t *enemy, *player;

    srand(time(NULL));
    enemy = get_rand_pokemon(list, rand()%list->numOfData + 1);

    print_gard(2);
    printf(BLUE"앗! 야생의 %s이(가) 나타났다!\n"DEFAULT, enemy->name);
    printf(YELLOW"%s\n> "DEFAULT, BAR);
    fflush_and_getc();

    player = pick_player_pokemon(user->list);
    while (1){
        player_turn(user, player, enemy, &status); if (status) break;
        enemy_turn(user, player, enemy, &status); if (status) break;
    }
    free_node(status, enemy, player, list);
}

void    walking(){
    int random;

    srand(time(NULL));
    random = rand()%2 + 1;
    for (int i = 0; i < random; i++){
        set_console(1, 1, "길을 걷는 중 . \n"); usleep(600000);
        set_console(1, 1, "길을 걷는 중 ..\n"); usleep(600000);
        set_console(1, 1, "길을 걷는 중 ...\n"); usleep(600000);
    }
}

void    travel(user_t *user, p_list_t *list){
    walking();
    battle(user, list);
}
