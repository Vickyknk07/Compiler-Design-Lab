/******************************************************     
Author       : Vicky Kumar Nayak
Created      : 2023-10-19
Filename     : 20075096_Assignment6.cpp
******************************************************/
#include <bits/stdc++.h>
using namespace std;

unordered_map<int, pair<char, string>> grammar;
map<pair<int, char>, string> action;
map<pair<int, char>, int> _goto;

void initGrammar() {
  grammar[1] = {'E', "TA"};
  grammar[2] = {'A', "+TA"};
  grammar[3] = {'A', "e"};
  grammar[4] = {'T', "FB"};
  grammar[5] = {'B', "*FB"};
  grammar[6] = {'B', "e"};
  grammar[7] = {'F', "(E)"};
  grammar[8] = {'F', "i"};
  return;
}

void initGoto() {
  _goto[{0, 'E'}] = 1;
  _goto[{0, 'T'}] = 2;
  _goto[{0, 'F'}] = 3;
  _goto[{2, 'A'}] = 6;
  _goto[{3, 'B'}] = 8;
  _goto[{4, 'E'}] = 10;
  _goto[{4, 'T'}] = 11;
  _goto[{4, 'F'}] = 12;
  _goto[{7, 'T'}] = 15;
  _goto[{7, 'F'}] = 3;
  _goto[{9, 'F'}] = 16;
  _goto[{11, 'A'}] = 18;
  _goto[{12, 'B'}] = 20;
  _goto[{13, 'E'}] = 22;
  _goto[{13, 'T'}] = 11;
  _goto[{13, 'F'}] = 12;
  _goto[{15, 'A'}] = 23;
  _goto[{16, 'B'}] = 24;
  _goto[{19, 'T'}] = 25;
  _goto[{19, 'F'}] = 12;
  _goto[{21, 'F'}] = 26;
  _goto[{25, 'A'}] = 28;
  _goto[{26, 'B'}] = 29;
  return;
}

void initAction() {
  action[{0, '('}] = "s4";
  action[{0, 'i'}] = "s5";

  action[{1, '$'}] = "accept";

  action[{2, '+'}] = "s7";
  action[{2, '$'}] = "r3";

  action[{3, '+'}] = "r6";
  action[{3, '*'}] = "s9";
  action[{3, '$'}] = "r6";

  action[{4, '('}] = "s13";
  action[{4, 'i'}] = "s14";

  action[{5, '+'}] = "r8";
  action[{5, '*'}] = "r8";
  action[{5, '$'}] = "r8";

  action[{6, '$'}] = "r1";

  action[{7, '('}] = "s4";
  action[{7, 'i'}] = "s5";

  action[{8, '+'}] = "r4";
  action[{8, '$'}] = "r4";

  action[{9, '('}] = "s4";
  action[{9, 'i'}] = "s5";

  action[{10, ')'}] = "s17";

  action[{11, '+'}] = "s19";
  action[{11, ')'}] = "r3";

  action[{12, '+'}] = "r6";
  action[{12, '*'}] = "s21";
  action[{12, ')'}] = "r6";

  action[{13, '('}] = "s13";
  action[{13, 'i'}] = "s14";

  action[{14, '+'}] = "r8";
  action[{14, '*'}] = "r8";
  action[{14, ')'}] = "r8";

  action[{15, '+'}] = "s7";
  action[{15, '$'}] = "r3";

  action[{16, '+'}] = "r6";
  action[{16, '*'}] = "s9";
  action[{16, '$'}] = "r6";

  action[{17, '+'}] = "r7";
  action[{17, '*'}] = "r7";
  action[{17, '$'}] = "r7";

  action[{18, ')'}] = "r1";

  action[{19, '('}] = "s13";
  action[{19, 'i'}] = "s14";

  action[{20, '+'}] = "r4";
  action[{20, ')'}] = "r4";

  action[{21, '('}] = "s13";
  action[{21, 'i'}] = "s14";

  action[{22, ')'}] = "s27";

  action[{23, '$'}] = "r2";

  action[{24, '+'}] = "r5";
  action[{24, '$'}] = "r5";

  action[{25, '+'}] = "s19";
  action[{25, ')'}] = "r3";

  action[{26, '+'}] = "r6";
  action[{26, '*'}] = "s21";
  action[{26, ')'}] = "r6";

  action[{27, '+'}] = "r7";
  action[{27, '*'}] = "r7";
  action[{27, ')'}] = "r7";

  action[{28, ')'}] = "r2";

  action[{29, '+'}] = "r5";
  action[{29, ')'}] = "r5";
  return;
}

bool canonicalLRParser(string s, int ind) {
  stack<int> state_table;
  stack<char> symbol_table;
  symbol_table.push('$');
  state_table.push(0);
  while(true){
    int tp = state_table.top();
    if(!action.count({tp, s[ind]})) return false;

    string act = action[{tp, s[ind]}];
    if(act[0] == 's'){
      act = act.substr(1);
      state_table.push(stoi(act));
      symbol_table.push(s[ind]);
      ind++;
    }
    else if(act[0] == 'r'){
      act = act.substr(1);
      pair<char, string> red = grammar[stoi(act)];
      int len = red.second.size();
      if(red.second == "e") len = 0;
      while(len--) {
        state_table.pop();
        symbol_table.pop();
      }
      int t = state_table.top();
      if(!_goto.count({t, red.first})) return false;
      state_table.push(_goto[{t, red.first}]);
      symbol_table.push(red.first);
    }
    else if(act == "accept") return true;

    else return false;
  }
  return false;
}

int main() {
  initGrammar();
  initGoto();
  initAction();
  
  string s;
  const string defaultInput = "id*(id + id)  id";

  string inp;
  getline(cin, inp);
  string input;
  if (!inp.empty()) input = inp;
  else input = defaultInput;

  input.erase(remove(input.begin(), input.end(), ' '), input.end());
  input.erase(remove(input.begin(), input.end(), 'd'), input.end());
  input.push_back('$');

  bool canParse = canonicalLRParser(input, 0);
  if(canParse) cout << "The given input is accepted by the grammar";
  else cout << "The given input is not accepted by the grammar";
}