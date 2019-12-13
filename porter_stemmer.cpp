#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include "document.h"
#include "porter_stemmer.h"

const char vowel[] = {
   'a', 'e', 'i', 'o', 'u'
};
const int total_vowels = 5;
enum VowelTracker {
  TRUE,
  FALSE,
  VOID
};

void WordList::parse_words(std::string document, int docnum) {
  std::string word;
  std::stringstream abstract(document);
  std::vector<std::string> parsed_abstract;
  std::vector<std::string> temp_list;
  while(getline(abstract, word, ' ')) {
    parsed_abstract.push_back(word);
  }
  for(int i = 0; i < parsed_abstract.size(); i++){
    word = this->stem_word(parsed_abstract[i].c_str());
    temp_list.push_back(word);
  }
  this->get_wordlist_list().push_back(temp_list);
};  // parse_words

char* WordList::stem_word(const char* word) {
  char* temp_word = strdup(word);
  char* stemmed_word;

  this->step_1a(temp_word);
  this->step_1b(temp_word);
  this->step_1c(temp_word);
  this->step_2(temp_word);
  this->step_3(temp_word);
  this->step_4(temp_word);
  this->step_5a(temp_word);

  stemmed_word = temp_word;
  return stemmed_word; 
  free(temp_word);
};  // stem_word

int WordList::count_vc(char* word, int cutoff) {
  char curr_char;
  VowelTracker curr_vowel = VOID;
  VowelTracker prev_vowel = VOID;
  int num_vc = 0;

  for(int i = 0; i < strlen(word) - cutoff; i++) {
    curr_char = word[i];
    if(curr_char == 'y' || curr_char == 'Y') {
      if(prev_vowel == FALSE) {
	curr_vowel = TRUE;
      }
      else {
        curr_vowel = FALSE;
      }
    }
    else {
      for(int i = 0; i < total_vowels; i++) {
        if (curr_char == vowel[i]) {
          curr_vowel = TRUE;
	  break;
        }
        else {
          curr_vowel = FALSE;
        }
      }
    }
  if(prev_vowel == TRUE && curr_vowel == FALSE) {
    num_vc++;
  }
  prev_vowel = curr_vowel;
  }

  return num_vc;
};  // count_vc

bool WordList::has_vowel(char* temp_word, int cutoff) {
  bool has_vowel_ = false;
  VowelTracker prev_vowel = VOID;
  
  for(int i = 0; i < strlen(temp_word) - (cutoff + 1); i++) {
    for(int j = 0; j < total_vowels; j++) {
      if(temp_word[i] == 'y' && prev_vowel == FALSE) {
	has_vowel_ = true;
	break;
      }
      if(temp_word[i] == vowel[j]) {
        has_vowel_ = true;
	break;
      }
      else {
	prev_vowel = TRUE;
      }
    }
    if(has_vowel_ == true) {
      break;
    }
  }

  return has_vowel_;
};  // has_vowel

bool WordList::has_double_consonant(char* temp_word, int cutoff, char exceptions[]) {
  bool has_double_consonant_ = false;
  char* suffix = temp_word + strlen(temp_word);
  int exceptions_size = strlen(exceptions);

  if(*(suffix - 1) == *(suffix - 2)) {
    has_double_consonant_ = true;
    for(int i = 0; i < exceptions_size; i++) {
      if(*(suffix - 1) == exceptions[i]) {
	has_double_consonant_ = false;
	break;
      }
    }
    for(int i = 0; i < total_vowels; i++) {
      if(*(suffix - 1) == vowel[i]) {
	has_double_consonant_ = false;
	break;
      }
    } 
  }
  return has_double_consonant_;
};  // has_double_consonant

bool WordList::has_cvc(char* temp_word) {
  char* suffix = temp_word + strlen(temp_word);
  bool has_vc_ = false;
  bool has_cvc_ = false;

  if(strlen(temp_word) > 3 || (*(suffix - 1) == 'w' || *(suffix - 1) == 'x' || *(suffix - 1) == 'y')) {}
  else {
    if(this->count_vc(suffix - 2, 0) == 1) {
      has_vc_ = true;
      }
    if(has_vc_) {
      if(!this->has_vowel(suffix - 3, 2)) {
	has_cvc_ = true;
      }
    }
  }
  return has_cvc_;
};  // has_cvc

void WordList::step_1a(char* temp_word) {
  char* suffix = temp_word + strlen(temp_word);

  if(strcmp(suffix - 4, "sses") == 0) {
    strcpy(suffix - 4, "ss\0\0");
  }
  else if(strcmp(suffix - 3, "ies") == 0) {
    strcpy(suffix - 3, "i\0\0");
  }
  else if(strcmp(suffix - 2, "ss") == 0) {
  }
  else if(strcmp(suffix - 1, "s") == 0) {
    strcpy(suffix - 1, "\0");
  }
};  // step_1a

void WordList::step_1b(char* temp_word) {
  char* suffix = temp_word + strlen(temp_word);
  bool step_2_or_3_success = false;
  int word_length = strlen(temp_word);

  if(word_length > 3 && strcmp(suffix - 3, "eed") == 0) {
    if(this->count_vc(temp_word, 3) > 0) {  
      strcpy(suffix - 3, "ee\0");
    }
  }
  else if(word_length > 2 && this->has_vowel(temp_word, 2) && strcmp(suffix - 2, "ed") == 0) {
    strcpy(suffix - 2, "\0\0");
    step_2_or_3_success = true;
  }
  else if(word_length > 3 && this->has_vowel(temp_word, 3) && strcmp(suffix - 3, "ing") == 0) {
    strcpy(suffix - 3, "\0\0\0");
    step_2_or_3_success = true;
  }
  if(step_2_or_3_success) {
    suffix = temp_word + strlen(temp_word);
    char exceptions[3] = {'l','s','z'};

    if(strcmp(suffix - 2, "at") == 0) {
      strcpy(suffix - 2, "ate");
    }
    else if(strcmp(suffix - 2, "bl") == 0) {
      strcpy(suffix - 2, "ble");
    }
    else if(strcmp(suffix - 2, "iz") == 0) {
      strcpy(suffix - 2, "ize");
    }
    else if(this->has_double_consonant(temp_word, 0, exceptions)) {
      strcpy(suffix - 1, "\0");
    }
    else if(this->has_cvc(temp_word) && this->count_vc(temp_word, 0) == 1) {
      strcpy(suffix, "e");
    }
  }
};  // step_1b

void WordList::step_1c(char* temp_word) {
  char* suffix = temp_word + strlen(temp_word);

  if(this->has_vowel(temp_word, 1) && strcmp(suffix - 1, "y") == 0) {
    strcpy(suffix - 1, "i");
  }
};  // step_1c

void WordList::step_2(char* temp_word) {
  char* suffix = temp_word + strlen(temp_word);
  int word_length = strlen(temp_word);

  if(word_length > 3 && this->count_vc(temp_word, 0) > 0) {
    if(word_length > 7 && this->count_vc(temp_word, 7) > 0 && strcmp(suffix - 7, "ational") == 0) {
      strcpy(suffix - 7, "ate\0\0\0\0");
    }
    else if(word_length > 6 && this->count_vc(temp_word, 6) > 0 && strcmp(suffix - 6, "tional") == 0) {
      strcpy(suffix - 6, "tion\0\0");
    }
    else if(word_length > 4 && this->count_vc(temp_word, 4) > 0 && strcmp(suffix - 4, "enci") == 0) {
      strcpy(suffix - 4, "ence");
    }
    else if(word_length > 4 && this->count_vc(temp_word, 4) > 0 && strcmp(suffix - 4, "anci") == 0) {
      strcpy(suffix - 4, "ance");
    }
    else if(word_length > 4 && this->count_vc(temp_word, 4) > 0 && strcmp(suffix - 4, "izer") == 0) {
      strcpy(suffix - 4, "ize\0");
    }
    else if(word_length > 4 && this->count_vc(temp_word, 4) > 0 && strcmp(suffix - 4, "abli") == 0) {
      strcpy(suffix - 4, "able");
    }
    else if(word_length > 4 && this->count_vc(temp_word, 4) > 0 && strcmp(suffix - 4, "alli") == 0) {
      strcpy(suffix - 4, "al\0\0");
    }
    else if(word_length > 5 && this->count_vc(temp_word, 5) > 0 && strcmp(suffix - 5, "entli") == 0) {
      strcpy(suffix - 5, "ent\0\0");
    }
    else if(word_length > 3 && this->count_vc(temp_word, 3) > 0 && strcmp(suffix - 3, "eli") == 0) {
      strcpy(suffix - 3, "e\0\0");
    }
    else if(word_length > 5 && this->count_vc(temp_word, 5) > 0 && strcmp(suffix - 5, "ousli") == 0) {
      strcpy(suffix - 5, "ous\0\0");
    }
    else if(word_length > 7 && this->count_vc(temp_word, 7) > 0 && strcmp(suffix - 7, "ization") == 0) {
      strcpy(suffix - 7, "ize\0\0\0\0");
    }
    else if(word_length > 5 && this->count_vc(temp_word, 5) > 0 && strcmp(suffix - 5, "ation") == 0) {
      strcpy(suffix - 5, "ate\0\0");
    }
    else if(word_length > 4 && this->count_vc(temp_word, 4) > 0 && strcmp(suffix - 4, "ator") == 0) {
      strcpy(suffix - 4, "ate\0");
    }
    else if(word_length > 5 && this->count_vc(temp_word, 5) > 0 && strcmp(suffix - 5, "alism") == 0) {
      strcpy(suffix - 5, "al\0\0\0");
    }
    else if(word_length > 7 && this->count_vc(temp_word, 7) > 0 && strcmp(suffix - 7, "iveness") == 0) {
      strcpy(suffix - 7, "ive\0\0\0\0");
    }
    else if(word_length > 7 && this->count_vc(temp_word, 7) > 0 && strcmp(suffix - 7, "fulness") == 0) {
      strcpy(suffix - 7, "ful\0\0\0\0");
    }
    else if(word_length > 7 && this->count_vc(temp_word, 7) > 0 && strcmp(suffix - 7, "ousness") == 0) {
      strcpy(suffix - 7, "ous\0\0\0\0");
    }
    else if(word_length > 5 && this->count_vc(temp_word, 5) > 0 && strcmp(suffix - 5, "aliti") == 0) {
      strcpy(suffix - 5, "al\0\0\0");
    }
    else if(word_length > 5 && this->count_vc(temp_word, 5) > 0 && strcmp(suffix - 5, "iviti") == 0) {
      strcpy(suffix - 5, "ive\0\0");
    }
    else if(word_length > 6 && this->count_vc(temp_word, 6) > 0 && strcmp(suffix - 6, "biliti") == 0) {
      strcpy(suffix - 6, "ble\0\0\0");
    }
  }
};  // step_2

void WordList::step_3(char* temp_word) {
  int word_length = strlen(temp_word);
  char* suffix = temp_word + word_length;
  
  if(this->count_vc(temp_word, 0) > 0) {
    if(word_length > 5 && this->count_vc(temp_word, 5) > 0 && strcmp(suffix - 5, "icate") == 0) {
      strcpy(suffix - 5, "ic\0\0\0");
    }
    else if(word_length > 5 && this->count_vc(temp_word, 5) > 0 && strcmp(suffix - 5, "ative") == 0) {
      strcpy(suffix - 5, "\0\0\0\0\0");
    }
    else if(word_length > 5 && this->count_vc(temp_word, 5) > 0 && strcmp(suffix - 5, "alize") == 0) {
      strcpy(suffix - 5, "al\0\0\0");
    }
    else if(word_length > 5 && this->count_vc(temp_word, 5) > 0 && strcmp(suffix - 5, "iciti") == 0) {
      strcpy(suffix - 5, "ic\0\0\0");
    }
    else if(word_length > 4 && this->count_vc(temp_word, 4) > 0 && strcmp(suffix - 4, "ical") == 0) {
      strcpy(suffix - 4, "ic\0\0\0");
    }
    else if(word_length > 3 && this->count_vc(temp_word, 3) > 0 && strcmp(suffix - 3, "ful") == 0) {
      strcpy(suffix - 3, "\0\0\0");
    }
    else if(word_length > 4 && this->count_vc(temp_word, 4) > 0 && strcmp(suffix - 4, "ness") == 0) {
      strcpy(suffix - 4, "\0\0\0\0");
    }
  }
};  // step_3

void WordList::step_4(char* temp_word) {
  int word_length = strlen(temp_word);
  char* suffix = temp_word + word_length;

  if(this->count_vc(temp_word, 0) > 1) {
    if(word_length > 2 && this->count_vc(temp_word, 2) > 1 && strcmp(suffix - 2, "al") == 0) {
      strcpy(suffix - 2, "\0\0");
    }
    else if(word_length > 4 && this->count_vc(temp_word, 4) > 1 && strcmp(suffix - 4, "ance") == 0) {
      strcpy(suffix - 4, "\0\0\0\0");
    }
    else if(word_length > 4 && this->count_vc(temp_word, 4) > 1 && strcmp(suffix - 4, "ence") == 0) {
      strcpy(suffix - 4, "\0\0\0\0");
    }
    else if(word_length > 2 && this->count_vc(temp_word, 2) > 1 && strcmp(suffix - 2, "er") == 0) {
      strcpy(suffix - 2, "\0\0");
    }
    else if(word_length > 2 && this->count_vc(temp_word, 2) > 1 && strcmp(suffix - 2, "ic") == 0) {
      strcpy(suffix - 2, "\0\0");
    }
    else if(word_length > 4 && this->count_vc(temp_word, 4) > 1 && strcmp(suffix - 4, "able") == 0) {
      strcpy(suffix - 4, "\0\0\0\0");
    }
    else if(word_length > 4 && this->count_vc(temp_word, 4) > 1 && strcmp(suffix - 4, "ible") == 0) {
      strcpy(suffix - 4, "\0\0\0\0");
    }
    else if(word_length > 3 && this->count_vc(temp_word, 3) > 1 && strcmp(suffix - 3, "ant") == 0) {
      strcpy(suffix - 3, "\0\0\0");
    }
    else if(word_length > 5 && this->count_vc(temp_word, 5) > 1 && strcmp(suffix - 5, "ement") == 0) {
      strcpy(suffix - 5, "\0\0\0\0\0");
    }
    else if(word_length > 4 && this->count_vc(temp_word, 4) > 1 && strcmp(suffix - 4, "ment") == 0) {
      strcpy(suffix - 4, "\0\0\0\0");
    }
    else if(word_length > 3 && this->count_vc(temp_word, 3) > 1 && strcmp(suffix - 3, "ent") == 0) {
      strcpy(suffix - 3, "\0\0\0");
    }
    else if(word_length > 4 && this->count_vc(temp_word, 4) > 1 && (strcmp(suffix - 4, "tion") == 0) || (strcmp(suffix - 4, "sion") == 0)) {
      strcpy(suffix - 3, "\0\0\0");
    }
    else if(word_length > 2 && this->count_vc(temp_word, 2) > 1 && strcmp(suffix - 2, "ou") == 0) {
      strcpy(suffix - 2, "\0\0");
    }
    else if(word_length > 3 && this->count_vc(temp_word, 3) > 1 && strcmp(suffix - 3, "ism") == 0) {
      strcpy(suffix - 3, "\0\0\0");
    }
    else if(word_length > 3 && this->count_vc(temp_word, 3) > 1 && strcmp(suffix - 3, "ate") == 0) {
      strcpy(suffix - 3, "\0\0\0");
    }
    else if(word_length > 3 && this->count_vc(temp_word, 3) > 1 && strcmp(suffix - 3, "iti") == 0) {
      strcpy(suffix - 3, "\0\0\0");
    }
    else if(word_length > 3 && this->count_vc(temp_word, 3) > 1 && strcmp(suffix - 3, "ous") == 0) {
      strcpy(suffix - 3, "\0\0\0");
    }
    else if(word_length > 3 && this->count_vc(temp_word, 3) > 1 && strcmp(suffix - 3, "ive") == 0) {
      strcpy(suffix - 3, "\0\0\0");
    }
    else if(word_length > 3 && this->count_vc(temp_word, 3) > 1 && strcmp(suffix - 3, "ize") == 0) {
      strcpy(suffix - 3, "\0\0\0");
    }
  }
};  // step_4

void WordList::step_5a(char* temp_word) {
  int word_length = strlen(temp_word);
  char* suffix = temp_word + word_length;

  if(this->count_vc(temp_word, 0) > 0) {
    if(word_length > 2 && strcmp(suffix - 1, "e") == 0) {
      if(this->count_vc(temp_word, 1) > 1) { 
	strcpy(suffix - 1, "\0");
      }
    }
    else if(word_length > 2 && this->count_vc(temp_word, 1) == 1 && !this->has_cvc(temp_word) && strcmp(suffix - 1, "e") == 0) {
      strcpy(suffix - 1, "\0");
    }
  }
};  // step_5a

void WordList::step_5b(char* temp_word) {
  int word_length = strlen(temp_word);
  char* suffix = temp_word + word_length;
  char exceptions[1] = {'0'};

  if(word_length > 2 && this->count_vc(temp_word, 0) > 1 && strcmp(suffix - 1, "l") == 0 && this->has_double_consonant(temp_word, 0, exceptions)) {
    strcpy(suffix - 1, "\0");
  }
};  // step_5b

std::vector<std::vector<std::string>>& WordList::get_wordlist_list() {
  return this->wordlist_list;
};  // get_wordlist

void WordList::print_stems(int docnum) {
  for(int i = 0; i < this->get_wordlist_list()[docnum].size(); i++) {
    cout << get_wordlist_list()[docnum][i] << " ";
  }  
  cout << "\nNumber of unique stemmed words: " <<  this->get_num_unique_words(docnum) << "\n\n";
};  // print_stems

int WordList::get_num_unique_words(int docnum) {
  int count = this->get_wordlist_list()[docnum].size() - 1;
  std::vector<bool> dupe;
  for(int i = 0; i < count + 1; i++) {
    dupe.push_back(false);
  }

  if(count > 1) {
    for(int i = 0; i < this->get_wordlist_list()[docnum].size() - 1; i++) {
      for(int j = i + 1; j < this->get_wordlist_list()[docnum].size(); j++) {
	if(get_wordlist_list()[docnum][i] == get_wordlist_list()[docnum][j]) {
	  dupe[j] = true;
	}
      }
    }
    for(int i = 0; i < this->get_wordlist_list()[docnum].size(); i++) {
      if(dupe[i]) {
	count--;
      }
    }
    return count;
  }
  else {
    return 1;
  }
};  // get_num_unique_words


