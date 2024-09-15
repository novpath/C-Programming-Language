/*示例程序来源：https://blog.csdn.net/LuHe123_ye/article/details/121715280*/
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
 
typedef struct _magazine {        //链表存储子弹
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
	
		int x1;  //左上
		int y1;
	
		int x2;  //左下
		int y2;
	
		int x3;  //右下
		int y3;
	
		int x4;  //右上
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
typedef struct _planegroup {        //链表存储子弹
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
void Creat_All(void);      //重新绘制所有图形
//-----view-----//
//-----model-----//
void load_Bullet(void);    //加载炮管内子弹
void load_Magazine(void);  //加载弹夹  
void load_Plane(void);     //加载飞机
void load_Planegroup(void);//加载飞机组
void load_Planetnt(void); //加载飞机炸弹 
void delete_Plane(void);   //超出画面就删除
void delete_Bullet(void);   //超出画面就删除
int test_Crash(void);     //检测碰撞
//-----model-----//
//-----ctrl-----//
void keyListener(int key, int event);
void timerListener(int id);
//-----ctrl-----//
 
 
 
PIPE   Pipe = { OLpipex,OLpipey - a, OLpipex,OLpipey, ORpipex,ORpipey,  ORpipex,ORpipey - a ,0 };         //初始化所有物件位置
PIPE   temp_Pipe = { OLpipex,OLpipey - a, OLpipex,OLpipey, ORpipex,ORpipey,  ORpipex,ORpipey - a ,0 };    //用于记录每次炮管的坐标
TURRET Turret = { OTturretx,OTturrety,OBturretx,OBturrety };
BULLET tBullet;             //初始化一个子弹，但不进行赋值，在load_Bullet后才进行赋值，以同步发射时和炮台的相对位置,每次存进链表后会被更新
PLANE tPlane;               //初始化一个飞机，每次存进链表后会被更新
//PLANE* boomPlane;           //指向爆炸的飞机
MAGAZINE* Magazine = NULL;     //创建一个链表弹夹
BULLET* pBullet = NULL;        //只控制炮管内上膛的子弹坐标，发射后指向下一颗子弹
PLANEGROUP* Planegroup = NULL; //创建一个链表机组
TEXT count_text;               //创建计分板
   
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
	startTimer(1, 50);    //子弹用
	startTimer(2, 50);   //飞机用
	startTimer(3, 1);    //碰撞用
	return 0;
}
//-----------------------------------------------------------------------------MAIN-----------------------------------------------------------------------------//
 
 
 
//-----------------------------------------------------------------------------VIEW-----------------------------------------------------------------------------//
void Creat_Turret(void) {                       //绘制炮塔
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
			temp_Pipe.angle = Pipe.angle++;       //调整角度
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
			{temp_Pipe.x1,temp_Pipe.y1},    //抬起键位的时候再输出一遍上次的图像，防止闪屏
			{temp_Pipe.x2,temp_Pipe.y2},
			{temp_Pipe.x3,temp_Pipe.y3},
			{temp_Pipe.x4,temp_Pipe.y4},
		};
		polygon(posPipe, 4);
	}
	endPaint();
}
void Shot_Bullet(void) {
	if (Magazine) {           //只有弹夹初始化后才能发射
		for (MAGAZINE* pMagazine = Magazine; pMagazine;pMagazine = pMagazine->next_Bullet) {   //找节点，如果存在就改变坐标，画子弹
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
void Creat_OTurret(void) {    //同时间内其他项目会将此时的画面clear，需要再输出一次上次的坐标
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
			{temp_Pipe.x1,temp_Pipe.y1},    //抬起键位的时候再输出一遍上次的图像，防止闪屏
			{temp_Pipe.x2,temp_Pipe.y2},
			{temp_Pipe.x3,temp_Pipe.y3},
			{temp_Pipe.x4,temp_Pipe.y4},
	};
	polygon(posPipe, 4);
	endPaint();
}
void Shot_OBullet(void) {     
	if (Magazine) {              //只有弹夹初始化后才能发射
		for (MAGAZINE* pMagazine = Magazine; pMagazine; pMagazine = pMagazine->next_Bullet) {  //找节点，如果存在就画子弹
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
void load_Bullet(void) {                  //根据炮管坐标初始化子弹位置
	tBullet.bangle = Pipe.angle;
	tBullet.x1 = (temp_Pipe.x1 + temp_Pipe.x4) / 2 - Bulletwidth / 2;
	tBullet.y1 = temp_Pipe.y1;
	tBullet.x2 = tBullet.x1 + Bulletwidth;
	tBullet.y2 = tBullet.y1 + Bulletlength;
}
void load_Magazine(void) {                //链表弹夹添加子弹
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
void load_Plane(void) {           //飞机y坐标随机产生   
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
void load_Planegroup(void) {            //将产生的飞机写入链表
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
void delete_Plane(void) {                     //超出画面的就删除
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
void delete_Bullet(void) {                     //超出画面的就删除
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
int test_Crash(void) {                        //检测子弹和飞机的碰撞（通过坐标是否在范围内判断）；
	int turn = 0;
	MAGAZINE* q = NULL;
	MAGAZINE* p = Magazine;
	for ( ; p; q = p, p = p->next_Bullet ) {
		PLANEGROUP* k = NULL;
		PLANEGROUP* j = Planegroup;
		for ( ; j; k = j, j = j->next_Plane ) {
			if (p->Bullet.x1 >= j->Plane.x1-5 && p->Bullet.x1 <= j->Plane.x2+5 && p->Bullet.y1 >= j->Plane.y1-5 && p->Bullet.y1 <= j->Plane.y2+5 && \
				p->Bullet.x2 <= j->Plane.x2+5 && p->Bullet.x2 >= j->Plane.x1-5 && p->Bullet.y2 <= j->Plane.y2+5 && p->Bullet.y2 >= j->Plane.y1-5) {              //nmmd整了半天不成功，原来是hitbox太小了
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
	case 'A':    //左移炮塔
		Turret.x1 -= tStep_x; Turret.x2 -= tStep_x;           //同时移动炮塔和炮管
		Pipe.x1 -= tStep_x; Pipe.x2 -= tStep_x;
		Pipe.x3 -= tStep_x; Pipe.x4 -= tStep_x;
		temp_Pipe.x1 -= tStep_x; temp_Pipe.x2 -= tStep_x;     //将位移后坐标赋值给上一轮的temp_Pipe;
		temp_Pipe.x3 -= tStep_x; temp_Pipe.x4 -= tStep_x;
		Creat_Turret();
		Creat_All();
		break;
	case 'D':    //右移炮塔
		Turret.x1 += tStep_x; Turret.x2 += tStep_x;
		Pipe.x1 += tStep_x; Pipe.x2 += tStep_x;
		Pipe.x3 += tStep_x; Pipe.x4 += tStep_x;
		temp_Pipe.x1 += tStep_x; temp_Pipe.x2 += tStep_x;
		temp_Pipe.x3 += tStep_x; temp_Pipe.x4 += tStep_x;
		Creat_Turret();
		Creat_All();
		break;
	case 'Q':    //左倾炮管
		Creat_Pipe(key, event);
		Creat_All();
		break;
	case 'E':    //右倾炮管
		Creat_Pipe(key, event);
		Creat_All();
		break;
	case ' ':    //加载子弹，并且发射
	{
		if (event == 1) {
			load_Bullet();    //加载子弹
			load_Magazine();  //装填子弹
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
		test_Crash();          //检测碰撞
	}
	if (id == 1) {             //控制子弹
			Shot_Bullet();
			Creat_All();
	}
	if (id == 2) {             //控制飞机
		cnt_plane++;
		if (cnt_plane % 12 == 0) {         //定时产生飞机
			load_Plane();
			load_Planegroup();
		}
		Creat_Plane();
		Creat_All();
	}
	Creat_All();
}
//-----------------------------------------------------------------------------CTRL-----------------------------------------------------------------------------//
 
