"""
File: binary_tree_dfs.py
Created Time: 2022-12-20
Author: a16su (lpluls001@gmail.com)
"""

import sys, os.path as osp
sys.path.append(osp.dirname(osp.dirname(osp.abspath(__file__))))
from modules import *

def pre_order(root: TreeNode | None) -> None:
    """ 前序遍历 """
    if root is None:
        return
    # 访问优先级：根结点 -> 左子树 -> 右子树
    res.append(root.val)
    pre_order(root=root.left)
    pre_order(root=root.right)

def in_order(root: TreeNode | None) -> None:
    """ 中序遍历 """
    if root is None:
        return
    # 访问优先级：左子树 -> 根结点 -> 右子树
    in_order(root=root.left)
    res.append(root.val)
    in_order(root=root.right)

def post_order(root: TreeNode | None) -> None:
    """ 后序遍历 """
    if root is None:
        return
    # 访问优先级：左子树 -> 右子树 -> 根结点
    post_order(root=root.left)
    post_order(root=root.right)
    res.append(root.val)


""" Driver Code """
if __name__ == "__main__":
    # 初始化二叉树
    # 这里借助了一个从数组直接生成二叉树的函数
    root = list_to_tree(arr=[1, 2, 3, 4, 5, 6, 7])
    print("\n初始化二叉树\n")
    print_tree(root)

    # 前序遍历
    res = []
    pre_order(root)
    print("\n前序遍历的结点打印序列 = ", res)
    assert res == [1, 2, 4, 5, 3, 6, 7]

    # 中序遍历
    res.clear()
    in_order(root)
    print("\n中序遍历的结点打印序列 = ", res)
    assert res == [4, 2, 5, 1, 6, 3, 7]

    # 后序遍历
    res.clear()
    post_order(root)
    print("\n后序遍历的结点打印序列 = ", res)
    assert res == [4, 5, 2, 6, 7, 3, 1]
