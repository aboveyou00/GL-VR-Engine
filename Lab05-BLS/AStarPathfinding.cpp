#include "stdafx.h"
#include "AStarPathfinding.h"
#include "GameObject.h"

static const float infinity = std::numeric_limits<float>::infinity();

float actualDistance(Node *fromNode, Node *toNode);
float heuristicDistance(Node *fromNode, Node *toNode);

std::vector<Node*> *reconstructPath(std::map<Node*, Node*> &cameFrom, Node *current);

std::vector<Node*> *pathfind_astar(Node *fromNode, Node *toNode)
{
    std::vector<Node*> checked;
    std::vector<Node*> toCheck;
    toCheck.push_back(fromNode);

    std::map<Node*, Node*> cameFrom;

    std::map<Node*, float> gScores;
    gScores[fromNode] = 0;

    std::map<Node*, float> fScores;
    fScores[fromNode] = heuristicDistance(fromNode, toNode);

    while (toCheck.size() != 0)
    {
        float currentFScore = infinity;
        Node *current = nullptr;
        for (auto node : toCheck)
        {
            auto fScore = get_with_default(fScores, node, infinity);
            if (fScore < currentFScore)
            {
                currentFScore = fScore;
                current = node;
            }
        }

        if (current == toNode) return reconstructPath(cameFrom, current);

        collection_remove(toCheck, current);
        checked.push_back(current);
        for (auto conn : current->connections())
        {
            if (std::find(checked.begin(), checked.end(), conn) != checked.end()) continue;

            auto tentativeGScore = gScores[current] + actualDistance(current, conn);
            if (std::find(toCheck.begin(), toCheck.end(), conn) == toCheck.end()) toCheck.push_back(conn);
            else if (tentativeGScore >= get_with_default(gScores, conn, infinity)) continue;

            cameFrom[conn] = current;
            gScores[conn] = tentativeGScore;
            fScores[conn] = tentativeGScore + heuristicDistance(conn, toNode);
        }
    }

    return nullptr;
}

std::vector<Node*> *reconstructPath(std::map<Node*, Node*> &cameFrom, Node *current)
{
    auto completePath = new std::vector<Node*>{ current };
    while ((current = get_with_default(cameFrom, current, (Node*)nullptr)) != nullptr) completePath->push_back(current);
    return completePath;
}

float actualDistance(Node *fromNode, Node *toNode)
{
    return (fromNode->gameObject()->globalTransform()->position() - toNode->gameObject()->globalTransform()->position()).Length();
}
float heuristicDistance(Node *fromNode, Node *toNode)
{
    return actualDistance(fromNode, toNode);
}
