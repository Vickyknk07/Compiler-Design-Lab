/******************************************************     
Author       : Vicky Kumar Nayak
Created      : 2023-09-28
Filename     : 20075096_Assignment5.cpp
******************************************************/
#include<bits/stdc++.h>
using namespace std; 

map<pair<char, char>, string> parseTable;

string transform(string input){
    int inputPtr = 0;
    int nextPtr = inputPtr+1;
    string output = "";
    while(inputPtr < input.size() && output != "invalid"){
        char current = input[inputPtr];
        switch(current){
            case 'i':
                if(nextPtr < input.size() && input[nextPtr] == 'd'){
                     output += 'i';
                     inputPtr += 2;
                     nextPtr = inputPtr+1;
                     break;
                }
                else{
                    output = "invalid";
                    break;
                }
            case '+':
                    output += '+';
                    inputPtr++;
                    nextPtr = inputPtr+1;
                    break;
            case '(':
                     output += '(';
                     inputPtr++;
                     nextPtr = inputPtr+1;
                     break;
            case ')':
                     output += ')';
                     inputPtr++;
                     nextPtr = inputPtr+1;
                     break;
            case '*':
                     output += '*';
                     inputPtr++;
                     nextPtr = inputPtr+1;
                     break;
            case ' ':
                     inputPtr++;
                     nextPtr = inputPtr+1;
                     break;
            default:
                     output = "invalid";
         } 
    }
    return output;
} 

bool isTerminal(char c){
    if(c != 'E' && c != 'e' && c != 'T' && c != 't' && c != 'F' && c != 'n') return true;
    return false;
}

bool LL1Parse(string input){
    stack<char> s;
    s.push('E');
    int inputPtr = 0; 
    while(!s.empty()){
        if(s.top() == input[inputPtr]){
            s.pop();
            inputPtr++;
        }
        else if(isTerminal(s.top())) return false;
        else if(parseTable.find({s.top(), input[inputPtr]}) == parseTable.end()) return false;
        else{
            string rightProd = parseTable[{s.top(), input[inputPtr]}];
            s.pop();
            for(int i=rightProd.size()-1; i>=0; i--){
                if(rightProd[i] != 'n') s.push(rightProd[i]);
            }
        }
    }  
    return true;
}

int main(){ 
    parseTable[{'E', 'i'}] = "Te";
    parseTable[{'E', '('}] = "Te";
    
    parseTable[{'e', '+'}] = "+Te";
    parseTable[{'e', ')'}] = "n";
    parseTable[{'e', '$'}] = "n";

    parseTable[{'T', 'i'}] = "Ft";
    parseTable[{'T', '('}] = "Ft";

    parseTable[{'t', '+'}] = "n";
    parseTable[{'t', '*'}] = "*Ft";
    parseTable[{'t', ')'}] = "n";
    parseTable[{'t', '$'}] = "n";
    
    parseTable[{'F', 'i'}] = "i";
    parseTable[{'F', '('}] = "(E)";
    
    const string defaultInput = "id*(id + id)";

    string inp;
    getline(cin, inp);
    string input;
    if (!inp.empty()) input = transform(inp);
    else input = transform(defaultInput);
    
    if(input != "invalid"){
        input += '$';
        bool canParse = LL1Parse(input);
        if(!canParse) cout << "The given input is not accepted by the grammar";
        else cout << "The given input is accepted by the grammar";
    }
    else cout << "Invalid Input";
}