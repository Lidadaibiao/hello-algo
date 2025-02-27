/**
 * File: array_deque.c
 * Created Time: 2023-03-13
 * Author: Gonglja (glj0@outlook.com)
 */

#include "../include/include.h"

/* 基于环形数组形成的双向队列 */
struct ArrayDeque {
    int *nums;       // 用于存储队列元素的数组
    int front;       // 队首指针，指向队首元素
    int queSize;     // 尾指针，指向队尾 + 1
    int queCapacity; // 队列容量
};

typedef struct ArrayDeque ArrayDeque;

/* 构造方法 */
ArrayDeque *newArrayDeque(int capacity) {
    ArrayDeque *deque = (ArrayDeque *) malloc(sizeof(ArrayDeque));
    // 初始化数组
    deque->queCapacity = capacity;
    deque->nums = (int *) malloc(sizeof(int) * deque->queCapacity);
    deque->front = deque->queSize = 0;
    return deque;
}

/* 析构方法 */
void delArrayDeque(ArrayDeque *deque) {
    free(deque->nums);
    deque->queCapacity = 0;
}

/* 获取双向队列的容量 */
int capacity(ArrayDeque *deque) {
    return deque->queCapacity;
}

/* 获取双向队列的长度 */
int size(ArrayDeque *deque) {
    return deque->queSize;
}

/* 判断双向队列是否为空 */
bool empty(ArrayDeque *deque) {
    return deque->queSize == 0;
}

int dequeIndex(ArrayDeque *deque, int i) {
    // 通过取余操作实现数组首尾相连
    // 当 i 越过数组尾部时，回到头部
    // 当 i 越过数组头部后，回到尾部
    return ((i + capacity(deque)) % capacity(deque));
}

/* 队首入队 */
void pushFirst(ArrayDeque *deque, int num) {
    if (deque->queSize == capacity(deque)) {
        printf("双向队列已满\r\n");
        return;
    }
    // 队首指针向左移动一位
    // 通过取余操作，实现 front 越过数组头部回到尾部
    deque->front = dequeIndex(deque, deque->front - 1);
    // 将 num 添加到队首
    deque->nums[deque->front] = num;
    deque->queSize++;
}

/* 队尾入队 */
void pushLast(ArrayDeque *deque, int num) {
    if (deque->queSize == capacity(deque)) {
        printf("双向队列已满\r\n");
        return;
    }
    // 计算尾指针，指向队尾索引 + 1
    int rear = dequeIndex(deque, deque->front + deque->queSize);
    // 将 num 添加至队尾
    deque->nums[rear] = num;
    deque->queSize++;
}

/* 访问队首元素 */
int peekFirst(ArrayDeque *deque) {
    // 访问异常：双向队列为空
    assert(empty(deque) == 0);
    return deque->nums[deque->front];        
}

/* 访问队尾元素 */
int peekLast(ArrayDeque *deque) {
    // 访问异常：双向队列为空
    assert(empty(deque) == 0);
    int last = dequeIndex(deque, deque->front + deque->queSize - 1);
    return deque->nums[last];     
}

/* 队首出队 */
int popFirst(ArrayDeque *deque) {
    int num = peekFirst(deque);
    // 队首指针向后移动一位
    deque->front = dequeIndex(deque, deque->front + 1);
    deque->queSize--;
    return num;
}

/* 队尾出队 */
int popLast(ArrayDeque *deque) {
    int num = peekLast(deque);
    deque->queSize--;
    return num;
}

/* 打印基于环形数组形成的队列 */
void printArrayDeque(ArrayDeque *deque) {
    int arr[deque->queSize];
    // 拷贝
    for (int i = 0, j = deque->front; i < deque->queSize; i++, j++) {
        arr[i] = deque->nums[j % deque->queCapacity];
    }
    printArray(arr, deque->queSize);
}


/* Driver Code */
int main() {
    /* 初始化队列 */
    int capacity = 10;
    ArrayDeque *deque = newArrayDeque(capacity);
    pushLast(deque, 3);
    pushLast(deque, 2);
    pushLast(deque, 5);
    printf("双向队列 deque = ");
    printArrayDeque(deque);

    /* 访问元素 */
    int peekFirstNum = peekFirst(deque);
    printf("队首元素 peekFirst = %d\r\n", peekFirstNum);
    int peekLastNum = peekLast(deque);
    printf("队尾元素 peekLast = %d\r\n", peekLastNum);

    /* 元素入队 */
    pushLast(deque, 4);
    printf("元素 4 队尾入队后 deque = ");
    printArrayDeque(deque);
    pushFirst(deque, 1);
    printf("元素 1 队首入队后 deque = ");
    printArrayDeque(deque);

    /* 元素出队 */
    int popLastNum = popLast(deque);
    printf("队尾出队元素 = %d，队尾出队后 deque= ", popLastNum);
    printArrayDeque(deque);
    int popFirstNum = popFirst(deque);
    printf("队首出队元素 = %d，队首出队后 deque= ", popFirstNum);
    printArrayDeque(deque);

    /* 获取队列的长度 */
    int dequeSize = size(deque);
    printf("双向队列长度 size = %d\r\n", dequeSize);

    /* 判断队列是否为空 */
    bool isEmpty = empty(deque);
    printf("队列是否为空 = %s\r\n", isEmpty ? "true" : "false");

    // 释放内存
    delArrayDeque(deque);
    
    return 0;
}
