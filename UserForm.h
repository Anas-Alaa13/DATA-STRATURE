#pragma once
#include "AdminFunctions.h"
#include "StudentFunctions.h"

namespace DataStructure {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class UserForm : public System::Windows::Forms::Form
	{
	public:
		UserForm(void)
		{
			InitializeComponent();
		}

	protected:
		~UserForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		System::Windows::Forms::Button^ btnStudent;
		System::Windows::Forms::Button^ btnAdmin;
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->btnStudent = (gcnew System::Windows::Forms::Button());
			this->btnAdmin = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// btnStudent
			// 
			this->btnStudent->BackColor = System::Drawing::Color::White;
			this->btnStudent->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10));
			this->btnStudent->Location = System::Drawing::Point(130, 60);
			this->btnStudent->Name = L"btnStudent";
			this->btnStudent->Size = System::Drawing::Size(140, 40);
			this->btnStudent->TabIndex = 1;
			this->btnStudent->Text = L"Student";
			this->btnStudent->UseVisualStyleBackColor = false;
			this->btnStudent->Click += gcnew System::EventHandler(this, &UserForm::btnStudent_Click);
			// 
			// btnAdmin
			// 
			this->btnAdmin->BackColor = System::Drawing::Color::White;
			this->btnAdmin->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10));
			this->btnAdmin->Location = System::Drawing::Point(130, 120);
			this->btnAdmin->Name = L"btnAdmin";
			this->btnAdmin->Size = System::Drawing::Size(140, 40);
			this->btnAdmin->TabIndex = 0;
			this->btnAdmin->Text = L"Admin";
			this->btnAdmin->UseVisualStyleBackColor = false;
			this->btnAdmin->Click += gcnew System::EventHandler(this, &UserForm::btnAdmin_Click);
			// 
			// UserForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(21)), static_cast<System::Int32>(static_cast<System::Byte>(52)),
				static_cast<System::Int32>(static_cast<System::Byte>(72)));
			this->ClientSize = System::Drawing::Size(400, 250);
			this->Controls->Add(this->btnAdmin);
			this->Controls->Add(this->btnStudent);
			this->Name = L"UserForm";
			this->Text = L"User Panel";
			this->Load += gcnew System::EventHandler(this, &UserForm::UserForm_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void btnAdmin_Click(System::Object^ sender, System::EventArgs^ e) {
		AdminFunctions^ adminForm = gcnew AdminFunctions();
		adminForm->Show();
	}

	private: System::Void btnStudent_Click(System::Object^ sender, System::EventArgs^ e) {
		StudentFunction^ studentForm = gcnew StudentFunction();
		studentForm->Show();
	}

	private: System::Void UserForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	};
}
