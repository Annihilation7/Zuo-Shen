//
// Created by nofalling on 2020/5/18.
//

/*
 * 实现猫狗队列
 * 两个要点：
 *  1. 增加时间戳
 *  2. 两个队列，一个只存猫，一个只存狗
 *  出队列可以比较两个队列队首的时间戳，来决定到底出哪个宠物就可以了
 */

#include <iostream>
#include <string>
#include <queue>
#include <cassert>
#include <vector>

using namespace std;


class Pet {
private:
    string type;

public:
    Pet() {
        type = "";
    }

    Pet(const string &cur_type) {
        assert(cur_type == "dog" || cur_type == "cat");
        type = cur_type;
    }

    string getPetType() {
        return type;
    }
};


// 包一层Dog以及Cat类，使之具有时间戳的功能
class MyPet {
private:
    Pet pet;  // 只声明就可以了
    long count;

public:
    MyPet(const string &input_pet_kind, long input_count) {
        pet = Pet(input_pet_kind);
        count = input_count;
    }

    // 获取pet
    Pet getPet() {
        return pet;
    }

    // 获取type
    string getPetType() {
        return pet.getPetType();
    }

    // 获取时间戳
    long getPetCount() {
        return count;
    }
};


// 构造猫狗队列
class DogCatQueue {
private:
    queue<MyPet> dog_queue;
    queue<MyPet> cat_queue;
    long count;

public:
    DogCatQueue() {
        dog_queue = queue<MyPet>();
        cat_queue = queue<MyPet>();
        count = 0;  // 最开始时间戳为0
    }

    // 判断队列是否为空
    bool isEmpty() {
        return dog_queue.empty() && cat_queue.empty();
    }

    // 拿到猫狗队列的size
    int getSize() {
        return dog_queue.size() + cat_queue.size();
    }

    // 添加一只猫或者一只狗
    void add(const string &input_type_name) {
        if (input_type_name == "dog")
            dog_queue.push(MyPet("dog", ++count));
        else
            cat_queue.push(MyPet("cat", ++count));
    }

    // 将队列中所有的实例按照进队列的先后顺序依次弹出
    // 类似merge操作
    vector<string> poolAll() {
        vector<string> res;
        while (!dog_queue.empty() && !cat_queue.empty()) {
            MyPet dog_front = dog_queue.front();
            MyPet cat_front = cat_queue.front();
            if (dog_front.getPetCount() <= cat_front.getPetCount()) {  // 严格来说不会有等于的情况
                res.push_back(dog_front.getPetType());
                dog_queue.pop();
            } else {
                res.push_back(cat_front.getPetType());
                cat_queue.pop();
            }
        }
        while (!dog_queue.empty()) {
            res.push_back(dog_queue.front().getPetType());
            dog_queue.pop();
        }
        while (!cat_queue.empty()) {
            res.push_back(cat_queue.front().getPetType());
            cat_queue.pop();
        }

        return res;
    }

    // 弹出队列中的一个dog元素
    string poolDog() {
        assert(!dog_queue.empty());
        MyPet dog_elem = dog_queue.front();
        dog_queue.pop();
        return dog_elem.getPetType();
    }

    // 弹出队列中的一个cat元素
    string poolCat() {
        assert(!cat_queue.empty());
        MyPet cat_elem = cat_queue.front();
        cat_queue.pop();
        return cat_elem.getPetType();
    }
};


int main() {
    vector<string> input_strings = {"dog", "dog", "cat", "dog", "cat", "cat", "cat"};
    DogCatQueue test = DogCatQueue();
    for (const auto &c: input_strings)
        test.add(c);

    // pollAll
    vector<string> res = test.poolAll();
    for (const auto &c: res)
        cout << c << " ";
    return 0;
}