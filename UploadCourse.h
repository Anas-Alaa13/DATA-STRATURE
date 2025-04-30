#pragma once
#include <iostream>
#include <fstream>

using namespace System;
using namespace System::ComponentModel;
using namespace System::Windows::Forms;
using namespace System::IO;

namespace DataStructure {

    public ref class UploadCourse : public System::Windows::Forms::Form
    {
    public:
        UploadCourse(void)
        {
            InitializeComponent();
        }

    protected:
        ~UploadCourse()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        System::Windows::Forms::TextBox^ title;
        System::Windows::Forms::Label^ titleLabel;
        System::Windows::Forms::TextBox^ syllabus;
        System::Windows::Forms::TextBox^ instructor;
        System::Windows::Forms::TextBox^ hours;
        System::Windows::Forms::Label^ syllabusLabel;
        System::Windows::Forms::Label^ instructorLabel;
        System::Windows::Forms::Label^ hoursLabel;
        System::Windows::Forms::Button^ submitButton;

        System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->title = (gcnew System::Windows::Forms::TextBox());
            this->titleLabel = (gcnew System::Windows::Forms::Label());
            this->syllabus = (gcnew System::Windows::Forms::TextBox());
            this->instructor = (gcnew System::Windows::Forms::TextBox());
            this->hours = (gcnew System::Windows::Forms::TextBox());
            this->syllabusLabel = (gcnew System::Windows::Forms::Label());
            this->instructorLabel = (gcnew System::Windows::Forms::Label());
            this->hoursLabel = (gcnew System::Windows::Forms::Label());
            this->submitButton = (gcnew System::Windows::Forms::Button());
            this->SuspendLayout();
            // 
            // title
            // 
            this->title->Location = System::Drawing::Point(140, 40);
            this->title->Name = L"title";
            this->title->Size = System::Drawing::Size(200, 22);
            this->title->TabIndex = 0;
            // 
            // titleLabel
            // 
            this->titleLabel->AutoSize = true;
            this->titleLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
            this->titleLabel->Location = System::Drawing::Point(50, 40);
            this->titleLabel->Name = L"titleLabel";
            this->titleLabel->Size = System::Drawing::Size(55, 25);
            this->titleLabel->TabIndex = 1;
            this->titleLabel->Text = L"Title:";
            // 
            // syllabus
            // 
            this->syllabus->Location = System::Drawing::Point(140, 80);
            this->syllabus->Name = L"syllabus";
            this->syllabus->Size = System::Drawing::Size(200, 22);
            this->syllabus->TabIndex = 2;
            // 
            // instructor
            // 
            this->instructor->Location = System::Drawing::Point(140, 160);
            this->instructor->Name = L"instructor";
            this->instructor->Size = System::Drawing::Size(200, 22);
            this->instructor->TabIndex = 6;
            // 
            // hours
            // 
            this->hours->Location = System::Drawing::Point(140, 120);
            this->hours->Name = L"hours";
            this->hours->Size = System::Drawing::Size(200, 22);
            this->hours->TabIndex = 4;
            // 
            // syllabusLabel
            // 
            this->syllabusLabel->AutoSize = true;
            this->syllabusLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
            this->syllabusLabel->Location = System::Drawing::Point(50, 80);
            this->syllabusLabel->Name = L"syllabusLabel";
            this->syllabusLabel->Size = System::Drawing::Size(93, 25);
            this->syllabusLabel->TabIndex = 3;
            this->syllabusLabel->Text = L"Syllabus:";
            // 
            // instructorLabel
            // 
            this->instructorLabel->AutoSize = true;
            this->instructorLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
            this->instructorLabel->Location = System::Drawing::Point(50, 160);
            this->instructorLabel->Name = L"instructorLabel";
            this->instructorLabel->Size = System::Drawing::Size(98, 25);
            this->instructorLabel->TabIndex = 7;
            this->instructorLabel->Text = L"Instructor:";
            // 
            // hoursLabel
            // 
            this->hoursLabel->AutoSize = true;
            this->hoursLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
            this->hoursLabel->Location = System::Drawing::Point(50, 120);
            this->hoursLabel->Name = L"hoursLabel";
            this->hoursLabel->Size = System::Drawing::Size(70, 25);
            this->hoursLabel->TabIndex = 5;
            this->hoursLabel->Text = L"Hours:";
            // 
            // submitButton
            // 
            this->submitButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold));
            this->submitButton->Location = System::Drawing::Point(140, 200);
            this->submitButton->Name = L"submitButton";
            this->submitButton->Size = System::Drawing::Size(100, 30);
            this->submitButton->TabIndex = 8;
            this->submitButton->Text = L"Submit";
            this->submitButton->UseVisualStyleBackColor = true;
            this->submitButton->Click += gcnew System::EventHandler(this, &UploadCourse::submitButton_Click);
            // 
            // UploadCourse
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(21)), static_cast<System::Int32>(static_cast<System::Byte>(52)),
                static_cast<System::Int32>(static_cast<System::Byte>(72)));
            this->ClientSize = System::Drawing::Size(400, 300);
            this->Controls->Add(this->submitButton);
            this->Controls->Add(this->instructorLabel);
            this->Controls->Add(this->instructor);
            this->Controls->Add(this->hoursLabel);
            this->Controls->Add(this->hours);
            this->Controls->Add(this->syllabusLabel);
            this->Controls->Add(this->syllabus);
            this->Controls->Add(this->titleLabel);
            this->Controls->Add(this->title);
            this->Name = L"UploadCourse";
            this->Text = L"Upload Course";
            this->Load += gcnew System::EventHandler(this, &UploadCourse::UploadCourse_Load);
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion

        void submitButton_Click(System::Object^ sender, System::EventArgs^ e)
        {
            String^ title1 = title->Text;
            String^ syllabus1 = syllabus->Text;
            String^ hours1 = hours->Text;
            String^ instructor1 = instructor->Text;

            String^ csvLine = String::Format("{0},{1},{2},{3}", title1, syllabus1, hours1, instructor1);
            String^ filePath = "courses.csv";

            try
            {
                System::IO::StreamWriter^ sw = gcnew System::IO::StreamWriter(filePath, true);
                sw->WriteLine(csvLine);
                sw->Close();

                MessageBox::Show("Successfully saved", "", MessageBoxButtons::OK, MessageBoxIcon::Information);
            }
            catch (Exception^ ex)
            {
                MessageBox::Show("Error: " + ex->Message);
            }
        }
    private: System::Void UploadCourse_Load(System::Object^ sender, System::EventArgs^ e) {
    }
};
}
