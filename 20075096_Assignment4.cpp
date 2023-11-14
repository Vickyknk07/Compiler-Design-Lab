#include <iostream>
#include <string>
#include <cctype>
using namespace std;

string input;
size_t index = 0;

bool match(char expected){
    while(index < input.length() && isspace(input[index])){
        index++;
    }
    if(index < input.length() && input[index] == expected){
        index++;
        return true;
    }
    return false;
}

bool parseE();
bool parseEPrime();
bool parseT();
bool parseTPrime();
bool parseF();

bool parseE(){
    if(parseT() && parseEPrime()){
        return true;
    }
    return false;
}

bool parseEPrime(){
    if(match('+') && parseT() && parseEPrime()){
        return true;
    }
    return true;  
}

bool parseT(){
    if(parseF() && parseTPrime()){
        return true;
    }
    return false;
}

bool parseTPrime(){
    if(match('*') && parseF() && parseTPrime()){
        return true;
    }
    return true; 
}

bool parseF(){
    if(match('(') && parseE() && match(')')){
        return true;
    }
    if(isalpha(input[index]) || input[index] == '_'){
        while(index < input.length() && (isalnum(input[index]) || input[index] == '_')){
            index++;
        }
        return true;
    }
    return false;
}

int main(){
    input = "(id * id + id";

    index = 0;

    if(parseE() && index == input.length()) {
        cout << input << ": Valid expression." << endl;
    } 
    else{
        cout << input << ": Invalid expression." << endl;
    }

    return 0;
}