//
// Created by nofalling on 2020/5/15.
//

/*
 * 编写一个类，用两个栈实现一个队列
 * 实现思路很简单：因为压栈两次就又变成原顺序了，一个负责压栈(a)，一个负责出栈(b)
 * 注意两点：
 *  1. a中元素必须一次全部压入b，否则顺序会乱
 *  2. b中若有元素，则a中元素一定不能压入b
 */

#include <stack>
#include <iostream>

using namespace std;


class TwoStackQueue {
private:
    stack<int> stackPush;
    stack<int> stackPop;

    void dao() {
        if (stackPop.empty()) {
            while (!stackPush.empty()) {
                stackPop.push(stackPush.top());
                stackPush.pop();
            }
        }
    }

public:
    TwoStackQueue() {
        stackPush = stack<int>();
        stackPop = stack<int>();
    }

    int getSize() {
        return stackPop.size() + stackPush.size();
    }

    bool isEmpty() {
        return getSize() == 0;
    }

    void enqueue(int num) {
        stackPush.push(num);
        dao();
    }

    int head() {
        if (isEmpty()) {
            throw runtime_error("Empty queue.");
        }
        dao();
        return stackPop.top();
    }

    void dequeue() {
        if (isEmpty()) {
            throw runtime_error("Empty queue.");
        }
        dao();
        stackPop.pop();
    }
};


int main() {
    TwoStackQueue test = TwoStackQueue();
    int nums[] = {1, 2, 3, 4, 5};
    int *iter = begin(nums);
    while (iter != end(nums)) {
        test.enqueue(*iter);
        iter += 1;
    }
    while (!test.isEmpty()) {
        cout << test.head() << endl;
        test.dequeue();
    }
    // test corner case
    // test.dequeue();
    return 0;
}

