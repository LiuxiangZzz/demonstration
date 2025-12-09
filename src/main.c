#include "battle.h"
//return 1
/**
 * 主函数 - 典韦 vs 曹操 决斗
 */
int main(void) {
    /* 初始化随机数种子 */
    srand((unsigned int)time(NULL));
    
    printf("========================================\n");
    printf("     典韦 vs 曹操 决斗系统\n");
    printf("========================================\n\n");
    
    /* 初始化角色 */
    Character dianwei, caocao;
    init_character(&dianwei, "典韦", DIANWEI_ATTACK, DIANWEI_SPEED);
    init_character(&caocao, "曹操", CAOCAO_ATTACK, CAOCAO_SPEED);
    
    /* 显示初始状态 */
    printf("【初始状态】\n");
    show_status(&dianwei);
    show_status(&caocao);
    printf("\n");
    
    /* 战斗循环 */
    int round = 1;
    while (1) {
        printf("--- 第 %d 回合 ---\n", round);
        
        /* 按照攻速决定攻击顺序：攻速高的先攻击 */
        int dianwei_attacks = 0;  /* 典韦本回合已攻击次数 */
        int caocao_attacks = 0;   /* 曹操本回合已攻击次数 */
        int total_attacks = dianwei.speed + caocao.speed;  /* 本回合总攻击次数 */
        
        /* 攻速高的先攻击 */
        Character *first_attacker = (caocao.speed > dianwei.speed) ? &caocao : &dianwei;
        Character *second_attacker = (caocao.speed > dianwei.speed) ? &dianwei : &caocao;
        int *first_count = (caocao.speed > dianwei.speed) ? &caocao_attacks : &dianwei_attacks;
        int *second_count = (caocao.speed > dianwei.speed) ? &dianwei_attacks : &caocao_attacks;
        int first_speed = (caocao.speed > dianwei.speed) ? caocao.speed : dianwei.speed;
        int second_speed = (caocao.speed > dianwei.speed) ? dianwei.speed : caocao.speed;
        
        /* 按照攻速比例交替攻击 */
        for (int i = 0; i < total_attacks; i++) {
            /* 检查是否有人死亡 */
            int winner = check_winner(&dianwei, &caocao);
            if (winner != 0) {
                printf("\n【战斗结束】\n");
                if (winner == 1) {
                    printf("胜利者：%s！\n", caocao.name);
                } else {
                    printf("胜利者：%s！\n", dianwei.name);
                }
                printf("最终状态：\n");
                show_status(&dianwei);
                show_status(&caocao);
                goto battle_end;
            }
            
            /* 判断谁应该攻击：使用进度比较 */
            /* 进度 = 已攻击次数 * 对方总攻速 / 自己总攻速 */
            /* 这样攻速高的角色进度增长慢，会先攻击 */
            int first_progress = (*first_count) * second_speed;
            int second_progress = (*second_count) * first_speed;
            
            /* 如果第一个角色还没攻击完，且进度小于等于第二个，或者第二个已经攻击完 */
            if (*first_count < first_speed && (first_progress <= second_progress || *second_count >= second_speed)) {
                /* 第一个角色攻击（攻速高的） */
                attack(first_attacker, second_attacker);
                (*first_count)++;
            } else if (*second_count < second_speed) {
                /* 第二个角色攻击 */
                attack(second_attacker, first_attacker);
                (*second_count)++;
            } else if (*first_count < first_speed) {
                /* 如果第二个攻击完了，第一个还没攻击完，继续攻击 */
                attack(first_attacker, second_attacker);
                (*first_count)++;
            } else {
                /* 两个角色都攻击完了 */
                break;
            }
        }
        
        /* 检查胜负 */
        int winner = check_winner(&dianwei, &caocao);
        if (winner != 0) {
            printf("\n【战斗结束】\n");
            if (winner == 1) {
                printf("胜利者：%s！\n", caocao.name);
            } else {
                printf("胜利者：%s！\n", dianwei.name);
            }
            printf("最终状态：\n");
            show_status(&dianwei);
            show_status(&caocao);
            break;
        }
        
        /* 显示回合结束状态 */
        printf("\n回合结束状态：\n");
        show_status(&dianwei);
        show_status(&caocao);
        printf("\n");
        
        round++;
        
        /* 防止无限循环 */
        if (round > 1000) {
            printf("战斗时间过长，平局！\n");
            break;
        }
    }
    
battle_end:
    
    printf("\n========================================\n");
    printf("当前进程ID: %d\n", getpid());
    printf("========================================\n");
    
    return 0;
}
