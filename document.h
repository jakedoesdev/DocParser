//#ifndef DOCUMENT_H_
//#define DOCUMENT_H_

#include <string>
#include <vector>

using namespace std;

class document {
	private:
		int ID;
		string title;
		string authors;
		string abstract;
		string rawText;
		vector <document*> docList;
	public:
		//document() {};
		void cleanDocs();
		void setID(int id);
		void setTitle(string title);
		void setAuthors(string author);
		void setAbstract(string abstract);
		int getID();
		string getTitle();
		string getAuthor();
		string getAbstract();
		vector<document*> getDocList();
		//void setDocList(document* doc, int i);
		void processDoc(string fileName);
		bool isDocument(string fileName);
};

//#endif  // DOCUMENT_H_
