#pragma once
#include "Globals.h"
#include "YouCube.h"
#include <GL/glut.h>

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

void ChangeColor(int face, Color color);

namespace YouCube
{
	public ref class ColorsPicker : public System::Windows::Forms::Form
	{
	public:
		ColorsPicker(void)
		{
			InitializeComponent();
		}

	protected:
		~ColorsPicker()
		{
			if (components) delete components;
		}
	private: System::Windows::Forms::Button^  buttonColor1;
	private: System::Windows::Forms::ColorDialog^  colorDialog;
	private: System::Windows::Forms::Button^  buttonColor2;
	private: System::Windows::Forms::Button^  buttonColor3;
	private: System::Windows::Forms::Button^  buttonColor4;
	private: System::Windows::Forms::Button^  buttonColor5;
	private: System::Windows::Forms::Button^  buttonColor6;
	protected:

	private:
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->buttonColor1 = (gcnew System::Windows::Forms::Button());
			this->colorDialog = (gcnew System::Windows::Forms::ColorDialog());
			this->buttonColor2 = (gcnew System::Windows::Forms::Button());
			this->buttonColor3 = (gcnew System::Windows::Forms::Button());
			this->buttonColor4 = (gcnew System::Windows::Forms::Button());
			this->buttonColor5 = (gcnew System::Windows::Forms::Button());
			this->buttonColor6 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// buttonColor1
			// 
			this->buttonColor1->Location = System::Drawing::Point(12, 12);
			this->buttonColor1->Name = L"buttonColor1";
			this->buttonColor1->Size = System::Drawing::Size(285, 48);
			this->buttonColor1->TabIndex = 0;
			this->buttonColor1->Text = L"Color 1";
			this->buttonColor1->UseVisualStyleBackColor = true;
			this->buttonColor1->Click += gcnew System::EventHandler(this, &ColorsPicker::buttonColor1_Click);
			this->buttonColor1->BackColor = Color::FromArgb(
				TheCube->Colors[0][0] * 255, 
				TheCube->Colors[0][1] * 255, 
				TheCube->Colors[0][2] * 255);

			// 
			// buttonColor2
			// 
			this->buttonColor2->Location = System::Drawing::Point(12, 66);
			this->buttonColor2->Name = L"buttonColor2";
			this->buttonColor2->Size = System::Drawing::Size(285, 48);
			this->buttonColor2->TabIndex = 1;
			this->buttonColor2->Text = L"Color 2";
			this->buttonColor2->UseVisualStyleBackColor = true;
			this->buttonColor2->Click += gcnew System::EventHandler(this, &ColorsPicker::buttonColor2_Click);
			this->buttonColor2->BackColor = Color::FromArgb(
				TheCube->Colors[1][0] * 255,
				TheCube->Colors[1][1] * 255,
				TheCube->Colors[1][2] * 255);
			// 
			// buttonColor3
			// 
			this->buttonColor3->Location = System::Drawing::Point(12, 120);
			this->buttonColor3->Name = L"buttonColor3";
			this->buttonColor3->Size = System::Drawing::Size(285, 48);
			this->buttonColor3->TabIndex = 2;
			this->buttonColor3->Text = L"Color 3";
			this->buttonColor3->UseVisualStyleBackColor = true;
			this->buttonColor3->Click += gcnew System::EventHandler(this, &ColorsPicker::buttonColor3_Click);
			this->buttonColor3->BackColor = Color::FromArgb(
				TheCube->Colors[2][0] * 255,
				TheCube->Colors[2][1] * 255,
				TheCube->Colors[2][2] * 255);
			// 
			// buttonColor4
			// 
			this->buttonColor4->Location = System::Drawing::Point(12, 174);
			this->buttonColor4->Name = L"buttonColor4";
			this->buttonColor4->Size = System::Drawing::Size(285, 48);
			this->buttonColor4->TabIndex = 3;
			this->buttonColor4->Text = L"Color 4";
			this->buttonColor4->UseVisualStyleBackColor = true;
			this->buttonColor4->Click += gcnew System::EventHandler(this, &ColorsPicker::buttonColor4_Click);
			this->buttonColor4->BackColor = Color::FromArgb(
				TheCube->Colors[3][0] * 255,
				TheCube->Colors[3][1] * 255,
				TheCube->Colors[3][2] * 255);
			// 
			// buttonColor5
			// 
			this->buttonColor5->Location = System::Drawing::Point(12, 228);
			this->buttonColor5->Name = L"buttonColor5";
			this->buttonColor5->Size = System::Drawing::Size(285, 48);
			this->buttonColor5->TabIndex = 4;
			this->buttonColor5->Text = L"Color 5";
			this->buttonColor5->UseVisualStyleBackColor = true;
			this->buttonColor5->Click += gcnew System::EventHandler(this, &ColorsPicker::buttonColor5_Click);
			this->buttonColor5->BackColor = Color::FromArgb(
				TheCube->Colors[4][0] * 255,
				TheCube->Colors[4][1] * 255,
				TheCube->Colors[4][2] * 255);
			// 
			// buttonColor6
			// 
			this->buttonColor6->Location = System::Drawing::Point(12, 282);
			this->buttonColor6->Name = L"buttonColor6";
			this->buttonColor6->Size = System::Drawing::Size(285, 48);
			this->buttonColor6->TabIndex = 5;
			this->buttonColor6->Text = L"Color 6";
			this->buttonColor6->UseVisualStyleBackColor = true;
			this->buttonColor6->Click += gcnew System::EventHandler(this, &ColorsPicker::buttonColor6_Click);
			this->buttonColor6->BackColor = Color::FromArgb(
				TheCube->Colors[5][0] * 255,
				TheCube->Colors[5][1] * 255,
				TheCube->Colors[5][2] * 255);
			// 
			// ColorsPicker
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(315, 342);
			this->Controls->Add(this->buttonColor6);
			this->Controls->Add(this->buttonColor5);
			this->Controls->Add(this->buttonColor4);
			this->Controls->Add(this->buttonColor3);
			this->Controls->Add(this->buttonColor2);
			this->Controls->Add(this->buttonColor1);
			this->Name = L"ColorsPicker";
			this->Text = L"ColorsPicker";
			this->ResumeLayout(false);

		}
#pragma endregion

		private: System::Void buttonColor1_Click(System::Object^ sender, System::EventArgs^ e)
		{
			colorDialog->ShowDialog();
			buttonColor1->BackColor = colorDialog->Color;
			ChangeColor(0, colorDialog->Color);
		}
		private: System::Void buttonColor2_Click(System::Object^ sender, System::EventArgs^ e)
		{
			colorDialog->ShowDialog();
			buttonColor2->BackColor = colorDialog->Color;
			ChangeColor(1, colorDialog->Color);
		}
		private: System::Void buttonColor3_Click(System::Object^ sender, System::EventArgs^ e)
		{
			colorDialog->ShowDialog();
			buttonColor3->BackColor = colorDialog->Color;
			ChangeColor(2, colorDialog->Color);
		}
		private: System::Void buttonColor4_Click(System::Object^ sender, System::EventArgs^ e)
		{
			colorDialog->ShowDialog();
			buttonColor4->BackColor = colorDialog->Color;
			ChangeColor(3, colorDialog->Color);
		}
		private: System::Void buttonColor5_Click(System::Object^ sender, System::EventArgs^ e)
		{
			colorDialog->ShowDialog();
			buttonColor5->BackColor = colorDialog->Color;
			ChangeColor(4, colorDialog->Color);
		}
		private: System::Void buttonColor6_Click(System::Object^ sender, System::EventArgs^ e)
		{
			colorDialog->ShowDialog();
			buttonColor6->BackColor = colorDialog->Color;
			ChangeColor(5, colorDialog->Color);
		}
	};
}