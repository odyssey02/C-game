// main.c
//
//2018 08 26
//
//설명 : 게임(윈도우에서만 정상작동함)

#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

#define mapx 30	//맵의 x값 설정
#define mapy 30	//맵의 y값 설정

int move = 1;	//처음 설정된 움직이는 방향
int slen = 3;	//처음 설정된 캐릭터의 길이
int sn[1300][2] = { {15,13},{15,14},{15,15},{15,16},{15,17} };//캐릭터의 길이별 좌표저장
int applexy[2];	//사과의 xy값 저장
int over = 0;	//게임오버 확인 변수

void mapset();	//초기 맵 세팅 함수
void pmove();	//캐릭터 움직임 담당 함수
void gotoxy(int x, int y); //지정된 좌표로 커서를 옮기는 함수
void ranapple();	//아이템 생성 위치 생성
void appleeat();	//아이템 획득 확인
void overtest();	//게임오버 조건 확인

int main()	// 메인 함수
{
	mapset();	//맵세팅
	ranapple();	//초기아이템 세팅
	while (1)
	{
		pmove();
		appleeat();
		overtest();
		if (over == 1)
			return 0;
		Sleep(200);	//게임의 속도를 바꿀수 있음
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
				printf("■");
			else if (i == mapy - 1)
				printf("■");
			else
			{
				if (j == 0 || j == mapx - 1)
					printf("■");
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
	int i, im1[2], im2[2];	//변수 스왑을 위한 변수
	char key;	//누른 키를 저장하는 변수
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
	for (i = 0; i < slen; i++)	//캐릭터가 이동하기전 자신을 지우는 부분
	{
		gotoxy(sn[i][0], sn[i][1]);
		printf(" ");
	}
	for (i = 0; i < slen; i++)
	{
		if (i == 0) //머리 방향을 조정하는 부분
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
		else	//몸통의 움직임 동기화
		{
			im2[0] = sn[i][0];
			im2[1] = sn[i][1];
			sn[i][0] = im1[0];
			sn[i][1] = im1[1];
			im1[0] = im2[0];
			im1[1] = im2[1];
		}
	}
	for (i = 0; i < slen; i++)	//캐릭터를 다시 출력하는 부분
	{
		gotoxy(sn[i][0], sn[i][1]);
		printf("□");
	}
}
void ranapple()
{
	int i;
	while (1)
	{
		int a = 0;
		srand(time(NULL));	//항상 다른 랜덤값을 가지도록 하는 랜덤시드 변경
		applexy[0] = (rand() % (mapx - 2)) + 1;	//사과의 랜덤 x값 생성
		applexy[1] = (rand() % (mapy - 2)) + 1;	//사과의 랜덤 y값 생성
		for (i = 0; i < slen; i++)	//생성된 좌표가 캐릭터랑 겹치는지 확인
		{
			if ((applexy[0] == sn[i][0]) && (applexy[1] == sn[i][1]))
			{
				a = 1;
				break;
			}
		}
		if (a == 0)	//안 겹칠때까지 반복
			break;
	}
	gotoxy(applexy[0], applexy[1]);	//사과를 정해진 좌표에 출력
	printf("●");
}
void appleeat()
{
	if ((sn[0][0] == applexy[0]) && (sn[0][1] == applexy[1]))	//사과랑 캐릭터의 머리가 겹치는지 확인
	{
		slen++;	//캐릭터의 길이를 증가시킴
		ranapple();	//다른곳에 새로운 사과를 생성
	}
}
void overtest()
{
	int i;
	if ((sn[0][0] == 0) || (sn[0][0] == (mapx - 1)) || (sn[0][1] == 0) || (sn[0][1] == (mapy - 1)))//만약 캐릭터가 맵의 벽에 닿았을 경우
	{
		over = 1;	//오버시킴
		return;	//이 함수 탈출
	}
	for (i = 1; i < slen; i++)
	{
		if ((sn[0][0] == sn[i][0]) && (sn[0][1] == sn[i][1]))	//자신의 몸이랑 닿을경우
		{
			over = 1;	//오버시킴
			return;// 이함수 탈출
		}
	}
}
