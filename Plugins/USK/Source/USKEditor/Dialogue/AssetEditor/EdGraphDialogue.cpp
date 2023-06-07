// Created by Henry Jooste

#include "EdGraphDialogue.h"
#include "USK/Dialogue/Dialogue.h"
#include "USK/Logger/Log.h"
#include "EdGraphNodeDialogueEntry.h"
#include "EdGraphNodeDialogueTransition.h"
#include "USK/Dialogue/DialogueTransition.h"

/**
 * @brief Rebuilds the dialogue graph.
 */
void UEdGraphDialogue::RebuildDialogue()
{
	USK_LOG_INFO("UDialogueEdGraph::RebuildDialogue has been called");
	UDialogue* Dialogue = GetDialogue();
	ClearDialogue();

	for (int i = 0; i < Nodes.Num(); ++i)
	{
		if (UEdGraphNodeDialogueEntry* EdNode = Cast<UEdGraphNodeDialogueEntry>(Nodes[i]))
		{
			if (EdNode->DialogueNode == nullptr)
			{
				continue;
			}

			UDialogueEntry* DialogueNode = EdNode->DialogueNode;
			NodeMap.Add(DialogueNode, EdNode);
			Dialogue->AllEntries.Add(DialogueNode);

			for (int PinIdx = 0; PinIdx < EdNode->Pins.Num(); ++PinIdx)
			{
				UEdGraphPin* Pin = EdNode->Pins[PinIdx];
				if (Pin->Direction != EGPD_Output)
				{
					continue;
				}

				for (int LinkToIdx = 0; LinkToIdx < Pin->LinkedTo.Num(); ++LinkToIdx)
				{
					UDialogueEntry* ChildNode = nullptr;
					if (const UEdGraphNodeDialogueEntry* EdNode_Child = Cast<UEdGraphNodeDialogueEntry>(
						Pin->LinkedTo[LinkToIdx]->GetOwningNode()))
					{
						ChildNode = EdNode_Child->DialogueNode;
					}
					else if (UEdGraphNodeDialogueTransition* EdNode_Edge = Cast<UEdGraphNodeDialogueTransition>(
						Pin->LinkedTo[LinkToIdx]->GetOwningNode()))
					{
						const UEdGraphNodeDialogueEntry* Child = EdNode_Edge->GetEndNode();;
						if (Child != nullptr)
						{
							ChildNode = Child->DialogueNode;
						}
					}

					if (ChildNode != nullptr)
					{
						DialogueNode->ChildrenNodes.Add(ChildNode);
						ChildNode->ParentNodes.Add(DialogueNode);
					}
					else
					{
						USK_LOG_ERROR("UEdGraphDialogue::RebuildDialogue can't find child node");
					}
				}
			}
		}
		else if (UEdGraphNodeDialogueTransition* EdgeNode = Cast<UEdGraphNodeDialogueTransition>(Nodes[i]))
		{
			const UEdGraphNodeDialogueEntry* StartNode = EdgeNode->GetStartNode();
			const UEdGraphNodeDialogueEntry* EndNode = EdgeNode->GetEndNode();
			UDialogueTransition* Edge = EdgeNode->DialogueEdge;

			if (StartNode == nullptr || EndNode == nullptr || Edge == nullptr)
			{
				USK_LOG_ERROR("UEdGraphDialogue::RebuildDialogue add edge failed.");
				continue;
			}

			EdgeMap.Add(Edge, EdgeNode);
			Edge->Rename(nullptr, Dialogue, REN_DontCreateRedirectors | REN_DoNotDirty);
			Edge->StartEntry = StartNode->DialogueNode;
			Edge->EndEntry = EndNode->DialogueNode;
			Edge->StartEntry->Edges.Add(Edge->EndEntry, Edge);
		}
	}

	for (int i = 0; i < Dialogue->AllEntries.Num(); ++i)
	{
		UDialogueEntry* Node = Dialogue->AllEntries[i];
		if (Node->ParentNodes.Num() == 0)
		{
			Dialogue->RootEntries.Add(Node);
			SortDialogue(Node);
		}

		Node->Dialogue = Dialogue;
		Node->Rename(nullptr, Dialogue, REN_DontCreateRedirectors | REN_DoNotDirty);
	}

	Dialogue->RootEntries.Sort([&](const UDialogueEntry& L, const UDialogueEntry& R)
	{
		const UEdGraphNodeDialogueEntry* EdNode_LNode = NodeMap[&L];
		const UEdGraphNodeDialogueEntry* EdNode_RNode = NodeMap[&R];
		return EdNode_LNode->NodePosX < EdNode_RNode->NodePosX;
	});
}

/**
 * @brief Returns the dialogue associated with this graph.
 * @return The dialogue associated with this graph.
 */
UDialogue* UEdGraphDialogue::GetDialogue() const
{
	return CastChecked<UDialogue>(GetOuter());
}

/**
 * @brief Overrides the Modify function of the parent class to mark the graph as dirty.
 * @param bAlwaysMarkDirty Whether to always mark the graph as dirty.
 * @return Whether the graph was modified.
 */
bool UEdGraphDialogue::Modify(bool bAlwaysMarkDirty)
{
	const bool Rtn = Super::Modify(bAlwaysMarkDirty);
	GetDialogue()->Modify();

	for (int32 i = 0; i < Nodes.Num(); ++i)
	{
		Nodes[i]->Modify();
	}

	return Rtn;
}

/**
 * @brief Clears the dialogue graph.
 */
void UEdGraphDialogue::ClearDialogue()
{
	UDialogue* Dialogue = GetDialogue();

	Dialogue->ClearDialogue();
	NodeMap.Reset();
	EdgeMap.Reset();

	for (int i = 0; i < Nodes.Num(); ++i)
	{
		if (const UEdGraphNodeDialogueEntry* EdNode = Cast<UEdGraphNodeDialogueEntry>(Nodes[i]))
		{
			UDialogueEntry* DialogueNode = EdNode->DialogueNode;
			if (DialogueNode)
			{
				DialogueNode->ParentNodes.Reset();
				DialogueNode->ChildrenNodes.Reset();
				DialogueNode->Edges.Reset();
			}
		}
	}
}

/**
 * @brief Sorts the dialogue graph starting from the root node.
 * @param RootNode The root node of the dialogue graph.
 */
void UEdGraphDialogue::SortDialogue(UDialogueEntry* RootNode)
{
	int Level = 0;
	TArray<UDialogueEntry*> CurrLevelNodes = { RootNode };
	TArray<UDialogueEntry*> NextLevelNodes;
	TSet<UDialogueEntry*> Visited;

	while (CurrLevelNodes.Num() != 0)
	{
		for (int i = 0; i < CurrLevelNodes.Num(); ++i)
		{
			UDialogueEntry* Node = CurrLevelNodes[i];
			Visited.Add(Node);

			auto Comp = [&](const UDialogueEntry& L, const UDialogueEntry& R)
			{
				const UEdGraphNodeDialogueEntry* EdNode_LNode = NodeMap[&L];
				const UEdGraphNodeDialogueEntry* EdNode_RNode = NodeMap[&R];
				return EdNode_LNode->NodePosX < EdNode_RNode->NodePosX;
			};

			Node->ChildrenNodes.Sort(Comp);
			Node->ParentNodes.Sort(Comp);

			for (int j = 0; j < Node->ChildrenNodes.Num(); ++j)
			{
				const UDialogueEntry* ChildNode = Node->ChildrenNodes[j];
				if (!Visited.Contains(ChildNode))
				{
					NextLevelNodes.Add(Node->ChildrenNodes[j]);
				}
			}
		}

		CurrLevelNodes = NextLevelNodes;
		NextLevelNodes.Reset();
		++Level;
	}
}

/**
 * @brief Overrides the PostEditUndo function of the parent class to update the graph after an undo operation.
 */
void UEdGraphDialogue::PostEditUndo()
{
	Super::PostEditUndo();
	NotifyGraphChanged();
}