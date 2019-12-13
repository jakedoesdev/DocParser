#include <string>
#include <iostream>
#include <algorithm>
#include "document.h"
#include "stopwords.h"
#include "porter_stemmer.h"
//#include "tf-idf.h"
//#include "user_query.h"
//#include "CosSim.h"

using namespace std;

document doc;
stopwords stop;
WordList wordlist;
//Query new_query;
//CosSim cosim;
//Tfidf tfidf;

int main()
{
	string collection;
	string stopFile;
//////////////////////////////// Cosine stuff
	vector<float> vec1;
	vector<vector<float>> vec2;
	vector<float> vec3;
	vector<float> vec4;

	float Vec1Total=0;
	float Vec2Total=0;

	float TempVec1=0;
	float TempVec2=0;

	float nominator=0;
	float denominator=0;
	float final=0;
///////////////////////////////
	cout << "Please enter the name of the collection file: ";
	cin >> collection;
	cin.ignore();
	
	cout << "Please enter the name of the stopwords file:";
	cin >> stopFile;
	cin.ignore();
	
	//collection = "cran5.txt";
	//stopFile = "stopwords.txt";
	
	if(doc.isDocument(collection)) {
		doc.processDoc(collection);
		//doc.processDoc("stemmerTester.txt");
		//doc.processDoc("cran1.txt");
		//doc.processDoc("cran5.txt");
		//doc.processDoc("cran10.txt");
		//doc.processDoc("cran25.txt");
		//doc.processDoc("cran100.txt");
	
		stop.processStops(stopFile);
		//stop.processStops("stopwords.txt");
		
		stop.docStop();
	
		vector<document*> docs = doc.getDocList();
		
		//replaces abstracts with abstracts with no stopwords
		vector <string> tmpAbstracts = stop.getCleanAbstracts();
		for (int i = 0; i < tmpAbstracts.size(); i++)
		{
			docs[i]->setAbstract(tmpAbstracts[i]);
		}
		for(int i = 0; i < docs.size(); i++) 
		{
			wordlist.parse_words(docs[i]->getAbstract(), i);
		}
		wordlist.print_stems(0);
        // for(int i = 0; i < wordlist.get_wordlist_list().size(); i++) {
		  // tfidf.count_words(wordlist);
		// }
		//parse_words(doc.docList[0]->abstract);
		
		//new_query.parse_query();

		// for(int x=0; x<vec2.size();x++)
		// {
			// cosim.Sum(vec1, TempVec1, Vec1Total);
			// cosim.Sum(vec2[x], TempVec2, Vec2Total);
			// cosim.Dot(vec1, vec2[x], nominator);//num
			// cosim.Dom(denominator, TempVec1, TempVec2);
			// final=nominator/denominator;
			// vec3.push_back(final);
			// cosim.Reset(Vec1Total,Vec2Total, TempVec1, TempVec2, nominator, denominator, final);
		// }

		// sort(vec3.begin(), vec3.end());
		// for(int x=vec3.size()-1;x>=0;x--)
		// {
			// cout<<"vec 3 "<<x<<" "<<vec3.at(x)<<endl;
		// }
		
		doc.cleanDocs();
		stop.cleanStops();
	}
	return 0;

}
