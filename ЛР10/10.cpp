#include<stdio.h>
#include<windows.h>
#include<locale.h>
#include<iostream>

int menu();
void input();
void output();
void callpage();
void InputProcesses();
void InfoProc();
void delProc();


int process = 0; // количество процессов
int freep = 0;// количество свободных страниц

typedef struct// процессы
{
	char name[20];// имя
	int numpage[20];// номера страниц на которых находится процесс 
	int calls;// обращения	
}proc;

typedef struct
{
	int memory;//общая память
	int quanity;// количество страниц
	int pagememory;// размер страницы
	proc p[100];// процессы
	int *freepage;// свободные страницы
}comp;

comp c;

int main()
{
	setlocale(LC_ALL, "RUS");
	int num;
	while(num != 9)
    {
        num = menu();
        system("cls");
        switch(num)
        {
            case 1 : input();
                break;
            case 2 : output();
                break;
           case 3 : InputProcesses();
                break;
           case 4 : InfoProc();
                break; 
            case 5 : callpage();
                break;
            case 6 : delProc();
                break;
            default : break; 
        } 
    }
	system("pause");
	return 0;
}

int menu ()
{
	int n;
	printf("\t\t\tМеню\n");
	printf("\t1.Ввести размер выведенной памяти\n");
	printf("\t2.Вывести информацию\n");
	printf("\t3.Ввести процесс\n");
	printf("\t4.Вывести информацию о процессах\n");
	printf("\t5.Обращение к страницам\n");
	printf("\t6.Удалить процесс\n");
	scanf("%d",&n);
	return n;
}

void input()
{
	if(c.memory)
	{
		printf("Данные были введены\n");
		return;
	}
	do{
		printf("Введите выделяемую память  : ");
		scanf("%d",&c.memory);
		printf("Введите количество страниц  : ");
		scanf("%d",&c.quanity);
	}while(c.memory % c.quanity !=0);
	c.pagememory = c.memory / c.quanity;
	freep = c.quanity;
	c.freepage = new int[c.quanity + 1];
	for(int j = 0; j < c.quanity + 1; j++) c.freepage[j] = 0;
	return;
}	

void output()
{
	if(!c.memory)
	{
		printf("Данные не были введены\n");
		return;
	}
	printf("Объём памяти = %d",c.memory);
	printf("\nКоличество страниц = %d",c.quanity);
	printf("\nРазмер страницы = %d",c.pagememory);
	printf("\nКоличество свободных страниц = %d",freep);
	puts("\n");
}

void InputProcesses()
{
	if(!c.memory)
	{
		printf("Данные не были введены\n");
		return;
	}
	int flag2 = 0,k=0,flag = 0,n = 0, j = 0,p = 0;
	char m[20];
	if(freep > 0)
	{
		printf("Введите имя процесса и номер страницы : ");
		scanf("%s%d",&m,&n);
		if(c.freepage[n] == 1)
		{
			j = 1;
			while(c.freepage[j] != 0 && j < c.quanity + 1)
			{
				j++;
			}
			n = j;
		}
	}
	else
	{
		printf("Все страницы заняты, введите имя процесса для замещения : ");
		scanf("%s",&m);
	}
	if(n > c.quanity)
	{
		printf("Нет такой страницы\n");
		return;
	}
	if (freep == 0)
	{
		int min = c.p[0].calls, minp = 0;
		for(int i = 0; i < c.quanity; i++)
		{
			if(min > c.p[i].calls) 
			{
				min = c.p[i].calls;
				minp = i;
			}	
		}
		strcpy(c.p[minp].name,m);
		c.p[minp].calls = 0;
	}
	else
	{
		if (process == 0)
		{
			strcpy(c.p[0].name,m);
			c.p[0].numpage[0] = n;
			c.p[0].calls = 0;
			c.freepage[n] = 1;
			process++;
			freep--; 
		}
		else 
		{   
			for(int i = 0; i < c.quanity; i++)
			{
				if(strcmp(m,c.p[i].name) == 0)
				{
	  				for(j = 0; j < c.quanity;j++)
			    	{
						if(c.p[i].numpage[j] != 0) k++;		
					}
					if(c.freepage[n] == 0)
					{
						c.p[i].numpage[k] = n;
						c.freepage[n] = 1;
						freep--;
						if(k != 0) flag2++;
					}
				}
			}	
			if(flag2 == 0)
			{
				if(c.freepage[n] == 0)
				{
					strcpy(c.p[process].name,m);
					c.p[process].numpage[0] = n;
					c.p[process].calls = 0;
					process++;
					freep--;
					c.freepage[n] = 1;
				}
			}	
		}
	}
}

void InfoProc()
{
	if(process == 0)
	{
		printf("Нет процессов\n");
		return;
	}
	for(int i = 0; i < process; i++)
	{
		printf("Процесс с именем %s размещён на странице(ах) : ",c.p[i].name);
		for(int j = 0; j < c.quanity; j++)
		{
			if(c.p[i].numpage[j] != 0)
			printf("%d ",c.p[i].numpage[j]);
		}
		printf("\nКоличество обращений : %d\n\n\n",c.p[i].calls);
	}	
}

void delProc()
{
	if(process == 0)
	{
		printf("Нет процессов\n");
		return;
	}
	char name[20];
	int n;
	printf("Введите имя процесса : ");
	scanf("%s",&name);
	for(int i = 0; i < c.quanity; i++)
	{
		if(strcmp(name,c.p[i].name) == 0)
		{
  			for(int j = 0; j < c.quanity;j++)
	    	{
				if(c.p[i].numpage[j] != 0) 
				{
					c.freepage[c.p[i].numpage[j]] = 0;
					freep++;
				}
				c.p[i].numpage[j] = 0;		
			}
			for(int j = i; j < process; j++)
			{
				strcpy(c.p[j].name,c.p[j+1].name);
				for(int g = 0; g < c.quanity; g++)
				{
					c.p[j].numpage[g] = c.p[j+1].numpage[g];
				}
				c.p[j].calls = c.p[j+1].calls;
			}
			process--;
		}
	}	
}

void callpage()
{
	int p;
	do{
		printf("Введите количество обращений (от 1 до 10) : ");
		scanf("%d",&p);
	}while(p < 1 || p > 10);
	int i = 0, r = 0;
	while(i < p)
	{
		r = rand() % c.quanity;
		c.p[r].calls++;
		i++;	
	}
	puts("\n");
}

