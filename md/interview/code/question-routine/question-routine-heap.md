# 堆 Heap

> 堆（Heap）是一种<font color='red'>通过vector或deque为底层类实现的容器适配器</font>，以top()函数返回的值不同，可以分为大根堆和小根堆。

[[toc]]

![大根堆的二叉树表示](/_images/interview/code/question-routine/Heap/大根堆的二叉树表示.png)

**priority_queue:**

| Member functions | description                     |
| ---------------- | ------------------------------- |
| (constructor)    | Construct priority queue        |
| empty            | Test whether container is empty |
| size             | Return size                     |
| top              | Access top element              |
| push             | Insert element                  |
| emplace          | Construct and insert element    |
| pop              | Remove top element              |
| swap             | Swap contents                   |

声明如下:
```
std::priority_queue<int> max_heap;
std::priority_queue<int, vector<int>, greater<int>> small_heap;
```

## Online VS Offline Algorithm

Online Algorithm:

* 针对一组流数据，没有固定长度，可以随时根据需求scalable

Offline Algorithm:

* 针对一组固定长度数据，每次scale后需要重新计算

## 实践应用

### 例题 215. 数组中的第K个最大元素

 ![数组中的第K个最大元素](/_images/interview/code/question-routine/Heap/数组中的第K个最大元素.png)

以下为解题代码：

```

```


### 例题 23. 合并K个升序链表

 ![合并K个升序链表](/_images/interview/code/question-routine/Heap/合并K个升序链表.png)

以下为解题代码：
```

```

