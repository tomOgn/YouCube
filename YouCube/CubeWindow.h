#pragma once

namespace YouCube
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	void start(int argc, char *argv[]);

	public ref class CubeWindow : public System::Windows::Forms::Form
	{
	public:
		CubeWindow(int argc, char *argv[])
		{
			InitializeComponent();
			start(argc, argv);
		}

	protected:
		~CubeWindow()
		{
			if (components) delete components;
		}
	private: System::Windows::Forms::ColorDialog^  colorDialog1;
	protected:

	private:
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated codery>
		void InitializeComponent(void)
		{
			this->colorDialog1 = (gcnew System::Windows::Forms::ColorDialog());
			this->SuspendLayout();
			// 
			// CubeWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(282, 255);
			this->Name = L"CubeWindow";
			this->Text = L"You Cube";
			this->ResumeLayout(false);

		}
#pragma endregion
	};
}