/**
 * File: linkedlist_deque.swift
 * Created Time: 2023-02-22
 * Author: nuomi1 (nuomi1@qq.com)
 */

/* 双向链表结点 */
class ListNode {
    var val: Int // 结点值
    var next: ListNode? // 后继结点引用（指针）
    var prev: ListNode? // 前驱结点引用（指针）

    init(val: Int) {
        self.val = val
    }
}

/* 基于双向链表实现的双向队列 */
class LinkedListDeque {
    private var front: ListNode? // 头结点 front
    private var rear: ListNode? // 尾结点 rear
    private var queSize: Int // 双向队列的长度

    init() {
        queSize = 0
    }

    /* 获取双向队列的长度 */
    func size() -> Int {
        queSize
    }

    /* 判断双向队列是否为空 */
    func isEmpty() -> Bool {
        size() == 0
    }

    /* 入队操作 */
    private func push(num: Int, isFront: Bool) {
        let node = ListNode(val: num)
        // 若链表为空，则令 front, rear 都指向 node
        if isEmpty() {
            front = node
            rear = node
        }
        // 队首入队操作
        else if isFront {
            // 将 node 添加至链表头部
            front?.prev = node
            node.next = front
            front = node // 更新头结点
        }
        // 队尾入队操作
        else {
            // 将 node 添加至链表尾部
            rear?.next = node
            node.prev = rear
            rear = node // 更新尾结点
        }
        queSize += 1 // 更新队列长度
    }

    /* 队首入队 */
    func pushFirst(num: Int) {
        push(num: num, isFront: true)
    }

    /* 队尾入队 */
    func pushLast(num: Int) {
        push(num: num, isFront: false)
    }

    /* 出队操作 */
    private func pop(isFront: Bool) -> Int {
        if isEmpty() {
            fatalError("双向队列为空")
        }
        let val: Int
        // 队首出队操作
        if isFront {
            val = front!.val // 暂存头结点值
            // 删除头结点
            let fNext = front?.next
            if fNext != nil {
                fNext?.prev = nil
                front?.next = nil
            }
            front = fNext // 更新头结点
        }
        // 队尾出队操作
        else {
            val = rear!.val // 暂存尾结点值
            // 删除尾结点
            let rPrev = rear?.prev
            if rPrev != nil {
                rPrev?.next = nil
                rear?.prev = nil
            }
            rear = rPrev // 更新尾结点
        }
        queSize -= 1 // 更新队列长度
        return val
    }

    /* 队首出队 */
    func popFirst() -> Int {
        pop(isFront: true)
    }

    /* 队尾出队 */
    func popLast() -> Int {
        pop(isFront: false)
    }

    /* 访问队首元素 */
    func peekFirst() -> Int? {
        isEmpty() ? nil : front?.val
    }

    /* 访问队尾元素 */
    func peekLast() -> Int? {
        isEmpty() ? nil : rear?.val
    }

    /* 返回数组用于打印 */
    func toArray() -> [Int] {
        var node = front
        var res = Array(repeating: 0, count: size())
        for i in res.indices {
            res[i] = node!.val
            node = node?.next
        }
        return res
    }
}

@main
enum _LinkedListDeque {
    /* Driver Code */
    static func main() {
        /* 初始化双向队列 */
        let deque = LinkedListDeque()
        deque.pushLast(num: 3)
        deque.pushLast(num: 2)
        deque.pushLast(num: 5)
        print("双向队列 deque = \(deque.toArray())")

        /* 访问元素 */
        let peekFirst = deque.peekFirst()
        print("队首元素 peekFirst = \(peekFirst!)")
        let peekLast = deque.peekLast()
        print("队尾元素 peekLast = \(peekLast!)")

        /* 元素入队 */
        deque.pushLast(num: 4)
        print("元素 4 队尾入队后 deque = \(deque.toArray())")
        deque.pushFirst(num: 1)
        print("元素 1 队首入队后 deque = \(deque.toArray())")

        /* 元素出队 */
        let popLast = deque.popLast()
        print("队尾出队元素 = \(popLast)，队尾出队后 deque = \(deque.toArray())")
        let popFirst = deque.popFirst()
        print("队首出队元素 = \(popFirst)，队首出队后 deque = \(deque.toArray())")

        /* 获取双向队列的长度 */
        let size = deque.size()
        print("双向队列长度 size = \(size)")

        /* 判断双向队列是否为空 */
        let isEmpty = deque.isEmpty()
        print("双向队列是否为空 = \(isEmpty)")
    }
}
