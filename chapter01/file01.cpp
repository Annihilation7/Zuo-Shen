//
// Created by nofalling on 2020/5/15.
//

/*
 * 设计一个有gitMin功能的栈
 * 有两种设计思路：
 *  1. 一个普通栈，一个最小栈。每次push的时候，如果push的元素比最小栈的的栈顶元素要小，就往最小栈push这个元素，否则什么也不做。
 *  2. 一个普通栈，一个最小栈。每次push的时候，最小栈push栈顶元素和push元素的较小者，这种占用空间稍微大点。
 *  两种方法各有优缺点。第一种push稍费时，第二种弹出稍费时。
 */


#include <iostream>
#include <stack>

using namespace std;


class Mystack1 {
private:
    stack<int> stackData;
    stack<int> stackMin;

public:
    Mystack1() {
        stackData = stack<int>();
        stackMin = stack<int>();
    }

    void push(int num) {
        if (stackMin.empty())
            stackMin.push(num);
        else if (stackMin.top() > num)  // 只有小于才加元素
            stackMin.push(num);
        stackData.push(num);
    }

    int pop() {
        if (stackData.empty()) {
            throw runtime_error("Empty min stack.");
        }
        int pop_elem = stackData.top();
        stackData.pop();
        if (pop_elem == stackMin.top()) {  // 相等才出栈
            stackMin.pop();
        }
        return pop_elem;
    }

    int getMin() {
        if (stackData.empty()) {
            throw runtime_error("Empty min stack.");
        }
        return stackMin.top();
    }
};


class Mystack2 {
private:
    stack<int> stackData;
    stack<int> stackMin;

public:
    Mystack2() {
        stackData = stack<int>();
        stackMin = stack<int>();
    }

    void push(int num) {
        if (stackMin.empty())
            stackMin.push(num);
        else {
            int min_elem = min(num, stackMin.top());
            stackMin.push(min_elem);
        }
        stackData.push(num);
    }

    int pop() {
        if (stackData.empty()) {
            throw runtime_error("Empty min stack.");
        }
        int pop_elem = stackData.top();
        stackData.pop();
        stackMin.pop();
        return pop_elem;
    }

    int getMin() {
        if (stackData.empty()) {
            throw runtime_error("Empty min stack.");
        }
        return stackMin.top();
    }
};


int main() {
    Mystack1 stack1 = Mystack1();
    Mystack2 stack2 = Mystack2();
    int push_nums[] = {2, 4, 3, 0, 1, 5};
    for (int i = 0; i < sizeof(push_nums) / sizeof(int); ++i) {
        stack1.push(push_nums[i]);
        stack2.push(push_nums[i]);
    }
    for (int i = 0; i < 3; ++i) {
        stack1.pop();
        stack2.pop();
    }
    cout << stack1.getMin() << endl;
    cout << stack2.getMin() << endl;

    return 0;
}