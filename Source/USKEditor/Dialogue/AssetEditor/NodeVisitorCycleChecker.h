// Created by Henry Jooste

#pragma once

/**
 * @brief A class for checking cycles in a graph of UEdGraphNodes.
 */
class FNodeVisitorCycleChecker
{
public:
	/**
	 * @brief Checks if there is a loop in the graph starting from StartNode and ending at EndNode.
	 * @param StartNode The node to start the check from.
	 * @param EndNode The node to end the check at.
	 * @return True if there is a loop, false otherwise.
	 */
	bool CheckForLoop(UEdGraphNode* StartNode, UEdGraphNode* EndNode);

private:
	/**
	 * @brief Traverses the nodes in the graph starting from the specified node.
	 * @param Node The node to start the traversal from.
	 * @return True if the traversal is successful, false otherwise.
	 */
	bool TraverseNodes(UEdGraphNode* Node);

	/**
	 * @brief Set of visited nodes during the traversal.
	 */
	TSet<UEdGraphNode*> VisitedNodes;

	/**
	 * @brief Set of finished nodes during the traversal.
	 */
	TSet<UEdGraphNode*> FinishedNodes;
};