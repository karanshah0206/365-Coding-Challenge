#pragma once

enum CellType { VACANT, WALL };

struct Cell {
	size_t fCol, fRow;
	CellType fCellType;

	Cell() = default;
	Cell(size_t aCol, size_t aRow, CellType aCellType = VACANT) :
		fCol(aCol), fRow(aRow), fCellType(aCellType) {}

	bool operator==(Cell aCell) { return fCol == aCell.fCol && fRow == aCell.fRow; }
};
