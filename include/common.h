#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

/* 角色属性定义 */
#define MAX_HP 10000
#define DIANWEI_ATTACK 350    /* 典韦攻击力 */
#define DIANWEI_SPEED 8       /* 典韦攻速（每回合攻击次数） */
#define CAOCAO_ATTACK 280     /* 曹操攻击力 */
#define CAOCAO_SPEED 10       /* 曹操攻速（每回合攻击次数） */

/* 战斗相关常量 */
#define CRITICAL_RATE 15      /* 暴击率（百分比） */
#define CRITICAL_DAMAGE 200   /* 暴击伤害倍数（百分比） */
#define MISS_RATE 10          /* 闪避率（百分比） */

#endif /* COMMON_H */
