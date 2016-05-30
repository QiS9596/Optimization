#pragma once
#include "DataManager.h"
#include "DotNetUtilities.h"
#include "linemethod.h"
#include "function.h"
#include "cg.h"
#include "simplified_matrix.h"
#include <vector>
#include "newton.h"
#define VecD std::vector<double>

namespace Optimization {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// MyForm 的摘要
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		std::vector<function*> * functions;
		MyForm(void)
		{
			InitializeComponent();
			dataManager = new DataManager();

			functions = new std::vector<function*>;
			//
			//TODO:  在此加入建構函式程式碼
			//
			/*

			testFunc1 *func01 = new testFunc1();
			testFunc2 *func02 = new testFunc2();
			testFunc3 *func03 = new testFunc3();
			(*functions).push_back(func01);
			(*functions).push_back(func02);
			(*functions).push_back(func03);
			//=============================================
			//test space

			std::cout << "Quasi-Newton Method test" << std::endl;
			testFunc1 func0;
			Qnewton qnw((*((*functions)[0])));
			VecD myp; myp.push_back(0.3);
			myp = qnw.minimize(myp);

			std::cout << "Conjugate Gradient method test: " << std::endl;
			testFunc2 func;
			cg<function> cg01(func);
			VecD p; p.push_back(0.3); 
			p = cg01.minimize(p);
			std::cout << "xmin " << p[0] << std::endl;
			std::cout << "fmin" << func(p) << std::endl;

			std::cout << "Newton Method for Optimization test: " << std::endl;
			testFunc3 func1;
			newton nw(func1);
			p.clear();
			p.push_back(5.0);
			p.push_back(5.0);
			p = nw.minimize(p);
			std::cout << p[0] << " " << p[1] << std::endl;*/
		}

	protected:
		/// <summary>
		DataManager* dataManager;
		/// 清除任何使用中的資源。
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;
	protected:
	private: System::Windows::Forms::FlowLayoutPanel^  flowLayoutPanel1;
	private: System::Windows::Forms::Label^  InputText;
	private: System::Windows::Forms::TextBox^  Input;
	private: System::Windows::Forms::Label^  OutputText;
	private: System::Windows::Forms::TextBox^  Output;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  loadEquationsToolStripMenuItem;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;

	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
		/// 這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->flowLayoutPanel1 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->InputText = (gcnew System::Windows::Forms::Label());
			this->Input = (gcnew System::Windows::Forms::TextBox());
			this->OutputText = (gcnew System::Windows::Forms::Label());
			this->Output = (gcnew System::Windows::Forms::TextBox());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->loadEquationsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->tableLayoutPanel1->SuspendLayout();
			this->flowLayoutPanel1->SuspendLayout();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->ColumnCount = 1;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel1->Controls->Add(this->flowLayoutPanel1, 0, 1);
			this->tableLayoutPanel1->Controls->Add(this->menuStrip1, 0, 0);
			this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel1->Location = System::Drawing::Point(0, 0);
			this->tableLayoutPanel1->Margin = System::Windows::Forms::Padding(4);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 2;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 5)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 95)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(726, 914);
			this->tableLayoutPanel1->TabIndex = 0;
			// 
			// flowLayoutPanel1
			// 
			this->flowLayoutPanel1->Controls->Add(this->InputText);
			this->flowLayoutPanel1->Controls->Add(this->Input);
			this->flowLayoutPanel1->Controls->Add(this->OutputText);
			this->flowLayoutPanel1->Controls->Add(this->Output);
			this->flowLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->flowLayoutPanel1->Location = System::Drawing::Point(4, 49);
			this->flowLayoutPanel1->Margin = System::Windows::Forms::Padding(4);
			this->flowLayoutPanel1->Name = L"flowLayoutPanel1";
			this->flowLayoutPanel1->Size = System::Drawing::Size(718, 861);
			this->flowLayoutPanel1->TabIndex = 0;
			// 
			// InputText
			// 
			this->InputText->AutoSize = true;
			this->InputText->Location = System::Drawing::Point(4, 0);
			this->InputText->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->InputText->Name = L"InputText";
			this->InputText->Size = System::Drawing::Size(43, 18);
			this->InputText->TabIndex = 0;
			this->InputText->Text = L"Input";
			this->InputText->Click += gcnew System::EventHandler(this, &MyForm::InputText_Click);
			// 
			// Input
			// 
			this->Input->Location = System::Drawing::Point(4, 22);
			this->Input->Margin = System::Windows::Forms::Padding(4);
			this->Input->Multiline = true;
			this->Input->Name = L"Input";
			this->Input->Size = System::Drawing::Size(710, 196);
			this->Input->TabIndex = 1;
			this->Input->TextChanged += gcnew System::EventHandler(this, &MyForm::Input_TextChanged);
			// 
			// OutputText
			// 
			this->OutputText->AutoSize = true;
			this->OutputText->Location = System::Drawing::Point(4, 222);
			this->OutputText->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->OutputText->Name = L"OutputText";
			this->OutputText->Size = System::Drawing::Size(54, 18);
			this->OutputText->TabIndex = 2;
			this->OutputText->Text = L"Output";
			// 
			// Output
			// 
			this->Output->Location = System::Drawing::Point(4, 244);
			this->Output->Margin = System::Windows::Forms::Padding(4);
			this->Output->Multiline = true;
			this->Output->Name = L"Output";
			this->Output->Size = System::Drawing::Size(710, 596);
			this->Output->TabIndex = 3;
			// 
			// menuStrip1
			// 
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(24, 24);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->fileToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Padding = System::Windows::Forms::Padding(9, 3, 0, 3);
			this->menuStrip1->Size = System::Drawing::Size(726, 33);
			this->menuStrip1->TabIndex = 1;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->loadEquationsToolStripMenuItem });
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(51, 27);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// loadEquationsToolStripMenuItem
			// 
			this->loadEquationsToolStripMenuItem->Name = L"loadEquationsToolStripMenuItem";
			this->loadEquationsToolStripMenuItem->Size = System::Drawing::Size(223, 30);
			this->loadEquationsToolStripMenuItem->Text = L"Load Equations";
			this->loadEquationsToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::loadEquationsToolStripMenuItem_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			this->openFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::openFileDialog1_FileOk);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 18);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(726, 914);
			this->Controls->Add(this->tableLayoutPanel1);
			this->MainMenuStrip = this->menuStrip1;
			this->Margin = System::Windows::Forms::Padding(4);
			this->Name = L"MyForm";
			this->Text = L"Optimization";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->tableLayoutPanel1->ResumeLayout(false);
			this->tableLayoutPanel1->PerformLayout();
			this->flowLayoutPanel1->ResumeLayout(false);
			this->flowLayoutPanel1->PerformLayout();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void loadEquationsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		openFileDialog1->ShowDialog();
	}
private: System::Void openFileDialog1_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
	//在Dialog按下OK便會進入此函式
	//字串轉制string^ to string
	std::string tempFileName;
	MarshalString(openFileDialog1->FileName, tempFileName);
	//將檔案路徑名稱傳入dataManager
	dataManager->SetFileName(tempFileName);
	//從讀取讀取向量資料
	if (dataManager->LoadEquationData())
	{
		std::vector<std::string> equations = dataManager->GetEquations();
		Output->Multiline = true;
		for (unsigned int i = 0; i < equations.size(); i++)
		{
			Output->Text += gcnew String(equations[i].c_str());
			Output->Text += Environment::NewLine;

		}
		for (unsigned int index = 0; index < equations.size(); index++){
			functions->push_back(new function(equations[index]));
			std::cout << (*functions)[index]->str() << index << std::endl;
		}
		std::cout << (*functions)[0]->dimension;
	}
}
private: System::Void Input_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	if (Input->Text->EndsWith("\n"))
	{
		String^ userInput = "";
		array<String^> ^userCommand1 = Input->Text->Split('\n');
		userInput = userCommand1[userCommand1->Length - 2];
		array<String^> ^userCommand = userInput->Split(' ');
		for (int i = 1; i < userCommand->Length; i++)
			userCommand[0] += userCommand[i];
		if (userCommand[0]->Length > 1) {
			if (userCommand[0] == "clr\r"||userCommand[0] == "clr")
			{
				Input->Text = "";
				Output->Text = "";
			}
			else if (userCommand[0] == "cmd\r" || userCommand[0] == "cmd") {
				Output->Text += "opt int(function select) double double (initial point) int (method)\r\n";
				Output->Text += "for 1D function, input any double value for the second double input for init point";
				Output->Text += Environment::NewLine;
			}
			else
			{

				int a = Convert::ToInt32(userCommand[4]);
				switch (a) {
				case 1: {
					int temp = Convert::ToInt32(userCommand[1]);
					std::cout << "break point" << std::endl;
					newton nw(*((*functions)[temp-1]));
					std::cout << "break point1" << std::endl;
					VecD p;
					p.push_back(Convert::ToDouble(userCommand[2]));
					std::cout << "current dimension " << (*functions)[temp]->dimension << std::endl;
					std::cout << (*functions)[temp]->str() << std::endl;
					if ((*functions)[temp-1]->dimension == 2)
						p.push_back(Convert::ToDouble(userCommand[3]));
					p = nw.minimize(p);
					Output->Text += gcnew String(nw.out_put_data().c_str());
					Output->Text += "x: ";
					Output->Text += p[0];
					if (temp != 1) {
						Output->Text += ", ";
						Output->Text += p[1];
					}
					Output->Text += Environment::NewLine;
					break;
				}
				case 2: {
					int temp = Convert::ToInt32(userCommand[1]);
					std::cout << "break point" << std::endl;
					Qnewton qnw(*((*functions)[temp - 1]));
					std::cout << "break point1" << std::endl;
					VecD p;
					p.push_back(Convert::ToDouble(userCommand[2]));
					if (temp != 1)
						p.push_back(Convert::ToDouble(userCommand[3]));
					p = qnw.minimize(p);
					Output->Text += gcnew String(qnw.out_put_data().c_str());
					Output->Text += "x: ";
					Output->Text += p[0];
					if (temp != 1) {
						Output->Text += ", ";
						Output->Text += p[1];
					}
					Output->Text += Environment::NewLine;
					break;
				}
				case 3: {
					int temp = Convert::ToInt32(userCommand[1]);
					std::cout << "break point" << std::endl;
					cg<function> cg1(*((*functions)[temp - 1]));
					std::cout << "break point1" << std::endl;
					VecD p;
					p.push_back(Convert::ToDouble(userCommand[2]));
					if (temp != 1)
						p.push_back(Convert::ToDouble(userCommand[3]));
					p = cg1.minimize(p);
					Output->Text += gcnew String(cg1.out_put_data().c_str());
					Output->Text += "x: ";
					Output->Text += p[0];
					if (temp != 1) {
						Output->Text += ", ";
						Output->Text += p[1];
					}
					Output->Text += Environment::NewLine;
					break;
				}
				}
			}
		}
	
	}
}
private: System::Void InputText_Click(System::Object^  sender, System::EventArgs^  e) {
}
};
}
