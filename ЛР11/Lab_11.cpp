#include <stdio.h>
#include <math.h>
#include <string.h>
#include <windows.h>

struct file
{
	char name[100];
	int size;
	bool type; // 1 - file, 0 - directory
	char place[100];
	bool defense;
	bool access; // false = read, true = write
	char info[1000];
	int index;
	int pos;
};

bool Check(char *string)
{
	for(int i = 0; i < strlen(string); i++)
	{
		if(string[i] < 48 || string[i] > 57) return false;
	}
	return true;
} 

int prov()
{
	bool right = true;
	char string[255];
	while(right)
	{
		scanf("%s",string);
		if(strlen(string)<32 && Check(string)) 
			right = false;
		else
			printf("Некоректный ввод!\n");
	}
	return atoi(string);
}


file createdirectory(file *f, file directory)
{
	char name[100];
	int i,t;
	file newdirectory;
	newdirectory.name[0] = '\0';
	bool flag = 0;
	printf("Введите имя каталога: ");
	scanf("%s",&name);
	i=0;
	while ( name[i] != '\0' && i < 16)
    {
        if ( name[i] == '\\' || name[i] == '/' || name[i] == ':' || name[i] == '*' || name[i] == '?' || name[i] == '.' || name[i] == '\"' || name[i] == '<' || name[i] == '>' || name[i] == '|' )
        {
            printf("Некорректный ввод!\n");
            flag = 1;
        }
        i++;
	}
	for(i=0;i<100;i++)
	{
		if(!strcmp(directory.name,f[i].place) && !strcmp(name,f[i].name))
		{
			printf("Такое имя уже существует!");
			printf("\n");
			flag = 1;
		}
	}
	if(!flag)
	{
		strcpy(newdirectory.name,name);
		newdirectory.size = 0;
		newdirectory.type = 0;
		strcpy(newdirectory.place,directory.name);
		newdirectory.access = true;
		return newdirectory;
	}
	else
	{
		return newdirectory;
	}				
}

file opendirectory(file *f, file directory)
{
	char name[100];
	int i;
	file newdirectory;
	newdirectory.name[0] = '\0';
	bool flag = 0;
	printf("Введите имя каталога: ");
	scanf("%s",&name);
	for(i=0;i<100;i++)
	{
		if(!strcmp(directory.name,f[i].place) && !strcmp(name,f[i].name))
		{
			flag = 1;
			newdirectory = f[i];
			if(f[i].type == 1)
			{
				newdirectory.name[0] = '\0';
				printf("Данноe имя принадлежит файлу!\n");
				flag = 0;
			}
		}
	}
	if(flag)
	{
		return newdirectory;
	}
	else
	{
		printf("Каталог не найден!\n");
		return newdirectory;
	}
}

file createtextfile(file *f, file directory)
{
	int t,e,i;
	char name[100];
	file newfile;
	newfile.name[0] = '\0';
	bool flag = 0;
	printf("Введите имя файла: ");
	scanf("%s",&name);
	i = 0;
    while ( name[i] != '\0' && i < 16)
    {
        if ( name[i] == '\\' || name[i] == '/' || name[i] == ':' || name[i] == '*' || name[i] == '?' || name[i] == '.' || name[i] == '\"' || name[i] == '<' || name[i] == '>' || name[i] == '|' )
        {
            printf("Некоректный ввод!\n");
            flag = 1;
        }
        i++;
    }
	for(i=0;i<100;i++)
	{
		if(!strcmp(directory.name,f[i].place) && !strcmp(name,f[i].name))
		{
			printf("Такое имя уже существует!");
			printf("\n");
			flag = 1;
		}
	}
	if(!flag)
	{
		strcpy(newfile.name,name);
		newfile.type = 1;
		strcpy(newfile.place,directory.name);
		printf("Хотите ли заполнить файл? (1 - да, 0 - нет): ");
		scanf("%d",&e);
		if(e == 1)
		{
			printf("Введите информацию: ");
			fflush(stdin);
			gets(newfile.info);
		}
		newfile.access = true;
		newfile.size = strlen(newfile.info);
		return newfile;
	}
	else
	{
		return newfile;
	}
}

void search(file *f)
{
	int t,e,i;
	char name[100],home[100] = "User";
	file nowfile[100];
	int flag = 0;	
	printf("Введите имя файла или каталога: ");
	scanf("%s",&name);
	for(i=0;i<100;i++)
	{
		if(!strcmp(name,f[i].name))
		{
			nowfile[flag] = f[i];
			flag++;
		}
	}
	if(flag == 0)
	{
		printf("Такого файла или каталога не существует!");
		printf("\n");
	}
	else
	{
		for(int j=0;j<flag;j++)
		{
			printf("%s\\",nowfile[j].name);
			while(strcmp(nowfile[j].name,home)!=0)
			{
				nowfile[j] = f[nowfile[j].index];
				printf("%s\\",nowfile[j].name);	
			}
			printf("\n");
		}
	}
}


void del(file *f, file pr, int *col, float *freespace)
{
	int i,j;
	for(i=0;i<99;i++)
	{
		if(!strcmp(pr.name,f[i].place))
		{
			if(f[i].type == 1)
			{
				*freespace -= f[i].size*10;
				for(j=i;j<99;j++)
				{
					f[j] = f[j+1];
					f[j].pos--;
					if(j+1>=f[j].index)
					{
						f[j].index--;
					}
				}
				col--;
			//	i--;
			}
			else
			{
				del(f,f[i],col,freespace);
				for(j=i;j<99;j++)
				{
					f[j] = f[j+1];
					f[j].pos--;
					if(j+1>=f[j].index)
					{
						f[j].index--;
					}
				}
				col--;
			//	i--;
			}
		}
	}
}

void delet(file *f, int *col,float *freespace)
{
	char name[100],password[100];
	int i,t,j,a;
	file newdirectory;
	bool flag = 0;
	printf("Введите имя файла или каталога: ");
	scanf("%s",&name);
	for(i=0;i<100;i++)
	{
		if(!strcmp(name,f[i].name))
		{
			if(f[i].type == 1)
			{
				
				*freespace -= f[i].size*10;
				for(j=i;j<99;j++)
				{
					f[j] = f[j+1];
					f[j].pos--;
					if(j+1>=f[j].index)
					{
						f[j].index--;
					}
				}
				col--;
			}
			else
			{
				del(f,f[i],col,freespace);
				for(j=i;j<99;j++)
				{
					f[j] = f[j+1];
					f[j].pos--;
					if(j+1>=f[j].index)
					{
						f[j].index--;
					}
				}
				col--;
			}
			flag = 1;
		}
	}
	if(flag == 0)
	{
		printf("Такого файла или каталога не существует!\n");
	}
	else
	{
		*col--;
	}
}

void changefile(file *f,float *freespace)
{
	int t,e,i,a;
	char name[100],home[100] = "User";
	char info[1000],po[20];
	file nowfile[100],nf;
	int flag = 0;	
	printf("Введите имя файла: ");
	scanf("%s",&name);
	for(i=0;i<100;i++)
	{
		if(!strcmp(name,f[i].name) && f[i].type == 1 && f[i].access == 1)
		{
			nowfile[flag] = f[i];
			flag++;
		}
	}
	if(flag == 0)
	{
		printf("Такого файла не существует!");
		printf("\n");
	}
	else
	{
		for(int j=0;j<flag;j++)
		{
			printf("%s\\",nowfile[j].name);
			nf = nowfile[j];
			while(strcmp(nf.name,home)!=0)
			{
				nf = f[nf.index];
				printf("%s\\",nf.name);	
			}
			printf("\n");
			printf("Текущая информация: %s",nowfile[j].info);
			printf("\n");
			printf("Хотите ли изменить данный файл? (1 - да, 0 - нет): ");
			scanf("%d",&e);
			if(e == 1)
			{
				*freespace -= nowfile[j].size*0.1;
				printf("Введите новую информацию: ");
				fflush(stdin);
				gets(info);
				*freespace +=strlen(info)*0.1;
				nowfile[j].size = strlen(info);
				strcpy(nowfile[j].info,info);
				printf("Информация изменена.\n");
			}
		}
	}
}


void read(file *f)
{
	FILE *hdd = fopen("hdd.txt","a+");
	int i=0;
	while(!feof(hdd))
	{
		fscanf(hdd,"%100s %d %d %100s %d %d %1000s %d\n",&f[i].name,&f[i].size,&f[i].type,&f[i].place,&f[i].defense,&f[i].access,&f[i].info,&f[i].index);
		i++;
		printf("Файл создан.\n");
	}
	fclose(hdd);
}

	
void write(file *f,int col)
{
	FILE *hdd = fopen("hdd.txt","w+");
	int i;
	for(i=0;i<col;i++)
	{
		fprintf(hdd,"%100s %d %d %100s %d %d %1000s %d\n",f[i].name,f[i].size,f[i].type,f[i].place,f[i].defense,f[i].access,f[i].info,f[i].index);
		printf("Данные записаны в файл: hdd.txt\n");
	}
	fclose(hdd);
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	bool block[100];
	file directory, f[100],tm;
	strcpy(directory.name,"User\0");
	directory.size = 0;
	directory.type = 0;
	directory.place[0] = '\0';
	directory.defense = 0;
	directory.access = 1;
	directory.info[0] = '\0';
	directory.index = 0;
	directory.pos = 0;
	f[0] = directory;
	int m, memory,col = 1,tmp,i;
	float sizeClaster,freespace;
	printf("Введите размер кластера: ");
	sizeClaster = prov();
	//scanf("%f",&sizeClaster);
	sizeClaster *=4.096;
	m=1;
	while(m!=0 && m<10 && m>0)
	{
		printf(" ______________________________________\n");
		printf("|    %20s              |\n",directory.name);
		printf("|______________________________________|\n");
		tmp = 1;
		for(i=1;i<col;i++)
		{
			if(!strcmp(f[i].place,directory.name))
			{
				if(f[i].type == 1)
				{
					printf("|%2d         %10s.txt             |\n",tmp,f[i].name);
				}
				else
				{
					printf("|%2d         %10s                 |\n",tmp,f[i].name);
				}
				tmp++;
			}	
		}
		printf("|______________________________________|\n");
		printf("| Текущая память = %.1f              |\n",sizeClaster-freespace);
		printf("|______________________________________|\n");
		printf("\n");
		printf("--------------------------------------------------------\n");
		printf("                          МЕНЮ                          \n");
		printf("--------------------------------------------------------\n");
		printf("1.Создать каталог\n");
		printf("2.Открыть каталог\n");
		printf("3.Создать текстовый файл\n");
		printf("4.Найти файл или директорию\n");
		printf("5.Удалить файл или директорию\n");
		printf("6.Отредактировать текстовый файл\n");
		printf("7.Выйти из каталога\n");
		printf("8.Сохранить в вируальный файл файлы с жёсткого диска\n");
		printf("9.Записать на жёсткий диск файлы из виртуального файла\n");
		printf("10.Выход\n");
		printf("--------------------------------------------------------\n");
		printf("Введите номер пункта: ");
		m = prov();
		//scanf("%d",&m);
		switch(m)
		{
			case 1:
				{
					f[col] = createdirectory(f,directory);
					if(f[col].name[0] != '\0')
					{
						f[col].index = directory.pos;
						f[col].pos = col;
						col++;
					}
					break;
				}
			case 2:
				{
					tm = opendirectory(f,directory);
					if(tm.name[0] != '\0')
					{
						directory = tm;
					}
					break;
				}
			case 3:
				{
					tm = createtextfile(f,directory);
					if(tm.name[0] != '\0')
					{
						f[col] = tm;
						f[col].index = directory.pos;
						f[col].pos = col;
						freespace+=f[col].size*0.1;
						col++;
					}
					break;
				}
			case 4:
				{
					search(f);
					break;
				}
			case 5:
				{
					delet(f,&col,&freespace);
					break;
				}
			case 6:
				{
					changefile(f,&freespace);
					break;
				}
			case 7:
				{
					directory = f[directory.index];
					break;
				}
			case 8:
				{
					read(f);
					break;
				}
			case 9:
				{
					write(f,col);
					break;
				}
			default : break;
		}
	}
}
