#include <iostream>
#include<time.h>
#include<windows.h>
#include<fstream>
#include<ctime>
using namespace std;
int rand_num();
int high_score();
void map_maker();
void display_refresh();
void playerMove();
void game_logic();
char x[89]={' '};
int playerPos,score=0,highscorea=0,speed=500,a=1,b=0,turn=0;
unsigned last,elapsed;
bool mapCondition=false,endGame=false,allow=true;
//========================================
int main()
{
    //initializing ramdomness
    last=clock();

    srand(time(NULL));
    //starting map..................

    for(int i=1;i<=(1+85);i+=5){
        x[i]=-37;
        playerPos=i;
    }
    //..............................
    while(!endGame){
        elapsed=clock()-last;
        display_refresh();
        if(elapsed>=speed){
            allow=true;
            last=clock();
        }else{
            allow=false;
        }
        if(score>800){
            speed=30;
        }else if(score>400){
            speed=50;
        }else if(score>225){
            speed=75;
        }else if(score>200){
            speed=100;
        }else if(score>175){
            speed=125;
        }else if(score>150){
            speed=150;
        }else if(score>125){
            speed=175;
        }else if(score>100){
            speed=200;
        }else if(score>75){
            speed=225;
        }else if(score>50){
            speed=250;
        }else if(score>25){
            speed=300;
        }

        //Sleep(speed);
        playerMove();
        game_logic();
    }
    display_refresh();
    cout<<endl<<"YOU LOSE"<<endl;
    system("pause");
    return 0;
}
//===========================================
int rand_num(){
    return rand()%5;
}
void map_maker(){
    while(a==b){
        b=rand_num();
    }
    //continuous map........
    for(int i=89;i>=5;i--){
        x[i]=x[i-5];
    }
    //......................
    for(int i=0;i<5;i++){
        x[i]=' ';
    }
    if(!mapCondition){
        if(a>b){
            for(int i=b;i<=a;i++){
                x[i]=-37;
            }
        }else{
            for(int i=a;i<=b;i++){
                x[i]=-37;
            }
        }
        mapCondition=true;
        a=b;
    }else if(mapCondition){
        x[a]=-37;
        mapCondition=false;
    }
}
void display_refresh(){
    if(allow){
        map_maker();
    }
    system("cls");
    for(int j=0;j<=89;j++){
        if(j%5==0){
            cout<<endl;
        }
        if(j==playerPos){
            if(endGame){
                cout<<(char)176;
            }else{
                cout<<'^';
            }
        }else{
            cout<<x[j];
        }
    }
    cout<<endl<<"SCORE: "<<score;
    cout<<endl<<"HIGHSCORE: "<<high_score();
    cout<<endl<<"Elapse: "<<elapsed<<" "<<"SPEED: "<<speed;
}

void playerMove(){
    if(GetAsyncKeyState(VK_LEFT)&&playerPos%5!=0&&x[playerPos-1]!=' '){
        playerPos--;
    }
    if(GetAsyncKeyState(VK_RIGHT)&&playerPos!=4&&playerPos!=9
       &&playerPos!=14&&playerPos!=19&&playerPos!=24&&playerPos!=29
       &&playerPos!=34&&playerPos!=39&&playerPos!=44&&playerPos!=49
       &&playerPos!=54&&playerPos!=59&&playerPos!=64&&playerPos!=69
       &&playerPos!=74&&playerPos!=79&&playerPos!=84&&playerPos!=89
       &&x[playerPos+1]!=' '
       ){
           playerPos++;
    }
}
void game_logic(){
    if(x[playerPos]==-37&&x[(playerPos-5)]==-37){
        playerPos-=5;
     }
    if(x[playerPos]==-37&&x[(playerPos-5)]==' '||playerPos<5){
        if(allow){
            playerPos+=5;
        }
    }

    if(x[playerPos+5]!=' '&&x[playerPos-5]!=' '){
        score++;
    }
    if(playerPos>89){
        playerPos-=5;
        endGame=true;
    }
}
int high_score(){
    //new highscore
    if (score>highscorea){
        ofstream file("highscore.txt");
        file<<score;
        file.close();
    }
    //read highscore
    ifstream file("highscore.txt");
    file>>highscorea;
    file.close();

    return highscorea;
}

