#ifndef SCREEN
#define SCREEN
#include "note.h"
#include <vector>
#include <string>

class Screen
{
private:
	int state; //0 = opening new notes, 1 =displaying menu,  2 = displaying notes 
	std::vector<Note*> notes;
	int rows; // stores number of rows in current console window
	int columns; // stores number of olumns in current console window.
	void LogicLoop();

	std::string GetFileName(const std::string & prompt);
	void Clear();
	void UpdateWindowSize();

public:
	Screen();
	void OpenNotes();
	int DisplayMenu();
	void DisplayNote(int split);
	void NextNote();
	void PreviousNote();
	void ReturntoMenu();
};
#endif