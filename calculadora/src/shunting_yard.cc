#include <shunting_yard.hh>

std::queue<Token *> ShuntingYard::ConvertirAPostfijo()
{
  std::queue<Token *> outputQueue;
  std::stack<TokenOperador *> operatorStack;

  Token *token;
  while (tokenizer.HasNext())
  {
    token = tokenizer.Next();

    if (token->IsNumber())
    {
      outputQueue.push(token);
    }
    else if (token->IsOperator())
    {
      TokenOperador *operador = static_cast<TokenOperador *>(token);

      if (operador->IsLeftParenthesis())
      {
        operatorStack.push(operador);
      }
      else if (operador->IsRightParenthesis())
      {
        while (!operatorStack.empty() && !operatorStack.top()->IsLeftParenthesis())
        {
          outputQueue.push(operatorStack.top());
          operatorStack.pop();
        }
        if (!operatorStack.empty() && operatorStack.top()->IsLeftParenthesis())
        {
          operatorStack.pop();
        }
        else
        {
          throw std::runtime_error("Problema con los paréntesis");
        }
      }
      else
      {
        while (!operatorStack.empty() && operatorStack.top()->IsOperator() && operatorStack.top()->GetPrecedence() >= operador->GetPrecedence())
        {
          outputQueue.push(operatorStack.top());
          operatorStack.pop();
        }
        operatorStack.push(operador);
      }
    }
  }

  while (!operatorStack.empty())
  {
    if (operatorStack.top()->IsRightParenthesis())
    {
      throw std::runtime_error("Problema con los paréntesis");
    }
    outputQueue.push(operatorStack.top());
    operatorStack.pop();
  }

  return outputQueue;
}