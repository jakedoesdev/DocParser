#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include "document.h"
#include "porter_stemmer.h"
#include "tf-idf.h"

std::vector<std::vector<Term>>& Tfidf::get_terms() {
  return terms;
};  // get_terms

void Tfidf::count_words(WordList wordlist) {
  std::vector<std::vector<int>> count;
  std::vector<int> temp_count;
  std::vector<std::vector<std::string>> stems = wordlist.get_wordlist_list();
  for(int i = 0; i < stems.size(); i++) {
    for(int j = 0; j < stems[i].size(); j++) {
      temp_count.push_back(1);
    }
    count.push_back(temp_count);
  }
  for(int i = 0; i < wordlist.get_wordlist_list().size(); i++) {
    for(int j = 0; j < stems[i].size() - 1; j++) {
      for(int k = j + 1; k < stems[i].size(); k++) {
        if(stems[i][j] == stems[i][k]) {
	  count[i][j]++;
	  stems[i].erase(stems[i].begin() + k);
	  count[i].erase(count[i].begin() + k);
	}
      }
    }
    for(int j = 0; j < stems[i].size(); j++) {
      std::vector<Term> tfidf_list;
      Term* term = new Term;
      term->word = stems[i][j];
      term->term_freq = count[i][j];
      tfidf_list.push_back(*term);
      this->get_terms().push_back(tfidf_list);
    }
  }
  bool dupe;
  for(int i = 0; i < this->get_terms().size() - 1; i++) {
    for(int j = 0; j < this->get_terms()[i].size(); j++) {
      dupe = false;
      for(int k = 0; k < this->get_terms().size(); k++) {
	for(int l = 0; l < this->get_terms()[k].size(); l++) {
	  if(this->get_terms()[i][j].word == this->get_terms()[k][l].word) {
	    this->get_terms()[i][j].doc_freq++;
	    dupe = true;
	  }
	}
	if(dupe) {
	  break;
	}
      }
    }
  }
};  // count_words

void Tfidf::print_tfidf() {
  for(int i = 0; i < this->get_terms().size(); i++) {
    for(int j = 0; j < this->get_terms()[i].size(); j++) {
      cout << "Word: " << this->get_terms()[i][j].word << " Frequency: " << this->get_terms()[i][j].term_freq << " Doc Frequency: " << this->get_terms()[i][j].term_freq << endl;
    }
  }
}
