#include <vector>
#include <string>
#include <windows.h>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include "screen.h"

using namespace std;

Screen::Screen()
{
	this->state = 0;
};

void Screen::LogicLoop()
{
	int displaySwitch = 1;

	while(1)
	{
		switch(this->state == 0)
		{
		case 0:
			this->OpenNotes();
			this->state = 1;
			break;
		case 2:
			displaySwitch =  this->DisplayMenu();
			switch(displaySwitch)
			{
			case 1: // new notes required, close current notes and create new notes.
				this->state = 0;
				break;
			case 2: // close program, exit screen
				return;
				break;
			default: //disaply corrosponding note
				this->DisplayNote(displaySwitch - 3);
				break;
			}
			break;
		}
		
	}
}

void Screen::Clear()
{
	this->UpdateWindowSize();
	//Spams newline to clear a screen.
	for (int i = 0; i<this->rows; i++)
	{
		cout << endl;
	}
}

void Screen::OpenNotes()
{
	string read = "";
	char c = ' ';
	int state = 0; // 0 = useless text, 1 = command, 2 = title, 3 = note.
	bool ignoreLine = true;
	Note* note = NULL;
	string noteTitle;
	string noteText;

	//find the notes file
	string filePath = "";
	filePath = GetFileName("Select Notes file");
	ifstream notesFile(filePath.c_str());

	if (!notesFile.good())
	{
		cout << "bad note file, failed to parse";
		return;
	}

	//Open notes file and being parsing
	while(c != EOF) // Loop until we run out of file
	{
		c = notesFile.get();
		if (c == '{')
		{
			state = 1;
			noteText = read;
			read = ""; // reset the read string
		}
		else if (c == '}') // End of command block, check command and react as neccessary
		{
			if (read == "end" )
			{
				note->SetInfo(noteTitle, noteText);
				notes.push_back(note);
				state = 0;
			}
			if (read == "split")
			{
				note->SetInfo(noteTitle, noteText);
				notes.push_back(note);
				note = new Note;
				state = 2;
			}
			if (read == "start")
			{
				note = new Note;
				state = 2;
			}
			read = ""; // reset the read string
		}
		else if (state == 2 && c == '\n') // set title and reset read.
		{
			if (ignoreLine)
			{
				ignoreLine = false;
			}
			else
			{
				noteTitle = read;
				read = "";
				ignoreLine = true;
				state = 3;
			}
		}
		else
		{
			read+=c; // append the new char to our read
		}
	}
	return;
}

string Screen::GetFileName( const string & prompt ) { 
    const int BUFSIZE = 1024;
    char buffer[BUFSIZE] = {0};
    OPENFILENAME ofns = {0};
    ofns.lStructSize = sizeof( ofns );
    ofns.lpstrFile = buffer;
    ofns.nMaxFile = BUFSIZE;
    ofns.lpstrTitle = prompt.c_str();
    GetOpenFileName( & ofns );
    return buffer;
}

int Screen::DisplayMenu()
{
	//clear space and generate the menu
	this->Clear();
	cout <<"Menu " << endl << endl;

	cout << "1) Open New Notes File" << endl;
	cout << "2) Exit" << endl << endl;

	cout << "Start splits at:" << endl;

	for (int i = 3; i < this->notes.size() + 3; i++)
	{
		cout << i << ")" << this->notes[i-3]->GetTitle() << endl; 
	}

	//get user input to find out what to do.
	do
	{
		string input;
		int inputInt;
		getline(cin, input);

		if (all_of(input.begin(), input.end(), ::isdigit))
		{
			inputInt = stoi(input);
			if (inputInt <= notes.size() +2)
			{
				return inputInt;
			}
		}
	}while(true);
}

void Screen::UpdateWindowSize()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    this->columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    this->rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    return;
}