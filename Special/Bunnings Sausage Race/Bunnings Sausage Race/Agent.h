#pragma once

#include "Map.h"
#include "Node.h"

struct Agent {
	Node* fState;
	Cell fEnd;
	std::vector<Cell> fGoals;
	Map fMap;

	Agent(std::istream& datastream) {
		std::string s;
		std::stringstream ss;

		// map
		fMap = Map::makeMap(datastream);

		// start
		std::getline(datastream, s);
		ss = std::stringstream(s.substr(8, s.length() - 9));
		std::getline(ss, s, ',');
		size_t startRow = stoi(s);
		std::getline(ss, s, ',');
		size_t startCol = stoi(s);
		startRow--; startCol--;
		fState = new Node(Cell(startCol, startRow));

		// end
		std::getline(datastream, s);
		ss = std::stringstream(s.substr(6, s.length() - 7));
		std::getline(ss, s, ',');
		size_t endRow = stoi(s);
		std::getline(ss, s, ',');
		size_t endCol = stoi(s);
		endRow--; endCol--;
		fEnd = Cell(endCol, endRow);

		// goals
		std::getline(datastream, s);
		ss = std::stringstream(s.substr(7));
		while (ss >> s) {
			if (s != "|") {
				std::stringstream sss(s.substr(1, s.length() - 2));
				getline(sss, s, ',');
				size_t goalRow = stoi(s);
				getline(sss, s, ',');
				size_t goalCol = stoi(s);
				goalRow--; goalCol--;
				fGoals.push_back(Cell(goalCol, goalRow));
			}
		}

		// walls
		fMap.addWalls(datastream);
	}

	std::vector<Node> getAdjacentNodes(Node* aNode) const {
		std::vector<Node> adjacentNodes = {};

		if (aNode->fCoordinates.fRow > 0) {
			Cell cell = fMap.getCell(aNode->fCoordinates.fCol, aNode->fCoordinates.fRow - 1);
			if (cell.fCellType == VACANT) adjacentNodes.push_back(Node(cell, aNode, "west"));
		}

		if (aNode->fCoordinates.fRow < fMap.fRowCount - 1) {
			Cell cell = fMap.getCell(aNode->fCoordinates.fCol, aNode->fCoordinates.fRow + 1);
			if (cell.fCellType == VACANT) adjacentNodes.push_back(Node(cell, aNode, "east"));
		}

		if (aNode->fCoordinates.fCol < fMap.fColCount - 1) {
			Cell cell = fMap.getCell(aNode->fCoordinates.fCol + 1, aNode->fCoordinates.fRow);
			if (cell.fCellType == VACANT) adjacentNodes.push_back(Node(cell, aNode, "south"));
		}

		if (aNode->fCoordinates.fCol > 0) {
			Cell cell = fMap.getCell(aNode->fCoordinates.fCol - 1, aNode->fCoordinates.fRow);
			if (cell.fCellType == VACANT) adjacentNodes.push_back(Node(cell, aNode, "north"));
		}

		return adjacentNodes;
	}

	bool endTest(Cell aCell) const { return aCell == fEnd; }
	bool endTest(Node* aNode) const { return endTest(aNode->fCoordinates); }

	bool goalTest(Cell aCell) const {
		for (const Cell& cell : fGoals)
			if (aCell == cell)
				return true;
		return false;
	}
	bool goalTest(Node* aNode) const { return goalTest(aNode->fCoordinates); }
};
