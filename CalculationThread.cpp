//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "CalculationThread.h"
#include "Main.h"

#include "FormulaProcessing.h"
#include "HolographicLensInit.h"
#include "PictureComposition.h"
#include "fft_lib.h"
#include "Routines.h"
#include "Colors.h"
#include "ConvertToBmp.h"
#include "Unit2.h"

#include <math.h>

#define PI 3.1415926535897932384626433832

#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall Unit1::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall TCalculationThread::TCalculationThread(bool CreateSuspended)
        : TThread(CreateSuspended)
{
}
//---------------------------------------------------------------------------

void __fastcall TCalculationThread::Execute()
{
        //---- Place thread code here ----
 FreeOnTerminate = true;

                do {

  if (FileExists(Form1 -> Edit11 -> Text) == true)
  if ( Application->MessageBox("Bitmap already exists. Overwrite?", "File exists", MB_YESNO + MB_ICONQUESTION) != IDYES)
  {
   //FocusControl(Form1 -> Edit11);
   Form1 -> Button3 -> Enabled = true;
   break;
  }

 Form1 -> StatusBar1 -> Panels -> Items[0] -> Text = "Status: Starting calculations";
 Form1 -> StatusBar1 -> Panels -> Items[1] -> Text = "Elapsed time (sec): ??????";
 Form1 -> StatusBar1 -> Update();
 Form1 -> ProgressBar1 -> Position = 0;
 Form1 -> Button3 -> Enabled = false;

 //FILE *fHandleOut;
 double focus, aperture, big_aperture, big_aperture_at_focus, lambda, step, deltaXY, deltaXfYf, ScreenWidth, ScreenHeight;
 double Xo, slope; //Xo - точка на экране смещенная по Х на величину |Xo| от оси. slope - наклон сферической волны относительно плоской (связан с Xo через Sin или tg (?))
 double Ro; //Величина, на которую будут нормироваться координаты X и Y 

 ulong NumOfPoints;
 ulong NumOfPixelsAtScreenX, NumOfPixelsAtScreenY;
 int LensInRow, LensInCol;
 //lambda - длина волны, NumOfPoints - кол-во точек для ДПФ, step - шаг дискретизации
 //deltaXY - шаг дискретизации на входной апретуре, deltaXfYf - на экране камеры в фокусе, обычно это 9.3мкм (то есть размер пикселя камеры)
 //LensInRow, LensInCol - кол-во линз в ряду и столбце анализатора Гартмана

 int Size; //Длина строки в Едит-боксе

 //Input function to describe wavefront Z(X, Y)
 Size = Form1 -> Edit1->GetTextLen();     //Get length of string in Edit1
 Size++;                         //Add room for null character
 char *str = new char[Size];     //Creates str dynamic variable
 Form1 -> Edit1->GetTextBuf(str,Size);    //Puts Edit1->Text into str
 function f(str);
 delete str;

 //Input Amplitude-function A(X, Y)
 Size = Form1 -> Edit2->GetTextLen();     //Get length of string in Edit2
 Size++;                         //Add room for null character
 char *str2 = new char[Size];    //Creates str2 dynamic variable
 Form1 -> Edit2->GetTextBuf(str2,Size);   //Puts Edit2->Text into str2
 function A(str2);
 delete str2;

 if(Form1 -> RadioButton4 -> Checked == true)
 {
  //Input axial angle between Object & Ref wavefronts (in radians or degrees)
  if(Form1 -> RadioButton5 -> Checked == true)
  slope = StrToFloat(Form1 -> Edit3 -> Text); // if slope already in rad
  if(Form1 -> RadioButton6 -> Checked == true)
  slope = (2*PI/360)*StrToFloat(Form1 -> Edit3 -> Text); // convert degrees to rad
 }

 //Input the focal distance of lens (mm)
 focus = StrToFloat(Form1 -> Edit4 -> Text);

 //Если линза дифракционная то найдем то смещение от оси системы где надо наблюдать картинку
 if(Form1 -> RadioButton4 -> Checked == true)
  Xo = focus*tan(slope);

 //Input the lens' aperture size (mm)
 aperture = StrToFloat(Form1 -> Edit5 -> Text);

 //Input number of lens by X-axis
 LensInRow = StrToInt(Form1 -> Edit6 -> Text);

 //Input number of lens by Y-axis
 LensInCol = StrToInt(Form1 -> Edit7 -> Text);

 //Input deltaXfYf - discretization step in focal plane
 deltaXfYf = 0.001*StrToFloat(Form1 -> Edit8 -> Text);//И сразу конвертируем из мкм в мм

 //Input the wave-length (И сразу конвертируем из нм в мм)
 lambda = 0.000001*StrToFloat(Form1 -> Edit9 -> Text);

 //Input Number Of Points (by lens by axis)
 NumOfPoints = StrToInt(Form1 -> Edit10 -> Text);

 //Input Ro (automatic OR user-defined)
 if(Form1 -> RadioButton7 -> Checked == true)
  Ro = (aperture*LensInRow/2)<(aperture*LensInCol/2)?(aperture*LensInRow/2):(aperture*LensInCol/2);
 else
  Ro = StrToFloat(Form1 -> Edit12 -> Text);
 //---------- Get time before calculations -------------------------------
                        DWORD start=GetTickCount();
 //-----------------------------------------------------------------------

 deltaXY = (lambda*focus)/(NumOfPoints*deltaXfYf);
 step = deltaXY;
 big_aperture = (NumOfPoints-1)*step;
 big_aperture_at_focus = (NumOfPoints-1)*deltaXfYf;
 ScreenWidth = aperture*LensInRow;
 ScreenHeight = aperture*LensInCol;

 if(Form1 -> CheckBox2 -> Checked == false) //Если картинку не надо обрезать "под сенсор"
 {
  NumOfPixelsAtScreenX = (ulong)(NumOfPoints + (LensInRow - 1)*aperture/deltaXfYf);
  NumOfPixelsAtScreenY = (ulong)(NumOfPoints + (LensInCol - 1)*aperture/deltaXfYf);
 }

 if(Form1 -> CheckBox2 -> Checked == true) //Если нужно обрезать картинку "под сенсор"
 {
  NumOfPixelsAtScreenX = (ulong)(ScreenWidth/deltaXfYf);
  NumOfPixelsAtScreenY = (ulong)(ScreenHeight/deltaXfYf);
 }
 //-----------------------------------------------------------------------

 double *Xc = new double[LensInRow];//
 double *Yc = new double[LensInCol];//Для хранения координат центров линз

 double *Xap = new double[NumOfPoints];//Значение координаты х вдоль большой апертуры для линзы
 double *Yap = new double[NumOfPoints];//Значение координаты у вдоль большой апертуры для линзы

 double *Xf = new double[NumOfPoints];//Значение Х на большой апертуре в фокусе
 double *Yf = new double[NumOfPoints];//Значение У на большой апертуре в фокусе

 double *Fi = new double[NumOfPoints*NumOfPoints];//Значение фазы (это величина действительная)
 double *Amplitude = new double[NumOfPoints*NumOfPoints];//А это амплитуда падающей волны (обычно она = конст=1, и тоже действительна)

 double *t = new double[NumOfPoints*NumOfPoints]; //Коефициент пропускания
                                                  //(точнее интерференционная картина обьектной
                                                  //и опорной волны использованных для записи
                                                  //diffraction-линзы)

 //-----------------------------------------------------------------------

 if(Form1 -> RadioButton4 -> Checked == true)
 {
  HolographicLensInitialization(big_aperture, step, NumOfPoints, lambda, focus, Xo, t);
 }

 //-----------------------------------------------------------------------

 Complex *Zf = new Complex[NumOfPoints*NumOfPoints];//Комплексная амплитуда в фокальной плоскости
 Complex *Cf = new Complex[NumOfPoints*NumOfPoints];//А вот это будет настоящая комплексная амплитуда, с учетом фазового
                                                    //множителя. см Гудмен Фурье оптика, стр 119
 double **ScreenIntensity;
 ScreenIntensity = new double*[NumOfPixelsAtScreenX];
 for(ulong i=0; i < NumOfPixelsAtScreenX; i++)
 ScreenIntensity[i] = new double[NumOfPixelsAtScreenY];

 for(ulong i=0; i < NumOfPixelsAtScreenX; i++)
 for(ulong j=0; j < NumOfPixelsAtScreenY; j++)
 {
  ScreenIntensity[i][j] = 0.0;
 }

 //----- Добавим массивы для хранения амплитуды на экране - действительной и мнимой части ------
 //Этот кусочек добавлен 15 декабря 2006 для того чтобы правильно высчитывать интерференцию на экране,
 //то есть складывать сначала все действительные и мнимые амплитуды (в случае наложения хвостов от
 //соседних линз), и только потом возводя в квадрат действительные и мнимые части и складывая получать интенсивность.
 //До этого в каждой точке экрана вычислялась интенсивность I = A.r^2 + A.i^2 и в случае наложения изображений
 //суммировались интенсивности, что абсолютно не правильно.

 double **ScreenAmplitudeReal;
 ScreenAmplitudeReal = new double*[NumOfPixelsAtScreenX];
 for(ulong i=0; i < NumOfPixelsAtScreenX; i++)
 ScreenAmplitudeReal[i] = new double[NumOfPixelsAtScreenY];

 for(ulong i=0; i < NumOfPixelsAtScreenX; i++)
 for(ulong j=0; j < NumOfPixelsAtScreenY; j++)
 {
  ScreenAmplitudeReal[i][j] = 0.0;
 }

 double **ScreenAmplitudeImag;
 ScreenAmplitudeImag = new double*[NumOfPixelsAtScreenX];
 for(ulong i=0; i < NumOfPixelsAtScreenX; i++)
 ScreenAmplitudeImag[i] = new double[NumOfPixelsAtScreenY];

 for(ulong i=0; i < NumOfPixelsAtScreenX; i++)
 for(ulong j=0; j < NumOfPixelsAtScreenY; j++)
 {
  ScreenAmplitudeImag[i][j] = 0.0;
 }
 //-------------

 Xc[0] = -(aperture*LensInRow/2) + aperture/2; //
 Yc[0] = -(aperture*LensInCol/2) + aperture/2; //

 for(int i=1; i < LensInRow; i++)              //
  Xc[i] = Xc[i-1] + aperture;

 for(int i=1; i < LensInCol; i++)              //Присваиваем центрам линз координаты.
  Yc[i] = Yc[i-1] + aperture;

 //-----------------------------------------------------------------------

 int ProgressBarStep = (int)(180/(LensInRow * LensInCol));

 if(Form1 -> RadioButton3 -> Checked == true) //for refraction lens
 {
   Form1 -> StatusBar1 -> Panels -> Items[0] -> Text = "Status: Processing refraction lenses";
   Form1 -> StatusBar1 -> Update();
   for(int r=0; r < LensInRow; r++) //По всем линзам в ряду
   for(int c=0; c < LensInCol; c++) //И по всем линзам в столбце сделаем двумерное Фурье (процедура LensHandler) для каждой линзы.
   {
        Xap[0] = -big_aperture/2 + Xc[r]; //
        Yap[0] = -big_aperture/2 + Yc[c]; //
        for(ulong i=1; i < NumOfPoints; i++)
        {
         Xap[i]=Xap[i-1]+step;
         Yap[i]=Yap[i-1]+step;
        }

        Xf[0] = -big_aperture_at_focus/2; // + Xc[r]; эти значения Xf, Yf будут подставляться в фазовый множитель перед
        Yf[0] = -big_aperture_at_focus/2; // + Yc[c]; интегралом фурье, поэтому они должны быть привязаны к локальной
                                          // системе координат линзы, то есть так чтобы в центре линзы Xf=0, Yf=0.
                                          // поэтому убрано добавление координат центров линз. Правлено 21 дек 2006.
        for(ulong i=1; i < NumOfPoints; i++)
        {
         Xf[i]=Xf[i-1]+deltaXfYf;
         Yf[i]=Yf[i-1]+deltaXfYf;
        }

        for(ulong i=0; i < NumOfPoints; i++)
        for(ulong j=0; j < NumOfPoints; j++)
        {
          if(Form1 -> RadioButton1 -> Checked == true)
           Fi[i*NumOfPoints + j]=(2*PI/lambda)*f.get(Xap[i]/Ro, Yap[j]/Ro);
          if(Form1 -> RadioButton2 -> Checked == true)
           Fi[i*NumOfPoints + j]=              f.get(Xap[i]/Ro, Yap[j]/Ro);

          Amplitude[i*NumOfPoints + j]=A.get(Xap[i], Yap[j]);
        }

        for(ulong i=0; i < NumOfPoints; i++)
        for(ulong j=0; j < NumOfPoints; j++)
        {
         if ((Xap[i] <= (aperture/2 + Xc[r])) && (Xap[i] >= (-aperture/2 + Xc[r])) && (Yap[j] <= (aperture/2 + Yc[c])) && (Yap[j] >= (-aperture/2 + Yc[c]) ))
         {
          Zf[i*NumOfPoints + j].r = Amplitude[i*NumOfPoints + j]*cos(Fi[i*NumOfPoints + j]); // <--------------------
          Zf[i*NumOfPoints + j].i = Amplitude[i*NumOfPoints + j]*sin(Fi[i*NumOfPoints + j]);
         } else
               {
                Zf[i*NumOfPoints + j].r = 0;
                Zf[i*NumOfPoints + j].i = 0;
               }
        }

        LensHandler(Zf, NumOfPoints);//Эта процедура делает преобразование Фурье над комплексной матрицей Zf[i,j]

        //тестовый кусочек для вывода средней линии вдоль оси Х в текстовый файл, чтобы потом построить "срез" картинки
        FILE *f_out;
        f_out = fopen("midline.txt", "at");
        for (unsigned long m = 0; m < NumOfPoints; m++)
        fprintf(f_out, "%d\t%f\n", m, sqrt(pow(Zf[m*NumOfPoints + NumOfPoints/2].r, 2) + pow(Zf[m*NumOfPoints + NumOfPoints/2].i, 2)));
        fprintf(f_out, "%s\n", "----------");
        fclose(f_out);
        //конец тестового кусочка

        //После того как сделано преобразование Фурье домножим результат на фазовый множитель, так как нас интересует
        //правильное распределение амплитуды. См Гудмен, Фурье оптика, стр 119. Кусочек добавлен 19 дек 2006
        for (ulong i=0; i < NumOfPoints; i++)
        for (ulong j=0; j < NumOfPoints; j++)
        {
         Cf[i*NumOfPoints + j].r = cos(PI/(lambda*focus)*(pow(Xf[i], 2)+pow(Yf[j], 2)))*Zf[i*NumOfPoints + j].r - sin(PI/(lambda*focus)*(pow(Xf[i], 2)+pow(Yf[j], 2)))*Zf[i*NumOfPoints + j].i;
         Cf[i*NumOfPoints + j].i = cos(PI/(lambda*focus)*(pow(Xf[i], 2)+pow(Yf[j], 2)))*Zf[i*NumOfPoints + j].i + sin(PI/(lambda*focus)*(pow(Xf[i], 2)+pow(Yf[j], 2)))*Zf[i*NumOfPoints + j].r;
        }

        for (ulong i=0; i < NumOfPoints; i++)
        for (ulong j=0; j < NumOfPoints; j++)
        {
         Zf[i*NumOfPoints + j] = Cf[i*NumOfPoints + j];
        }

        if (Form1 -> CheckBox2 -> Checked == false)
         CompositionPictureWithoutAnyAdjusting(NumOfPoints, r, c, aperture, deltaXfYf, Zf, /*ScreenIntensity*/ ScreenAmplitudeReal, ScreenAmplitudeImag);

        if (Form1 -> CheckBox2 -> Checked == true)
        {
         for(ulong i=0; i < NumOfPoints; i++)
         {
          Xf[i]+=Xc[r]; //Прежде чем компоновать картинку нужно фокальные координаты Xf, Yf сместить в соответствующие места
          Yf[i]+=Yc[c]; //согласно координатам центров соответствующих линз
         }
         CompositionPictureWithAdjustingToSHSensorSize(ScreenWidth, ScreenHeight, NumOfPoints, deltaXfYf, Xf, Yf, NumOfPixelsAtScreenX, NumOfPixelsAtScreenY, Zf, /*ScreenIntensity*/ ScreenAmplitudeReal, ScreenAmplitudeImag);
        }

        Form1 -> ProgressBar1 -> Position += ProgressBarStep;
        Form1 -> ProgressBar1 -> Update();

                if(Terminated) break;
   }
 }

 if(Form1 -> RadioButton4 -> Checked == true) //for difraction lens
 {
   Form1 -> StatusBar1 -> Panels -> Items[0] -> Text = "Status: Processing difraction lenses";
   Form1 -> StatusBar1 -> Update();
   for(int r=0; r < LensInRow; r++) //По всем линзам в ряду
   for(int c=0; c < LensInCol; c++) //И по всем линзам в столбце сделаем двумерное Фурье (процедура LensHandler) для каждой линзы.
   {
        cout << endl;
        cout << " Xc[" << r << "]=" << Xc[r] << endl;
        cout << " Yc[" << c << "]=" << Yc[c] << endl;

        Xap[0] = -big_aperture/2 + Xc[r]; //
        Yap[0] = -big_aperture/2 + Yc[c]; //
        for(ulong i=1; i < NumOfPoints; i++)
        {
         Xap[i]=Xap[i-1]+step;
         Yap[i]=Yap[i-1]+step;
        }

        Xf[0] = -big_aperture_at_focus/2 + Xc[r];
        Yf[0] = -big_aperture_at_focus/2 + Yc[c];
        for(ulong i=1; i < NumOfPoints; i++)
        {
         Xf[i]=Xf[i-1]+deltaXfYf;
         Yf[i]=Yf[i-1]+deltaXfYf;
        }

        for(ulong i=0; i < NumOfPoints; i++)
        for(ulong j=0; j < NumOfPoints; j++)
        {
          if(Form1 -> RadioButton1 -> Checked == true)
           Fi[i*NumOfPoints + j]=(2*PI/lambda)*f.get(Xap[i]/Ro, Yap[j]/Ro);
          if(Form1 -> RadioButton2 -> Checked == true)
           Fi[i*NumOfPoints + j]=              f.get(Xap[i]/Ro, Yap[j]/Ro);

          Amplitude[i*NumOfPoints + j]=A.get(Xap[i], Yap[j]);
        }

        for(ulong i=0; i < NumOfPoints; i++)
        for(ulong j=0; j < NumOfPoints; j++)
        {
         if ((Xap[i] <= (aperture/2 + Xc[r])) && (Xap[i] >= (-aperture/2 + Xc[r])) && (Yap[j] <= (aperture/2 + Yc[c])) && (Yap[j] >= (-aperture/2 + Yc[c]) ))
         {
          Zf[i*NumOfPoints + j].r = Amplitude[i*NumOfPoints + j]*t[i*NumOfPoints + j]*cos(Fi[i*NumOfPoints + j] - PI*( pow(Xap[i] - Xo - Xc[r], 2) + pow(Yap[j] - Yc[c], 2) )/(lambda*focus)); // <--------------------
          Zf[i*NumOfPoints + j].i = Amplitude[i*NumOfPoints + j]*t[i*NumOfPoints + j]*sin(Fi[i*NumOfPoints + j] - PI*( pow(Xap[i] - Xo - Xc[r], 2) + pow(Yap[j] - Yc[c], 2) )/(lambda*focus));
         } else
               {
                Zf[i*NumOfPoints + j].r = 0;
                Zf[i*NumOfPoints + j].i = 0;
               }
        }

        LensHandler(Zf, NumOfPoints);//Эта процедура делает преобразование Фурье над комплексной
        //матрицей Zf[i,j], А в действительности, так как мы передаем в процедуру LensHandler не просто
        //амплитуду, а амплитуду умноженную на некоторый коеф. пропускания t, который есть
        //интерференционной картиной (см. выше) то LensHandler делает преобразование Френеля,
        //таким образом моделируем дифракционную линзу с помощью преобр. Фурье.


        if (Form1 -> CheckBox2 -> Checked == false)
         CompositionPictureWithoutAnyAdjusting(NumOfPoints, r, c, aperture, deltaXfYf, Zf, /*ScreenIntensity*/ ScreenAmplitudeReal, ScreenAmplitudeImag);

        if (Form1 -> CheckBox2 -> Checked == true)
         CompositionPictureWithAdjustingToSHSensorSize(ScreenWidth, ScreenHeight, NumOfPoints, deltaXfYf, Xf, Yf, NumOfPixelsAtScreenX, NumOfPixelsAtScreenY, Zf, /*ScreenIntensity*/ ScreenAmplitudeReal, ScreenAmplitudeImag);

        Form1 -> ProgressBar1 -> Position += ProgressBarStep;
        Form1 -> ProgressBar1 -> Update();

                if(Terminated) break;
   }
 }

 //В результате алгоритмов описанных выше мы получаем либо действительную и мнимую амплитуду на экране для рефракционной линзы
 //либо то же самое для дифракционной. Но нам далее нужно оперировать с интенсивностью, поэтому возводя в квадрат
 //действительную и мнимую часть амплитуды сформируем массив интенсивности на экране (ScreenIntensity). Этот кусок добавлен
 //18 дек 2006:

 for(ulong i=0; i < NumOfPixelsAtScreenX; i++)
 for(ulong j=0; j < NumOfPixelsAtScreenY; j++)
 {
  ScreenIntensity[i][j]=pow(ScreenAmplitudeReal[i][j], 2) + pow(ScreenAmplitudeImag[i][j], 2);
 }

/*
 fHandleOut = fopen("RAW_DATA.DAT", "wt"); //Откроем файл на запись.
   for(ulong i=0; i < NumOfPixelsAtScreenX; i++)
   for(ulong j=0; j < NumOfPixelsAtScreenY; j++)
   {
    fprintf(fHandleOut, "%lu\t%lu\t%lf\n", i, j, ScreenIntensity[i][j]);
   }
 fclose(fHandleOut);
*/
 //-----------------------------------------------------------------------

 delete [] Xc;
 delete [] Yc;
 delete [] Fi;
 delete [] Amplitude;
 delete [] Yap;
 delete [] Xap;
 delete [] Zf;
 delete [] Yf;
 delete [] Xf;
 delete [] t;

 if(Terminated)
 {
  for(ulong i=0; i < NumOfPixelsAtScreenX; i++)
  delete []ScreenIntensity[i];
  delete []ScreenIntensity;

  for(ulong i=0; i < NumOfPixelsAtScreenX; i++)
  delete []ScreenAmplitudeReal[i];
  delete []ScreenAmplitudeReal;

  for(ulong i=0; i < NumOfPixelsAtScreenX; i++)
  delete []ScreenAmplitudeImag[i];
  delete []ScreenAmplitudeImag;

  Form2 -> Hide();
  Form1 -> StatusBar1 -> Panels -> Items[0] -> Text = "Process terminated";
  Application->MessageBox("Process has been terminated", "Terminated", MB_OK + MB_ICONSTOP );
  break;
 }

 Form1 -> ProgressBar1 -> Position += 10;
 Form1 -> StatusBar1 -> Panels -> Items[0] -> Text = "Status: Writing bitmap";
 Form1 -> StatusBar1 -> Update();

 int **NormedIntensity; //Нормировання интенсивность - значения от 0 до 255
 NormedIntensity = new int*[NumOfPixelsAtScreenX];
 for(ulong i=0; i < NumOfPixelsAtScreenX; i++)
 NormedIntensity[i] = new int[NumOfPixelsAtScreenY];

 for(ulong i=0; i < NumOfPixelsAtScreenX; i++)
 for(ulong j=0; j < NumOfPixelsAtScreenY; j++)
 {
  NormedIntensity[i][j] = 0.0;
 }

 double MaxIntensity; //MaxIntensity - нужно чтоб пронормировать интенсивность по градациям серого
 MaxIntensity = FindMaxIn2D_ARRAY(ScreenIntensity, NumOfPixelsAtScreenX, NumOfPixelsAtScreenY);

 long double GradientStep; //шаг постоянного цвета
 GradientStep = MaxIntensity/255;

 long double ColorScale[256];

 //Зададим шкалу, по которой будем далее определять индекс цвета, зная интенсивность
 for(int i=0; i < 256; i++)
 ColorScale[i] = MaxIntensity;
 for(int i=0; i < 256; i++)
 {
  ColorScale[i] = (ColorScale[i]-((255-i)*GradientStep));
 }

 for(ulong i=0; i < NumOfPixelsAtScreenX; i++)
 for(ulong j=0; j < NumOfPixelsAtScreenY; j++)
 {
  for(int k=0; k < 255; k++)
  {
   if((ScreenIntensity[i][j] >= ColorScale[k]) && (ScreenIntensity[i][j] <= ColorScale[k+1]))
   {
    NormedIntensity[i][j] = k+1;
   }
  }
 }

 //-------------------------- End of calculating time -------------------------------------
                        float time = ((GetTickCount()-start)/1000.0);
                        Form1 -> StatusBar1 -> Panels -> Items[1] -> Text = FloatToStr(time);
 //----------------------------------------------------------------------------------------

 Form1 -> ProgressBar1 -> Position = 190;
 Form1 -> ProgressBar1 -> Update();

 //----------------запись в бмп файл-------------------------
  AnsiString name = Form1 -> Edit11 -> Text;
  Convert2DIntensityArrayToBitmap24(name, NormedIntensity, NumOfPixelsAtScreenX, NumOfPixelsAtScreenY);
 //--------------------------------------------------------------------------

 Form1 -> ProgressBar1 -> Position = 200;
 Form1 -> StatusBar1 -> Panels -> Items[0] -> Text = "Status: Complete";
 Form1 -> StatusBar1 -> Update();

 for(ulong i=0; i < NumOfPixelsAtScreenX; i++)
 delete []ScreenIntensity[i];
 delete []ScreenIntensity;

 for(ulong i=0; i < NumOfPixelsAtScreenX; i++)
 delete []ScreenAmplitudeReal[i];
 delete []ScreenAmplitudeReal;

 for(ulong i=0; i < NumOfPixelsAtScreenX; i++)
 delete []ScreenAmplitudeImag[i];
 delete []ScreenAmplitudeImag;

 for(ulong i=0; i < NumOfPixelsAtScreenX; i++)
 delete []NormedIntensity[i];
 delete []NormedIntensity;

 char notification[] = "File sucsessfully written: ";
 strcat(notification, name.c_str());
 Application->MessageBox(notification, "Notification", MB_OK + MB_ICONINFORMATION );
 Form1 -> Button3 -> Enabled = true;

                }while (0);
                 Form1 -> Button4 -> Enabled = false;
                 Form1 -> Button6 -> Enabled = false;
                 Form1 -> Button3 -> Enabled = true;
                 Form1 -> Button5 -> Enabled = true;
                 Form2 -> Hide();
}
//---------------------------------------------------------------------------
