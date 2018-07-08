#ifndef _CONVERT_TO_BMP_H_
#define _CONVERT_TO_BMP_H_

void Convert2DIntensityArrayToBitmap24(AnsiString file_name, int **NormedIntensity, unsigned long pict_width, unsigned long pict_height)
{
     Graphics::TBitmap *bmp=new Graphics::TBitmap();
     bmp->PixelFormat=pf24bit;

     bmp->Width = pict_width+2;
     bmp->Height = pict_height+2;

     bmp->Canvas->Brush->Color=clBlack;                      //Заливка черным
     bmp->Canvas->FillRect(Rect(0,0,bmp->Width,bmp->Height));//

     for(unsigned long i=0; i < pict_width; i++)
     for(unsigned long j=0; j < pict_height; j++)
     {
      BYTE *scan=(BYTE*)bmp->ScanLine[j];
      *(scan+i*3)=_COLORS[NormedIntensity[i][j]];
      *(scan+i*3+1)=_COLORS[NormedIntensity[i][j]];
      *(scan+i*3+2)=_COLORS[NormedIntensity[i][j]];
     }

     bmp->SaveToFile(file_name);
     delete bmp;

}

#endif
 