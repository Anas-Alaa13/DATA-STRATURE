#pragma once
#include "UploadCourse.h"
//#include "EditStudentForm.h"
#include"Edit.h"
namespace DataStructure {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class AdminFunctions : public System::Windows::Forms::Form
	{
	public:
		AdminFunctions(void)
		{
			InitializeComponent();
		}

	protected:
		~AdminFunctions()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		Button^ btnUploadCourse;
		Button^ btnSetPrerequisites;
		Button^ btnManageGrades;
		Button^ btnEditData;
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->btnUploadCourse = (gcnew System::Windows::Forms::Button());
			this->btnSetPrerequisites = (gcnew System::Windows::Forms::Button());
			this->btnManageGrades = (gcnew System::Windows::Forms::Button());
			this->btnEditData = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// btnUploadCourse
			// 
			this->btnUploadCourse->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnUploadCourse->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->btnUploadCourse->Location = System::Drawing::Point(125, 30);
			this->btnUploadCourse->Name = L"btnUploadCourse";
			this->btnUploadCourse->Size = System::Drawing::Size(150, 40);
			this->btnUploadCourse->TabIndex = 0;
			this->btnUploadCourse->Text = L"Upload Course";
			this->btnUploadCourse->Click += gcnew System::EventHandler(this, &AdminFunctions::btnUploadCourse_Click);
			// 
			// btnSetPrerequisites
			// 
			this->btnSetPrerequisites->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnSetPrerequisites->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->btnSetPrerequisites->Location = System::Drawing::Point(125, 80);
			this->btnSetPrerequisites->Name = L"btnSetPrerequisites";
			this->btnSetPrerequisites->Size = System::Drawing::Size(150, 40);
			this->btnSetPrerequisites->TabIndex = 1;
			this->btnSetPrerequisites->Text = L"Set Prerequisites";
			// 
			// btnManageGrades
			// 
			this->btnManageGrades->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnManageGrades->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->btnManageGrades->Location = System::Drawing::Point(125, 130);
			this->btnManageGrades->Name = L"btnManageGrades";
			this->btnManageGrades->Size = System::Drawing::Size(150, 40);
			this->btnManageGrades->TabIndex = 2;
			this->btnManageGrades->Text = L"Manage Grades";
			// 
			// btnEditData
			// 
			this->btnEditData->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnEditData->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->btnEditData->Location = System::Drawing::Point(125, 180);
			this->btnEditData->Name = L"btnEditData";
			this->btnEditData->Size = System::Drawing::Size(150, 40);
			this->btnEditData->TabIndex = 3;
			this->btnEditData->Text = L"Edit Data";
			this->btnEditData->Click += gcnew System::EventHandler(this, &AdminFunctions::btnEditData_Click);
			// 
			// AdminFunctions
			// 
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(21)), static_cast<System::Int32>(static_cast<System::Byte>(52)),
				static_cast<System::Int32>(static_cast<System::Byte>(72)));
			this->ClientSize = System::Drawing::Size(400, 300);
			this->Controls->Add(this->btnUploadCourse);
			this->Controls->Add(this->btnSetPrerequisites);
			this->Controls->Add(this->btnManageGrades);
			this->Controls->Add(this->btnEditData);
			this->Name = L"AdminFunctions";
			this->Text = L"Admin Functions";
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void btnUploadCourse_Click(System::Object^ sender, System::EventArgs^ e) {
		// إذا استعملت using namespace DataStructure
		UploadCourse^ uploadForm = gcnew UploadCourse();
		uploadForm->Show();           // أو ShowDialog() إذا حابب تفتحه مودال

		// بدون الـ using namespace
		// DataStructure::UploadCourse^ uploadForm = gcnew DataStructure::UploadCourse();
		// uploadForm->Show();
	}


	private: System::Void btnEditData_Click(System::Object^ sender, System::EventArgs^ e) {
		// أنشئ الـ form باستخدام handle (^) و gcnew
		EditStudentForm^ editForm = gcnew EditStudentForm();
		// لتفتحها كنافذة مستقلة
		editForm->Show();
		// أو لو حاببها نموذج حواري (Modal) يمنع التفاعل مع النافذة الأم حتى يُغلق:
		// editForm->ShowDialog();
	}


};
}

