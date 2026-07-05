#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ID_LEN 20
#define MAX_NAME_LEN 20
#define MAX_SCORE 100
#define MIN_SCORE 0
#define DATA_FILE "students.dat"

// 学生结构体
typedef struct Student {
    char id[MAX_ID_LEN];
    char name[MAX_NAME_LEN];
    float score;
    struct Student* next;
} StudentNode;

// 函数声明
StudentNode* createList();
StudentNode* addToList(StudentNode* head, const char* id, const char* name, float score);
void searchStudent(StudentNode* head);
void insertStudent(StudentNode** head);
void updateStudent(StudentNode* head);
void deleteStudent(StudentNode** head);
void display(StudentNode* head);
void displayStatistics(StudentNode* head);
void freeList(StudentNode* head);
int exists(StudentNode* head, const char* id);
int isValidScore(float score);
void saveToFile(StudentNode* head, const char* filename);
StudentNode* loadFromFile(const char* filename);
StudentNode* sortByScore(StudentNode* head);
void clearInputBuffer();

// 主函数
int main() {
    StudentNode* head = NULL;
    int choice;

    // 程序启动时加载数据
    head = loadFromFile(DATA_FILE);
    if (head != NULL) {
        printf("已从文件加载学生数据。\n\n");
    }

    while (1) {
        printf("\n========== 学生成绩管理系统 ==========\n");
        printf("1. 登记学生成绩(覆盖)    2. 查询学生成绩\n");
        printf("3. 插入新学生          4. 更新学生成绩\n");
        printf("5. 删除学生            6. 显示所有学生\n");
        printf("7. 显示统计信息        8. 按成绩排序显示\n");
        printf("9. 保存到文件          0. 退出\n");
        printf("=====================================\n");
        printf("请选择操作 (0-9): ");

        if (scanf("%d", &choice) != 1) {
            clearInputBuffer();
            printf("❌ 输入无效！请输入数字。\n");
            continue;
        }

        switch (choice) {
        case 1: {
            // 覆盖模式：先清空再创建
            freeList(head);
            head = createList();
            printf("✓ 学生数据已登记。\n");
            break;
        }
        case 2:
            searchStudent(head);
            break;
        case 3:
            insertStudent(&head);
            break;
        case 4:
            updateStudent(head);
            break;
        case 5:
            deleteStudent(&head);
            break;
        case 6:
            display(head);
            break;
        case 7:
            displayStatistics(head);
            break;
        case 8: {
            StudentNode* sorted = sortByScore(head);
            if (sorted) {
                printf("\n按成绩从高到低排序：\n");
                display(sorted);
                freeList(sorted);
            }
            break;
        }
        case 9:
            saveToFile(head, DATA_FILE);
            printf("✓ 数据已保存到文件。\n");
            break;
        case 0:
            saveToFile(head, DATA_FILE);
            freeList(head);
            printf("✓ 程序已退出。数据已自动保存。\n");
            return 0;
        default:
            printf("❌ 无效选择！请输入 0-9。\n");
        }
    }
}

// 清空输入缓冲区
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// 判断成绩是否有效
int isValidScore(float score) {
    return score >= MIN_SCORE && score <= MAX_SCORE;
}

// 判断学号是否存在
int exists(StudentNode* head, const char* id) {
    while (head) {
        if (strcmp(head->id, id) == 0)
            return 1;
        head = head->next;
    }
    return 0;
}

// 释放链表
void freeList(StudentNode* head) {
    while (head) {
        StudentNode* tmp = head;
        head = head->next;
        free(tmp);
    }
}

// 向链表添加学生（辅助函数）
StudentNode* addToList(StudentNode* head, const char* id, const char* name, float score) {
    StudentNode* node = (StudentNode*)malloc(sizeof(StudentNode));
    if (!node) {
        printf("❌ 内存分配失败！\n");
        return head;
    }

    strncpy(node->id, id, MAX_ID_LEN - 1);
    node->id[MAX_ID_LEN - 1] = '\0';
    strncpy(node->name, name, MAX_NAME_LEN - 1);
    node->name[MAX_NAME_LEN - 1] = '\0';
    node->score = score;
    node->next = NULL;

    if (!head) {
        return node;
    }

    // 尾插
    StudentNode* tail = head;
    while (tail->next) {
        tail = tail->next;
    }
    tail->next = node;
    return head;
}

// 创建链表
StudentNode* createList() {
    int n;
    printf("请输入学生人数: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        clearInputBuffer();
        printf("❌ 输入无效！\n");
        return NULL;
    }

    if (n > 10000) {
        printf("❌ 学生人数过多，最多10000人。\n");
        return NULL;
    }

    StudentNode* head = NULL;

    for (int i = 0; i < n; i++) {
        char id[MAX_ID_LEN];
        char name[MAX_NAME_LEN];
        float score;

        printf("\n--- 第 %d 个学生 ---\n", i + 1);

        printf("学号: ");
        scanf("%19s", id);

        if (exists(head, id)) {
            printf("❌ 学号 %s 重复！请重新输入。\n", id);
            i--;
            continue;
        }

        printf("姓名: ");
        scanf("%19s", name);

        printf("成绩 (0-100): ");
        while (scanf("%f", &score) != 1 || !isValidScore(score)) {
            clearInputBuffer();
            printf("❌ 输入错误！请输入 0-100 之间的成绩: ");
        }

        head = addToList(head, id, name, score);
        printf("✓ 学生已添加。\n");
    }

    return head;
}

// 查询
void searchStudent(StudentNode* head) {
    if (!head) {
        printf("❌ 无学生数据。\n");
        return;
    }

    char id[MAX_ID_LEN];
    printf("输入学号: ");
    scanf("%19s", id);

    while (head) {
        if (strcmp(head->id, id) == 0) {
            printf("\n✓ 找到学生信息：\n");
            printf("  学号: %s\n  姓名: %s\n  成绩: %.2f\n", head->id, head->name, head->score);
            return;
        }
        head = head->next;
    }
    printf("❌ 未找到学号为 %s 的学生。\n", id);
}

// 插入学生（头插）
void insertStudent(StudentNode** head) {
    StudentNode* node = (StudentNode*)malloc(sizeof(StudentNode));
    if (!node) {
        printf("❌ 内存分配失败！\n");
        return;
    }

    printf("学号: ");
    scanf("%19s", node->id);

    if (exists(*head, node->id)) {
        printf("❌ 学号已存在！\n");
        free(node);
        return;
    }

    printf("姓名: ");
    scanf("%19s", node->name);

    printf("成绩 (0-100): ");
    while (scanf("%f", &node->score) != 1 || !isValidScore(node->score)) {
        clearInputBuffer();
        printf("❌ 输入错误！请输入 0-100 之间的成绩: ");
    }

    node->next = *head;
    *head = node;

    printf("✓ 插入成功！\n");
}

// 更新学生成绩
void updateStudent(StudentNode* head) {
    if (!head) {
        printf("❌ 无学生数据。\n");
        return;
    }

    char id[MAX_ID_LEN];
    printf("输入要更新的学号: ");
    scanf("%19s", id);

    while (head) {
        if (strcmp(head->id, id) == 0) {
            printf("当前成绩: %.2f\n", head->score);
            printf("输入新成绩 (0-100): ");
            while (scanf("%f", &head->score) != 1 || !isValidScore(head->score)) {
                clearInputBuffer();
                printf("❌ 输入错误！请输入 0-100 之间的成绩: ");
            }
            printf("✓ 成绩已更新。\n");
            return;
        }
        head = head->next;
    }
    printf("❌ 未找到该学生。\n");
}

// 删除学生
void deleteStudent(StudentNode** head) {
    if (!*head) {
        printf("❌ 无学生数据。\n");
        return;
    }

    char id[MAX_ID_LEN];
    printf("输入要删除的学号: ");
    scanf("%19s", id);

    StudentNode* cur = *head;
    StudentNode* prev = NULL;

    while (cur) {
        if (strcmp(cur->id, id) == 0) {
            if (prev)
                prev->next = cur->next;
            else
                *head = cur->next;

            printf("✓ 学生 %s 已删除。\n", cur->name);
            free(cur);
            return;
        }
        prev = cur;
        cur = cur->next;
    }
    printf("❌ 未找到该学生。\n");
}

// 显示所有学生
void display(StudentNode* head) {
    if (!head) {
        printf("❌ 无学生数据。\n");
        return;
    }

    printf("\n========== 学生信息表 ==========\n");
    printf("%-12s %-12s %10s\n", "学号", "姓名", "成绩");
    printf("================================\n");

    int count = 0;
    while (head) {
        printf("%-12s %-12s %10.2f\n", head->id, head->name, head->score);
        head = head->next;
        count++;
    }
    printf("================================\n");
    printf("总计: %d 名学生\n\n", count);
}

// 显示统计信息
void displayStatistics(StudentNode* head) {
    if (!head) {
        printf("❌ 无学生数据。\n");
        return;
    }

    int count = 0;
    float sum = 0, max = -1, min = 101;

    StudentNode* temp = head;
    while (temp) {
        count++;
        sum += temp->score;
        if (temp->score > max) max = temp->score;
        if (temp->score < min) min = temp->score;
        temp = temp->next;
    }

    printf("\n========== 统计信息 ==========\n");
    printf("学生总数: %d\n", count);
    printf("平均成绩: %.2f\n", sum / count);
    printf("最高成绩: %.2f\n", max);
    printf("最低成绩: %.2f\n", min);
    printf("===============================\n\n");
}

// 按成绩排序（降序）- 返回新链表，不修改原链表
StudentNode* sortByScore(StudentNode* head) {
    if (!head || !head->next) {
        return head;
    }

    // 使用冒泡排序的思想
    int swapped;
    StudentNode* ptr1, * lptr = NULL;

    do {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if (ptr1->score < ptr1->next->score) {
                // 交换数据
                char tempId[MAX_ID_LEN], tempName[MAX_NAME_LEN];
                float tempScore;

                strcpy(tempId, ptr1->id);
                strcpy(tempName, ptr1->name);
                tempScore = ptr1->score;

                strcpy(ptr1->id, ptr1->next->id);
                strcpy(ptr1->name, ptr1->next->name);
                ptr1->score = ptr1->next->score;

                strcpy(ptr1->next->id, tempId);
                strcpy(ptr1->next->name, tempName);
                ptr1->next->score = tempScore;

                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);

    return head;
}

// 保存到文件
void saveToFile(StudentNode* head, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        printf("❌ 无法打开文件 %s\n", filename);
        return;
    }

    int count = 0;
    StudentNode* temp = head;
    while (temp) {
        count++;
        temp = temp->next;
    }

    fwrite(&count, sizeof(int), 1, file);

    temp = head;
    while (temp) {
        fwrite(temp->id, sizeof(char), MAX_ID_LEN, file);
        fwrite(temp->name, sizeof(char), MAX_NAME_LEN, file);
        fwrite(&temp->score, sizeof(float), 1, file);
        temp = temp->next;
    }

    fclose(file);
}

// 从文件加载
StudentNode* loadFromFile(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        return NULL;
    }

    int count;
    if (fread(&count, sizeof(int), 1, file) != 1) {
        fclose(file);
        return NULL;
    }

    StudentNode* head = NULL;

    for (int i = 0; i < count; i++) {
        char id[MAX_ID_LEN];
        char name[MAX_NAME_LEN];
        float score;

        if (fread(id, sizeof(char), MAX_ID_LEN, file) != MAX_ID_LEN ||
            fread(name, sizeof(char), MAX_NAME_LEN, file) != MAX_NAME_LEN ||
            fread(&score, sizeof(float), 1, file) != 1) {
            break;
        }

        head = addToList(head, id, name, score);
    }

    fclose(file);
    return head;
}