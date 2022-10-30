#include <iostream>
#include <unordered_map>


class TNode {
public:
    TNode(int left = 0, int right = 0) : start(left), end(right) {}

    std::unordered_map<char, TNode*> edges;
    TNode* suffixLink = nullptr;

    int start;
    int end;

    char lexMinEdge = 0; // edge with lexicographically minimal char
};


class TSuffixTree {
public:
    std::string text;
    int endPos = -1; // variable for end position

    TNode* root = new TNode();

    // a point where we will start the next phase
    TNode* activeNode = root; // start node
    int activeEdge = -1; // id of the edge
    int activeLength = 0; // how far should we go along the edge

    int remaining = 0; // amount of suffixed we should add


    TSuffixTree(std::string& str);
    ~TSuffixTree();

    void Extend(int phase);

    std::string FindlexMinString();

    void Delete(TNode* node);

};


TSuffixTree::TSuffixTree(std::string& str) {
    // adding a sentinel
    text = str + '$';

    for (int i = 0; i < text.length(); ++i) {
        Extend(i);
    }
}

void TSuffixTree::Extend(int phase) {
    TNode* lastCreatedInternalNode = nullptr; // for creating suffix links

    ++remaining; // at every phase we should add one more suffix
    ++endPos; // incrementing end pos

    while (remaining > 0) {
        if (activeLength == 0) {
            // searching for current character from active edge
            activeEdge = phase;
        }

        if (!activeNode->edges[text[activeEdge]]) {
            // there is no edge starting with current char -> creating it
            activeNode->edges[text[activeEdge]] = new TNode(phase, -1); // -1 is endPos

            // updating LexMin edge for active node
            if ((text[phase] < activeNode->lexMinEdge && text[phase] != '$') || activeNode->lexMinEdge == 0) {
                activeNode->lexMinEdge = text[phase];
            }

            // as we've created an internal node, we should update a suffix link
            if (lastCreatedInternalNode != nullptr) {
                lastCreatedInternalNode->suffixLink = activeNode;
            }
            lastCreatedInternalNode = activeNode;
        }
        else {
            // there is an edge starting with current char -> walking along it
            TNode* nextNode = activeNode->edges[text[activeEdge]];
            int curEnd = nextNode->end == -1 ? endPos : nextNode->end;
            int edgeLength = curEnd - nextNode->start + 1;

            if (activeLength >= edgeLength) {
                // we should change active node
                activeEdge += edgeLength;
                activeLength -= edgeLength;
                activeNode = nextNode;
                continue;
            }

            if (text[nextNode->start + activeLength] == text[phase]) {
                // there is already a suffix in the tree -> updating and stopping
                ++activeLength;
                // we could have created an internal node earlier -> updating suffix links
                if (lastCreatedInternalNode != nullptr) {
                    lastCreatedInternalNode->suffixLink = activeNode;
                }
                break;
            }

            // there are no suffix in the tree -> creating new internal node
            TNode* internalNode = new TNode(nextNode->start, nextNode->start + activeLength - 1);
            TNode* leafNode = new TNode(phase, -1);

            activeNode->edges[text[activeEdge]] = internalNode;
            nextNode->start += activeLength;
            internalNode->edges[text[phase]] = leafNode;
            internalNode->edges[text[nextNode->start]] = nextNode;

            // finding a LexMin edge for new internal node
            if (text[nextNode->start] < text[leafNode->start]) {
                if (text[nextNode->start != '$']) {
                    internalNode->lexMinEdge = text[nextNode->start];
                }
                else {
                    internalNode->lexMinEdge = text[leafNode->start];
                }
            }
            else {
                if (text[leafNode->start] != '$') {
                    internalNode->lexMinEdge = text[leafNode->start];
                }
                else {
                    internalNode->lexMinEdge = text[nextNode->start];
                }
            }

            // as we've created an internal node, we should add a suffix link
            if (lastCreatedInternalNode != nullptr) {
                lastCreatedInternalNode->suffixLink = internalNode;
            }
            lastCreatedInternalNode = internalNode;
        }
        --remaining; // we've added 1 suffix

        if (activeNode != root) {
            activeNode = activeNode->suffixLink;
        }
        else if (activeNode == root && activeLength > 0) {
            --activeLength;
            ++activeEdge;
        }
    }
}

std::string TSuffixTree::FindlexMinString() {
    std::string lexMinString;
    TNode* curNode = root;

    while (lexMinString.length() < (text.length() - 1) / 2) {
        curNode = curNode->edges[curNode->lexMinEdge];
        int curEnd = curNode->end == -1 ? endPos : curNode->end;

        for (int i = curNode->start; i <= curEnd; ++i) {
            lexMinString += text[i];
            if (lexMinString.length() == (text.length() - 1) / 2) {
                break;
            }
        }
    }
    return lexMinString;
}

TSuffixTree::~TSuffixTree() {
    Delete(root);
}

void TSuffixTree::Delete(TNode* node) {
    for (auto child : node->edges) {
        Delete(child.second);
    }

    delete node;
}


int main() {
    std::string str;
    std::cin >> str;

    // double the string
    str += str;
    TSuffixTree tree(str);
    std::cout << tree.FindlexMinString() << "\n";
}
