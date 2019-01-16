///Iqbal Mahmud
///HSTU

#include<bits/stdc++.h>
#include<unistd.h>
#include<windows.h>
#include<conio.h>///For getting a character from the console window
using namespace std;

//Variables declared for setting up the game.

bool GameOver;
const int hieght = 22;
const int width = 35;
int x,y,fruitX,fruitY, tot, coun, bonousX, bonousY;
enum eDirection {STOP = 0,LEFT,RIGHT,UP,DOWN};
eDirection dir;
int tailX[200],tailY[200];
int trail;


//Setup function to set up the game board
void Setup()
{
    GameOver=false;
    dir=STOP;
    x=rand()%width;
    y=rand()%hieght;
    fruitX=rand()%width;
    fruitY=rand()%hieght;
    bonousX=rand()%width;
    bonousY=rand()%hieght;
}

//Draw function draws the outline for the game
void Draw()
{
    system("cls");
    for(int i=0;i<width+2;i++)
        cout<<"#";
    cout<<endl;
    for(int i=0;i<hieght;i++)
    {
        for(int j=0;j<width;j++)
        {
            if(j==0)
                cout<<"#";
            if(i==y && j==x)
                cout<<"I";
            else if(i==fruitY && j==fruitX)
            {
                if(coun!=0&&coun%5==0)
                    cout<<"T";
                else
                    cout<<"O";
            }
            else
            {
                bool printed = false;
                for(int k=0;k<trail;k++)
                {
                    if(tailX[k]==j && tailY[k]==i)
                    {
                        cout<<"o";
                        printed=true;
                    }
                }
                if(!printed)
                    cout<<" ";
            }
            if(j==width-1)
                cout<<"#";
        }
        cout<<endl;
    }
    for(int i=0;i<width+2;i++)
        cout<<"#";
    cout<<endl;
    cout<<"Your Score: "<<tot<<endl;
    cout<<"Press \'e\' to Exit"<<endl;
}

//Input function works with the input/console input
void Input()
{
    if(_kbhit())
    {
        switch(_getch())
        {
        case 'w':
            dir=UP;
            break;
        case 's':
            dir=DOWN;
            break;
        case 'd':
            dir=RIGHT;
            break;
        case 'a':
            dir=LEFT;
            break;
        case 'e':
            GameOver=true;
            break;
        }
    }
}

//This is the logic section
void Logic()
{
    ///Logic for tail of the snake
    int prevX=tailX[0];
    int prevY=tailY[0];
    int nowX,nowY;
    tailX[0]=x;
    tailY[0]=y;
    for(int i=1;i<trail;i++)
    {
        nowX=tailX[i];
        nowY=tailY[i];
        tailX[i]=prevX;
        tailY[i]=prevY;
        prevX=nowX;
        prevY=nowY;
    }
    //Direction Logic
    switch(dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }
    //Game over and score logic
    if(x>width||x<0||y>hieght||y<0)
        GameOver=true;
    if(x==fruitX&&y==fruitY)
    {
        tot+=5;
        coun++;
        if(coun!=0&&coun%6==0)
        {
            usleep(1000);
            tot+=rand()%100;
        }
        fruitX=rand()%width;
        fruitY=rand()%hieght;
        trail++;
    }
}

///Driver Function
int main()
{
    Setup();
    while(!GameOver)
    {
        Draw();
        Input();
        Logic();
        usleep(500);
    }
    return 0;
}
