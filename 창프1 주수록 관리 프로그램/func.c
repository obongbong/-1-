#include "address.h"
#define X 30
#define Y 4


//파일에 저장하기(파일의 끝에 연락처 정보 추가)
void saveAddressBookToFile(AddressBook* addressBook, const char* filename) {
    //FILE* openFile(filename, a);

    FILE* file = fopen(filename, "a");
    if (file == NULL) {
        perror("파일을 열 수 없습니다.\n");
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

//파일에 저장하기(파일에 새로 쓰기)
void saveAddressBookToFileW(AddressBook* addressBook, const char* filename) {

    //FILE* openFile(filename, w);

    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("파일을 열 수 없습니다.\n");
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

//파일 정보 불러오기(구조체에 저장)
void loadAddressBookFromFile(AddressBook* addressBook, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return;
    }

    // 수정된 파일 포맷에 맞게 데이터를 읽어옴
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
        printf("더 이상 연락처를 추가할 수 없습니다.\n");
        return;
    }
    //loadAddressBookFromFile(addressBook, "address.txt");
    int x = 30;
    int y = 4;
    gotoxy(x, y);

    fflush(stdin);
    printf("등록할 사람의 정보를 입력해주세요.\n");
    gotoxy(x, y+2);
    printf("이름: ");
    fgets(addressBook->contacts[addressBook->contactCount].name, STRING_SIZE, stdin);
    addressBook->contacts[addressBook->contactCount].name[strcspn(addressBook->contacts[addressBook->contactCount].name, "\n")] = '\0';

    gotoxy(x, y + 4);
    printf("전화번호: ");
    fgets(addressBook->contacts[addressBook->contactCount].number, STRING_SIZE, stdin);
    addressBook->contacts[addressBook->contactCount].number[strcspn(addressBook->contacts[addressBook->contactCount].number, "\n")] = '\0';

    gotoxy(x, y + 6);
    printf("주소: ");
    fgets(addressBook->contacts[addressBook->contactCount].address, STRING_SIZE, stdin);
    addressBook->contacts[addressBook->contactCount].address[strcspn(addressBook->contacts[addressBook->contactCount].address, "\n")] = '\0';

    gotoxy(x, y + 8);
    printf("생일: ");
    fgets(addressBook->contacts[addressBook->contactCount].birthday, STRING_SIZE, stdin);
    addressBook->contacts[addressBook->contactCount].birthday[strcspn(addressBook->contacts[addressBook->contactCount].birthday, "\n")] = '\0';

    gotoxy(x, y + 10);
    printf("관계: ");
    fgets(addressBook->contacts[addressBook->contactCount].relationship, STRING_SIZE, stdin);
    addressBook->contacts[addressBook->contactCount].relationship[strcspn(addressBook->contacts[addressBook->contactCount].relationship, "\n")] = '\0';

    addressBook->contacts[addressBook->contactCount].Favorite = 0;

    // 이름에서 초성 추출
    char initials[STRING_SIZE];
    int num_initials = getinitials(addressBook->contacts[addressBook->contactCount].name, initials, STRING_SIZE);
    strncpy(addressBook->contacts[addressBook->contactCount].initials, initials, STRING_SIZE);
    addressBook->contacts[addressBook->contactCount].initials[STRING_SIZE - 1] = '\0';

    // 현재 날짜를 추가된 날짜로 저장
    time_t currentTime;
    time(&currentTime);  // 현재 시간 정보를 얻음
    struct tm* localTime = localtime(&currentTime);

    // 현재 날짜를 "YYYY-MM-DD" 형식의 문자열로 변환하여 저장;
    sprintf(addressBook->contacts[addressBook->contactCount].addedDate.date,
        "%04d%02d%02d", localTime->tm_year + 1900, localTime->tm_mon + 1, localTime->tm_mday);

    // 새로운 연락처를 주소록에 추가
    addressBook->contactCount++;
    system("cls");
    draw_square2(20, 0, 56, 30);
    gotoxy(x+10, y + 4);
    printf("추가완료!\n");

    saveAddressBookToFile(addressBook, "address.txt");
}


//
//연락처 조회기능
// 주소록 조회기능(주소록에 저장된 정보를 출력하고 등록된 날짜도 함께 출력)
void displayContacts(AddressBook* addressBook, const char* filename) {
    int x = 6;
    int y = 1;
    int choice=0;

    do {
        choice = nextPagedraw();
        draw_square4(38, 15, 70, 30);
        // 여기서 nextPagedraw가 반환한 값을 기반으로 다음 처리를 수행
        if (choice == 60) {
            // '<' 버튼을 선택한 경우에 대한 처리
            // 현재 페이지를 감소시키거나 이전 페이지의 정보를 출력하는 등의 동작
        }
        else if (choice == 67) {
            // '>' 버튼을 선택한 경우에 대한 처리
            // 현재 페이지를 증가시키거나 다음 페이지의 정보를 출력하는 등의 동작
        }

        // 현재 페이지의 연락처 출력
        draw_square4(38, 15, 70, 30);
        // ... (이하 연락처 출력 코드 유지)
    } while (1);

    

    for (int i = 0; i < addressBook->contactCount; i++) {
        gotoxy(x, y);
        printf("이름: %s", addressBook->contacts[i].name);
        if (addressBook->contacts[i].Favorite == 1) {

            printf(" ★"); // 즐겨찾기이면 ★을 출력
        }
        
        y += 1;
        gotoxy(x, y);
        printf("전화번호: %s", addressBook->contacts[i].number);
        y += 1;
        gotoxy(x, y);
        printf("주소: %s", addressBook->contacts[i].address);
        y += 1;
        gotoxy(x, y);
        printf("생일: %s", addressBook->contacts[i].birthday);
        y += 1;
        gotoxy(x, y);
        printf("관계: %s", addressBook->contacts[i].relationship);
        y += 1;
        gotoxy(x, y);
        printf("등록 날짜: %s\n\n", addressBook->contacts[i].addedDate.date);
        y += 2;
        gotoxy(x, y);

        

    }

}


//삭제함수
void deleteContactByName(AddressBook* addressBook) {
    char nameToDelete[STRING_SIZE];
    int found = 0;  // 연락처를 찾았는지 여부를 나타내는 플래그

    gotoxy(X, Y);

    // 사용자로부터 삭제할 연락처의 이름 입력 받기
    printf("삭제할 연락처의 이름을 입력하세요: ");
    fgets(nameToDelete, STRING_SIZE, stdin);
    nameToDelete[strcspn(nameToDelete, "\n")] = '\0';  // 개행 문자 제거

    loadAddressBookFromFile(addressBook, "address.txt");
    gotoxy(X, Y + 2);

    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].name, nameToDelete) == 0) {
            // 연락처를 찾았으므로 해당 연락처를 제거하고 배열을 감소시킴
            for (int j = i; j < addressBook->contactCount - 1; j++) {
                addressBook->contacts[j] = addressBook->contacts[j + 1];
            }
            addressBook->contactCount--;
            found = 1;  // 연락처를 찾았음을 표시
            printf("연락처가 삭제되었습니다.\n");
            saveAddressBookToFileW(addressBook, "address.txt");  // 수정된 주소록을 파일에 저장
            return;  // 삭제 후 종료
        }
    }

    if (!found) {
        printf("해당 이름의 연락처를 찾을 수 없습니다.\n");
    }

}

//연락처 수정(미완성)
//수정 메뉴 선택기능 방향키 입력으로 선택하는걸로 바꾸는중
void modifyContact(AddressBook* addressBook) {

    char name[128];
    int num;

    int x = 40;
    int y = 8;

    

    //파일 데이터 불러오기
    loadAddressBookFromFile(addressBook, "address.txt");
    gotoxy(X, Y);
    
    printf("수정할 사람의 이름을 입력해주세요: ");
    gotoxy(X+ 6, Y + 2);
    scanf("%s", name);
    getchar();
    int found = 0;



    //이름 일치 확인
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].name, name) == 0)
        {
            found = 1;
            gotoxy(x, y);
            printf("1. 이름 \n");
            gotoxy(x, y + 2);
            printf("2. 전화번호 \n");
            gotoxy(x, y + 4);
            printf("3. 주소 \n");
            gotoxy(x, y + 6);
            printf("4. 생일 \n");
            gotoxy(x, y + 8);
            printf("5. 관계 \n");
            gotoxy(x, y + 10);
            printf("6. 즐겨찾기 \n");

            //getchar();
            gotoxy(x, y + 12);

            //키보드 방향키 입력
            int numchoice = Keyinput(x, y, y+10, y);

            switch (numchoice) {
            case 1:
                //이름
                system("cls");
                draw_square2(20, 0, 56, 30);
                gotoxy(x-4, y);
                printf("이름을 입력해주세요: ");
                fgets(addressBook->contacts[i].name, 128, stdin);
                addressBook->contacts[i].name[strcspn(addressBook->contacts[i].name, "\n")] = '\0';
                break;
                //전화번호
            case 2:
                system("cls");
                draw_square2(20, 0, 56, 30);
                gotoxy(x - 4, y+2);
                printf("전화번호를 입력해주세요: ");
                fgets(addressBook->contacts[i].number, 128, stdin);
                addressBook->contacts[i].number[strcspn(addressBook->contacts[i].number, "\n")] = '\0';
                break;
                //주소
            case 3:
                system("cls");
                draw_square2(20, 0, 56, 30);
                gotoxy(x - 4, y+4);
                printf("주소를 입력해주세요: ");
                fgets(addressBook->contacts[i].address, 128, stdin);
                addressBook->contacts[i].address[strcspn(addressBook->contacts[i].address, "\n")] = '\0';
                break;
                //생일
            case 4:
                system("cls");
                draw_square2(20, 0, 56, 30);
                gotoxy(x - 4, y+6);
                printf("생일을 입력해주세요: ");
                fgets(addressBook->contacts[i].birthday, 128, stdin);
                addressBook->contacts[i].birthday[strcspn(addressBook->contacts[i].birthday, "\n")] = '\0';
                break;
                //관계
            case 5:
                system("cls");
                draw_square2(20, 0, 56, 30);
                gotoxy(x - 4, y+8);
                printf("관계를 입력해주세요 : ");
                fgets(addressBook->contacts[i].relationship, 128, stdin);
                addressBook->contacts[i].relationship[strcspn(addressBook->contacts[i].relationship, "\n")] = '\0';
                break;
            case 6:
                system("cls");
                draw_square2(20, 0, 56, 30);
                gotoxy(x , y);
                printf("즐겨찾기 추가");
                gotoxy(x, y + 2);
                printf("즐겨찾기 삭제");
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
            printf("수정완료! \n");
            saveAddressBookToFileW(addressBook, "address.txt");  // Save the updated contact data to the file
            return;
        }
    }
    if (found == 0)
    {
        printf("이름을 찾지 못했습니다.");
    }
}

//관계 검색(부분 문자열 검색 O)
void searchRelation(AddressBook* addressBook, const char* filename)
{
    //파일정보 불러오기
    loadAddressBookFromFile(addressBook, "address.txt");

    printf("검색할 관계를 입력해주세요: ");
    char relationship[128];

    fgets(relationship, sizeof(relationship), stdin);

    int found = 0;

    //엔터키 지우기
    if (relationship[strlen(relationship) - 1] == '\n') {
        relationship[strlen(relationship) - 1] = '\0';
    }

    //관계 일치 확인
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strstr(addressBook->contacts[i].relationship, relationship) != NULL)
        {
            printf("이름: %s\n", addressBook->contacts[i].name);
            printf("전화번호: %s\n", addressBook->contacts[i].number);
            printf("주소: %s\n", addressBook->contacts[i].address);
            printf("생일: %s\n", addressBook->contacts[i].birthday);
            printf("관계: %s\n", addressBook->contacts[i].relationship);
            printf("등록 날짜: %s\n", addressBook->contacts[i].addedDate.date);
            printf("\n");
            
            found = 1;
        }

    }
    if (found == 0)
    {
        
        printf("그런 관계인 사람이 없습니다.");
    }

}
// 생일 알림 기능
void birthdayalarm(AddressBook* addressBook)
{
    loadAddressBookFromFile(addressBook, "address.txt");
    draw_square4(95, 15, 40, 30);
    char today[128];
    time_t currentTime;
    time(&currentTime);  // 현재 시간 정보를 얻음
    struct tm* todayDate = localtime(&currentTime);

    //int birthcount = 0;

    
    // 오늘의 월과 일 정보만 저장
    sprintf(today, "%02d%02d", todayDate->tm_mon + 1, todayDate->tm_mday);

    int x = 80;
    int y = 2;
    
    int birthdayFound = 0; // 생일이 맞는 연락처를 찾았는지 여부를 나타내는 플래그

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        char birthdayMonthDay[5];
        // 연월일 -> 월일로 변환해서 저장
        strncpy(birthdayMonthDay, addressBook->contacts[i].birthday + 4, 4);
        birthdayMonthDay[4] = '\0';

        if (strcmp(birthdayMonthDay, today) == 0)
        {
            //birthcount++;
            
            gotoxy(x, y);
            printf("오늘 %s님의 생일입니다!\n", addressBook->contacts[i].name);
            birthdayFound = 1;
            y += 2;

        }
    }

    if (!birthdayFound)
    {
        gotoxy(x, y);
        printf("오늘 생일인 사람이 없습니다!\n");
    }
}

//즐겨찾기 기능



// s   : 초성을 구할 문자열
// cho: 초성을 담을 공간
// size: cho 크기
// 반환값: 초성 개수
//초성 분리 기능
int getinitials(const char* s, char* cho, int size)

{

    int i, j;

    int cnt, cho_index;

    char han[3] = { 0, };

    static char* cho_list[] = { "", //index: 1(ㄱ)~14(ㅎ)

         "ㄱ","ㄴ","ㄷ","ㄹ","ㅁ","ㅂ","ㅅ","ㅇ","ㅈ","ㅊ","ㅋ","ㅌ","ㅍ","ㅎ" };



    for (i = j = cnt = 0; s[i] && i < size; i++) {

        if ((unsigned char)s[i] & 0x80) {  // 한글이면...

            han[0] = s[i++];  // 한글(2바이트) 첫 바이트 분리

            han[1] = s[i];    // 한글 다음 바이트 분리

            // 시작, 끝 글자 범위인지 확인해서 초성 구함

            if (strcmp("가", han) <= 0 && strcmp("나", han) > 0)

                cho_index = 1;                               // ㄱ

            else if (strcmp("다", han) > 0) cho_index = 2;  // ㄴ

            else if (strcmp("라", han) > 0) cho_index = 3;  // ㄷ

            else if (strcmp("마", han) > 0) cho_index = 4;  // ㄹ

            else if (strcmp("바", han) > 0) cho_index = 5;  // ㅁ

            else if (strcmp("사", han) > 0) cho_index = 6;  // ㅂ

            else if (strcmp("아", han) > 0) cho_index = 7;  // ㅅ

            else if (strcmp("자", han) > 0) cho_index = 8;  // ㅇ

            else if (strcmp("차", han) > 0) cho_index = 9;  // ㅈ

            else if (strcmp("카", han) > 0) cho_index = 10; // ㅊ

            else if (strcmp("타", han) > 0) cho_index = 11; // ㅋ

            else if (strcmp("파", han) > 0) cho_index = 12; // ㅌ

            else if (strcmp("하", han) > 0) cho_index = 13; // ㅍ

            else cho_index = 14;                          // ㅎ



            cho[j++] = cho_list[cho_index][0];        // 초성 상위 바이트 저장

            cho[j++] = cho_list[cho_index][1];        // 초성 하위 바이트 저장

            cnt++;   // 초성 개수

        }

    }

    cho[j] = 0; // 문자열 널 종료 문자 추가

    return cnt; // 초성을 구한 개수

}

// 연락처 검색 함수 (초성 또는 전체 이름 검색)
void searchinitials(AddressBook* addressBook) {
    
    loadAddressBookFromFile(addressBook, "address.txt");

    char search_initials[128];
    int found = 0;  // 연락처를 찾았는지 여부를 나타내는 플래그

    printf("검색할 초성 또는 전체 이름을 입력하세요: ");
    fgets(search_initials, sizeof(search_initials), stdin);
    search_initials[strcspn(search_initials, "\n")] = '\0';  // 개행 문자 제거

    for (int i = 0; i < addressBook->contactCount; i++) {
        char contactInitials[128];
        // 연락처 이름의 초성을 추출하고 저장
        int numInitials = getinitials(addressBook->contacts[i].name, contactInitials, sizeof(contactInitials));

        // 검색한 초성 또는 전체 이름이 연락처의 초성 또는 전체 이름에 포함되는 경우를 확인
        if (strstr(contactInitials, search_initials) != NULL || strstr(addressBook->contacts[i].name, search_initials) != NULL) {
            printf("이름: %s\n", addressBook->contacts[i].name);
            printf("전화번호: %s\n", addressBook->contacts[i].number);
            printf("주소: %s\n", addressBook->contacts[i].address);
            printf("생일: %s\n", addressBook->contacts[i].birthday);
            printf("관계: %s\n", addressBook->contacts[i].relationship);
            printf("등록 날짜: %s\n", addressBook->contacts[i].addedDate.date);
            printf("\n");
            found = 1;  // 연락처를 찾았음을 표시
        }
    }

    if (!found) {
        printf("일치하는 연락처를 찾을 수 없습니다.\n");
    }
}

//추가해야 될 기능들

//즐겨찾기 추가
void addFavorite(AddressBook* addressBook)
{
    loadAddressBookFromFile(addressBook, "address.txt");

    char name[STRING_SIZE];
    gotoxy(X-2, Y);
    printf("즐겨찾기 추가할 이름을 입력해주세요: \n");
    gotoxy(X-2, Y+2);
    printf("입력 >> ");
    scanf("%s", &name);

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
    if (found)
    {
        gotoxy(X, Y + 4);
        printf("즐겨찾기가 추가되었습니다.");
        saveAddressBookToFileW(addressBook, "address.txt");
    }
    else
    {
        gotoxy(X, Y + 4);
        printf("해당하는 이름이 없습니다.\n");
    }
}

//즐겨찾기 삭제
void deleteFavorite(AddressBook* addressBook)
{
    loadAddressBookFromFile(addressBook, "address.txt");
    char name[STRING_SIZE];
    gotoxy(X - 2, Y);
    printf("즐겨찾기 삭제할 이름을 입력해주세요: ");
    gotoxy(X - 2, Y+2);
    printf("입력>>");
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
        printf("연락처의 즐겨찾기 표시가 제거되었습니다.\n");
        saveAddressBookToFileW(addressBook, "address.txt");
        
    }
    else {
        gotoxy(X - 2, Y + 4);
        printf("해당 이름의 연락처를 찾을 수 없습니다.\n");
    }
}

//관계 정렬
void swap(Person* a, Person* b) {
    Person temp = *a;
    *a = *b;
    *b = temp;
}

int partition(Person contacts[], int low, int high)
{
    char pivot[STRING_SIZE];
    strcpy(pivot, contacts[high].relationship);
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        if (strcmp(contacts[j].relationship, pivot) < 0)
        {
            i++;
            swap(&contacts[i], &contacts[j]);
        }
    }
    swap(&contacts[i + 1], &contacts[high]);
    return (i + 1);
}

void quickSort(Person contacts[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(contacts, low, high);
        quickSort(contacts, low, pi - 1);
        quickSort(contacts, pi + 1, high);
    }
}

//이름 정렬


//구조체 초기화 함수
void initialize(AddressBook* addressBook) {
    addressBook->contactCount = 0;
}

//이름 중복 확인
void check_name(AddressBook* addressBook)
{
    loadAddressBookFromFile(&addressBook, "address.txt");
    
    

}

