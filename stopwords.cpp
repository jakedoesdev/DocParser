#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <string.h>
#include "document.h"
#include "stopwords.h"

//vector <string> stopList;
extern document doc;

//clears stopList vector of pointers
void stopwords::cleanStops()
{
	stopList.clear();
}

/*
processStops function:
Parameter:  string fileName

This function opens, reads, and stores a file of newline delimited stopwords in a vector called stopList.
While end of file has not been reached, each word is push_backed onto the vector and counted. Once complete, the count is added to stopwords 
and output using GetCount(). 
*/
void stopwords::processStops(string fileName)
{
	fstream in;
	int count = 0;
	string tmpWord;
	stopwords *tmpStop;
	
	//open file
	in.open(fileName);
	
	tmpStop = new stopwords;
	
	//if file is open, store each word/letter as a separate vector element of stopList
	if (in.is_open())
	{
		while (in >> tmpWord)
		{
			//cout << tmpWord << endl;
			count++;
			stopList.push_back(tmpWord);
		}
		
		tmpStop->setCount(count);
		
	}
	//exit program if file is not found 
	else
	{
		cout << "Stopwords file not found, exiting." << endl;
		exit(0);
	}
	
	// for (auto it = stopList.begin(); it != stopList.end(); it++)
	// {
		// cout << *it << endl;
	// }
	
	cout << endl << "There are currently " << tmpStop->getCount() << " known stopwords." << endl << endl;
	
	//stopList.push_back(".")
	//stop.updateStop();
	
	in.close();
	//delete [] tmpStop;
	
}

/*
docStop function:
Parameter:  None

This function removes stopwords and punctuation from the abstract of the first document read in. The "cleaned" abstracts are each stored in 
a vector (cleanAbs), with the first cleaned abstract stored at cleanAbs[0].
Once all abstracts have been processed, the function loops through cleanAbs and counts all spaces, using that number + 1 (to account for last word) 
as the number of unique unstemmed words in the abstract.
*/
void stopwords::docStop()
{
	string abst;
	vector <string> cleanAbs;
	stopwords stop;
	int wordCnt = 0;
	
	noStopDocs = doc.getDocList();
	
	//store each cleaned abst in its own element
	for (int i = 0; i < noStopDocs.size(); i++)
	{
		abst = noStopDocs[i]->getAbstract();
		
		stringstream absStream(abst);
		string tmp;
		string cleaned;
		for (int j = 0; absStream >> tmp; j++)
		{
			if (!(isStopWord(tmp)))
			{
					if (tmp.back() != ',' && tmp.back() != '/' && tmp.back() != ')')
					{
						cleaned += (tmp + " ");
					}
					else
					{	
						if (tmp.front() != '(') // && //tmp.front != '\\')
						{
							cleaned += (tmp + " ");
						}
						else
						{
							tmp = tmp.erase(0, 1);
							cleaned += (tmp + " ");
						}
						
					}
			}
		}
		//cleanAbstract.push_back(cleaned);
		cleanAbs.push_back(cleaned);
	}
	
	//hacky last-minute fix to actually store abstracts rather than temp store them, and to allow teammate access to 
	//cleaned abstracts for porter stemmmer
	for (int i = 0; i < cleanAbs.size(); i++)
	{
		cleanAbstract.push_back(cleanAbs[i]);
		//stop.setCleanAbstract(cleanAbs[i]);
	}
	
	//cout << "docStop cleanAbstract.size: " << cleanAbstract.size() << endl;
	
	//cout << stop.getCleanAbstractAt(0);
	
	// for (int i = 0; i < cleanAbs.size(); i++)
	// {
		// cout << "get clean Abstract: " << stop.getCleanAbstractAt(i) << endl;
	// }
	

	cout << cleanAbs[0] << endl;
	//cout << cleanAbstract[0] << endl;
	
	for (int i = 0; i < cleanAbs[0].length(); i++)
	{	
		if (cleanAbs[0][i] == ' ')
		{
			wordCnt++;
		}
	}
	
	//wordCnt = count(cleanAbs[0].begin(), cleanAbs[0].end, ' ');

	
	cout << "Number of unique unstemmed words: " << wordCnt << endl << endl;
}
	
/*
Given a string, determine if that string is in the list of stopwords. Return true if yes, false if no.
*/
bool stopwords::isStopWord(string s)
{
	stringstream ss(s);
	int i;
	
	for (int i = 0; i < stopList.size(); i++)
	{
		if (stopList[i] == s)
		{
			return true;
		}
		else if (s == ".")
		{
			return true;
		}
		else if (!((ss >> i).fail()))
		{
			return true;
		}
	}
	return false;
}

vector <string> stopwords::getCleanAbstracts()
{
	return cleanAbstract;
}


// string stopwords::getCleanAbstractAt(int i)
// {
	// //cout << "cleanAbstract.size: " << cleanAbstract.size() << endl;
	
	// cout << "getting" << endl;
	// return cleanAbstract.at(i);
	// cout << "got" << endl;
// }

// void stopwords::setCleanAbstract(string s)
// {
	// //cout << "setting" << endl;
	// //cout << s << endl;
	// cleanAbstract.push_back(s);
	// //cout << "set" << endl;
	// //cout << cleanAbstract.size() << endl;
// }

vector <string> stopwords::getStopList()
{
	return stopList;
}

void stopwords::setCount(int c)
{
	count = c;
}

int stopwords::getCount()
{
	return count;
}


