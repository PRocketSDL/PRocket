#include <windows.h>




void ColorBox()
{
  CHOOSECOLOR cc;                 // common dialog box structure 
  static COLORREF acrCustClr[16]; // array of custom colors 
  HBRUSH hbrush;                  // brush handle
  static DWORD rgbCurrent;  
        // initial color selection
  // Initialize CHOOSECOLOR 
  ZeroMemory(&cc, sizeof(cc));
  cc.lStructSize = sizeof(cc);
  cc.hwndOwner = NULL;            //No need
  cc.lpCustColors = (LPDWORD) acrCustClr;
  cc.rgbResult = rgbCurrent;
  cc.Flags = CC_FULLOPEN | CC_RGBINIT | CC_SOLIDCOLOR | CC_ANYCOLOR;
 
    if (ChooseColor(&cc))
    {
      hbrush = CreateSolidBrush(cc.rgbResult);
      rgbCurrent = cc.rgbResult; 
    }
}