// ComboDialog.cpp

#include "StdAfx.h"
#include "ComboDialog.h"

#include "Windows/Control/Static.h"

#ifdef LANG
#include "LangUtils.h"
#endif

using namespace NWindows;

#ifdef LANG
static CIDLangPair kIDLangPairs[] =
{
  { IDOK, 0x02000702 },
  { IDCANCEL, 0x02000710 }
};
#endif

bool CComboDialog::OnInit()
{
  #ifdef LANG
  LangSetDlgItemsText(HWND(*this), kIDLangPairs, sizeof(kIDLangPairs) / sizeof(kIDLangPairs[0]));
  #endif
  _comboBox.Attach(GetItem(IDC_COMBO_COMBO));

  /*
  // why it doesn't work ?
  DWORD style = _comboBox.GetStyle();
  if (Sorted)
    style |= CBS_SORT;
  else
    style &= ~CBS_SORT;
  _comboBox.SetStyle(style);
  */
  SetText(Title);
  
  NControl::CStatic staticContol;
  staticContol.Attach(GetItem(IDC_COMBO_STATIC));
  staticContol.SetText(Static);
  _comboBox.SetText(Value);
  for(int i = 0; i < Strings.Size(); i++)
    _comboBox.AddString(Strings[i]);
  NormalizeSize();
  return CModalDialog::OnInit();
}

bool CComboDialog::OnSize(WPARAM /* wParam */, int xSize, int ySize)
{
  int mx, my;
  GetMargins(8, mx, my);
  int bx1, bx2, by;
  GetItemSizes(IDCANCEL, bx1, by);
  GetItemSizes(IDOK, bx2, by);
  int y = ySize - my - by;
  int x = xSize - mx - bx1;

  InvalidateRect(NULL);

  MoveItem(IDCANCEL, x, y, bx1, by);
  MoveItem(IDOK, x - mx - bx2, y, bx2, by);
  ChangeSubWindowSizeX(_comboBox, xSize - mx * 2);
  return false;
}

void CComboDialog::OnOK()
{
  _comboBox.GetText(Value);
  CModalDialog::OnOK();
}
