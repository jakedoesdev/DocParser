#include <string>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <sstream>
#include "document.h"
#include "stopwords.h"
#include "porter_stemmer.h"
#include "tf-idf.h"
#include "user_query.h"

void Query::parse_query() {
  std::string word;
  std::string query;

  cout << "Enter a space-separated query\n";
  getline(std::cin, query);
  for(int i = 0; i < query.size(); i++) {
    if(ispunct(query[i])) {
      query.erase(i, 1);
      i--;
    }
  }
  WordList wordlist;
  wordlist.parse_words(query, 0);
  for(int i = 0; i < wordlist.get_wordlist_list()[0].size(); i++) {
    this->get_user_query().push_back(wordlist.get_wordlist_list()[0][i]);
  }
  Tfidf tfidf;
  tfidf.count_words(wordlist);
  for(int i = 0; i < tfidf.get_terms()[0].size(); i++) {
    this->get_query_terms().push_back(tfidf.get_terms()[0][i]);
  }
};  // parse_query

void Query::remove_stopwords(stopwords stop) {
  for(int i = 0; i < stop.getStopList().size(); i++) {
    for(int j = 0; j < this->get_user_query().size(); j++) {
      if(stop.getStopList()[i] == this->get_user_query()[j]) {
	this->get_user_query().erase(this->get_user_query().begin() + i);
	i--;
      }
    }
  }
};  // remove_stopwords

std::vector<std::string> Query::get_user_query() {
  return this->user_query;
};  // get_user_query

std::vector<Term> Query::get_query_terms() {
  return this->query_terms;
};
