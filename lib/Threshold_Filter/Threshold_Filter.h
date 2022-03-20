//
// Created by Tom Danvers on 16/03/2022.
// 2022 TeamSunride.
//

#ifndef DATANODE_H
#define DATANODE_H

#include <cstdint>
#include "Vector.h"

typedef void (*DownstreamFunctionPointer)();

#define MAX_DOWNSTREAM_FUNCTIONS 5

class DataNode {
public:
    /**
     *
     * @param functionPointer
     */
    void addChild(DownstreamFunctionPointer functionPointer);
    void callChildren(); // should probably be protected

    DataNode();
private:
    DownstreamFunctionPointer pointerStorage[MAX_DOWNSTREAM_FUNCTIONS] = {};
    Vector<DownstreamFunctionPointer> downstreamFunctionPointers;
};


#endif //DATANODE_H
