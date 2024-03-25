// Created by Henry Jooste

#include "NodeVisitorCycleChecker.h"

/**
 * @brief Checks if there is a loop in the graph starting from StartNode and ending at EndNode.
 * @param StartNode The node to start the check from.
 * @param EndNode The node to end the check at.
 * @return True if there is a loop, false otherwise.
 */
bool FNodeVisitorCycleChecker::CheckForLoop(UEdGraphNode* StartNode, UEdGraphNode* EndNode)
{
	VisitedNodes.Add(StartNode);
	return TraverseNodes(EndNode);
}

/**
 * @brief Traverses the nodes in the graph starting from the specified node.
 * @param Node The node to start the traversal from.
 * @return True if the traversal is successful, false otherwise.
 */
bool FNodeVisitorCycleChecker::TraverseNodes(UEdGraphNode* Node)
{
	VisitedNodes.Add(Node);    
    for (UEdGraphPin* MyPin : Node->Pins)
    {
    	if (MyPin->Direction != EGPD_Output)
    	{
    		continue;
    	}

    	for (const UEdGraphPin* OtherPin : MyPin->LinkedTo)
    	{
    		UEdGraphNode* OtherNode = OtherPin->GetOwningNode();
    		if (VisitedNodes.Contains(OtherNode) ||
    			(!FinishedNodes.Contains(OtherNode) && !TraverseNodes(OtherNode)))
    		{
    			return false;
    		}
    	}
    }

    VisitedNodes.Remove(Node);
    FinishedNodes.Add(Node);
    return true;
}