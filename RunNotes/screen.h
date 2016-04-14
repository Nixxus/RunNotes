#ifndef SCREEN
#define SCREEN
#include "note.h"

class Screen
{
private:
	int state; //0 = menu, 1 = displaying notes 
	vector<Note*> notes;
	string GetFileName(const string & prompt);

public:
	Screen();
	void OpenNotes();
	void DisplayMenu();
	void DisplayNote(int split);
	void NextNote();
	void PreviousNote();
	void ReturntoMenu();
};
#endif