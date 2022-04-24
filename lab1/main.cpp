#include <iostream>
#include <vector>

using namespace std;

struct TPair {
    char Key[32];
    char* Value;
};

istream& operator>> (istream& input, TPair& pair) {
    for (int i = 0; i < 32; ++i) {
        input >> pair.Key[i];
    }
    input >> pair.Value;
    return input;
}

ostream& operator<< (ostream& output, TPair& pair) {
    for (int i = 0; i < 32; ++i) {
        output << pair.Key[i];
    }
    output << '\t' << pair.Value;
    return output;
}

void CountingSort(int i, vector<TPair>& v) {
    vector<TPair> res(v.size());
    int count[16] = { 0 };
    for (long long j = 0; j < v.size(); ++j) {
        if (v[j].Key[i] - '0' - 49 >= 0) {  // ASCII коды: 'a' = 97, '0' = 48
            ++count[v[j].Key[i] - '0' - 39];
        }
        else {
            ++count[v[j].Key[i] - '0'];
        }
    }
    for (int j = 1; j < 16; ++j) {
        count[j] += count[j - 1];
    }
    for (long long j = v.size() - 1; j >= 0; --j) {
        if (v[j].Key[i] - '0' - 49 >= 0) {
            --count[v[j].Key[i] - '0' - 39];
            res[count[v[j].Key[i] - '0' - 39]] = v[j];
        }
        else {
            --count[v[j].Key[i] - '0'];
            res[count[v[j].Key[i] - '0']] = v[j];
        }
    }
    v = move(res);
}

void RadixSort(vector<TPair>& v) {
    for (int i = 31; i >= 0; --i) {
        CountingSort(i, v);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    vector<TPair> v;
    TPair pair;
    pair.Value = (char*)malloc(sizeof(char) * 64);
    while (cin >> pair) {
        v.push_back(pair);
        pair.Value = (char*)malloc(sizeof(char) * 64);
    }
    if (v.size() == 0) {
        return 0;
    }
    RadixSort(v);
    for (int i = 0; i < v.size(); ++i) {
        cout << v[i] << '\n';
    }
    return 0;
}
