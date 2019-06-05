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

snake *head;//����
snake *food; //ʳ��



//�ƶ����
void gotoxy(int x,int y){
    HANDLE handle = GetStdHandle(STD_ERROR_HANDLE);
    COORD coord={x,y};
    SetConsoleCursorPosition(handle,coord);
}

//��ʾ��ӭҳ��
void showWelcome(){
    //system()���е���cmd����̨���� include <windows.h>
    system("mode con cols=100 lines=30");//���ÿ���̨��С
    system("title ̰������Ϸ");//���ÿ���̨����

    system("cls");
    gotoxy(40,10);//�ƶ����
    printf("��ӭ����̰������Ϸ��");
    Sleep(2000);
}

//���Ƶ�ͼ
void drawMap(){
    int i;
    for(i=0;i<mapWidth;i+=2){ //�������±߿�
        gotoxy(i,0);
        printf("��");

        gotoxy(i,mapHeighth);
        printf("��");
    }


    for(i=0;i<=mapHeighth;i++){//�������ұ߿�
        gotoxy(0,i);
        printf("��");

        gotoxy(mapWidth,i);
        printf("��");
    }
}

//��ʼ������
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

//����̰����
void drawSnake(){
    snake *tail=head;// ȫ�ֱ���headһ����ָ����ͷ������Ҫ�����������ֲ���������
    while(tail != NULL){
        gotoxy(tail->x,tail->y);
        printf("��");//�����뷨�е������ַ���ӡ,����ռ2������ռ1
        tail=tail->next;
    }
}

//�ƶ�̰����
void moveSnake(){
     //��ͷ�ڵ���ǰ�ƶ�
    int x1=head->x;//��¼�ϸ��ڵ������ �ƶ�ǰ�ȼ�¼
    int y1=head->y;
    if(state == state_r){//�޸���ͷ����
            head->x += 2;//����ռ2
    }else if(state == state_l){
            head->x -= 2;
    }else if(state == state_u){
            head->y --;
    }else if(state == state_d){
            head->y ++;
    }

    //����ڵ㶼��ǰ�ƶ�
    snake *tail=head->next;// ȫ�ֱ���headһ����ָ����ͷ������Ҫ�����������ֲ���������
    int x2,y2;//���汾�ڵ�  x1,y1������һ���ڵ�
    while(1){//�����whileѭ������⣬���һ��ѭ��δ�����Ϳ��ܲ�����������
            x2=tail->x;//��¼���ڵ������
            y2=tail->y;

            tail->x=x1; //�����ڵ�������Ϊ��һ���ڵ������  ��ֵǰ�ȼ�¼ ������¼ ABC��ת
            tail->y=y1;
            if(tail->next == NULL){  //tail����Ϊ��ָ�� ����Ҫ�õ�
                break;
            }
            tail=tail->next;//ħ����������һ��ѭ��ʱ�Ѿ������һ���ڵ�
            x1=x2;
            y1=y2;
    }
    gotoxy(x2,y2); //����ԭ����β�Ľڵ� ��Ϊ������ǰ�ƶ� �����������ǹؼ�������
    printf(" ");


    //�ж��Ƿ���ǽ
    if(head->x >= 80 || head->x<=0 ||head->y >=20 || head->y <=0){
            state=state_over;
    }


     //����ʳ��
    if(foodState==hasFood&&(head->x == food->x)&&(head->y == food->y)){
       snake *t=(snake *)malloc(sizeof(snake));
       t->x=x2;
       t->y=y2;
       t->next=NULL;
       tail->next=t;
       foodState=noFood;
    }

    //�ж��Ƿ���������
    snake *p = head->next;
    while(p !=NULL){
        if(head->x == p->x  && (head->y == p->y)){
            state=state_over;
            break;
        }
        p=p->next;
    }


}

//��ʼ��ʳ��
void initFood(){
    food=(snake *)malloc(sizeof(snake));//���ֻ���ں����е���
}

//����ʳ��
void drawFood(){
    int flag;
    snake *p;
    while(1){//�������ѭ��������غϾ�������ֱ���������������غϵ�ʳ��Ϊֹ
        flag=1;
        p=head;
        while(p !=NULL){   //�������ѭ����������ʳ���Ƿ��������غ�
            srand((unsigned)time(NULL));//���������  ��Ҫ#include <time.h>
            food->x=rand()%38*2+2;
            food->y=rand()%19+1;
            if(p->x == food->x && (p->y == food->y)){ //�����غ�
                flag=0;
                break;
            }
            p=p->next;
        }

        if(flag==1){//˵�����������δ��ʳ���غ�
            break;
        }
    }

    gotoxy(food->x,food->y);//����ʳ��
    printf("��");
    foodState=hasFood;
}
//��ʾ��Ϸҳ��
void showGame(){
    system("cls");
    drawMap();
    initSnake();
    initFood();
    state=state_r;
    while(1){//ÿ��һ��ʱ�����»���һ��ҳ��
        //��Ϸ����
        //�ؼ�˼�룺��ȫ�ֱ�������ѭ����֧���������������������ȫ�ֱ���--�������Ƶ�˼��
        if(GetAsyncKeyState(VK_ESCAPE)){ //����ESC�� �˳�
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

        moveSnake();//�߳���β���ػ� �������������ػ�
        drawSnake();

    Sleep(300);
    }
}

//��ʾ��Ϸ����ҳ��
void showGameOver(){
    system("cls");
    gotoxy(45,10);
    printf("��Ϸ������");
    gotoxy(40,20);
    system("pause");//��ͣ
}



