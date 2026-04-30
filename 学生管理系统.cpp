#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 学生结构体
typedef struct Student {
    char id[20];
    char name[20];
    float score;
    struct Student* next;
} StudentNode;

// 函数声明
StudentNode* createList();
void searchStudent(StudentNode* head);
void insertStudent(StudentNode** head);
void deleteStudent(StudentNode** head);
void display(StudentNode* head);
void freeList(StudentNode* head);
int exists(StudentNode* head, char* id);

// 主函数
int main() {
    StudentNode* head = NULL;
    int choice;

    while (1) {
        printf("\n--- 学生成绩管理系统 ---\n");
        printf("1. 登记学生成绩\n2. 查询学生成绩\n3. 插入学生成绩\n4. 删除学生成绩\n5. 显示所有\n6. 退出\n");
        printf("请选择操作: ");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("输入无效！\n");
            continue;
        }

        switch (choice) {
        case 1:
            freeList(head);
            head = createList();
            break;
        case 2:
            searchStudent(head);
            break;
        case 3:
            insertStudent(&head);
            break;
        case 4:
            deleteStudent(&head);
            break;
        case 5:
            display(head);
            break;
        case 6:
            freeList(head);
            return 0;
        default:
            printf("无效选择！\n");
        }
    }
}

// 释放链表
void freeList(StudentNode* head) {
    while (head) {
        StudentNode* tmp = head;
        head = head->next;
        free(tmp);
    }
}

// 判断学号是否存在
int exists(StudentNode* head, char* id) {
    while (head) {
        if (strcmp(head->id, id) == 0)
            return 1;
        head = head->next;
    }
    return 0;
}

// 创建链表
StudentNode* createList() {
    int n;
    printf("请输入学生人数: ");
    scanf("%d", &n);

    StudentNode* head = NULL;
    StudentNode* tail = NULL;

    for (int i = 0; i < n; i++) {
        StudentNode* node = (StudentNode*)malloc(sizeof(StudentNode));

        printf("学号: ");
        scanf("%19s", node->id);

        if (exists(head, node->id)) {
            printf("学号重复！重新输入。\n");
            free(node);
            i--;
            continue;
        }

        printf("姓名: ");
        scanf("%19s", node->name);

        printf("成绩: ");
        while (scanf("%f", &node->score) != 1) {
            while (getchar() != '\n');
            printf("输入错误，请重新输入成绩: ");
        }

        node->next = NULL;

        if (!head)
            head = tail = node;
        else {
            tail->next = node;
            tail = node;
        }
    }

    return head;
}

// 查询
void searchStudent(StudentNode* head) {
    char id[20];
    printf("输入学号: ");
    scanf("%19s", id);

    while (head) {
        if (strcmp(head->id, id) == 0) {
            printf("找到：%s %s %.2f\n", head->id, head->name, head->score);
            return;
        }
        head = head->next;
    }
    printf("未找到\n");
}

// 插入（头插）
void insertStudent(StudentNode** head) {
    StudentNode* node = (StudentNode*)malloc(sizeof(StudentNode));

    printf("学号: ");
    scanf("%19s", node->id);

    if (exists(*head, node->id)) {
        printf("学号已存在！\n");
        free(node);
        return;
    }

    printf("姓名: ");
    scanf("%19s", node->name);

    printf("成绩: ");
    scanf("%f", &node->score);

    node->next = *head;
    *head = node;

    printf("插入成功！\n");
}

// 删除
void deleteStudent(StudentNode** head) {
    char id[20];
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

            free(cur);
            printf("删除成功！\n");
            return;
        }
        prev = cur;
        cur = cur->next;
    }
    printf("未找到该学生。\n");
}

// 显示
void display(StudentNode* head) {
    if (!head) {
        printf("无数据\n");
        return;
    }

    while (head) {
        printf("%s %s %.2f\n", head->id, head->name, head->score);
        head = head->next;
    }
}