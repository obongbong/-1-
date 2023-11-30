#include "address.h"
#define X 30
#define Y 4

//���Ͽ� �����ϱ�(������ ���� ����ó ���� �߰�)
void saveAddressBookToFile(AddressBook* addressBook, const char* filename) {
    //FILE* openFile(filename, a);

    FILE* file = fopen(filename, "a");
    if (file == NULL) {
        perror("������ �� �� �����ϴ�.\n");
        return;
    }

    for (int i = 0; i < addressBook->contactCount; i++) {
        fprintf(file, "%s|%s|%s|%s|%s|%s|%s|%d\n",
            addressBook->contacts[i].name,
            addressBook->contacts[i].number,
            addressBook->contacts[i].address,
            addressBook->contacts[i].birthday,
            addressBook->contacts[i].relationship,
            addressBook->contacts[i].initials,
            addressBook->contacts[i].addedDate.date,
            addressBook->contacts[i].Favorite);
    }

    fclose(file);
}

//���Ͽ� �����ϱ�(���Ͽ� ���� ����)
void saveAddressBookToFileW(AddressBook* addressBook, const char* filename) {

    //FILE* openFile(filename, w);

    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("������ �� �� �����ϴ�.\n");
        return;
    }

    for (int i = 0; i < addressBook->contactCount; i++) {
        fprintf(file, "%s|%s|%s|%s|%s|%s|%s|%d\n",
            addressBook->contacts[i].name,
            addressBook->contacts[i].number,
            addressBook->contacts[i].address,
            addressBook->contacts[i].birthday,
            addressBook->contacts[i].relationship,
            addressBook->contacts[i].initials,
            addressBook->contacts[i].addedDate.date,
            addressBook->contacts[i].Favorite);
    }

    fclose(file);
}

//���� ���� �ҷ�����(����ü�� ����)
void loadAddressBookFromFile(AddressBook* addressBook, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("������ �� �� �����ϴ�.\n");
        return;
    }

    // ������ ���� ���˿� �°� �����͸� �о��
    while (fscanf(file, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d\n",
        addressBook->contacts[addressBook->contactCount].name,
        addressBook->contacts[addressBook->contactCount].number,
        addressBook->contacts[addressBook->contactCount].address,
        addressBook->contacts[addressBook->contactCount].birthday,
        addressBook->contacts[addressBook->contactCount].relationship,
        addressBook->contacts[addressBook->contactCount].initials,
        addressBook->contacts[addressBook->contactCount].addedDate.date,
        &addressBook->contacts[addressBook->contactCount].Favorite) == 8) {

        addressBook->contacts[addressBook->contactCount].name[STRING_SIZE - 1] = '\0';
        addressBook->contacts[addressBook->contactCount].number[STRING_SIZE - 1] = '\0';
        addressBook->contacts[addressBook->contactCount].address[STRING_SIZE - 1] = '\0';
        addressBook->contacts[addressBook->contactCount].birthday[STRING_SIZE - 1] = '\0';
        addressBook->contacts[addressBook->contactCount].relationship[STRING_SIZE - 1] = '\0';
        addressBook->contacts[addressBook->contactCount].initials[STRING_SIZE - 1] = '\0';
        addressBook->contacts[addressBook->contactCount].addedDate.date[STRING_SIZE - 1] = '\0'; // Ensure null-termination for date

        addressBook->contactCount++;
    }

    fclose(file);
}

void addContact(AddressBook* addressBook) {
    if (addressBook->contactCount >= MAX) {
        printf("�� �̻� ����ó�� �߰��� �� �����ϴ�.\n");
        return;
    }
    //loadAddressBookFromFile(addressBook, "address.txt");
    int x = 30;
    int y = 4;
    gotoxy(x, y);

    fflush(stdin);
    printf("����� ����� ������ �Է����ּ���.\n");
    gotoxy(x, y+2);
    printf("�̸�: ");
    fgets(addressBook->contacts[addressBook->contactCount].name, STRING_SIZE, stdin);
    addressBook->contacts[addressBook->contactCount].name[strcspn(addressBook->contacts[addressBook->contactCount].name, "\n")] = '\0';

    gotoxy(x, y + 4);
    printf("��ȭ��ȣ: ");
    fgets(addressBook->contacts[addressBook->contactCount].number, STRING_SIZE, stdin);
    addressBook->contacts[addressBook->contactCount].number[strcspn(addressBook->contacts[addressBook->contactCount].number, "\n")] = '\0';

    gotoxy(x, y + 6);
    printf("�ּ�: ");
    fgets(addressBook->contacts[addressBook->contactCount].address, STRING_SIZE, stdin);
    addressBook->contacts[addressBook->contactCount].address[strcspn(addressBook->contacts[addressBook->contactCount].address, "\n")] = '\0';

    gotoxy(x, y + 8);
    printf("����: ");
    fgets(addressBook->contacts[addressBook->contactCount].birthday, STRING_SIZE, stdin);
    addressBook->contacts[addressBook->contactCount].birthday[strcspn(addressBook->contacts[addressBook->contactCount].birthday, "\n")] = '\0';

    gotoxy(x, y + 10);
    printf("����: ");
    fgets(addressBook->contacts[addressBook->contactCount].relationship, STRING_SIZE, stdin);
    addressBook->contacts[addressBook->contactCount].relationship[strcspn(addressBook->contacts[addressBook->contactCount].relationship, "\n")] = '\0';

    addressBook->contacts[addressBook->contactCount].Favorite = 0;

    // �̸����� �ʼ� ����
    char initials[STRING_SIZE];
    int num_initials = getinitials(addressBook->contacts[addressBook->contactCount].name, initials, STRING_SIZE);
    strncpy(addressBook->contacts[addressBook->contactCount].initials, initials, STRING_SIZE);
    addressBook->contacts[addressBook->contactCount].initials[STRING_SIZE - 1] = '\0';

    // ���� ��¥�� �߰��� ��¥�� ����
    time_t currentTime;
    time(&currentTime);  // ���� �ð� ������ ����
    struct tm* localTime = localtime(&currentTime);

    // ���� ��¥�� "YYYY-MM-DD" ������ ���ڿ��� ��ȯ�Ͽ� ����;
    sprintf(addressBook->contacts[addressBook->contactCount].addedDate.date,
        "%04d%02d%02d", localTime->tm_year + 1900, localTime->tm_mon + 1, localTime->tm_mday);

    // ���ο� ����ó�� �ּҷϿ� �߰�
    addressBook->contactCount++;
    system("cls");
    draw_square4(47, 15, 50, 30);
    gotoxy(x+10, y + 4);
    printf("�߰��Ϸ�!\n");

    saveAddressBookToFile(addressBook, "address.txt");
}



void displayContacts(AddressBook* addressBook, const char* filename) {
    loadAddressBookFromFile(addressBook, "address.txt");
    int x = 6;
    int y = 1;
    int choice = 0;
    int leftselect = 0;
    int rightselect = 1;

    int currentPage = 0;
    int contactsPerPage = 4;
    int totalPages = (addressBook->contactCount + contactsPerPage - 1) / contactsPerPage;

    

    // ó�� ȣ�� �� ù ��° �������� ����ó ������ ���
    draw_square4(38, 15, 70, 30);
    nextredraw(leftselect, rightselect);
    gotoxy(34, 27);
    printf(" %d / %d\n", currentPage + 1, totalPages);

    do {
        system("cls");
        draw_square4(38, 15, 70, 30);
        nextredraw(leftselect, rightselect);
        gotoxy(34, 27);
        printf(" %d / %d\n", currentPage + 1, totalPages);

        // ����ó ���� ���
        int startIndex = currentPage * contactsPerPage;
        int endIndex = startIndex + contactsPerPage;
        
        // ���� ���������� ����� ������ ������ y �ʱ�ȭ
        y = 1;

        for (int i = startIndex; i < endIndex && i < addressBook->contactCount; ++i) {
            gotoxy(x, y);
            printf("�̸�: %s", addressBook->contacts[i].name);
            if (addressBook->contacts[i].Favorite == 1) {
                printf(" ��"); // ���ã���̸� ���� ���
            }

            y += 1;
            gotoxy(x, y);
            printf("��ȭ��ȣ: %s", addressBook->contacts[i].number);
            y += 1;
            gotoxy(x, y);
            printf("�ּ�: %s", addressBook->contacts[i].address);
            y += 1;
            gotoxy(x, y);
            printf("����: %s", addressBook->contacts[i].birthday);
            y += 1;
            gotoxy(x, y);
            printf("����: %s", addressBook->contacts[i].relationship);
            y += 1;
            gotoxy(x, y);
            printf("��� ��¥: %s\n\n", addressBook->contacts[i].addedDate.date);
            y += 2;
        }
        birthdayalarm(addressBook);
        choice = nextPagedraw();
        
        // ���⼭ nextPagedraw�� ��ȯ�� ���� ������� ���� ó���� ����
        if (choice == 60) {
            leftselect = 1;
            rightselect = 0;
            currentPage--;
            if (currentPage < 0) {
                currentPage = 0;
            }
            // '<' ��ư�� ������ ��쿡 ���� ó��
            // ���� �������� ���ҽ�Ű�ų� ���� �������� ������ ����ϴ� ���� ����
        }
        else if (choice == 67) {
            leftselect = 0;
            rightselect = 1;
            currentPage++;
            if (currentPage >= totalPages) {
                currentPage = totalPages - 1;
            }
        }

        
        if (choice == 27)
        {
            printMenu();
            break;

        }
    } while (1);

}

//�����Լ�
void deleteContactByName(AddressBook* addressBook) {
    char nameToDelete[STRING_SIZE];
    int found = 0;  // ����ó�� ã�Ҵ��� ���θ� ��Ÿ���� �÷���

    gotoxy(X, Y);

    // ����ڷκ��� ������ ����ó�� �̸� �Է� �ޱ�
    printf("������ ����ó�� �̸��� �Է��ϼ���: ");
    gotoxy(X + 6, Y + 2);
    fgets(nameToDelete, STRING_SIZE, stdin);
    nameToDelete[strcspn(nameToDelete, "\n")] = '\0';  // ���� ���� ����
    rewind(stdin);
    loadAddressBookFromFile(addressBook, "address.txt");
    gotoxy(X, Y + 3);
   
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].name, nameToDelete) == 0) {
            // ����ó�� ã�����Ƿ� �ش� ����ó�� �����ϰ� �迭�� ���ҽ�Ŵ
            for (int j = i; j < addressBook->contactCount - 1; j++) {
                addressBook->contacts[j] = addressBook->contacts[j + 1];
            }
            addressBook->contactCount--;
            found = 1;  // ����ó�� ã������ ǥ��
            printf("����ó�� �����Ǿ����ϴ�.\n");
            saveAddressBookToFileW(addressBook, "address.txt");  // ������ �ּҷ��� ���Ͽ� ����
            
            return;  // ���� �� ����
        }
    }

    if (!found) {
        printf("�ش� �̸��� ����ó�� ã�� �� �����ϴ�.\n");
    }

}

//����ó ����(�̿ϼ�)
//���� �޴� ���ñ�� ����Ű �Է����� �����ϴ°ɷ� �ٲٴ���
void modifyContact(AddressBook* addressBook) {

    char name[128];
    int num;

    int x = 40;
    int y = 8;

    

    //���� ������ �ҷ�����
    loadAddressBookFromFile(addressBook, "address.txt");
    gotoxy(X, Y);
    
    printf("������ ����� �̸��� �Է����ּ���: ");
    gotoxy(X+ 6, Y + 2);
    scanf("%s", name);
    getchar();
    int found = 0;



    //�̸� ��ġ Ȯ��
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].name, name) == 0)
        {
            found = 1;
            gotoxy(x, y);
            printf("1. �̸� \n");
            gotoxy(x, y + 2);
            printf("2. ��ȭ��ȣ \n");
            gotoxy(x, y + 4);
            printf("3. �ּ� \n");
            gotoxy(x, y + 6);
            printf("4. ���� \n");
            gotoxy(x, y + 8);
            printf("5. ���� \n");
            gotoxy(x, y + 10);
            printf("6. ���ã�� \n");

            gotoxy(x, y + 12);

            //Ű���� ����Ű �Է�
            int numchoice = Keyinput(x, y, y+10, y);

            switch (numchoice) {
            case 1:
                //�̸�
                system("cls");
                draw_square2(20, 0, 56, 30);
                gotoxy(x-4, y);
                printf("�̸��� �Է����ּ���: ");
                fgets(addressBook->contacts[i].name, 128, stdin);
                addressBook->contacts[i].name[strcspn(addressBook->contacts[i].name, "\n")] = '\0';
                break;
                //��ȭ��ȣ
            case 2:
                system("cls");
                draw_square2(20, 0, 56, 30);
                gotoxy(x - 4, y+2);
                printf("��ȭ��ȣ�� �Է����ּ���: ");
                fgets(addressBook->contacts[i].number, 128, stdin);
                addressBook->contacts[i].number[strcspn(addressBook->contacts[i].number, "\n")] = '\0';
                break;
                //�ּ�
            case 3:
                system("cls");
                draw_square2(20, 0, 56, 30);
                gotoxy(x - 4, y+4);
                printf("�ּҸ� �Է����ּ���: ");
                fgets(addressBook->contacts[i].address, 128, stdin);
                addressBook->contacts[i].address[strcspn(addressBook->contacts[i].address, "\n")] = '\0';
                break;
                //����
            case 4:
                system("cls");
                draw_square2(20, 0, 56, 30);
                gotoxy(x - 4, y+6);
                printf("������ �Է����ּ���: ");
                fgets(addressBook->contacts[i].birthday, 128, stdin);
                addressBook->contacts[i].birthday[strcspn(addressBook->contacts[i].birthday, "\n")] = '\0';
                break;
                //����
            case 5:
                system("cls");
                draw_square2(20, 0, 56, 30);
                gotoxy(x - 4, y+8);
                printf("���踦 �Է����ּ��� : ");
                fgets(addressBook->contacts[i].relationship, 128, stdin);
                addressBook->contacts[i].relationship[strcspn(addressBook->contacts[i].relationship, "\n")] = '\0';
                break;
            case 6:
                system("cls");
                draw_square2(20, 0, 56, 30);
                gotoxy(x , y);
                printf("���ã�� �߰�");
                gotoxy(x, y + 2);
                printf("���ã�� ����");
                int favoritenum = Keyinput(x, y, y + 2, y);
                switch (favoritenum)
                {
                case 1:
                    addressBook->contacts[i].Favorite = 1;
                    break;

                case 2:
                    addressBook->contacts[i].Favorite = 0;
                    break;

                }

            }
            system("cls");
            draw_square2(20, 0, 56, 30);
            gotoxy(x, y);
            printf("�����Ϸ�! \n");
            saveAddressBookToFileW(addressBook, "address.txt");  // Save the updated contact data to the file
            return;
        }
    }
    if (found == 0)
    {
        gotoxy(x-3, y);
        printf("�̸��� ã�� ���߽��ϴ�.");
    }
}
/*
���� �˻�(�κ� ���ڿ� �˻� O)
*/

void searchRelation(AddressBook* addressBook, const char* filename, SearchResult* searchResult)
{
    //searchResult->contactCount = 0;
    int x1 = 6;
    int y1 = 1;
    int choice = 0;
    int leftselect = 0;
    int rightselect = 1;

    int currentPage = 0;
    int contactsPerPage = 4;


    int x = 40;
    int y = 8;
    //�������� �ҷ�����
    loadAddressBookFromFile(addressBook, "address.txt");

    draw_square4(47, 15, 50, 30);
    gotoxy(x-6, y);


    printf("�˻��� ���踦 �Է����ּ���: ");
    char relationship[128];
    gotoxy(x - 2, y + 1);
    fgets(relationship, sizeof(relationship), stdin);
    int count = 0;

    int found = 0;

    //����Ű �����
    if (relationship[strlen(relationship) - 1] == '\n') {
        relationship[strlen(relationship) - 1] = '\0';
    }

    //���� ��ġ Ȯ��
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strstr(addressBook->contacts[i].relationship, relationship) != NULL)
        {
            strcpy(searchResult->relcon[count].name, addressBook->contacts[i].name);
            strcpy(searchResult->relcon[count].number, addressBook->contacts[i].number);
            strcpy(searchResult->relcon[count].address, addressBook->contacts[i].address);
            strcpy(searchResult->relcon[count].birthday, addressBook->contacts[i].birthday);
            strcpy(searchResult->relcon[count].relationship, addressBook->contacts[i].relationship);
            strcpy(searchResult->relcon[count].addedDate.date, addressBook->contacts[i].addedDate.date);
            searchResult->relcon[count].Favorite = addressBook->contacts[i].Favorite;
                count++;
                searchResult->contactCount++;
                found = 1;
        }
    }

    //searchResult->contactCount = count; // �˻� ����� ����ó �� ������Ʈ
    if (found == 0)
    {
        gotoxy(x - 6, y + 3);
        printf("�׷� ������ ����� �����ϴ�.");
    }
    int totalPages = (searchResult->contactCount + contactsPerPage - 1) / contactsPerPage;
    system("cls");
    draw_square4(38, 15, 70, 30);
    nextredraw(leftselect, rightselect);
    gotoxy(34, 27);
    printf(" %d / %d\n", currentPage + 1, totalPages);

    // ����ó ���� ���
    int startIndex = currentPage * contactsPerPage;
    int endIndex = startIndex + contactsPerPage;

    do {
        system("cls");
        draw_square4(38, 15, 70, 30);
        nextredraw(leftselect, rightselect);
        gotoxy(34, 27);
        printf(" %d / %d\n", currentPage + 1, totalPages);

        // ����ó ���� ���
        int startIndex = currentPage * contactsPerPage;
        int endIndex = startIndex + contactsPerPage;

        // ���� ���������� ����� ������ ������ y �ʱ�ȭ
        y1 = 1;

        for (int i = startIndex; i < endIndex && i < searchResult->contactCount; ++i) {
            gotoxy(x1, y1);
            printf("�̸�: %s", searchResult->relcon[i].name);
            if (searchResult->relcon[i].Favorite == 1) {
                printf(" ��"); // ���ã���̸� ���� ���
            }

            y1 += 1;
            gotoxy(x1, y1);
            printf("��ȭ��ȣ: %s", searchResult->relcon[i].number);
            y1 += 1;
            gotoxy(x1, y1);
            printf("�ּ�: %s", searchResult->relcon[i].address);
            y1 += 1;
            gotoxy(x1, y1);
            printf("����: %s", searchResult->relcon[i].birthday);
            y1 += 1;
            gotoxy(x1, y1);
            printf("����: %s", searchResult->relcon[i].relationship);
            y1 += 1;
            gotoxy(x1, y1);
            printf("��� ��¥: %s\n\n", searchResult->relcon[i].addedDate.date);
            y1 += 2;
        }
        birthdayalarm(addressBook);
        choice = nextPagedraw();

        // ���⼭ nextPagedraw�� ��ȯ�� ���� ������� ���� ó���� ����
        if (choice == 60) {
            leftselect = 1;
            rightselect = 0;
            currentPage--;
            if (currentPage < 0) {
                currentPage = 0;
            }
            // '<' ��ư�� ������ ��쿡 ���� ó��
            // ���� �������� ���ҽ�Ű�ų� ���� �������� ������ ����ϴ� ���� ����
        }
        else if (choice == 67) {
            leftselect = 0;
            rightselect = 1;
            currentPage++;
            if (currentPage >= totalPages) {
                currentPage = totalPages - 1;
            }
        }


        if (choice == 27)
        {
            
            printMenu();
            break;

        }
    } while (1);
    

}









// ���� �˸� ���
void birthdayalarm(AddressBook* addressBook)
{
    //loadAddressBookFromFile(addressBook, "address.txt");
    draw_square4(95, 15, 40, 30);
    char today[128];
    time_t currentTime;
    time(&currentTime);  // ���� �ð� ������ ����
    struct tm* todayDate = localtime(&currentTime);

    //int birthcount = 0;

    
    // ������ ���� �� ������ ����
    sprintf(today, "%02d%02d", todayDate->tm_mon + 1, todayDate->tm_mday);

    int x = 80;
    int y = 2;
    
    int birthdayFound = 0; // ������ �´� ����ó�� ã�Ҵ��� ���θ� ��Ÿ���� �÷���

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        char birthdayMonthDay[5];
        // ������ -> ���Ϸ� ��ȯ�ؼ� ����
        strncpy(birthdayMonthDay, addressBook->contacts[i].birthday + 4, 4);
        birthdayMonthDay[4] = '\0';

        if (strcmp(birthdayMonthDay, today) == 0)
        {
            //birthcount++;
            
            gotoxy(x, y);
            printf("���� %s���� �����Դϴ�!\n", addressBook->contacts[i].name);
            birthdayFound = 1;
            y += 2;

        }
    }

    if (!birthdayFound)
    {
        gotoxy(x, y);
        printf("���� ������ ����� �����ϴ�!\n");
    }
}


// s   : �ʼ��� ���� ���ڿ�
// cho: �ʼ��� ���� ����
// size: cho ũ��
// ��ȯ��: �ʼ� ����
//�ʼ� �и� ���
int getinitials(const char* s, char* cho, int size)
{
    int i, j;
    int cnt, cho_index;
    char han[3] = { 0, };

    static char* cho_list[] = { "", //index: 1(��)~14(��)

         "��","��","��","��","��","��","��","��","��","��","��","��","��","��" };

    for (i = j = cnt = 0; s[i] && i < size; i++) {

        if ((unsigned char)s[i] & 0x80) {  // �ѱ��̸�...

            han[0] = s[i++];  // �ѱ�(2����Ʈ) ù ����Ʈ �и�

            han[1] = s[i];    // �ѱ� ���� ����Ʈ �и�

            // ����, �� ���� �������� Ȯ���ؼ� �ʼ� ����

            if (strcmp("��", han) <= 0 && strcmp("��", han) > 0)

                cho_index = 1;                               // ��
            
            else if (strcmp("��", han) > 0) cho_index = 2;  // ��

            else if (strcmp("��", han) > 0) cho_index = 3;  // ��

            else if (strcmp("��", han) > 0) cho_index = 4;  // ��

            else if (strcmp("��", han) > 0) cho_index = 5;  // ��

            else if (strcmp("��", han) > 0) cho_index = 6;  // ��

            else if (strcmp("��", han) > 0) cho_index = 7;  // ��

            else if (strcmp("��", han) > 0) cho_index = 8;  // ��

            else if (strcmp("��", han) > 0) cho_index = 9;  // ��

            else if (strcmp("ī", han) > 0) cho_index = 10; // ��

            else if (strcmp("Ÿ", han) > 0) cho_index = 11; // ��

            else if (strcmp("��", han) > 0) cho_index = 12; // ��

            else if (strcmp("��", han) > 0) cho_index = 13; // ��

            else cho_index = 14;                          // ��

            cho[j++] = cho_list[cho_index][0];        // �ʼ� ���� ����Ʈ ����

            cho[j++] = cho_list[cho_index][1];        // �ʼ� ���� ����Ʈ ����

            cnt++;   // �ʼ� ����

        }

    }

    cho[j] = 0; // ���ڿ� �� ���� ���� �߰�

    return cnt; // �ʼ��� ���� ����

}

// ����ó �˻� �Լ� (�ʼ� �Ǵ� ��ü �̸� �˻�)
void searchinitials(AddressBook* addressBook, Searchinitials* initials)
{
    int x = 30;
    int y = 8;
    loadAddressBookFromFile(addressBook, "address.txt");
    int x1 = 6;
    int y1 = 1;
    int choice = 0;
    int leftselect = 0;
    int rightselect = 1;
    int currentPage = 0;
    int contactsPerPage = 4;

    char search_initials[128];
    int found = 0;  // ����ó�� ã�Ҵ��� ���θ� ��Ÿ���� �÷���
    //����â
    draw_square4(47, 15, 50, 30);
    gotoxy(x - 3, y);
    printf("�˻��� �ʼ� �Ǵ� ��ü �̸��� �Է��ϼ���: ");
    gotoxy(x+8, y + 2);
    fgets(search_initials, sizeof(search_initials), stdin);
    search_initials[strcspn(search_initials, "\n")] = '\0';  // ���� ���� ����
    int j = 0;
    for (int i = 0; i < addressBook->contactCount; i++) {
        char contactInitials[128];
        // ����ó �̸��� �ʼ��� �����ϰ� ����
        int numInitials = getinitials(addressBook->contacts[i].name, contactInitials, sizeof(contactInitials));

        // �˻��� �ʼ� �Ǵ� ��ü �̸��� ����ó�� �ʼ� �Ǵ� ��ü �̸��� ���ԵǴ� ��츦 Ȯ��
        if (strstr(contactInitials, search_initials) != NULL || strstr(addressBook->contacts[i].name, search_initials) != NULL) {
           
            strcpy(initials->initials[j].name, addressBook->contacts[i].name);
            strcpy(initials->initials[j].number, addressBook->contacts[i].number);
            strcpy(initials->initials[j].address, addressBook->contacts[i].address);
            strcpy(initials->initials[j].birthday, addressBook->contacts[i].birthday);
            strcpy(initials->initials[j].relationship, addressBook->contacts[i].relationship);
            strcpy(initials->initials[j].addedDate.date, addressBook->contacts[i].addedDate.date);
            initials->initials[j].Favorite = addressBook->contacts[i].Favorite;
            j++;
            initials->contactCount++;
            found = 1;  // ����ó�� ã������ ǥ��
        }
    }
    if (found == 0)
    {
        gotoxy(x - 6, y + 3);
        printf("�׷� ������ ����� �����ϴ�.");
        //getchar();
    }
    int totalPages = (initials->contactCount + contactsPerPage - 1) / contactsPerPage;
    if (found == 1)
    { 
        do {
            system("cls");
            draw_square4(38, 15, 70, 30);
            nextredraw(leftselect, rightselect);
            gotoxy(34, 27);
            printf(" %d / %d\n", currentPage + 1, totalPages);

            // ����ó ���� ���
            int startIndex = currentPage * contactsPerPage;
            int endIndex = startIndex + contactsPerPage;

            // ���� ���������� ����� ������ ������ y �ʱ�ȭ
            y1 = 1;

            for (int i = startIndex; i < endIndex && i < initials->contactCount; ++i) {
                gotoxy(x1, y1);
                printf("�̸�: %s", initials->initials[i].name);
                if (initials->initials[i].Favorite == 1) {
                    printf(" ��"); // ���ã���̸� ���� ���
                }

                y1 += 1;
                gotoxy(x1, y1);
                printf("��ȭ��ȣ: %s", initials->initials[i].number);
                y1 += 1;
                gotoxy(x1, y1);
                printf("�ּ�: %s", initials->initials[i].address);
                y1 += 1;
                gotoxy(x1, y1);
                printf("����: %s", initials->initials[i].birthday);
                y1 += 1;
                gotoxy(x1, y1);
                printf("����: %s", initials->initials[i].relationship);
                y1 += 1;
                gotoxy(x1, y1);
                printf("��� ��¥: %s\n\n", initials->initials[i].addedDate.date);
                y1 += 2;
            }
            birthdayalarm(addressBook);
            choice = nextPagedraw();

            // ���⼭ nextPagedraw�� ��ȯ�� ���� ������� ���� ó���� ����
            if (choice == 60) {
                leftselect = 1;
                rightselect = 0;
                currentPage--;
                if (currentPage < 0) {
                    currentPage = 0;
                }
                // '<' ��ư�� ������ ��쿡 ���� ó��
                // ���� �������� ���ҽ�Ű�ų� ���� �������� ������ ����ϴ� ���� ����
            }
            else if (choice == 67) {
                leftselect = 0;
                rightselect = 1;
                currentPage++;
                if (currentPage >= totalPages) {
                    currentPage = totalPages - 1;
                }
            }


            if (choice == 27)
            {

                printMenu();
                break;

            }
        } while (1);
    }
    
}

//���ã�� �߰�
void addFavorite(AddressBook* addressBook)
{
    loadAddressBookFromFile(addressBook, "address.txt");

    char name[STRING_SIZE];
    gotoxy(X-2, Y);
    printf("���ã�� �߰��� �̸��� �Է����ּ���: \n");
    gotoxy(X-2, Y+2);
    printf("�Է� >> ");
    scanf("%s", &name);
    //rewind(stdin);
    int found = 0;

    for (int i = 0; i < addressBook->contactCount; i++ )
    {
        if (strcmp(addressBook->contacts[i].name, name) == 0)
        {
            addressBook->contacts[i].Favorite = 1;
            found = 1;
            break;
        }
    }
    if (found==1)
    {
        gotoxy(X, Y + 4);
        printf("���ã�Ⱑ �߰��Ǿ����ϴ�.");
        saveAddressBookToFileW(addressBook, "address.txt");
    }
    else
    {
        gotoxy(X, Y + 4);
        printf("�ش��ϴ� �̸��� �����ϴ�.\n");
    }
    getchar();
}

//���ã�� ����
void deleteFavorite(AddressBook* addressBook)
{
    loadAddressBookFromFile(addressBook, "address.txt");
    char name[STRING_SIZE];
    gotoxy(X - 2, Y);
    printf("���ã�� ������ �̸��� �Է����ּ���: ");
    gotoxy(X - 2, Y+2);
    printf("�Է�>>");
    scanf("%s", &name);
    
    int found = 0;
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].name, name) == 0) {
            found = 1;
            addressBook->contacts[i].Favorite = 0;
            break;
        }
    }
    if (found)
    {
        gotoxy(X - 2, Y + 4);
        printf("����ó�� ���ã�� ǥ�ð� ���ŵǾ����ϴ�.\n");
        saveAddressBookToFileW(addressBook, "address.txt");
    }
    else {
        gotoxy(X - 2, Y + 4);
        printf("�ش� �̸��� ����ó�� ã�� �� �����ϴ�.\n");
    }
    getchar();
}

//����ü �ʱ�ȭ �Լ�
void initialize(AddressBook* addressBook) {
    addressBook->contactCount = 0;
}

void searchfavorite(AddressBook* addressBook, SearchFavorite* searchFavorite)
{
    int x1 = 6;
    int y1 = 1;
    loadAddressBookFromFile(addressBook, "address.txt");
    int x = 6;
    int y = 1;
    int choice = 0;
    int leftselect = 0;
    int rightselect = 1;
    int currentPage = 0;
    int contactsPerPage = 4;

    int j = 0;

    // ó�� ȣ�� �� ù ��° �������� ����ó ������ ���

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (addressBook->contacts[i].Favorite == 1)
        {
            strcpy(searchFavorite->Favorite[j].name, addressBook->contacts[i].name);
            strcpy(searchFavorite->Favorite[j].address, addressBook->contacts[i].address);
            strcpy(searchFavorite->Favorite[j].address, addressBook->contacts[i].address);
            strcpy(searchFavorite->Favorite[j].birthday, addressBook->contacts[i].birthday);
            strcpy(searchFavorite->Favorite[j].relationship, addressBook->contacts[i].relationship);
            strcpy(searchFavorite->Favorite[j].addedDate.date, addressBook->contacts[i].addedDate.date);
            searchFavorite->Favorite[j].Favorite = 1;
            j++;
            searchFavorite->contactCount++;
        }
    }
    int totalPages = (searchFavorite->contactCount + contactsPerPage - 1) / contactsPerPage;
    draw_square4(38, 15, 70, 30);
    nextredraw(leftselect, rightselect);
    gotoxy(34, 27);
    printf(" %d / %d\n", currentPage + 1, totalPages);

    do {
        system("cls");
        draw_square4(38, 15, 70, 30);
        nextredraw(leftselect, rightselect);
        gotoxy(34, 27);
        printf(" %d / %d\n", currentPage + 1, totalPages);

        // ����ó ���� ���
        int startIndex = currentPage * contactsPerPage;
        int endIndex = startIndex + contactsPerPage;

        // ���� ���������� ����� ������ ������ y �ʱ�ȭ
        y1 = 1;

        for (int i = startIndex; i < endIndex && i < searchFavorite->contactCount; ++i) {
            if (searchFavorite->Favorite[i].Favorite == 1)
            {
                gotoxy(x1, y1);
                printf("�̸�: %s", searchFavorite->Favorite[i].name);
                if (searchFavorite->Favorite[i].Favorite == 1) {
                    printf(" ��"); // ���ã���̸� ���� ���
                }

                y1 += 1;
                gotoxy(x1, y1);
                printf("��ȭ��ȣ: %s", searchFavorite->Favorite[i].number);
                y1 += 1;
                gotoxy(x1, y1);
                printf("�ּ�: %s", searchFavorite->Favorite[i].address);
                y1 += 1;
                gotoxy(x1, y1);
                printf("����: %s", searchFavorite->Favorite[i].birthday);
                y1 += 1;
                gotoxy(x1, y1);
                printf("����: %s", searchFavorite->Favorite[i].relationship);
                y1 += 1;
                gotoxy(x1, y1);
                printf("��� ��¥: %s\n\n", searchFavorite->Favorite[i].addedDate.date);
                y1 += 2;
            }
        }
     
        birthdayalarm(addressBook);
        choice = nextPagedraw();

        // ���⼭ nextPagedraw�� ��ȯ�� ���� ������� ���� ó���� ����
        if (choice == 60) {
            leftselect = 1;
            rightselect = 0;
            currentPage--;
            if (currentPage < 0) {
                currentPage = 0;
            }
            // '<' ��ư�� ������ ��쿡 ���� ó��
            // ���� �������� ���ҽ�Ű�ų� ���� �������� ������ ����ϴ� ���� ����
        }
        else if (choice == 67) {
            leftselect = 0;
            rightselect = 1;
            currentPage++;
            if (currentPage >= totalPages) {
                currentPage = totalPages - 1;
            }
        }


        if (choice == 27)
        {
            printMenu();
            break;

        }
    } while (1);
}