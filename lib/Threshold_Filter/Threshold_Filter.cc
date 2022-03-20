//
// Created by Tom Danvers on 16/03/2022.
// 2022 TeamSunride.
//

#include "DataNode.h"

#include "iostream"

using namespace std;

void DataNode::addChild(DownstreamFunctionPointer functionPointer) {
    downstreamFunctionPointers.push_back(functionPointer);
}

DataNode::DataNode() {
    downstreamFunctionPointers = Vector<DownstreamFunctionPointer>(pointerStorage, sizeof pointerStorage);
}

void DataNode::callChildren() {
    for (DownstreamFunctionPointer & element : downstreamFunctionPointers) {
        cout << element << endl;
    }
}
