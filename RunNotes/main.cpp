#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>
#include "note.h"

using namespace std;

vector<Note*> LoadNotes();
string GetFileName( const string & prompt );

int main()
{
	vector<Note*> notes;

	//Select note to load and parse the txt file
	notes = LoadNotes();

	//Return an error if this fails (LoadNotes will go into more detail)
	if (notes.empty())
	{
		std::cout << "Something went wrong parsing your notes, please double check them and reload the program. If this continues, get in touch with Nixxus on github with a copy of your notes. \n";
		system("pause");
	}
	//Proceed to split selection if this succeeds

	//Show notes and prep for the run

	//Handle inputs during the run

	return 0;
}

vector<Note*> LoadNotes()
{
	vector<Note*> notes;

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

	return notes;
}

string GetFileName( const string & prompt ) { 
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