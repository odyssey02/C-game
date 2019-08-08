// main.c
//
//2018 08 26
//
//���� : ����(�����쿡���� �����۵���)

#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

#define mapx 30	//���� x�� ����
#define mapy 30	//���� y�� ����

int move = 1;	//ó�� ������ �����̴� ����
int slen = 3;	//ó�� ������ ĳ������ ����
int sn[1300][2] = { {15,13},{15,14},{15,15},{15,16},{15,17} };//ĳ������ ���̺� ��ǥ����
int applexy[2];	//����� xy�� ����
int over = 0;	//���ӿ��� Ȯ�� ����

void mapset();	//�ʱ� �� ���� �Լ�
void pmove();	//ĳ���� ������ ��� �Լ�
void gotoxy(int x, int y); //������ ��ǥ�� Ŀ���� �ű�� �Լ�
void ranapple();	//������ ���� ��ġ ����
void appleeat();	//������ ȹ�� Ȯ��
void overtest();	//���ӿ��� ���� Ȯ��

int main()	// ���� �Լ�
{
	mapset();	//�ʼ���
	ranapple();	//�ʱ������ ����
	while (1)
	{
		pmove();
		appleeat();
		overtest();
		if (over == 1)
			return 0;
		Sleep(200);	//������ �ӵ��� �ٲܼ� ����
	}
}

void gotoxy(int x, int y)
{
	COORD Cur;
	Cur.X = x * 2;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}
void mapset()
{
	int i, j;
	for (i = 0; i < mapy; i++)
	{
		for (j = 0; j < mapx; j++)
		{
			if (i == 0)
				printf("��");
			else if (i == mapy - 1)
				printf("��");
			else
			{
				if (j == 0 || j == mapx - 1)
					printf("��");
				else
					printf("  ");
			}
		}
		printf("\n");
	}
	return;
}
void pmove()
{
	int i, im1[2], im2[2];	//���� ������ ���� ����
	char key;	//���� Ű�� �����ϴ� ����
	if (_kbhit())
	{
		key = _getch();
		switch (key)
		{
		case 'w':
			if (move != 3)
				move = 1;
			break;
		case 'a':
			if (move != 4)
				move = 2;
			break;
		case 's':
			if (move != 1)
				move = 3;
			break;
		case 'd':
			if (move != 2)
				move = 4;
			break;
		}
	}
	for (i = 0; i < slen; i++)	//ĳ���Ͱ� �̵��ϱ��� �ڽ��� ����� �κ�
	{
		gotoxy(sn[i][0], sn[i][1]);
		printf(" ");
	}
	for (i = 0; i < slen; i++)
	{
		if (i == 0) //�Ӹ� ������ �����ϴ� �κ�
		{
			im1[0] = sn[i][0];
			im1[1] = sn[i][1];
			if (move == 1)
				sn[i][1]--;
			else if (move == 2)
				sn[i][0]--;
			else if (move == 3)
				sn[i][1]++;
			else if (move == 4)
				sn[i][0]++;
		}
		else	//������ ������ ����ȭ
		{
			im2[0] = sn[i][0];
			im2[1] = sn[i][1];
			sn[i][0] = im1[0];
			sn[i][1] = im1[1];
			im1[0] = im2[0];
			im1[1] = im2[1];
		}
	}
	for (i = 0; i < slen; i++)	//ĳ���͸� �ٽ� ����ϴ� �κ�
	{
		gotoxy(sn[i][0], sn[i][1]);
		printf("��");
	}
}
void ranapple()
{
	int i;
	while (1)
	{
		int a = 0;
		srand(time(NULL));	//�׻� �ٸ� �������� �������� �ϴ� �����õ� ����
		applexy[0] = (rand() % (mapx - 2)) + 1;	//����� ���� x�� ����
		applexy[1] = (rand() % (mapy - 2)) + 1;	//����� ���� y�� ����
		for (i = 0; i < slen; i++)	//������ ��ǥ�� ĳ���Ͷ� ��ġ���� Ȯ��
		{
			if ((applexy[0] == sn[i][0]) && (applexy[1] == sn[i][1]))
			{
				a = 1;
				break;
			}
		}
		if (a == 0)	//�� ��ĥ������ �ݺ�
			break;
	}
	gotoxy(applexy[0], applexy[1]);	//����� ������ ��ǥ�� ���
	printf("��");
}
void appleeat()
{
	if ((sn[0][0] == applexy[0]) && (sn[0][1] == applexy[1]))	//����� ĳ������ �Ӹ��� ��ġ���� Ȯ��
	{
		slen++;	//ĳ������ ���̸� ������Ŵ
		ranapple();	//�ٸ����� ���ο� ����� ����
	}
}
void overtest()
{
	int i;
	if ((sn[0][0] == 0) || (sn[0][0] == (mapx - 1)) || (sn[0][1] == 0) || (sn[0][1] == (mapy - 1)))//���� ĳ���Ͱ� ���� ���� ����� ���
	{
		over = 1;	//������Ŵ
		return;	//�� �Լ� Ż��
	}
	for (i = 1; i < slen; i++)
	{
		if ((sn[0][0] == sn[i][0]) && (sn[0][1] == sn[i][1]))	//�ڽ��� ���̶� �������
		{
			over = 1;	//������Ŵ
			return;// ���Լ� Ż��
		}
	}
}
