#ifndef BATTLE_H
#define BATTLE_H

#include "common.h"

/* 角色结构体 */
typedef struct {
    char name[20];    /* 角色名称 */
    int hp;           /* 当前血量 */
    int max_hp;       /* 最大血量 */
    int attack;       /* 攻击力 */
    int speed;        /* 攻速 */
} Character;

/* 函数声明 */

/**
 * 初始化角色
 * @param chara 角色指针
 * @param name 角色名称
 * @param attack 攻击力
 * @param speed 攻速
 */
void init_character(Character *chara, const char *name, int attack, int speed);

/**
 * 攻击函数
 * @param attacker 攻击者
 * @param defender 防御者
 * @return 实际造成的伤害
 */
int attack(Character *attacker, Character *defender);

/**
 * 判断是否有人死亡
 * @param chara1 角色1
 * @param chara2 角色2
 * @return 0-无人死亡, 1-角色1死亡, 2-角色2死亡
 */
int check_winner(Character *chara1, Character *chara2);

/**
 * 显示角色状态
 * @param chara 角色指针
 */
void show_status(Character *chara);

#endif /* BATTLE_H */
