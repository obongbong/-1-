#include "address.h"



int main() {

    //AddressBook addressBook;
    //addressBook.contactCount = 0;  // 초기화

    //HWND console = GetConsoleWindow();
    //RECT rect;
    //GetWindowRect(console, &rect);

    //ui 콘솔창 크기 조절용
    //int width = 800;
    //int height = 600;
    // 조절할 창의 크기를 설정
    //MoveWindow(console, rect.left, rect.top, width, height, TRUE);
    //draw_square();

    //system("cls");
    //system("mode con:cols=180 lines=180");

    //생일 알림
    //birthdayalarm(&addressBook);

    //매인메뉴 그리기
    do {
        initialize(&addressBook);
        printMenu();
        _getch();
        system("cls");
        
    } while (1);



    // 연락처 추가
    //addContact(&addressBook);


    //char contactName[128];
    //int contactIndex;


    //연락처 조회
    //displayContacts(&addressBook, "address.txt");
    
    // 연락처 삭제 함수 호출
    //deleteContactByName(&addressBook);

    //연락처 수정
    //modifyContact(&addressBook);

    //관계 검색
    //searchRelation(&addressBook, "address,txt");

    //초성검색
    //searchinitials(&addressBook);

    //Keyinput(38, 8);

    

    return 0;
}