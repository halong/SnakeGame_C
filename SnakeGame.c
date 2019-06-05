#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include "SnakeGame.h"

int mapWidth=80;
int mapHeighth=20;

int state_r=1;
int state_l=2;
int state_u=3;
int state_d=4;
int state_over=0;
int state;

int foodState;
int hasFood=1;
int noFood=0;

snake *head;//蛇身
snake *food; //食物



//移动光标
void gotoxy(int x,int y){
    HANDLE handle = GetStdHandle(STD_ERROR_HANDLE);
    COORD coord={x,y};
    SetConsoleCursorPosition(handle,coord);
}

//显示欢迎页面
void showWelcome(){
    //system()运行的是cmd控制台命令 include <windows.h>
    system("mode con cols=100 lines=30");//设置控制台大小
    system("title 贪吃蛇游戏");//设置控制台标题

    system("cls");
    gotoxy(40,10);//移动光标
    printf("欢迎来到贪吃蛇游戏！");
    Sleep(2000);
}

//绘制地图
void drawMap(){
    int i;
    for(i=0;i<mapWidth;i+=2){ //绘制上下边框
        gotoxy(i,0);
        printf("■");

        gotoxy(i,mapHeighth);
        printf("■");
    }


    for(i=0;i<=mapHeighth;i++){//绘制左右边框
        gotoxy(0,i);
        printf("■");

        gotoxy(mapWidth,i);
        printf("■");
    }
}

//初始化蛇身
void initSnake(){
    snake *tail= NULL;
    int i;
    for(i=0;i<4;i++){
        head=(snake *)malloc(sizeof(snake));
        head->x=4+2*i;
        head->y=4;
        head->next=tail;
        tail=head;
    }
}

//绘制贪吃蛇
void drawSnake(){
    snake *tail=head;// 全局变量head一定是指向蛇头，所以要重新声明个局部变量代替
    while(tail != NULL){
        gotoxy(tail->x,tail->y);
        printf("■");//用输入法中的特殊字符打印,横向占2，纵向占1
        tail=tail->next;
    }
}

//移动贪吃蛇
void moveSnake(){
     //蛇头节点向前移动
    int x1=head->x;//记录上个节点的坐标 移动前先记录
    int y1=head->y;
    if(state == state_r){//修改蛇头坐标
            head->x += 2;//横向占2
    }else if(state == state_l){
            head->x -= 2;
    }else if(state == state_u){
            head->y --;
    }else if(state == state_d){
            head->y ++;
    }

    //蛇身节点都向前移动
    snake *tail=head->next;// 全局变量head一定是指向蛇头，所以要重新声明个局部变量代替
    int x2,y2;//缓存本节点  x1,y1缓存上一个节点
    while(1){//加深对while循环的理解，最后一次循环未结束就可能不符合条件了
            x2=tail->x;//记录本节点的坐标
            y2=tail->y;

            tail->x=x1; //将本节点的坐标改为上一个节点的坐标  赋值前先记录 两级记录 ABC互转
            tail->y=y1;
            if(tail->next == NULL){  //tail不能为空指针 下面要用到
                break;
            }
            tail=tail->next;//魔鬼在这里，最后一次循环时已经是最后一个节点
            x1=x2;
            y1=y2;
    }
    gotoxy(x2,y2); //擦除原先蛇尾的节点 因为蛇在向前移动 ！！！这里是关键！！！
    printf(" ");


    //判断是否碰墙
    if(head->x >= 80 || head->x<=0 ||head->y >=20 || head->y <=0){
            state=state_over;
    }


     //遇到食物
    if(foodState==hasFood&&(head->x == food->x)&&(head->y == food->y)){
       snake *t=(snake *)malloc(sizeof(snake));
       t->x=x2;
       t->y=y2;
       t->next=NULL;
       tail->next=t;
       foodState=noFood;
    }

    //判断是否碰到自身
    snake *p = head->next;
    while(p !=NULL){
        if(head->x == p->x  && (head->y == p->y)){
            state=state_over;
            break;
        }
        p=p->next;
    }


}

//初始化食物
void initFood(){
    food=(snake *)malloc(sizeof(snake));//这个只能在函数中调用
}

//绘制食物
void drawFood(){
    int flag;
    snake *p;
    while(1){//外面这个循环，如果重合就再来，直到产生不与蛇身重合的食物为止
        flag=1;
        p=head;
        while(p !=NULL){   //里面这个循环检查产生的食物是否与蛇身重合
            srand((unsigned)time(NULL));//产生随机数  需要#include <time.h>
            food->x=rand()%38*2+2;
            food->y=rand()%19+1;
            if(p->x == food->x && (p->y == food->y)){ //与蛇重合
                flag=0;
                break;
            }
            p=p->next;
        }

        if(flag==1){//说明检查完蛇身未与食物重合
            break;
        }
    }

    gotoxy(food->x,food->y);//绘制食物
    printf("■");
    foodState=hasFood;
}
//显示游戏页面
void showGame(){
    system("cls");
    drawMap();
    initSnake();
    initFood();
    state=state_r;
    while(1){//每隔一段时间重新绘制一次页面
        //游戏控制
        //关键思想：用全局变量控制循环分支，再用其他函数控制这个全局变量--变量控制的思想
        if(GetAsyncKeyState(VK_ESCAPE)){ //按下ESC键 退出
            break;
        }else if(state== state_over){
            break;
        }

        else if(GetAsyncKeyState(VK_UP) && state != state_d){
            state = state_u;
        }
        else if(GetAsyncKeyState(VK_DOWN)&& state != state_u){
            state = state_d;
        }
        else if(GetAsyncKeyState(VK_LEFT)&& state != state_r){
            state = state_l;
        }
        else if(GetAsyncKeyState(VK_RIGHT)&& state != state_l){
            state = state_r;
        }

       if(foodState == noFood)
           drawFood();

        moveSnake();//檫除蛇尾，重绘 ，而不是清屏重绘
        drawSnake();

    Sleep(300);
    }
}

//显示游戏结束页面
void showGameOver(){
    system("cls");
    gotoxy(45,10);
    printf("游戏结束！");
    gotoxy(40,20);
    system("pause");//暂停
}



