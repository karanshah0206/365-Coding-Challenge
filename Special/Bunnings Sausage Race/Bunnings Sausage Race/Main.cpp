#include "Search.h"

#include <fstream>

int main(int argc, char* argv[]) {
	if (argc <= 2) {
		std::cout << "Required Arguments: <filename> <method>" << std::endl;
		std::cout << "Available Methods:" << std::endl << "\t- DFS" << std::endl << "\t- BFS" << std::endl;
		return 1;
	}

	if (argv[2] != (std::string)"DFS" && argv[2] != (std::string)"BFS") {
		std::cout << "Unknown Method: " << argv[2] << std::endl;
		std::cout << "Available Methods:" << std::endl << "\t- DFS" << std::endl << "\t- BFS" << std::endl;
		return 2;
	}

	std::ifstream datastream(argv[1]);

	if (!datastream.good()) {
		std::cout << "Could not read from file: " << argv[1] << std::endl;
		return 3;
	}

	Agent lAgent(datastream);
	GUI* lGUI = new GUI("Bunnings Sausage Race", lAgent);
	Search lSearch(argv[2], lAgent, lGUI);
	bool endReached = false;

	while (lAgent.fGoals.size() != 0 || !endReached) {
		Node* lFinalNode = lSearch.search();
		if (lFinalNode == nullptr) {
			std::cout << "No solution found.";
			break;
		}
		else {
			lSearch.tracePath(lFinalNode);
			lAgent.removeGoal(lFinalNode->fCoordinates);
			lFinalNode->fParent = nullptr;
			if (lAgent.endTest(lFinalNode)) endReached = true;
			lGUI->reset();
		}
		std::cout << std::endl;
	}

	while (lGUI->fRunning) lGUI->handleEvents();

	return 0;
}
