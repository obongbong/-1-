#include "address.h"



int main() {

    //AddressBook addressBook;
    //addressBook.contactCount = 0;  // �ʱ�ȭ

    //HWND console = GetConsoleWindow();
    //RECT rect;
    //GetWindowRect(console, &rect);

    //ui �ܼ�â ũ�� ������
    //int width = 800;
    //int height = 600;
    // ������ â�� ũ�⸦ ����
    //MoveWindow(console, rect.left, rect.top, width, height, TRUE);
    //draw_square();

    //system("cls");
    //system("mode con:cols=180 lines=180");

    //���� �˸�
    //birthdayalarm(&addressBook);

    //���θ޴� �׸���
    do {
        initialize(&addressBook);
        printMenu();
        _getch();
        system("cls");
        
    } while (1);



    // ����ó �߰�
    //addContact(&addressBook);


    //char contactName[128];
    //int contactIndex;


    //����ó ��ȸ
    //displayContacts(&addressBook, "address.txt");
    
    // ����ó ���� �Լ� ȣ��
    //deleteContactByName(&addressBook);

    //����ó ����
    //modifyContact(&addressBook);

    //���� �˻�
    //searchRelation(&addressBook, "address,txt");

    //�ʼ��˻�
    //searchinitials(&addressBook);

    //Keyinput(38, 8);

    

    return 0;
}