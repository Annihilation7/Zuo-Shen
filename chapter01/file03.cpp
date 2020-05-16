//
// Created by nofalling on 2020/5/17.
//


/*
 * 如何仅用递归函数和栈操作逆序一个栈
 * 思路：
 *   - 两个递归函数实现，一个递归函数用于将栈底元素抽出来，另一个递归函数用于向底层推进即可。
 */


#include <iostream>
#include <stack>
#include <vector>

using namespace std;


int getBottom(stack<int> &input_stack) {
    // 拿到当前栈的栈底元素
    int top_elem = input_stack.top();
    input_stack.pop();
    if (input_stack.empty()) {
        return top_elem;
    }

    int bot_elem = getBottom(input_stack);
    input_stack.push(top_elem);  // 别忘了再扔回去，要不栈空了！
    return bot_elem;
}

void reverseStack(stack<int> &input_stack) {
    // 向底层推进
    if (input_stack.empty()) {
        return;
    }

    int bot_elem = getBottom(input_stack);
    reverseStack(input_stack);
    input_stack.push(bot_elem);
}


int main() {
    stack<int> test_stack = stack<int>();
    int elems[] = {1, 2, 3, 4};
    for (const auto &c: elems) {
        test_stack.push(c);
    }
    reverseStack(test_stack);
    vector<int> res;
    while (!test_stack.empty()) {
        int pop_elem = test_stack.top();
        res.push_back(pop_elem);
        test_stack.pop();
    }
    for (const auto &c: res)
        cout << c << " ";
    return 0;
}
