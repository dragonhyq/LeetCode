题目链接：https://leetcode.com/problems/min-stack/

Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.

push(x) -- Push element x onto stack.
pop() -- Removes the element on top of the stack.
top() -- Get the top element.
getMin() -- Retrieve the minimum element in the stack.

Example:

MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin();   --> Returns -3.
minStack.pop();
minStack.top();      --> Returns 0.
minStack.getMin();   --> Returns -2.

---

最小值，首先想到的是minheap。不过虽然取最小值比较容易，O(1)，但是如果需要pop的恰好是最小值，还需要把最小值从heap里面pop出去，就需要O(logN)。我们还是希望所有的操作都用O(1)完成。就不用heap。

那假设我们只用一个变量`v`存最小值，然后被push进来的新值`x < v`，那我们要不要更新`v = x`呢？不行。因为，如果之后`x`被pop出去了，那`v`以前的值也找不到了，因为被覆盖掉了。所以用一个变量来存最小值是不够的。我们需要一个有可能很长的空间。

那我们用一个栈`min_val`来存最小值。如果`x <= min_val.top()`，就把`x`入栈。pop的时候，如果pop的值等与`min_val.top()`，就同时pop`min_val`。

```cpp
class MinStack {
public:
    /** initialize your data structure here. */
    MinStack() {
        min_val.push(INT_MAX);        
    }
    
    void push(int x) {
        val.push(x);
        if (x <= min_val.top()) min_val.push(x);         
    }
    
    void pop() {
        int x = val.top(); 
        val.pop();
        if (x == min_val.top()) min_val.pop();    
    }
    
    int top() {
        return val.top();    
    }
    
    int getMin() {
        return min_val.top();
    }

private:
    stack<int> val;
    stack<int> min_val; 
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
```
其实上面那种做法是想保存最小值的时候稍微smart一些。如果不想，就直接naively存一个最小值的栈就好，就和数据的栈是平行的，那么代码为：

```cpp
class MinStack {
public:
    /** initialize your data structure here. */
    MinStack() {
        min_val.push(INT_MAX);        
    }
    
    void push(int x) {
        val.push(x);
        min_val.push(min(x, min_val.top()));         
    }
    
    void pop() {
        val.pop();
        min_val.pop();    
    }
    
    int top() {
        return val.top();    
    }
    
    int getMin() {
        return min_val.top();
    }

private:
    stack<int> val;
    stack<int> min_val; 
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
 ```

