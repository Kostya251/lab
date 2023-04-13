//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VirtualTrees"
#pragma resource "*.dfm"
TForm1* Form1;
int result;
sqlite3* Database;
//const WCHAR* filename = L"D:\\Projects\\test_sqlite\\History";
UnicodeString filename;
sqlite3_stmt* pStatementVisits;
sqlite3_stmt* pStatementUrl;
sqlite3_stmt* pStatementDeleteRow;
sqlite3_stmt* pStatementDeleteAll;
const char* errmsg;
const WCHAR* sqlVisits =
    L"SELECT id,url,datetime(visit_time / 1000000 + (strftime('%s', '1601-01-01')), 'unixepoch', 'localtime') FROM visits;";
const WCHAR* sqlUrl = L"SELECT id,url,visit_count FROM urls where id = ?;";
const WCHAR* sqlDeleteRow = L"DELETE FROM visits WHERE id = ?;";
const WCHAR* sqlDeleteAll = L"DELETE from visits;";
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner) {}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject* Sender)
{
    VirtualStringTree->NodeDataSize = sizeof(TreeData);
    //    VirtualStringTree->Header->Columns[0].SetDefaultWidth(30);
    //    LoadData();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnDeleteClick(TObject* Sender)
{
    if (isReady == false)
        return;
    PVirtualNode node = VirtualStringTree->GetFirstSelected();
    for (UInt64 i = 0; i < VirtualStringTree->SelectedCount; ++i) {
        TreeData* treeData = (TreeData*)VirtualStringTree->GetNodeData(node);
        node = VirtualStringTree->GetNextSelected(node);
        if ((result = sqlite3_bind_int64(
                 pStatementDeleteRow, 1, treeData->id)) != SQLITE_OK)
        {
            isReady = false;
            break;
        }
        if ((result = sqlite3_step(pStatementDeleteRow)) != SQLITE_DONE) {
            isReady = false;
            break;
        }
        sqlite3_reset(pStatementDeleteRow);
        Log("Delete " + treeData->url);
    }
    if (isReady == false) {
        errmsg = sqlite3_errmsg(Database);
        Log(errmsg);
    } else {
        VirtualStringTree->BeginUpdate();
		VirtualStringTree->DeleteSelectedNodes();
        VirtualStringTree->EndUpdate();
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::VirtualStringTreeGetText(TBaseVirtualTree* Sender,
    PVirtualNode Node, TColumnIndex Column, TVSTTextType TextType,
    UnicodeString &CellText)

{
    TreeData* treeData = (TreeData*)Sender->GetNodeData(Node);
    switch (Column) {
        case 0:
            CellText = treeData->url;
            break;
        case 1:
            CellText = treeData->date;
            break;
    }
}

//---------------------------------------------------------------------------

void __fastcall TForm1::VirtualStringTreeAddToSelection(
    TBaseVirtualTree* Sender, PVirtualNode Node)
{
    TreeData* treeData = (TreeData*)Sender->GetNodeData(Node);
    Log("Visit count: " + AnsiString(treeData->visitCount));
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Log(UnicodeString str)
{
    StatusBar1->Panels->Items[0]->Text = str;
}

void __fastcall TForm1::N2Click(TObject* Sender)
{
    AnsiString exeFile = Application->ExeName;
    if (filename.IsEmpty())
        filename = ExtractFilePath(exeFile);
    OpenDialog1->InitialDir = filename;
    OpenDialog1->Execute();
    filename = OpenDialog1->FileName;
    if (filename != "") {
        if (isReady)
            CloseDataBase();
        VirtualStringTree->Clear();
        Log("Loading file " + filename);
        LoadData(filename);
    } else {
        Log("bad");
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::LoadData(UnicodeString filename)
{
    if (sqlite3_open16(filename.c_str(), &Database) == SQLITE_OK) {
        Log("database was opened successfully");
    } else {
        Log("Error open file " + filename);
        return;
    }
    result =
        sqlite3_prepare16_v2(Database, sqlVisits, -1, &pStatementVisits, NULL);
    if (result != SQLITE_OK) {
        errmsg = sqlite3_errmsg(Database);
        Log(errmsg);
        sqlite3_close(Database);
        return;
    }
    result = sqlite3_prepare16_v2(Database, sqlUrl, -1, &pStatementUrl, NULL);
    if (result != SQLITE_OK) {
        errmsg = sqlite3_errmsg(Database);
        Log(errmsg);
        sqlite3_close(Database);
        return;
    }
    result = sqlite3_prepare16_v2(
        Database, sqlDeleteRow, -1, &pStatementDeleteRow, NULL);
    if (result != SQLITE_OK) {
        errmsg = sqlite3_errmsg(Database);
        Log(errmsg);
        sqlite3_close(Database);
        return;
    }
    result = sqlite3_prepare16_v2(
        Database, sqlDeleteAll, -1, &pStatementDeleteAll, NULL);
    if (result != SQLITE_OK) {
        errmsg = sqlite3_errmsg(Database);
        Log(errmsg);
        sqlite3_close(Database);
        return;
    }
    char* strUrl;
    char* strTime;
    int id;
    int urlId;
    int visitCount;
    VirtualStringTree->BeginUpdate();
    while ((result = sqlite3_step(pStatementVisits)) == SQLITE_ROW) {
        id = sqlite3_column_int64(pStatementVisits, 0);
        urlId = sqlite3_column_int64(pStatementVisits, 1);
        if ((result = sqlite3_bind_int64(pStatementUrl, 1, urlId)) != SQLITE_OK)
            break;
        if ((result = sqlite3_step(pStatementUrl)) != SQLITE_ROW)
            break;
        strUrl = (char*)sqlite3_column_text(pStatementUrl, 1);
        visitCount = sqlite3_column_int64(pStatementUrl, 2);
        //        Log((char*)strUrl);
        strTime = (char*)sqlite3_column_text(pStatementVisits, 2);
        PVirtualNode Node = VirtualStringTree->AddChild(NULL);
        TreeData* treeData = (TreeData*)VirtualStringTree->GetNodeData(Node);
        treeData->id = id;
        treeData->url = strUrl;
        treeData->date = strTime;
        treeData->visitCount = visitCount;
        sqlite3_reset(pStatementUrl);
    }
    VirtualStringTree->EndUpdate();
    if (result != SQLITE_DONE && result != SQLITE_OK) {
        errmsg = sqlite3_errmsg(Database);
        Log("*" + UnicodeString(errmsg));
    }
    isReady = true;
}

void __fastcall TForm1::CloseDataBase()
{
    sqlite3_finalize(pStatementVisits);
    sqlite3_finalize(pStatementUrl);
    sqlite3_finalize(pStatementDeleteRow);
    sqlite3_close(Database);
    isReady = false;
}

void __fastcall TForm1::FormClose(TObject* Sender, TCloseAction &Action)
{
    CloseDataBase();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N3Click(TObject* Sender)
{
    this->Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject* Sender)
{
    if (isReady == false)
        return;
    if ((result = sqlite3_step(pStatementDeleteAll)) != SQLITE_DONE) {
        isReady = false;
		errmsg = sqlite3_errmsg(Database);
		Log(errmsg);
    }
	sqlite3_reset(pStatementDeleteRow);
    VirtualStringTree->Clear();
    Log("Table is cleared.");
}
//---------------------------------------------------------------------------


