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


//날짜 정보를 저장할 구조체
typedef struct {
	char date[STRING_SIZE];
}Date;

//구조체 정의
typedef struct _Person
{
	char name[STRING_SIZE]; //이름
	char number[STRING_SIZE]; //전화번호
	char address[STRING_SIZE]; //주소
	char birthday[STRING_SIZE]; //생일
	char relationship[STRING_SIZE]; //관계
	char initials[STRING_SIZE]; // 초성
	Date addedDate; //등록된 날짜
	int Favorite; //즐겨찾기 여부
	
}Person;

//연락처들을 관리할 구조체: 추가, 삭제, 수정, 검색, 정렬 등 기능 수행
typedef struct _AddressBook {
	Person contacts[MAX];
	int contactCount;
} AddressBook;

//char nameToDelete[STRING_SIZE];

AddressBook addressBook;


//FILE* openFile(const char* fileName, const char* mode);
//파일 열기
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
void searchRelation(AddressBook* addressBook, const char* filename);
void birthdayalarm(AddressBook* addressBook);
void searchinitials(AddressBook* addressBook);
void initialize(AddressBook* addressBook);

//즐겨찾기 함수
void addFavorite(AddressBook* addressBook);
void deleteFavorite(AddressBook* addressBook);

//ui 함수
int Keyinput(int x, int y, int max_y, int min_y);
void HideConsoleCursor();

void draw_sq(int x, int y);
void draw_square2(int x, int y, int width, int height);
void draw_square3();
void draw_square4(int x, int y, int width, int height);
void nextredraw();
void textcolor(int colorNum);
int nextPagedraw();
