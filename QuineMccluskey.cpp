#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<conio.h>
typedef struct strNum {   //숫자별로 구조체로 생성
	int num; //숫자
	char arr[4]; //숫자를 이진화
	int sellect; //숫자 선택했는지 안했는지 체크
}strNum; //구조체 선언
typedef struct QuickFirst {
	int firstNum;
	int secondNum;
	char arr[4];
	int sellect;
}QuickFirst;  // 첫번째 체인징비트 후 구조체선언
typedef struct QuickSecond { //두번째 체인징 비트 후 구조체
	int firstNum, secondNum, thirdNum, fourthNum;
	char arr[4];
	int sellect;
}QuickSecond;// 두번째 체인징비트 후 구조체선언
typedef struct QuickThird { //두번째 체인징 비트 후 구조체
	int firstNum, secondNum, thirdNum, fourthNum, fivethNum, sixthNum, seventhNum, eighthNum;
	char arr[4];
	int sellect;
}QuickThird;// 세번째 체인징비트 후 구조체선언
typedef struct QuickFourth {
	int firstNum, secondNum, thirdNum, fourthNum, fivethNum, sixthNum, seventhNum, eighthNum;
	int ninethNum, tenthNum, eleventhNum, twelvethNum, thirteenNum, fourteenNum, fifteenNum, sixteenNum;
	char arr[4];
	int sellect;
}QuickFourth;

strNum strArr[16]; //16개짜리 구조체 배열 생성
strNum strInfo[5][10]; // 1의 갯수별로 그룹화 하는 배열
QuickFirst quickArr[5][1000]; //Quine-McClusky 방식 (1단계) 배열
QuickSecond quickArr2[4][1000]; //quine-McClusky 방식 (2단계) 배열
QuickThird quickArr3[3][1000]; //quine-McClusky 방식 (3단계) 배열
QuickFourth quickArr4[2][1000]; //quine-McClusky 방식 (4단계) 배열 
int valueArr[16][16];  //EPI를 구하기 위한 테이블
int totalZero = 0, totalOne = 0, totalTwo = 0, totalThree = 0, totalFour = 0; //각 구조체 배열 크기 저장
char key = 77;
int projectPage = 0;  //다음 이전 설정
int staheight = 0, stawidth = 0; //테이블 크기 저장
int piArr[100]; //EPI 구하기위한 값저장배열
int stCount = 0; //pi배열의 크기 저장
int epiArr[100][100];  //
void input() { //구조체에 데이터 입력해놓기
	int subNum; //배열 숫자 이진화하기위해 잡아주는것
	for (int i = 0; i < 16; i++)
	{
		strArr[i].num = i;
		subNum = strArr[i].num;
		for (int j = 3; j >= 0; j--)
		{
			strArr[i].arr[j] = subNum % 2;
			subNum = subNum / 2;
		}
	}
}
void printSituation(int set) //화면출력확인용 
{
	int row = 0;
	int oneCount = 1;
	int width = stawidth;
	int height = 1;
	if (set == 1) //전체 출력!
	{
		printf("숫자\t이진수\n");
		for (int i = 0; i < 16; i++)
		{
			printf("%d\t", strArr[i].num);
			for (int j = 0; j < 4; j++)
			{
				if (strArr[i].arr[j] == 1 || strArr[i].arr[j] == 0)
					printf("%d", strArr[i].arr[j]);
				else
					printf("%c", strArr[i].arr[j]);
			}
			printf("\n");
		}

	}
	else if (set == 2)//선택된것만 출력
	{
		printf("숫자\t이진수\n");
		for (int i = 0; i < 16; i++)
		{
			if (strArr[i].sellect == 1)
			{
				printf("%d\t", strArr[i].num);
				for (int j = 0; j < 4; j++)
				{
					if (strArr[i].arr[j] == 1 || strArr[i].arr[j] == 0)
						printf("%d", strArr[i].arr[j]);
					else
						printf("%c", strArr[i].arr[j]);
				}
				printf("\n");
			}
		}

	}
	else if (set == 3)//그룹화 해서 출력
	{
		printf("숫자\t이진수\n");
		printf("\t0개\n"); //1의갯수 0개
		if (strInfo[0][0].sellect == 1)
		{
			printf("%d\t", strInfo[0][0].num);
			for (int j = 0; j < 4; j++)
			{
				if (strInfo[0][0].arr[j] == 1 || strInfo[0][0].arr[j] == 0)
					printf("%d", strInfo[0][0].arr[j]);
				else
					printf("%c", strInfo[0][0].arr[j]);
			}
			printf("\n");
		}

		for (int row = 1; row < 5; row++)
		{
			if (oneCount < 5)
			{
				printf("\t%d개\n", oneCount);//1의갯수 1개
				oneCount++;
			}
			for (int i = 0; i < 10 && strInfo[row][i].num != NULL; i++)
			{
				if (strInfo[row][i].sellect == 1)
				{
					printf("%d\t", strInfo[row][i].num);
					for (int j = 0; j < 4; j++)
					{
						if (strInfo[row][i].arr[j] == 1 || strInfo[row][i].arr[j] == 0)
							printf("%d", strInfo[row][i].arr[j]);
						else
							printf("%c", strInfo[row][i].arr[j]);
					}
					printf("\n");
				}
			}
		}
	}  // 그룹화후 프린트
	else if (set == 4)//퀵맥 1-1단계 하고 출력
	{
		printf("1차 체인징비트\n");
		printf("숫자\t\t이진수\n");
		for (int row = 0; row < 5; row++)
		{
			for (int i = 0; i < 1000, quickArr[row][i].firstNum + quickArr[row][i].secondNum != 0; i++)
			{
				printf("%d,%d          \t", quickArr[row][i].firstNum, quickArr[row][i].secondNum);
				for (int j = 0; j < 4; j++)
				{
					if (quickArr[row][i].arr[j] == 1 || quickArr[row][i].arr[j] == 0)
						printf("%d", quickArr[row][i].arr[j]);
					else
						printf("%c", quickArr[row][i].arr[j]);
				}
				printf("\n");
			}
			printf("---------------------------------------------------\n");
		}
		printf("\n");
	}  //1차체인징 비트 후 프린트
	else if (set == 5)//퀵맥 1-2단계 하고 출력
	{
		printf("2차 체인징비트\n");
		printf("숫자\t\t\t이진수\n");
		for (int row = 0; row < 4; row++)
		{
			for (int i = 0; i < 1000, quickArr2[row][i].firstNum != 0, quickArr2[row][i].thirdNum != 0; i++)
			{
				printf("%d,%d+%d,%d   \t\t", quickArr2[row][i].firstNum, quickArr2[row][i].secondNum, quickArr2[row][i].thirdNum, quickArr2[row][i].fourthNum);
				for (int j = 0; j < 4; j++)
				{
					if (quickArr2[row][i].arr[j] == 1 || quickArr2[row][i].arr[j] == 0)
						printf("%d", quickArr2[row][i].arr[j]);
					else
						printf("%c", quickArr2[row][i].arr[j]);
				}
				printf("\n");
			}
			printf("---------------------------------------------------\n");
		}

	}  // 2차체인징 비트 후 프린트
	else if (set == 6)
	{
		printf("3차 체인징비트\n");
		printf("숫자\t\t\t\t\t이진수\n");
		for (int row = 0; row < 3; row++)
		{
			for (int i = 0; i < 1000, quickArr3[row][i].firstNum != 0, quickArr3[row][i].fivethNum != 0; i++)
			{
				printf("%d,%d,%d,%d + %d,%d,%d,%d       \t\t", quickArr3[row][i].firstNum, quickArr3[row][i].secondNum, quickArr3[row][i].thirdNum, quickArr3[row][i].fourthNum, quickArr3[row][i].fivethNum, quickArr3[row][i].sixthNum, quickArr3[row][i].seventhNum, quickArr3[row][i].eighthNum);
				for (int j = 0; j < 4; j++)
				{
					if (quickArr3[row][i].arr[j] == 1 || quickArr3[row][i].arr[j] == 0)
						printf("%d", quickArr3[row][i].arr[j]);
					else
						printf("%c", quickArr3[row][i].arr[j]);
				}
				printf("\n");
			}
			printf("---------------------------------------------------\n");
		}

	}     //3차체인징 비트 후 프린트
	else if (set == 7)
	{
		printf("4차 체인징비트\n");
		printf("숫자\t\t\t\t\t\t이진수\n");
		for (int row = 0; row < 2; row++)
		{
			for (int i = 0; i < 1000, quickArr4[row][i].firstNum != 0, quickArr4[row][i].ninethNum != 0; i++)
			{
				printf("%d,%d,%d,%d,%d,%d,%d,%d + %d,%d,%d,%d,%d,%d,%d,%d \t\t", quickArr4[row][i].firstNum, quickArr4[row][i].secondNum, quickArr4[row][i].thirdNum, quickArr4[row][i].fourthNum, quickArr4[row][i].fivethNum, quickArr4[row][i].sixthNum, quickArr4[row][i].seventhNum, quickArr4[row][i].eighthNum, quickArr4[row][i].ninethNum, quickArr4[row][i].tenthNum, quickArr4[row][i].eleventhNum, quickArr4[row][i].twelvethNum, quickArr4[row][i].thirteenNum, quickArr4[row][i].fourteenNum, quickArr4[row][i].fifteenNum, quickArr4[row][i].sixteenNum);
				for (int j = 0; j < 4; j++)
				{
					if (quickArr4[row][i].arr[j] == 1 || quickArr4[row][i].arr[j] == 0)
						printf("%d", quickArr4[row][i].arr[j]);
					else
						printf("%c", quickArr4[row][i].arr[j]);
				}
				printf("\n");
			}
			printf("---------------------------------------------------\n");
		}

	}
	else if (set == 8) //테이블 출력!
	{
		printf("테이블\n");
		printf("숫자\t\t\t\t\t│");
		for (int x = 0; x < stawidth; x++)
		{
			printf("%d\t", valueArr[0][x]);
		}
		printf("\n");
		for (int row = 1; row < 5; row++)
		{
			for (int i = 0; i < 1000, strInfo[row][i].num != 0; i++)
			{
				if (strInfo[row][i].sellect == 1)
				{
					printf("%d\t\t\t\t\t│", strInfo[row][i]);
					for (int x = 0; x < stawidth; x++) {
						if (valueArr[height][x] == 100) printf("●\t");
						else if (valueArr[height][x] == 200) printf("○\t");
						else if (valueArr[height][x] == 300) printf("◎\t");
						else printf("\t");
					}
					height++;
					printf("\n");
				}
			}
		}
		for (int row = 0; row < 5; row++)
		{
			for (int i = 0; i < 1000, quickArr[row][i].firstNum + quickArr[row][i].secondNum != 0; i++)
			{
				if (quickArr[row][i].sellect == 0)
				{
					printf("%d,%d\t\t\t\t\t│", quickArr[row][i].firstNum, quickArr[row][i].secondNum);
					for (int x = 0; x < stawidth; x++) {
						if (valueArr[height][x] == 100) printf("●\t");
						else if (valueArr[height][x] == 200) printf("○\t");
						else if (valueArr[height][x] == 300) printf("◎\t");
						else printf("\t");
					}
					height++;
					printf("\n");
				}
			}
		}
		for (int row = 0; row < 4; row++)
		{
			for (int i = 0; i < 1000, quickArr2[row][i].firstNum != 0, quickArr2[row][i].thirdNum != 0; i++)
			{
				if (quickArr2[row][i].sellect == 0)
				{
					printf("%d,%d+%d,%d   \t\t\t\t│", quickArr2[row][i].firstNum, quickArr2[row][i].secondNum, quickArr2[row][i].thirdNum, quickArr2[row][i].fourthNum);
					for (int x = 0; x < stawidth; x++) {
						if (valueArr[height][x] == 100) printf("●\t");
						else if (valueArr[height][x] == 200) printf("○\t");
						else if (valueArr[height][x] == 300) printf("◎\t");
						else printf("\t");
					}
					height++;
					printf("\n");
				}
			}
		}
		for (int row = 0; row < 3; row++)
		{
			for (int i = 0; i < 1000, quickArr3[row][i].firstNum != 0, quickArr3[row][i].fivethNum != 0; i++)
			{
				if (quickArr3[row][i].sellect == 0)
				{
					printf("%d,%d,%d,%d + %d,%d,%d,%d\t\t\t│", quickArr3[row][i].firstNum, quickArr3[row][i].secondNum, quickArr3[row][i].thirdNum, quickArr3[row][i].fourthNum, quickArr3[row][i].fivethNum, quickArr3[row][i].sixthNum, quickArr3[row][i].seventhNum, quickArr3[row][i].eighthNum);
					for (int x = 0; x < stawidth; x++) {
						if (valueArr[height][x] == 100) printf("●\t");
						else if (valueArr[height][x] == 200) printf("○\t");
						else if (valueArr[height][x] == 300) printf("◎\t");
						else printf("\t");
					}
					height++;
					printf("\n");
				}
			}
		}
		for (int row = 0; row < 2; row++)
		{
			for (int i = 0; i < 1000, quickArr4[row][i].firstNum != 0, quickArr4[row][i].ninethNum != 0; i++)
			{
				if (quickArr4[row][i].sellect == 0)
				{
					printf("%d,%d,%d,%d,%d,%d,%d,%d + %d,%d,%d,%d,%d,%d,%d,%d \t│", quickArr4[row][i].firstNum, quickArr4[row][i].secondNum, quickArr4[row][i].thirdNum, quickArr4[row][i].fourthNum, quickArr4[row][i].fivethNum, quickArr4[row][i].sixthNum, quickArr4[row][i].seventhNum, quickArr4[row][i].eighthNum, quickArr4[row][i].ninethNum, quickArr4[row][i].tenthNum, quickArr4[row][i].eleventhNum, quickArr4[row][i].twelvethNum, quickArr4[row][i].thirteenNum, quickArr4[row][i].fourteenNum, quickArr4[row][i].fifteenNum, quickArr4[row][i].sixteenNum);
					for (int x = 0; x < stawidth; x++) {
						if (valueArr[height][x] == 100) printf("●\t");
						else if (valueArr[height][x] == 200) printf("○\t");
						else if (valueArr[height][x] == 300) printf("◎\t");
						else printf("\t");
					}
					height++;
					printf("\n");
				}
			}
		}
	}

}
void checkEPI() {   //EPI 체크함수 
	int width = stawidth;
	int height = staheight;
	int count = 0;
	for (int i = 0; i < width; i++)
	{
		for (int j = 1; j < height; j++)
		{
			if (valueArr[j][i] == 100) count++; //EPI테이블에서 체크된값이 있으면 카운트
		}
		if (count == 1)   //한개있으면 PI로 설정
		{
			for (int j = 1; j < height; j++)
			{

				if (valueArr[j][i] == 100)valueArr[j][i] = 200;
			}
			count = 0;
		}
		count = 0;
	}
}
void extractfun() {  //마지막 식 도출을 위한 함수
	int width = stawidth;
	int height = staheight;
	int count = 0, check2 = 0;
	int x2 = 0, y2 = 0;
	int count2 = 0;
	int pluscount = 0, plus = 0;
	for (int i = 1; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (valueArr[i][j] == 300 && count2 == 0)
			{
				for (int j2 = j; j2 < width; j2++)
				{
					if (valueArr[i][j2] == 300 && count2 == 0)
					{
						epiArr[x2][y2] = valueArr[0][j2];   //EPI 체크 한후 그 값들 배열에 저장
						y2++;
					}
				}
				x2++;
				y2 = 0;
				count2++;
			}
			else if (valueArr[i][j] == 200 && count2 == 0)
			{
				for (int j2 = 0; j2 < width; j2++)
				{
					if (valueArr[i][j2] == 100 || valueArr[i][j2] == 200)
					{
						epiArr[x2][y2] = valueArr[0][j2];//EPI 체크 한후 그 값들 배열에 저장
						y2++;
					}
				}
				x2++;
				y2 = 0;
				count2++;
			}
		}
		count2 = 0;
	}
	plus = x2;
	for (int row = 0; row < 5; row++)  //한개짜리가 EPI이면 소환
	{
		for (int i = 0; i < 1000, strInfo[row][i].num != 0; i++)
		{
			if (strInfo[row][i].sellect == 1) //초기에 선택 확인
			{
				for (int x2 = 0; x2 < 16 && epiArr[x2][0] + epiArr[x2][1] != 0; x2++)
				{
					if (strInfo[row][i].num == epiArr[x2][0])  //한개 짜리이므로 한개만 확인! 
					{
						pluscount++;
						for (int k = 0; k < 4; k++) //맞으면 출력
						{
							if (k == 0)
							{
								if (strInfo[row][i].arr[k] == 0)printf("A'");
								else if (strInfo[row][i].arr[k] == 1)printf("A");
								else if (strInfo[row][i].arr[k] == '-');
							}
							if (k == 1)
							{
								if (strInfo[row][i].arr[k] == 0)printf("B'");
								else if (strInfo[row][i].arr[k] == 1)printf("B");
								else if (strInfo[row][i].arr[k] == '-');
							}
							if (k == 2)
							{
								if (strInfo[row][i].arr[k] == 0)printf("C'");
								else if (strInfo[row][i].arr[k] == 1)printf("C");
								else if (strInfo[row][i].arr[k] == '-');
							}
							if (k == 3)
							{
								if (strInfo[row][i].arr[k] == 0)printf("D'");
								else if (strInfo[row][i].arr[k] == 1)printf("D");
								else if (strInfo[row][i].arr[k] == '-');
							}
						}
						if (pluscount != plus)
						{
							printf(" + ");
						}
					}
				}
			}
		}
	}
	for (int row = 0; row < 5; row++)  //EPI가 두개짜리 일때 확인
	{
		for (int i = 0; i < 1000, quickArr[row][i].firstNum + quickArr[row][i].secondNum != 0; i++)
		{
			if (quickArr[row][i].sellect == 0) //선택 됬는지 확인
			{
				for (int x2 = 0; x2 < 16 && epiArr[x2][0] + epiArr[x2][1] != 0; x2++)
				{
					if (quickArr[row][i].firstNum == epiArr[x2][0]) //2차 식이므로 2개 확인
					{
						check2++;
					}
					if (quickArr[row][i].secondNum == epiArr[x2][1])
					{
						check2++;
					}
					if (check2 == 2)
					{
						pluscount++;
						for (int k = 0; k < 4; k++)
						{
							if (k == 0)
							{
								if (quickArr[row][i].arr[k] == 0)printf("A'");
								else if (quickArr[row][i].arr[k] == 1)printf("A");
								else if (quickArr[row][i].arr[k] == '-');
							}
							if (k == 1)
							{
								if (quickArr[row][i].arr[k] == 0)printf("B'");
								else if (quickArr[row][i].arr[k] == 1)printf("B");
								else if (quickArr[row][i].arr[k] == '-');
							}
							if (k == 2)
							{
								if (quickArr[row][i].arr[k] == 0)printf("C'");
								else if (quickArr[row][i].arr[k] == 1)printf("C");
								else if (quickArr[row][i].arr[k] == '-');
							}
							if (k == 3)
							{
								if (quickArr[row][i].arr[k] == 0)printf("D'");
								else if (quickArr[row][i].arr[k] == 1)printf("D");
								else if (quickArr[row][i].arr[k] == '-');
							}
						}
						check2 = 0;
						if (pluscount != plus)
						{
							printf(" + ");
						}
						break;
					}
					check2 = 0;
				}
				check2 = 0;
			}
		}
	}
	for (int row = 0; row < 4; row++)
	{
		for (int i = 0; i < 1000, quickArr2[row][i].firstNum + quickArr2[row][i].secondNum != 0; i++)
		{
			if (quickArr2[row][i].sellect == 0) //똑같이 4개짜리 확인
			{
				for (int x2 = 0; x2 < 16 && epiArr[x2][0] + epiArr[x2][1] != 0; x2++)
				{
					if (quickArr2[row][i].firstNum == epiArr[x2][0])
					{
						check2++;
					}
					if (quickArr2[row][i].secondNum == epiArr[x2][1])
					{
						check2++;
					}
					if (quickArr2[row][i].thirdNum == epiArr[x2][2])
					{
						check2++;
					}
					if (quickArr2[row][i].fourthNum == epiArr[x2][3])
					{
						check2++;
					}
					if (check2 == 4)
					{
						pluscount++;
						for (int k = 0; k < 4; k++)
						{
							if (k == 0)
							{
								if (quickArr2[row][i].arr[k] == 0)printf("A'");
								else if (quickArr2[row][i].arr[k] == 1)printf("A");
								else if (quickArr2[row][i].arr[k] == '-');
							}
							if (k == 1)
							{
								if (quickArr2[row][i].arr[k] == 0)printf("B'");
								else if (quickArr2[row][i].arr[k] == 1)printf("B");
								else if (quickArr2[row][i].arr[k] == '-');
							}
							if (k == 2)
							{
								if (quickArr2[row][i].arr[k] == 0)printf("C'");
								else if (quickArr2[row][i].arr[k] == 1)printf("C");
								else if (quickArr2[row][i].arr[k] == '-');
							}
							if (k == 3)
							{
								if (quickArr2[row][i].arr[k] == 0)printf("D'");
								else if (quickArr2[row][i].arr[k] == 1)printf("D");
								else if (quickArr2[row][i].arr[k] == '-');
							}
						}
						check2 = 0;
						if (pluscount != plus)
						{
							printf(" + ");
						}
						break;
					}
					check2 = 0;
				}
				check2 = 0;
			}
		}
	}
	for (int row = 0; row < 3; row++)
	{
		for (int i = 0; i < 1000, quickArr3[row][i].firstNum + quickArr3[row][i].secondNum != 0; i++)
		{
			if (quickArr3[row][i].sellect == 0)  //8개짜리 확인
			{
				for (int x2 = 0; x2 < 16 && epiArr[x2][0] + epiArr[x2][1] != 0; x2++)
				{
					if (quickArr3[row][i].firstNum == epiArr[x2][0])
					{
						check2++;
					}
					if (quickArr3[row][i].secondNum == epiArr[x2][1])
					{
						check2++;
					}
					if (quickArr3[row][i].thirdNum == epiArr[x2][2])
					{
						check2++;
					}
					if (quickArr3[row][i].fourthNum == epiArr[x2][3])
					{
						check2++;
					}
					if (quickArr3[row][i].fivethNum == epiArr[x2][4])
					{
						check2++;
					}
					if (quickArr3[row][i].sixthNum == epiArr[x2][5])
					{
						check2++;
					}
					if (quickArr3[row][i].seventhNum == epiArr[x2][6])
					{
						check2++;
					}
					if (quickArr3[row][i].eighthNum == epiArr[x2][7])
					{
						check2++;
					}
					if (check2 == 8)
					{
						pluscount++;
						for (int k = 0; k < 4; k++)
						{

							if (k == 0)
							{
								if (quickArr3[row][i].arr[k] == 0)printf("A'");
								else if (quickArr3[row][i].arr[k] == 1)printf("A");
								else if (quickArr3[row][i].arr[k] == '-');
							}
							if (k == 1)
							{
								if (quickArr3[row][i].arr[k] == 0)printf("B'");
								else if (quickArr3[row][i].arr[k] == 1)printf("B");
								else if (quickArr3[row][i].arr[k] == '-');
							}
							if (k == 2)
							{
								if (quickArr3[row][i].arr[k] == 0)printf("C'");
								else if (quickArr3[row][i].arr[k] == 1)printf("C");
								else if (quickArr3[row][i].arr[k] == '-');
							}
							if (k == 3)
							{
								if (quickArr3[row][i].arr[k] == 0)printf("D'");
								else if (quickArr3[row][i].arr[k] == 1)printf("D");
								else if (quickArr3[row][i].arr[k] == '-');
							}
						}
						check2 = 0;
						if (pluscount != plus)
						{
							printf(" + ");
						}
						break;

					}
					check2 = 0;
				}
			}
		}
	}
	for (int row = 0; row < 2; row++)
	{
		for (int i = 0; i < 1000, quickArr4[row][i].firstNum + quickArr4[row][i].secondNum != 0; i++)
		{
			if (quickArr4[row][i].sellect == 0)
			{
				for (int x2 = 0; x2 < 16 && epiArr[x2][0] + epiArr[x2][1] != 0; x2++)   //16개짜리확인
				{
					if (quickArr4[row][i].firstNum == epiArr[x2][0])
					{
						check2++;
					}
					if (quickArr4[row][i].secondNum == epiArr[x2][1])
					{
						check2++;
					}
					if (quickArr4[row][i].thirdNum == epiArr[x2][2])
					{
						check2++;
					}
					if (quickArr4[row][i].fourthNum == epiArr[x2][3])
					{
						check2++;
					}
					if (quickArr4[row][i].fivethNum == epiArr[x2][4])
					{
						check2++;
					}
					if (quickArr4[row][i].sixthNum == epiArr[x2][5])
					{
						check2++;
					}
					if (quickArr4[row][i].seventhNum == epiArr[x2][6])
					{
						check2++;
					}
					if (quickArr4[row][i].eighthNum == epiArr[x2][7])
					{
						check2++;
					}
					if (quickArr4[row][i].ninethNum == epiArr[x2][8])
					{
						check2++;
					}
					if (quickArr4[row][i].tenthNum == epiArr[x2][9])
					{
						check2++;
					}
					if (quickArr4[row][i].eleventhNum == epiArr[x2][10])
					{
						check2++;
					}
					if (quickArr4[row][i].twelvethNum == epiArr[x2][11])
					{
						check2++;
					}
					if (quickArr4[row][i].thirteenNum == epiArr[x2][12])
					{
						check2++;
					}
					if (quickArr4[row][i].fourteenNum == epiArr[x2][13])
					{
						check2++;
					}
					if (quickArr4[row][i].fifteenNum == epiArr[x2][14])
					{
						check2++;
					}
					if (quickArr4[row][i].sixteenNum == epiArr[x2][15])
					{
						check2++;
					}
					if (check2 == 16)
					{
						pluscount++;
						for (int k = 0; k < 4; k++)
						{
							if (k == 0)
							{
								if (quickArr4[row][i].arr[k] == 0)printf("A'");
								else if (quickArr4[row][i].arr[k] == 1)printf("A");
								else if (quickArr4[row][i].arr[k] == '-');
							}
							if (k == 1)
							{
								if (quickArr4[row][i].arr[k] == 0)printf("B'");
								else if (quickArr4[row][i].arr[k] == 1)printf("B");
								else if (quickArr4[row][i].arr[k] == '-');
							}
							if (k == 2)
							{
								if (quickArr4[row][i].arr[k] == 0)printf("C'");
								else if (quickArr4[row][i].arr[k] == 1)printf("C");
								else if (quickArr4[row][i].arr[k] == '-');
							}
							if (k == 3)
							{
								if (quickArr4[row][i].arr[k] == 0 || k == 4)printf("D'");
								else if (quickArr4[row][i].arr[k] == 1 || k == 4)printf("D");
								else if (quickArr4[row][i].arr[k] == '-');
							}
						}
						check2 = 0;
						if (pluscount != plus)
						{
							printf(" + ");
						}
						break;
					}
					check2 = 0;
				}
			}
		}
	}
}
void checkaddEPI()  //EPI 체크 후 추가 EPI확인을 위한 함수 
{

	int width = stawidth;
	int height = staheight;
	int count = 0;
	int check = 0;
	int check2 = 0;
	int height2 = 1;
	for (int i = 1; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (valueArr[i][j] == 200)  // PI가 나왔던 것의 숫자들 전부다 배열에 저장
			{
				for (int j2 = 0; j2 < width; j2++)
				{
					if (valueArr[i][j2] == 100 || valueArr[i][j2] == 200)
					{
						for (int k2 = 0; k2 < count; k2++)
						{
							if (piArr[k2] == valueArr[0][j2])check2++;
						}
						if (check2 != 0)check2 = 0;
						else
						{
							piArr[count] = valueArr[0][j2];
							count++;
						}
					}
				}
			}

		}
	}
	stCount = count;
	for (int row = 0; row < 5; row++)
	{
		for (int i = 0; i < 1000, strInfo[row][i].num != 0; i++)
		{
			if (strInfo[row][i].sellect == 1)  //1개짜리에서 확인
			{
				for (int x = 0; x < count; x++)
				{
					if (strInfo[row][i].num == piArr[x])
					{
						check++;
					}
				}
				if (check != 0)
				{
					check = 0;
					height2++;
				}
				else
				{
					for (int x = 0; x < width; x++)
					{
						if (valueArr[height2][x] == 100)
							valueArr[height2][x] = 300;
					}
					height2++;
					check = 0;
				}
			}
		}
	}
	for (int row = 0; row < 5; row++)
	{
		for (int i = 0; i < 1000, quickArr[row][i].firstNum + quickArr[row][i].secondNum != 0; i++)
		{
			if (quickArr[row][i].sellect == 0)  //2개짜리에서 확인
			{
				for (int x = 0; x < count; x++)
				{
					if (quickArr[row][i].firstNum == piArr[x] || quickArr[row][i].secondNum == piArr[x])  //값이 한개라도 같다면 추가 EPI가 아니므로 check를 ++해줌
					{
						check++;
					}
				}
				if (check != 0) //아니면 2차원배열의 height2값증가로 다음 위치 비교를 위한 세팅
				{

					check = 0;
					height2++;
				}
				else  //하나도 없다면 추가 EPI이므로 설정되어있던곳 전부 추가EPI로 표시
				{
					for (int x = 0; x < width; x++)
					{
						if (valueArr[height2][x] == 100)
							valueArr[height2][x] = 300;
					}
					height2++;
					check = 0;
				}
			}
		}
	}
	for (int row = 0; row < 4; row++)
	{
		for (int i = 0; i < 1000, quickArr2[row][i].firstNum + quickArr2[row][i].secondNum != 0; i++)
		{
			if (quickArr2[row][i].sellect == 0)   //위에랑 똑같이 반복.
			{
				for (int x = 0; x < count; x++)
				{
					if (quickArr2[row][i].firstNum == piArr[x] || quickArr2[row][i].secondNum == piArr[x] || quickArr2[row][i].thirdNum == piArr[x] || quickArr2[row][i].fourthNum == piArr[x])
					{
						check++;
					}
				}
				if (check != 0)
				{
					check = 0;
					height2++;
				}
				else
				{
					for (int x = 0; x < width; x++)
					{
						if (valueArr[height2][x] == 100)
							valueArr[height2][x] = 300;
					}
					height2++;
					check = 0;
				}
			}
		}
	}
	for (int row = 0; row < 3; row++)
	{
		for (int i = 0; i < 1000, quickArr3[row][i].firstNum + quickArr3[row][i].secondNum != 0; i++)
		{
			if (quickArr3[row][i].sellect == 0)  //위에랑 똑같이 반복 
			{
				for (int x = 0; x < count; x++)
				{
					if (quickArr3[row][i].firstNum == piArr[x] || quickArr3[row][i].secondNum == piArr[x] || quickArr3[row][i].thirdNum == piArr[x] || quickArr3[row][i].fourthNum == piArr[x] || quickArr3[row][i].fivethNum == piArr[x] || quickArr3[row][i].sixthNum == piArr[x] || quickArr3[row][i].seventhNum == piArr[x] || quickArr3[row][i].eighthNum == piArr[x])
					{
						check++;
					}
				}
				if (check != 0)
				{
					check = 0;
					height2++;
				}
				else
				{
					for (int x = 0; x < width; x++)
					{
						if (valueArr[height2][x] == 100)
							valueArr[height2][x] = 300;
					}
					height2++;
					check = 0;
				}
			}
		}
	}
	for (int row = 0; row < 2; row++)  //위에랑 똑같이 반복
	{
		for (int i = 0; i < 1000, quickArr4[row][i].firstNum + quickArr4[row][i].secondNum != 0; i++)
		{
			if (quickArr4[row][i].sellect == 0)
			{
				for (int x = 0; x < count; x++)
				{
					if (quickArr4[row][i].firstNum == piArr[x] || quickArr4[row][i].secondNum == piArr[x] || quickArr4[row][i].thirdNum == piArr[x] || quickArr4[row][i].fourthNum == piArr[x] || quickArr4[row][i].fivethNum == piArr[x] || quickArr4[row][i].sixthNum == piArr[x] || quickArr4[row][i].seventhNum == piArr[x] || quickArr4[row][i].eighthNum == piArr[x] || quickArr4[row][i].ninethNum == piArr[x] || quickArr4[row][i].tenthNum == piArr[x] || quickArr4[row][i].eleventhNum == piArr[x] || quickArr4[row][i].twelvethNum == piArr[x] || quickArr4[row][i].thirteenNum == piArr[x] || quickArr4[row][i].fourteenNum == piArr[x] || quickArr4[row][i].fifteenNum == piArr[x] || quickArr4[row][i].sixteenNum == piArr[x])
					{
						check++;
					}
				}
				if (check != 0)
				{
					check = 0;
					height2++;
				}
				else
				{
					for (int x = 0; x < width; x++)
					{
						if (valueArr[height2][x] == 100)
							valueArr[height2][x] = 300;
					}
					height2++;
					check = 0;
				}
			}
		}
	}
}
void inputValue(int width) { //PI테이블에 값넣어주는 함수
	int height = 0;   //테이블 그리기위한 배열 좌표
	int check = 0;  //중복 체크를 위한 변수
	int temp;  //정렬을 위한 템프변수
	for (int row = 0; row < 5; row++)  //1개짜리 숫자부터 시작
	{
		for (int i = 0; i < 1000, strInfo[row][i].num != 0; i++)
		{
			if (strInfo[row][i].sellect == 1)  //선택됬을시 배열에 넣어주고 배열 다음주소로++
			{
				valueArr[height][width] = strInfo[row][i].num;
				width++;
			}
		}
	}
	for (int row = 0; row < 5; row++)  //마찬가지로 2개짜리 시작
	{
		for (int i = 0; i < 1000, quickArr[row][i].firstNum + quickArr[row][i].secondNum != 0; i++)
		{
			if (quickArr[row][i].sellect == 0) //선택됬을시
			{
				for (int total = 0; total < width; total++) {  //값들이 중복되는지 확인을 위해 포문으로 확인 
					if (quickArr[row][i].firstNum == valueArr[height][total]) //첫번째값
					{
						check++;
						break;
					}
				}
				if (check != 0)check = 0;
				else
				{
					valueArr[height][width] = quickArr[row][i].firstNum;
					width++;
				}
				for (int total = 0; total < width; total++) {  //2번째값
					if (quickArr[row][i].secondNum == valueArr[height][total])
					{
						check++;
						break;
					}
				}
				if (check != 0)check = 0;
				else
				{
					valueArr[height][width] = quickArr[row][i].secondNum;
					width++;
				}
			}
		}
	}
	for (int row = 0; row < 4; row++) //위에와 같이 반복
	{
		for (int i = 0; i < 1000, quickArr2[row][i].firstNum + quickArr2[row][i].secondNum != 0; i++)
		{
			if (quickArr2[row][i].sellect == 0)
			{
				for (int total = 0; total < width; total++) {
					if (quickArr2[row][i].firstNum == valueArr[height][total])
					{
						check++;
						break;
					}
				}
				if (check != 0)check = 0;
				else
				{
					valueArr[height][width] = quickArr2[row][i].firstNum;
					width++;
				}
				for (int total = 0; total < width; total++) {
					if (quickArr2[row][i].secondNum == valueArr[height][total])
					{
						check++;
						break;
					}
				}
				if (check != 0)check = 0;
				else
				{
					valueArr[height][width] = quickArr2[row][i].secondNum;
					width++;
				}
				for (int total = 0; total < width; total++) {
					if (quickArr2[row][i].thirdNum == valueArr[height][total])
					{
						check++;
						break;
					}
				}
				if (check != 0)check = 0;
				else
				{
					valueArr[height][width] = quickArr2[row][i].thirdNum;
					width++;
				}
				for (int total = 0; total < width; total++) {
					if (quickArr2[row][i].fourthNum == valueArr[height][total])
					{
						check++;
						break;
					}
				}
				if (check != 0)check = 0;
				else
				{
					valueArr[height][width] = quickArr2[row][i].fourthNum;
					width++;
				}
			}
		}
	}
	for (int row = 0; row < 3; row++)//위에와 같이 반복
	{
		for (int i = 0; i < 1000, quickArr3[row][i].firstNum + quickArr3[row][i].secondNum != 0; i++)
		{
			if (quickArr3[row][i].sellect == 0)
			{
				for (int total = 0; total < width; total++) {
					if (quickArr3[row][i].firstNum == valueArr[height][total])
					{
						check++;
						break;
					}
				}
				if (check != 0)check = 0;
				else
				{
					valueArr[height][width] = quickArr3[row][i].firstNum;
					width++;
				}
				for (int total = 0; total < width; total++) {
					if (quickArr3[row][i].secondNum == valueArr[height][total])
					{
						check++;
						break;
					}
				}
				if (check != 0)check = 0;
				else
				{
					valueArr[height][width] = quickArr3[row][i].secondNum;
					width++;
				}
				for (int total = 0; total < width; total++) {
					if (quickArr3[row][i].thirdNum == valueArr[height][total])
					{
						check++;
						break;
					}
				}
				if (check != 0)check = 0;
				else
				{
					valueArr[height][width] = quickArr3[row][i].thirdNum;
					width++;
				}
				for (int total = 0; total < width; total++) {
					if (quickArr3[row][i].fourthNum == valueArr[height][total])
					{
						check++;
						break;
					}
				}
				if (check != 0)check = 0;
				else
				{
					valueArr[height][width] = quickArr3[row][i].fourthNum;
					width++;
				}
				for (int total = 0; total < width; total++) {
					if (quickArr3[row][i].fivethNum == valueArr[height][total])
					{
						check++;
						break;
					}
				}
				if (check != 0)check = 0;
				else
				{
					valueArr[height][width] = quickArr3[row][i].fivethNum;
					width++;
				}
				for (int total = 0; total < width; total++) {
					if (quickArr3[row][i].sixthNum == valueArr[height][total])
					{
						check++;
						break;
					}
				}
				if (check != 0)check = 0;
				else
				{
					valueArr[height][width] = quickArr3[row][i].sixthNum;
					width++;
				}
				for (int total = 0; total < width; total++) {
					if (quickArr3[row][i].seventhNum == valueArr[height][total])
					{
						check++;
						break;
					}
				}
				if (check != 0)check = 0;
				else
				{
					valueArr[height][width] = quickArr3[row][i].seventhNum;
					width++;
				}
				for (int total = 0; total < width; total++) {
					if (quickArr3[row][i].eighthNum == valueArr[height][total])
					{
						check++;
						break;
					}
				}
				if (check != 0)check = 0;
				else
				{
					valueArr[height][width] = quickArr3[row][i].eighthNum;
					width++;
				}
			}
		}
	}
	for (int row = 0; row < 2; row++) //위에와 같이 반복
	{
		for (int i = 0; i < 1000, quickArr4[row][i].firstNum + quickArr4[row][i].secondNum != 0; i++)
		{
			if (quickArr4[row][i].sellect == 0)
			{
				for (int total = 0; total < width; total++) {
					if (quickArr4[row][i].firstNum == valueArr[height][total])
					{
						check++;
						break;
					}
				}
				if (check != 0)check = 0;
				else
				{
					valueArr[height][width] = quickArr4[row][i].firstNum;
					width++;
				}
				for (int total = 0; total < width; total++) {
					if (quickArr4[row][i].secondNum == valueArr[height][total])
					{
						check++;
						break;
					}
				}
				if (check != 0)check = 0;
				else
				{
					valueArr[height][width] = quickArr4[row][i].secondNum;
					width++;
				}
				for (int total = 0; total < width; total++) {
					if (quickArr4[row][i].thirdNum == valueArr[height][total])
					{
						check++;
						break;
					}
				}
				if (check != 0)check = 0;
				else
				{
					valueArr[height][width] = quickArr4[row][i].thirdNum;
					width++;
				}
				for (int total = 0; total < width; total++) {
					if (quickArr4[row][i].fourthNum == valueArr[height][total])
					{
						check++;
						break;
					}
				}
				if (check != 0)check = 0;
				else
				{
					valueArr[height][width] = quickArr4[row][i].fourthNum;
					width++;
				}
				for (int total = 0; total < width; total++) {
					if (quickArr4[row][i].fivethNum == valueArr[height][total])
					{
						check++;
						break;
					}
				}
				if (check != 0)check = 0;
				else
				{
					valueArr[height][width] = quickArr4[row][i].fivethNum;
					width++;
				}
				for (int total = 0; total < width; total++) {
					if (quickArr4[row][i].sixthNum == valueArr[height][total])
					{
						check++;
						break;
					}
				}
				if (check != 0)check = 0;
				else
				{
					valueArr[height][width] = quickArr4[row][i].sixthNum;
					width++;
				}
				for (int total = 0; total < width; total++) {
					if (quickArr4[row][i].seventhNum == valueArr[height][total])
					{
						check++;
						break;
					}
				}
				if (check != 0)check = 0;
				else
				{
					valueArr[height][width] = quickArr4[row][i].seventhNum;
					width++;
				}
				for (int total = 0; total < width; total++) {
					if (quickArr4[row][i].eighthNum == valueArr[height][total])
					{
						check++;
						break;
					}
				}
				if (check != 0)check = 0;
				else
				{
					valueArr[height][width] = quickArr4[row][i].eighthNum;
					width++;
				}for (int total = 0; total < width; total++) {
					if (quickArr4[row][i].ninethNum == valueArr[height][total])
					{
						check++;
						break;
					}
				}
				if (check != 0)check = 0;
				else
				{
					valueArr[height][width] = quickArr4[row][i].ninethNum;
					width++;
				}
				for (int total = 0; total < width; total++) {
					if (quickArr4[row][i].tenthNum == valueArr[height][total])
					{
						check++;
						break;
					}
				}
				if (check != 0)check = 0;
				else
				{
					valueArr[height][width] = quickArr4[row][i].tenthNum;
					width++;
				}
				for (int total = 0; total < width; total++) {
					if (quickArr4[row][i].eleventhNum == valueArr[height][total])
					{
						check++;
						break;
					}
				}
				if (check != 0)check = 0;
				else
				{
					valueArr[height][width] = quickArr4[row][i].eleventhNum;
					width++;
				}
				for (int total = 0; total < width; total++) {
					if (quickArr4[row][i].twelvethNum == valueArr[height][total])
					{
						check++;
						break;
					}
				}
				if (check != 0)check = 0;
				else
				{
					valueArr[height][width] = quickArr4[row][i].twelvethNum;
					width++;
				}
				for (int total = 0; total < width; total++) {
					if (quickArr4[row][i].thirteenNum == valueArr[height][total])
					{
						check++;
						break;
					}
				}
				if (check != 0)check = 0;
				else
				{
					valueArr[height][width] = quickArr4[row][i].thirteenNum;
					width++;
				}
				for (int total = 0; total < width; total++) {
					if (quickArr4[row][i].fourteenNum == valueArr[height][total])
					{
						check++;
						break;
					}
				}
				if (check != 0)check = 0;
				else
				{
					valueArr[height][width] = quickArr4[row][i].fourteenNum;
					width++;
				}
				for (int total = 0; total < width; total++) {
					if (quickArr4[row][i].fifteenNum == valueArr[height][total])
					{
						check++;
						break;
					}
				}
				if (check != 0)check = 0;
				else
				{
					valueArr[height][width] = quickArr4[row][i].fifteenNum;
					width++;
				}
				for (int total = 0; total < width; total++) {
					if (quickArr4[row][i].sixteenNum == valueArr[height][total])
					{
						check++;
						break;
					}
				}
				if (check != 0)check = 0;
				else
				{
					valueArr[height][width] = quickArr4[row][i].sixteenNum;
					width++;
				}
			}
		}
	}
	for (int i = 0; i < width - 1; i++)  //값 정렬
	{
		for (int j = i + 1; j < width; j++)
		{
			if (valueArr[0][i] > valueArr[0][j])
			{
				temp = valueArr[0][i];
				valueArr[0][i] = valueArr[0][j];
				valueArr[0][j] = temp;
			}
		}
	}
	stawidth = width;
}
void insertValue()
{
	int height = 0, width = 0;   //테이블 그리기위한 배열 좌표
	int check = 0;  //중복 체크를 위한 변수
	if (strInfo[0][0].sellect == 1) //0이 선택됬을시 0을 테이블에 넣어주고 시작
	{
		valueArr[height][width] = strInfo[0][0].sellect;
		width++;
		inputValue(width);
	}
	else  //안됬을시 그냥 시작
	{
		inputValue(width);
	}
}
void makingTable() {  //테이블에 값체크 및 정리
	int width = stawidth;
	int height = 1;
	for (int row = 0; row < 5; row++) //테이블에 값들을보고 표시해주기 위해 시작 1개짜리부터
	{
		for (int i = 0; i < 1000, strInfo[row][i].num != 0; i++)
		{
			if (strInfo[row][i].sellect == 1) //1개짜리 선택됬을시
			{
				for (int x = 0; x < width; x++)
				{
					if (strInfo[row][i].num == valueArr[0][x]) {  //그 숫자와 선택된 값들의 위치 가 같다면 그자리 에 표시
						valueArr[height][x] = 100;
					}
				}
				height++;
			}
		}
	}
	for (int row = 0; row < 5; row++) //위와 반복
	{
		for (int i = 0; i < 1000, quickArr[row][i].firstNum + quickArr[row][i].secondNum != 0; i++)
		{
			if (quickArr[row][i].sellect == 0)
			{
				for (int x = 0; x < width; x++)
				{
					if (quickArr[row][i].firstNum == valueArr[0][x] || quickArr[row][i].secondNum == valueArr[0][x])
					{
						valueArr[height][x] = 100;
					}
				}
				height++;
			}
		}
	}
	for (int row = 0; row < 4; row++) //위와 반복
	{
		for (int i = 0; i < 1000, quickArr2[row][i].firstNum + quickArr2[row][i].secondNum != 0; i++)
		{
			if (quickArr2[row][i].sellect == 0)
			{
				for (int x = 0; x < width; x++)
				{
					if (quickArr2[row][i].firstNum == valueArr[0][x] || quickArr2[row][i].secondNum == valueArr[0][x] || quickArr2[row][i].thirdNum == valueArr[0][x] || quickArr2[row][i].fourthNum == valueArr[0][x])
					{
						valueArr[height][x] = 100;
					}
				}
				height++;
			}
		}
	}
	for (int row = 0; row < 3; row++) //위와 반복
	{
		for (int i = 0; i < 1000, quickArr3[row][i].firstNum + quickArr3[row][i].secondNum != 0; i++)
		{
			if (quickArr3[row][i].sellect == 0)
			{
				for (int x = 0; x < width; x++)
				{
					if (quickArr3[row][i].firstNum == valueArr[0][x] || quickArr3[row][i].secondNum == valueArr[0][x] || quickArr3[row][i].thirdNum == valueArr[0][x] || quickArr3[row][i].fourthNum == valueArr[0][x] || quickArr3[row][i].fivethNum == valueArr[0][x] || quickArr3[row][i].sixthNum == valueArr[0][x] || quickArr3[row][i].seventhNum == valueArr[0][x] || quickArr3[row][i].eighthNum == valueArr[0][x])
					{
						valueArr[height][x] = 100;
					}
				}
				height++;
			}
		}
	}
	for (int row = 0; row < 2; row++) //위와 반복
	{
		for (int i = 0; i < 1000, quickArr4[row][i].firstNum + quickArr4[row][i].secondNum != 0; i++)
		{
			if (quickArr4[row][i].sellect == 0)
			{
				for (int x = 0; x < width; x++)
				{
					if (quickArr4[row][i].firstNum == valueArr[0][x] || quickArr4[row][i].secondNum == valueArr[0][x] || quickArr4[row][i].thirdNum == valueArr[0][x] || quickArr4[row][i].fourthNum == valueArr[0][x] || quickArr4[row][i].fivethNum == valueArr[0][x] || quickArr4[row][i].sixthNum == valueArr[0][x] || quickArr4[row][i].seventhNum == valueArr[0][x] || quickArr4[row][i].eighthNum == valueArr[0][x])
					{
						valueArr[height][x] = 100;
					}
					if (quickArr4[row][i].ninethNum == valueArr[0][x] || quickArr4[row][i].tenthNum == valueArr[0][x] || quickArr4[row][i].eleventhNum == valueArr[0][x] || quickArr4[row][i].twelvethNum == valueArr[0][x] || quickArr4[row][i].thirteenNum == valueArr[0][x] || quickArr4[row][i].fourteenNum == valueArr[0][x] || quickArr4[row][i].fifteenNum == valueArr[0][x] || quickArr4[row][i].sixteenNum == valueArr[0][x])
					{
						valueArr[height][x] = 100;
					}
				}
				height++;
			}
		}
	}
	staheight = height;
}
void grouping() //그룹화 하는 과정
{
	totalZero = 0, totalOne = 0, totalTwo = 0, totalThree = 0, totalFour = 0;
	int total;
	/*for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			strInfo[i][j].sellect = 0;
		}
	}*/
	for (int i = 0; i < 16; i++)
	{
		total = 0;
		for (int j = 0; j < 4; j++)
		{
			total += strArr[i].arr[j];
		}
		if (total == 0 && strArr[i].sellect == 1)
		{

			strInfo[0][totalZero] = strArr[i];
			totalZero++;
		}
		else if (total == 1 && strArr[i].sellect == 1)
		{

			strInfo[1][totalOne] = strArr[i];
			totalOne++;
		}
		else if (total == 2 && strArr[i].sellect == 1)
		{
			strInfo[2][totalTwo] = strArr[i];
			totalTwo++;
		}
		else if (total == 3 && strArr[i].sellect == 1)
		{
			strInfo[3][totalThree] = strArr[i];
			totalThree++;
		}
		else if (total == 4 && strArr[i].sellect == 1)
		{
			strInfo[4][totalFour] = strArr[i];
			totalFour++;
		}
	}
}
void firstQuick() {//Quine-McClusky 방식 (1단계) 
	int count = 0;
	int row = 0;
	int subZero = totalZero, subOne = totalOne, subTwo = totalTwo, subThree = totalThree, subFour = totalFour;  //배열들 크기를 대신 받아서 확인
	totalZero = 0, totalOne = 0, totalTwo = 0, totalThree = 0, totalFour = 0;

	for (int i = 0; i < subZero; i++)
	{
		for (int j = 0; j < subOne; j++)
		{
			for (int k = 0; k < 4; k++)   //이진화 배열들의 다른지 맞는지 확인
			{
				if (strInfo[row][i].arr[k] != strInfo[row + 1][j].arr[k]) count++;
			}
			if (count == 1)  //한개다르면 수행
			{
				strInfo[row][i].sellect = 2;
				strInfo[row + 1][j].sellect = 2;
				for (int k = 0; k < 4; k++)
				{
					if (strInfo[row][i].arr[k] != strInfo[row + 1][j].arr[k]) quickArr[row][totalZero].arr[k] = '-';
					else
						quickArr[row][totalZero].arr[k] = strInfo[row][i].arr[k];
				}
				quickArr[row][totalZero].firstNum = strInfo[row][i].num;
				quickArr[row][totalZero].secondNum = strInfo[row + 1][j].num;
				count = 0;
				totalZero++;

			}
			count = 0;
		}
	}
	row++;
	count = 0;
	for (int i = 0; i < subOne; i++)
	{
		for (int j = 0; j < subTwo; j++)
		{
			for (int k = 0; k < 4; k++)   //이진화 배열들의 다른지 맞는지 확인
			{
				if (strInfo[row][i].arr[k] != strInfo[row + 1][j].arr[k]) count++;
			}
			if (count == 1)  //한개다르면 수행
			{
				strInfo[row][i].sellect = 2;
				strInfo[row + 1][j].sellect = 2;
				for (int k = 0; k < 4; k++)
				{
					if (strInfo[row][i].arr[k] != strInfo[row + 1][j].arr[k]) quickArr[row][totalOne].arr[k] = '-';
					else
						quickArr[row][totalOne].arr[k] = strInfo[row][i].arr[k];
				}
				quickArr[row][totalOne].firstNum = strInfo[row][i].num;
				quickArr[row][totalOne].secondNum = strInfo[row + 1][j].num;
				count = 0;
				totalOne++;
			}
			count = 0;
		}
	}
	row++;
	count = 0;
	for (int i = 0; i < subTwo; i++)
	{
		for (int j = 0; j < subThree; j++)
		{
			for (int k = 0; k < 4; k++)   //이진화 배열들의 다른지 맞는지 확인
			{
				if (strInfo[row][i].arr[k] != strInfo[row + 1][j].arr[k]) count++;
			}
			if (count == 1)  //한개다르면 수행
			{
				strInfo[row][i].sellect = 2;
				strInfo[row + 1][j].sellect = 2;
				for (int k = 0; k < 4; k++)
				{
					if (strInfo[row][i].arr[k] != strInfo[row + 1][j].arr[k]) quickArr[row][totalTwo].arr[k] = '-';
					else
						quickArr[row][totalTwo].arr[k] = strInfo[row][i].arr[k];
				}
				quickArr[row][totalTwo].firstNum = strInfo[row][i].num;
				quickArr[row][totalTwo].secondNum = strInfo[row + 1][j].num;
				count = 0;
				totalTwo++;

			}
			count = 0;
		}
	}
	row++;
	count = 0;
	for (int i = 0; i < subThree; i++)
	{
		for (int j = 0; j < subFour; j++)
		{
			for (int k = 0; k < 4; k++)   //이진화 배열들의 다른지 맞는지 확인
			{
				if (strInfo[row][i].arr[k] != strInfo[row + 1][j].arr[k]) count++;
			}
			if (count == 1)  //한개다르면 수행
			{
				strInfo[row][i].sellect = 2;
				strInfo[row + 1][j].sellect = 2;
				for (int k = 0; k < 4; k++)
				{
					if (strInfo[row][i].arr[k] != strInfo[row + 1][j].arr[k]) quickArr[row][totalThree].arr[k] = '-';
					else
						quickArr[row][totalThree].arr[k] = strInfo[row][i].arr[k];
				}
				quickArr[row][totalThree].firstNum = strInfo[row][i].num;
				quickArr[row][totalThree].secondNum = strInfo[row + 1][j].num;
				count = 0;
				totalThree++;
			}
			count = 0;
		}
	}

}
void secondQuick() { //2차 
	int count = 0;
	int row = 0;
	int check = 0, count2 = 0;
	char compare[4];
	int subZero = totalZero, subOne = totalOne, subTwo = totalTwo, subThree = totalThree, subFour = totalFour;  //배열들 크기를 대신 받아서 확인
	totalZero = 0, totalOne = 0, totalTwo = 0, totalThree = 0, totalFour = 0;
	for (int i = 0; i < subZero; i++)
	{
		for (int j = 0; j < subOne; j++)
		{
			for (int k = 0; k < 4; k++)   //이진화 배열들의 다른지 맞는지 확인
			{
				if (quickArr[row][i].arr[k] != quickArr[row + 1][j].arr[k]) count++;
			}
			if (count == 1)  //한개다르면 수행
			{
				quickArr[row][i].sellect = 1;
				quickArr[row + 1][j].sellect = 1;
				for (int k = 0; k < 4; k++)
				{
					if (quickArr[row][i].arr[k] != quickArr[row + 1][j].arr[k]) compare[k] = '-';
					else
						compare[k] = quickArr[row][i].arr[k];
				}
				for (int j2 = 0; j2 < totalZero; j2++)
				{
					for (int k = 0; k < 4; k++)
					{
						if (compare[k] != quickArr2[row][j2].arr[k]) count2++;

					}
					if (count2 == 0)
					{
						check++;
						count2 = 0;
						break;
					}
					count2 = 0;

				}
				if (check != 0);
				else if (check == 0)
				{
					for (int k = 0; k < 4; k++)
					{
						if (quickArr[row][i].arr[k] != quickArr[row + 1][j].arr[k]) quickArr2[row][totalZero].arr[k] = '-';
						else
							quickArr2[row][totalZero].arr[k] = quickArr[row][i].arr[k];
					}
					quickArr2[row][totalZero].firstNum = quickArr[row][i].firstNum;
					quickArr2[row][totalZero].secondNum = quickArr[row][i].secondNum;
					quickArr2[row][totalZero].thirdNum = quickArr[row + 1][j].firstNum;
					quickArr2[row][totalZero].fourthNum = quickArr[row + 1][j].secondNum;
					count = 0;
					totalZero++;
					check = 0;
					count2 = 0;
				}

			}
			count = 0;
			check = 0;
		}
	}
	row++;
	count = 0;
	check = 0;
	count2 = 0;
	for (int i = 0; i < subOne; i++)
	{
		for (int j = 0; j < subTwo; j++)
		{
			for (int k = 0; k < 4; k++)   //이진화 배열들의 다른지 맞는지 확인
			{
				if (quickArr[row][i].arr[k] != quickArr[row + 1][j].arr[k]) count++;
			}
			if (count == 1)  //한개다르면 수행
			{
				quickArr[row][i].sellect = 1;
				quickArr[row + 1][j].sellect = 1;
				for (int k = 0; k < 4; k++)
				{
					if (quickArr[row][i].arr[k] != quickArr[row + 1][j].arr[k]) compare[k] = '-';
					else
						compare[k] = quickArr[row][i].arr[k];
				}
				for (int j2 = 0; j2 < totalOne; j2++)
				{
					for (int k = 0; k < 4; k++)
					{
						if (compare[k] != quickArr2[row][j2].arr[k]) count2++;
					}
					if (count2 == 0)
					{
						check++;
						count2 = 0;
						break;
					}
					count2 = 0;
				}
				if (check != 0);
				else if (check == 0)
				{
					for (int k = 0; k < 4; k++)
					{
						if (quickArr[row][i].arr[k] != quickArr[row + 1][j].arr[k]) quickArr2[row][totalOne].arr[k] = '-';
						else
							quickArr2[row][totalOne].arr[k] = quickArr[row][i].arr[k];
					}
					quickArr2[row][totalOne].firstNum = quickArr[row][i].firstNum;
					quickArr2[row][totalOne].secondNum = quickArr[row][i].secondNum;
					quickArr2[row][totalOne].thirdNum = quickArr[row + 1][j].firstNum;
					quickArr2[row][totalOne].fourthNum = quickArr[row + 1][j].secondNum;
					count = 0;
					totalOne++;
					check = 0;
					count2 = 0;
				}

			}
			count = 0;
			check = 0;
		}
	}
	row++;
	count = 0;
	check = 0;
	count2 = 0;
	for (int i = 0; i < subTwo; i++)
	{
		for (int j = 0; j < subThree; j++)
		{
			for (int k = 0; k < 4; k++)   //이진화 배열들의 다른지 맞는지 확인
			{
				if (quickArr[row][i].arr[k] != quickArr[row + 1][j].arr[k]) count++;
			}
			if (count == 1)  //한개다르면 수행
			{
				quickArr[row][i].sellect = 1;
				quickArr[row + 1][j].sellect = 1;
				for (int k = 0; k < 4; k++)
				{
					if (quickArr[row][i].arr[k] != quickArr[row + 1][j].arr[k]) compare[k] = '-';
					else
						compare[k] = quickArr[row][i].arr[k];
				}
				for (int j2 = 0; j2 < totalTwo; j2++)
				{
					for (int k = 0; k < 4; k++)
					{
						if (compare[k] != quickArr2[row][j2].arr[k]) count2++;

					}
					if (count2 == 0)
					{
						check++;
						count2 = 0;
						break;
					}
					count2 = 0;
				}
				if (check != 0);
				else if (check == 0)
				{
					for (int k = 0; k < 4; k++)
					{
						if (quickArr[row][i].arr[k] != quickArr[row + 1][j].arr[k]) quickArr2[row][totalTwo].arr[k] = '-';
						else
							quickArr2[row][totalTwo].arr[k] = quickArr[row][i].arr[k];
					}
					quickArr2[row][totalTwo].firstNum = quickArr[row][i].firstNum;
					quickArr2[row][totalTwo].secondNum = quickArr[row][i].secondNum;
					quickArr2[row][totalTwo].thirdNum = quickArr[row + 1][j].firstNum;
					quickArr2[row][totalTwo].fourthNum = quickArr[row + 1][j].secondNum;
					count = 0;
					totalTwo++;
					check = 0;
					count2 = 0;
				}

			}
			count = 0;
			check = 0;
		}
	}
}
void thirdQuick()
{
	int count = 0, count2 = 0;;
	int row = 0;
	int check = 0;
	char compare[4];
	int subZero = totalZero, subOne = totalOne, subTwo = totalTwo, subThree = totalThree, subFour = totalFour;  //배열들 크기를 대신 받아서 확인
	totalZero = 0, totalOne = 0, totalTwo = 0, totalThree = 0, totalFour = 0;
	for (int i = 0; i < subZero; i++)
	{
		for (int j = 0; j < subOne; j++)
		{
			for (int k = 0; k < 4; k++)   //이진화 배열들의 다른지 맞는지 확인
			{
				if (quickArr2[row][i].arr[k] != quickArr2[row + 1][j].arr[k]) count++;
			}
			if (count == 1)  //한개다르면 수행
			{
				quickArr2[row][i].sellect = 1;
				quickArr2[row + 1][j].sellect = 1;
				for (int k = 0; k < 4; k++)
				{
					if (quickArr2[row][i].arr[k] != quickArr2[row + 1][j].arr[k]) compare[k] = '-';
					else
						compare[k] = quickArr2[row][i].arr[k];
				}
				for (int i2 = 0; i2 <= row; i2++)
				{
					for (int j2 = 0; j2 < totalZero; j2++)
					{
						for (int k = 0; k < 4; k++)
						{
							if (compare[k] != quickArr3[i2][j2].arr[k]) count2++;
						}
						if (count2 == 0)
						{
							check++;
							count2 = 0;
							break;
						}
						count2 = 0;
					}
				}
				if (check != 0);
				else if (check == 0)
				{
					for (int k = 0; k < 4; k++)
					{
						if (quickArr2[row][i].arr[k] != quickArr2[row + 1][j].arr[k]) quickArr3[row][totalZero].arr[k] = '-';
						else
							quickArr3[row][totalZero].arr[k] = quickArr2[row][i].arr[k];
					}
					quickArr3[row][totalZero].firstNum = quickArr2[row][i].firstNum;
					quickArr3[row][totalZero].secondNum = quickArr2[row][i].secondNum;
					quickArr3[row][totalZero].thirdNum = quickArr2[row][i].thirdNum;
					quickArr3[row][totalZero].fourthNum = quickArr2[row][i].fourthNum;
					quickArr3[row][totalZero].fivethNum = quickArr2[row + 1][j].firstNum;
					quickArr3[row][totalZero].sixthNum = quickArr2[row + 1][j].secondNum;
					quickArr3[row][totalZero].seventhNum = quickArr2[row + 1][j].thirdNum;
					quickArr3[row][totalZero].eighthNum = quickArr2[row + 1][j].fourthNum;
					count = 0;
					totalZero++;
					check = 0;
					count2 = 0;
				}

			}
			count = 0;
			check = 0;
		}
	}
	row++;
	count = 0;
	check = 0;
	count2 = 0;
	for (int i = 0; i < subOne; i++)
	{
		for (int j = 0; j < subTwo; j++)
		{
			for (int k = 0; k < 4; k++)   //이진화 배열들의 다른지 맞는지 확인
			{
				if (quickArr2[row][i].arr[k] != quickArr2[row + 1][j].arr[k]) count++;
			}
			if (count == 1)  //한개다르면 수행
			{
				quickArr2[row][i].sellect = 1;
				quickArr2[row + 1][j].sellect = 1;
				for (int k = 0; k < 4; k++)
				{
					if (quickArr2[row][i].arr[k] != quickArr2[row + 1][j].arr[k]) compare[k] = '-';
					else
						compare[k] = quickArr2[row][i].arr[k];
				}
				for (int i2 = 0; i2 <= row; i2++)
				{
					for (int j2 = 0; j2 < totalOne; j2++)
					{
						for (int k = 0; k < 4; k++)
						{
							if (compare[k] != quickArr3[i2][j2].arr[k]) count2++;
						}
						if (count2 == 0)
						{
							check++;
							count2 = 0;
							break;
						}
						count2 = 0;
					}
				}
				if (check != 0);
				else if (check == 0)
				{
					for (int k = 0; k < 4; k++)
					{
						if (quickArr2[row][i].arr[k] != quickArr2[row + 1][j].arr[k]) quickArr3[row][totalOne].arr[k] = '-';
						else
							quickArr3[row][totalOne].arr[k] = quickArr2[row][i].arr[k];
					}
					quickArr3[row][totalOne].firstNum = quickArr2[row][i].firstNum;
					quickArr3[row][totalOne].secondNum = quickArr2[row][i].secondNum;
					quickArr3[row][totalOne].thirdNum = quickArr2[row][i].thirdNum;
					quickArr3[row][totalOne].fourthNum = quickArr2[row][i].fourthNum;
					quickArr3[row][totalOne].fivethNum = quickArr2[row + 1][j].firstNum;
					quickArr3[row][totalOne].sixthNum = quickArr2[row + 1][j].secondNum;
					quickArr3[row][totalOne].seventhNum = quickArr2[row + 1][j].thirdNum;
					quickArr3[row][totalOne].eighthNum = quickArr2[row + 1][j].fourthNum;
					count = 0;
					totalOne++;
					check = 0;
					count2 = 0;
				}
			}
			count = 0;
			check = 0;
		}
	}
}
void fourthQuick() {
	int count = 0, count2 = 0;
	int row = 0;
	int check = 0;
	char compare[4];
	int subZero = totalZero, subOne = totalOne, subTwo = totalTwo, subThree = totalThree, subFour = totalFour;  //배열들 크기를 대신 받아서 확인
	totalZero = 0, totalOne = 0, totalTwo = 0, totalThree = 0, totalFour = 0;
	for (int i = 0; i < subZero; i++)
	{
		for (int j = 0; j < subOne; j++)
		{
			for (int k = 0; k < 4; k++)   //이진화 배열들의 다른지 맞는지 확인
			{
				if (quickArr3[row][i].arr[k] != quickArr3[row + 1][j].arr[k]) count++;
			}
			if (count == 1)  //한개다르면 수행
			{
				quickArr3[row][i].sellect = 1;
				quickArr3[row + 1][j].sellect = 1;
				for (int k = 0; k < 4; k++)
				{
					if (quickArr3[row][i].arr[k] != quickArr3[row + 1][j].arr[k]) compare[k] = '-';
					else
						compare[k] = quickArr3[row][i].arr[k];
				}
				for (int j2 = 0; j2 < totalZero; j2++)
				{
					for (int k = 0; k < 4; k++)
					{
						if (compare[k] != quickArr4[row][j2].arr[k]) count2++;
					}
					if (count2 == 0)
					{
						check++;
						count2 = 0;
						break;
					}
					count2 = 0;
				}
				if (check != 0);
				else if (check == 0)
				{
					for (int k = 0; k < 4; k++)
					{
						if (quickArr3[row][i].arr[k] != quickArr3[row + 1][j].arr[k]) quickArr4[row][totalZero].arr[k] = '-';
						else
							quickArr4[row][totalZero].arr[k] = quickArr3[row][i].arr[k];
					}
					quickArr4[row][totalZero].firstNum = quickArr3[row][i].firstNum;
					quickArr4[row][totalZero].secondNum = quickArr3[row][i].secondNum;
					quickArr4[row][totalZero].thirdNum = quickArr3[row][i].thirdNum;
					quickArr4[row][totalZero].fourthNum = quickArr3[row][i].fourthNum;
					quickArr4[row][totalZero].fivethNum = quickArr3[row][i].fivethNum;
					quickArr4[row][totalZero].sixthNum = quickArr3[row][i].sixthNum;
					quickArr4[row][totalZero].seventhNum = quickArr3[row][i].seventhNum;
					quickArr4[row][totalZero].eighthNum = quickArr3[row][i].eighthNum;
					quickArr4[row][totalZero].ninethNum = quickArr3[row + 1][j].firstNum;
					quickArr4[row][totalZero].tenthNum = quickArr3[row + 1][j].secondNum;
					quickArr4[row][totalZero].eleventhNum = quickArr3[row + 1][j].thirdNum;
					quickArr4[row][totalZero].twelvethNum = quickArr3[row + 1][j].fourthNum;
					quickArr4[row][totalZero].thirteenNum = quickArr3[row + 1][j].firstNum;
					quickArr4[row][totalZero].fourteenNum = quickArr3[row + 1][j].secondNum;
					quickArr4[row][totalZero].fifteenNum = quickArr3[row + 1][j].seventhNum;
					quickArr4[row][totalZero].sixteenNum = quickArr3[row + 1][j].eighthNum;
					count = 0;
					totalZero++;
					check = 0;
					count2 = 0;
				}

			}
			count = 0;
			check = 0;
		}
	}
}

int main()
{
	int check = 0;
	input(); //처음에 설정
	printSituation(1); //첫 설정 출력
	printf("다음:N 이전:P  ->");
	for (;;)
	{
		fflush(stdin);
		//scanf_s("%c", &key);
		key = _getch();
		/*if (key == 'p' || key == 'P')  //이전단계로 돌아가는것
		{
			projectPage--;
			if (projectPage < 0) projectPage = 0;
		}
		if (key == 'n' || key == 'N') //다음단계로 넘어가는것
		{
			projectPage++;
		}
		if (key != 'n' || key != 'N' || key != 'p' || key != 'P')
		{
			printf("올바른키 입력\n");
			printf("다음:N 이전:P  ->");
		}
		switch (projectPage)
		{
		case 1:
		{
				  system("cls");
				  printSituation(1);
				  for (int i = 0; i < 16; i++)
				  {
					  strArr[i].sellect = 0;
					  printf("%d번째 입력:", i);
					  scanf_s("%d", &strArr[i].sellect);
				  }
				  system("cls");
				  printSituation(2);
				  printf("다음:N 이전:P  ->");
				  break;
		}
		case 2:
		{
				  printf("그룹화하는중..\n");
				  Sleep(300);
				  system("cls");
				  grouping();
				  printSituation(3);
				  break;
		}
		case 3:
		{
				  system("cls");
				  firstQuick();
				  secondQuick();
				  thirdQuick();
				  fourthQuick();
				  printSituation(4);
				  printSituation(5);
				  printSituation(6);
				  printSituation(7);
				  break;
		}
		case 4:
		{
				  system("cls");
				  insertValue();
				  makingTable();
				  printf("●:좌표 표시\t○:EPI\t◎:추가EPI\n");
				  printSituation(8);
				  break;
		}
		case 5:
		{
				  system("cls");
				  printf("EPI\n");
				  printf("●:좌표 표시\t○:EPI\t◎:추가EPI\n");
				  checkEPI();
				  printSituation(8);
				  break;
		}
		case 6:
		{
				  system("cls");
				  printf("추가EPI\n");
				  printf("●:좌표 표시\t○:EPI\t◎:추가EPI\n");
				  checkaddEPI();
				  printSituation(8);
				  break;
		}
		case 7:
		{
				  printf("\n");
				  printf("F=");
				  extractfun();
				  break;
		}
		default:
			break;*/
		if (key == 'p' || key == 'P')  //이전단계로 돌아가는것
		{
			projectPage--;
			if (projectPage < 0) projectPage = 0;
		}
		if (key == 'n' || key == 'N') //다음단계로 넘어가는것
		{
			projectPage++;
		}
		if (projectPage == 1 && ((key == 'n' || key == 'N') || (key == 'p' || key == 'P')))
		{
			system("cls");
			printSituation(1);
			for (int i = 0; i < 16; i++)
			{
				printf("%d번째 입력:", i);
				scanf_s("%d", &strArr[i].sellect);
			}
			system("cls");
			printSituation(2);

			printf("다음:N ->");
		}
		else if (projectPage == 2 && ((key == 'n' || key == 'N') || (key == 'p' || key == 'P')))
		{
			printf("그룹화하는중..\n");
			Sleep(300);
			system("cls");
			grouping();
			printSituation(3);
			firstQuick();
			secondQuick();
			thirdQuick();
			fourthQuick();
			insertValue();
			makingTable();
			checkEPI();
			printf("다음:N 이전:P  ->");
		}
		else if (projectPage == 1 && (key == 'p' || key == 'P'))
		{
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 100; j++)
				{
					strInfo[i][j].num = NULL;
					strInfo[i][j].sellect = NULL;
					quickArr[i][j].firstNum = NULL;
					quickArr[i][j].secondNum = NULL;
					quickArr[i][j].sellect = NULL;
					quickArr2[i][j].firstNum = NULL;
					quickArr2[i][j].secondNum = NULL;
					quickArr2[i][j].thirdNum = NULL;
					quickArr2[i][j].fourthNum = NULL;
					quickArr2[i][j].sellect = NULL;
					quickArr3[i][j].firstNum = NULL;
					quickArr3[i][j].secondNum = NULL;
					quickArr3[i][j].thirdNum = NULL;
					quickArr3[i][j].fourthNum = NULL;
					quickArr3[i][j].fivethNum = NULL;
					quickArr3[i][j].sixthNum = NULL;
					quickArr3[i][j].seventhNum = NULL;
					quickArr3[i][j].eighthNum = NULL;
					quickArr3[i][j].sellect = NULL;
					quickArr4[i][j].firstNum = NULL;
					quickArr4[i][j].secondNum = NULL;
					quickArr4[i][j].thirdNum = NULL;
					quickArr4[i][j].fourthNum = NULL;
					quickArr4[i][j].fivethNum = NULL;
					quickArr4[i][j].sixthNum = NULL;
					quickArr4[i][j].seventhNum = NULL;
					quickArr4[i][j].eighthNum = NULL;
					quickArr4[i][j].ninethNum = NULL;
					quickArr4[i][j].tenthNum = NULL;
					quickArr4[i][j].eleventhNum = NULL;
					quickArr4[i][j].fourthNum = NULL;
					quickArr4[i][j].fivethNum = NULL;
					quickArr4[i][j].sixthNum = NULL;
					quickArr4[i][j].seventhNum = NULL;
					quickArr4[i][j].eighthNum = NULL;
					quickArr4[i][j].sellect = NULL;
					valueArr[i][j] = NULL;
					piArr[i] = NULL;
					epiArr[i][j] = NULL;
					for (int k = 0; k < 4; k++)
					{
						strInfo[i][j].arr[k] = NULL;
						quickArr[i][j].arr[k] = NULL;
						quickArr2[i][j].arr[k] = NULL;
						quickArr3[i][j].arr[k] = NULL;
						quickArr4[i][j].arr[k] = NULL;
					}
				}
			}
		}
		else if (projectPage == 3 && ((key == 'n' || key == 'N') || (key == 'p' || key == 'P')))
		{
			system("cls");
			/*firstQuick();
			secondQuick();
			thirdQuick();
			fourthQuick();
			printSituation(4);
			printSituation(5);
			printSituation(6);
			printSituation(7);*/
			printf("다음:N 이전:P  ->");
		}
		else if (projectPage == 4 && ((key == 'n' || key == 'N') || (key == 'p' || key == 'P'))) {
			system("cls");
			/*insertValue();
			makingTable();*/
			printf("●:좌표 표시\t○:EPI\t◎:추가EPI\n");
			printSituation(8);
			printf("다음:N 이전:P  ->");
		}
		else if (projectPage == 5 && ((key == 'n' || key == 'N') || (key == 'p' || key == 'P'))) {
			system("cls");
			printf("EPI\n");
			printf("●:좌표 표시\t○:EPI\t◎:추가EPI\n");
			//checkEPI();
			printSituation(8);
			printf("다음:N 이전:P  ->");
		}
		else if (projectPage == 6 && ((key == 'n' || key == 'N') || (key == 'p' || key == 'P'))) {
			system("cls");
			printf("추가EPI\n");
			printf("●:좌표 표시\t○:EPI\t◎:추가EPI\n");
			//checkaddEPI();
			printSituation(8);
			printf("다음:N 이전:P  ->");
		}
		else if (projectPage == 7 && ((key == 'n' || key == 'N') || (key == 'p' || key == 'P'))) {
			printf("\n");
			printf("F=");
			extractfun();
			printf("\n");
			break;
		}
		else {
			printf("올바른키 입력\n");
			printf("다음:N 이전:P  ->");
		}
	}
	system("pause");
}