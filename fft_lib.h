#ifndef _FFT_LIB_H_
#define _FFT_LIB_H_

#include <math.h>
#include "general.h"
#include "Complex.h"

//-------------------------------------------------------------------------------

#define TRIG_VARS                 	\
	ulong TLen,TNdx;int TDir;	\
	Complex PRoot,Root;

#define INIT_TRIG(LENGTH,DIR)    		\
	TNdx=0;TLen=(LENGTH);TDir=(DIR);    	\
	PRoot.r=1.0;PRoot.i=0.0;          	\
	Root.r=sin(CONST_PI/((LENGTH)*2.0)); 	\
	Root.r=-2.0*Root.r*Root.r;         	\
	Root.i=sin(CONST_PI/(LENGTH))*(DIR);

#define NEXT_TRIG_POW               			\
	if (((++TNdx)&15)==0) {            		\
		real Angle=(CONST_PI*(TNdx))/TLen;      \
		PRoot.r=sin(Angle*0.5);         	\
		PRoot.r=1.0-2.0*PRoot.r*PRoot.r;	\
		PRoot.i=sin(Angle)*(TDir);      	\
	} else {             				\
		Complex Temp;                     	\
		Temp=PRoot;                     	\
		PRoot = PRoot*Root;     		\
		PRoot = PRoot+Temp;     		\
	}

//-------------------------------------------------------------------------------

ulong rev_next(ulong r, ulong n) {
	do {
		n = n >> 1;
		r = r^n;
	} while ( (r&n) == 0);
	return r;
}

//-------------------------------------------------------------------------------

void FFTReOrder(Complex *Data, ulong Len) {
	Complex temp;
	if (Len <= 2) return;
	ulong r=0;
	for ( ulong x=1; x<Len; x++) {
		r = rev_next(r, Len);
		if (r>x) { temp=Data[x]; Data[x]=Data[r]; Data[r]=temp; }
	}
}

//-------------------------------------------------------------------------------

void IFFT_T(Complex *Data, ulong Len, int Dir) {
	ulong Step, HalfStep;
	ulong b;
	TRIG_VARS;

	Step = 1;
	while (Step < Len) {
		HalfStep = Step;
		Step *= 2;

		INIT_TRIG(HalfStep,Dir);

		for (b = 0; b < HalfStep; b++) {
			ulong L,R;
			for (L=b; L<Len; L+=Step) {
				Complex TRight,TLeft;
				R=L+HalfStep;
				TLeft=Data[L];TRight=Data[R];
				TRight  = TRight * PRoot;
				Data[L] = TLeft + TRight;
				Data[R] = TLeft - TRight;
			}
			NEXT_TRIG_POW;
		}

	}
}

//-------------------------------------------------------------------------------

void FFT_T(Complex *Data, ulong Len, int Dir) {
	ulong k;

	TRIG_VARS;

	if (Len <= (CACHE_HALF/sizeof(Complex)) ) {
		IFFT_T(Data, Len,Dir);
		return;
	}

	Len /= 2;

	INIT_TRIG(Len, Dir);

	FFT_T(Data,    Len,Dir);
	FFT_T(Data+Len,Len,Dir);

	for (k=0; k<Len; k++) {
		Complex b,c;
		b=Data[k];
		c = Data[k+Len] * PRoot;
		Data[k] = b + c;
		Data[k+Len] = b - c;
		NEXT_TRIG_POW;
	}
}

//-------------------------------------------------------------------------------

void Resort(Complex *Data, ulong Len)
{
  Complex *Sorted_Data = new Complex[Len];
  ulong i;
  for(i=Len/2; i < Len; i++)
  {
   Sorted_Data[i-Len/2] = Data[i];
  }

  for(i=0; i < Len/2; i++)
  {
   Sorted_Data[i+Len/2] = Data[i];
  }

  for(i=0; i < Len; i++)
  {
   Data[i] = Sorted_Data[i];
  }

  delete [] Sorted_Data;
}

//-------------------------------------------------------------------------------
void LensHandler(Complex *Data, ulong Len)
{
 Complex *Temp_Data = new Complex[Len];
 for(ulong j=0; j < Len; j++)
 {
        for(ulong i=0; i < Len; i++)
        {
         Temp_Data[i] = Data[i*Len + j];
        }
        Resort(Temp_Data, Len);
        FFTReOrder(Temp_Data, Len);
        FFT_T(Temp_Data, Len, 1);
        Resort(Temp_Data, Len);

        for(ulong i=0; i < Len; i++)
        {
         Data[i*Len + j] = Temp_Data[i];
        }
 }

 for(ulong i=0; i < Len; i++)
 {
        for(ulong j=0; j < Len; j++)
        {
         Temp_Data[j] = Data[i*Len + j];
        }

        Resort(Temp_Data, Len);
        FFTReOrder(Temp_Data, Len);
        FFT_T(Temp_Data, Len, 1);
        Resort(Temp_Data, Len);

        for(ulong j=0; j < Len; j++)
        {
         Data[i*Len + j] = Temp_Data[j];
        }
 }

 delete [] Temp_Data;
}
//-------------------------------------------------------------------------------

#endif

