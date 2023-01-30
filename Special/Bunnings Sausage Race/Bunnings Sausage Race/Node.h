#pragma once

#include "Cell.h"

#include <iostream>

struct Node {
	Cell fCoordinates;
	Node* fParent;
	std::string fPayload;

	Node(Cell aCoordinates, Node* aParent = nullptr, std::string aPayload = "") :
		fCoordinates(aCoordinates), fParent(aParent), fPayload(aPayload) {}

	bool operator==(Node aNode) { return fCoordinates == aNode.fCoordinates; }
};
