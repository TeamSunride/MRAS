//
// Created By Alexander Becker 2022-03-20
// 2022 TeamSunride.
//
#include "node.h"

Node::Node()
    : input(Measurement(MeasurementType::Pressure, 0)),
      output(Measurement(MeasurementType::Pressure, 0)){};

void Node::pass_result_to(Node *dstr_node) {
  if (registered_downstream_nodes == MAX_DOWNSTREAM_NODES)
    return;
  child_nodes[registered_downstream_nodes] = dstr_node;
  registered_downstream_nodes++;
}

void Node::propagate_result() {
  for (unsigned int i = 0; i < registered_downstream_nodes; i++) {
    child_nodes[i]->receive_measurement(output);
  }
}
