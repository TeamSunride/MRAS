//
// Created by Alexander Becker on 2022-03-20
// 2022 TeamSunride.
//

#ifndef _NODE_H_
#define _NODE_H_

#include "measurement.h"
#include "common.h"

class Node {
public:
	Node();
    void pass_result_to(Node*);
    virtual void receive_measurement(Measurement) = 0;
protected:
    unsigned int registered_downstream_nodes;
    void propagate_result();
    Measurement input;
    Measurement output;
    Node *child_nodes[MAX_DOWNSTREAM_NODES];
};

#endif
