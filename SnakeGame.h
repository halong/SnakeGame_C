#ifndef SNAKEGAME_H
#define SNAKEGAME_H  //ͷ�ļ� �걣�� �����ظ�����

//ͷ�ļ��ʺ϶���ṹ�壬���������ĺ����������ĳ���

//�����Զ����������ͣ��ṹ�壬ö�����ͣ�������
typedef struct SNAKE{
    int x;
    int y;
    struct SNAKE *next;  //ָ��Ҫ��*   SNAKE�ṹ������ʱ��Ҫ��struct
}snake; //typedef ��struct SNAKE ����Ϊ snake����������ʱ����Ҫ��struct
//�ṹ�����ַ�ʽ������ָ�뷽ʽ �෽ʽ
//ָ�뷽ʽ:
//snake *s=(snake *)malloc(sizeof(snake));//����
//snake->x=0;//���ʸ�ֵ
//free(s);

//�෽ʽ:
//snake s;
//s.x=0;

//ö�����Ͷ��壺
enum week{
 Mon = 1, Tues = 2, Wed = 3, Thurs = 4, Fri = 5, Sat = 6, Sun = 7
};
//enum week a=Mon; //û��typedef�����Դ��ؼ���enum ���������湲����ֱ������
 //������ͷ�ļ���������


//�����壺ֻ��һ������ ���Ա任���� ����һ����ַ
union Data{
	int num;
	char name;
	float score;
}stu1_data,stu2_data; //����stu1_data�Ǳ����� ��������,����struct�����ָ�ṹ��
//ͬ�������ڽṹ�壬��������Ϊ��ͬ��Ķ��忪���ڴ�ռ䣬��Ϊ��ͬ��������٣�


static int hjj=100;//�������� ���ܴ������� �����ǿ�����������

//�������⹫���ĺ���
void showWelcome();
void showGame();
void showGameOver();
void gotoxy(int x,int y);
void drawMap();

#endif // SNAKEGAME_H
