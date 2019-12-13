#ifndef USER_QUERY_H
#define USER_QUERY_H

#include <stdlib.h>
#include <stdio.h>
#include <string>

class Query {
 private:
  std::vector<std::string> user_query;
  std::vector<Term> query_terms;
 public:
  std::vector<std::string> get_user_query();
  std::vector<Term> get_query_terms();
  void parse_query();
  void remove_stopwords(stopwords stop);
};

#endif
