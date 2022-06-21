#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>

struct process
{
	int Size;
	char Name[100];
	int Priority;
	int Address;
	bool RAM;
	bool HDD;
	bool present;
};

struct memory
{
	int size;
	int fullmemory;
};

void AddNewProcess(struct memory storage, struct process Block[100]);
void OutputData(struct memory storage, struct process Block[100]);
void calculation(struct memory storage, struct process Block[100]);
void ShowTable(struct memory storage, struct process Block[100]);
void DeleteProcess(struct memory storage, struct process Block[100]);

int FreeSpace, QuantityProcess = 0;



int main()
{
	setlocale (LC_ALL, "RUS");
	struct memory storage;
	struct process block[100];
	printf("Введите размер памяти:\n");
	int test = scanf("%d", &storage.size);
	if (test==0) 
	{ 
		printf("Некорректный ввод!\n"); 
		return 0; 
	}
	int FreeSpace = storage.size;
	int value = 0;
	while (1)
	{
		calculation(storage, block);
		OutputData(storage, block);
		printf("-----------------------------------\n");
		printf(" 1) Добавить новый процесс.\n");
		printf(" 2) Удалить процесс по адресу.\n");
		printf(" 3) Показать таблицу процессов.\n");
		printf("-----------------------------------\n");
		test = scanf("%d", &value);
		if (test==0) 
		{ 
			printf("Некорректный ввод!\n"); 
			return 0; 
		}
		switch (value)
		{
		case 1:
			AddNewProcess(storage, block);
			break;
		case 2:
			DeleteProcess(storage, block);
			break;
		case 3:
			ShowTable(storage, block);
			break;
		}
	}
}

void AddNewProcess(struct memory storage, struct process Block[100])
{
	setlocale (LC_ALL, "RUS");
	printf("Введите имя процесса %d:\n", QuantityProcess+1);
	scanf("%s", Block[QuantityProcess].Name);
	printf("Введите количество пямяти, которая занимает процесс:\n");
	int test = scanf("%d", &Block[QuantityProcess].Size);
	if (test==0) 
	{ 
		printf("Некорректный ввод!\n"); 
		return; 
	}
	printf("Введите приоритет процесса:\n");
	test = scanf("%d", &Block[QuantityProcess].Priority);
	if (test==0) 
	{ 
		printf("Некорректный ввод!\n"); 
		return; 
	}
	Block[QuantityProcess].Address = QuantityProcess;
	Block[QuantityProcess].present = true;
	Block[QuantityProcess].RAM = true;
	Block[QuantityProcess].HDD = false;
	QuantityProcess++;
}

void OutputData(struct memory storage, struct process Block[100])
{
	setlocale (LC_ALL, "RUS");
	int RAM = 0, HDD = 0;
	printf("Размер памяти: %d \n", storage.size);
	printf("Приоритет процесса: %d \n", QuantityProcess);
	for (int i = 0; i < QuantityProcess; i++)
	{
		if (Block[i].present == true && Block[i].RAM == true)
		{
			RAM++;
		}
		if (Block[i].present == true && Block[i].HDD == true)
		{
			HDD++;
		}
	}
	printf("Приоритет процесса, который находится в RAM: %d \n", RAM);
	printf("Приоритет процесса, который находится в HDD: %d \n", HDD);
}

void ShowTable(struct memory storage, struct process Block[100])
{
	int Counter = 0;
	printf("---------------------------------------------------------------------------\n");
	printf("|   Имя    |     Память    | 	 RAM    |   HDD   |  Адрес  |  Приоритет  |\n");
	for (Counter = 0; Counter < QuantityProcess; Counter++)
	{
		if (Block[Counter].present == true)
		{
			printf("|%10.10s|%13.1d|%13.1d|%9.1d|%11.1d|%12.1d|\n", Block[Counter].Name, Block[Counter].Size, Block[Counter].RAM, Block[Counter].HDD, Block[Counter].Address, Block[Counter].Priority);
		}
	}
	printf("\n");
	printf("---------------------------------------------------------------------------\n");
}


void calculation(struct memory storage, struct process Block[100])
{
	setlocale (LC_ALL, "RUS");
	int i = 0, j = 0;
	while (i < QuantityProcess)
	{
		if (Block[i].Size <= (storage.size - storage.fullmemory))
		{
			storage.fullmemory += Block[i].Size;
			Block[i].HDD = false;
			Block[i].RAM = true;
		}
		else
		{
			for (j = 0; j < QuantityProcess; j++)
			{
				if ((Block[i].Priority < Block[j].Priority) &&  (Block[j].RAM == true))
				{
					Block[j].RAM = false;
					Block[j].HDD = true;
					storage.fullmemory -= Block[j].Size;
					if (Block[i].Size <= (storage.size - storage.fullmemory))
					{
						storage.fullmemory += Block[i].Size;
						Block[i].HDD = false;
						Block[i].RAM = true;
						j = 5;
					}
				}
			}
		}
		i++;
	}
}

void DeleteProcess(struct memory storage, struct process Block[100])
{
	setlocale (LC_ALL, "RUS");
	bool flag = false;
	printf("Введите адресс процесса:\n");
	int value = 0;
	int test = scanf("%d", &value);
	if (test==0) 
	{ 
		printf("Некорректный ввод!\n"); 
		return; 
	}
	if (value >= 0 && value <= 100)
	{
		if(value != 0 )
		{
			for (int Counter = value; value < QuantityProcess; Counter++)
			{
				if(Block[Counter +1].present == true)
				{
					Block[Counter].Address = Block[Counter + 1].Address;
					strcpy(Block[Counter].Name, Block[Counter + 1].Name);
					Block[Counter].Priority = Block[Counter + 1].Priority;
					Block[Counter].Size = Block[Counter + 1].Size;
					Block[Counter].RAM = Block[Counter + 1].RAM;
					Block[Counter].HDD = Block[Counter + 1].HDD;
					flag = true;
				}
				else
				{
					QuantityProcess--;
				}
			}
			if(flag == true)
				{	
					QuantityProcess--;
				}
		}
		else
		{
			QuantityProcess--;
		}
	}
}


