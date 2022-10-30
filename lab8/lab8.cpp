#include <iostream>
#include <vector>

using namespace std;

long long GetNextPos(short num, long long curPos, vector<short> &nums, bool reverseOrder = false) {
    if (nums.empty() || curPos < 0 || curPos >= nums.size()) {
        return 0;
    }
    if (!reverseOrder) {
        while (nums[curPos] != num && curPos + 1 < nums.size()) {
            ++curPos;
        }
    } 
    else {
        while (nums[curPos] != num && curPos - 1 >= 0) {
            --curPos;
        }
    }
    return curPos;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    const int MAX_NUM = 3;

    long long n;
    cin >> n;
    vector<short> nums(n);
    vector<long long> counts(MAX_NUM);
    for (long long i = 0; i < n; ++i) {
        cin >> nums[i];
        ++counts[nums[i] - 1];
    }

    long long swaps = 0;
    long long pos2_1 = GetNextPos(1, counts[0], nums);
    long long pos3_1 = GetNextPos(1, n - 1, nums, true);
    long long pos3_2 = GetNextPos(2, counts[0] + counts[1], nums);

    for (int i = 0; i < n; ++i) {
        if (i < counts[0] && nums[i] != 1) {
            // found number 2 or 3 which must be replaced by 1
            if (nums[i] == 2) {
                swap(nums[i], nums[pos2_1]);
                ++swaps;
                pos2_1 = GetNextPos(1, pos2_1, nums);
            } else {
                swap(nums[i], nums[pos3_1]);
                ++swaps;
                pos3_1 = GetNextPos(1, pos3_1, nums, true);
            }
        } 
        else if (counts[0] <= i && i < counts[0] + counts[1] && nums[i] != 2) {
            // found number 3 which must be replaced by 2
            // numbers 1 can't be here, they are already placed correctly
            swap(nums[i], nums[pos3_2]);
            ++swaps;
            pos3_2 = GetNextPos(2, pos3_2, nums);
        }
    }

    cout << swaps << "\n";
}