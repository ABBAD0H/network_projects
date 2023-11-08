#pragma once
#include <iostream>
#pragma comment(lib,"ws2_32.lib")
#include <WinSock2.h>
#include <string>
#include <msclr\marshal_cppstd.h> 
#pragma warning(disable : 4996)
using namespace std;
using namespace msclr::interop;
SOCKET connection;
string msg2;
sockaddr_in addr;
bool flag = 0;
namespace chat2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	void ClientHandler()
	{
		char msg[256];

		while (1)
		{
			//string fff;
			recv(connection, msg, sizeof(msg), NULL);
			/*
			for (int i = 0; i < 256; i++)
				fff += msg[i];
			System::String^ msga = marshal_as<System::String^>(fff);
			MessageBox::Show(msga);
			fff.clear();
			*/
			
			for (int i = 0; i < 256; i++)
				msg2 += msg[i];
			flag = 1;
			

		}
	}
	/// <summary>
	/// —водка дл€ MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button1;
	protected:
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::Timer^ timer1;
	private: System::ComponentModel::IContainer^ components;

	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(39, 277);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"ќтправить";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(39, 45);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(270, 226);
			this->textBox1->TabIndex = 1;
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(315, 45);
			this->textBox2->Multiline = true;
			this->textBox2->Name = L"textBox2";
			this->textBox2->ReadOnly = true;
			this->textBox2->Size = System::Drawing::Size(277, 226);
			this->textBox2->TabIndex = 2;
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Interval = 500;
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(604, 371);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) 
	{
		WSADATA data;
		WORD DLLversion = MAKEWORD(2, 1);
		if (WSAStartup(DLLversion, &data) != 0)
		{
			MessageBox::Show("Library error");
			exit(1);
		}
		
		addr.sin_addr.s_addr = inet_addr("192.168.0.1");
		addr.sin_port = htons(7500);
		addr.sin_family = AF_INET;

		connection = socket(AF_INET, SOCK_STREAM, NULL);

		if (connect(connection, (SOCKADDR*)&addr, sizeof(addr)) != 0)
		{
			MessageBox::Show("client error connection");
			exit(1);
		}
		char msg[4] = { '1','1','1','1' };
		send(connection, msg, sizeof(msg), NULL);
		MessageBox::Show("connection to server complete"); 

		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, NULL, NULL, NULL);

	}


	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) 
	{
		
		if (flag)
		{
			System::String^ msg = marshal_as<System::String^>(msg2);
			textBox2->Text = msg;
			msg2.clear();
			flag = 0;
		}
		
	}
private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) 
{
	string msg;
	System::String^ msg1 = textBox1->Text;
	msg = marshal_as<string>(msg1);
	char messenge[256];
	for (int i = 0; i < msg.length(); i++)
		messenge[i] = msg[i];
	messenge[msg.length() + 1] = 0;
	send(connection, messenge, sizeof(messenge), NULL);
	Sleep(10);
}
};
}
