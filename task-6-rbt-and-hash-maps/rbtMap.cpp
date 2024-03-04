#include "rbtMap.h"

using namespace RbtMapExceptions;
	
RbtNode::RbtNode(string k, unsigned char c, RbtNode* left, RbtNode* right, int v) {
	key = new string(k);
	val = v;
	col = c;
	heirs[LEFT] = left;
	heirs[RIGHT] = right;
}

RbtNode::~RbtNode() {
	delete key;
}

RbtMap::~RbtMap() {
	Clear();
}

int RbtMap::Assert(RbtNode* node) {
	if (node == nullptr) {
		return 1;
	}

	int lh, rh;
	RbtNode* ln = node->heirs[LEFT];
	RbtNode* rn = node->heirs[RIGHT];

	if (IS_RED(node)) {
		if (IS_RED(ln) || IS_RED(rn)) {
			/*throw*/ RedViolation();
			return 0;
		}
	}

	lh = Assert(ln);
	rh = Assert(rn);

	if ((ln != nullptr && *(ln->key) >= *(node->key)) || (rn != nullptr && *(rn->key) <= *(node->key))) {
		/*throw*/ BinaryTreeViolation();
		return 0;
	}

	if (lh != 0 && rh != 0 && lh != rh) {
		/*throw*/ BlackViolation();
		return 0;
	}

	if (lh != 0 && rh != 0) {
		return IS_RED(node) ? lh : lh + 1;
	}
	else {
		/*throw*/ RbtViolation();
		return 0;
	}
}

RbtNode* RbtMap::RotateSingle(RbtNode* node, bool dir) {
	RbtNode* save = node->heirs[!dir];

	node->heirs[!dir] = save->heirs[dir];
	save->heirs[dir] = node;

	node->col = RED;
	save->col = BLACK;
	
	return save;
}

RbtNode* RbtMap::RotateDouble(RbtNode* node, bool dir) {
	node->heirs[!dir] = RotateSingle(node->heirs[!dir], !dir);
	return RotateSingle(node, dir);
}

void RbtMap::PrintNode(ostream& os, RbtNode* node, RbtNode* parent) {
	if (node == nullptr) {
		return;
	}

	os << setw(15) << *(node->key) <<  setw(3) << node->val <<  " -- ";

	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (node->col == RED) {
		SetConsoleTextAttribute(console, TEXT_COLOR_RED);
	}
	else {
		SetConsoleTextAttribute(console, TEXT_COLOR_GREEN);
	}
	os << setw(7) << kColors[node->col];
	SetConsoleTextAttribute(console, TEXT_COLOR_DEFAULT);

	if (node != root) {
		os << " " << setw(6) << kDirections[GET_DIRECTION(node, parent)] << " потомок " << *(parent->key);
	}
	else {
		os << " корень дерева";
	}
	os << '\n';

	PrintNode(os, node->heirs[LEFT], node);
	PrintNode(os, node->heirs[RIGHT], node);
}

int RbtMap::GetSize() const {
	return size;
}

void RbtMap::Print(ostream& os) {
	PrintNode(os, root, nullptr);
	Assert(root);
}

void RbtMap::Save(string file) {
	std::ofstream ofs(file);
	if (ofs.is_open()) {
		Print(ofs);
		ofs.close();
	}
}

void RbtMap::Load(string file) {
	std::ifstream ifs(file);
	if (ifs.is_open()) {
		string s;
		boost::basic_regex<char, boost::cpp_regex_traits<char>> expr;
		expr.imbue(std::locale{"russian"});
		expr = RX_WORDS_RU;

		while (ifs >> s) {
			if (boost::regex_match(s, expr)) {
				Insert(s);
			}
		}

		ifs.close();
	}
}

RbtNode* RbtMap::Search(RbtNode* node, string key, RbtNode*& parent) {
	if ((node == nullptr) || (*(node->key) == key)) {
		return node;
	}

	int dir = *(node->key) < key;
	parent = node;
	return Search(node->heirs[dir], key, parent);
}

RbtNode* RbtMap::Find(string key, RbtNode*& parent) {
	if (nullptr == root) {
		throw RootIsNull();
		//return;
	}

	transform(key.begin(), key.end(), key.begin(), tolower);
	return Search(root, key, parent);
}

RbtNode* RbtMap::InsertRecur(RbtNode* node, string key) {
	if (node == nullptr) {
		node = new RbtNode(key);
		return node;
	}

	bool dir = (*(node->key)) < key;
	node->heirs[dir] = InsertRecur(node->heirs[dir], key);

	if (IS_RED(node->heirs[dir])) {
		if (IS_RED(node->heirs[!dir])) {
			node->col = RED;
			node->heirs[LEFT]->col = node->heirs[RIGHT]->col = BLACK;
		}
		else {
			if (IS_RED(node->heirs[dir]->heirs[dir])) {
				node = RotateSingle(node, !dir);
			}
			else if (IS_RED(node->heirs[dir]->heirs[!dir])) {
				node = RotateDouble(node, !dir);
			}
		}
	}

	return node;
}

bool RbtMap::Insert(string key) {
	transform(key.begin(), key.end(), key.begin(), tolower);

	if (root == nullptr) {
		root = new RbtNode(key, BLACK);
		size++;
		return true;
	}

	RbtNode *parent = nullptr, *found = Find(key, parent);
	if (found) {
		(found->val)++;
		return false;
	}

	root = InsertRecur(root, key);
	root->col = BLACK;
	size++;
	return true;
}

bool RbtMap::Remove(string key) {
	if (root == nullptr) {
		return false;
	}

	transform(key.begin(), key.end(), key.begin(), tolower);

	RbtNode falseRoot;
	RbtNode *it = &falseRoot, *parent = nullptr, *gParent = nullptr, *found = nullptr, *tmp = nullptr;
	int dir = RIGHT, tmpDir, last;
	bool res = false;
	it->heirs[RIGHT] = root;

	while (it->heirs[dir] != nullptr) {
		last = dir;

		gParent = parent;
		parent = it;
		it = it->heirs[dir];
		dir = *(it->key) < key;

		if (*(it->key) == key) {
			found = it;
		}

		if (!IS_RED(it) && !IS_RED(it->heirs[dir])) {
			if (IS_RED(it->heirs[!dir])) {
				parent = parent->heirs[last] = RotateSingle(it, dir);
			}
			else if (!IS_RED(it->heirs[!dir])) {
				tmp = parent->heirs[!last];

				if (tmp != nullptr) {
					if (!IS_RED(tmp->heirs[!last]) && !IS_RED(it->heirs[last])) {
						parent->col = BLACK;
						tmp->col = RED;
						it->col = RED;
					}
					else {
						tmpDir = (gParent->heirs[RIGHT] == parent);

						if (IS_RED(tmp->heirs[last])) {
							gParent->heirs[tmpDir] = RotateDouble(parent, last);
						}
						else if (IS_RED(tmp->heirs[!last])) {
							gParent->heirs[tmpDir] = RotateSingle(parent, last);
						}

						it->col = gParent->heirs[tmpDir]->col = RED;
						gParent->heirs[tmpDir]->heirs[LEFT]->col = BLACK;
						gParent->heirs[tmpDir]->heirs[RIGHT]->col = BLACK;
					}
				}
			}
		}
	}

	if (found) {
		std::swap(found->key, it->key);
		parent->heirs[parent->heirs[RIGHT] == it] = it->heirs[it->heirs[LEFT] == nullptr];
		delete it;
		size--;
		res = true;
	}

	root = falseRoot.heirs[RIGHT];
	if (root != nullptr) {
		root->col = BLACK;
	}

	return res;
}

void RbtMap::ClearRecur(RbtNode*& node) {
	if (node == nullptr) {
		return;
	}

	ClearRecur(node->heirs[LEFT]);
	ClearRecur(node->heirs[RIGHT]);
	delete node;
	node = nullptr;
	size--;
}

void RbtMap::Clear() {
	ClearRecur(root);
}