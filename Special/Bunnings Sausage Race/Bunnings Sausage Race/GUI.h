#pragma once

#include "Agent.h"
#include "SDL.h";

struct GUI_Cell {
	SDL_Rect fRect;
	SDL_Color fColor;
};

struct GUI {
	SDL_Window* fWindow;
	SDL_Renderer* fRenderer;
	size_t fWidth, fHeight;
	float fCellWidth, fCellHeight;
	std::vector<GUI_Cell> fCells;
	Agent& fAgent;
	bool fRunning;

	GUI(const char* aTitle, Agent& aAgent) :
		fWidth(700), fHeight(700), fAgent(aAgent) {
		fWindow = SDL_CreateWindow(aTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, fWidth, fHeight, SDL_WINDOW_SHOWN);
		fRenderer = SDL_CreateRenderer(fWindow, -1, 0);
		SDL_SetRenderDrawColor(fRenderer, 0, 0, 0, 255);
		fRunning = true;
		fCellWidth = (float)fWidth / (float)fAgent.fMap.fColCount;
		fCellHeight = (float)fHeight / (float)fAgent.fMap.fRowCount;
		generateCells();
		addPath();
	}

	void generateCells() {
		for (const Cell& cell : fAgent.fMap.fGrid) {
			GUI_Cell gCell;
			gCell.fRect.y = cell.fCol * fCellHeight;
			gCell.fRect.x = cell.fRow * fCellWidth;
			gCell.fRect.w = fCellWidth - 1;
			gCell.fRect.h = fCellHeight - 1;
			if (fAgent.endTest(cell)) {
				gCell.fColor.r = 255;
				gCell.fColor.g = 0;
				gCell.fColor.b = 0;
			}
			else if (fAgent.goalTest(cell)) {
				gCell.fColor.r = 128;
				gCell.fColor.g = 0;
				gCell.fColor.b = 128;
			}
			else if (cell.fCellType == VACANT) {
				gCell.fColor.r = 255;
				gCell.fColor.g = 255;
				gCell.fColor.b = 255;
			}
			else {
				gCell.fColor.r = 128;
				gCell.fColor.g = 128;
				gCell.fColor.b = 128;
			}
			gCell.fColor.a = 255;
			fCells.push_back(gCell);
		}
	}

	void addPath() {
		for (GUI_Cell& cell : fCells) {
			if ((cell.fRect.y / (size_t)fCellHeight == fAgent.fState->fCoordinates.fCol) &&
				(cell.fRect.x / (size_t)fCellWidth == fAgent.fState->fCoordinates.fRow)) {
				cell.fColor.r = 0;
				cell.fColor.g = 255;
				cell.fColor.b = 0;
				break;
			}
		}
		render(100);
	}

	void addVisitedCell(Cell aCell) {
		if (!(aCell == fAgent.fState->fCoordinates) && !fAgent.endTest(aCell)) {
			for (GUI_Cell& cell : fCells) {
				if ((cell.fRect.x / (size_t)fCellWidth == aCell.fRow) &&
					(cell.fRect.y / (size_t)fCellHeight == aCell.fCol)) {
					if (cell.fColor.r == 255 && cell.fColor.g == 255 && cell.fColor.b == 0) return;
					cell.fColor.r = 255;
					cell.fColor.g = 255;
					cell.fColor.b = 0;
					break;
				}
			}
		}
		render(100);
	}

	void render(size_t aDelayPeriod) {
		SDL_RenderClear(fRenderer);
		drawCells();
		SDL_RenderPresent(fRenderer);
		if (aDelayPeriod > 0) SDL_Delay(aDelayPeriod);
	}

	void drawCells() {
		for (const GUI_Cell& cell : fCells) {
			SDL_SetRenderDrawColor(fRenderer, cell.fColor.r, cell.fColor.g, cell.fColor.b, cell.fColor.a);
			SDL_RenderFillRect(fRenderer, &cell.fRect);
			SDL_SetRenderDrawColor(fRenderer, 0, 0, 0, 255);
		}
	}

	void handleEvents() {
		SDL_Event event;
		SDL_PollEvent(&event);
		if (event.type == SDL_WINDOWEVENT)
			switch (event.window.event)
				case SDL_WINDOWEVENT_CLOSE: clean();
	}

	void reset() {
		SDL_Delay(500);
		for (GUI_Cell& cell : fCells)
			if (cell.fColor.r == 255 && cell.fColor.g == 255 && cell.fColor.b == 0)
				cell.fColor.b = 255;
		render(500);
	}

	void clean() {
		fRunning = false;
		SDL_DestroyWindow(fWindow);
		SDL_DestroyRenderer(fRenderer);
		SDL_Quit();
	}
};
