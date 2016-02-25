#include <iostream.h>
#include <conio.h>
#include <stdlib.h>
#include <graphics.h>
#include <dos.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#define ROUND(a) ((int)(a+0.5))


//Global variables
//group1 gun
  int w,h;
  int xgb,xge1,xge2;
  int ygb,yge1,yge2;
//group2 bullet
     int numBullets;
     int movebx[10];
     int moveby[10];
     int moving[10];
     int xb,yb;
     int xinc[10];

//group3  global
 int score=0;
 int counter=0;

class Gun
{ private:

   public:
     void drawBase();
     void initialize();
     void drawGun();
     void adjustGun(int);
};
//=======================================
void Gun::initialize()
{  xgb=getmaxx()/2-10;
   ygb=getmaxy();
   w=20;
   h=80;
   xge1=xgb;
   xge2=xgb+w;
   yge1=ygb-h;
   yge2=yge1;
}
//===================================
void Gun::drawBase()
{  setcolor(YELLOW);
   ellipse(xgb+10,ygb,0,360,40,15);
   line(xgb,ygb,xgb-30,ygb);
   line(xgb+w,ygb,xgb+50,ygb);
}
//=================================
void Gun::drawGun()
{ setcolor(YELLOW);
  line(xgb,ygb,xge1,yge1);
  line(xgb+w,ygb,xge2,yge2);
  line(xge1,yge1,xge2,yge2);
}
//===================================
void Gun::adjustGun(int key)
{
    int x,y;
     double T=5*M_PI/180;
     setcolor(0);
     line(xgb,ygb,xge1,yge1);
     line(xgb+w,ygb,xge2,yge2);
     line(xge1,yge1,xge2,yge2);

     if(key==110) exit(1);
     else if(key==77)
     { x=xge1;
       y=yge1;
       xge1=ROUND((x-xgb)*cos(T)+(ygb-y)*sin(T)+xgb);
       yge1=ROUND((y-ygb)*cos(T)+(x-xgb)*sin(T)+ygb);

       x=xge2;
       y=yge2;
       xge2=ROUND((x-xgb-w)*cos(T)+(ygb-y)*sin(T)+xgb+w);
       yge2=ROUND((y-ygb)*cos(T)+(x-xgb-w)*sin(T)+ygb);
     }
     else if(key==75)
     { x=xge1;
       y=yge1;
       xge1=ROUND((x-xgb)*cos(T)-(ygb-y)*sin(T)+xgb);
       yge1=ROUND((y-ygb)*cos(T)-(x-xgb)*sin(T)+ygb);

       x=xge2;
       y=yge2;
       xge2=ROUND((x-xgb-w)*cos(T)-(ygb-y)*sin(T)+xgb+w);
       yge2=ROUND((y-ygb)*cos(T)-(x-xgb-w)*sin(T)+ygb);
     }
    setcolor(YELLOW);
    line(xgb,ygb,xge1,yge1);
    line(xgb+w,ygb,xge2,yge2);
    line(xge1,yge1,xge2,yge2);
    drawBase();

}
//=============================================
class bullet
{  private:
   public:

     void initialize();
     void drawBullet();
     void incrementMoveb();
     void chkBulletOut();
     void shootBullet(int);

};
//=================================================
void bullet::initialize()
{ numBullets=10;
  for(int i=0;i<numBullets;i++)
  { xinc[i]=movebx[i]=moveby[i]=moving[i]=0;
  }
}
//===============================
void bullet::drawBullet()
{
  xb=ROUND((xge1+xge2)/2.0);
  yb=ROUND((yge1+yge2)/2.0);
  for(int i=0;i<numBullets;i++)
  {  //pieslice(xb+movebx[i],yb-moveby[i],0,360,5);
     circle(xb+movebx[i],yb-moveby[i],5);
  }
  setcolor(0);
   //setfillstyle(EMPTY_FILL,getmaxcolor());
   //pieslice(xb,yb,0,360,5);
   circle(xb,yb,5);
}
//====================================
void bullet::shootBullet(int key)
{  if(key==72)
   {
     for(int i=0;i<numBullets;i++)
     { if(moving[i]==0)
       { moving[i]=1;
	 xinc[i]=ROUND(20*(xge1-xgb)/(double)(ygb-yge1));
	 counter++;
	 if(counter>=50&&score>=10)
	 {  char scr[10];
	     setcolor(0);
	    // sprintf(scr,"SCORE:  %d",score);
	     //outtextxy(470,430,scr);
	     setcolor(YELLOW);
	     score-=10;
	     //sprintf(scr,"SCORE:  %d",score);
	     //outtextxy(470,430,scr);
	     counter=0;
	 }
	 break;
	}
     }
   }
}
//=======================================
void bullet::incrementMoveb()
{ for(int i=0;i<numBullets;i++)
  { if(moving[i]==1)
    {  moveby[i]+=20;
       movebx[i]+=xinc[i];
    }
  }
}
//====================================
void bullet::chkBulletOut()
{ for(int i=0;i<numBullets;i++)
  { if(moveby[i]>getmaxy()||movebx[i]<-getmaxx()/2+50||movebx[i]>getmaxx()/2-50)
    { xinc[i]=moveby[i]=movebx[i]=moving[i]=0;
    }
  }
}
//=====================================
class plane
{ private:
    int numPlanes;
    int lastSpace;
    int movep[10];
    int nump1,nump2;
    int xincbmb, yincbmb;
    int yincMan;
    int bDropd,mDropd;
    int expldD2Bmb,expldD2Mn;
    int random2;

  public:
    void initialize();
    void drawPlane();
    void drawPlane2();
    void dropMan();
    void incrementMovep();

    void checkPlaneOut();
    void chkHit(bullet);
    void chkExplosionBmb();
    void chkBombHit();
    void chkManBelow();
    void chkManHit();
    void dropBomb();
    void play();
    void gameOver();
    //void start();
    void printScore();
};
void plane::printScore()
{ char scr[3];
  //restorecrtmode();
 // sprintf(scr,"SCORE:  %d",score);

 // setgraphmode(getgraphmode());
  setcolor(MAGENTA);
  outtextxy(470,430,scr);
}

//======================================
void plane::dropMan()
{   int pln;
    if(mDropd==0)
    {  pln=random(10);
       random2=random(20)+10;
    }
   if(movep[pln]>=15+15*(random2)&&movep[pln]<=40+15*random2) mDropd=1;
   if(mDropd)
   {  setcolor(0);
      ellipse(30+15*(random2),40+yincMan,0,360,10,30);
      yincMan+=10;
      setcolor(RED);
      ellipse(30+15*(random2),40+yincMan,0,360,10,30);
   }
}
//======================================
void plane::chkManBelow()
{ if(40+yincMan>getmaxy()+40)
  {  char scr[10];
     mDropd=0;
     yincMan=0;
    // printScore();
    // sprintf(scr,"SCORE:  %d",score);
    // outtextxy(470,430,scr);
     setcolor(YELLOW);
     if(score>=20)
     {  score-=20;
     }
    // printScore();
    // sprintf(scr,"SCORE:  %d",score);
    // outtextxy(470,430,scr);
     expldD2Mn++;
     if(expldD2Mn==30)
     { gameOver(); //exit(1);
     }

  }
}
//==========================================

void plane::chkManHit()
{  for(int blt=0;blt<numBullets;blt++)
   { if( 15+15*random2<=xb+movebx[blt] && xb+movebx[blt]<=45+15*random2
      && 10+yincMan<=yb-moveby[blt] && yb-moveby[blt]<=yincMan+70
      && movebx[blt]!=0)
   {
	 char scr[10];
	  setcolor(0);
	  ellipse(30+15*random2,40+yincMan,0,360,10,30);

	  mDropd=0;
	  yincMan=0;
	//  printScore();
	//  sprintf(scr,"SCORE:  %d",score);
	//  outtextxy(470,430,scr);
	  setcolor(YELLOW);
	  score+=20;
	//  printScore();
	  //sprintf(scr,"SCORE:  %d",score);
	  //outtextxy(470,430,scr);
      }
   }
}

//================================================

void plane::dropBomb()
{  int pln;
   if(bDropd==0)
   {  pln=rand()%10;
   }
   if(movep[pln]>=15 && movep[pln]<=45) bDropd=1;
   if(bDropd)
   {  setcolor(0);
      circle(25+xincbmb,40+yincbmb,7);

      xincbmb+=6;//-15*(random1);
      yincbmb+=8;
      setcolor(RED);
      circle(25+xincbmb,40+yincbmb,7);
   }
}
//===================================================
void plane::chkBombHit()
{  for(int blt=0;blt<numBullets;blt++)
   { if( 5+xincbmb<=xb+movebx[blt] && xb+movebx[blt]<=30+xincbmb
      && 33+yincbmb<=yb-moveby[blt] && yb-moveby[blt]<=47+yincbmb
      && movebx[blt]!=0)
      {   char scr[10];
	  setcolor(0);
	  circle(25+xincbmb,40+yincbmb,7);

	  bDropd=0;
	  xincbmb=yincbmb=0;
	 // printScore();
	 // sprintf(scr,"SCORE:  %d",score);
	 // outtextxy(470,430,scr);
	  setcolor(YELLOW);
	  score+=50;
	  //printScore();
	 // sprintf(scr,"SCORE:  %d",score);
	 // outtextxy(470,430,scr);
      }
  }
}
//======================================

void plane::chkExplosionBmb()
{  if(yincbmb>getmaxy()-70)
   {
     setcolor(RED);
     circle(25+xincbmb,40+yincbmb,10);
     circle(25+xincbmb,40+yincbmb,15);
     circle(25+xincbmb,40+yincbmb,20);
     delay(20);
     setcolor(0);
     circle(25+xincbmb,40+yincbmb,10);
     circle(25+xincbmb,40+yincbmb,15);
     circle(25+xincbmb,40+yincbmb,20);

     circle(25+xincbmb,40+yincbmb,7);
     bDropd=0;

     xincbmb=yincbmb=0;
     expldD2Bmb++;
     if(expldD2Bmb==30)
     { gameOver(); //exit(1);
     }
  }
}
//=======================================
void plane::initialize()
{  time_t t;
   srand(time(&t));
   numPlanes=10;

  //bomb related variables
  bDropd=mDropd=0;
  random2=0;
  expldD2Bmb=expldD2Mn=0;
  xincbmb=yincbmb=0;
  yincMan=0;

  movep[0]=-165;
  for(int i=1;i<numPlanes;i++)
  { movep[i]=movep[i-1]-165;
  }
  lastSpace=movep[9];//-15*rand()%10;
}
//=========================================
void plane::drawPlane()
{ for(int i=0;i<numPlanes;i++)
  { line(0+movep[i],20,25+movep[i],20);
    line(8+movep[i],20,8+movep[i],35);
    line(12+movep[i],20,12+movep[i],30);
    line(12+movep[i],30,27+movep[i],30);
    line(8+movep[i],35,27+movep[i],35);
    line(27+movep[i],30,27+movep[i],35);
    line(27+movep[i],30,50+movep[i],20);
    line(50+movep[i],20,70+movep[i],20);
    line(60+movep[i],20,60+movep[i],10);
    line(45+movep[i],10,75+movep[i],10);
    line(70+movep[i],20,80+movep[i],27);
    line(27+movep[i],35,37+movep[i],35);
    line(37+movep[i],35,40+movep[i],40);
    line(40+movep[i],40,70+movep[i],40);
    line(70+movep[i],40,80+movep[i],35);
    line(80+movep[i],27,80+movep[i],35);

    line(39+movep[i],25,70+movep[i],24);
    line(70+movep[i],24,80+movep[i],27);
  }
}
//===========================================
void plane::incrementMovep()
{ for(int i=0;i<numPlanes;i++)
  { movep[i]+=15;
  }
  lastSpace+=15;
}
//===========================================
void plane::checkPlaneOut()
{ for(int i=0;i<numPlanes;i++)
  { if(movep[i]>getmaxx()+80)
    {  movep[i]=lastSpace;
       lastSpace=movep[i]-165-15*random(10);


 //   movep[i]=lastSpace;
   //   lastSpace=lastSpace-165-15*rand()%10;
    }
  }
}
//=====================================================
void plane::chkHit(bullet b)
{ for(int pln=0;pln<numPlanes;pln++)
  { for(int blt=0;blt<numBullets;blt++)
    {  if(movep[pln]<=xb+movebx[blt] && xb+movebx[blt]<=movep[pln]+80
	  &&10<yb-moveby[blt]&&yb-moveby[blt] <35)
	{ char scr[10];

	  setcolor(RED);
	  circle(movep[pln]+40,30,30);
	  circle(movep[pln]+40,30,20);
	  circle(movep[pln]+40,30,10);
	  circle(movep[pln]+40,30,5);
	  circle(movep[pln]+40,30,3);

	  setcolor(0);
	  sound(20000);
	  delay(50);
	  nosound();

	  circle(movep[pln]+40,30,30);
	  circle(movep[pln]+40,30,20);
	  circle(movep[pln]+40,30,10);
	  circle(movep[pln]+40,30,5);
	  circle(movep[pln]+40,30,3);
	  drawPlane();
	  b.drawBullet();
	  movep[pln]=lastSpace;
	  lastSpace=movep[pln]-165-15*random(10);
	  moveby[blt]=movebx[blt]=0;
	  moving[blt]=0;

	  printScore();
	 // sprintf(scr,"SCORE:  %d",score);
	 // outtextxy(470,430,scr);
	  setcolor(YELLOW);
	  score+=10;
	  printScore();
	 // sprintf(scr,"SCORE:  %d",score);
	 // outtextxy(470,430,scr);
	}
     }
   }
}
//==============================================
//=============================================
void plane::play()
{
  cleardevice();
  setcolor(YELLOW);
  outtextxy(10,440,"press N to stop the game!");

  Gun g;
  bullet b;
  g.initialize();
  g.drawBase();
  g.drawGun();
  b.initialize();
  initialize();
  while(1)
  {  setcolor(WHITE);
     drawPlane();
     if(kbhit())
     { int key=getch();
       g.adjustGun(key);
       b.shootBullet(key);
     }
     b.drawBullet();
     chkHit(b);
     dropBomb();
     dropMan();
     chkExplosionBmb();
     chkBombHit();
     chkManHit();
     chkManBelow();

     delay(50);

     setcolor(0);
     b.drawBullet();
     drawPlane();
     b.incrementMoveb();
     b.chkBulletOut();

     incrementMovep();
     checkPlaneOut();
     setcolor(CYAN);
     outtextxy(10,440,"press N to stop the game!");
  }
}
//================================
void plane::gameOver()
{    char scr[10];
     cleardevice();
     setcolor(YELLOW);
     //getch();
     //getch();
     outtextxy(160,50,"Congratulations!");
    // sprintf(scr," YOUR SCORE IS :  %d   Points",score);
    // outtextxy(160,150,scr);
   //  sprintf(scr,"You Have Missed %d Men and have been fired by %d bullets",expldD2Bmb,expldD2Mn);
    // outtextxy(160,200,scr);
    // outtextxy(180,30,"press Y to continue or any other key to stop.");


     int check=getch();
     if(check==121)
     {  cleardevice();
	plane p;
	p.play();
     }

      exit(1);

}
//====================================
int main(int argc, char* argv[])
{  int gd=DETECT,gm;
   int check;
   initgraph(&gd,&gm,"c:\\tc\\bgi");
   do
   {  cleardevice();
      outtextxy(160,20,"Programmed in December 19/1998 ");
      outtextxy(160,50,"By Tech. Tseghai @mit.local");
      outtextxy(160,80,"Computer Science and Eng. Department.");
      outtextxy(160,110,"Class Year IV.");

      outtextxy(180,200,"press Enter to Play!");
      check=getch();
      if(check==13)
      {  plane p;
	 p.play();
      }
      cleardevice();
      outtextxy(180,30,"press Y to continue!");
      check=getch();
   }
   while(check==121);
   getch();
   return 0;
}

//=========================================
/*void plane::drawPlane1()
{
    for(int i=0;i<numPlanes;i++)
    {
      ellipse(-73+movep[i],30,0,360,10,5);

      line(-83+movep[i],30,-63+movep[i],30);
      line(-73+movep[i],25,-73+movep[i],35);

      line(-73+movep[i],35,-70+movep[i],40);
      line(-73+movep[i],25,-60+movep[i],40);

      line(-70+movep[i],40,-60+movep[i],40);
      ellipse(-30+movep[i],40,0,360,30,15);

      line(-20+movep[i],55,-15+movep[i],60);
      ellipse(-15+movep[i],63,0,360,5,3);

      line(-33+movep[i],55,-28+movep[i],60);
      ellipse(-28+movep[i],63,0,360,5,3);


      line(-30+movep[i],25,-30+movep[i],10);
      ellipse(-30+movep[i],15,0,360,15,5);
      line(-30+movep[i],15,-30+movep[i],10);
      line(-45+movep[i],15,-15+movep[i],15);
    }
}
//===========================================
void plane::drawPlane2()
{  for(int i=0;i<numPlanes;i++)
   { line(0+movep[i],10,10+movep[i],8);
    line(10+movep[i],8,20+movep[i],20);
    line(0+movep[i],10,20+movep[i],30);
    line(20+movep[i],30,20+movep[i],40);
    line(20+movep[i],40,120+movep[i],40);
    line(35+movep[i],40,30+movep[i],45);
    line(30+movep[i],45,40+movep[i],45);
    line(45+movep[i],40,40+movep[i],45);
    line(80+movep[i],18,120+movep[i],40);
    line(50+movep[i],18,80+movep[i],18);
    line(40+movep[i],3,50+movep[i],20);
    line(25+movep[i],8,40+movep[i],3);
    line(40+movep[i],20,25+movep[i],8);
    line(20+movep[i],20,40+movep[i],20);

    line(25+movep[i],30,80+movep[i],28);
    line(80+movep[i],28,120+movep[i],40);

  }
}
//=========================================
*/
