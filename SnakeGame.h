#ifndef SNAKEGAME_H
#define SNAKEGAME_H  //头文件 宏保护 避免重复引入

//头文件适合定义结构体，声明公开的函数，公开的常量

//三大自定义数据类型：结构体，枚举类型，共用体
typedef struct SNAKE{
    int x;
    int y;
    struct SNAKE *next;  //指针要用*   SNAKE结构体声明时需要带struct
}snake; //typedef 将struct SNAKE 定义为 snake，所以声明时不需要带struct
//结构体两种方式创建：指针方式 类方式
//指针方式:
//snake *s=(snake *)malloc(sizeof(snake));//创建
//snake->x=0;//访问赋值
//free(s);

//类方式:
//snake s;
//s.x=0;

//枚举类型定义：
enum week{
 Mon = 1, Tues = 2, Wed = 3, Thurs = 4, Fri = 5, Sat = 6, Sun = 7
};
//enum week a=Mon; //没有typedef必须自带关键字enum 或者像下面共用体直接声明
 //不能在头文件创建变量


//共用体：只是一个数据 可以变换类型 共用一个地址
union Data{
	int num;
	char name;
	float score;
}stu1_data,stu2_data; //这里stu1_data是变量名 声明变量,不像struct那里代指结构体
//同样类似于结构体，编译器不为共同体的定义开辟内存空间，而为共同体变量开辟；


static int hjj=100;//创建常量 不能创建变量 ，但是可以声明变量

//声明对外公开的函数
void showWelcome();
void showGame();
void showGameOver();
void gotoxy(int x,int y);
void drawMap();

#endif // SNAKEGAME_H
