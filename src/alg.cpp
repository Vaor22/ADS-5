// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int getPriority(char op) {
  if (op == '+' || op == '-') return 1;
  if (op == '*' || op == '/') return 2;
  return 0;
}

bool isDigit(char ch) {
  return ch >= '0' && ch <= '9';
}

std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> stack;
  std::string postfix = "";

  for (size_t i = 0; i < inf.length(); i++) {
    char ch = inf[i];

    if (ch == ' ') continue;

    if (isDigit(ch)) {
      while (i < inf.length() && isDigit(inf[i])) {
        postfix += inf[i];
        i++;
      }
      postfix += ' ';
      i--;
    } else if (ch == '(') {
      stack.push(ch);
    } else if (ch == ')') {
      while (!stack.isEmpty() && stack.get() != '(') {
        postfix += stack.pop();
        postfix += ' ';
      }
      if (!stack.isEmpty() && stack.get() == '(') {
        stack.pop();
      }
    } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
      while (!stack.isEmpty() && stack.get() != '(' &&
             getPriority(stack.get()) >= getPriority(ch)) {
        postfix += stack.pop();
        postfix += ' ';
      }
      stack.push(ch);
    }
  }

  while (!stack.isEmpty()) {
    postfix += stack.pop();
    postfix += ' ';
  }

  if (!postfix.empty() && postfix.back() == ' ') {
    postfix.pop_back();
  }

  return postfix;
}

int eval(const std::string& post) {
  TStack<int, 100> stack;

  for (size_t i = 0; i < post.length(); i++) {
    char ch = post[i];

    if (ch == ' ') continue;

    if (isDigit(ch)) {
      int num = 0;
      while (i < post.length() && isDigit(post[i])) {
        num = num * 10 + (post[i] - '0');
        i++;
      }
      stack.push(num);
      i--;
    } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
      int val2 = stack.pop();
      int val1 = stack.pop();

      switch (ch) {
        case '+': stack.push(val1 + val2); break;
        case '-': stack.push(val1 - val2); break;
        case '*': stack.push(val1 * val2); break;
        case '/': stack.push(val1 / val2); break;
      }
    }
  }

  return stack.get();
}
