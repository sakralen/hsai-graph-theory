#pragma once

#include "global.h"
#include "rbtMap.h"

class HashMap {
	vector<RbtMap*> data = vector<RbtMap*>();
	int size = 0;

public:
	~HashMap();
	static unsigned int GetHashValue(string key);
	int GetSize() const;
	RbtNode* Find(string key, RbtNode*& parent);
	void Print(ostream& os);
	bool Insert(string key);
	bool Remove(string key);
	void Clear();
	void Load(string file = HASH_INPUT_TXT);
	void Save(string file = HASH_OUTPUT_TXT);
};