//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm2::FormCreate(TObject *Sender)
{
 HMENU MenuHandle = GetSystemMenu(Handle, false);
 if(MenuHandle)
  DeleteMenu(MenuHandle, SC_CLOSE, MF_BYCOMMAND);        
}
//---------------------------------------------------------------------------
 