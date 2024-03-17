#include <algorithm>
#include <cassert>
#include <cctype>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

class BadExpression : exception {};

struct Operation {
  int priority;
  int isLeft;
};
enum TypeElem {
  Number,
  Plus,
  Minus,
  Multiplication,
  Division,
  Remainder,
  Exponentiation,
  And,
  Or,
  Not,
  BitwiseAnd,
  BitwiseOr,
  BitwiseNot,
  BitwiseLeftShift,
  BitwiseRightShift,
  Less,
  Greater,
  Equal,
  NotEqual,
  LessOrEqual,
  GreaterOrEqual,
  OpenBracket,
  CloseBracket,
  Assigment,
  AssigmentSum,
  AssigmentDiff
};

map<TypeElem, Operation> priorities = {{Plus, {4, 1}},
                                       {Minus, {4, 1}},
                                       {Multiplication, {3, 1}},
                                       {Division, {3, 1}},
                                       {Remainder, {3, 1}},
                                       {Exponentiation, {1, 1}},
                                       {And, {11, 1}},
                                       {Or, {12, 1}},
                                       {Not, {2, 0}},
                                       {BitwiseAnd, {8, 1}},
                                       {BitwiseOr, {10, 1}},
                                       {BitwiseNot, {2, 0}},
                                       {BitwiseLeftShift, {5, 1}},
                                       {BitwiseRightShift, {5, 1}},
                                       {Less, {6, 1}},
                                       {Greater, {6, 1}},
                                       {Equal, {7, 1}},
                                       {NotEqual, {7, 1}},
                                       {LessOrEqual, {6, 1}},
                                       {GreaterOrEqual, {6, 1}},
                                       {Assigment, {14, 0}},
                                       {AssigmentSum, {14, 0}},
                                       {AssigmentDiff, {14, 0}}};

vector<pair<string, TypeElem>> parse(string str) {
  vector<pair<string, TypeElem>> ans;
  int n = str.size();
  for (int i = 0; i < n; i++) {
    char ch = str[i];
    switch (ch) {
    case ' ':
      break;
    case '(':
      ans.push_back({{ch}, OpenBracket});
      break;
    case ')':
      ans.push_back({{ch}, CloseBracket});
      break;
    case '+': {
      i++;
      if (i >= n) {
        throw BadExpression();
      }
      char nextCh = str[i];
      switch (nextCh) {
      case '=':
        ans.push_back({{ch, nextCh}, AssigmentSum});
        break;
      default:
        ans.push_back({{ch}, Plus});
        i--;
      }
      break;
    }
    case '-': {
      i++;
      if (i >= n) {
        throw BadExpression();
      }
      char nextCh = str[i];
      switch (nextCh) {
      case '=':
        ans.push_back({{ch, nextCh}, AssigmentDiff});
        break;
      default:
        ans.push_back({{ch}, Minus});
        i--;
      }
      break;
    }
    case '*':
      ans.push_back({{ch}, Multiplication});
      break;
    case '/':
      ans.push_back({{ch}, Division});
      break;
    case '%':
      ans.push_back({{ch}, Remainder});
      break;
    case '^':
      ans.push_back({{ch}, Exponentiation});
      break;
    case '&': {
      i++;
      if (i >= n) {
        throw BadExpression();
      }
      char nextCh = str[i];
      switch (nextCh) {
      case '&':
        ans.push_back({{ch, nextCh}, And});
        break;
      default:
        ans.push_back({{ch}, BitwiseAnd});
        i--;
      }
      break;
    }
    case '|': {
      i++;
      if (i >= n) {
        throw BadExpression();
      }
      char nextCh = str[i];
      switch (nextCh) {
      case '|':
        ans.push_back({{ch, nextCh}, Or});
        break;
      default:
        ans.push_back({{ch}, BitwiseOr});
        i--;
      }
      break;
    }
    case '~':
      ans.push_back({{ch}, BitwiseNot});
      break;
    case '!': {
      i++;
      if (i >= n) {
        throw BadExpression();
      }
      char nextCh = str[i];
      switch (nextCh) {
      case '=':
        ans.push_back({{ch, nextCh}, NotEqual});
        break;
      default:
        ans.push_back({{ch}, Not});
        i--;
      }
      break;
    }
    case '<': {
      i++;
      if (i >= n) {
        throw BadExpression();
      }
      char nextCh = str[i];
      switch (nextCh) {
      case '<':
        ans.push_back({{ch, nextCh}, BitwiseLeftShift});
        break;
      case '=':
        ans.push_back({{ch, nextCh}, LessOrEqual});
        break;
      default:
        ans.push_back({{ch}, Less});
        i--;
      }
      break;
    }
    case '>': {
      i++;
      if (i >= n) {
        throw BadExpression();
      }
      char nextCh = str[i];
      switch (nextCh) {
      case '>':
        ans.push_back({{ch, nextCh}, BitwiseRightShift});
        break;
      case '=':
        ans.push_back({{ch, nextCh}, GreaterOrEqual});
        break;
      default:
        ans.push_back({{ch}, Greater});
        i--;
      }
      break;
    }
    case '=': {
      i++;
      if (i >= n) {
        throw BadExpression();
      }
      char nextCh = str[i];
      switch (nextCh) {
      case '=':
        ans.push_back({{ch, nextCh}, Equal});
        break;
      default:
        ans.push_back({{ch}, Assigment});
      }
      break;
    }
    default:
      string number = "";
      while (isdigit(str[i]) || isalpha(str[i])) {
        number += str[i];
        i++;
      }
      if (number.empty()) {
        throw BadExpression();
      }
      i--;
      ans.push_back({number, Number});
    }
  }
  return ans;
}

string toPostfix(string str) {
  vector<pair<string, TypeElem>> stack;
  string ans;
  vector<pair<string, TypeElem>> parsedStr = parse(str);
  for (int i = 0; i < parsedStr.size(); i++) {
    string elem = parsedStr[i].first;
    TypeElem elemType = parsedStr[i].second;
    switch (elemType) {
    case Number:
      ans += elem + " ";
      break;
    case OpenBracket:
      stack.push_back(parsedStr[i]);
      break;
    case CloseBracket: {
      if (stack.empty()) {
        throw BadExpression();
      }
      pair<string, TypeElem> op = stack.back();
      stack.pop_back();
      while (op.second != OpenBracket) {
        ans += op.first + " ";
        op = stack.back();
        stack.pop_back();
      }
      break;
    }
    default:
      if (!stack.empty()) {
        pair<string, TypeElem> op = stack.back();
        while (
            (op.second != OpenBracket) &&
            ((priorities[elemType].priority > priorities[op.second].priority) ||
             (priorities[elemType].priority == priorities[op.second].priority) &&
                 priorities[elemType].isLeft)) {
          ans += op.first + " ";
          stack.pop_back();
          if (stack.empty()) {
            break;
          }
          op = stack.back();
        }
      }
      stack.push_back(parsedStr[i]);
    }
  }
  while (!stack.empty()) {
    ans += stack.back().first + " ";
    stack.pop_back();
  }
  if (!ans.empty())
    ans.pop_back();
  return ans;
}

void test(string inp, string expect) {
  string out = toPostfix(inp);
  cout << out << "\n";
  assert(out == expect);
}

int main() {
  test("1 + 1 + 2", "1 1 + 2 +");
  test("15/(7-(1+1))", "15 7 1 1 + - /");
  test("!(0 && 2) + 4 / 2", "0 2 && ! 4 2 / +");
  test("14^4*(3+51)%2", "14 4 ^ 3 51 + * 2 %");
  test("0 || (!1) && (0 && (1 || 0 || (1 && 1)))",
       "0 1 ! 0 1 0 1 1 && || || && && ||");
  test("(54 != 50) && ((12 < 5) && (13 > 4))", "54 50 != 12 5 < 13 4 > && &&");
  test("1 + 1 - 2", "1 1 + 2 -");
  test("a = b += c", "a b c = +=");
  cout << "All tests passed!\n";
}
