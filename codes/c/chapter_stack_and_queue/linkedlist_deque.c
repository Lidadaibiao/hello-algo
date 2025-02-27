/**
 * File: linkedlist_deque.c
 * Created Time: 2023-03-13
 * Author: Gonglja (glj0@outlook.com)
 */

#include "../include/include.h"

/* 双向链表结点 */
struct DoublyListNode {
    int val;                     // 结点值
    struct DoublyListNode *next; // 后继结点
    struct DoublyListNode *prev; // 前驱结点
};

typedef struct DoublyListNode DoublyListNode;

/* 双向链表结点构造方法 */
DoublyListNode *newDoublyListNode(int num) {
    DoublyListNode* new = (DoublyListNode *) malloc(sizeof(DoublyListNode));
    new->val = num;
    new->next = NULL;
    new->prev = NULL;
    return new;
}

/* 双向链表结点析构方法 */
void delDoublyListNode(DoublyListNode *node) {
    free(node);
}

/* 基于双向链表实现的双向队列 */
struct LinkedListDeque {
    DoublyListNode *front, *rear; // 头结点 front ，尾结点 rear
    int queSize;                  // 双向队列的长度
};

typedef struct LinkedListDeque LinkedListDeque;

/* 构造方法 */
LinkedListDeque *newLinkedListDeque() {
    LinkedListDeque *deque = (LinkedListDeque *) malloc(sizeof(LinkedListDeque));
    deque->front = NULL;
    deque->rear = NULL;
    deque->queSize = 0;
}

/* 析构方法 */
void delLinkedListdeque(LinkedListDeque *deque) {
    // 释放所有结点
    for (int i=0; i<deque->queSize && deque->front != NULL; i++) {
        DoublyListNode *tmp = deque->front;
        deque->front = deque->front->next;
        free(tmp);
    }
    // 释放 deque 结构体
    free(deque);
}

/* 获取队列的长度 */
int size(LinkedListDeque *deque) {
    return deque->queSize;
}

/* 判断队列是否为空 */
bool empty(LinkedListDeque *deque) {
    return (size(deque) == 0);
}

/* 入队 */
void push(LinkedListDeque *deque, int num, bool isFront) {
    DoublyListNode *node = newDoublyListNode(num);
    // 若链表为空，则令 front, rear 都指向node
    if (empty(deque)) {
        deque->front = deque->rear = node;
    }
    // 队首入队操作
    else if (isFront){
        // 将 node 添加至链表头部
        deque->front->prev = node;
        node->next = deque->front;
        deque->front = node;// 更新头结点
    }
    // 对尾入队操作
    else {
        // 将 node 添加至链表尾部
        deque->rear->next = node;
        node->prev = deque->rear;
        deque->rear = node;
    }
    deque->queSize++; // 更新队列长度
}

/* 队首入队 */
void pushFirst(LinkedListDeque *deque, int num) {
    push(deque, num, true);
}

/* 队尾入队 */
void pushLast(LinkedListDeque *deque, int num) {
    push(deque, num, false);
}

/* 访问队首元素 */
int peekFirst(LinkedListDeque *deque) {
    assert(size(deque) && deque->front);
    return deque->front->val;
}

/* 访问队尾元素 */
int peekLast(LinkedListDeque *deque) {
    assert(size(deque) && deque->rear);
    return deque->rear->val;
}

/* 出队 */
int pop(LinkedListDeque *deque, bool isFront) {
    if (empty(deque))
        return -1;
    int val;
    // 队首出队操作
    if(isFront) {
        val = peekFirst(deque); // 暂存头结点值
        DoublyListNode *fNext = deque->front->next;
        if (fNext) {
            fNext->prev = NULL;
            deque->front->next = NULL;
            delDoublyListNode(deque->front);
        }
        deque->front = fNext; // 更新头结点
    }
    // 队尾出队操作
    else {
        val = peekLast(deque); // 暂存尾结点值
        DoublyListNode *rPrev = deque->rear->prev;
        if (rPrev) {
            rPrev->next = NULL;
            deque->rear->prev = NULL;
            delDoublyListNode(deque->rear);
        }
        deque->rear = rPrev; // 更新尾结点
    }
    deque->queSize--;      // 更新队列长度
    return val;
}

/* 队首出队 */
int popFirst(LinkedListDeque *deque) {
    return pop(deque, true);
}

/* 队尾出队 */
int popLast(LinkedListDeque *deque) {
    return pop(deque, false);
}

/* 打印队列 */
void printLinkedListDeque(LinkedListDeque *deque) {
    int arr[deque->queSize];
    // 拷贝链表中的数据到数组
    int i;
    DoublyListNode *node;
    for (i=0, node = deque->front; i < deque->queSize; i++){
      arr[i] = node->val;
      node = node->next;
    }
    printArray(arr, deque->queSize);
}

/* Driver Code */
int main() {
    /* 初始化双向队列 */
    LinkedListDeque *deque = newLinkedListDeque();
    pushLast(deque, 3);
    pushLast(deque, 2);
    pushLast(deque, 5);
    printf("双向队列 deque = ");
    printLinkedListDeque(deque);

    /* 访问元素 */
    int peekFirstNum = peekFirst(deque);
    printf("队首元素 peekFirst = %d\r\n", peekFirstNum);
    int peekLastNum = peekLast(deque);
    printf("队首元素 peekLast = %d\r\n", peekLastNum);

    /* 元素入队 */
    pushLast(deque, 4);
    printf("元素 4 队尾入队后 deque =");
    printLinkedListDeque(deque);
    pushFirst(deque, 1);
    printf("元素 1 队首入队后 deque =");
    printLinkedListDeque(deque);

    /* 元素出队 */
    int popLastNum = popLast(deque);
    printf("队尾出队元素 popLast = %d，队尾出队后 deque = ", popLastNum);
    printLinkedListDeque(deque);
    int popFirstNum = popFirst(deque);
    printf("队首出队元素 popFirst = %d，队首出队后 deque = ", popFirstNum);
    printLinkedListDeque(deque);

    /* 获取队列的长度 */
    int dequeSize = size(deque);
    printf("双向队列长度 size = %d\r\n", dequeSize);

    /* 判断队列是否为空 */
    bool isEmpty = empty(deque);
    printf("双向队列是否为空 = %s\r\n", isEmpty ? "true" : "false");

    /* 释放内存 */
    delLinkedListdeque(deque);
    return 0;
}

