#pragma once

#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace System::IO;
using namespace System::Collections::Generic;

public ref class EditStudentForm : public Form {
public:
    EditStudentForm() {
        InitializeComponent();
        InitializeForm();
        LoadStudents();
    }

protected:
    ~EditStudentForm() {
        if (components) delete components;
    }

private:
    // Controls
    ListBox^ listBoxUsers;
    array<Label^>^ labels;
    array<TextBox^>^ textBoxes;
    Button^ btnSave;

    // Data
    Dictionary<String^, List<String^>^>^ students;
    List<String^>^ headers;

    System::ComponentModel::Container^ components;

    void InitializeComponent() {
        this->components = gcnew System::ComponentModel::Container();
        this->SuspendLayout();
        // 
        // EditStudentForm
        // 
     //   this->AutoScaleMode = AutoScaleMode::Font;
        this->ClientSize = Drawing::Size(600, 450);
        this->Name = L"EditStudentForm";
        this->Text = L"Edit Student Data";
        this->ResumeLayout(false);
    }

    void InitializeForm() {
        // Form appearance
        this->BackColor = Color::FromArgb(21, 52, 72);

        // Headers
        headers = gcnew List<String^>();
        headers->AddRange(gcnew array<String^>{
            "ID", "First Name", "Last Name", "Phone", "Username", "Password", "Email"
        });
        students = gcnew Dictionary<String^, List<String^>^>();

        // ListBox
        listBoxUsers = gcnew ListBox();
        listBoxUsers->Location = Point(10, 10);
        listBoxUsers->Size = Drawing::Size(200, 380);
        listBoxUsers->SelectedIndexChanged += gcnew EventHandler(this, &EditStudentForm::OnUserSelected);
        this->Controls->Add(listBoxUsers);

        // Labels + TextBoxes
        int count = headers->Count;
        labels = gcnew array<Label^>(count);
        textBoxes = gcnew array<TextBox^>(count);

        for (int i = 0; i < count; i++) {
            Label^ lbl = gcnew Label();
            lbl->Text = headers[i];
            lbl->ForeColor = Color::White;
            lbl->Location = Point(230, 20 + i * 45);
            lbl->Size = Drawing::Size(100, 25);
            this->Controls->Add(lbl);
            labels[i] = lbl;

            TextBox^ txt = gcnew TextBox();
            txt->Location = Point(340, 18 + i * 45);
            txt->Size = Drawing::Size(220, 28);
            this->Controls->Add(txt);
            textBoxes[i] = txt;
        }

        // Save button
        btnSave = gcnew Button();
        btnSave->Text = "Save";
        btnSave->Location = Point(340, 20 + count * 45);
       // btnSave->Size = Drawing::Size(100, thirty);
        btnSave->BackColor = Color::White;
        btnSave->ForeColor = Color::FromArgb(21, 52, 72);
        btnSave->FlatStyle = FlatStyle::Flat;
        btnSave->FlatAppearance->BorderColor = Color::White;
        btnSave->FlatAppearance->BorderSize = 2;
        btnSave->Click += gcnew EventHandler(this, &EditStudentForm::OnSaveClicked);
        this->Controls->Add(btnSave);
    }

    void LoadStudents() {
        std::ifstream infile("database.csv");
        std::string line;
        while (std::getline(infile, line)) {
            std::stringstream ss(line);
            std::vector<std::string> row;
            std::string field;
            while (std::getline(ss, field, ',')) row.push_back(field);
            if (row.size() == headers->Count) {
                String^ user = gcnew String(row[4].c_str());
                List<String^>^ data = gcnew List<String^>();
                for (auto& f : row) data->Add(gcnew String(f.c_str()));
                students[user] = data;
                listBoxUsers->Items->Add(user);
            }
        }
        infile.close();
    }

    void OnUserSelected(Object^, EventArgs^) {
        String^ user = safe_cast<String^>(listBoxUsers->SelectedItem);
        if (user == nullptr) return;
        List<String^>^ vals = students[user];
        for (int i = 0; i < vals->Count; i++)
            textBoxes[i]->Text = vals[i];
    }

    void OnSaveClicked(Object^, EventArgs^) {
        String^ sel = safe_cast<String^>(listBoxUsers->SelectedItem);
        if (sel == nullptr) return;

        // Collect updated data
        List<String^>^ updated = gcnew List<String^>();
        for each (TextBox ^ txt in textBoxes)
            updated->Add(txt->Text);
        students[sel] = updated;

        // Write back to CSV (overwrite)
        StreamWriter^ sw = gcnew StreamWriter("database.csv", false);
        for each (KeyValuePair<String^, List<String^>^> kv in students)
            sw->WriteLine(String::Join(",", kv.Value));
        sw->Close();

        MessageBox::Show("Student data updated successfully!",
            "Info", MessageBoxButtons::OK, MessageBoxIcon::Information);
    }
};
