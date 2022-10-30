#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int FindMaxRectangleSquare(const vector<vector<char>>& matrix) {
    if (matrix.size() == 0) {
        return 0;
    }
    vector<vector<int>> h(matrix.size(), vector<int>(matrix[0].size()));
    for (int i = 0; i < matrix[0].size(); i++) {
        int count = 0;
        for (int j = 0; j < matrix.size(); j++){
            if (matrix[j][i] == '0') {
                count++;
            }
            else {
                count = 0;
            }
            h[j][i] = count;
        }
    }
    int max_area = 0;
    for (int i = 0; i < h.size(); i++) {
        stack<int> s;
        h[i].push_back(0);
        for (int j = 0; j < h[i].size(); j++) {
            while (!s.empty() && h[i][s.top()] >= h[i][j]) {
                int cur_idx = s.top();
                s.pop();
                int width = s.empty() ? j : j - s.top() - 1;
                max_area = max(max_area, h[i][cur_idx] * width);
            }
            s.push(j);
        }
    }
    return max_area;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<char>> v(n, vector<char>(m));
    for (int i = 0; i < n; i++) {
        string row;
        cin >> row;
        for (int j = 0; j < m; j++) {
            v[i][j] = row[j];
        }
    }
    cout << FindMaxRectangleSquare(v);
}
/*
4 4
1110
1100
1000
0000*/