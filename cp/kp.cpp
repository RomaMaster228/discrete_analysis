#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

unordered_map<string, unsigned long long> dict = {{"a", 0}, {"b", 1}, {"c", 2}, {"d", 3}, {"e", 4}, {"f", 5}, {"g", 6}, {"h", 7}, {"i", 8}, {"j", 9}, {"k", 10}, {"l", 11}, {"m", 12}, {"n", 13}, {"o", 14}, {"p", 15}, {"q", 16}, {"r", 17}, {"s", 18}, {"t", 19}, {"u", 20}, {"v", 21}, {"w", 22}, {"x", 23}, {"y", 24}, {"z", 25}};
unordered_map<unsigned long long, string> reversed_dict = {{0, "a"}, {1, "b"}, {2, "c"}, {3, "d"}, {4, "e"}, {5, "f"}, {6, "g"}, {7, "h"}, {8, "i"}, {9, "j"}, {10, "k"}, {11, "l"}, {12, "m"}, {13, "n"}, {14, "o"}, {15, "p"}, {16, "q"}, {17, "r"}, {18, "s"}, {19, "t"}, {20, "u"}, {21, "v"}, {22, "w"}, {23, "x"}, {24, "y"}, {25, "z"}};


void LZW_encode(string s) {
   if (!s.size()) {
      cout << 26 << '\n';
      return;
   }

   unsigned long long index = 27;
   string prev_word = "";
   prev_word += s[0];
   bool flag = false;

   for (const auto& c: s) {

      if (!flag) {
         flag = true;
         continue;
      }
   
      if (dict.count(prev_word + c) == 0) {
         cout << dict[prev_word] << " ";
         dict[prev_word + c] = index++;
         prev_word = c;
      }
   
      else {
         prev_word += c;
      }
   }
   cout << dict[prev_word] << " "; 
   cout << 26 << " " << '\n';
}


void LZW_decode() {
   unsigned long long index = 27;
   unsigned long long cur_code, prev_code;
   cin >> prev_code;
   if (prev_code == 26) {
   	cout << '\n';
      return;
   }
   cout << reversed_dict[prev_code];
   while (cin >> cur_code) {

      if (cur_code == 26) {
         break;
      }

      string cur_word = "";
      if (reversed_dict.count(cur_code) == 0) {
         cur_word += reversed_dict[prev_code] + reversed_dict[prev_code][0];
      }
      else {
         cur_word += reversed_dict[cur_code];
      }
      cout << cur_word;

      reversed_dict[index++] = reversed_dict[prev_code] + cur_word[0];
      prev_code = cur_code;
   }
   cout << '\n';
}


int main() {
   string task, s;
   cin >> task;
   if (task == "compress") {
      cin >> s;
      LZW_encode(s);
   }
   else if (task == "decompress"){
      LZW_decode();
   }
   return 0;
}