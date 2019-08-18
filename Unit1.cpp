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
int leftBuff = 0;
int rightBuff = 0;
int toEndRightBuff = 5;
int toEndBuff = 5;
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
   if(Key == 'W' && leftBuff >=3)
   {
      LeftBuffTimer->Enabled = true;
      toEndBuff = 5;
   }
  if(Key == VK_RIGHT && rightBuff >=3)
   {
      BuffRightTimer->Enabled = true;
      toEndRightBuff = 5;
   }
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
    // odbij od górnej krawêdzi
    if(Ball->Top - 5 <= Background->Top) y = -y;
    //odbij od dolnej krawêdzi
    if(Ball->Top + Ball->Height + 5 >= Background->Height) y=-y;
     // Buff
    if(LeftBuffTimer->Enabled == true)
    {
      //odbij od lewej krawedzi
      if(Ball->Left < Background->Left)
      {
         if(x<0) x=-x;
      }
    }
     if(BuffRightTimer->Enabled == true)
    {
      //odbij od prawej krawedzi
      if(Ball->Left + Ball->Width > Background->Left + Background->Width)
      {
         if(x>0) x=-x;
      }
    }
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
         Button1->Enabled = true;
         Button1->Visible = true;
         NewRoundButton->Enabled = true;
         NewRoundButton->Visible = true;
         Label2->Caption = "Liczba odbiæ = " + IntToStr(bounceCount);
         Label2->Visible = true;
         Label3->Caption = "Liczba punktów = " + IntToStr(leftPlayerPoints) + ":" + IntToStr(rightPlayerPoints);
         Label3->Visible = true;

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
         Button1->Enabled = true;
         Button1->Visible = true;
         NewRoundButton->Enabled = true;
         NewRoundButton->Visible = true;
         Label2->Caption = "Liczba odbiæ = " + IntToStr(bounceCount);
         Label2->Visible = true;
         Label3->Caption = "Liczba punktów = " + IntToStr(leftPlayerPoints) + ":" + IntToStr(rightPlayerPoints);
         Label3->Visible = true;

     }

     //srodek paletki lewej
        if(Ball->Top + Ball->Height/2 > PaddleLeft->Top + PaddleLeft->Height/2 - 20 &&
        Ball->Top + Ball->Height/2  < PaddleLeft->Top + PaddleLeft->Height/2 + 20 &&
        Ball->Left  < PaddleLeft->Left)
        {
                if(x<0) x = -1.5*x;
                bounceCount++;
                leftBuff++;
                BuffLeft->Caption = "Buff points: " + IntToStr(leftBuff);
        }
        // górna strona lewej
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
        //lewa górny kant
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
                rightBuff++;
                BuffRight->Caption = "Buff points: " + IntToStr(rightBuff);
        }
           // górna strona prawej
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
           //prawa górny kant
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
    Ball->Left = 550;
    Ball->Top = 250;
    orgx = 12;
    orgy = 12;
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
    Label3->Visible = false;
    Button1->Visible = false;
    Button1->Enabled = false;
    NewRoundButton->Enabled = false;
    NewRoundButton->Visible = false;
    leftPlayerPoints = 0;
    rightPlayerPoints = 0;
    bounceCount = 0;
    BuffLeft->Caption = "Buff points: 0";
    BuffRight->Caption = "Buff points: 0";
    leftBuff = 0;
    rightBuff = 0;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::IncreseSpeedTimer(TObject *Sender)
{
    orgx = orgx * 1.1;
    orgy = orgy * 1.1;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
      AnsiString FirstLine = "Witaj w grze Ping Pong!";
      AnsiString SecondLine = "Lewy gracz steruje paletk¹ za pomoc¹ klawiszy 'a' i 'z'.";
      AnsiString ThirdLine = "Prawy gracz steruje za pomoca klawiszy strza³ek góra i dó³.";
      AnsiString FourthLine = "Dla urozmaicenia gry: odbicie œrodkiem paletki spowoduje ¿e pi³ka przyœpieszy i zmieni k¹t.";
      AnsiString FifthLine = "Odbicie pi³ki kantem paletki znacznie zmieni k¹t odbicia.";
      AnsiString FifthALine = "Obcicie pi³ki trzykrotnie œrodkiem paletki umo¿liwia otrzymanie wzmocnienia - ";
      AnsiString FifthBbLine = "- przez 5 sekund pi³ka odbije siê od twojej krawêdzi zamiast policzyc punkt przeciwnikowi";
      AnsiString FifthCbLine = "Aktywacja wzmocnienia dla lewego gracza: 'W', dla prawego: strza³ka prawo";
      AnsiString SixthLine = "Pi³ka przyœpiesza z czasem.";
      AnsiString SeventhLine = "Mi³ej zabawy!";


	ShowMessage(FirstLine + sLineBreak + SecondLine + sLineBreak +
			ThirdLine + sLineBreak + FourthLine + sLineBreak +
                        FifthLine +sLineBreak + FifthALine + sLineBreak + FifthBbLine +
                        sLineBreak + FifthCbLine + sLineBreak +
                        SixthLine + sLineBreak + SeventhLine);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::NewRoundButtonClick(TObject *Sender)
{
    BallTimer->Enabled = true;
    IncreseSpeed->Enabled = true;
    PaddleLeft->Enabled = true;
    PaddleRight->Enabled = true;
    Ball->Left = 550;
    Ball->Top = 250;
    orgx = 12;
    orgy = 12;
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
    Label3->Visible = false;
    Button1->Visible = false;
    Button1->Enabled = false;
    NewRoundButton->Enabled = false;
    NewRoundButton->Visible = false;
    BuffLeft->Caption = "Buff points: 0";
    BuffRight->Caption = "Buff points: 0";
    leftBuff = 0;
    rightBuff = 0;
    bounceCount = 0;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::LeftBuffTimerTimer(TObject *Sender)
{
  toEndBuff--;
  BuffLeft->Caption = "Buff ON";
  if(toEndBuff <= 0)
  {
    LeftBuffTimer->Enabled = false;
    leftBuff = 0;
    BuffLeft->Caption = "Buff points: 0";
  }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::BuffRightTimerTimer(TObject *Sender)
{
    toEndRightBuff--;
  BuffRight->Caption = "Buff ON";
  if(toEndRightBuff <= 0)
  {
    BuffRightTimer->Enabled = false;
    rightBuff = 0;
    BuffRight->Caption = "Buff points: 0";
  }
}
//---------------------------------------------------------------------------

