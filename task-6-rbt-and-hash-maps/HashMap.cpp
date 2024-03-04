#include "HashMap.h"

HashMap::~HashMap() {
	Clear();
}

unsigned int HashMap::GetHashValue(string key) {
	transform(key.begin(), key.end(), key.begin(), tolower);

	int first = key[0];
	int mid = key[key.size() / 2];
	int last = key[key.size() - 1];

	return abs((first + mid + last) / 3);
}

int HashMap::GetSize() const {
	return size;
}

RbtNode* HashMap::Find(string key, RbtNode*& parent) {
	if (size != 0) {
		transform(key.begin(), key.end(), key.begin(), tolower);
		unsigned int hashVal = GetHashValue(key);
		RbtNode* found = nullptr;

		if (hashVal < data.size()) {
			if (data[hashVal] != nullptr) {
				found = data[hashVal]->Find(key, parent);
			}
		}

		return found;
	}
	return nullptr;
}

void HashMap::Print(ostream& os) {
	if (size != 0) {
		for (unsigned int i = 0; i < data.size(); i++) {
			if (data[i] != nullptr) {
				data[i]->Print(os);
				os << '\n';
			}
		}
	}
}

bool HashMap::Insert(string key) {
	transform(key.begin(), key.end(), key.begin(), tolower);

	RbtNode *found = nullptr, *parent = nullptr;
	found = Find(key, parent);

	if (found) {
		(found->val)++;
		return false;
	}

	unsigned int hashVal = GetHashValue(key);

	if (hashVal >= data.size()) {
		data.resize(hashVal + 1, nullptr);
	}

	if (data[hashVal] == nullptr) {
		data[hashVal] = new RbtMap();
	}
	
	data[hashVal]->Insert(key);
	size++;
	return true;
}

bool HashMap::Remove(string key) {
	if (size != 0) {
		transform(key.begin(), key.end(), key.begin(), tolower);

		RbtNode* found = nullptr, * parent = nullptr;
		found = Find(key, parent);

		if (found) {
			int hashVal = GetHashValue(key);
			data[hashVal]->Remove(key);
			if (data[hashVal]->GetSize() == 0) {
				delete data[hashVal];
				data[hashVal] = nullptr;
			}
			size--;
			return true;
		}
	}
	return false;
}

void HashMap::Clear() {
	if (size != 0) {
		for (unsigned int i = 0; i < data.size(); i++) {
			if (data[i] != nullptr) {
				data[i]->Clear();
				delete data[i];
				data[i] = nullptr;
			}
		}
		size = 0;
	}
}

void HashMap::Load(string file) {
	std::ifstream ifs(file);
	if (ifs.is_open()) {
		string s;
		boost::basic_regex<char, boost::cpp_regex_traits<char>> expr;
		expr.imbue(std::locale{ "russian" });
		expr = RX_WORDS_RU;

		while (ifs >> s) {	
			if (boost::regex_match(s, expr)) {
				Insert(s);
			}
		}

		ifs.close();
	}
}

void HashMap::Save(string file) {
	std::ofstream ofs(file);
	if (ofs.is_open()) {
		Print(ofs);
		ofs.close();
	}
}