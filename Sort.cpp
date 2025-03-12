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
	printf("Кол-во объектов в массиве: ");
	while (!scanf_s("%d", &kol_biletov) || kol_biletov < 0)                       //Проверка на ввод
	{
		printf("Введите положительное число.\n");
		rewind(stdin);
	}

	data = (struct bilet*)malloc(kol_biletov * sizeof(struct bilet));				//динамическое выделение памяти
	temp = (struct bilet*)malloc(kol_biletov * sizeof(struct bilet));

	//if (!(data = (struct bilet*)malloc(kol_biletov * sizeof(struct bilet))))
	//{
	//	//выделилась ли память
	//	puts("Недостаточно памяти");
	//	return;
	//}

		for (a = 0; a < kol_biletov; a++)
		{
			printf("Введите номер операции: ");
			while (!scanf_s("%d", &(data[a].nomer)) || data[a].nomer < 0)                       //Проверка на ввод
			{
				printf("Введите положительное число.\n");
				rewind(stdin);
			}


			printf("Введите сезон: ");
			scanf_s("%s", data[a].season, 20);

			printf("Введите кол-во билетов: ");
			while (!scanf_s("%d", &(data[a].kolvo)) || data[a].kolvo < 0)                       //Проверка на ввод
			{
				printf("Введите положительное число.\n");
				rewind(stdin);
			}

			printf("Введите цену: ");
			while (!scanf_s("%f", &(data[a].price)) || data[a].price < 0)                       //Проверка на ввод
			{
				printf("Введите положительное число.\n");
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

	if (kol_biletov <= 0)										//проверка наличия записей
	{
		printf("\nОтсутствуют записи для вывода.\n");
	}
	else
	{

		printf("\n");
		printf("#	Сезон		Кол-во		Цена за 1		Итого\n");
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

	register int nom;											//номер записи, которую нужно изменить
	int vibor;

	if (kol_biletov <= 0)										//проверка наличия записей
	{
		printf("\nОтсутствуют записи для изменения.\n");
	}
	else
	{
		printf("\nВведите номер записи.\n");
		while (!scanf_s("%d", &nom) || nom < 0)                 //Проверка на ввод
		{
			printf("Введите положительное число.\n");
			rewind(stdin);
		}

		for (a = 0; a < kol_biletov; a++)
		{
			if (nom == (*(data + a)).nomer)						//проверка наличия записей с введённым номером
			{

				do {
					printf("1.Изменить сезон\n");
					printf("2.Изменить кол-во\n");
					printf("3.Изменить цену за 1 билет\n");
					printf("4.Готово\n");
					scanf_s("%d", &vibor);
					switch (vibor)
					{
					case 1:
						printf("Введите новый сезон\n");
						scanf_s("%s", data[nom - 1].season, 20);
						break;

					case 2:
						printf("Введите новое ко-во билетов\n");
						while (!scanf_s("%d", &(data[nom - 1].kolvo)) || data[nom - 1].kolvo < 0)                       //Проверка на ввод
						{
							printf("Введите положительное число.\n");
							rewind(stdin);
						}
						data[nom - 1].itog_stoimost = data[nom - 1].kolvo * data[nom - 1].price;
						break;

					case 3:
						printf("Введите новую цену за 1 билет\n");
						while (!scanf_s("%f", &(data[nom - 1].price)) || data[nom - 1].price < 0)                       //Проверка на ввод
						{
							printf("Введите положительное число.\n");
							rewind(stdin);
						}
						data[nom - 1].itog_stoimost = data[nom - 1].kolvo * data[nom - 1].price;
						break;

					case 4:
						return;
					}


				} while (1);
			}
		} printf("Нет записи под таким номером.\n");
	}

}

extern void del()
{
	int d;  //номер записи, которую нужно удалить
	printf("\nВведите номер записи, которую необходимо удалить\n");
	printf("Удалить все записи - нажмите '000'\n");
	scanf_s("%d", &d);
	while (!scanf_s("%d", &d) || d < 0)                       //Проверка на ввод
	{
		printf("Введите положительное число.\n");
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
			(*(data + i)) = tmp;				//замещаем каждую структуру в массиве пустой структурой
		kol_biletov = 0;
	}
	printf("\nЗапись удалена.\n");
}

extern void sort_nomer()
{
	register int a, b;
	printf("Старая: ");
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
	printf("Новая: ");
	print();
}

extern void sort_kol()
{
	register int a, b;
	printf("Старая: ");
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
	printf("Новая: ");
	print();
}
extern void sort_price()
{
	register int a, b;
	printf("Старая: ");
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
	printf("Новая: ");
	print();
}
extern void sort_itog_stoimost()
{
	register int a, b;
	printf("Старая: ");
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
	printf("Новая: ");
	print();
}
extern int sort()
{
	if (kol_biletov <= 0)									
	{
		printf("\nОтсутствуют записи для сортировки.\n");
	}
	else
	{
		int choice;
		do {
			printf("\n\t1.Сортировать по номеру операции.\n");
			printf("\t2.Сортировать по цене за 1 билет.\n");
			printf("\t3.Сортировать по количеству.\n");
			printf("\t4.Сортировать по итоговой стоимости.\n");

			while (!scanf_s("%d", &choice) || choice < 0)                       //Проверка на ввод
			{
				printf("Введите положительное число.\n");
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
