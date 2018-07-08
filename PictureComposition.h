#ifndef _PICTURE_COMPOSITION_H_
#define _PICTURE_COMPOSITION_H_

#include "Complex.h"
void CompositionPictureWithAdjustingToSHSensorSize(double ScreenWidth, double ScreenHeight, unsigned long NumOfPoints, double deltaXfYf, double *Xf, double *Yf, unsigned long NumOfPixelsAtScreenX, unsigned long NumOfPixelsAtScreenY,  Complex *Zf, /*double **ScreenIntensity*/ double **ScreenAmplitudeReal, double **ScreenAmplitudeImag)
{
         unsigned long StartPixX, StartPixY, EndPixX, EndPixY, LeftUnusedPixX, DownUnusedPixY;
         //Находим область большой фокальной апертуры которую нужно записать в массив интенсивности на экране
         //Большая фок. апертура как правило значительно больше экрана и поэтому
         //лишние ее куски будут торчать за пределами экрана. Их нужно отсеять.
         //Результатом работы приведенного ниже алгоритма будут величины:
         //UsedPixX(Y) - количество подлежащих записи пикселов, остальные отсекаются как не влазящие
         //StartPixX(Y) - номер пикселя в массиве интенсивности ЭКРАНА, начиная с которого нужно
         //записать количество UsedPix пикселов
         //EndPixX(Y) - номер последнего подлежащего записи пикселя.

         //----------- Сначала для X --------------------------------
         if(Xf[0] < -ScreenWidth/2)
         {
          StartPixX = 0;
          LeftUnusedPixX = NumOfPoints/2 - (Xf[NumOfPoints/2] + ScreenWidth/2)/deltaXfYf;
         }
         else
             {
              StartPixX = (unsigned long)fabs((Xf[0]+ScreenWidth/2)/deltaXfYf);
              LeftUnusedPixX = 0;
             }

         if(Xf[NumOfPoints-1] > ScreenWidth/2)
         {
          EndPixX = NumOfPixelsAtScreenX;
         }
         else
             {
              EndPixX =(unsigned long)(NumOfPixelsAtScreenX/2 + Xf[NumOfPoints-1]/deltaXfYf);
             }

         //UsedPixX = EndPixX-StartPixX;

         //---------- А теперь для Y ------------------------------

         if(Yf[0] < -ScreenHeight/2)
         {
          StartPixY = 0;
          DownUnusedPixY = NumOfPoints/2 - (Yf[NumOfPoints/2] + ScreenHeight/2)/deltaXfYf;
         }
         else
             {
              StartPixY = (unsigned long)fabs((Yf[0]+ScreenHeight/2)/deltaXfYf);
              DownUnusedPixY = 0;
             }

         if(Yf[NumOfPoints-1] > ScreenHeight/2)
         {
          EndPixY = NumOfPixelsAtScreenY;
         }
         else
             {
              EndPixY =(unsigned long)(NumOfPixelsAtScreenY/2 + Yf[NumOfPoints-1]/deltaXfYf);
             }

         //UsedPixY = EndPixY - StartPixY;
         //--------------------------------------------------------

         for(unsigned long k=StartPixX; k != EndPixX; k++)
         for(unsigned long l=StartPixY; l != EndPixY; l++)
         {
          //ScreenIntensity[k][l]+=pow(Zf[(k-StartPixX+LeftUnusedPixX)*NumOfPoints + (l-StartPixY+DownUnusedPixY)].r, 2) + pow(Zf[(k-StartPixX+LeftUnusedPixX)*NumOfPoints + (l-StartPixY+DownUnusedPixY)].i, 2);
          ScreenAmplitudeReal[k][l]+=Zf[(k-StartPixX+LeftUnusedPixX)*NumOfPoints + (l-StartPixY+DownUnusedPixY)].r;
          ScreenAmplitudeImag[k][l]+=Zf[(k-StartPixX+LeftUnusedPixX)*NumOfPoints + (l-StartPixY+DownUnusedPixY)].i;
         }

}


void CompositionPictureWithoutAnyAdjusting(unsigned long NumOfPoints, int r, int c, double aperture, double deltaXfYf, Complex *Zf, /*double **ScreenIntensity*/ double **ScreenAmplitudeReal, double **ScreenAmplitudeImag)
{
        for(unsigned long k = 0; k < NumOfPoints; k++)
        for(unsigned long l = 0; l < NumOfPoints; l++)
        {
         //ScreenIntensity[k+(unsigned long)(r*aperture/deltaXfYf)][l+(unsigned long)(c*aperture/deltaXfYf)] += pow(Zf[k*NumOfPoints + l].r, 2) + pow(Zf[k*NumOfPoints + l].i, 2);
         ScreenAmplitudeReal[k+(unsigned long)(r*aperture/deltaXfYf)][l+(unsigned long)(c*aperture/deltaXfYf)]+=Zf[k*NumOfPoints + l].r;
         ScreenAmplitudeImag[k+(unsigned long)(r*aperture/deltaXfYf)][l+(unsigned long)(c*aperture/deltaXfYf)]+=Zf[k*NumOfPoints + l].i;
        }

}

#endif
