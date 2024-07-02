#include "stdafx.h"    // Подключение стандартного заголовочного файла
#include <stdio.h>     // Подключение библиотеки для работы с вводом-выводом
#include <stdlib.h>    // Подключение стандартной библиотеки для работы с памятью и преобразованиями
#include <conio.h>     // Подключение библиотеки для работы с консольным вводом-выводом
#include <string.h>    // Подключение библиотеки для работы со строками
#include <malloc.h>    // Подключение библиотеки для работы с динамическим распределением памяти
#include <clocale>     // Подключение библиотеки для работы с локалью
#include <windows.h>   // Подключение библиотеки Windows API

using namespace std;
using namespace System;
using namespace System::IO;

#define ENTER 13
#define ESC 27
#define UP 72
#define DOWN 80
#define HOME 71
#define END 79
#define LENGTHMENU 84

struct z  *z=NULL;

struct z {
    char name[20];
    char position[13];
    long age;
	long height;
	char country[30];
	long goal;
};

struct sp {
char fio[20];
long ura;//хранение общего количества голов забитых игроком
struct sp* sled;
struct sp* pred;
};
int menu(int,char [][LENGTHMENU]); 
	void maxim(struct z*,int NC);
	void kolvo(struct z*,int NC);
	void rost(struct z*,int NC);
	void vozrast(struct z*,int NC);
	void alfalist(struct z*,struct sp** spisok,int NC);
	void listing(struct z*,int NC);
	void diagram(struct z*,struct sp** spisok,int NC);
	void vstavka(struct z*,struct sp** spisok,char*,int NC);


int main(array<System::String ^> ^args)
{
int i,n,NC;
struct sp *spisok=nullptr;
char BlankLine[70] = "                                                           ";
char dan[][LENGTHMENU] = {
"Кто самый возрастной игрок Локомотива ?                  ",
"Сколько игроков из России с возрастом старше 25 лет?     ",
"Сколько всего зарубежных футболистов                     ",
"Алфавитный список футболистов                            ",
"Футболисты с одинаковым ростом на одинаковой позиции     ",
"Футболисты у которых одинаковый возраст и национальность ",
"Диаграмма                                                ",
"Выход                                                    "};
 FILE *in;
 struct z *clients;// Указатель на массив структур z
setlocale(LC_CTYPE,"Russian");
	Console::CursorVisible::set(false);// Установка непрозрачного курсора
	Console::WindowWidth=120;
	Console::BufferHeight=Console::WindowHeight;
	Console::BufferWidth=Console::WindowWidth; // Установка ширины окна консоли и синхронизация буфера
if((in=fopen("kursovoy.txt","r"))==NULL)
{
printf("\nФайл с данными не открыт !");
      getch(); exit(1);
}
fscanf(in, "%d", &NC);
    clients = (struct z*)malloc(NC * sizeof(struct z));
    for (i = 0; i < NC; i++)
        fscanf(in, "%s%s%ld%ld%s%ld", clients[i].name,clients[i].position, &clients[i].age,&clients[i].height,clients[i].country,&clients[i].goal);
    for (i = 0; i < NC; i++)
        printf("\n%-20s %-20s %7ld %10ld %10s %7ld",clients[i].name,clients[i].position, clients[i].age,clients[i].height,clients[i].country,clients[i].goal);
    getch();
    while (1)
{
	Console::ForegroundColor=ConsoleColor::DarkRed;
	Console::BackgroundColor=ConsoleColor::DarkRed;
	Console::Clear();// Установка цвета текста и фона консоли на темно-красный и очищение экрана
	Console::ForegroundColor=ConsoleColor::Red;
	Console::BackgroundColor=ConsoleColor::Black;// Установка цветов текста и фона для следующего вывода
	Console::CursorLeft=10;
	Console::CursorTop=4;// Установка позиции курсора консоли
	printf(BlankLine);

for(i=0;i<8;i++)
{
	Console::CursorLeft=10;
	Console::CursorTop=i+5;
printf(" %s ",dan[i]);// Цикл для печати данных dan
}
	Console::CursorLeft=10;
	Console::CursorTop=13;  // Установка позиции курсора
printf(BlankLine); // Печать пустой строки
getch();
n=menu(8,dan);// Вызов функции menu для выбора опции и сохранение результата в n
switch(n)
{
case 1: maxim(clients,NC); break;
case 2: listing(clients,NC); break;
case 3: kolvo(clients,NC); break;
case 4: alfalist(clients,&spisok,NC); break;
case 5: rost(clients,NC); break;
case 6: vozrast(clients,NC); break;
case 7: diagram(clients,&spisok,NC); break;
case 8: exit(0);
}
}
getch();
return 0;
}

int menu(int n,char dan[][LENGTHMENU])
{
int y1=0,y2=n-1;
char c=1;
while (c!=ESC) // Цикл, который будет выполняться до тех пор, пока не будет нажата клавиша ESC
{
switch(c) {             // Проверка значения нажатой клавиши
        case DOWN:             // Если клавиша "Вниз" нажата
             y2 = y1;           // Сохранение текущей позиции
             y1++;              // Переход на одну позицию вниз
             break;
        case UP:              
             y2 = y1;        
             y1--;              // Переход на одну позицию вверх
             break;
        case ENTER:            // Если клавиша "Enter" нажата
             return y1 + 1;     // Возвращение текущей позиции + 1
        case HOME:           
             y2 = y1;         
             y1 = 0;            // Перемещение на первую позицию
             break;
        case END:              // Если клавиша "End" нажата
             y2 = y1;      
             y1 = n - 1;        // Перемещение на последнюю позицию
             break;
}
if(y1>n-1){y2=n-1;y1=0;} //Если y1 выходит за пределы нижней границы(Установка y2 на последнюю позицию;Установка y1 на первую позицию)
	if(y1<0) {y2=0;y1=n-1;}//Наоборот
		Console::ForegroundColor=ConsoleColor::White;
		Console::BackgroundColor=ConsoleColor::Red;
		Console::CursorLeft=11;// Установка горизонтальной позиции курсора
		Console::CursorTop=y1+5;// Установка вертикальной позиции курсора с учетом отступа
	printf("%s",dan[y1]);// Вывод текущего элемента меню(Красит текст и фон выделенного объекта в указанные цвета)
		Console::ForegroundColor=ConsoleColor::Red;
		Console::BackgroundColor=ConsoleColor::Black;
		Console::CursorLeft=11;
		Console::CursorTop=y2+5;
	printf("%s",dan[y2]);//Тоже самое, но для предыдущего
	c=getch();
}
	exit(0);// Завершение программы в случае выхода из цикла
}
void maxim(struct z* client,int NC)
{
int i=0; 
struct sp *spisok;
struct z best;// Инициализация структуры best для хранения информации о самом возрастном клиенте
	strcpy(best.name,client[0].name);
	best.age=client[0].age;
for(i=1;i<NC;i++)
	if (client[i].age>best.age)
{
	strcpy(best.name,client[i].name);
	best.age=client[i].age;
}
	Console::ForegroundColor=ConsoleColor::White;
	Console::BackgroundColor=ConsoleColor::DarkRed;
	Console::CursorLeft=10;
	Console::CursorTop=15;
	printf("  Самый возрастной игрок Локомотива - %s",best.name);
	Console::CursorLeft=10;
	Console::CursorTop=16;//Сдвиг курсора вниз
	printf("  С возрастом %ld лет",best.age);
	getch();
}


void kolvo(struct z *client,int NC)
{
 int i,k=0;
 struct sp *spisok;
 for(i=0;i<NC;i++)
	if (strcmp(client[i].country,"Россия")!=0)
	k++;
	Console::ForegroundColor=ConsoleColor::White;
	Console::BackgroundColor=ConsoleColor::DarkRed;
	Console::CursorLeft=10;
	Console::CursorTop=15;
	printf("  Кол-во игроков не из России : %d",k);
	getch();
 }
void vstavka(struct z* client,struct sp** spisok,char* fio,int NC)// Функция для вставки элемента в список в алфавитном порядке
{
	
int i;
struct sp *nov,*nt,*z=0;
	for(nt=*spisok; nt!=0 && strcmp(nt->fio,fio)<0; z=nt, nt=nt->sled); /* Ищем место для вставки нового элемента,
	пока не достигнем конца списка или не найдем позицию для вставки*/
		if(nt && strcmp(nt->fio,fio)==0) return; // Если элемент с таким именем уже существует, выходим из функции
			nov=(struct sp *) malloc(sizeof(struct sp));// Выделяем память для нового элемента списка
			strcpy(nov->fio,fio);// Копируем имя игрока в новый элемент списка
			nov->sled=nt;//указатель на следующий элемент
			nov->pred=z;//на предыдущий
			nov->ura=0;//устанавливаем изначальное кол-во голов равное 0
		for(i=0;i<NC;i++) //цикл перебирующий всех игроков в массиве clients
			if(strcmp(client[i].name,fio)==0) //проверка на совпадение с именем
				nov->ura+=client[i].goal;//количество голов забитых игроком добавляется к `nov->ura`.
				if(!z) *spisok=nov;// Если элемент вставляется в начало списка, обновляем указатель на первый элемент списка
				if (z)z->sled=nov;// Если есть предыдущий элемент, обновляем его указатель на следующий элемент
				if(nt) nt->pred=nov;// Если есть следующий элемент, обновляем его указатель на предыдущий элемент
			return;

}



void alfalist(struct z* client,struct sp** spisok,int NC)
{
	int i;
	char deli[50];
		struct sp* nt,*z=0;
		Console::ForegroundColor=ConsoleColor::White;
		Console::BackgroundColor=ConsoleColor::DarkRed;
		Console::Clear();
if(!*spisok)
	for(i=0;i<NC;i++)
	vstavka(client,spisok,client[i].name,NC); // Если список пуст, заполняем его
	Console::Clear();
	printf("\n Алфавитный список игроков Локомотива	 Обратный алфавитный список игроков Локомотива");
	printf("\n ====================================    =============================================\n");
for(nt=*spisok; nt!=0; nt=nt->sled)//цикл на вывод каждого элемента

	printf("\n %-20s",nt->fio);//тут еще k добавили чтобы пронумерованы были футболеры
for(nt=*spisok,z=0; nt!=0; z=nt,nt=nt->sled); 
 for(nt=z, i = 0; nt!=0; nt=nt->pred, i++ ){ 
    Console::CursorLeft=40; 
    Console::CursorTop = i + 4; 

    printf(" %-30s",nt->fio); 
} 
getch();

} 



void listing(struct z* client,int NC)
{
int i;
	struct z* nt;
	Console::ForegroundColor=ConsoleColor::White;
	Console::BackgroundColor=ConsoleColor::DarkRed;
	Console::Clear();
	printf("\n\r Список игроков из России с возрастом больше 25 лет");//n перемещает курсор на новую строку а r в начало строки
	printf("\n\r **************************************************\n\r");
for(i=0,nt=client;i<NC;nt++,i++) // Проходимся по всем клиентам
        if (nt->age>25 && strcmp(nt->country,"Россия")==0) // Если возраст игрока больше 25 лет и он из России, выводим его данные
			printf("\n\r  %-20s  %ld лет",nt->name,nt->age);
getch();
}

void rost(struct z* clients,int NC)
{
  int a = 0;
  for (int i = 0; i < NC; i++)//первый цикл проходит по всем футболерам
  {
   for (int j = 0; j < NC; j++)//второй цикл
   {
    if (j == i) continue;//если фамилия совпадает скипаем
    else
    {
     if(clients[i].height==clients[j].height)
     {
      if (strcmp(clients[i].position, clients[j].position) == 0);
      {
       a++;
      
       Console::ForegroundColor = ConsoleColor::White;
       Console::BackgroundColor = ConsoleColor::DarkRed;
       Console::CursorLeft = 10;
       Console::CursorTop = 16;
       printf("Эти футболисты-%s и %s с ростом %d", clients[i].name, clients[j].name,clients[i].height);
       break;
      }
     }
    }
   if (a == 1) break;//если нашли хотя бы одну пару то выходим из цикла
   }


  }
  if (a == 0) printf("Такие футболисты отсутствуют");//если не было найдено совпадения
  getch();
}
void vozrast(struct z* clients,int NC)
{
  int a = 0;
  for (int i = 0; i < NC; i++)
  {
   for (int j = 0; j < NC; j++)
   {
    if (j == i) continue;
    else
    {
     if(clients[i].age==clients[j].age)
     {
      if (strcmp(clients[i].country, clients[j].country) == 0);
      {
       a++;
      
       Console::ForegroundColor = ConsoleColor::White;
       Console::BackgroundColor = ConsoleColor::DarkRed;
       Console::CursorLeft = 10;
       Console::CursorTop = 16;
       printf("Эти футболисты-%s и %s с возрастом %d", clients[i].name, clients[j].name,clients[i].age);
       break;
      }
     }
    }
   if (a == 1) break;
   }


  }
  if (a == 0) printf("Такие футболисты отсутствуют");
  getch();
}

void diagram(struct z *client,struct sp** spisok,int NC)
{
	struct sp *nt;
	int len,i,NColor;
	long sum = 0 ;
	char str1[20];
	char str2[20];
		System::ConsoleColor Color;
		Console::ForegroundColor=ConsoleColor::White;
		Console::BackgroundColor=ConsoleColor::Black;
		Console::Clear();
	for(i=0;i<NC;i++) sum = sum+client[i].goal; //подсчет всех голов 
	if(!*spisok){//если список пуст заполняем его
		for(i=0;i<NC;i++){
			vstavka(client,spisok,client[i].name,NC);
			Color=ConsoleColor::Black; NColor=0;}
	}//начальный цвет диаграммы
	for(nt=*spisok,i=0; nt!=0; nt=nt->sled,i++)//проходим по списку игроков и выводим диграмму
{
		sprintf(str1,"%s",nt->fio);//форматируем строку с именем игрока
		sprintf(str2,"%3.1f%%",(nt->ura*100./sum));//форматируем строку с процентом голов
		Console::ForegroundColor=ConsoleColor::Red;
		Console::BackgroundColor= ConsoleColor::Black;
		Console::CursorLeft=5; Console::CursorTop=i+1;
		printf(str1);//выводим имя игрока
		Console::CursorLeft=20;
		printf("%s",str2);//выводим процент голов
		Console::BackgroundColor=++Color; NColor++;//устанавливаем цвет фона для диграммы
		Console::CursorLeft=30;
		for(len=0; len<nt->ura*100/sum; len++) printf(" ");//рисуем диграмму
			if(NColor==14) //сбрасываем цвет если достигли лимита цветов
{ Color=ConsoleColor::Black; NColor=0; }
}
getch();
return ;
}

