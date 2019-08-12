//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
int x = 12;
int y = -12;
int orgx = 12;
int orgy = 12;
int bounceCount = 0;
int leftPlayerPoints = 0;
int rightPlayerPoints = 0;
char roundPoint;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
   if(Key == 'A') LeftUp->Enabled = true;
   if(Key == 'Z') LeftDown->Enabled = true;
   if(Key == VK_UP) RightUp->Enabled = true;
   if(Key == VK_DOWN) RightDown->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::LeftUpTimer(TObject *Sender)
{
    if(PaddleLeft->Top > 10) PaddleLeft->Top -= 20;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::LeftDownTimer(TObject *Sender)
{
   if((PaddleLeft->Top + PaddleLeft->Height) < Background->Height + 10) PaddleLeft->Top += 20;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
   if(Key == 'A') LeftUp->Enabled = false;
   if(Key == 'Z') LeftDown->Enabled = false;
   if(Key == VK_UP) RightUp->Enabled = false;
   if(Key == VK_DOWN) RightDown->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RightUpTimer(TObject *Sender)
{
    if(PaddleRight->Top > 10) PaddleRight->Top -= 20;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RightDownTimer(TObject *Sender)
{
   if((PaddleRight->Top + PaddleRight->Height) < Background->Height + 10) PaddleRight->Top += 20;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BallTimerTimer(TObject *Sender)
{
    Ball->Left += x;
    Ball->Top += y;
    // odbij od g�rnej kraw�dzi
    if(Ball->Top - 5 <= Background->Top) y = -y;
    //odbij od dolnej kraw�dzi
    if(Ball->Top + Ball->Height + 5 >= Background->Height) y=-y;
     // skucha
     if(Ball->Left >= PaddleRight->Left + PaddleRight->Width + 30)
     {
         BallTimer->Enabled = false;
         IncreseSpeed->Enabled = false;
         Ball->Visible = false;
         PaddleLeft->Enabled = false;
         PaddleRight->Enabled = false;
         leftPlayerPoints++;
         roundPoint = '<';
         Label1->Caption = "< Punkt dla gracza z lewej strony!";
         Label1->Visible = true;
         Button1->Visible = true;
         Label2->Caption = "Liczba odbi� = " + IntToStr(bounceCount);
         Label2->Visible = true;

     }
     if( Ball->Left + Ball->Width + 30 <= PaddleLeft->Left)
     {
         BallTimer->Enabled = false;
         IncreseSpeed->Enabled = false;
         Ball->Visible = false;
         PaddleLeft->Enabled = false;
         PaddleRight->Enabled = false;
         rightPlayerPoints++;
         roundPoint = '>';
         Label1->Caption = "Punkt dla gracza z prawej strony! >";
         Label1->Visible = true;
         Button1->Visible = true;
         Label2->Caption = "Liczba odbi� = " + IntToStr(bounceCount);
         Label2->Visible = true;

     }

     //srodek paletki lewej
        if(Ball->Top + Ball->Height/2 > PaddleLeft->Top + PaddleLeft->Height/2 - 20 &&
        Ball->Top + Ball->Height/2  < PaddleLeft->Top + PaddleLeft->Height/2 + 20 &&
        Ball->Left  < PaddleLeft->Left)
        {
                if(x<0) x = -1.5*x;
                bounceCount++;
        }
        // g�rna strona lewej
          else if (Ball->Top + Ball->Height/2 > PaddleLeft->Top + 20 &&
        Ball->Top + Ball->Height/2  < (PaddleLeft->Top + PaddleLeft->Height/2) - 20  &&
        Ball->Left < PaddleLeft->Left)
        {
                if(x<0) {
                                x = orgx;
                        }
                    if(y>0) y = orgy;
                 if(y<0) y = -orgy;
                 bounceCount++;

        }
        //dolna strona lewej
          else if (Ball->Top + Ball->Height/2 < PaddleLeft->Top + PaddleLeft->Height &&
        Ball->Top + Ball->Height/2  > (PaddleLeft->Top + PaddleLeft->Height/2) + 20  &&
        Ball->Left < PaddleLeft->Left)
        {
                if(x<0) {
                                x = orgx;
                        }
                    if(y>0) y = orgy;
                 if(y<0) y = -orgy;
                 bounceCount++;

        }
        //lewa g�rny kant
           else if (Ball->Top + Ball->Height/2 - 10 > PaddleLeft->Top &&
        Ball->Top + Ball->Height/2  < PaddleLeft->Top + 20  &&
        Ball->Left < PaddleLeft->Left)
        {
                if(x<0) {
                             x = orgx;
                        }
                         y = -orgy * 2.5;
                         bounceCount++;

        }
        //lewa dolny kant
           else if (Ball->Top + Ball->Height/2 + 10 < PaddleLeft->Top + PaddleLeft->Height &&
        Ball->Top + Ball->Height/2  > PaddleLeft->Top + PaddleLeft->Height - 20 &&
        Ball->Left < PaddleLeft->Left)
        {
                if(x<0) {
                             x = orgx;
                        }
                        y = orgy * 2.5;
                        bounceCount++;
        }
        //srodek paletki prawej
        if(Ball->Top + Ball->Height/2 > PaddleRight->Top + PaddleRight->Height/2 - 20 &&
        Ball->Top + Ball->Height/2  < PaddleRight->Top + PaddleRight->Height/2 + 20 &&
        Ball->Left + Ball->Width  > PaddleRight->Left + PaddleRight->Width)
        {
                if(x>0) x = -1.5*x;
                bounceCount++;
        }
           // g�rna strona prawej
          else if (Ball->Top + Ball->Height/2 > PaddleRight->Top + 20 &&
        Ball->Top + Ball->Height/2  < (PaddleRight->Top + PaddleRight->Height/2) - 20  &&
        Ball->Left + Ball->Width  > PaddleRight->Left + PaddleRight->Width)
        {
                if(x>0) {
                                x = -orgx;
                        }
                 if(y>0) y = orgy;
                 if(y<0) y = -orgy;
                 bounceCount++;

        }
          //dolna strona prawej
          else if (Ball->Top + Ball->Height/2 < PaddleRight->Top + PaddleRight->Height - 20 &&
        Ball->Top + Ball->Height/2  > (PaddleRight->Top + PaddleRight->Height/2) + 20  &&
        Ball->Left + Ball->Width  > PaddleRight->Left + PaddleRight->Width)
        {
                if(x>0) {
                                x = -orgx;
                        }
                    if(y>0) y = orgy;
                 if(y<0) y = -orgy;
                 bounceCount++;

        }
           //prawa g�rny kant
           else if (Ball->Top + Ball->Height/2 - 10 > PaddleRight->Top &&
        Ball->Top + Ball->Height/2  < PaddleRight->Top + 20  &&
        Ball->Left + Ball->Width  > PaddleRight->Left + PaddleRight->Width)
        {
                if(x>0) {
                             x = -orgx;
                        }
                         y = -orgy * 2.5;
                         bounceCount++;

        }
        //prawa dolny kant
           else if (Ball->Top + Ball->Height/2 + 10 < PaddleRight->Top + PaddleRight->Height &&
        Ball->Top + Ball->Height/2  > PaddleRight->Top + PaddleRight->Height - 20 &&
        Ball->Left + Ball->Width  > PaddleRight->Left + PaddleRight->Width)
        {
                if(x>0) {
                             x = -orgx;
                        }
                        y = orgy * 2.5;
                        bounceCount++;
        }

  }
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
    BallTimer->Enabled = true;
    IncreseSpeed->Enabled = true;
    PaddleLeft->Enabled = true;
    PaddleRight->Enabled = true;
    Ball->Left = 450;
    Ball->Top = 250;
    if(roundPoint == '<')
    {
        x = -orgx;
        y = orgy;
    }
     if(roundPoint == '>')
    {
        x = orgx;
        y = orgy;
    }
    Ball->Visible = true;
    Label1->Visible = false;
    Label2->Visible = false;
    Button1->Visible = false;
    leftPlayerPoints = 0;
    rightPlayerPoints = 0;
    bounceCount = 0;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::IncreseSpeedTimer(TObject *Sender)
{
    orgx = orgx * 1,1;
    orgy = orgy * 1,1;
}
//---------------------------------------------------------------------------

