//#ifndef STOPWORDS_H_
//#define STOPWORDS_H_

#include <string>
#include <vector>

using namespace std;

class stopwords {
	private:
		vector <string> stopList;
		int count;
		vector <document*> noStopDocs;
		vector <string> cleanAbstract;
	public:
		//stopwords() {};
		void cleanStops();
		void setCount(int c);
		int getCount();
		void processStops(string fileName);
		void docStop();
		vector <string> getCleanAbstracts();
		bool isStopWord(string s);
		vector <string> getStopList();
		//string getCleanAbstractAt(int i);
		//void setCleanAbstract(string s);
		//string getStopAbstract();
		//void setStopAbstract(string s, int i);
};

//#endif  // STOPWORDS_H_
