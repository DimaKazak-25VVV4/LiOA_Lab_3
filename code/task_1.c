#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef struct element {
    char data[256];
    int priority;
    struct element *next;
} element;

element *head = NULL;   // начало приоритетной очереди
element *last = NULL;   // конец приоритетной очереди

element* createNode(void) {
    element *p = NULL;
    char s[256];

    p = (element*)malloc(sizeof(element));
    if (p == NULL) {
        printf("Ошибка при распределении памяти\n");
        exit(1);
    }

    printf("Введите название объекта: ");
    scanf("%255s", s);  // защита от переполнения буфера

    if (s[0] == '\0') {
        printf("Запись не была произведена\n");
        free(p);
        return NULL;
    }

    strcpy(p->data, s);

    printf("Введите приоритет (целое число): ");
    scanf("%d", &p->priority);

    p->next = NULL;

    return p;
}


void addWithPriority(void) {
    element *newNode = createNode();
    if (newNode == NULL) {
        return;  // если создание узла не удалось
    }

    // случай 1: список пуст
    if (head == NULL) {
        head = newNode;
        last = newNode;
        return;
    }

    // случай 2: новый элемент должен стать первым (приоритет больше, чем у head)
    if (newNode->priority > head->priority) {
        newNode->next = head;
        head = newNode;
        return;
    }

    // случай 3: ищем место для вставки в середину или в конец
    element *current = head;
    element *previous = NULL;

    // идём по списку, пока следующий элемент существует
    // и его приоритет больше или равен приоритету нового узла
    while (current != NULL && current->priority >= newNode->priority) {
        previous = current;
        current = current->next;
    }

    // вставляем между previous и current
    previous->next = newNode;
    newNode->next = current;

    // если вставили в самый конец, обновляем last
    if (current == NULL) {
        last = newNode;
    }
}


int main(void) {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    int choice;
    while (1) {
        printf("\n1. Добавить элемент в приоритетную очередь\n");
        printf("2. Показать очередь\n");
        printf("0. Выход\n");
        printf("Выбор: ");
        scanf("%d", &choice);

        if (choice == 1) {
            addWithPriority();
        } else if (choice == 2) {
            // тут позже напишешь функцию просмотра
            element *cur = head;
            if (cur == NULL) {
                printf("Очередь пуста\n");
            } else {
                while (cur != NULL) {
                    printf("Объект: %s, приоритет: %d\n", cur->data, cur->priority);
                    cur = cur->next;
                }
            }
        } else if (choice == 0) {
            // тут потом добавишь очистку памяти
            break;
        } else {
            printf("Неверный выбор\n");
        }
    }

    return 0;
}
