//http://rflinux.blogspot.com/2011/10/red-black-trees.html

#pragma once

#include "global.h"

#define BLACK 0
#define RED 1
#define LEFT 0
#define RIGHT 1
#define IS_RED(n) ((n != nullptr) && (n->col == RED))
#define GET_DIRECTION(n, p) (p->heirs[RIGHT] == n)

const string kColors[] = { "чёрный", "красный" };
const string kDirections[] = { "левый", "правый" };

struct RbtNode {
	string* key;
	int val;
	unsigned char col;
	RbtNode* heirs[2];

	RbtNode(string k = string(), unsigned char c = RED, RbtNode* left = nullptr, RbtNode* right = nullptr, int v = 0);
	~RbtNode();
};

namespace RbtMapExceptions {
	struct RedViolation {
		RedViolation() {
			cout << "Red violation!\n";
		}
	};

	struct BlackViolation {
		BlackViolation() {
			cout << "Black violation!\n";
		}
	};

	struct BinaryTreeViolation {
		BinaryTreeViolation() {
			cout << "Binary tree violation!\n";
		}
	};

	struct RbtViolation {
		RbtViolation() {
			cout << "Red-black tree violation!\n";
		}
	};

	struct RootIsNull { };
}

class RbtMap {
	RbtNode* root = nullptr;
	int size = 0;

	int Assert(RbtNode* node);
	void PrintNode(ostream& os, RbtNode* node, RbtNode* parent);
	RbtNode* Search(RbtNode* node, string key, RbtNode*& parent);
	RbtNode* RotateSingle(RbtNode* node, bool dir);
	RbtNode* RotateDouble(RbtNode* node, bool dir);
	RbtNode* InsertRecur(RbtNode* node, string key);
	void ClearRecur(RbtNode*& node);
public:
	~RbtMap();
	int GetSize() const;
	void Print(ostream& os);
	void Save(string file = RBT_OUTPUT_TXT);
	void Load(string file = RBT_INPUT_TXT);
	RbtNode* Find(string key, RbtNode*& parent);
	bool Insert(string key);
	bool Remove(string key);
	void Clear();
};

