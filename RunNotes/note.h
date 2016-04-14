#ifndef NOTE
#define NOTE
#include <string>

class Note
{
	private:
		std::string title;
		std::string note;

	public:
		std::string GetNote();
		std::string GetTitle();
		int SetInfo(std::string title, std::string note);

};

#endif 