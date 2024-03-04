#pragma once

#include "global.h"
#include "rbtMap.h"
#include "HashMap.h"

#define DELIMETER "--------------------------------------------------"
#define MENU_RBT_ITEMS_CNT 7
#define MENU_HASH_ITEMS_CNT 7
#define MENU_ADDITIONAL_ITEMS_CNT 1

enum class MenuItems {
	kRbtPrint,
	kRbtFind,
	kRbtInsert,
	kRbtRemove,
	kRbtClear,
	kRbtLoad,
	kRbtSave,
	kHashPrint,
	kHashFind,
	kHashInsert,
	kHashRemove,
	kHashClear,
	kHashLoad,
	kHashSave,
	kExit
};

const string kMenuStrings[] = {
	"Вывод на экран содержимого словаря",
	"Найти запись",
	"Добавить запись",
	"Удалить запись",
	"Очистить словарь",
	"Загрузить записи из файла",
	"Сохранить записи в файл",
	"Выход"
};

bool IsContinue(bool overrideFlag = false);
bool GetInt(int& inp, int min, int max, int* forbidden = nullptr);
bool GetStr(string& str, string rx);
void PrintMenu();

void ExecRbtPrint(RbtMap& map);
void ExecRbtFind(RbtMap& map);
void ExecRbtInsert(RbtMap& map);
void ExecRbtRemove(RbtMap& map);
void ExecRbtClear(RbtMap& map);
void ExecRbtLoad(RbtMap& map);
void ExecRbtSave(RbtMap& map);

void ExecHashPrint(HashMap& map);
void ExecHashFind(HashMap& map);
void ExecHashInsert(HashMap& map);
void ExecHashRemove(HashMap& map);
void ExecHashClear(HashMap& map);
void ExecHashLoad(HashMap& map);
void ExecHashSave(HashMap& map);