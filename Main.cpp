#include <vcl.h>
#pragma hdrstop

#include <iostream.h>
#include "Main.h"
#include "Unit2.h"
#include "CalculationThread.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
TCalculationThread* Thread;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
 if (StrToInt(Edit10 -> Text) <= 1024)
 Edit10 -> Text = IntToStr(StrToInt(Edit10 -> Text)*2);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
 if (StrToInt(Edit10 -> Text) >= 128)
 Edit10 -> Text = IntToStr(StrToInt(Edit10 -> Text)/2);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
 Label3 -> Enabled = false;
 Edit3 -> Enabled = false;
 RadioButton5 -> Enabled = false;
 RadioButton6 -> Enabled = false;
 Button6 -> Enabled = false;

 /*
 HMENU MenuHandle = GetSystemMenu(Handle, false);
 if(MenuHandle)
  DeleteMenu(MenuHandle, SC_CLOSE, MF_BYCOMMAND);
 */
 //-------- Reading ini-file ---------------------
 FILE *f;
 char temp_str[30];
 int temp_int;

 if((f = fopen("settings.ini", "rt"))==NULL) //Откроем ini-файл на чтение.
 {
  Application->MessageBox("Error opening file \"settings.ini\". Maybe file does not exists. \nProgram will be loaded with default settings.", "I/O Error", MB_OK + MB_ICONWARNING );
 } else
   {
    fscanf(f, "%s", &temp_str);
    fscanf(f, "%s", &temp_str);
        Edit1->Text = (AnsiString)temp_str;
    //--------------------------------------------
    fscanf(f, "%s", &temp_str);
    fscanf(f, "%d", &temp_int);
        if(temp_int == 1)
        {
         RadioButton1 -> Checked = true; RadioButton2 -> Checked = false;
          //RadioButton7 -> Enabled = false;
          //RadioButton8 -> Enabled = false;
          //Label11 -> Enabled = false;
          //Edit12 -> Enabled = false;
          //GroupBox10 -> Enabled = false;
        } else
              {
               RadioButton1 -> Checked = false; RadioButton2 -> Checked = true;
                //RadioButton7 -> Enabled = true;
                //RadioButton8 -> Enabled = true;
                //Label11 -> Enabled = true;
                //Edit12 -> Enabled = true;
                //GroupBox10 -> Enabled = true;
              }
    fscanf(f, "%d", &temp_int);
    //--------------------------------------------
    fscanf(f, "%s", &temp_str);
    fscanf(f, "%s", &temp_str);
        Edit2->Text = (AnsiString)temp_str;
    //--------------------------------------------
    fscanf(f, "%s", &temp_str);
    fscanf(f, "%d", &temp_int);
        if(temp_int == 1)
        {
         RadioButton3 -> Checked = true; RadioButton4 -> Checked = false;
        } else
              {
               RadioButton3 -> Checked = false; RadioButton4 -> Checked = true;
              }
    fscanf(f, "%d", &temp_int);
    //--------------------------------------------
    fscanf(f, "%s", &temp_str);
    fscanf(f, "%s", &temp_str);
        Edit3 -> Text = AnsiString(temp_str);
    //--------------------------------------------
    fscanf(f, "%s", &temp_str);
    fscanf(f, "%d", &temp_int);
        if(temp_int == 1)
        {
         RadioButton5 -> Checked = true; RadioButton6 -> Checked = false;
        } else
              {
               RadioButton5 -> Checked = false; RadioButton6 -> Checked = true;
              }
    fscanf(f, "%d", &temp_int);
    //--------------------------------------------
    fscanf(f, "%s", &temp_str);
    fscanf(f, "%s", &temp_str);
        Edit4 -> Text = (AnsiString)temp_str;
    //--------------------------------------------
    fscanf(f, "%s", &temp_str);
    fscanf(f, "%s", &temp_str);
        Edit5 -> Text = (AnsiString)temp_str;
    //--------------------------------------------
    fscanf(f, "%s", &temp_str);
    fscanf(f, "%s", &temp_str);
        Edit9 -> Text = (AnsiString)temp_str;
    //--------------------------------------------
    fscanf(f, "%s", &temp_str);
    fscanf(f, "%s", &temp_str);
        Edit6 -> Text = (AnsiString)temp_str;
        UpDown1 -> Position = StrToInt((AnsiString)temp_str);
    //--------------------------------------------
    fscanf(f, "%s", &temp_str);
    fscanf(f, "%s", &temp_str);
        Edit7 -> Text = (AnsiString)temp_str;
        UpDown2 -> Position = StrToInt((AnsiString)temp_str);
    //--------------------------------------------
    fscanf(f, "%s", &temp_str);
    fscanf(f, "%s", &temp_str);
        Edit8 -> Text = (AnsiString)temp_str;
    //--------------------------------------------
    fscanf(f, "%s", &temp_str);
    fscanf(f, "%s", &temp_str);
        Edit10 -> Text = (AnsiString)temp_str;
    //--------------------------------------------
    fscanf(f, "%s", &temp_str);
    fscanf(f, "%d", &temp_int);
        if(temp_int == 1)
        CheckBox2 -> Checked = true;
          else
          CheckBox2 -> Checked = false;
    //--------------------------------------------
    fscanf(f, "%s", &temp_str);
    fscanf(f, "%s", &temp_str);
        Edit11 -> Text = (AnsiString)temp_str;
    //--------------------------------------------
    fscanf(f, "%s", &temp_str);
    fscanf(f, "%d", &temp_int);
        if(temp_int == 1)
        {
         RadioButton7 -> Checked = true; RadioButton8 -> Checked = false; Edit12 -> Enabled = false;
        } else
              {
               RadioButton7 -> Checked = false; RadioButton8 -> Checked = true; Edit12 -> Enabled = true;
              }
    fscanf(f, "%d", &temp_int);
    fscanf(f, "%s", &temp_str);
        Edit12 -> Text = (AnsiString)temp_str;
   }


 fclose(f);
 //-----------------------------------------------
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton3Click(TObject *Sender)
{
 Label3 -> Enabled = false;
 Edit3 -> Enabled = false;
 RadioButton5 -> Enabled = false;
 RadioButton6 -> Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton4Click(TObject *Sender)
{
 Label3 -> Enabled = true;
 Edit3 -> Enabled = true;
 RadioButton5 -> Enabled = true;
 RadioButton6 -> Enabled = true;
}

//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
 Thread = new TCalculationThread(true);
 if(!Thread)
 {
  ShowMessage("Error! Cannot create thread.");
  Application -> Terminate();
 }
 Thread -> Priority = tpLower; // set the priority lower than normal

 Thread -> Resume();
 Button6 -> Tag = 0;
 Button6 -> Caption = "PAUSE";
 Button3 -> Enabled = false;
 Button4 -> Enabled = true;
 Button6 -> Enabled = true;
 Button5 -> Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
 Form2 -> Show();
 Thread -> Terminate();
 Button4 -> Enabled = false;
 Button6 -> Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button6Click(TObject *Sender)
{
 if(Button6 -> Tag == 0)
 {
  Thread -> Suspend();
  Button6 -> Caption = "CONTINUE";
  Button4 -> Enabled = false;
  Button6 -> Tag = 1;
 } else
        if(Button6 -> Tag == 1)
        {
         Thread -> Resume();
         Button6 -> Caption = "PAUSE";
         Button4 -> Enabled = true;
         Button6 -> Tag = 0;
        }
}

//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
 FILE *f;
 if((f = fopen("settings.ini", "wt"))==NULL) //Откроем ini-файл на запись.
 {
  Application->MessageBox("Error opening file \"settings.ini\". Maybe file is READ-ONLY. \nAll settings will have not saved.", "I/O Error", MB_OK + MB_ICONWARNING );
 } else
  {
   fprintf(f, "%s\n", "[WAVEFRONT]");
   fprintf(f, "%s\n", (Edit1->Text).c_str());
   //-------------------------------------------
   fprintf(f, "%s\n", "[MM_OR_RAD]");
   if(RadioButton1 -> Checked == true)
   {
    fprintf(f, "%d\n", 1);
    fprintf(f, "%d\n", 0);
   }else
        {
         fprintf(f, "%d\n", 0);
         fprintf(f, "%d\n", 1);
        }
   //-------------------------------------------
   fprintf(f, "%s\n", "[AMPLITUDE]");
   fprintf(f, "%s\n", (Edit2->Text).c_str());
   //-------------------------------------------
   fprintf(f, "%s\n", "[TYPE_OF_LENS]");
   if(RadioButton3 -> Checked == true)
   {
    fprintf(f, "%d\n", 1);
    fprintf(f, "%d\n", 0);
   }else
        {
         fprintf(f, "%d\n", 0);
         fprintf(f, "%d\n", 1);
        }
   //-------------------------------------------
   fprintf(f, "%s\n", "[ALPHA]");
   fprintf(f, "%s\n", (Edit3->Text).c_str());
   //-------------------------------------------
   fprintf(f, "%s\n", "[RAD_OR_DEG]");
   if(RadioButton5 -> Checked == true)
   {
    fprintf(f, "%d\n", 1);
    fprintf(f, "%d\n", 0);
   }else
        {
         fprintf(f, "%d\n", 0);
         fprintf(f, "%d\n", 1);
        }
   //-------------------------------------------
   fprintf(f, "%s\n", "[FOCUS]");
   fprintf(f, "%s\n", (Edit4->Text).c_str());
   //-------------------------------------------
   fprintf(f, "%s\n", "[LENS_APERTURE]");
   fprintf(f, "%s\n", (Edit5->Text).c_str());
   //-------------------------------------------
   fprintf(f, "%s\n", "[WAVELENGTH]");
   fprintf(f, "%s\n", (Edit9->Text).c_str());
   //-------------------------------------------
   fprintf(f, "%s\n", "[NUM_OF_LENS_BY_X]");
   fprintf(f, "%s\n", (Edit6->Text).c_str());
   //-------------------------------------------
   fprintf(f, "%s\n", "[NUM_OF_LENS_BY_Y]");
   fprintf(f, "%s\n", (Edit7->Text).c_str());
   //-------------------------------------------
   fprintf(f, "%s\n", "[SIZE_OF_PIXEL]");
   fprintf(f, "%s\n", (Edit8->Text).c_str());
   //-------------------------------------------
   fprintf(f, "%s\n", "[NUM_OF_POINTS]");
   fprintf(f, "%s\n", (Edit10->Text).c_str());
   //-------------------------------------------
   fprintf(f, "%s\n", "[IS_CHKBOX_CHECKD]");
   if(CheckBox2 -> Checked == true)
    fprintf(f, "%d\n", 1);
    else fprintf(f, "%d\n", 0);
   //-------------------------------------------
   fprintf(f, "%s\n", "[FILENAME]");
   fprintf(f, "%s\n", (Edit11->Text).c_str());
   //-------------------------------------------
   fprintf(f, "%s\n", "[Normalization]");
   if(RadioButton7 -> Checked == true)
   {
    fprintf(f, "%d\n", 1);
    fprintf(f, "%d\n", 0);
   }else
        {
         fprintf(f, "%d\n", 0);
         fprintf(f, "%d\n", 1);
        }
   fprintf(f, "%s\n", (Edit12->Text).c_str());
   //-------------------------------------------
  }
 fclose(f);

 Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton8Click(TObject *Sender)
{
 Edit12 -> Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton7Click(TObject *Sender)
{
 Edit12 -> Enabled = false; 
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton2Click(TObject *Sender)
{
 //RadioButton7 -> Enabled = true;
 //RadioButton8 -> Enabled = true;
 //Label11 -> Enabled = true;
 if(RadioButton8 -> Checked == true)
  Edit12 -> Enabled = true;
 else Edit12 -> Enabled = false;
 //GroupBox10 -> Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton1Click(TObject *Sender)
{
 //RadioButton7 -> Enabled = false;
 //RadioButton8 -> Enabled = false;
 //Label11 -> Enabled = false;
 //Edit12 -> Enabled = false;
 //GroupBox10 -> Enabled = false;
}
//---------------------------------------------------------------------------

