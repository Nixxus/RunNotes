#include "note.h"

std::string Note::GetNote()
{
	return this->note;
}

int Note::SetInfo(std::string title, std::string note)
{
	//Check if the title or note are empty, if so return an error code
	if (title.empty()) return 1;
	if (note.empty()) return 2;

	//set info if all is well.
	this->title = title;
	this->note = note;
	

	return 0;

}