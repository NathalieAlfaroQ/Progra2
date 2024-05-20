#ifndef TOKENIZER_HH
#define TOKENIZER_HH

#include <stdexcept>
#include <string>
#include <string_view>
#include <token.hh>

class ITokenizer
{
public:
  virtual bool HasNext() const = 0;
  virtual Token *Next() = 0;
  virtual ~ITokenizer() = default;
};

class Tokenizer : public ITokenizer
{
public:
  Tokenizer(const std::string &text);
  bool HasNext() const override;
  Token *Next() override;
  ~Tokenizer() override = default;

private:
  std::string text_;
  size_t position;
};

#endif
