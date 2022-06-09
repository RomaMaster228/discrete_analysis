#include <map>
#include <sstream>
#include <vector>
#include <iostream>
#include <string>
#include <queue>

using namespace std;

typedef struct TBohrItem {
	map<string, TBohrItem*> path;
	TBohrItem* sufflink = nullptr;
	vector<int> success; // pattern id
} TBohrItem;


class TBohr {
public:
	TBohr();
	TBohrItem* Next(TBohrItem* item, string letter);
	TBohrItem* Move(TBohrItem* item, string letter);
	void Parse(const string&);
	void Push(const vector<string>&);
	void PushLetter(TBohrItem* node, string let, int patid);
	TBohrItem* FindSufflink(TBohrItem* child, TBohrItem* parent, const string letter);
	void Search(vector<string>&, vector<pair<int, int>>&);
	void Linkate();
	vector<int> pieceIndex;  // how many patterns in each line
private:
	TBohrItem* root;
	int patternSize;
	int pieces;

};


TBohr::TBohr() :
	patternSize(0), pieces(0) {
	root = new TBohrItem;
	root->sufflink = root;
}


TBohrItem* TBohr::Move(TBohrItem* item, string letter) {

	try {
		item = item->path.at(letter);
	}
	catch (out_of_range&) {

		if (item == root) {
			item = root;
		}
		else {
			item = Move(item->sufflink, letter);
		}
	}
	return item;
}


TBohrItem* TBohr::Next(TBohrItem* item, string letter) {

	if (!item) {
		return nullptr;
	}
	try {
		item = item->path.at(letter);
	}
	catch (out_of_range&) {
		item = nullptr;
	}
	return item;
}


void TBohr::Linkate() {

	TBohrItem* node, * child;
	queue<TBohrItem*> queue;
	queue.push(root);
	while (!queue.empty()) {
		node = queue.front();
		queue.pop();
		map<string, TBohrItem*>::iterator childPairIt;
		for (childPairIt = node->path.begin(); childPairIt != node->path.end(); ++childPairIt) {
			child = childPairIt->second;
			queue.push(child);
			child->sufflink = FindSufflink(child, node, childPairIt->first);


			child->success.insert(child->success.end(),
				child->sufflink->success.begin(),
				child->sufflink->success.end());


			child->success.shrink_to_fit();
		}
	}
}


TBohrItem* TBohr::FindSufflink(TBohrItem* child, TBohrItem* parent,
	const string letter) {
	TBohrItem* linkup = parent->sufflink, * check;
	while (true) {
		check = Next(linkup, letter);
		if (check) {
			return (check != child) ? check : root;
		}
		if (linkup == root) {
			return root;
		}
		linkup = linkup->sufflink;

	}
}


void TBohr::Push(const vector<string>& str) {
	TBohrItem* bohr = root, * next;
	for (size_t i = 0; i < str.size(); ++i) {
		next = Next(bohr, str[i]);
		if (!next) {
			next = new TBohrItem;
			next->sufflink = root;
			bohr->path.insert(pair<string, TBohrItem*>(str[i], next));
		}
		bohr = next;
	}
	bohr->success.push_back(pieces);
	pieces++;
}


void TBohr::Search(vector<string>& text, vector<pair<int, int>>& grid) {
	Linkate();
	int m = text.size();
	TBohrItem* node = root;
	int occurrence;
	int c;
	for (c = 0; c < m; ++c) {
		for (size_t i = 0; i < node->success.size(); ++i) {
			occurrence = c - pieceIndex[node->success[i]];
			cout << grid[occurrence].first << ", " << grid[occurrence].second << ", " << node->success[i] + 1 << '\n';
		}

		node = Move(node, text[c]);

	}

	for (size_t i = 0; i < node->success.size(); ++i) {
		occurrence = c - pieceIndex[node->success[i]];
		cout << grid[occurrence].first << ", " << grid[occurrence].second << ", " << node->success[i] + 1 << '\n';
	}
}


int main() {
	vector<pair<int, int>> grid;
	vector<string> input;
	vector<string> patterns;
	string line, word;
	string pattern;
	TBohr b;
	int index = 0;
	while (getline(cin, pattern) && !pattern.empty()) {
		stringstream lineStream(pattern);
		while (lineStream >> word) {
			for (unsigned int i = 0; i < word.length(); ++i) {
				word[i] = tolower(word[i]);
			}

			patterns.push_back(word);
			index++;
		}

		b.Push(patterns);
		b.pieceIndex.push_back(index);

		index = 0;
		pattern.clear();
		patterns.clear();

	}

	int lineIndex = 1, wordIndex = 1;

	while (getline(cin, line)) {
		stringstream lineStream(line);
		while (lineStream >> word) {	
			for (unsigned int i = 0; i < word.length(); ++i) {
				word[i] = tolower(word[i]);
			}
			input.push_back(word);
			grid.push_back(make_pair(lineIndex, wordIndex));
			wordIndex++;
		}

		wordIndex = 1;
		lineIndex++;

	}
	input.shrink_to_fit();
	grid.shrink_to_fit();
	b.Search(input, grid);
	return 0;
}
