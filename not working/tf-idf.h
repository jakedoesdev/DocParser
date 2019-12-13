#ifndef TF_IDF_H_
#define TF_IDF_H_

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

struct Term {
  int term_freq;
  int doc_freq;
  std::string word;
  Term() {
    term_freq = 1;
    doc_freq = 1;
  }
};

class Tfidf {
 private:
	 std::vector<std::vector<Term>> terms;
 public:
  std::vector<std::vector<Term>>& get_terms();
  void count_words(WordList wordlist);
  void calc_tfidf();
  void print_tfidf();
};

#endif
