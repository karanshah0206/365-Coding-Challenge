#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

typedef pair<size_t, size_t> coord;

enum cell { VACANT, WALL };
vector<vector<cell>> grid;
vector<coord> goals;
coord start, stop;

void processInput(istream& datastream) {
	string s;
	stringstream ss;

	// dimensions
	getline(datastream, s);
	ss = stringstream(s.substr(12, s.length() - 13));
	getline(ss, s, ',');
	vector<cell> row(stoi(s));
	ss >> s;
	for (size_t i = 0; i < stoi(s); i++) grid.push_back(row);

	// start
	getline(datastream, s);
	ss = stringstream(s.substr(8, s.length() - 9));
	getline(ss, s, ',');
	start.first = stoi(s);
	getline(ss, s, ',');
	start.second = stoi(s);

	// stop
	getline(datastream, s);
	ss = stringstream(s.substr(6, s.length() - 7));
	getline(ss, s, ',');
	stop.first = stoi(s);
	getline(ss, s, ',');
	stop.second = stoi(s);

	// goals
	getline(datastream, s);
	ss = stringstream(s.substr(7));
	while (ss >> s) {
		if (s != "|") {
			stringstream sss(s.substr(1, s.length() - 2));
			coord g;
			getline(sss, s, ',');
			g.first = stoi(s);
			getline(sss, s, ',');
			g.second = stoi(s);
			goals.push_back(g);
		}
	}

	// walls
	datastream >> s;
	while (datastream >> s) {
		if (s[s.length() - 1] == ',') s = s.substr(0, s.length() - 1);
		coord w;
		s = s.substr(1, s.length() - 2);
		ss = stringstream(s);
		getline(ss, s, ',');
		w.first = stoi(s);
		getline(ss, s, ',');
		w.second = stoi(s);
		grid[w.second - 1][w.first - 1] = WALL;
	}
}

int main(int argc, char* argv[]) {
	if (argc <= 1) {
		cout << "Missing Argument: filename" << endl;
		return 1;
	}

	ifstream datastream(argv[1]);

	if (!datastream.good()) {
		cout << "Could not read from file: " << argv[1] << endl;
		return 2;
	}

	processInput(datastream);

	return 0;
}
