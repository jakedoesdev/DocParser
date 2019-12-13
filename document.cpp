#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include "document.h"

using namespace std;

/*
processDoc function:
Parameter:  string fileName

This function opens and processes a text file based on 4 delimiting strings (".I", ".T", ".A", ".W")
Enters a loop until no more IDs are found to be processed
Creates a document object, tmpDoc, to hold data for each document 
A series of if statements finds the position of each mark and stores the associated data in tmpDoc.
Stores each tmpDoc in a vector, docList.
*/
bool document::isDocument(string fileName)
{
	bool isDocument;
	ifstream in;
	string raw;

	in.open(fileName);

	//if file is open, copy everything in it line by line to string raw
	if (in.is_open())
	{
		isDocument = true;
		getline(in, raw, '\0');
	}
	//exit program if file is not found
	else 
	{
		isDocument = false;
		cout << "Collection file not found, exiting." << endl;
		exit(0);
	}
	return isDocument;
}

void document::processDoc(string fileName)
{
	ifstream in;
	string title, authors, abstract, raw, editStr;
	string idMark = ".I", titleMark = ".T", authMark = ".A", absMark = ".W";
	int id, idPos, titlePos, authPos, absPos = 0;
	//int docCount = 1;
	document *tmpDoc;
	
	//open file
	in.open(fileName);
	
	//if file is open, copy everything in it line by line to string raw
	if (in.is_open())
	{
		getline(in, raw, '\0');
	}
	//exit program if file is not found
	else 
	{
		cout << "Collection file not found, exiting." << endl;
		exit(0);
	}

	//store raw text in a string to be edited
	editStr = raw;
	
	//replace newlines with spaces throughout string
	replace(editStr.begin(), editStr.end(), '\n', ' ');

	//loop runs while the idPos (position of next idMark) does not equal NULL/-1/npos
	do
	{
		
		//create new doc to store elements
		tmpDoc = new document;
		
		//store rawText in each object in case other team members need/want it for their functions
		tmpDoc->rawText = raw;
		
		/*find the position of the next idMark (".I"). if the position is not npos (i.e. if it exists), 
		erase up to the position of the ID number and convert that string to an int
		store resulting int in tmpDoc->ID.*/
		idPos = editStr.find(idMark);
		if (idPos != editStr.npos)
		{
			editStr.erase(idPos, editStr.find(' ') + 1);
			
			titlePos = editStr.find(titleMark);
			id = stoi(editStr.substr(0, titlePos - 1));
			tmpDoc->ID = id;		
		}
		
		//find pos of next titleMark (".T"). if that position exists, erase up to the title
		//store the title (a substring from 0 to titlePos + 3) in tmpDoc->title
		titlePos = editStr.find(titleMark);
		if (titlePos != editStr.npos)
		{
			editStr.erase(0, titlePos + 3);
			
			authPos = editStr.find(authMark);
			title = editStr.substr(0, authPos - 1);
			
			tmpDoc->title = title;		
		}
		
		//find pos of next authMark (".A"). if pos exists, erase up to the authors
		//store the author/s in tmpDoc->authors.
		authPos = editStr.find(authMark);
		if (authPos != editStr.npos)
		{
			editStr.erase(0, authPos + 3);
			
			absPos = editStr.find(absMark);
			authors = editStr.substr(0, absPos - 1);
			
			tmpDoc->authors = authors;
			
		}
		
		/*
		find pos of next absMark (".W"). if pos exists, erase up to the beginning of the abstract
		(will also erase the title found at beginning of abstract)
		find next idMark. 
		If none is found, the last ID has been processed (so the abstract runs from 0 to end of file)
		If another is found, more IDs need to be processed (so the abstract runs from 0 to the next idPos)
		Store abstract in tmpDoc->abstract
		*/
		absPos = editStr.find(absMark);
		if (absPos != editStr.npos)
		{
			editStr.erase(0, ((absPos + 2)+title.length() + 1));
					
			idPos = editStr.find(idMark);
			//case for last id already processed
			if (idPos == editStr.npos)
			{
				abstract = editStr.substr(0, editStr.npos);
			}
			//case for more ids to process
			else if (idPos != editStr.npos)
			{
				abstract = editStr.substr(0, idPos);
				editStr.erase(0, idPos);
			}
			
			tmpDoc->abstract = abstract;
		}
		
		//store tmpDoc in docList document vector
		docList.push_back(tmpDoc);
		//docCount++;

	} while (idPos != -1);  //while (idPos != editStr.npos);
	
	
	//output elements of first item in docList 
	cout << "ID: " << docList[0]->ID << " Title: " << docList[0]->title << endl
			 << "Authors: " << docList[0]->authors << endl << docList[0]->abstract << endl;
	
	//close file
	in.close();
	//delete tmpDoc;

}

vector <document*> document::getDocList()
{
	return docList;
}

void document::cleanDocs()
{
	for (auto it = docList.begin(); it != docList.end(); it++)
	{
		delete *it;
	}
	docList.clear();
}

// void document::setDocList(document* doc, int i)
// {
	// docList[i] = doc;
// }

void document::setID(int id)
{
	ID = id;
}

void document::setTitle(string ttl)
{
	title = ttl;
}

void document::setAuthors(string auth)
{
	authors = auth;
}

void document::setAbstract(string abs)
{
	abstract = abs;
}

int document::getID()
{
	return ID;
}

string document::getTitle()
{
	return title;
}

string document::getAuthor()
{
	return authors;
}

string document::getAbstract()
{
	return abstract;
}
