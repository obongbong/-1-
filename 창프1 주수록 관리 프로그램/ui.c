#include "address.h"

enum ColorType {
	BLACK,  	//0
	darkBLUE,	//1
	DarkGreen,	//2
	darkSkyBlue,    //3
	DarkRed,  	//4
	DarkPurple,	//5
	DarkYellow,	//6
	GRAY,		//7
	DarkGray,	//8
	BLUE,		//9
	GREEN,		//10
	SkyBlue,	//11
	RED,		//12
	PURPLE,		//13
	YELLOW,		//14
	WHITE		//15
} COLOR;

void textcolor(int colorNum) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNum);
}

//���θ޴� �׸���
void printMenu()
{
	system("cls");
	//����ü �ʱ�ȭ
	initialize(&searchResult);
	initialize(&addressBook);
	initialize(&initials);
	initialize(&searchFavorite);
	loadAddressBookFromFile(&addressBook, "address.txt");
	//���� �˸�
	birthdayalarm(&addressBook);
	initialize(&addressBook);

	int x = 40;
	int y = 8;
	gotoxy(x, 2);
	printf("\033[1m�ּҷ� ���α׷�\033[0m\n");
	draw_square3();

	draw_square4(47, 15, 50, 30);
	
	gotoxy(x, y);
	printf("1. ����ó �߰�");
	gotoxy(x, y+2);
	printf("2. ����ó �˻�");
	gotoxy(x, y+4);
	printf("3. ����ó ��ȸ");
	gotoxy(x, y+6);
	printf("4. ����ó ����");
	gotoxy(x, y+8);
	printf("5. ����ó ����");
	gotoxy(x, y + 10);
	printf("6. ���ã��");
	gotoxy(x, y + 12);
	printf("7. ����");

	int menuChoice = Keyinput(x, y, MAX_Y, MIN_Y);

		switch (menuChoice)
		{
		case 1:
			system("cls");
			draw_square4(47, 15, 50, 30);
			addContact(&addressBook);
			break;
		case 2:
			system("cls");
			draw_square4(47, 15, 50, 30);
			gotoxy(x, y);
			printf("1. �̸�(�ʼ�) �˻�");
			gotoxy(x, y + 2);
			printf("2. ���� �˻�");
			int subChoice = Keyinput(x, y, MAX_Y - 10, MIN_Y);

			switch (subChoice)
			{
			case 1:
				system("cls");
				searchinitials(&addressBook, &initials);
				break;
			case 2:
				system("cls");
				searchRelation(&addressBook, "address.txt", &searchResult);
				break;
			}
			break;

		case 3:
			system("cls");
			draw_square4(47, 15, 50, 30);
			gotoxy(x, y);
			printf("1. ��� ����ó ��ȸ");
			gotoxy(x, y + 2);
			printf("2. ���ã�� ��ȸ");
			int subChoice3 = Keyinput(x, y, MAX_Y - 10, MIN_Y);
			switch (subChoice3)
			{
			case 1:
				system("cls");
				displayContacts(&addressBook, "address.txt");
				break;
			case 2:
				system("cls");
				searchfavorite(&addressBook, &searchFavorite);
			}

			break;
		case 4:
			system("cls");
			draw_square4(47, 15, 50, 30);
			modifyContact(&addressBook);
			break;
		case 5:
			system("cls");
			draw_square4(47, 15, 50, 30);
			deleteContactByName(&addressBook);
			break;
		case 6:
			system("cls");
			draw_square4(47, 15, 50, 30);
			gotoxy(x, y);
			printf("1. ���ã�� �߰�");
			gotoxy(x, y + 2);
			printf("2. �ٰ�ã�� ����");
			int subChoice2 = Keyinput(x, y, MAX_Y - 10, MIN_Y);
			switch (subChoice2)
			{
			case 1:
				system("cls");
				draw_square4(47, 15, 50, 30);
				addFavorite(&addressBook);
				break;
			case 2:
				system("cls");
				draw_square4(47, 15, 50, 30);
				deleteFavorite(&addressBook);
				break;
			}
			break;
		case 7:
			exit(0);
		}
}

// Ŀ�� ������ �Լ�
void HideConsoleCursor()
{
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.dwSize = 1; // Ŀ�� ũ��
	cursorInfo.bVisible = FALSE; // Ŀ�� ���� ����
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

int Keyinput(int x, int y, int max_y, int min_y)
{
	int POS = 0;

	int nkey = 0;
	HideConsoleCursor();

	gotoxy(x, y);

	while (1)
	{
		// ȭ��ǥ ���
		gotoxy(x - 2, y);
		printf("=>");

		if (_kbhit())
		{
			nkey = _getch();

			// ȭ��ǥ ��� ��ġ�� ����
			gotoxy(x - 2, y);
			printf("  ");

			if (nkey == ARROW)
			{
				nkey = _getch();
				switch (nkey)
				{
				case UP:
					if (y > min_y)
						y -= 2;
					break;
				case DOWN:
					if (y <max_y)
						y += 2;
					break;
				}
			}
			else if (nkey == 13) // ����Ű �ƽ�Ű�ڵ� 13
			{
				return (y - 8) / 2 + 1;
			}
		}
		gotoxy(x, y);
	}
}

void selectMenu(int x, int y)
{
	//if()
}

void gotoxy(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//�� �׸���
void draw_square()
{
	gotoxy(38, 1);
	for (int i = 1; i < 20; i++)
	{
		printf("-");
	}
	gotoxy(37, 2);
	printf("��");
	gotoxy(56, 2);
	printf("��");
	gotoxy(38, 3);
	for (int i = 1; i < 20; i++)
	{
		printf("-");
	}

}

void draw_square5(int x, int y, int width, int height, int selected) {
	
	// ���� �ؽ�Ʈ ���� ����
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	WORD originalColor = csbi.wAttributes;

	// Calculate the top-left corner coordinates
	int topLeftX = x - width / 2;
	int topLeftY = y - height / 2;

	// Draw the top border
	gotoxy(topLeftX, topLeftY);
	printf("��");
	for (int i = 1; i < width - 1; i++) {
		printf("��");
	}
	printf("��");

	// Draw the left and right borders
	for (int i = 1; i < height - 1; i++) {
		gotoxy(topLeftX, topLeftY + i);
		printf("��");
		gotoxy(topLeftX + width - 1, topLeftY + i);
		printf("��");
	}

	// Draw the bottom border
	gotoxy(topLeftX, topLeftY + height - 1);
	printf("��");
	for (int i = 1; i < width - 1; i++) {
		printf("��");
	}
	printf("��");
	// ���� ����
	if (selected == 1) {
		textcolor(WHITE);
		gotoxy(60, 27);
		printf("��");
		textcolor(RED);
		gotoxy(67, 27);
		printf("��");
	}
	else{
		textcolor(RED);
		gotoxy(60, 27);
		printf("��");
		textcolor(WHITE);
		gotoxy(67, 27);
		printf("��");
	}
	// ������ �������� ����
	textcolor(WHITE);
}

void draw_square4(int x, int y, int width, int height) {
	int topLeftX = x - width / 2;
	int topLeftY = y - height / 2;

	gotoxy(topLeftX, topLeftY);
	printf("��");
	for (int i = 1; i < width - 1; i++) {
		printf("��");
	}
	printf("��");

	for (int i = 1; i < height - 1; i++) {
		gotoxy(topLeftX, topLeftY + i);
		printf("��");
		gotoxy(topLeftX + width - 1, topLeftY + i);
		printf("��");
	}

	gotoxy(topLeftX, topLeftY + height - 1);
	printf("��");
	for (int i = 1; i < width - 1; i++) {
		printf("��");
	}
	printf("��");
}

void draw_square3() {



	gotoxy(38, 1);
	printf("������������������������������������");
	gotoxy(38, 2);
	printf("��");
	gotoxy(55, 2);
	printf("��");
	gotoxy(38, 3);
	printf("������������������������������������");

}

void draw_square2(int x, int y, int width, int height) {
	for (int i = 0; i < width; i++) {
		gotoxy(x + i, y);
		putchar('-');
		gotoxy(x + i, y + height - 1);
		putchar('-');
	}

	for (int i = 0; i < height; i++) {
		gotoxy(x, y + i);
		putchar('|');
		gotoxy(x + width - 1, y + i);
		putchar('|');
	}
}

void draw_sq(int x, int y)
{
	gotoxy(x, y);
	for (int i = 1; i < x; i++)
	{
		printf("-");
	}
	gotoxy(x - 1, y + 1);
	printf("l");
	gotoxy(x + 20, y + 1);
	printf("l");
	gotoxy(x, y + 2);
	for (int i = 1; i < x; i++)
	{
		printf("-");
	}
}

// ȭ���� ����� ���� �׸��� �Լ�
void nextredraw(int leftSelected, int rightSelected) {
	// ���� �ؽ�Ʈ ���� ����
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	WORD originalColor = csbi.wAttributes;

	// ���ο� UI�� �׸�
	draw_square5(60, 27, 5, 3, leftSelected);
	draw_square5(67, 27, 5, 3, rightSelected);

	// ������ �������� ����
	textcolor(WHITE);
}

int nextPagedraw() {
	int x = 67;
	int y = 27;
	int nkey = 0;
	int min_x = 60;
	int max_x = 67;
	int leftselect = 0;
	int rightselect = 1;
	int exit = 27;
	
	// �ʱ� ȭ�� �׸���
	nextredraw(0, 1);

	while (1) {
		if (_kbhit()) {
			nkey = _getch();


			gotoxy(x, y);

			if (nkey == ARROW) {
				nkey = _getch();
				switch (nkey) {
				case LEFT:
					if (max_x >= x && x >= min_x)
						x = 60;
					leftselect = 1;
					rightselect = 0;
					break;
				case RIGHT:
					if (min_x <= x && x <= max_x)
						x = 67;
					leftselect = 0;
					rightselect = 1;
					break;
				case 27:
					break;
				}
			}
			else if (nkey == 13) { // ����Ű �ƽ�Ű�ڵ� 13
				return x; //x�� 60�̸� <���� ���� ������ 67�̸� > ������ ���� ������
			}
			nextredraw(leftselect, rightselect);

			// ESC Ű�� �ԷµǾ����� Ȯ��

			if (nkey == 27) { // ESC Ű �ƽ�Ű�ڵ� 27
				//printf("esc �Է�");
				//system("cls");
				
				return exit;
				break;
			}
		}
	}
}

