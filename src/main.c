#include "battle.h"

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
        
        /* 典韦攻击（根据攻速攻击多次） */
        for (int i = 0; i < dianwei.speed; i++) {
            if (check_winner(&dianwei, &caocao) != 0) {
                break;
            }
            attack(&dianwei, &caocao);
        }
        
        /* 检查胜负 */
        int winner = check_winner(&dianwei, &caocao);
        if (winner == 2) {
            printf("\n【战斗结束】\n");
            printf("胜利者：%s！\n", dianwei.name);
            printf("最终状态：\n");
            show_status(&dianwei);
            show_status(&caocao);
            break;
        }
        
        /* 曹操攻击（根据攻速攻击多次） */
        for (int i = 0; i < caocao.speed; i++) {
            if (check_winner(&dianwei, &caocao) != 0) {
                break;
            }
            attack(&caocao, &dianwei);
        }
        
        /* 检查胜负 */
        winner = check_winner(&dianwei, &caocao);
        if (winner == 1) {
            printf("\n【战斗结束】\n");
            printf("胜利者：%s！\n", caocao.name);
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
    
    printf("\n========================================\n");
    printf("当前进程ID: %d\n", getpid());
    printf("========================================\n");
    
    return 0;
}
