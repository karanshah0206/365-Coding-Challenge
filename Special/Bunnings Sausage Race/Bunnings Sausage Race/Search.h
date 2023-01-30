#pragma once

#include "GUI.h"

struct Search {
	Agent& fAgent;
	std::string fMethod;
	std::vector<Node> fTree, fFrontier;
	GUI* fGUI;

	Search(std::string aMethod, Agent& aAgent, GUI* aGUI) :
		fMethod(aMethod), fAgent(aAgent), fGUI(aGUI) {}

	bool isUnexplored(Node aNode) {
		for (Node& node : fTree) if (node == aNode) return false;
		for (Node& node : fFrontier) if (node == aNode) return false;
		return true;
	}

	Node* search() {
		fTree = {};
		fFrontier = {};
		fTree.reserve(50000);
		if (fMethod == "DFS") return dfs();
		if (fMethod == "BFS") return bfs();
		return nullptr;
	}

	void tracePath(Node* aNode) const {
		if (aNode->fParent != nullptr) tracePath(aNode->fParent);
		if (aNode->fPayload != "") std::cout << aNode->fPayload << "; ";
		fAgent.fState = aNode;
		fGUI->addPath();
	}

	Node* dfs() {
		if (fAgent.endTest(fAgent.fState)) {
			fTree.push_back(*fAgent.fState);
			return &fTree[0];
		}

		fFrontier.push_back(*fAgent.fState);
		while (fFrontier.size() > 0) {
			fTree.push_back(fFrontier[0]);
			fFrontier.erase(fFrontier.begin());
			Node* current = &fTree[fTree.size() - 1];
			fGUI->addVisitedCell(current->fCoordinates);
			std::vector<Node> children = fAgent.getAdjacentNodes(current);
			for (size_t i = 0; i < children.size(); i++) {
				if (fAgent.endTest(&children[i])) {
					fTree.push_back(children[i]);
					return &fTree[fTree.size() - 1];
				}
				if (isUnexplored(children[i])) fFrontier.insert(fFrontier.begin(), children[i]);
			}
		}

		return nullptr;
	}

	Node* bfs() {
		if (fAgent.endTest(fAgent.fState)) {
			fTree.push_back(*fAgent.fState);
			return &fTree[0];
		}

		fFrontier.push_back(*fAgent.fState);
		while (fFrontier.size() > 0) {
			fTree.push_back(fFrontier[0]);
			fFrontier.erase(fFrontier.begin());
			Node* current = &fTree[fTree.size() - 1];
			fGUI->addVisitedCell(current->fCoordinates);
			std::vector<Node> children = fAgent.getAdjacentNodes(current);
			for (int i = children.size() - 1; i >= 0; i--) {
				if (isUnexplored(children[i])) {
					if (fAgent.endTest(&children[i])) {
						fTree.push_back(children[i]);
						return &fTree[fTree.size() - 1];
					}
					fFrontier.push_back(children[i]);
				}
			}
		}

		return nullptr;
	}
};
