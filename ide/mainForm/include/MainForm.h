#pragma once

#include <msclr/marshal_cppstd.h>
#include <cstdlib>
#include <fstream>

namespace IDE {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
    using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
            win1251 = System::Text::Encoding::GetEncoding(1251);
            utf8 = gcnew System::Text::UTF8Encoding(false, false);//System::Text::Encoding::UTF8;
            InitializeComponent();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
                delete utf8;
                delete win1251;
            }
		}

	private:
        System::Text::Encoding^ win1251;
        System::Text::Encoding^ utf8;
        msclr::interop::marshal_context context;
        System::String^ openedFileName;
        bool isNeedSave = false, isOpened = false;

    private: System::Windows::Forms::MenuStrip^ menuStrip2;
    private: System::Windows::Forms::ToolStripMenuItem^ fileToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^ openToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^ saveToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^ runToolStripMenuItem;
    private: System::Windows::Forms::RichTextBox^ richTextBox1;
    private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
    private: System::Windows::Forms::SaveFileDialog^ saveFileDialog1;
    private: System::ComponentModel::BackgroundWorker^ backgroundWorker1;
    private: System::Windows::Forms::RichTextBox^ richTextBox2;


        /// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
            this->menuStrip2 = (gcnew System::Windows::Forms::MenuStrip());
            this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->saveToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->runToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
            this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
            this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
            this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
            this->richTextBox2 = (gcnew System::Windows::Forms::RichTextBox());
            this->menuStrip2->SuspendLayout();
            this->SuspendLayout();
            // 
            // menuStrip2
            // 
            this->menuStrip2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
                | System::Windows::Forms::AnchorStyles::Right));
            this->menuStrip2->Dock = System::Windows::Forms::DockStyle::None;
            this->menuStrip2->GripMargin = System::Windows::Forms::Padding(2, 2, 0, 2);
            this->menuStrip2->ImageScalingSize = System::Drawing::Size(24, 24);
            this->menuStrip2->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
                this->fileToolStripMenuItem,
                    this->runToolStripMenuItem
            });
            this->menuStrip2->Location = System::Drawing::Point(0, 0);
            this->menuStrip2->Name = L"menuStrip2";
            this->menuStrip2->Size = System::Drawing::Size(121, 33);
            this->menuStrip2->TabIndex = 1;
            this->menuStrip2->Text = L"menuStrip2";
            // 
            // fileToolStripMenuItem
            // 
            this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
                this->openToolStripMenuItem,
                    this->saveToolStripMenuItem
            });
            this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
            this->fileToolStripMenuItem->Size = System::Drawing::Size(54, 29);
            this->fileToolStripMenuItem->Text = L"File";
            // 
            // openToolStripMenuItem
            // 
            this->openToolStripMenuItem->Name = L"openToolStripMenuItem";
            this->openToolStripMenuItem->Size = System::Drawing::Size(158, 34);
            this->openToolStripMenuItem->Text = L"Open";
            this->openToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::openToolStripMenuItem_Click);
            // 
            // saveToolStripMenuItem
            // 
            this->saveToolStripMenuItem->Name = L"saveToolStripMenuItem";
            this->saveToolStripMenuItem->Size = System::Drawing::Size(158, 34);
            this->saveToolStripMenuItem->Text = L"Save";
            this->saveToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::saveToolStripMenuItem_Click);
            // 
            // runToolStripMenuItem
            // 
            this->runToolStripMenuItem->Name = L"runToolStripMenuItem";
            this->runToolStripMenuItem->Size = System::Drawing::Size(59, 29);
            this->runToolStripMenuItem->Text = L"Run";
            this->runToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::runToolStripMenuItem_Click);
            // 
            // richTextBox1
            // 
            this->richTextBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
                | System::Windows::Forms::AnchorStyles::Left)
                | System::Windows::Forms::AnchorStyles::Right));
            this->richTextBox1->Font = (gcnew System::Drawing::Font(L"Cascadia Mono", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->richTextBox1->Location = System::Drawing::Point(0, 36);
            this->richTextBox1->Name = L"richTextBox1";
            this->richTextBox1->ShortcutsEnabled = false;
            this->richTextBox1->Size = System::Drawing::Size(1898, 814);
            this->richTextBox1->TabIndex = 2;
            this->richTextBox1->Text = L"";
            this->richTextBox1->WordWrap = false;
            this->richTextBox1->TextChanged += gcnew System::EventHandler(this, &MainForm::richTextBox1_TextChanged);
            // 
            // openFileDialog1
            // 
            this->openFileDialog1->FileName = L"openFileDialog1";
            // 
            // backgroundWorker1
            // 
            this->backgroundWorker1->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &MainForm::RunCode);
            // 
            // richTextBox2
            // 
            this->richTextBox2->Location = System::Drawing::Point(0, 856);
            this->richTextBox2->Name = L"richTextBox2";
            this->richTextBox2->Size = System::Drawing::Size(1898, 285);
            this->richTextBox2->TabIndex = 3;
            this->richTextBox2->Text = L"";
            // 
            // MainForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(1898, 1144);
            this->Controls->Add(this->richTextBox2);
            this->Controls->Add(this->richTextBox1);
            this->Controls->Add(this->menuStrip2);
            this->Name = L"MainForm";
            this->ShowIcon = false;
            this->ShowInTaskbar = false;
            this->Text = L"IDE";
            this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
            this->menuStrip2->ResumeLayout(false);
            this->menuStrip2->PerformLayout();
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion

private: System::Void openToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
    if (this->openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::Cancel)
        return;

    openedFileName = this->openFileDialog1->FileName;
    std::ifstream openedFile(context.marshal_as<std::string>(openedFileName));
    String^ text = gcnew String(std::string(std::istreambuf_iterator<char>(openedFile), {}).c_str());

    this->richTextBox1->Text = RuStr(text);
    isOpened = true;
    openedFile.close();
}

private: String^ RuStr(String^ str) {
    return utf8->GetString(win1251->GetBytes(str));
}

private: System::Void SaveCurrentFile() {
    if (isOpened && isNeedSave) {
        std::ofstream openedFile(context.marshal_as<std::string>(openedFileName));
        openedFile << context.marshal_as<std::string>(this->richTextBox1->Text);
        openedFile.close();
    }
}

private: System::Void Form1_Closing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e)
{
    SaveCurrentFile();
}
private: System::Void saveToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
    SaveCurrentFile();
}
private: System::Void runToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
    if (!this->backgroundWorker1->IsBusy && isOpened) {
        SaveCurrentFile();
        this->backgroundWorker1->RunWorkerAsync();
    }
}

private: System::Void richTextBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
    isNeedSave = true;
}

private: System::Void RunCode(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e) {
    this->richTextBox2->Text = "";
    System::String^ tmpFileName = time(NULL).ToString() + ".txt";
    std::string command = context.marshal_as<std::string>("..\\bin\\Pascal--.exe /f " + openedFileName + " >> " + tmpFileName + " || pause");
    system(command.c_str());
    //WinExec(command.c_str(), HIDE_WINDOW);

    std::ifstream openedFile(context.marshal_as<std::string>(tmpFileName));
    String^ text = gcnew String(std::string(std::istreambuf_iterator<char>(openedFile), {}).c_str());

    this->richTextBox2->Text = RuStr(text);
    openedFile.close();

    system(("rm " + context.marshal_as<std::string>(tmpFileName)).c_str());
    //WinExec(("rm " + context.marshal_as<std::string>(tmpFileName)).c_str(), HIDE_WINDOW);
}
};
}
