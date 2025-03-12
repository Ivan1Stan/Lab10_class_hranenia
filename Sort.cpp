#include <stdio.h>
#include <string.h>
#include <windows.h> 
#include "Header.h"
#include <stdlib.h>

struct bilet
{
	int nomer;
	char season[20];
	int kolvo;
	float price;
	int itog_stoimost;
};

static bilet tmp;

static bilet* data;
static bilet* temp;

int kol_biletov = 0;
extern void enter()
{
	register int a;
	printf("���-�� �������� � �������: ");
	while (!scanf_s("%d", &kol_biletov) || kol_biletov < 0)                       //�������� �� ����
	{
		printf("������� ������������� �����.\n");
		rewind(stdin);
	}

	data = (struct bilet*)malloc(kol_biletov * sizeof(struct bilet));				//������������ ��������� ������
	temp = (struct bilet*)malloc(kol_biletov * sizeof(struct bilet));

	//if (!(data = (struct bilet*)malloc(kol_biletov * sizeof(struct bilet))))
	//{
	//	//���������� �� ������
	//	puts("������������ ������");
	//	return;
	//}

		for (a = 0; a < kol_biletov; a++)
		{
			printf("������� ����� ��������: ");
			while (!scanf_s("%d", &(data[a].nomer)) || data[a].nomer < 0)                       //�������� �� ����
			{
				printf("������� ������������� �����.\n");
				rewind(stdin);
			}


			printf("������� �����: ");
			scanf_s("%s", data[a].season, 20);

			printf("������� ���-�� �������: ");
			while (!scanf_s("%d", &(data[a].kolvo)) || data[a].kolvo < 0)                       //�������� �� ����
			{
				printf("������� ������������� �����.\n");
				rewind(stdin);
			}

			printf("������� ����: ");
			while (!scanf_s("%f", &(data[a].price)) || data[a].price < 0)                       //�������� �� ����
			{
				printf("������� ������������� �����.\n");
				rewind(stdin);
			}

			data[a].itog_stoimost = data[a].kolvo * data[a].price;
			printf("\n");

		}
		printf("\n");

}
extern void print()
{
	register int a;

	if (kol_biletov <= 0)										//�������� ������� �������
	{
		printf("\n����������� ������ ��� ������.\n");
	}
	else
	{

		printf("\n");
		printf("#	�����		���-��		���� �� 1		�����\n");
		printf("=====================================================================\n");
		for (a = 0; a < kol_biletov; a++)
		{
			printf("%d %12s %12d %18.2f %22d", (*(data + a)).nomer, (*(data + a)).season, (*(data + a)).kolvo, (*(data + a)).price, (*(data + a)).itog_stoimost);
			printf("\n");
		}
		printf("\n");
	}
}

extern void change()
{
	register int a;

	register int nom;											//����� ������, ������� ����� ��������
	int vibor;

	if (kol_biletov <= 0)										//�������� ������� �������
	{
		printf("\n����������� ������ ��� ���������.\n");
	}
	else
	{
		printf("\n������� ����� ������.\n");
		while (!scanf_s("%d", &nom) || nom < 0)                 //�������� �� ����
		{
			printf("������� ������������� �����.\n");
			rewind(stdin);
		}

		for (a = 0; a < kol_biletov; a++)
		{
			if (nom == (*(data + a)).nomer)						//�������� ������� ������� � �������� �������
			{

				do {
					printf("1.�������� �����\n");
					printf("2.�������� ���-��\n");
					printf("3.�������� ���� �� 1 �����\n");
					printf("4.������\n");
					scanf_s("%d", &vibor);
					switch (vibor)
					{
					case 1:
						printf("������� ����� �����\n");
						scanf_s("%s", data[nom - 1].season, 20);
						break;

					case 2:
						printf("������� ����� ��-�� �������\n");
						while (!scanf_s("%d", &(data[nom - 1].kolvo)) || data[nom - 1].kolvo < 0)                       //�������� �� ����
						{
							printf("������� ������������� �����.\n");
							rewind(stdin);
						}
						data[nom - 1].itog_stoimost = data[nom - 1].kolvo * data[nom - 1].price;
						break;

					case 3:
						printf("������� ����� ���� �� 1 �����\n");
						while (!scanf_s("%f", &(data[nom - 1].price)) || data[nom - 1].price < 0)                       //�������� �� ����
						{
							printf("������� ������������� �����.\n");
							rewind(stdin);
						}
						data[nom - 1].itog_stoimost = data[nom - 1].kolvo * data[nom - 1].price;
						break;

					case 4:
						return;
					}


				} while (1);
			}
		} printf("��� ������ ��� ����� �������.\n");
	}

}

extern void del()
{
	int d;  //����� ������, ������� ����� �������
	printf("\n������� ����� ������, ������� ���������� �������\n");
	printf("������� ��� ������ - ������� '000'\n");
	scanf_s("%d", &d);
	while (!scanf_s("%d", &d) || d < 0)                       //�������� �� ����
	{
		printf("������� ������������� �����.\n");
		rewind(stdin);
	}
	if (d != 000)
	{
		for (int i = (d - 1); i < kol_biletov; i++)
			(*(data + i)) = (*(data + i + 1));									
		kol_biletov = kol_biletov - 1;					
	}
	if (d == 000)
	{
		for (int i = 0; i < 20; i++)			
			(*(data + i)) = tmp;				//�������� ������ ��������� � ������� ������ ����������
		kol_biletov = 0;
	}
	printf("\n������ �������.\n");
}

extern void sort_nomer()
{
	register int a, b;
	printf("������: ");
	print();
	for (a = 1; a < kol_biletov; a++)
		for (b = kol_biletov - 1; b >= a; b--)
		{

			if ((*(data + b - 1)).nomer > (*(data + b)).nomer)
			{
				(*(temp + b)) = (*(data + b - 1));
				(*(data + b - 1)) = (*(data + b));
				(*(data + b)) = (*(temp + b));
			}
		}
	printf("�����: ");
	print();
}

extern void sort_kol()
{
	register int a, b;
	printf("������: ");
	print();
	for (a = 1; a < kol_biletov; a++)
		for (b = kol_biletov - 1; b >= a; b--)
		{
			if ((*(data + b - 1)).kolvo > (*(data + b)).kolvo)
			{
				(*(temp + b)) = (*(data + b - 1));
				(*(data + b - 1)) = (*(data + b));
				(*(data + b)) = (*(temp + b));
			}
		}
	printf("�����: ");
	print();
}
extern void sort_price()
{
	register int a, b;
	printf("������: ");
	print();
	for (a = 1; a < kol_biletov; a++)
		for (b = kol_biletov - 1; b >= a; b--)
		{
			if ((*(data + b - 1)).price > (*(data + b)).price)
			{
				(*(temp + b)) = (*(data + b - 1));
				(*(data + b - 1)) = (*(data + b));
				(*(data + b)) = (*(temp + b));
			}
		}
	printf("�����: ");
	print();
}
extern void sort_itog_stoimost()
{
	register int a, b;
	printf("������: ");
	print();
	for (a = 1; a < kol_biletov; a++)
		for (b = kol_biletov - 1; b >= a; b--)
		{
			if ((*(data + b - 1)).itog_stoimost > (*(data + b)).itog_stoimost)
			{
				(*(temp + b)) = (*(data + b - 1));
				(*(data + b - 1)) = (*(data + b));
				(*(data + b)) = (*(temp + b));
			}
		}
	printf("�����: ");
	print();
}
extern int sort()
{
	if (kol_biletov <= 0)									
	{
		printf("\n����������� ������ ��� ����������.\n");
	}
	else
	{
		int choice;
		do {
			printf("\n\t1.����������� �� ������ ��������.\n");
			printf("\t2.����������� �� ���� �� 1 �����.\n");
			printf("\t3.����������� �� ����������.\n");
			printf("\t4.����������� �� �������� ���������.\n");

			while (!scanf_s("%d", &choice) || choice < 0)                       //�������� �� ����
			{
				printf("������� ������������� �����.\n");
				rewind(stdin);
			}
			switch (choice)
			{
			case 1: sort_nomer();
				break;
			case 2: sort_price();
				break;
			case 3: sort_kol();
				break;
			case 4: sort_itog_stoimost();
				break;
			}
		} while (choice > 5);
		printf("\n");
		return 0;
	}
}
