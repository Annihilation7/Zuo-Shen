//
// Created by nofalling on 2020/5/18.
//

/*
 *  用一个栈实现另一个栈的排序，只允许申请一个栈空间。
 *  思路：
 *      1. 设输入栈为a，申请的栈为b，将a中元素的top向b中仍
 *      2. 如果从a出来的元素比b中的top大，就继续重复1, 2步骤。
 *      3. 如果没有比top大，将b中的元素开始向a中仍，直到b的top元素小于等于a出来的这个元素，将a出来的
 *          这个元素塞入b中，然后宠物1,2即可。
 *      a，b栈都用于存放元素，只不过用做存放时的时机不一样。
 */


#include <iostream>
#include <stack>
using namespace std;


void sortStackbyStack(stack<int>& input_stack){
    stack<int> helper = stack<int>();
    while(!input_stack.empty()){
        int pop_elem_a = input_stack.top();
        input_stack.pop();
        // helper不为空，并且helper头部元素要大于pop_elem_a
        while(!helper.empty() && helper.top() > pop_elem_a){
            int pop_elem_b = helper.top();
            helper.pop();
            input_stack.push(pop_elem_b);
        }
        helper.push(pop_elem_a);
    }
    input_stack = helper;
}


int main(){
    int input_nums[] = {5, 4, 3, 2, 1};
    int input_size = sizeof(input_nums) / sizeof(int);
    stack<int> test_stack = stack<int>();
    for(const auto& c: input_nums) {
        test_stack.push(c);  // 正好是反着的
    }

    sortStackbyStack(test_stack);

    int* new_res = new int[input_size];
    for(int i = 0; i < input_size; i++){
        int pop_elem = test_stack.top();
        test_stack.pop();
        new_res[i] = pop_elem;
    }
    // print
    cout << "top ";
    for(int i = 0; i < input_size; ++i)
        cout << new_res[i] << " ";
    cout << "bottom";
    delete [] new_res;
    return 0;
}