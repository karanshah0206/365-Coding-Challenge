#include <iostream>
#include <string>

using namespace std;

size_t levenstein(string s1, string s2) {
  if (s1 == s2) return 0;
  if (s1.size() == 0 || s2.size() == 0) return (s1.size() + s2.size());
  if (s1.length() == s2.length()) {
    size_t r = 0;
    for (const char& c1 : s1) for (const char& c2 : s2) if (c2 != c2) r++;
    return r;
  }
  if (s1.length() == 1) {
    size_t res = 0;
    for (const char& c : s2) if (s1[0] != c) res++;
    return res;
  }
  if (s2.length() == 1) {
    size_t res = 0;
    for (const char& c : s1) if (s2[0] != c) res++;
    return res;
  }
  else {
    size_t res = 0;
    if (s1 < s2)
      for (size_t i = 0; i < s1.size() - 1; i++)
        if (s1[i] != s2[i]) {
          if (s1[i+1] == s2[i+1]) res++;
          else {
            s1 = s1.substr(0, i) + s1.substr(i+1);
            res += levenstein(s1, s2);
            break;
          }
        }
    else
      for (size_t i = 0; i < s2.size() - 1; i++)
        if (s1[i] != s2[i]) {
          if (s1[i+1] == s2[i+1]) res++;
          else {
            s2 = s2.substr(0, i) + s2.substr(i+1);
            res += levenstein(s1, s2);
            break;
          }
        }
    return res;
  }
}

int main() {
  string s1, s2;
  cin >> s1 >> s2;
  int res = levenstein(s1, s2);
  if (res >= s1.size() && res >= s2.size()) res = -1;
  cout << res << endl;
  return 0;
}
