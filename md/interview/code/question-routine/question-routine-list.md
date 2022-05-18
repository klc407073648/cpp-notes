# List Vs Vector

[[toc]]

* 数组由于是紧凑连续存储，可以随机访问， 通过索引快速找到对应元素，而且相对节约存储空间。

     * 但正因为连续存储， 内存空间必须一次性分配够， 所以说数组如果要扩容， 需要重新分配一块更大的空间，再把数据全部复制过去，时间复杂度 O(N)。

     * 数组中间进行插入或删除，每次必须搬移后面的所有数据以保持连续， 时间复杂度 O(N)。

* 链表因为元素不连续， 而是靠指针指向下一个元素的位置， 所以不存在数组的扩容问题。
  * 根据某个元素的前驱和后驱， 操作指针即可删除该元素或插入新元素， 时间复杂度 O(1)。
  * 存储空间不连续，无法根据索引算出对应元素的地址，索引不能随机访问；
  * 每个元素必须存储指向前后元素位置的指针， 会消耗相对更多的储存空间。

通常情况下，刷题中遇到的ListNode都是只有next指针，没有pre指针的结构。

List的解题思路，通常用双指针和递归方法。

# Two Pointers

两个指针指向List节点，不再是Index

两个指针必定<font color='red'>同向</font>而行。

需要明确：

1. 一个快一个慢，距离隔开多少
2. 两个指针的移动速度

# 实践应用

## List中找中间节点

```c++
public ListNode* linkedlistMiddleNode(ListNode* head){
	ListNode* i = head, j = head;
	
	while(j!=nullptr && j->next!=nullptr){
		i=i->next;
		j=j->next->next;
	}
	
	return i;
}
```

## List中找倒数第K个节点

```c++
public ListNode* linkedlistLastKthNode(ListNode* head, int k){
	ListNode* i = head, j = head;
	
	for(int c=0;c<k;c++){
		j=j->next;
	}
	
	while(j!=nullptr ){
		i=i->next;
		j=j->next;
	}
	
	return i;
}
```

# Recursion

Bottom up recursion 3 steps:

1.  Ask for subproblem result
2. Do something in current level of recursion
3. return result

## Reverse Linked List

```c++
ListNode *reverseList(ListNode *head)
{
    if(head == nullptr || head->next == nullptr)
    	return head;
    	
    ListNode * reversed_head = reverseList(head->next);
    head->next->next = head;
    head->next = nullptr;
    
    return reversed_head;
}


ListNode *reverseList(ListNode *head)
{
    ListNode *prev = nullptr;
    ListNode *curr = head;
    while (curr)
    {
        ListNode *next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}
```

