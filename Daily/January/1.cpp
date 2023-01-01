#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

using namespace std;

unordered_map<int, size_t> getInput() {
  unordered_map<int, size_t> counter;
  string s;
  cin >> s; cin >> s; cin >> s;
  s = s.substr(1, s.length() - 2);
  stringstream ss(s);
  while(getline(ss, s, ',')) counter[stoi(s)]++;
  return counter;
}

int getMode(const unordered_map<int, size_t>& counter) {
  int res;
  size_t max = 0;
  for (const auto& c : counter)
    if (c.second > max) { res = c.first; max = c.second; }
  return res;
}

int main() {
  cout << getMode(getInput()) << endl;
  return 0;
}
