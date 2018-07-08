#ifndef _HOLOGRAPHIC_LENS_INITIALIZATION_H_
#define _HOLOGRAPHIC_LENS_INITIALIZATION_H_

#include "general.h"

void HolographicLensInitialization(double big_aperture, double step, unsigned long NumOfPoints, double lambda, double focus, double Xo, double *t)
{
 double *Xap = new double[NumOfPoints];//�������� ���������� � ����� ������� �������� ��� �����
 double *Yap = new double[NumOfPoints];//�������� ���������� � ����� ������� �������� ��� �����

   //������� ��������������� �����, ��������� ������� ��������� ������������� ���������� ������������
   //��� ��������������� ����� ���������, ������ ������ �������� ������ ���� ���
   //� ��� ����� � ������� � ����� (0,0)

   Xap[0] = -big_aperture/2; //
   Yap[0] = -big_aperture/2; //
   for(ulong i=1; i < NumOfPoints; i++)
   {
    Xap[i]=Xap[i-1]+step;
    Yap[i]=Yap[i-1]+step;
   }

   for(unsigned long i=0; i < NumOfPoints; i++)
   for(unsigned long j=0; j < NumOfPoints; j++)
   {
    t[i*NumOfPoints + j] = 1 + cos(    (PI/(lambda*focus))*( pow(Xap[i] - Xo, 2) + pow(Yap[j], 2) )   );
   }

 delete [] Yap;
 delete [] Xap;
}

#endif
 