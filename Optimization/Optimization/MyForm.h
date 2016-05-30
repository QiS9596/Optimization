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
		}
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	public:
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  loadEquationsToolStripMenuItem;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::TextBox^  Input;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::TextBox^  Output;

	public:


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

	protected:








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
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->loadEquationsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->Input = (gcnew System::Windows::Forms::TextBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->Output = (gcnew System::Windows::Forms::TextBox());
			this->menuStrip1->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->SuspendLayout();
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			this->openFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::openFileDialog1_FileOk);
			// 
			// menuStrip1
			// 
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(24, 24);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->fileToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(449, 24);
			this->menuStrip1->TabIndex = 4;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->loadEquationsToolStripMenuItem });
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(39, 20);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// loadEquationsToolStripMenuItem
			// 
			this->loadEquationsToolStripMenuItem->Name = L"loadEquationsToolStripMenuItem";
			this->loadEquationsToolStripMenuItem->Size = System::Drawing::Size(164, 22);
			this->loadEquationsToolStripMenuItem->Text = L"Load Equations";
			this->loadEquationsToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::loadEquationsToolStripMenuItem_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->Input);
			this->groupBox1->Dock = System::Windows::Forms::DockStyle::Top;
			this->groupBox1->Location = System::Drawing::Point(0, 24);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Padding = System::Windows::Forms::Padding(5, 3, 5, 5);
			this->groupBox1->Size = System::Drawing::Size(449, 167);
			this->groupBox1->TabIndex = 5;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Input";
			// 
			// Input
			// 
			this->Input->Dock = System::Windows::Forms::DockStyle::Fill;
			this->Input->Font = (gcnew System::Drawing::Font(L"Consolas", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Input->Location = System::Drawing::Point(5, 18);
			this->Input->Multiline = true;
			this->Input->Name = L"Input";
			this->Input->Size = System::Drawing::Size(439, 144);
			this->Input->TabIndex = 1;
			this->Input->TextChanged += gcnew System::EventHandler(this, &MyForm::Input_TextChanged);
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->Output);
			this->groupBox2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->groupBox2->Location = System::Drawing::Point(0, 191);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Padding = System::Windows::Forms::Padding(5, 3, 5, 5);
			this->groupBox2->Size = System::Drawing::Size(449, 338);
			this->groupBox2->TabIndex = 6;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Output";
			// 
			// Output
			// 
			this->Output->Dock = System::Windows::Forms::DockStyle::Fill;
			this->Output->Font = (gcnew System::Drawing::Font(L"Consolas", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Output->Location = System::Drawing::Point(5, 18);
			this->Output->Multiline = true;
			this->Output->Name = L"Output";
			this->Output->Size = System::Drawing::Size(439, 315);
			this->Output->TabIndex = 3;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(449, 529);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->menuStrip1);
			this->Name = L"MyForm";
			this->Text = L"Optimization";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

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
				Output->Text += "	for 1D function, input any double value for the second double input for init point";
				Output->Text += Environment::NewLine;
				Output->Text += "	method = 1 for new ton 2 for q newton 3 for conjugete gradient";
				Output->Text += Environment::NewLine;
				Output->Text += "func \r\n";
				Output->Text += "	print out all the functions";
				Output->Text += Environment::NewLine;
				Output->Text += "itv int(function number) double(lower bound) double(upper bound)";
				Output->Text += Environment::NewLine;
				Output->Text += "	set the x's inverval. Unfortunately it may cause error for newton and q newton method currently";
				Output->Text += Environment::NewLine;
			}
			else if (userCommand[0][0] == 'i'&&userCommand[0][1] == 't'&&userCommand[0][2] == 'v') {
				int a = Convert::ToInt32(userCommand[1]);
				(*functions)[a - 1]->setInterval(Convert::ToDouble(userCommand[2]), Convert::ToDouble(userCommand[3]));
			}

			else if (userCommand[0] == "func" || userCommand[0] == "func\r") {
				for (int index = 0; index < (*functions).size(); index++) {
					Output->Text += index+1;
					Output->Text += "th func:";
					Output->Text += gcnew String((*functions)[index]->str().c_str());
					//Output->Text += Environment::NewLine;
				}
			}
			else if(userCommand[0][0] == 'o' && userCommand[0][1] == 'p' && userCommand[0][2] == 't')
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
					//std::cout << "current dimension " << (*functions)[temp]->dimension << std::endl;
					//std::cout << (*functions)[temp]->str() << std::endl;
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
};
}
