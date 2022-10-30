#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int eraseOverlapIntervals(vector<vector<int>>& intervals) {
    if (intervals.size() <= 1) {
        return 0;
    }
  
    sort(intervals.begin(), intervals.end(), 
        [](const vector<int>& a, const vector<int>& b) 
                    { return a[0] < b[0]; });
  
    int end = intervals[0][1];
    int res = 0;
    for (int i = 1; i < intervals.size(); i++) {
        if (intervals[i][0] < end) {
            res++;
            end = min(intervals[i][1], end);
        }
        else {
            end = intervals[i][1];
        }
    }
    return res;
}

int main() {
    vector<vector<int>> intervals = {{1,2},{2,3},{3,4},{1,3}};
    cout << eraseOverlapIntervals(intervals) << '\n';
}