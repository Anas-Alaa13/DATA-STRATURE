#pragma once

namespace DataStructure {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class StudentFunction : public System::Windows::Forms::Form
	{
	public:
		StudentFunction(void)
		{
			InitializeComponent();
		}

	protected:
		~StudentFunction()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		Button^ btnCourseRegistration;
		Button^ btnViewGrades;
		Button^ btnCheckPrerequisites;
		Button^ btnMakeReport;
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->btnCourseRegistration = (gcnew System::Windows::Forms::Button());
			this->btnViewGrades = (gcnew System::Windows::Forms::Button());
			this->btnCheckPrerequisites = (gcnew System::Windows::Forms::Button());
			this->btnMakeReport = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// btnCourseRegistration
			// 
			this->btnCourseRegistration->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
			this->btnCourseRegistration->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->btnCourseRegistration->Location = System::Drawing::Point(110, 30);
			this->btnCourseRegistration->Name = L"btnCourseRegistration";
			this->btnCourseRegistration->Size = System::Drawing::Size(180, 40);
			this->btnCourseRegistration->TabIndex = 0;
			this->btnCourseRegistration->Text = L"Course Registration";
			// 
			// btnViewGrades
			// 
			this->btnViewGrades->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
			this->btnViewGrades->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->btnViewGrades->Location = System::Drawing::Point(110, 80);
			this->btnViewGrades->Name = L"btnViewGrades";
			this->btnViewGrades->Size = System::Drawing::Size(180, 40);
			this->btnViewGrades->TabIndex = 1;
			this->btnViewGrades->Text = L"View Grades";
			// 
			// btnCheckPrerequisites
			// 
			this->btnCheckPrerequisites->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
			this->btnCheckPrerequisites->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->btnCheckPrerequisites->Location = System::Drawing::Point(110, 130);
			this->btnCheckPrerequisites->Name = L"btnCheckPrerequisites";
			this->btnCheckPrerequisites->Size = System::Drawing::Size(180, 40);
			this->btnCheckPrerequisites->TabIndex = 2;
			this->btnCheckPrerequisites->Text = L"Check Prerequisites";
			// 
			// btnMakeReport
			// 
			this->btnMakeReport->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
			this->btnMakeReport->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->btnMakeReport->Location = System::Drawing::Point(110, 180);
			this->btnMakeReport->Name = L"btnMakeReport";
			this->btnMakeReport->Size = System::Drawing::Size(180, 40);
			this->btnMakeReport->TabIndex = 3;
			this->btnMakeReport->Text = L"Make Report";
			// 
			// StudentFunction
			// 
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(21)), static_cast<System::Int32>(static_cast<System::Byte>(52)),
				static_cast<System::Int32>(static_cast<System::Byte>(72)));
			this->ClientSize = System::Drawing::Size(400, 300);
			this->Controls->Add(this->btnCourseRegistration);
			this->Controls->Add(this->btnViewGrades);
			this->Controls->Add(this->btnCheckPrerequisites);
			this->Controls->Add(this->btnMakeReport);
			this->Name = L"StudentFunction";
			this->Text = L"Student Function";
			this->Load += gcnew System::EventHandler(this, &StudentFunction::StudentFunction_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void StudentFunction_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	};
}

