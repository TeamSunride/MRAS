//
// Created by Tom Danvers on 16/03/2022.
// 2022 TeamSunride.
//

#include "DataNode.h"
#include "unity.h"
#include "iostream"

using namespace std;

bool functionACalled = false;
bool functionBCalled = false;

void functionA() {
    cout << "functionA was called" << endl;
    functionACalled = true;
}

void functionB() {
    cout << "functionB was called" << endl;
    functionBCalled = true;
}

void test_DataNode() {
    DataNode myNode;
    functionACalled = false; functionBCalled = false;
    myNode.addChild(functionA);
    myNode.addChild(functionB);
    myNode.callChildren();
    TEST_ASSERT_TRUE(functionACalled)
    TEST_ASSERT_TRUE(functionBCalled)
}

int main() {
    UNITY_BEGIN();

    cout << "starting test!" << endl;

    RUN_TEST(test_DataNode);

    UNITY_END();

    return 0;
}