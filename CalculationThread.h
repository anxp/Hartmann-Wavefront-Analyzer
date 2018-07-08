//---------------------------------------------------------------------------

#ifndef CalculationThreadH
#define CalculationThreadH
//---------------------------------------------------------------------------
#include <Classes.hpp>
//---------------------------------------------------------------------------
class TCalculationThread : public TThread
{
private:
protected:
        void __fastcall Execute();
public:
        __fastcall TCalculationThread(bool CreateSuspended);
};
//---------------------------------------------------------------------------
#endif
