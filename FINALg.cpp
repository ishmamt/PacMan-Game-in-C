#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdbool.h>
#include<math.h>
#include<graphics.h>
#include<time.h>
using namespace std;
#define ERROR puts("Error");


int maxx=639,maxy=479;
char map[100][100];
int H=20,W=41;
int page=0;
int f=0;


struct coord
{
   int x;
   int y;
};
struct PacMan {
   struct coord position;
   int vx;
   int vy;
   int lives;
   int score;
   int pulse;
   int dir;
};
struct Ghost {
    struct coord position;
    int vx;
    int vy;
    int food;
    int pulse;
    int dir;
};
struct PacMan player={
                        {
                            .x=1,
                            .y=1,
                        },
                        .vx=0,
                        .vy=0,
                        .lives=4,
                        .score=0,
                        .pulse=1,
                        .dir=1
                     };
struct Ghost ghost1={
                        {
                            .x=14,
                            .y=7,
                        },
                        .vx=0,
                        .vy=0,
                        .food=1,
                        .pulse=2,
                        .dir=0
                    };
struct Ghost ghost2={
                        {
                            .x=1,
                            .y=9,
                        },
                        .vx=0,
                        .vy=0,
                        .food=1,
                        .pulse=2,
                        .dir=0
                    };
struct Ghost ghost3={
                        {
                            .x=29,
                            .y=3,
                        },
                        .vx=0,
                        .vy=0,
                        .food=1,
                        .pulse=2,
                        .dir=0
                    };
struct score
{
    int post;
    char initials[3];
    int scr;
}fp[100];
//34 8
//639 479


void mapread();
void mapping();
void foodinit();
void init();
void user_input();
void player_movement();
void show();
void intro();
void menu();
void ghost_movement();
void ghost_direction();
void game_over();
void scoreadd();
int scorereader();
void highscoredisplay();


int main()
{
    int gd=DETECT,gm;
    char test[100];
    initgraph(&gd,&gm,NULL);
    intro();
    menu();
    init();
    while(1)
    {
        setactivepage(page);
        setvisualpage(1-page);
        setfillstyle(1, 0);
        bar(0,0,640, 480);
        mapping();
        ghost_direction();
        user_input();
        player_movement();
        ghost_movement();
        if(player.lives<=1)
        {
            delay(100);
            game_over();
        }
        delay(100);
        page=1-page;
    }
    closegraph();
    return 0;
}
void mapread()
{
    FILE *fp;
    int i=0,j=0;
    char p;
    if((fp=fopen("map1.txt","r"))==NULL)
    {
        ERROR;
        exit(1);
    }
    while(!feof(fp))
    {
        if((p=fgetc(fp))!='\n')
        {
            map[i][j]=p;
            j++;
        }
        else
        {
            map[i][j]=p;
            i++;
            j=0;
        }
    }
    map[i][j]='\0';
    fclose(fp);
    return;
}
void mapping()
{
    int x=0,y=0,i,j,r=4,x1,y1;
    char text[100];
    for(i=1;i<=H;i++)
    {
        for(j=1;j<=W;j++)
        {
            if(map[i-1][j-1]=='#')
            {
                setfillstyle(SOLID_FILL,RED);
                bar(x,y,x+20,y+15);
                x+=20;
            }
            else if(map[i-1][j-1]=='.')
            {
                circle(x+5,y+5,1);
                f++;
                x+=20;
            }
            else if(map[i-1][j-1]==' ')
            {
                x+=20;
            }
            else if(map[i-1][j-1]=='0')
            {
                if(player.pulse)
                {
                    if(player.dir==3)
                    {
                        circle(x+5,y+8,0);
                        readimagefile("pac_3.jpg",x,y,14+x,14+y);
                    }
                    else if(player.dir==4)
                    {
                        circle(x+5,y+8,0);
                        readimagefile("pac_4.jpg",x,y,14+x,14+y);
                    }
                    else if(player.dir==1)
                    {
                        circle(x+5,y+8,0);
                        readimagefile("pac_1.jpg",x,y,14+x,14+y);
                    }
                    else if(player.dir==2)
                    {
                        circle(x+5,y+8,0);
                        readimagefile("pac_2.jpg",x,y,14+x,14+y);
                    }
                    player.pulse=0;
                }
                else
                {
                    readimagefile("pac_0.jpg",x,y,14+x,14+y);
                    player.pulse=1;
                }
                x+=20;
            }
            else if(map[i-1][j-1]=='G')
            {
                x1=x+5;
                y1=y+4;
                setcolor(WHITE);
                //circle(x+5,y+8,4);
                //readimagefile("ghost_1.jpg",x,y,13+x,13+y);
                setcolor(MAGENTA);
                setfillstyle(SOLID_FILL,MAGENTA);
                circle(x1,y1,r);
                floodfill(x1,y1,MAGENTA);
                rectangle(x1-r-1,y1,x1+r,y1+9);
                floodfill(x1-r,y1+1,MAGENTA);
                x+=20;
                ghost1.position.x=j-1;
                ghost1.position.y=i-1;
                setcolor(WHITE);
            }
            else if(map[i-1][j-1]=='P')
            {
                x1=x+5;
                y1=y+4;
                setcolor(WHITE);
                //circle(x+5,y+8,4);
                //readimagefile("ghost_2.jpg",x,y,13+x,13+y);
                setcolor(CYAN);
                setfillstyle(SOLID_FILL,CYAN);
                circle(x1,y1,r);
                floodfill(x1,y1,CYAN);
                rectangle(x1-r-1,y1,x1+r,y1+9);
                floodfill(x1-r,y1+1,CYAN);
                x+=20;
                ghost2.position.x=j-1;
                ghost2.position.y=i-1;
                setcolor(WHITE);
            }
            else if(map[i-1][j-1]=='X')
            {
                x1=x+5;
                y1=y+4;
                setcolor(WHITE);
                //circle(x+5,y+8,4);
                //readimagefile("ghost_3.jpg",x,y,13+x,13+y);
                setcolor(GREEN);
                setfillstyle(SOLID_FILL,GREEN);
                circle(x1,y1,r);
                floodfill(x1,y1,GREEN);
                rectangle(x1-r-1,y1,x1+r,y1+9);
                floodfill(x1-r,y1+1,GREEN);
                x+=20;
                ghost3.position.x=j-1;
                ghost3.position.y=i-1;
                setcolor(WHITE);
            }
        }
        x=0;y=(15*i);
    }
    settextstyle(2,0,27);
    sprintf(text,"Score: %d    Lives: %d",player.score,player.lives-1);
    outtextxy(180,350,text);


}
void foodinit()
{
    int i,j;
    for(i=0;i<H;i++)
    {
        for(j=0;j<W;j++)
        {
            if(map[i][j]==' ')
            {
                map[i][j]='.';
            }
        }

    }
}
void init()
{
    mapread();
    foodinit();
    mapping();
}
void user_input()
{
    char choice,c;
    while(1)
    {
        if(GetAsyncKeyState(VK_UP))
        {
            player.vy=-1;
            player.vx=0;
            player.dir=3;
            return;
        }
        else if(GetAsyncKeyState(VK_DOWN))
        {
            player.vy=1;
            player.vx=0;
            player.dir=4;
            return;
        }
        else if(GetAsyncKeyState(VK_LEFT))
        {
            player.vx=-1;
            player.vy=0;
            player.dir=2;
            return;
        }
        else if(GetAsyncKeyState(VK_RIGHT))
        {
            player.vx=1;
            player.vy=0;
            player.dir=1;
            return;
        }
        else if(GetAsyncKeyState(VK_ESCAPE))
        {
            game_over();
        }
        else
        {
            return;
        }
    }
}
void player_movement()
{
    int x,y;
    if(map[player.position.y][player.position.x]=='G'||map[player.position.y][player.position.x]=='P'||map[player.position.y][player.position.x]=='X')
    {
        player.lives--;
        player.position.x=1;
        player.position.y=1;
        if(player.lives==0)
        {
            game_over();
        }
    }
    map[player.position.y][player.position.x]=' ';
    x=player.position.x+player.vx;
    y=player.position.y+player.vy;
    if(map[y][x]=='#')
    {
        player.vx=0;
        player.vy=0;
    }
    player.position.x+=player.vx;
    player.position.y+=player.vy;
    if(map[player.position.y][player.position.x]=='.')
    {
        player.score++;
    }
    if(map[player.position.y][player.position.x]=='G'||map[player.position.y][player.position.x]=='P'||map[player.position.y][player.position.x]=='X')
    {
        player.lives--;
        player.position.x=1;
        player.position.y=1;
    }
    if(f==0)
    {
        game_over();
    }
    map[player.position.y][player.position.x]='0';
}
void show()
{
    int i,j;
    for(i=0;i<H;i++)
    {
        for(j=0;j<W;j++)
        {
            printf("%c",map[i][j]);
        }
    }
    system("cls");
}
void intro()
{
    /*int gd=DETECT, gm;

initgraph(&gd,&gm,NULL);


    initgraph(&gd,&gm,NULL);*/
    settextstyle(3,HORIZ_DIR,4);
    outtextxy(145,50,"Presented By:");
    readimagefile("logo.jpg",200,160,200+200,160+200);
    delay(2000);
    cleardevice();
    outtextxy(90,200,"Press Enter to skip the intro");
    delay(1000);
    cleardevice();
    int i=0,key=0;
while(i<450)
{
    if(kbhit())
    {
        //key=getch();
        if(key=getch())
        {
            return;
        }
    }
setcolor(BLUE);
       setfillstyle(SOLID_FILL,BLUE);
    circle(100+i,200,70);


//setcolor(BLACK);
//setfillstyle(SOLID_FILL,BLACK);
line(100+i,200,162+i,166);

    line(100+i,200,162+i,237);
    floodfill(98+i,200,BLUE);
    setcolor(BLACK);
    circle(100+i,200,70);
    line(100+i,200,162+i,166);

    line(100+i,200,162+i,237);
    setfillstyle(SOLID_FILL ,BLACK);
floodfill(150+i,200,BLACK);

setcolor(BLACK);
circle(100+i,200,70);
setfillstyle(SOLID_FILL,BLACK);
floodfill(0+i,50,BLACK);
delay(150);

cleardevice();

setcolor(BLUE);
circle(100+i,200,70);
setfillstyle(SOLID_FILL,BLUE);
floodfill(100+i,200,BLUE);
setcolor(BLACK);
circle(100+i,200,70);
setfillstyle(SOLID_FILL,BLACK);
floodfill(0+i,50,BLACK);

i=i+30;
delay(150);
cleardevice();
}
delay(1000);
setcolor(YELLOW);
setfillstyle(SOLID_FILL,YELLOW);
settextstyle(3,HORIZ_DIR,20);
outtextxy(40,170,"PACMAN");
delay(2000);
cleardevice();
//settextstyle(9,HORIZ_DIR,2.5);
//outtextxy(10,180,"TO KNOW THE RULES PRESS 5");
//outtextxy(10,230,"TO GO STRAIGHT TO THE GAME PRESS 6");
/*char choice;
choice=getchar();
if(choice=='6')
{
    return;
}
getch();*/
//closegraph();
return;
}
void menu()
{
  start:
  setcolor(YELLOW);
setfillstyle(SOLID_FILL,YELLOW);
settextstyle(3,HORIZ_DIR,3);
rectangle(150,150,350,180);
outtextxy(210,150+2,"High score");
rectangle(150,230,350,260);
outtextxy(210,230+2,"Instruction");
rectangle(150,310,350,340);
outtextxy(230,310+2,"Exit");
rectangle(150,70,350,100);
outtextxy(210,70+2,"New Game");



char c;


int k=0;
int s=0;
int j=0,l=0;
int y1=140,y2=190;
   setcolor(GREEN);
   setfillstyle(SOLID_FILL,GREEN);
//rectangle(140,140,360,190);
//rectangle(140,y1-80,360,y2-80);
//rectangle(138,y1-78,362,y2-78);
//rectangle(136,y1-76,364,y2-76);

while(1)
{

getch();

if(GetAsyncKeyState(VK_UP))
{

if(y1!=60)

{setcolor(GREEN);
setfillstyle(SOLID_FILL,GREEN);
rectangle(140,y1-80,360,y2-80);
rectangle(138,y1-78,362,y2-78);
rectangle(136,y1-76,364,y2-76);
setcolor(BLACK);
setfillstyle(SOLID_FILL,BLACK);
rectangle(140,y1,360,y2);
rectangle(138,y1+2,362,y2+2);
rectangle(136,y1+4,364,y2+4);

s=0;
k++;

y1=y1-80;
y2=y2-80;

/*if(y1==140)
{
    l=0;
}
else if(y1==60)
{
    l=1;
}
else if(y1==220)
{
    l=2;
}
else if(y1==300)
{
    l=3;
}*/
getch();

}



}


else if(GetAsyncKeyState(VK_DOWN))
{

 if(y1!=300)
 {setcolor(GREEN);
setfillstyle(SOLID_FILL,GREEN);

rectangle(140,y1+80,360,y2+80);
rectangle(138,y1+82,362,y2+82);
rectangle(136,y1+84,364,y2+84);
setcolor(BLACK);
setfillstyle(SOLID_FILL,BLACK);
rectangle(140,y1,360,y2);
rectangle(138,y1+2,362,y2+2);
rectangle(136,y1+4,364,y2+4);
y1=y1+80;
y2=y2+80;
/*if(y1==140)
{
    l=0;
}
else if(y1==60)
{
    l=1;
}
else if(y1==220)
{
    l=2;
}
else if(y1==300)
{
    l=3;
}*/
k=0;
s++;
getch();
}

}
else if(GetAsyncKeyState(VK_RETURN))
{
    if(y1==140) //high score//
    {
     highscoredisplay();
     cleardevice();
     goto start;
     //return;
    }

    else if(y1==220)   //220-instruction//
    {

        cleardevice();
        setcolor(WHITE);
        setfillstyle(SOLID_FILL,WHITE);
        outtextxy(200,3,"Rules of the game:");
        outtextxy(10,50+10,"1.Eat the fruits");
        outtextxy(10,100+10,"2.Avoid The Ghosts");
        outtextxy(10,150+10,"3.Set the high Score");
        outtextxy(10,200+10,"4.Use the Arrow keys to move");
        outtextxy(10,250+10,"5.Press esc anytime to quit the game");
        getch();
        cleardevice();

goto start;

    }
    else if(y1==300) //exit//
    {
        exit(1);
    }
    else if(y1==60) //new game//
    {
        return;

    }

getch();
}
if(l++)
{
    j++;
}



}}
void ghost_direction()
{
    srand(time(0));
    int x1,y1,x2,y2,x3,y3;
    if(ghost1.pulse>=2||(ghost1.vx==0&&ghost1.vy==0))
    {
        start1:
        ghost1.dir=rand()%4;
        if(ghost1.dir==0)
        {
            ghost1.vy=-1;
            ghost1.vx=0;
            x1=ghost1.position.x+ghost1.vx;
            y1=ghost1.position.y+ghost1.vy;
            if(map[y1][x1]=='#')
            {
                goto start1;
            }
            //ERROR
        }
        else if(ghost1.dir==1)
        {
            ghost1.vy=1;
            ghost1.vx=0;
            x1=ghost1.position.x+ghost1.vx;
            y1=ghost1.position.y+ghost1.vy;
            if(map[y1][x1]=='#')
            {
                goto start1;
            }
            //ERROR
        }
        else if(ghost1.dir==2)
        {
            ghost1.vy=0;
            ghost1.vx=1;
            x1=ghost1.position.x+ghost1.vx;
            y1=ghost1.position.y+ghost1.vy;
            if(map[y1][x1]=='#')
            {
                goto start1;
            }
            //ERROR
        }
        else if(ghost1.dir==3)
        {
            ghost1.vy=0;
            ghost1.vx=-1;
            x1=ghost1.position.x+ghost1.vx;
            y1=ghost1.position.y+ghost1.vy;
            if(map[y1][x1]=='#')
            {
                goto start1;
            }
            //ERROR
        }
        ghost1.pulse=0;
    }

    //Ghost2 Direction

    if(ghost2.pulse>=2||(ghost2.vx==0&&ghost2.vy==0))
    {
        start2:
        ghost2.dir=rand()%4;
        if(ghost2.dir==0)
        {
            ghost2.vy=-1;
            ghost2.vx=0;
            x2=ghost2.position.x+ghost2.vx;
            y2=ghost2.position.y+ghost2.vy;
            if(map[y2][x2]=='#')
            {
                goto start2;
            }
            //ERROR
        }
        else if(ghost2.dir==1)
        {
            ghost2.vy=1;
            ghost2.vx=0;
            x2=ghost2.position.x+ghost2.vx;
            y2=ghost2.position.y+ghost2.vy;
            if(map[y2][x2]=='#')
            {
                goto start2;
            }
            //ERROR
        }
        else if(ghost2.dir==2)
        {
            ghost2.vy=0;
            ghost2.vx=1;
            x2=ghost2.position.x+ghost2.vx;
            y2=ghost2.position.y+ghost2.vy;
            if(map[y2][x2]=='#')
            {
                goto start2;
            }
            //ERROR
        }
        else if(ghost2.dir==3)
        {
            ghost2.vy=0;
            ghost2.vx=-1;
            x2=ghost2.position.x+ghost2.vx;
            y2=ghost2.position.y+ghost2.vy;
            if(map[y2][x2]=='#')
            {
                goto start2;
            }
            //ERROR
        }
        ghost2.pulse=0;
    }

    //Ghost3 Direction

    if(ghost3.pulse>=2||(ghost3.vx==0&&ghost3.vy==0))
    {
        start3:
        ghost3.dir=rand()%4;
        if(ghost3.dir==0)
        {
            ghost3.vy=-1;
            ghost3.vx=0;
            x3=ghost3.position.x+ghost3.vx;
            y3=ghost3.position.y+ghost3.vy;
            if(map[y3][x3]=='#')
            {
                goto start3;
            }
            //ERROR
        }
        else if(ghost3.dir==1)
        {
            ghost3.vy=1;
            ghost3.vx=0;
            x3=ghost3.position.x+ghost3.vx;
            y3=ghost3.position.y+ghost3.vy;
            if(map[y3][x3]=='#')
            {
                goto start3;
            }
            //ERROR
        }
        else if(ghost3.dir==2)
        {
            ghost3.vy=0;
            ghost3.vx=1;
            x3=ghost3.position.x+ghost3.vx;
            y3=ghost3.position.y+ghost3.vy;
            if(map[y3][x3]=='#')
            {
                goto start3;
            }
            //ERROR
        }
        else if(ghost3.dir==3)
        {
            ghost3.vy=0;
            ghost3.vx=-1;
            x3=ghost3.position.x+ghost3.vx;
            y3=ghost3.position.y+ghost3.vy;
            if(map[y3][x3]=='#')
            {
                goto start3;
            }
            //ERROR
        }
        ghost3.pulse=0;
    }
}
void ghost_movement()
{
    int x1,y1,x2,y2,x3,y3;
    if(ghost1.food)
    {
        map[ghost1.position.y][ghost1.position.x]='.';
    }
    else
    {
        map[ghost1.position.y][ghost1.position.x]=' ';
    }
    x1=ghost1.position.x+ghost1.vx;
    y1=ghost1.position.y+ghost1.vy;
    if(map[y1][x1]=='#')
    {
        ghost1.vx=0;
        ghost1.vy=0;
    }
    ghost1.position.x+=ghost1.vx;
    ghost1.position.y+=ghost1.vy;
    if(map[ghost1.position.y][ghost1.position.x]=='.')
    {
        ghost1.food=1;
    }
    else
    {
        ghost1.food=0;
    }
    map[ghost1.position.y][ghost1.position.x]='G';
    ghost1.pulse++;

    //ghost2 movement

    if(ghost2.food)
    {
        map[ghost2.position.y][ghost2.position.x]='.';
    }
    else
    {
        map[ghost2.position.y][ghost2.position.x]=' ';
    }
    x2=ghost2.position.x+ghost2.vx;
    y2=ghost2.position.y+ghost2.vy;
    if(map[y2][x2]=='#')
    {
        ghost2.vx=0;
        ghost2.vy=0;
    }
    ghost2.position.x+=ghost2.vx;
    ghost2.position.y+=ghost2.vy;
    if(map[ghost2.position.y][ghost2.position.x]=='.')
    {
        ghost2.food=1;
    }
    else
    {
        ghost2.food=0;
    }
    map[ghost2.position.y][ghost2.position.x]='P';
    ghost2.pulse++;

    //Ghost3 movement

    if(ghost3.food)
    {
        map[ghost3.position.y][ghost3.position.x]='.';
    }
    else
    {
        map[ghost3.position.y][ghost3.position.x]=' ';
    }
    x3=ghost3.position.x+ghost3.vx;
    y3=ghost3.position.y+ghost3.vy;
    if(map[y3][x3]=='#')
    {
        ghost3.vx=0;
        ghost3.vy=0;
    }
    ghost3.position.x+=ghost3.vx;
    ghost3.position.y+=ghost3.vy;
    if(map[ghost3.position.y][ghost3.position.x]=='.')
    {
        ghost3.food=1;
    }
    else
    {
        ghost3.food=0;
    }
    map[ghost3.position.y][ghost3.position.x]='X';
    ghost3.pulse++;
}
void game_over()
{
    setactivepage(1-page);
    setfillstyle(1, 0);
    bar(0,0,640, 480);
    if(f==0)
    {
        outtextxy(145,200,"CONGRATULATIONS");
        delay(2000);
        cleardevice();
        scoreadd();
        highscoredisplay();
        closegraph();
        exit(1);
    }
     if(player.score==69)
    {
        readimagefile("easteregg_2.jpg",0,0,639,479);
        delay(2000);
        cleardevice();
        scoreadd();
        highscoredisplay();
        closegraph();
        exit(1);
    }
    else if(player.score==28)
    {
        readimagefile("easteregg_1.jpg",0,0,639,479);
        delay(2000);
        cleardevice();
        scoreadd();
        highscoredisplay();
        closegraph();
        exit(1);
    }
    else if(player.score==6)
    {
        readimagefile("easteregg_3.jpg",0,0,639,479);
        delay(2000);
        cleardevice();
        scoreadd();
        highscoredisplay();
        closegraph();
        exit(1);
    }
    else if(player.score==0&&player.lives<=1)
    {
        readimagefile("easteregg_4.jpg",0,0,639,479);
        delay(2000);
        cleardevice();
        scoreadd();
        highscoredisplay();
        closegraph();
        exit(1);
    }
    outtextxy(200,200,"GAME OVER");
    delay(2000);
    cleardevice();
    scoreadd();
    highscoredisplay();
    closegraph();
    exit(1);
}
int scorereader()
{
    FILE *scoreboard=fopen("score1.txt","r");
    if(scoreboard==NULL)
    {
        printf("couldn't open the scoreboard");
        exit(1);
    }
    struct score ;
    int i=0;
    char str[10];
    while(!feof(scoreboard))
    {
        fgets(str,10,scoreboard);
        //puts(str);
        sscanf(str,"%d %s %d",&fp[i].post,fp[i].initials,&fp[i].scr);
        i++;
    }
    //printf("%d\n",fp[i-1].post);
    fclose(scoreboard);
    //return 0;
    return fp[i-1].post;
}
char in[3]={};
int initinp()
{
        setcolor(YELLOW);
        settextstyle(2,0,9);
        outtextxy(50,200,"Enter your initials(2 Characters):");
        setcolor(RED);
        setfillstyle(SOLID_FILL,RED);
        rectangle(120,350,450,400);
        int cc=0;
     while(1)
    {
        if(cc>1) break;
        getch();

        if(GetAsyncKeyState(65))
        {
            setcolor(GREEN);
            outtextxy(120+cc*50,355,"A");
            in[cc]='A';
            cc++;
        }
        if(GetAsyncKeyState(66))
        {
            setcolor(GREEN);
            outtextxy(120+cc*50,355,"B");
            in[cc]='B';
            cc++;
        }
        if(GetAsyncKeyState(67))
        {
            setcolor(GREEN);
            outtextxy(120+cc*50,355,"C");
            in[cc]='C';
            cc++;
        }
        if(GetAsyncKeyState(68))
        {
            setcolor(GREEN);
            outtextxy(120+cc*50,355,"D");
            in[cc]='D';
            cc++;
        }
        if(GetAsyncKeyState(69))
        {
            setcolor(GREEN);
            outtextxy(120+cc*50,355,"E");
            in[cc]='E';
            cc++;
        }
        if(GetAsyncKeyState(70))
        {
            setcolor(GREEN);
            outtextxy(120+cc*50,355,"F");
            in[cc]='F';
            cc++;
        }
        if(GetAsyncKeyState(71))
        {
            setcolor(GREEN);
            outtextxy(120+cc*50,355,"G");
            in[cc]='G';
            cc++;
        }
        if(GetAsyncKeyState(72))
        {
            setcolor(GREEN);
            outtextxy(120+cc*50,355,"H");
            in[cc]='H';
            cc++;
        }
        if(GetAsyncKeyState(73))
        {
            setcolor(GREEN);
            outtextxy(120+cc*50,355,"I");
            in[cc]='I';
            cc++;
        }
        if(GetAsyncKeyState(74))
        {
            setcolor(GREEN);
            outtextxy(120+cc*50,355,"J");
            in[cc]='J';
            cc++;
        }
        if(GetAsyncKeyState(75))
        {
            setcolor(GREEN);
            outtextxy(120+cc*50,355,"K");
            in[cc]='K';
            cc++;
        }
        if(GetAsyncKeyState(76))
        {
            setcolor(GREEN);
            outtextxy(120+cc*50,355,"L");
            in[cc]='L';
            cc++;
        }
        if(GetAsyncKeyState(77))
        {
            setcolor(GREEN);
            outtextxy(120+cc*50,355,"M");
            in[cc]='M';
            cc++;
        }
        if(GetAsyncKeyState(78))
        {
            setcolor(GREEN);
            outtextxy(120+cc*50,355,"N");
            in[cc]='N';
            cc++;
        }
        if(GetAsyncKeyState(79))
        {
            setcolor(GREEN);
            outtextxy(120+cc*50,355,"O");
            in[cc]='O';
            cc++;
        }
        if(GetAsyncKeyState(80))
        {
            setcolor(GREEN);
            outtextxy(120+cc*50,355,"P");
            in[cc]='P';
            cc++;
        }
        if(GetAsyncKeyState(81))
        {
            setcolor(GREEN);
            outtextxy(120+cc*50,355,"Q");
            in[cc]='Q';
            cc++;
        }
        if(GetAsyncKeyState(82))
        {
            setcolor(GREEN);
            outtextxy(120+cc*50,355,"R");
            in[cc]='R';
            cc++;
        }
        if(GetAsyncKeyState(83))
        {
            setcolor(GREEN);
            outtextxy(120+cc*50,355,"S");
            in[cc]='S';
            cc++;
        }
        if(GetAsyncKeyState(84))
        {
            setcolor(GREEN);
            outtextxy(120+cc*50,355,"T");
            in[cc]='T';
            cc++;
        }
        if(GetAsyncKeyState(85))
        {
            setcolor(GREEN);
            outtextxy(120+cc*50,355,"U");
            in[cc]='U';
            cc++;
        }
        if(GetAsyncKeyState(86))
        {
            setcolor(GREEN);
            outtextxy(120+cc*50,355,"V");
            in[cc]='V';
            cc++;
        }
        if(GetAsyncKeyState(87))
        {
            setcolor(GREEN);
            outtextxy(120+cc*50,355,"W");
            in[cc]='W';
            cc++;
        }
        if(GetAsyncKeyState(88))
        {
            setcolor(GREEN);
            outtextxy(120+cc*50,355,"X");
            in[cc]='X';
            cc++;
        }
        if(GetAsyncKeyState(89))
        {
            setcolor(GREEN);
            outtextxy(120+cc*50,355,"Y");
            in[cc]='Y';
            cc++;
        }
        if(GetAsyncKeyState(90))
        {
            setcolor(GREEN);
            outtextxy(120+cc*50,355,"Z");
            in[cc]='Z';
            cc++;
        }/*
        if(GetAsyncKeyState(65))
        {
            setcolor(GREEN);
            outtextxy(80+cc*50,355,"A");
            in[cc]='A';
            cc++;
        }*/


    }
    //strcpy(fp1.initials,in);

    getch();
    delay(1000);

    return 0;
}
void scoreadd()
{

    FILE *scoreboard=fopen("score1.txt","a");
    //char in[3];
    initinp();
    /*printf("Enter your initials: ");
    scanf("%s",in);*/
    struct score fp1;
    fp1.post = scorereader()+1;fp1.scr=player.score;
    //printf("%s",in);
    strcpy(fp1.initials,in);
    //scoreboard;

    if(scoreboard==NULL)
    {
        printf("couldn't open the scoreboard");
        exit(1);
    }
    //printf("file is open now\n");
    //int x=10;
    //printf("%d %s %d\n",fp.post,fp.initials,fp.scr);
    if(fp1.post==11&&fp1.scr>fp[9].scr||fp1.post<=10){
    fprintf(scoreboard,"%d %s %d\n",fp1.post,fp1.initials,fp1.scr);
    //printf("done printing\n");
    }
    fclose(scoreboard);

}
void highscoredisplay()
{
    struct score fp1;
    int x=scorereader();
    for(int i=0;i<x;i++)
    {
        for(int j=i+1;j<x;j++)
        {
            if(fp[i].scr<fp[j].scr)
            {
                fp1.scr=fp[i].scr;
                strcpy(fp1.initials,fp[i].initials);
                fp[i].scr=fp[j].scr;
                strcpy(fp[i].initials,fp[j].initials);
                fp[j].scr=fp1.scr;
                strcpy(fp[j].initials,fp1.initials);
            }
        }

    }
    FILE *scoreboard=fopen("score1.txt","w");
        for(int i=0;i<x*(x<=10)+10*(x>10);i++)
        {
            fprintf(scoreboard,"%d %s %d\n",fp[i].post,fp[i].initials,fp[i].scr);
        }
    fclose(scoreboard);

    /*printf("HIGH SCORE:\n");
    for(int i=0;i<x;i++)
        {
            printf("%d %s %d\n",fp[i].post,fp[i].initials,fp[i].scr);
        }*/
    char sh[10];
    cleardevice();
    setcolor(YELLOW);
    settextstyle(2,0,10);
    outtextxy(170,50,"Highscores");
    FILE *scoreboard1=fopen("score1.txt","r");
        for(int i=0;i<x*(x<=10)+10*(x>10);i++)
        {
            fgets(sh,10,scoreboard1);
            setcolor(WHITE);
            settextstyle(2,0,8);
            outtextxy(250,100+30*i,sh);
        }
    getch();
    fclose(scoreboard1);
    return;
}
