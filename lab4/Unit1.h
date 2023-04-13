//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "VirtualTrees.hpp"
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Menus.hpp>
#include "sqlite3.h"
#include <Vcl.Dialogs.hpp>

typedef struct
{
	int id;
	UnicodeString url;
	AnsiString date;
    int visitCount;
} TreeData;
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
  __published: // IDE-managed Components
    TGridPanel* GridPanel1;
    TButton* btnDelete;
    TStatusBar* StatusBar1;
    TVirtualStringTree* VirtualStringTree;
    TMainMenu* MainMenu1;
    TMenuItem* N1;
    TMenuItem* N2;
    TMenuItem* N3;
    TOpenDialog* OpenDialog1;
	TButton *Button1;
    void __fastcall FormCreate(TObject* Sender);
    void __fastcall btnDeleteClick(TObject* Sender);
    void __fastcall VirtualStringTreeGetText(TBaseVirtualTree* Sender,
        PVirtualNode Node, TColumnIndex Column, TVSTTextType TextType,
        UnicodeString &CellText);
    void __fastcall VirtualStringTreeAddToSelection(
        TBaseVirtualTree* Sender, PVirtualNode Node);
    void __fastcall N2Click(TObject* Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall N3Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);

  private: // User declarations
    void __fastcall Log(UnicodeString str);
	void __fastcall LoadData(UnicodeString filename);
	void __fastcall CloseDataBase();
	bool isReady=false;
  public: // User declarations
    __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1* Form1;
//---------------------------------------------------------------------------
#endif

