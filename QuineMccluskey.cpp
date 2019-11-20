#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<conio.h>
typedef struct strNum {   //���ں��� ����ü�� ����
	int num; //����
	char arr[4]; //���ڸ� ����ȭ
	int sellect; //���� �����ߴ��� ���ߴ��� üũ
}strNum; //����ü ����
typedef struct QuickFirst {
	int firstNum;
	int secondNum;
	char arr[4];
	int sellect;
}QuickFirst;  // ù��° ü��¡��Ʈ �� ����ü����
typedef struct QuickSecond { //�ι�° ü��¡ ��Ʈ �� ����ü
	int firstNum, secondNum, thirdNum, fourthNum;
	char arr[4];
	int sellect;
}QuickSecond;// �ι�° ü��¡��Ʈ �� ����ü����
typedef struct QuickThird { //�ι�° ü��¡ ��Ʈ �� ����ü
	int firstNum, secondNum, thirdNum, fourthNum, fivethNum, sixthNum, seventhNum, eighthNum;
	char arr[4];
	int sellect;
}QuickThird;// ����° ü��¡��Ʈ �� ����ü����
typedef struct QuickFourth {
	int firstNum, secondNum, thirdNum, fourthNum, fivethNum, sixthNum, seventhNum, eighthNum;
	int ninethNum, tenthNum, eleventhNum, twelvethNum, thirteenNum, fourteenNum, fifteenNum, sixteenNum;
	char arr[4];
	int sellect;
}QuickFourth;

strNum strArr[16]; //16��¥�� ����ü �迭 ����
strNum strInfo[5][10]; // 1�� �������� �׷�ȭ �ϴ� �迭
QuickFirst quickArr[5][1000]; //Quine-McClusky ��� (1�ܰ�) �迭
QuickSecond quickArr2[4][1000]; //quine-McClusky ��� (2�ܰ�) �迭
QuickThird quickArr3[3][1000]; //quine-McClusky ��� (3�ܰ�) �迭
QuickFourth quickArr4[2][1000]; //quine-McClusky ��� (4�ܰ�) �迭 
int valueArr[16][16];  //EPI�� ���ϱ� ���� ���̺�
int totalZero = 0, totalOne = 0, totalTwo = 0, totalThree = 0, totalFour = 0; //�� ����ü �迭 ũ�� ����
char key = 77;
int projectPage = 0;  //���� ���� ����
int staheight = 0, stawidth = 0; //���̺� ũ�� ����
int piArr[100]; //EPI ���ϱ����� ������迭
int stCount = 0; //pi�迭�� ũ�� ����
int epiArr[100][100];  //
void input() { //����ü�� ������ �Է��س���
	int subNum; //�迭 ���� ����ȭ�ϱ����� ����ִ°�
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
void printSituation(int set) //ȭ�����Ȯ�ο� 
{
	int row = 0;
	int oneCount = 1;
	int width = stawidth;
	int height = 1;
	if (set == 1) //��ü ���!
	{
		printf("����\t������\n");
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
	else if (set == 2)//���õȰ͸� ���
	{
		printf("����\t������\n");
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
	else if (set == 3)//�׷�ȭ �ؼ� ���
	{
		printf("����\t������\n");
		printf("\t0��\n"); //1�ǰ��� 0��
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
				printf("\t%d��\n", oneCount);//1�ǰ��� 1��
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
	}  // �׷�ȭ�� ����Ʈ
	else if (set == 4)//���� 1-1�ܰ� �ϰ� ���
	{
		printf("1�� ü��¡��Ʈ\n");
		printf("����\t\t������\n");
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
	}  //1��ü��¡ ��Ʈ �� ����Ʈ
	else if (set == 5)//���� 1-2�ܰ� �ϰ� ���
	{
		printf("2�� ü��¡��Ʈ\n");
		printf("����\t\t\t������\n");
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

	}  // 2��ü��¡ ��Ʈ �� ����Ʈ
	else if (set == 6)
	{
		printf("3�� ü��¡��Ʈ\n");
		printf("����\t\t\t\t\t������\n");
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

	}     //3��ü��¡ ��Ʈ �� ����Ʈ
	else if (set == 7)
	{
		printf("4�� ü��¡��Ʈ\n");
		printf("����\t\t\t\t\t\t������\n");
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
	else if (set == 8) //���̺� ���!
	{
		printf("���̺�\n");
		printf("����\t\t\t\t\t��");
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
					printf("%d\t\t\t\t\t��", strInfo[row][i]);
					for (int x = 0; x < stawidth; x++) {
						if (valueArr[height][x] == 100) printf("��\t");
						else if (valueArr[height][x] == 200) printf("��\t");
						else if (valueArr[height][x] == 300) printf("��\t");
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
					printf("%d,%d\t\t\t\t\t��", quickArr[row][i].firstNum, quickArr[row][i].secondNum);
					for (int x = 0; x < stawidth; x++) {
						if (valueArr[height][x] == 100) printf("��\t");
						else if (valueArr[height][x] == 200) printf("��\t");
						else if (valueArr[height][x] == 300) printf("��\t");
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
					printf("%d,%d+%d,%d   \t\t\t\t��", quickArr2[row][i].firstNum, quickArr2[row][i].secondNum, quickArr2[row][i].thirdNum, quickArr2[row][i].fourthNum);
					for (int x = 0; x < stawidth; x++) {
						if (valueArr[height][x] == 100) printf("��\t");
						else if (valueArr[height][x] == 200) printf("��\t");
						else if (valueArr[height][x] == 300) printf("��\t");
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
					printf("%d,%d,%d,%d + %d,%d,%d,%d\t\t\t��", quickArr3[row][i].firstNum, quickArr3[row][i].secondNum, quickArr3[row][i].thirdNum, quickArr3[row][i].fourthNum, quickArr3[row][i].fivethNum, quickArr3[row][i].sixthNum, quickArr3[row][i].seventhNum, quickArr3[row][i].eighthNum);
					for (int x = 0; x < stawidth; x++) {
						if (valueArr[height][x] == 100) printf("��\t");
						else if (valueArr[height][x] == 200) printf("��\t");
						else if (valueArr[height][x] == 300) printf("��\t");
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
					printf("%d,%d,%d,%d,%d,%d,%d,%d + %d,%d,%d,%d,%d,%d,%d,%d \t��", quickArr4[row][i].firstNum, quickArr4[row][i].secondNum, quickArr4[row][i].thirdNum, quickArr4[row][i].fourthNum, quickArr4[row][i].fivethNum, quickArr4[row][i].sixthNum, quickArr4[row][i].seventhNum, quickArr4[row][i].eighthNum, quickArr4[row][i].ninethNum, quickArr4[row][i].tenthNum, quickArr4[row][i].eleventhNum, quickArr4[row][i].twelvethNum, quickArr4[row][i].thirteenNum, quickArr4[row][i].fourteenNum, quickArr4[row][i].fifteenNum, quickArr4[row][i].sixteenNum);
					for (int x = 0; x < stawidth; x++) {
						if (valueArr[height][x] == 100) printf("��\t");
						else if (valueArr[height][x] == 200) printf("��\t");
						else if (valueArr[height][x] == 300) printf("��\t");
						else printf("\t");
					}
					height++;
					printf("\n");
				}
			}
		}
	}

}
void checkEPI() {   //EPI üũ�Լ� 
	int width = stawidth;
	int height = staheight;
	int count = 0;
	for (int i = 0; i < width; i++)
	{
		for (int j = 1; j < height; j++)
		{
			if (valueArr[j][i] == 100) count++; //EPI���̺��� üũ�Ȱ��� ������ ī��Ʈ
		}
		if (count == 1)   //�Ѱ������� PI�� ����
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
void extractfun() {  //������ �� ������ ���� �Լ�
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
						epiArr[x2][y2] = valueArr[0][j2];   //EPI üũ ���� �� ���� �迭�� ����
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
						epiArr[x2][y2] = valueArr[0][j2];//EPI üũ ���� �� ���� �迭�� ����
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
	for (int row = 0; row < 5; row++)  //�Ѱ�¥���� EPI�̸� ��ȯ
	{
		for (int i = 0; i < 1000, strInfo[row][i].num != 0; i++)
		{
			if (strInfo[row][i].sellect == 1) //�ʱ⿡ ���� Ȯ��
			{
				for (int x2 = 0; x2 < 16 && epiArr[x2][0] + epiArr[x2][1] != 0; x2++)
				{
					if (strInfo[row][i].num == epiArr[x2][0])  //�Ѱ� ¥���̹Ƿ� �Ѱ��� Ȯ��! 
					{
						pluscount++;
						for (int k = 0; k < 4; k++) //������ ���
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
	for (int row = 0; row < 5; row++)  //EPI�� �ΰ�¥�� �϶� Ȯ��
	{
		for (int i = 0; i < 1000, quickArr[row][i].firstNum + quickArr[row][i].secondNum != 0; i++)
		{
			if (quickArr[row][i].sellect == 0) //���� ����� Ȯ��
			{
				for (int x2 = 0; x2 < 16 && epiArr[x2][0] + epiArr[x2][1] != 0; x2++)
				{
					if (quickArr[row][i].firstNum == epiArr[x2][0]) //2�� ���̹Ƿ� 2�� Ȯ��
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
			if (quickArr2[row][i].sellect == 0) //�Ȱ��� 4��¥�� Ȯ��
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
			if (quickArr3[row][i].sellect == 0)  //8��¥�� Ȯ��
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
				for (int x2 = 0; x2 < 16 && epiArr[x2][0] + epiArr[x2][1] != 0; x2++)   //16��¥��Ȯ��
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
void checkaddEPI()  //EPI üũ �� �߰� EPIȮ���� ���� �Լ� 
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
			if (valueArr[i][j] == 200)  // PI�� ���Դ� ���� ���ڵ� ���δ� �迭�� ����
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
			if (strInfo[row][i].sellect == 1)  //1��¥������ Ȯ��
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
			if (quickArr[row][i].sellect == 0)  //2��¥������ Ȯ��
			{
				for (int x = 0; x < count; x++)
				{
					if (quickArr[row][i].firstNum == piArr[x] || quickArr[row][i].secondNum == piArr[x])  //���� �Ѱ��� ���ٸ� �߰� EPI�� �ƴϹǷ� check�� ++����
					{
						check++;
					}
				}
				if (check != 0) //�ƴϸ� 2�����迭�� height2�������� ���� ��ġ �񱳸� ���� ����
				{

					check = 0;
					height2++;
				}
				else  //�ϳ��� ���ٸ� �߰� EPI�̹Ƿ� �����Ǿ��ִ��� ���� �߰�EPI�� ǥ��
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
			if (quickArr2[row][i].sellect == 0)   //������ �Ȱ��� �ݺ�.
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
			if (quickArr3[row][i].sellect == 0)  //������ �Ȱ��� �ݺ� 
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
	for (int row = 0; row < 2; row++)  //������ �Ȱ��� �ݺ�
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
void inputValue(int width) { //PI���̺� ���־��ִ� �Լ�
	int height = 0;   //���̺� �׸������� �迭 ��ǥ
	int check = 0;  //�ߺ� üũ�� ���� ����
	int temp;  //������ ���� ��������
	for (int row = 0; row < 5; row++)  //1��¥�� ���ں��� ����
	{
		for (int i = 0; i < 1000, strInfo[row][i].num != 0; i++)
		{
			if (strInfo[row][i].sellect == 1)  //���É����� �迭�� �־��ְ� �迭 �����ּҷ�++
			{
				valueArr[height][width] = strInfo[row][i].num;
				width++;
			}
		}
	}
	for (int row = 0; row < 5; row++)  //���������� 2��¥�� ����
	{
		for (int i = 0; i < 1000, quickArr[row][i].firstNum + quickArr[row][i].secondNum != 0; i++)
		{
			if (quickArr[row][i].sellect == 0) //���É�����
			{
				for (int total = 0; total < width; total++) {  //������ �ߺ��Ǵ��� Ȯ���� ���� �������� Ȯ�� 
					if (quickArr[row][i].firstNum == valueArr[height][total]) //ù��°��
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
				for (int total = 0; total < width; total++) {  //2��°��
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
	for (int row = 0; row < 4; row++) //������ ���� �ݺ�
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
	for (int row = 0; row < 3; row++)//������ ���� �ݺ�
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
	for (int row = 0; row < 2; row++) //������ ���� �ݺ�
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
	for (int i = 0; i < width - 1; i++)  //�� ����
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
	int height = 0, width = 0;   //���̺� �׸������� �迭 ��ǥ
	int check = 0;  //�ߺ� üũ�� ���� ����
	if (strInfo[0][0].sellect == 1) //0�� ���É����� 0�� ���̺� �־��ְ� ����
	{
		valueArr[height][width] = strInfo[0][0].sellect;
		width++;
		inputValue(width);
	}
	else  //�ȉ����� �׳� ����
	{
		inputValue(width);
	}
}
void makingTable() {  //���̺� ��üũ �� ����
	int width = stawidth;
	int height = 1;
	for (int row = 0; row < 5; row++) //���̺� ���������� ǥ�����ֱ� ���� ���� 1��¥������
	{
		for (int i = 0; i < 1000, strInfo[row][i].num != 0; i++)
		{
			if (strInfo[row][i].sellect == 1) //1��¥�� ���É�����
			{
				for (int x = 0; x < width; x++)
				{
					if (strInfo[row][i].num == valueArr[0][x]) {  //�� ���ڿ� ���õ� ������ ��ġ �� ���ٸ� ���ڸ� �� ǥ��
						valueArr[height][x] = 100;
					}
				}
				height++;
			}
		}
	}
	for (int row = 0; row < 5; row++) //���� �ݺ�
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
	for (int row = 0; row < 4; row++) //���� �ݺ�
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
	for (int row = 0; row < 3; row++) //���� �ݺ�
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
	for (int row = 0; row < 2; row++) //���� �ݺ�
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
void grouping() //�׷�ȭ �ϴ� ����
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
void firstQuick() {//Quine-McClusky ��� (1�ܰ�) 
	int count = 0;
	int row = 0;
	int subZero = totalZero, subOne = totalOne, subTwo = totalTwo, subThree = totalThree, subFour = totalFour;  //�迭�� ũ�⸦ ��� �޾Ƽ� Ȯ��
	totalZero = 0, totalOne = 0, totalTwo = 0, totalThree = 0, totalFour = 0;

	for (int i = 0; i < subZero; i++)
	{
		for (int j = 0; j < subOne; j++)
		{
			for (int k = 0; k < 4; k++)   //����ȭ �迭���� �ٸ��� �´��� Ȯ��
			{
				if (strInfo[row][i].arr[k] != strInfo[row + 1][j].arr[k]) count++;
			}
			if (count == 1)  //�Ѱ��ٸ��� ����
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
			for (int k = 0; k < 4; k++)   //����ȭ �迭���� �ٸ��� �´��� Ȯ��
			{
				if (strInfo[row][i].arr[k] != strInfo[row + 1][j].arr[k]) count++;
			}
			if (count == 1)  //�Ѱ��ٸ��� ����
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
			for (int k = 0; k < 4; k++)   //����ȭ �迭���� �ٸ��� �´��� Ȯ��
			{
				if (strInfo[row][i].arr[k] != strInfo[row + 1][j].arr[k]) count++;
			}
			if (count == 1)  //�Ѱ��ٸ��� ����
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
			for (int k = 0; k < 4; k++)   //����ȭ �迭���� �ٸ��� �´��� Ȯ��
			{
				if (strInfo[row][i].arr[k] != strInfo[row + 1][j].arr[k]) count++;
			}
			if (count == 1)  //�Ѱ��ٸ��� ����
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
void secondQuick() { //2�� 
	int count = 0;
	int row = 0;
	int check = 0, count2 = 0;
	char compare[4];
	int subZero = totalZero, subOne = totalOne, subTwo = totalTwo, subThree = totalThree, subFour = totalFour;  //�迭�� ũ�⸦ ��� �޾Ƽ� Ȯ��
	totalZero = 0, totalOne = 0, totalTwo = 0, totalThree = 0, totalFour = 0;
	for (int i = 0; i < subZero; i++)
	{
		for (int j = 0; j < subOne; j++)
		{
			for (int k = 0; k < 4; k++)   //����ȭ �迭���� �ٸ��� �´��� Ȯ��
			{
				if (quickArr[row][i].arr[k] != quickArr[row + 1][j].arr[k]) count++;
			}
			if (count == 1)  //�Ѱ��ٸ��� ����
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
			for (int k = 0; k < 4; k++)   //����ȭ �迭���� �ٸ��� �´��� Ȯ��
			{
				if (quickArr[row][i].arr[k] != quickArr[row + 1][j].arr[k]) count++;
			}
			if (count == 1)  //�Ѱ��ٸ��� ����
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
			for (int k = 0; k < 4; k++)   //����ȭ �迭���� �ٸ��� �´��� Ȯ��
			{
				if (quickArr[row][i].arr[k] != quickArr[row + 1][j].arr[k]) count++;
			}
			if (count == 1)  //�Ѱ��ٸ��� ����
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
	int subZero = totalZero, subOne = totalOne, subTwo = totalTwo, subThree = totalThree, subFour = totalFour;  //�迭�� ũ�⸦ ��� �޾Ƽ� Ȯ��
	totalZero = 0, totalOne = 0, totalTwo = 0, totalThree = 0, totalFour = 0;
	for (int i = 0; i < subZero; i++)
	{
		for (int j = 0; j < subOne; j++)
		{
			for (int k = 0; k < 4; k++)   //����ȭ �迭���� �ٸ��� �´��� Ȯ��
			{
				if (quickArr2[row][i].arr[k] != quickArr2[row + 1][j].arr[k]) count++;
			}
			if (count == 1)  //�Ѱ��ٸ��� ����
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
			for (int k = 0; k < 4; k++)   //����ȭ �迭���� �ٸ��� �´��� Ȯ��
			{
				if (quickArr2[row][i].arr[k] != quickArr2[row + 1][j].arr[k]) count++;
			}
			if (count == 1)  //�Ѱ��ٸ��� ����
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
	int subZero = totalZero, subOne = totalOne, subTwo = totalTwo, subThree = totalThree, subFour = totalFour;  //�迭�� ũ�⸦ ��� �޾Ƽ� Ȯ��
	totalZero = 0, totalOne = 0, totalTwo = 0, totalThree = 0, totalFour = 0;
	for (int i = 0; i < subZero; i++)
	{
		for (int j = 0; j < subOne; j++)
		{
			for (int k = 0; k < 4; k++)   //����ȭ �迭���� �ٸ��� �´��� Ȯ��
			{
				if (quickArr3[row][i].arr[k] != quickArr3[row + 1][j].arr[k]) count++;
			}
			if (count == 1)  //�Ѱ��ٸ��� ����
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
	input(); //ó���� ����
	printSituation(1); //ù ���� ���
	printf("����:N ����:P  ->");
	for (;;)
	{
		fflush(stdin);
		//scanf_s("%c", &key);
		key = _getch();
		/*if (key == 'p' || key == 'P')  //�����ܰ�� ���ư��°�
		{
			projectPage--;
			if (projectPage < 0) projectPage = 0;
		}
		if (key == 'n' || key == 'N') //�����ܰ�� �Ѿ�°�
		{
			projectPage++;
		}
		if (key != 'n' || key != 'N' || key != 'p' || key != 'P')
		{
			printf("�ùٸ�Ű �Է�\n");
			printf("����:N ����:P  ->");
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
					  printf("%d��° �Է�:", i);
					  scanf_s("%d", &strArr[i].sellect);
				  }
				  system("cls");
				  printSituation(2);
				  printf("����:N ����:P  ->");
				  break;
		}
		case 2:
		{
				  printf("�׷�ȭ�ϴ���..\n");
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
				  printf("��:��ǥ ǥ��\t��:EPI\t��:�߰�EPI\n");
				  printSituation(8);
				  break;
		}
		case 5:
		{
				  system("cls");
				  printf("EPI\n");
				  printf("��:��ǥ ǥ��\t��:EPI\t��:�߰�EPI\n");
				  checkEPI();
				  printSituation(8);
				  break;
		}
		case 6:
		{
				  system("cls");
				  printf("�߰�EPI\n");
				  printf("��:��ǥ ǥ��\t��:EPI\t��:�߰�EPI\n");
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
		if (key == 'p' || key == 'P')  //�����ܰ�� ���ư��°�
		{
			projectPage--;
			if (projectPage < 0) projectPage = 0;
		}
		if (key == 'n' || key == 'N') //�����ܰ�� �Ѿ�°�
		{
			projectPage++;
		}
		if (projectPage == 1 && ((key == 'n' || key == 'N') || (key == 'p' || key == 'P')))
		{
			system("cls");
			printSituation(1);
			for (int i = 0; i < 16; i++)
			{
				printf("%d��° �Է�:", i);
				scanf_s("%d", &strArr[i].sellect);
			}
			system("cls");
			printSituation(2);

			printf("����:N ->");
		}
		else if (projectPage == 2 && ((key == 'n' || key == 'N') || (key == 'p' || key == 'P')))
		{
			printf("�׷�ȭ�ϴ���..\n");
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
			printf("����:N ����:P  ->");
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
			printf("����:N ����:P  ->");
		}
		else if (projectPage == 4 && ((key == 'n' || key == 'N') || (key == 'p' || key == 'P'))) {
			system("cls");
			/*insertValue();
			makingTable();*/
			printf("��:��ǥ ǥ��\t��:EPI\t��:�߰�EPI\n");
			printSituation(8);
			printf("����:N ����:P  ->");
		}
		else if (projectPage == 5 && ((key == 'n' || key == 'N') || (key == 'p' || key == 'P'))) {
			system("cls");
			printf("EPI\n");
			printf("��:��ǥ ǥ��\t��:EPI\t��:�߰�EPI\n");
			//checkEPI();
			printSituation(8);
			printf("����:N ����:P  ->");
		}
		else if (projectPage == 6 && ((key == 'n' || key == 'N') || (key == 'p' || key == 'P'))) {
			system("cls");
			printf("�߰�EPI\n");
			printf("��:��ǥ ǥ��\t��:EPI\t��:�߰�EPI\n");
			//checkaddEPI();
			printSituation(8);
			printf("����:N ����:P  ->");
		}
		else if (projectPage == 7 && ((key == 'n' || key == 'N') || (key == 'p' || key == 'P'))) {
			printf("\n");
			printf("F=");
			extractfun();
			printf("\n");
			break;
		}
		else {
			printf("�ùٸ�Ű �Է�\n");
			printf("����:N ����:P  ->");
		}
	}
	system("pause");
}