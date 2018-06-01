//---------------------------------------------------------------------------

#include <vcl.h>

#include <iostream>
#include <vector>
#include <string>
#include <locale>
#include <cctype>
#include <fstream>

#include "Patient.h"

#pragma hdrstop

#include "MainForm.h"
#include "ABOUT.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

using namespace std;

TForm1 *Form1;
//---------------------------------------------------------------------------

int i;
int count_patient = 0;
int current_id = 0;

int ID = 0;
float height = 0;
float weight = 0;
string firstName;
string secondName;
string thirdName;

vector<Patient> patient_base;
vector<Patient>::iterator it;

bool changes = false;

string path;


const int columns = 6;
String columnHeaders[columns] = {"ID", "Фамилия", "Имя", "Отчество", "Рост", "Вес"};
int columnSize[columns] = {50, 100, 100, 100, 50, 50};



__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
	StringGrid->ColCount = columns;

	for ((i = 0); i < columns; i++) {
		StringGrid->Cells[i][0] =  columnHeaders[i];
		StringGrid->ColWidths[i] = columnSize[i];
	}

	StatusBar->Panels->Items[0]->Text = "Пациентов в базе: 0";
	RadioGroup->ItemIndex = 0;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
	N7->Click();
	patient_base.clear();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ButtonDeleteClick(TObject *Sender)
{
	changes = true;
	int row = StringGrid->Row;
	it = patient_base.begin();
	advance(it, row - 1);
	patient_base.erase(it);
	count_patient--;
	ButtonDelete->Enabled = false;
	ButtonUpdate->Click();

}
//---------------------------------------------------------------------------

void __fastcall TForm1::ButtonAddClick(TObject *Sender)
{
	setlocale(LC_ALL, "Russian");
	ButtonDone->Click();
	if (!(EditSecondName->Text.IsEmpty()) && !(EditFirstName->Text.IsEmpty()) && !(EditThirdName->Text.IsEmpty()) && !(EditHeight->Text.IsEmpty()) && !(EditWeight->Text.IsEmpty())){
		secondName = AnsiString(EditSecondName->Text).c_str();
		firstName = AnsiString(EditFirstName->Text).c_str();
		thirdName = AnsiString(EditThirdName->Text).c_str();
		secondName[0] = toupper(secondName[0]);
		firstName[0] = toupper(firstName[0]);
		thirdName[0] = toupper(thirdName[0]);
		patient_base.push_back(Patient(++current_id,  firstName, secondName, thirdName, StrToFloat(EditHeight->Text), StrToFloat(EditWeight->Text)));
		count_patient++;
		EditSecondName->Clear();
		EditFirstName->Clear();
		EditThirdName->Clear();
		EditHeight->Clear();
		EditWeight->Clear();
		ButtonUpdate->Click();
		changes = true;
	} else {
		MessageBox(0, L"Заполните поля", L"Ошибка ввода", MB_OK);
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ButtonUpdateClick(TObject *Sender)
{
	int i, j;
	StringGrid->RowCount = count_patient + 1;
	if (count_patient > 0) {
		StringGrid->FixedRows = 1;
	}
	for (i = 0; i < count_patient; i++) {
		StringGrid->Cells[0][i + 1] = IntToStr(patient_base[i].GetID());
		StringGrid->Cells[1][i + 1] = patient_base[i].GetSecondName().c_str();
		StringGrid->Cells[2][i + 1] = patient_base[i].GetFirstName().c_str();
		StringGrid->Cells[3][i + 1] = patient_base[i].GetThirdName().c_str();
		StringGrid->Cells[4][i + 1] = FormatFloat("###.#", patient_base[i].GetHeight());
		StringGrid->Cells[5][i + 1] = FormatFloat("###.#", patient_base[i].GetWeight());
	}

	StatusBar->Panels->Items[0]->Text = "Пациентов в базе: " + IntToStr(count_patient);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StringGridDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
		  TGridDrawState State)
{
	if (ARow==0) {
		StringGrid->Canvas->Brush->Color = clYellow;
		StringGrid->Canvas->FillRect(Rect);
		DrawText(StringGrid->Canvas->Handle,StringGrid->Cells[ACol][0].w_str(),-1,
			&Rect,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StringGridSelectCell(TObject *Sender, int ACol, int ARow,
          bool &CanSelect)
{
	if (ARow == 0) {
		StringGrid->Options >> goEditing;
	}
	else {
		if (ACol == 0) {
			 StringGrid->Options >> goEditing;
		}
		else {
			StringGrid->Options << goEditing;
		}
		ButtonDelete->Enabled = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StringGridSetEditText(TObject *Sender, int ACol, int ARow,
		  const UnicodeString Value)
{
	changes = true;
	ButtonApplyChanges->Click();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StringGridExit(TObject *Sender)
{
	ButtonApplyChanges->Click();
	ButtonUpdate->Click();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ButtonApplyChangesClick(TObject *Sender)
{
	setlocale(LC_ALL, "Russian");
	int i, j;
	for (i = 0; i < count_patient; i++) {
		if (StringGrid->Cells[1][i + 1] != "" && StringGrid->Cells[2][i + 1] != "" && StringGrid->Cells[3][i + 1] != "" && StringGrid->Cells[4][i + 1] != "" && StringGrid->Cells[5][i + 1] != "") {
			ID = StrToInt(StringGrid->Cells[0][i + 1]);
			secondName = AnsiString(StringGrid->Cells[1][i + 1]).c_str();
			firstName = AnsiString(StringGrid->Cells[2][i + 1]).c_str();
			thirdName = AnsiString(StringGrid->Cells[3][i + 1]).c_str();
			secondName[0] = toupper(secondName[0]);
			firstName[0] = toupper(firstName[0]);
			thirdName[0] = toupper(thirdName[0]);
			height = StrToFloat(StringGrid->Cells[4][i + 1]);
			weight = StrToFloat(StringGrid->Cells[5][i + 1]);

			patient_base[i].SetPatient(ID, firstName, secondName, thirdName, height, weight);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ButtonSearchClick(TObject *Sender)
{
	setlocale(LC_ALL, "Russian");
	string temp;
	int findCol;
	if (EditSearchValue->Text != "") {
		findCol = RadioGroup->ItemIndex;
		if (findCol == 1 || findCol == 2 || findCol == 3) {
			temp = AnsiString(EditSearchValue->Text).c_str();
			temp[0] = toupper(temp[0]);
			EditSearchValue->Text = temp.c_str();
		}
		for (i = 0; i < count_patient; i++) {
			if (StringGrid->Cells[findCol][i + 1] != EditSearchValue->Text) {
				StringGrid->RowHeights[i + 1] = 0;
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ButtonDoneClick(TObject *Sender)
{
	EditSearchValue->Clear();
    for (i = 0; i < count_patient; i++) {
		StringGrid->RowHeights[i + 1] = StringGrid->DefaultRowHeight;;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::NButtonOpenClick(TObject *Sender)
{
	if (count_patient > 0 && changes) {
		if (MessageBox(0, L"Сохранить файл?", L"Подтвердите сохранение", MB_YESNO) == IDYES) {
			N5->Click();
		}
	}
	if (OpenDialog->Execute()) {
		ifstream fin;
		fin.open(AnsiString(OpenDialog->FileName).c_str());
		if (!fin.is_open()) {
			MessageBox(0, L"Не удалось открыть файл", L"Ошибка чтения файла", MB_OK);
		}
		else {
			if (fin.read((char*)&count_patient, sizeof(int))) {
				fin >> current_id;
				for (i = 0; i < count_patient; i++) {
					fin >> ID;
					fin >> firstName;
					fin >> secondName;
					fin >> thirdName;
					fin >> height;
					fin >> weight;
					patient_base.push_back(Patient(ID, firstName, secondName, thirdName, height, weight));
				}
			}
			else {
				count_patient = 0;
			}
		}
		fin.close();
		StatusBar->Panels->Items[1]->Text = OpenDialog->FileName;
		ButtonUpdate->Click();
		changes = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N6Click(TObject *Sender)
{
	if (SaveDialog->Execute()) {
		ButtonApplyChanges->Click();
		ofstream fout;
		fout.open(AnsiString(SaveDialog->FileName + ".patient").c_str());

		if (!fout.is_open()) {
			MessageBox(0, L"Не удалось открыть файл", L"Ошибка чтения файла", MB_OK);
		}
		else {
			fout.write((char*)&count_patient, sizeof(int));

			if (patient_base.empty()) {
				current_id = 0;
			}

			fout << current_id << endl;

			for (i = 0; i != patient_base.size(); i++) {
				fout << patient_base[i].GetID() << endl;
				fout << patient_base[i].GetFirstName() << endl;
				fout << patient_base[i].GetSecondName() << endl;
				fout << patient_base[i].GetThirdName() << endl;
				fout << patient_base[i].GetHeight() << endl;
				fout << patient_base[i].GetWeight() << endl;
			}
		}

		fout.close();
		changes = false;
		StatusBar->Panels->Items[1]->Text = SaveDialog->FileName;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N7Click(TObject *Sender)
{
	if (count_patient > 0 && changes) {
		if (MessageBox(0, L"Сохранить изменения в файле?", L"Подтвердите сохранение", MB_YESNO) == IDYES) {
			N5->Click();
		}
	}

	for (i = 1; i < StringGrid->RowCount; i++) {
		StringGrid->Rows[i]->Clear();
	}

	StringGrid->RowCount = 1;

	patient_base.clear();
	count_patient = 0;
	ButtonUpdate->Click();
	StatusBar->Panels->Items[1]->Text = "Без имени";
	changes = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N5Click(TObject *Sender)
{
	if (StatusBar->Panels->Items[1]->Text == "Без имени") {
		N6->Click();
	}
	else {
		ButtonApplyChanges->Click();
		ofstream fout;
		fout.open(AnsiString(StatusBar->Panels->Items[1]->Text).c_str());

		if (!fout.is_open()) {
			MessageBox(0, L"Не удалось открыть файл", L"Ошибка чтения файла", MB_OK);
		}
		else {
			fout.write((char*)&count_patient, sizeof(int));

			if (patient_base.empty()) {
				current_id = 0;
			}

			fout << current_id << endl;

			for (i = 0; i != patient_base.size(); i++) {
				fout << patient_base[i].GetID() << endl;
				fout << patient_base[i].GetFirstName() << endl;
				fout << patient_base[i].GetSecondName() << endl;
				fout << patient_base[i].GetThirdName() << endl;
				fout << patient_base[i].GetHeight() << endl;
				fout << patient_base[i].GetWeight() << endl;
			}
		}

		fout.close();
		changes = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N2AboutClick(TObject *Sender)
{
	Application->CreateForm(__classid(TAboutBox), &AboutBox);
	AboutBox->ShowModal();
	AboutBox->Free();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N8Click(TObject *Sender)
{
	Form1->Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::EditSecondNameKeyPress(TObject *Sender, System::WideChar &Key)
{
	if(!iswalpha(Key) && Key != VK_BACK){
		Key = 0;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::EditHeightKeyPress(TObject *Sender, System::WideChar &Key)
{
	String dsstr = FormatSettings.DecimalSeparator;
	if(!isdigit(Key) &&  Key != VK_BACK){
		if (Key == '.' && dsstr=="." || Key == ',' && dsstr==",") {
			if (EditHeight->Text.Pos(Key)!=0) {
				Key = 0;
			}
		} else {Key = 0;}
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::EditWeightKeyPress(TObject *Sender, System::WideChar &Key)
{
	String dsstr = FormatSettings.DecimalSeparator;
	if(!isdigit(Key) &&  Key != VK_BACK){
		if (Key == '.' && dsstr=="." || Key == ',' && dsstr==",") {
			if (EditWeight->Text.Pos(Key)!=0) {
				Key = 0;
			}
		} else {Key = 0;}
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	if (MessageBox(0, L"Действительно выйти?", L"Подтвердите выход", MB_YESNO) == IDYES) {
		CanClose=true;
	}
	else CanClose=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StringGridKeyPress(TObject *Sender, System::WideChar &Key)
{
	String dsstr = FormatSettings.DecimalSeparator;
	if (StringGrid->Col == 4 || StringGrid->Col == 5) {
		String dstr = FormatSettings.DecimalSeparator;
		if(!isdigit(Key) &&  Key != VK_BACK){
			if (Key == '.' && dsstr=="." || Key == ',' && dsstr==",") {
				if (StringGrid->Cells[StringGrid->Col][StringGrid->Row].Pos(Key)!=0) {
					Key = 0;
				}
			} else {Key = 0;}
		}
	}
	else {
    	if(!iswalpha(Key) && Key != VK_BACK){
			Key = 0;
		}
	}
}
//---------------------------------------------------------------------------


