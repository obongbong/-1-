#include "address.h"



int main() {


    //매인메뉴 그리기
    do {
        initialize(&addressBook);
        printMenu();
        getchar();
        system("cls");
        
    } while (1);

    

    return 0;
}