#ifndef PORTERSTEMMER_H_
#define PORTERSTEMMER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>

class WordList {
 private:
  std::vector<std::vector<std::string>> wordlist_list;
 public:
  std::vector<std::vector<std::string>>& get_wordlist_list();
  void print_stems(int docnum);
  int get_num_unique_words(int docnum);

void parse_words(std::string, int docnum);

char* stem_word(const char* word);
int count_vc(char*, int cutoff);
bool has_vowel(char*, int cutoff);
bool has_double_consonant(char*, int cutoff, char exceptions[]);
bool has_cvc(char* word);

void step_1a(char* word);
void step_1b(char* temp_word);
void step_1c(char* stemmed_word_);
void step_2(char* stemmed_word_);
void step_3(char* stemmed_word_);
void step_4(char* stemmed_word_);
void step_5a(char* stemmed_word_);
void step_5b(char* stemmed_word_);


};  // class WordList

#endif  // PORTERSTEMMER_H_

