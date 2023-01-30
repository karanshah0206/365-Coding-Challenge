#pragma once

#include "Cell.h"

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

struct Map {
	size_t fRowCount, fColCount, fVacantCount;
	std::vector<Cell> fGrid;

	Map() = default;
	Map(size_t aRowCount, size_t aColCount) :
		fRowCount(aRowCount), fColCount(aColCount) {
		for (size_t i = 0; i < fColCount; i++)
			for (size_t j = 0; j < fRowCount; j++)
				fGrid.push_back(Cell(i, j));
		fVacantCount = fGrid.size();
	}

	const Cell getCell(size_t aCol, size_t aRow) const {
		for (const Cell& cell : fGrid)
			if (cell.fCol == aCol && cell.fRow == aRow)
				return cell;
	}

	void addWalls(std::istream& datastream) {
		std::string s;
		datastream >> s;
		while (datastream >> s) {
			if (s[s.length() - 1] == ',') s = s.substr(0, s.length() - 1);
			std::stringstream ss(s.substr(1, s.length() - 2));
			std::getline(ss, s, ',');
			size_t row = std::stoi(s);
			std::getline(ss, s, ',');
			size_t col = std::stoi(s);
			row--; col--;
			for (Cell& cell : fGrid) {
				if (cell.fRow == row && cell.fCol == col) {
					cell.fCellType = WALL;
					fVacantCount--;
					break;
				}
			}
		}
	}

	static Map makeMap(std::istream& datastream) {
		std::string s;
		std::getline(datastream, s);
		std::stringstream ss(s.substr(12, s.length() - 13));
		std::getline(ss, s, ',');
		size_t rowCount = stoi(s);
		ss >> s;
		size_t colCount = stoi(s);
		return Map(rowCount, colCount);
	}
};
