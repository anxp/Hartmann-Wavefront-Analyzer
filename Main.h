//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TGroupBox *GroupBox1;
        TGroupBox *GroupBox2;
        TGroupBox *GroupBox3;
        TGroupBox *GroupBox4;
        TLabel *Label1;
        TEdit *Edit1;
        TRadioButton *RadioButton1;
        TRadioButton *RadioButton2;
        TLabel *Label2;
        TEdit *Edit2;
        TGroupBox *GroupBox5;
        TRadioButton *RadioButton3;
        TRadioButton *RadioButton4;
        TGroupBox *GroupBox6;
        TLabel *Label3;
        TEdit *Edit3;
        TRadioButton *RadioButton5;
        TRadioButton *RadioButton6;
        TLabel *Label4;
        TEdit *Edit4;
        TLabel *Label5;
        TEdit *Edit5;
        TLabel *Label6;
        TEdit *Edit6;
        TLabel *Label7;
        TEdit *Edit7;
        TLabel *Label8;
        TEdit *Edit8;
        TLabel *Label9;
        TEdit *Edit9;
        TGroupBox *GroupBox7;
        TLabel *Label10;
        TEdit *Edit10;
        TButton *Button1;
        TButton *Button2;
        TGroupBox *GroupBox9;
        TButton *Button3;
        TProgressBar *ProgressBar1;
        TStatusBar *StatusBar1;
        TLabel *Label12;
        TLabel *Label13;
        TLabel *Label14;
        TLabel *Label15;
        TCheckBox *CheckBox2;
        TButton *Button4;
        TButton *Button5;
        TButton *Button6;
        TGroupBox *GroupBox8;
        TEdit *Edit11;
        TUpDown *UpDown1;
        TUpDown *UpDown2;
        TGroupBox *GroupBox10;
        TRadioButton *RadioButton7;
        TRadioButton *RadioButton8;
        TEdit *Edit12;
        TLabel *Label11;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall RadioButton3Click(TObject *Sender);
        void __fastcall RadioButton4Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Button5Click(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall Button6Click(TObject *Sender);
        void __fastcall RadioButton8Click(TObject *Sender);
        void __fastcall RadioButton7Click(TObject *Sender);
        void __fastcall RadioButton2Click(TObject *Sender);
        void __fastcall RadioButton1Click(TObject *Sender);

private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
