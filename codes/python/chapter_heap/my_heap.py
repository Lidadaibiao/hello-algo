"""
File: my_heap.py
Created Time: 2023-02-23
Author: Krahets (krahets@163.com)
"""

import sys, os.path as osp
sys.path.append(osp.dirname(osp.dirname(osp.abspath(__file__))))
from modules import *

class MaxHeap:
    """ 大顶堆 """
    def __init__(self, nums: list[int]):
        """ 构造方法 """
        # 将列表元素原封不动添加进堆
        self.max_heap = nums
        # 堆化除叶结点以外的其他所有结点
        for i in range(self.parent(self.size() - 1), -1, -1):
            self.sift_down(i)

    def left(self, i: int) -> int:
        """ 获取左子结点索引 """
        return 2 * i + 1

    def right(self, i: int) -> int:
        """ 获取右子结点索引 """
        return 2 * i + 2

    def parent(self, i: int) -> int:
        """ 获取父结点索引 """
        return (i - 1) // 2  # 向下整除

    def swap(self, i: int, j: int):
        """ 交换元素 """
        a, b = self.max_heap[i], self.max_heap[j]
        self.max_heap[i], self.max_heap[j] = b, a

    def size(self) -> int:
        """ 获取堆大小 """
        return len(self.max_heap)

    def is_empty(self) -> bool:
        """ 判断堆是否为空 """
        return self.size() == 0

    def peek(self) -> int:
        """ 访问堆顶元素 """
        return self.max_heap[0]

    def push(self, val: int):
        """ 元素入堆 """
        # 添加结点
        self.max_heap.append(val)
        # 从底至顶堆化
        self.sift_up(self.size() - 1)

    def sift_up(self, i: int):
        """ 从结点 i 开始，从底至顶堆化 """
        while True:
            # 获取结点 i 的父结点
            p = self.parent(i)
            # 当“越过根结点”或“结点无需修复”时，结束堆化
            if p < 0 or self.max_heap[i] <= self.max_heap[p]:
                break
            # 交换两结点
            self.swap(i, p)
            # 循环向上堆化
            i = p

    def pop(self) -> int:
        """ 元素出堆 """
        # 判空处理
        assert not self.is_empty()
        # 交换根结点与最右叶结点（即交换首元素与尾元素）
        self.swap(0, self.size() - 1)
        # 删除结点
        val = self.max_heap.pop()
        # 从顶至底堆化
        self.sift_down(0)
        # 返回堆顶元素
        return val

    def sift_down(self, i: int):
        """ 从结点 i 开始，从顶至底堆化 """
        while True:
            # 判断结点 i, l, r 中值最大的结点，记为 ma
            l, r, ma = self.left(i), self.right(i), i
            if l < self.size() and self.max_heap[l] > self.max_heap[ma]:
                ma = l
            if r < self.size() and self.max_heap[r] > self.max_heap[ma]:
                ma = r
            # 若结点 i 最大或索引 l, r 越界，则无需继续堆化，跳出
            if ma == i:
                break
            # 交换两结点
            self.swap(i, ma)
            # 循环向下堆化
            i = ma

    def print(self):
        """ 打印堆（二叉树） """
        print_heap(self.max_heap)


""" Driver Code """
if __name__ == "__main__":
    # 初始化大顶堆
    max_heap = MaxHeap([9, 8, 6, 6, 7, 5, 2, 1, 4, 3, 6, 2])
    print("\n输入列表并建堆后")
    max_heap.print()

    # 获取堆顶元素
    peek = max_heap.peek()
    print(f"\n堆顶元素为 {peek}")

    # 元素入堆
    val = 7
    max_heap.push(val)
    print(f"\n元素 {val} 入堆后")
    max_heap.print()

    # 堆顶元素出堆
    peek = max_heap.pop()
    print(f"\n堆顶元素 {peek} 出堆后")
    max_heap.print()

    # 获取堆大小
    size = max_heap.size()
    print(f"\n堆元素数量为 {size}")

    # 判断堆是否为空
    is_empty = max_heap.is_empty()
    print(f"\n堆是否为空 {is_empty}")
