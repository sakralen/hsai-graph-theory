#include "menu.h"

bool IsContinue(bool overrideFlag) {
	if (overrideFlag) {
		return false;
	}

	boost::basic_regex<char, boost::cpp_regex_traits<char>> expr;
	expr.imbue(std::locale{ "russian" });
	expr = RX_YES_OR_NO;

	string inp;
	char decision;

	do {
		cout << "����������? (Y/N): ";
		getline(cin, inp);
		if (boost::regex_match(inp, expr)) {
			decision = inp[0];

			switch (decision) {
			case 'Y':
			case 'y':
				return true;
			case 'N':
			case 'n':
				return false;
			}
		}
		else {
			cout << "������������ ����!\n\n";
		}
	} while (true);
}

bool GetInt(int& inp, int min, int max, int* forbidden) {
	string str;
	bool res;

	boost::basic_regex<char, boost::cpp_regex_traits<char>> expr;
	expr.imbue(std::locale{"russian"});
	expr = RX_NUMBERS;

	getline(cin, str);
	if (boost::regex_match(str, expr)) {
		inp = stoi(str);

		if ((forbidden != nullptr) && ((*forbidden) == inp)) {
			res = false;
		}
		else if (IS_IN_RANGE_CLOSED(inp, min, max)) {
			res = true;
		}
		else {
			res = false;
		}
	}
	else {
		res = false;
	}

	if (res) {
		return true;
	}
	else {
		cout << "������������ ����!\n\n";
		return false;
	}
}

bool GetStr(string& inp, string rx) {
	boost::basic_regex<char, boost::cpp_regex_traits<char>> expr;
	expr.imbue(std::locale{"russian"});
	expr = rx;

	getline(cin, inp);
	if (boost::regex_match(inp, expr)) {
		return true;
	}
	else {
		cout << "������������ ����!\n\n";
		return false;
	}
}

void PrintMenu() {
	cout << DELIMETER << '\n';
	cout << "\t������� �� ������ ������-������� �����:\n";
	for (int i = 0; i < MENU_RBT_ITEMS_CNT; i++) {
		cout << std::setw(3) << i << ": " << kMenuStrings[i] << '\n';
	}
	cout << "\n\t������� �� ������ ���-�������:\n";
	for (int i = 0; i < MENU_RBT_ITEMS_CNT; i++) {
		cout << std::setw(3) << i + MENU_RBT_ITEMS_CNT << ": " << kMenuStrings[i] << '\n';
	}

	cout << '\n' << std::setw(3) << MENU_RBT_ITEMS_CNT + MENU_HASH_ITEMS_CNT + MENU_ADDITIONAL_ITEMS_CNT - 1 \
		<< ": " << kMenuStrings[MENU_HASH_ITEMS_CNT] << '\n';
	cout << DELIMETER << '\n';
}

void ExecRbtPrint(RbtMap& map) {
	if (!map.GetSize()) {
		cout << "������� ����!\n";
		return;
	}

	cout << "���������� �������:\n";
	map.Print(cout);
}

void ExecRbtFind(RbtMap& map) {
	if (!map.GetSize()) {
		cout << "������� ����!\n";
		return;
	}

	string inp;
	RbtNode *found = nullptr, *parent = nullptr;

	do {
		cout << "������� �����:\n";
	} while (!GetStr(inp, RX_WORDS_RU));
	cout << '\n';

	found = map.Find(inp, parent);

	if (found) {
		cout << setw(15) << *(found->key) << setw(3) << found->val << " -- ";

		HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
		if (found->col == RED) {
			SetConsoleTextAttribute(console, TEXT_COLOR_RED);
		}
		else {
			SetConsoleTextAttribute(console, TEXT_COLOR_GREEN);
		}
		cout << setw(7) << kColors[found->col];
		SetConsoleTextAttribute(console, TEXT_COLOR_DEFAULT);

		if (parent) {
			cout << " " << setw(6) << kDirections[GET_DIRECTION(found, parent)] << " ������� " << *(parent->key);
		}
		else {
			cout << " ������ ������";
		}
		cout << '\n';
	}
	else {
		cout << "������ �� �������!\n";
	}
}

void ExecRbtInsert(RbtMap& map) {
	string inp;

	do {
		cout << "������� �����:\n";
	} while (!GetStr(inp, RX_WORDS_RU));
	cout << '\n';

	if (map.Insert(inp)) {
		cout << "������ ��������� � �������!\n";
	}
	else {
		cout << "������ ��� ���� � �������, ������� �������� ������ ��������!\n";
	}
}

void ExecRbtRemove(RbtMap& map) {
	if (!map.GetSize()) {
		cout << "������� ����!\n";
		return;
	}

	string inp;

	do {
		cout << "������� �����:\n";
	} while (!GetStr(inp, RX_WORDS_RU));
	cout << '\n';

	if (map.Remove(inp)) {
		cout << "������ �������!\n";
	}
	else {
		cout << "������ �� �������!\n";
	}
}

void ExecRbtClear(RbtMap& map) {
	if (!map.GetSize()) {
		cout << "������� ����!\n";
		return;
	}

	map.Clear();
	cout << "������� ������!\n";
}

void ExecRbtLoad(RbtMap& map) {
	map.Load(RBT_INPUT_TXT);
	cout << "������ ���������!\n";
}

void ExecRbtSave(RbtMap& map) {
	if (!map.GetSize()) {
		cout << "������� ����!\n";
		return;
	}

	map.Save(RBT_OUTPUT_TXT);
	cout << "������ ���������!\n";
}

void ExecHashPrint(HashMap& map) {
	if (!map.GetSize()) {
		cout << "������� ����!\n";
		return;
	}

	cout << "���������� �������:\n";
	map.Print(cout);
}

void ExecHashFind(HashMap& map) {
	if (!map.GetSize()) {
		cout << "������� ����!\n";
		return;
	}

	string inp;
	RbtNode* found = nullptr, * parent = nullptr;

	do {
		cout << "������� �����:\n";
	} while (!GetStr(inp, RX_WORDS_RU));
	cout << '\n';

	found = map.Find(inp, parent);

	if (found) {
		cout << setw(15) << *(found->key) << setw(3) << found->val << " -- ";

		HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
		if (found->col == RED) {
			SetConsoleTextAttribute(console, TEXT_COLOR_RED);
		}
		else {
			SetConsoleTextAttribute(console, TEXT_COLOR_GREEN);
		}
		cout << setw(7) << kColors[found->col];
		SetConsoleTextAttribute(console, TEXT_COLOR_DEFAULT);

		if (parent) {
			cout << " " << setw(6) << kDirections[GET_DIRECTION(found, parent)] << " ������� " << *(parent->key);
		}
		else {
			cout << " ������ ������";
		}
		cout << '\n';
	}
	else {
		cout << "������ �� �������!\n";
	}
}

void ExecHashInsert(HashMap& map) {
	string inp;

	do {
		cout << "������� �����:\n";
	} while (!GetStr(inp, RX_WORDS_RU));
	cout << '\n';

	if (map.Insert(inp)) {
		cout << "������ ��������� � �������!\n";
	}
	else {
		cout << "������ ��� ���� � �������, ������� �������� ������ ��������!\n";
	}
}

void ExecHashRemove(HashMap& map) {
	if (!map.GetSize()) {
		cout << "������� ����!\n";
		return;
	}

	string inp;

	do {
		cout << "������� �����:\n";
	} while (!GetStr(inp, RX_WORDS_RU));
	cout << '\n';

	if (map.Remove(inp)) {
		cout << "������ �������!\n";
	}
	else {
		cout << "������ �� �������!\n";
	}
}

void ExecHashClear(HashMap& map) {
	if (!map.GetSize()) {
		cout << "������� ����!\n";
		return;
	}

	map.Clear();
	cout << "������� ������!\n";
}

void ExecHashLoad(HashMap& map) {
	map.Load(HASH_INPUT_TXT);
	cout << "������ ���������!\n";
}

void ExecHashSave(HashMap& map) {
	if (!map.GetSize()) {
		cout << "������� ����!\n";
		return;
	}

	map.Save(HASH_OUTPUT_TXT);
	cout << "������ ���������!\n";
}