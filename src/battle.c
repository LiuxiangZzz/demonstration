#include "battle.h"

/**
 * 初始化角色
 */
void init_character(Character *chara, const char *name, int attack, int speed) {
    int i = 0;
    while (name[i] != '\0' && i < 19) {
        chara->name[i] = name[i];
        i++;
    }
    chara->name[i] = '\0';
    
    chara->hp = MAX_HP;
    chara->max_hp = MAX_HP;
    chara->attack = attack;
    chara->speed = speed;
}

/**
 * 攻击函数
 */
int attack(Character *attacker, Character *defender) {
    /* 判断是否闪避 */
    int miss_roll = rand() % 100;
    if (miss_roll < MISS_RATE) {
        printf("  %s 的攻击被 %s 闪避了！\n", attacker->name, defender->name);
        return 0;
    }
    
    /* 计算基础伤害 */
    int damage = attacker->attack;
    
    /* 判断是否暴击 */
    int crit_roll = rand() % 100;
    if (crit_roll < CRITICAL_RATE) {
        damage = damage * CRITICAL_DAMAGE / 100;
        printf("  【暴击！】");
    }
    
    /* 伤害波动（80%-120%） */
    int variance = 80 + (rand() % 41);
    damage = damage * variance / 100;
    
    /* 造成伤害 */
    defender->hp -= damage;
    if (defender->hp < 0) {
        defender->hp = 0;
    }
    
    printf("  %s 对 %s 造成了 %d 点伤害！", attacker->name, defender->name, damage);
    printf(" %s 剩余血量: %d\n", defender->name, defender->hp);
    
    return damage;
}

/**
 * 判断是否有人死亡
 */
int check_winner(Character *chara1, Character *chara2) {
    if (chara1->hp <= 0) {
        return 1;  /* 角色1死亡 */
    }
    if (chara2->hp <= 0) {
        return 2;  /* 角色2死亡 */
    }
    return 0;  /* 无人死亡 */
}

/**
 * 显示角色状态
 */
void show_status(Character *chara) {
    printf("%s: HP %d/%d, 攻击力 %d, 攻速 %d\n", 
           chara->name, chara->hp, chara->max_hp, chara->attack, chara->speed);
}
