#ifndef VIEWGRADESFORM_H
#define VIEWGRADESFORM_H

#pragma once
#include <msclr/marshal_cppstd.h>

namespace CourseRegistration {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class ViewGradesForm : public System::Windows::Forms::Form
    {
    public:
        ViewGradesForm(void)
        {
            InitializeComponent();
        }

    protected:
        ~ViewGradesForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        System::ComponentModel::Container^ components;
        System::Windows::Forms::DataGridView^ dataGridViewGrades;
        System::Windows::Forms::Button^ btnLoadGrades;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->dataGridViewGrades = (gcnew System::Windows::Forms::DataGridView());
            this->btnLoadGrades = (gcnew System::Windows::Forms::Button());
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridViewGrades))->BeginInit();
            this->SuspendLayout();
            // 
            // dataGridViewGrades
            // 
            this->dataGridViewGrades->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
            this->dataGridViewGrades->Location = System::Drawing::Point(12, 12);
            this->dataGridViewGrades->Name = L"dataGridViewGrades";
            this->dataGridViewGrades->Size = System::Drawing::Size(560, 300);
            this->dataGridViewGrades->TabIndex = 0;
            // 
            // btnLoadGrades
            // 
            this->btnLoadGrades->Location = System::Drawing::Point(12, 318);
            this->btnLoadGrades->Name = L"btnLoadGrades";
            this->btnLoadGrades->Size = System::Drawing::Size(100, 30);
            this->btnLoadGrades->TabIndex = 1;
            this->btnLoadGrades->Text = L"Load Grades";
            this->btnLoadGrades->UseVisualStyleBackColor = true;
            this->btnLoadGrades->Click += gcnew System::EventHandler(this, &ViewGradesForm::btnLoadGrades_Click);
            // 
            // ViewGradesForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(584, 361);
            this->Controls->Add(this->btnLoadGrades);
            this->Controls->Add(this->dataGridViewGrades);
            this->Name = L"ViewGradesForm";
            this->Text = L"View Student Grades";
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridViewGrades))->EndInit();
            this->ResumeLayout(false);
        }
#pragma endregion

    private:
        System::Void btnLoadGrades_Click(System::Object^ sender, System::EventArgs^ e)
        {
            // Placeholder for loading grades (to be implemented)
            MessageBox::Show("Load Grades button clicked!", "Info");
        }
    };
}
#endif