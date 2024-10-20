#include <deque>
#include <string>
#include <vector>
#include <cassert>

template <class T>
class Stack
{
private:
    std::vector<T> elems; // elements
public:
    void push(T const &elem); // push element
    void pop();               // pop element
    T const &top() const;     // return top element
    bool empty() const
    { // return whether the stack is empty
        return elems.empty();
    }
};
template <class T>
void Stack<T>::push(T const &elem)
{
    elems.push_back(elem); // append copy of passed elem
}
template <class T>
void Stack<T>::pop()
{
    assert(!elems.empty());
    elems.pop_back(); // remove last element
}
template <class T>
T const &Stack<T>::top() const
{
    assert(!elems.empty());
    return elems.back(); // return copy of last element
}

// 特例化
template <>
class Stack<std::string>
{
private:
    std::deque<std::string> elems; // elements
public:
    void push(std::string const &); // push element
    void pop();                     // pop element
    std::string const &top() const; // return top element
    bool empty() const
    { // return whether the stack is empty
        return elems.empty();
    }
};
void Stack<std::string>::push(std::string const &elem)
{
    elems.push_back(elem); // append copy of passed elem
}
void Stack<std::string>::pop()
{
    assert(!elems.empty());
    elems.pop_back(); // remove last element
}
std::string const &Stack<std::string>::top() const
{
    assert(!elems.empty());
    return elems.back(); // return copy of last element
}

//部分特例化
// partial specialization of class Stack<> for pointers:
template <class T>
class Stack<T *>
{
private:
    std::vector<T *> elems; // elements
public:
    void push(T *); // push element
    T *pop();       // pop element
    T *top() const; // return top element
    bool empty() const
    {
        return elems.empty(); // return whether the stack is empty
    }
};
template <class T>
void Stack<T *>::push(T *elem)
{
    elems.push_back(elem); // append copy of passed elem
}
template <class T>
T *Stack<T *>::pop()
{
    assert(!elems.empty());
    T *p = elems.back();
    elems.pop_back(); // remove last element
    return p;         // and return it (unlike in the general case)
}
template <class T>
T *Stack<T *>::top() const
{
    assert(!elems.empty());
    return elems.back(); // return copy of last element
}
