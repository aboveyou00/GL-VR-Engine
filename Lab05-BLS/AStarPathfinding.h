#pragma once

#include "PathingNodeObject.h"
typedef PathingNodeObject Node;

std::vector<Node*> *pathfind_astar(Node *fromNode, Node *toNode);
