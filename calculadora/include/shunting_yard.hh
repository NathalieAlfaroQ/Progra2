#ifndef SHUNTING_YARD_HH
#define SHUNTING_YARD_HH

#include <queue>
#include <stack>
#include <tokenizer.hh>

class ShuntingYard
{
private:
  ITokenizer &tokenizer;

public:
  ShuntingYard(ITokenizer &tokenizer)
      : tokenizer(tokenizer)
  {
  }
  std::queue<Token *> ConvertirAPostfijo();
};
#endif