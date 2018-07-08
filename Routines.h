#ifndef _ROUTINES_H_
#define _ROUTINES_H_

#include "general.h"

double FindMax(double *Data, ulong Len)
{
 double MaxData;
 MaxData=Data[0];

 for(ulong i=1; i < Len; i++)
 {
  if(Data[i] > MaxData)
  MaxData = Data[i];
 }

 return(MaxData);
}

//-------------------------------

int FindMax(int *Data, ulong Len)
{
 int MaxData;
 MaxData=Data[0];

 for(ulong i=1; i < Len; i++)
 {
  if(Data[i] > MaxData)
  MaxData = Data[i];
 }

 return(MaxData);
}

//-------------------------------

double FindMaxIn2D_ARRAY(double **Data, ulong NumOfPointsByX, ulong NumOfPointsByY)
{
 double MaxData;
 MaxData = Data[0][0];

 for(ulong i=1; i < NumOfPointsByX; i++)
 for(ulong j=1; j < NumOfPointsByY; j++)
 {
  if(Data[i][j] > MaxData)
  MaxData = Data[i][j];
 }

 return(MaxData);
}
#endif
