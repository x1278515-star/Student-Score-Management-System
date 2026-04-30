#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// 定义学生结点
typedef struct Student {
    char id[20];
    char name[20];
    float score;
    struct Student* next;
} StudentNode;

// 函数声明
StudentNode* createList();
void searchStudent(StudentNode* head);
void insertStudent(StudentNode* head);
void deleteStudent(StudentNode** head);
void display(StudentNode* head);

int main() {
    StudentNode* head = NULL;
    int choice;

    while (1) {
        printf("\n--- 学生成绩管理系统 ---\n");
        printf("1. 登记学生成绩\n2. 查询学生成绩\n3. 插入学生成绩\n4. 删除学生成绩\n5. 退出\n");
        printf("请选择操作: ");
        if (scanf("%d", &choice) != 1) {
            // 清理输入并继续
            int c;
            while ((c = getchar()) != EOF && c != '\n');
            printf("输入无效，请输入数字。\n");
            continue;
        }

        switch (choice) {
        case 1: head = createList(); break;
        case 2: searchStudent(head); break;
        case 3: insertStudent(head); break;
        case 4: deleteStudent(&head); break;
        case 5:
            // 退出前释放链表内存
            while (head) {
                StudentNode* tmp = head;
                head = head->next;
                free(tmp);
            }
            exit(0);
        default: printf("无效选择！\n");
        }
    }
    return 0;
}

// 创建链表并返回头指针
StudentNode* createList() {
    int n;
    printf("请输入学生人数: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        int c;
        while ((c = getchar()) != EOF && c != '\n');
        printf("人数输入无效。\n");
        return NULL;
    }

    StudentNode* head = NULL;
    StudentNode* tail = NULL;

    for (int i = 0; i < n; ++i) {
        StudentNode* node = (StudentNode*)malloc(sizeof(StudentNode));
        if (!node) {
            printf("内存分配失败。\n");
            // 释放已分配的节点
            while (head) {
                StudentNode* tmp = head;
                head = head->next;
                free(tmp);
            }
            return NULL;
        }
        printf("第 %d 个学生 - 学号: ", i + 1);
        scanf("%19s", node->id);
        printf("第 %d 个学生 - 姓名: ", i + 1);
        scanf("%19s", node->name);
        printf("第 %d 个学生 - 成绩: ", i + 1);
        if (scanf("%f", &node->score) != 1) {
            int c;
            while ((c = getchar()) != EOF && c != '\n');
            node->score = 0.0f;
        }
        node->next = NULL;

        if (head == NULL) {
            head = tail = node;
        }
        else {
            tail->next = node;
            tail = node;
        }
    }

    printf("已登记 %d 名学生。\n", n);
    display(head);
    return head;
}

// 按学号查询
void searchStudent(StudentNode* head) {
    if (!head) {
        printf("当前没有学生记录，请先登记学生成绩。\n");
        return;
    }
    char id[20];
    printf("请输入要查询的学号: ");
    scanf("%19s", id);

    StudentNode* cur = head;
    while (cur) {
        if (strcmp(cur->id, id) == 0) {
            printf("找到学生: 学号=%s, 姓名=%s, 成绩=%.2f\n", cur->id, cur->name, cur->score);
            return;
        }
        cur = cur->next;
    }
    printf("未找到学号为 %s 的学生。\n", id);
}

// 在指定学号之后插入新学生（如果找不到指定学号则插入到链表末尾）
// 注意：函数签名无法修改，因此当 head == NULL 时提示先登记
void insertStudent(StudentNode* head) {
    if (!head) {
        printf("当前没有学生记录，无法插入。请先选择 1. 登记学生成绩。\n");
        return;
    }

    char afterId[20];
    printf("请输入要在其后插入的新节点的学号（输入目标学号，若找不到则插入末尾）: ");
    scanf("%19s", afterId);

    StudentNode* node = (StudentNode*)malloc(sizeof(StudentNode));
    if (!node) {
        printf("内存分配失败，插入失败。\n");
        return;
    }
    printf("新学生 - 学号: ");
    scanf("%19s", node->id);
    printf("新学生 - 姓名: ");
    scanf("%19s", node->name);
    printf("新学生 - 成绩: ");
    if (scanf("%f", &node->score) != 1) {
        int c;
        while ((c = getchar()) != EOF && c != '\n');
        node->score = 0.0f;
    }
    node->next = NULL;

    StudentNode* cur = head;
    while (cur) {
        if (strcmp(cur->id, afterId) == 0) {
            node->next = cur->next;
            cur->next = node;
            printf("已在学号 %s 之后插入学生 %s。\n", afterId, node->id);
            display(head);
            return;
        }
        if (!cur->next) break;
        cur = cur->next;
    }

    // 如果未找到目标学号，插入到末尾
    cur->next = node;
    printf("未找到学号 %s，已将学生插入到末尾。\n", afterId);
    display(head);
}

// 按学号删除
void deleteStudent(StudentNode** head) {
    if (!head || !(*head)) {
        printf("当前没有学生记录，无法删除。\n");
        return;
    }

    char id[20];
    printf("请输入要删除的学号: ");
    scanf("%19s", id);

    StudentNode* cur = *head;
    StudentNode* prev = NULL;

    while (cur) {
        if (strcmp(cur->id, id) == 0) {
            if (prev) {
                prev->next = cur->next;
            }
            else {
                // 删除头节点
                *head = cur->next;
            }
            printf("已删除学号为 %s 的学生（姓名=%s）。\n", cur->id, cur->name);
            free(cur);
            display(*head);
            return;
        }
        prev = cur;
        cur = cur->next;
    }

    printf("未找到学号为 %s 的学生，删除失败。\n", id);
}

// 显示链表
void display(StudentNode* head) {
    if (!head) {
        printf("当前无学生记录。\n");
        return;
    }
    printf("\n当前学生列表:\n");
    StudentNode* cur = head;
    int idx = 1;
    while (cur) {
        printf("%d: 学号=%s, 姓名=%s, 成绩=%.2f\n", idx++, cur->id, cur->name, cur->score);
        cur = cur->next;
    }
}