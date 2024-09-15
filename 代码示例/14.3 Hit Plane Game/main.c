/*ʾ��������Դ��https://blog.csdn.net/LuHe123_ye/article/details/121715280*/
#include<stdio.h>
#include<stdlib.h>
#include"acllib.h"
#include<time.h>
#include<math.h>
 
#define WIN_WEIGTH 1000
#define WIN_LENGTH 720
#define CHANGE_pipeANGLE 0.1
#define CHANGE_bulletANGLE 0.1
 
//Turret and Pipe
#define tStep_x 20
#define OLpipex  485
#define OLpipey  680
#define ORpipex  515
#define ORpipey  680
#define OAngle   1
#define OTturretx 450
#define OTturrety 680
#define OBturretx 550
#define OBturrety 720
#define a 60 //Pipe height 
 
//Bullet
#define Bulletlength 8
#define Bulletwidth  8
#define vBullet      20
 
//Plane
#define Move_Planex 5
#define OTplanex 0
#define OTplaney 0
#define OBplanex 20
#define OBplaney 20
#define planeWidth 40
#define planeLength 15
 
 
typedef struct _bullet {
	int x1;
	int y1;
	int x2;
	int y2;
	int bangle;
}BULLET;
 
typedef struct _magazine {        //����洢�ӵ�
	BULLET Bullet;
	struct _magazine* next_Bullet;
}MAGAZINE;
 
typedef struct _turret {
	int x1;
	int y1;
	int x2;
	int y2;
}TURRET;
typedef struct _pipe {
	
		int x1;  //����
		int y1;
	
		int x2;  //����
		int y2;
	
		int x3;  //����
		int y3;
	
		int x4;  //����
		int y4;
 
	int angle;
}PIPE;
typedef struct _plane {
	int x1;
	int y1;
	int x2;
	int y2;
	int randnum;
}PLANE;
typedef struct _planegroup {        //����洢�ӵ�
	PLANE Plane;
	struct _planegroup* next_Plane;
}PLANEGROUP;
 
typedef struct _text {
	int x;
	int y;
	char ch;
}TEXT;
 
 
//-----view-----//
void Creat_Turret(void);
void Creat_Pipe(int key, int event);
void Shot_Bullet(void);
void Creat_OTurret(void);  //print a oturret(not clear screen)
void Creat_OPipe(void);    //print a opipe(not clear screen)
void Shot_OBullet(void);
void Shot_Bullet(void);
void Creat_OPlane(void);
void Creat_boom(PLANE* boom_plane);
void Creat_All(void);      //���»�������ͼ��
//-----view-----//
//-----model-----//
void load_Bullet(void);    //�����ڹ����ӵ�
void load_Magazine(void);  //���ص���  
void load_Plane(void);     //���طɻ�
void load_Planegroup(void);//���طɻ���
void load_Planetnt(void); //���طɻ�ը�� 
void delete_Plane(void);   //���������ɾ��
void delete_Bullet(void);   //���������ɾ��
int test_Crash(void);     //�����ײ
//-----model-----//
//-----ctrl-----//
void keyListener(int key, int event);
void timerListener(int id);
//-----ctrl-----//
 
 
 
PIPE   Pipe = { OLpipex,OLpipey - a, OLpipex,OLpipey, ORpipex,ORpipey,  ORpipex,ORpipey - a ,0 };         //��ʼ���������λ��
PIPE   temp_Pipe = { OLpipex,OLpipey - a, OLpipex,OLpipey, ORpipex,ORpipey,  ORpipex,ORpipey - a ,0 };    //���ڼ�¼ÿ���ڹܵ�����
TURRET Turret = { OTturretx,OTturrety,OBturretx,OBturrety };
BULLET tBullet;             //��ʼ��һ���ӵ����������и�ֵ����load_Bullet��Ž��и�ֵ����ͬ������ʱ����̨�����λ��,ÿ�δ�������ᱻ����
PLANE tPlane;               //��ʼ��һ���ɻ���ÿ�δ�������ᱻ����
//PLANE* boomPlane;           //ָ��ը�ķɻ�
MAGAZINE* Magazine = NULL;     //����һ��������
BULLET* pBullet = NULL;        //ֻ�����ڹ������ŵ��ӵ����꣬�����ָ����һ���ӵ�
PLANEGROUP* Planegroup = NULL; //����һ���������
TEXT count_text;               //�����Ʒְ�
   
unsigned cnt_plane = 0;
int count = 0;
//-----------------------------------------------------------------------------MAIN-----------------------------------------------------------------------------//
 
int Setup() {
 
	initConsole();
	printf("do you want start?\n[1]YES\t[2]NO\n");
	char start;
	while (1) {
		char* p = &start;
		*p = getchar();
		if (*p == '1') {
			break;
		}
		else {
			exit(0);
		}
	}
    initWindow("Turret fight with plane", DEFAULT, DEFAULT, WIN_WEIGTH, WIN_LENGTH);
	registerKeyboardEvent(keyListener);
	registerTimerEvent(timerListener);
	startTimer(1, 50);    //�ӵ���
	startTimer(2, 50);   //�ɻ���
	startTimer(3, 1);    //��ײ��
	return 0;
}
//-----------------------------------------------------------------------------MAIN-----------------------------------------------------------------------------//
 
 
 
//-----------------------------------------------------------------------------VIEW-----------------------------------------------------------------------------//
void Creat_Turret(void) {                       //��������
	beginPaint();
	clearDevice();
	setPenColor(BLACK);
	setPenWidth(3);
	setBrushColor(EMPTY);
	setPenStyle(PEN_STYLE_SOLID);
	rectangle(Turret.x1, Turret.y1, Turret.x2, Turret.y2);
	endPaint();
}
void Creat_Pipe(int key, int event) {
	beginPaint();
	clearDevice();
	setPenColor(RED);
	setPenWidth(3);
	setBrushColor(EMPTY);
	setPenStyle(PEN_STYLE_SOLID);
	PIPE* pPipe = &Pipe;
	if ( event == 1) {
		if (key == 'Q') {
			temp_Pipe.angle = Pipe.angle++;       //�����Ƕ�
			if (Pipe.angle > 12) {
				Pipe.angle = 12;
			}
		}
		else if (key == 'E') {
			temp_Pipe.angle = Pipe.angle--;
			if (Pipe.angle < -12) {
				Pipe.angle = -12;
			}
		}
		int px = a * sin(Pipe.angle * CHANGE_pipeANGLE);
		int py = a * cos(Pipe.angle * CHANGE_pipeANGLE);
		POINT posPipe[] = {
			{temp_Pipe.x1 = Pipe.x2 - px, temp_Pipe.y1 = Pipe.y2 - py},
			{temp_Pipe.x2 = Pipe.x2, temp_Pipe.y2 = Pipe.y2},
			{temp_Pipe.x3 = Pipe.x3, temp_Pipe.y3 = Pipe.y3},
			{temp_Pipe.x4 = Pipe.x3 - px, temp_Pipe.y4 = Pipe.y3-py},
		};
		polygon(posPipe, 4);
	}else  {
		POINT posPipe[] = {
			{temp_Pipe.x1,temp_Pipe.y1},    //̧���λ��ʱ�������һ���ϴε�ͼ�񣬷�ֹ����
			{temp_Pipe.x2,temp_Pipe.y2},
			{temp_Pipe.x3,temp_Pipe.y3},
			{temp_Pipe.x4,temp_Pipe.y4},
		};
		polygon(posPipe, 4);
	}
	endPaint();
}
void Shot_Bullet(void) {
	if (Magazine) {           //ֻ�е��г�ʼ������ܷ���
		for (MAGAZINE* pMagazine = Magazine; pMagazine;pMagazine = pMagazine->next_Bullet) {   //�ҽڵ㣬������ھ͸ı����꣬���ӵ�
			int px = vBullet * sin(pMagazine->Bullet.bangle * CHANGE_pipeANGLE);
			int py = vBullet * cos(pMagazine->Bullet.bangle * CHANGE_pipeANGLE);
			pMagazine->Bullet.x1 -= px;
			pMagazine->Bullet.y1 -= py;
			pMagazine->Bullet.x2 -= px;
			pMagazine->Bullet.y2 -= py;
			beginPaint();
			clearDevice();
			setPenColor(BLUE);
			setPenWidth(1);
			setBrushColor(BLUE);
			setPenStyle(PEN_STYLE_SOLID);
			rectangle(pMagazine->Bullet.x1, pMagazine->Bullet.y1, pMagazine->Bullet.x2, pMagazine->Bullet.y2);
			endPaint();
		}
	}
	
}
void Creat_Plane(void) {
	if (Planegroup) {
	beginPaint();
	clearDevice();
	endPaint();
		for (PLANEGROUP* pPlanegroup = Planegroup; pPlanegroup; pPlanegroup = pPlanegroup->next_Plane) {
			/*if (Planegroup->Plane.randnum == 1) {*/
				//printf(" oo ");
				pPlanegroup->Plane.x1 += Move_Planex;
				pPlanegroup->Plane.x2 += Move_Planex;
			/*}*/
			/*else if(Planegroup->Plane.randnum == 0) {
				printf(" ** ");
				pPlanegroup->Plane.x1 -= Move_Planex;
				pPlanegroup->Plane.x2 -= Move_Planex;
			}*/
			beginPaint();
			setPenColor(RGB(147, 112, 219));
			setPenWidth(3);
			setBrushColor(RGB(123, 104, 238));
			setPenStyle(PEN_STYLE_SOLID);
			rectangle(pPlanegroup->Plane.x1, pPlanegroup->Plane.y1, pPlanegroup->Plane.x2, pPlanegroup->Plane.y2);
			endPaint();
		}
	}
}
void Creat_OTurret(void) {    //ͬʱ����������Ŀ�Ὣ��ʱ�Ļ���clear����Ҫ�����һ���ϴε�����
	beginPaint();
	setPenColor(BLACK);
	setPenWidth(3);
	setBrushColor(EMPTY);
	setPenStyle(PEN_STYLE_SOLID);
	rectangle(Turret.x1, Turret.y1, Turret.x2, Turret.y2);
	endPaint();
}
void Creat_OPipe(void) {
	int px = a * sin(Pipe.angle * CHANGE_pipeANGLE);
	int py = a * cos(Pipe.angle * CHANGE_pipeANGLE);
	beginPaint();
	setPenColor(RED);
	setPenWidth(3);
	setBrushColor(EMPTY);
	setPenStyle(PEN_STYLE_SOLID);
	POINT posPipe[] = {
			{temp_Pipe.x1,temp_Pipe.y1},    //̧���λ��ʱ�������һ���ϴε�ͼ�񣬷�ֹ����
			{temp_Pipe.x2,temp_Pipe.y2},
			{temp_Pipe.x3,temp_Pipe.y3},
			{temp_Pipe.x4,temp_Pipe.y4},
	};
	polygon(posPipe, 4);
	endPaint();
}
void Shot_OBullet(void) {     
	if (Magazine) {              //ֻ�е��г�ʼ������ܷ���
		for (MAGAZINE* pMagazine = Magazine; pMagazine; pMagazine = pMagazine->next_Bullet) {  //�ҽڵ㣬������ھͻ��ӵ�
			beginPaint();
			setPenColor(BLUE);
			setPenWidth(1);
			setBrushColor(BLUE);
			setPenStyle(PEN_STYLE_SOLID);
			rectangle(pMagazine->Bullet.x1, pMagazine->Bullet.y1, pMagazine->Bullet.x2, pMagazine->Bullet.y2);
			endPaint();
		}
	}
}
void Creat_OPlane(void) {
	if (Planegroup) {
		for (PLANEGROUP* pPlanegroup = Planegroup; pPlanegroup; pPlanegroup = pPlanegroup->next_Plane) {
			beginPaint();
			setPenColor(RGB(147, 112, 219));
			setPenWidth(3);
			setBrushColor(RGB(123, 104, 238));
			setPenStyle(PEN_STYLE_SOLID);
			rectangle(pPlanegroup->Plane.x1, pPlanegroup->Plane.y1, pPlanegroup->Plane.x2, pPlanegroup->Plane.y2);
			endPaint();
		}
	}
}
//void Creat_boom(void) {
//	if (boomPlane) {
//		beginPaint();
//		setPenColor(RED);
//		setPenWidth(3);
//		setBrushColor(RED);
//		setPenStyle(PEN_STYLE_SOLID);
//		rectangle(boomPlane->x1, boomPlane->y1, boomPlane->x2, boomPlane->y2);
//		endPaint();
//	}
//}
void Creat_All(void) {
	test_Crash();
	Creat_OPipe();
	Creat_OTurret();
	Shot_OBullet();
	Creat_OPlane();
	//Creat_boom();
}
void Creat_boom(PLANE* boom_Plane) {
	beginPaint();
	setPenColor(RED);
	setPenWidth(3);
	setBrushColor(RED);
	setPenStyle(PEN_STYLE_SOLID);
    ellipse(boom_Plane->x1-20, boom_Plane->y1-20, boom_Plane->x2+20, boom_Plane->y2+20);
	endPaint();
}
//-----------------------------------------------------------------------------VIEW-----------------------------------------------------------------------------//
 
//-----------------------------------------------------------------------------MODEL-----------------------------------------------------------------------------//
void load_Bullet(void) {                  //�����ڹ������ʼ���ӵ�λ��
	tBullet.bangle = Pipe.angle;
	tBullet.x1 = (temp_Pipe.x1 + temp_Pipe.x4) / 2 - Bulletwidth / 2;
	tBullet.y1 = temp_Pipe.y1;
	tBullet.x2 = tBullet.x1 + Bulletwidth;
	tBullet.y2 = tBullet.y1 + Bulletlength;
}
void load_Magazine(void) {                //����������ӵ�
	MAGAZINE* pMagazine = (MAGAZINE*)malloc(sizeof(MAGAZINE));
	pMagazine->Bullet = tBullet;
	pMagazine->next_Bullet = NULL;
	MAGAZINE* last = Magazine;
	if (last) {
		while (last->next_Bullet != NULL) {
			last = last->next_Bullet;
		}
		last->next_Bullet = pMagazine;
	}
	else {
		Magazine = pMagazine;
	}
}
void load_Plane(void) {           //�ɻ�y�����������   
	int t = rand()%2;
	//printf("%d ",t);
	tPlane.y1 = rand()%320+1;
	tPlane.y2 = tPlane.y1 + planeLength;
	if (t == 1) {
		tPlane.x1 = -planeWidth;
		tPlane.x2 = tPlane.x1 + planeWidth;
		tPlane.randnum = 1;
	}
	else if( t == 0 ) {
		//printf("\n**\n");
		tPlane.x1 = WIN_WEIGTH + planeWidth;
		tPlane.x2 = tPlane.x1 + planeWidth;
		tPlane.randnum = 0;
	}
}
void load_Planegroup(void) {            //�������ķɻ�д������
	PLANEGROUP* pPlanegroup = (PLANEGROUP*)malloc(sizeof(PLANEGROUP));
	pPlanegroup->Plane = tPlane;
	pPlanegroup->next_Plane = NULL;
	PLANEGROUP* last = Planegroup;
	if (last) {
		while (last->next_Plane != NULL) {
			last = last->next_Plane;
		}
		last->next_Plane = pPlanegroup;
		//last->next_Plane->next_Plane = NULL;
	}
	else {
		Planegroup = pPlanegroup;
	}
}
void delete_Plane(void) {                     //��������ľ�ɾ��
	PLANEGROUP* q = NULL;
	PLANEGROUP* p = Planegroup;
	for ( ; p; q = p, p = p->next_Plane ) {
		if ( p->Plane.x1 > WIN_WEIGTH ) {
			//printf(" * ");
			if (q) {
				q->next_Plane = p->next_Plane;
			}
			else {
				Planegroup = p->next_Plane;
			}
			free(p);
			break;
		}
	}
}
void delete_Bullet(void) {                     //��������ľ�ɾ��
	MAGAZINE* q = NULL;
	MAGAZINE* p = Magazine;
	for (; p; q = p, p = p->next_Bullet) {
		if ( p->Bullet.y2 < 0 ) {
			//printf(" $ ");
			if (q) {
				q->next_Bullet = p->next_Bullet;
			}
			else {
				Magazine = p->next_Bullet;
			}
			free(p);
			break;
		}
	}
}
int test_Crash(void) {                        //����ӵ��ͷɻ�����ײ��ͨ�������Ƿ��ڷ�Χ���жϣ���
	int turn = 0;
	MAGAZINE* q = NULL;
	MAGAZINE* p = Magazine;
	for ( ; p; q = p, p = p->next_Bullet ) {
		PLANEGROUP* k = NULL;
		PLANEGROUP* j = Planegroup;
		for ( ; j; k = j, j = j->next_Plane ) {
			if (p->Bullet.x1 >= j->Plane.x1-5 && p->Bullet.x1 <= j->Plane.x2+5 && p->Bullet.y1 >= j->Plane.y1-5 && p->Bullet.y1 <= j->Plane.y2+5 && \
				p->Bullet.x2 <= j->Plane.x2+5 && p->Bullet.x2 >= j->Plane.x1-5 && p->Bullet.y2 <= j->Plane.y2+5 && p->Bullet.y2 >= j->Plane.y1-5) {              //nmmd���˰��첻�ɹ���ԭ����hitbox̫С��
				//boomPlane = &j->Plane;
				if (q) {
					q->next_Bullet = p->next_Bullet;
				}
				else {
					Magazine = p->next_Bullet;
				}
				if (k) {
					k->next_Plane = j->next_Plane;
				}
				else {
					Planegroup = j->next_Plane;
				}
				/*printf("bullet: x1 = %d,y1 = %d,x2 = %d,y2 = %d\t", p->Bullet.x1, p->Bullet.y1, p->Bullet.x2, p->Bullet.y2);
				printf("plane: x1 = %d,y1 = %d,x2 = %d,y2 = %d\n", j->Plane.x1, j->Plane.y1, j->Plane.x2, j->Plane.y2);*/
				//printf(" 1 ");
				Creat_boom(j);
				free(p);
				free(j);
				
				//printf(" *\n");
				turn = 1;
				break;
			}
		}
		if (turn) {
			//printf(" & ");
			return 1;
		}
	}
	//printf(" 0 ");
	return 0;
}
//-----------------------------------------------------------------------------MODEL-----------------------------------------------------------------------------//
 
//-----------------------------------------------------------------------------CTRL-----------------------------------------------------------------------------//
void keyListener(int key, int event) {
	switch (key)
	{
	case 'A':    //��������
		Turret.x1 -= tStep_x; Turret.x2 -= tStep_x;           //ͬʱ�ƶ��������ڹ�
		Pipe.x1 -= tStep_x; Pipe.x2 -= tStep_x;
		Pipe.x3 -= tStep_x; Pipe.x4 -= tStep_x;
		temp_Pipe.x1 -= tStep_x; temp_Pipe.x2 -= tStep_x;     //��λ�ƺ����긳ֵ����һ�ֵ�temp_Pipe;
		temp_Pipe.x3 -= tStep_x; temp_Pipe.x4 -= tStep_x;
		Creat_Turret();
		Creat_All();
		break;
	case 'D':    //��������
		Turret.x1 += tStep_x; Turret.x2 += tStep_x;
		Pipe.x1 += tStep_x; Pipe.x2 += tStep_x;
		Pipe.x3 += tStep_x; Pipe.x4 += tStep_x;
		temp_Pipe.x1 += tStep_x; temp_Pipe.x2 += tStep_x;
		temp_Pipe.x3 += tStep_x; temp_Pipe.x4 += tStep_x;
		Creat_Turret();
		Creat_All();
		break;
	case 'Q':    //�����ڹ�
		Creat_Pipe(key, event);
		Creat_All();
		break;
	case 'E':    //�����ڹ�
		Creat_Pipe(key, event);
		Creat_All();
		break;
	case ' ':    //�����ӵ������ҷ���
	{
		if (event == 1) {
			load_Bullet();    //�����ӵ�
			load_Magazine();  //װ���ӵ�
			Creat_All();
			break;
		}
	}
	}
}
void timerListener(int id) {
	delete_Plane();
	delete_Bullet();
	if (id == 3) {
		test_Crash();          //�����ײ
	}
	if (id == 1) {             //�����ӵ�
			Shot_Bullet();
			Creat_All();
	}
	if (id == 2) {             //���Ʒɻ�
		cnt_plane++;
		if (cnt_plane % 12 == 0) {         //��ʱ�����ɻ�
			load_Plane();
			load_Planegroup();
		}
		Creat_Plane();
		Creat_All();
	}
	Creat_All();
}
//-----------------------------------------------------------------------------CTRL-----------------------------------------------------------------------------//
 
