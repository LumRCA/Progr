//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
int Game[3][3]; //Игровое поле
bool EndOfGame;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
        for(int j=0;j<3;j++)
                for(int i=0;i<3;i++)
                        Game[i][j]=0;


Krestik=new Graphics::TBitmap();
Krestik->LoadFromFile("Krestik.bmp");
Krestik->Transparent=true;
Nolik=new Graphics::TBitmap();
Nolik->LoadFromFile("Nolik.bmp");
Nolik->Transparent=true;
Canvas->Pen->Width=5;
ViktoryLine1=Point(-1,-1);
ViktoryLine2=Point(-1,-1);
EndOfGame=false;
}
//---------------------------------------------------------------------------


TForm1::DrawKresikAndNolik()
{

Canvas->MoveTo(100,10) ;
Canvas->LineTo(100,290);
Canvas->MoveTo(200,10) ;
Canvas->LineTo(200,290);

Canvas->MoveTo(10,100) ;
Canvas->LineTo(290,100);
Canvas->MoveTo(10,200) ;
Canvas->LineTo(290,200);

for(int j=0;j<3;j++)
        for(int i=0;i<3;i++)
        if(Game[i][j]==1)Canvas->Draw(i*100+10,j*100+10,Krestik);
        else
        if(Game[i][j]==2)Canvas->Draw(i*100+10,j*100+10,Nolik);

if(ViktoryLine1.x!=-1)
{
Canvas->Pen->Color=clRed;
Canvas->MoveTo(ViktoryLine1.x*100+50,ViktoryLine1.y*100+50);
Canvas->LineTo(ViktoryLine2.x*100+50,ViktoryLine2.y*100+50);
Canvas->Pen->Color=clBlack;
}
 return 0;
}


void __fastcall TForm1::FormPaint(TObject *Sender)
{
DrawKresikAndNolik();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormMouseDown(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
if(!EndOfGame)
{
int KletkaX=X/(100);
int KletkaY=Y/(100);
if((Game[KletkaX][KletkaY]!=2)&&(Game[KletkaX][KletkaY]!=1))
        {
        if(Button==mbLeft)Game[KletkaX][KletkaY]=1;
        if(Button==mbRight)Game[KletkaX][KletkaY]=2;
        int viktory=TestForVictory();
        Repaint();
        if(viktory==1){ShowMessage("Ваша победа");EndOfGame=true;}else
        if(viktory==3){ShowMessage("Ничья");EndOfGame=true;}else
        if(viktory==2){ShowMessage("Победа компьютера");EndOfGame=true;}else
        {
        Sleep(300);
        HodComputera();
        viktory=TestForVictory();
        Repaint();
        if(viktory==1){ShowMessage("Ваша победа");EndOfGame=true;}else
        if(viktory==3){ShowMessage("Ничья");EndOfGame=true;}else
        if(viktory==2){ShowMessage("Победа компьютера");EndOfGame=true;}
        }
        }
}
}
//---------------------------------------------------------------------------


TForm1::HodComputera()
{

 //Поиск ситуаций, когда один ход сразу же принесет победу (0 0)
 for(int i=0;i<3;i++)
 {
 if((Game[0][i]==2)&&(Game[1][i]==2)&&(Game[2][i]==0)){Game[2][i]=2;return 0;} //110
 else
 if((Game[1][i]==2)&&(Game[2][i]==2)&&(Game[0][i]==0)){Game[0][i]=2;return 0;} //011
 else
 if((Game[0][i]==2)&&(Game[2][i]==2)&&(Game[1][i]==0)){Game[1][i]=2;return 0;} //101
 else                                                                    //вертикаль
 if((Game[i][0]==2)&&(Game[i][1]==2)&&(Game[i][2]==0)){Game[i][2]=2;return 0;} //110
 else
 if((Game[i][1]==2)&&(Game[i][2]==2)&&(Game[i][0]==0)){Game[i][0]=2;return 0;} //011
 else
 if((Game[i][0]==2)&&(Game[i][2]==2)&&(Game[i][1]==0)){Game[i][1]=2;return 0;} //101
 }                                                                           //Диагональ слева направо
 if((Game[0][0]==2)&&(Game[1][1]==2)&&(Game[2][2]==0)){Game[2][2]=2;return 0;} //110
 else
 if((Game[1][1]==2)&&(Game[2][2]==2)&&(Game[0][0]==0)){Game[0][0]=2;return 0;} //011
 else
 if((Game[0][0]==2)&&(Game[2][2]==2)&&(Game[1][1]==0)){Game[1][1]=2;return 0;} //101
 else                                                                        //Диагональ справа на лево
 if((Game[2][0]==2)&&(Game[1][1]==2)&&(Game[0][2]==0)){Game[0][2]=2;return 0;} //110
 else
 if((Game[1][1]==2)&&(Game[0][2]==2)&&(Game[2][0]==0)){Game[2][0]=2;return 0;} //011
 else
 if((Game[2][0]==2)&&(Game[0][2]==2)&&(Game[1][1]==0)){Game[1][1]=2;return 0;} //101



//Поиск опасных ситуаций  типа XX
 for(int i=0;i<3;i++)
 {
 if((Game[0][i]==1)&&(Game[1][i]==1)&&(Game[2][i]==0)){Game[2][i]=2;return 0;} //110
 else
 if((Game[1][i]==1)&&(Game[2][i]==1)&&(Game[0][i]==0)){Game[0][i]=2;return 0;} //011
 else
 if((Game[0][i]==1)&&(Game[2][i]==1)&&(Game[1][i]==0)){Game[1][i]=2;return 0;} //101
 else                                                                    //вертикаль
 if((Game[i][0]==1)&&(Game[i][1]==1)&&(Game[i][2]==0)){Game[i][2]=2;return 0;} //110
 else
 if((Game[i][1]==1)&&(Game[i][2]==1)&&(Game[i][0]==0)){Game[i][0]=2;return 0;} //011
 else
 if((Game[i][0]==1)&&(Game[i][2]==1)&&(Game[i][1]==0)){Game[i][1]=2;return 0;} //101
 }                                                                           //Диагональ слева направо
 if((Game[0][0]==1)&&(Game[1][1]==1)&&(Game[2][2]==0)){Game[2][2]=2;return 0;} //110
 else
 if((Game[1][1]==1)&&(Game[2][2]==1)&&(Game[0][0]==0)){Game[0][0]=2;return 0;} //011
 else
 if((Game[0][0]==1)&&(Game[2][2]==1)&&(Game[1][1]==0)){Game[1][1]=2;return 0;} //101
 else                                                                        //Диагональ справа на лево
 if((Game[2][0]==1)&&(Game[1][1]==1)&&(Game[0][2]==0)){Game[0][2]=2;return 0;} //110
 else
 if((Game[1][1]==1)&&(Game[0][2]==1)&&(Game[2][0]==0)){Game[2][0]=2;return 0;} //011
 else
 if((Game[2][0]==1)&&(Game[0][2]==1)&&(Game[1][1]==0)){Game[1][1]=2;return 0;} //101

 if(Game[1][1]==0){Game[1][1]=2;return 0;}
for(int j=0;j<3;j++)
        for(int i=0;i<3;i++)
                if(Game[i][j]==0){Game[i][j]=2;return 0;}
return 0;
}

int TForm1::TestForVictory()
{
for(int i=0;i<3;i++)
{
if((Game[i][0]==1)&&(Game[i][1]==1)&&(Game[i][2]==1))
{ViktoryLine1=Point(i,0);ViktoryLine2=Point(i,2);return 1;}

if((Game[0][i]==1)&&(Game[1][i]==1)&&(Game[2][i]==1))
{ViktoryLine1=Point(0,i);ViktoryLine2=Point(2,i);return 1;}

if((Game[i][0]==2)&&(Game[i][1]==2)&&(Game[i][2]==2))
{ViktoryLine1=Point(i,0);ViktoryLine2=Point(i,2);return 2;}

if((Game[0][i]==2)&&(Game[1][i]==2)&&(Game[2][i]==2))
{ViktoryLine1=Point(0,i);ViktoryLine2=Point(2,i);return 2;}
}

if((Game[0][0]==1)&&(Game[1][1]==1)&&(Game[2][2]==1))
{ViktoryLine1=Point(0,0);ViktoryLine2=Point(2,2);return 1;}
if((Game[2][0]==1)&&(Game[1][1]==1)&&(Game[0][2]==1))
{ViktoryLine1=Point(2,0);ViktoryLine2=Point(0,2);return 1;}

if((Game[0][0]==2)&&(Game[1][1]==2)&&(Game[2][2]==2))
{ViktoryLine1=Point(0,0);ViktoryLine2=Point(2,2);return 2;}
if((Game[2][0]==2)&&(Game[1][1]==2)&&(Game[0][2]==2))
{ViktoryLine1=Point(2,0);ViktoryLine2=Point(0,2);return 2;}

if(!EndOfGame)
{bool err=false;
for(int j=0;j<3;j++)
        for(int i=0;i<3;i++)
                if(Game[i][j]==0)err=true;

if(err==false)return 3;
}
return 0;
}



void TForm1::NewGame()
{
for(int j=0;j<3;j++)
                for(int i=0;i<3;i++)
                        Game[i][j]=0;
ViktoryLine1=Point(-1,-1);
ViktoryLine2=Point(-1,-1);
EndOfGame=false;
}
void __fastcall TForm1::N1Click(TObject *Sender)
{
NewGame();
Repaint();        
}
//---------------------------------------------------------------------------

