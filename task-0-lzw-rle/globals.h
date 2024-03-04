#ifndef GLOBALS_H
#define GLOBALS_H

//conditional translation

//include
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <bitset> //��� �������� ������������� � �������� ����
#include <filesystem>
#include <algorithm>

//define
#define SYMB_CNT 25					//����� ��������� ��������
#define SOURCE_FILE_SIZE 10000		//��������� ����� �����
#define LZW_DEPTH 13				//����������� ��� ����� LZW
									//��� �������� ���������� ���������� ~5000 ����� -> 13 ��� 
#define RLE_DEPTH 8					//����������� ��� ���������� ���������� � RLE
									//������ ������ -- ���������� ������ ������� 10000 ��� -> 14 ���	
									//������� 8 -> 127 �������� � ������������������

#define SOURCE_FILE_NAME "source.txt"				//�������� ������������ �����-"���������"
#define ENCODED_LZW_FILE_NAME "lzw_encoded.txt"		//�������� ��������������� LZW �����
#define DECODED_LZW_FILE_NAME "lzw_decoded.txt"		//�������� ��������������� LZW �����
#define ENCODED_RLE_FILE_NAME "rle_encoded.txt"		//�������� ��������������� RLE �����
#define DECODED_RLE_FILE_NAME "rle_decoded.txt"		//�������� ��������������� RLE �����

#define stop __asm nop

//using
using std::ofstream;
using std::ifstream;
using std::map;
using std::string;
using std::bitset;
using std::ios;
using std::cout;

//typedef
typedef short curtype;

//constants
const string kSymbStr = "������������0123456789 ).";
//const string kSymbStr = "abc";

//enums

//global variables
extern map<char, float> mapSymbPrice;		//������� �������� � ��� �����������
extern map<string, curtype> mapLzwComp;		//������� ��������/������������������� � �� ����� ��� ������
extern map<curtype, string> mapLzwDecomp;	//������� ����� � �� ��������/������������������� ��� ����������

//functions
void FillFile();			//��������� ���� ��������� �������
void FillMap();				//��������� ������� �������� � ��� �����������
void CalcPrice();			//��������� ���� �����������
void InitMapLzwComp();		//�������������� ������� ��� ������ ��� LZW
void InitMapLzwDecomp();	//���������� ��� �������������
int CountBits(int num);		//������� �������� �������� � �����
void CompressLzw(const char* name);			//���������� ������ �� ��������� LZW
void DecompressLzw(const char* name);		//���������� ���������� �� ��������� LZW
int GetFileSize_cpp17(string name);			//��������� ����� ����� !!! ������ C++17 � ���� (?) !!!
//int GetFileSize_lazy(const char* name);	//��������� ����� ����� ��������� ��������
float CalcCompressionRatio(const char* name);			//��������� ����. ������
bool IsFilesEqual(const string f1, const string f2);	//�������� ��������� ������
void ComressRle(const char* name);										//���������� ������ �� ��������� RLE
void DecompressRle(const char* name);									//���������� ���������� �� ��������� RLE

void EncodeRepSeq(char letter, int count, ofstream& ofs);					//�������� ������������� ����.-��
void EncodeDiffSeq(int startPos, int count, ifstream& ifs, ofstream& ofs);	//�������� ��������������� ����.-��


void DbgCheckEqual(const string f1, const string f2);

#endif // !GLOBALS_H
