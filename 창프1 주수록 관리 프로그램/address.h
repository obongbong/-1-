#pragma once
#define MAX 1024
#define STRING_SIZE 128
#define WIDTH 800
#define HEIGHT 600
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "address.h"
#include <conio.h>
#include <Windows.h>
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define ARROW 224

#define MAX_X 40
#define MIN_Y 8
#define MAX_Y 20



//��¥ ������ ������ ����ü
typedef struct {
	char date[STRING_SIZE];
}Date;

//����ü ����
typedef struct _Person
{
	char name[STRING_SIZE]; //�̸�
	char number[STRING_SIZE]; //��ȭ��ȣ
	char address[STRING_SIZE]; //�ּ�
	char birthday[STRING_SIZE]; //����
	char relationship[STRING_SIZE]; //����
	char initials[STRING_SIZE]; // �ʼ�
	Date addedDate; //��ϵ� ��¥
	int Favorite; //���ã�� ����
	
}Person;

//����ó���� ������ ����ü: �߰�, ����, ����, �˻�, ���� �� ��� ����
typedef struct _AddressBook {
	Person contacts[MAX];
	int contactCount;
} AddressBook;

// �˻� ����� �����ϴ� ����ü �迭
typedef struct {
	Person relcon[MAX];
	int contactCount;
} SearchResult;

typedef struct {
	Person initials[MAX];
	int contactCount;
}Searchinitials;

typedef struct {
	Person Favorite[MAX];
	int contactCount;
}SearchFavorite;

//char nameToDelete[STRING_SIZE];
AddressBook addressBook;
SearchResult searchResult;
Searchinitials initials;
SearchFavorite searchFavorite;

//FILE* openFile(const char* fileName, const char* mode);
//���� ����
void loadAddressBookFromFile(AddressBook* addressBook, const char* filename);
void saveAddressBookToFile(AddressBook* addressBook, const char* filename);
void addContact(AddressBook* addressBook);
void displayContacts(AddressBook* addressBook, const char* filename);
void saveAddressBookToFileW(AddressBook* addressBook, const char* filename);
void deleteContactByName(AddressBook* addressBook);
void gotoxy(int x, int y);
void printMenu();
void draw_square();
void modifyContact(AddressBook* addressBook);
void searchRelation(AddressBook* addressBook, const char* filename, SearchResult* searchResult);
void birthdayalarm(AddressBook* addressBook);
void initialize(AddressBook* addressBook);
void searchinitials(AddressBook* addressBook, Searchinitials* initials);
void searchfavorite(AddressBook* addressBook, SearchFavorite* searchFavorite);

//���ã�� �Լ�
void addFavorite(AddressBook* addressBook);
void deleteFavorite(AddressBook* addressBook);

//ui �Լ�
int Keyinput(int x, int y, int max_y, int min_y);
void HideConsoleCursor();

void draw_sq(int x, int y);
void draw_square2(int x, int y, int width, int height);
void draw_square3();
void draw_square4(int x, int y, int width, int height);
void nextredraw(int leftSelected, int rightSelected);
void textcolor(int colorNum);
int nextPagedraw();
void draw_square5(int x, int y, int width, int height, int selected);

