#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades){
    const char *s;
    char format[] = "%[^:]: %d %d %d";
    int x,y,z,sum;
    string text;
    char name[100];
    char g;
    
    ifstream source;
    source.open(filename);
    while(getline(source,text)){
        s = text.c_str();
        sscanf(s,format,name,&x,&y,&z);
        sum = x+y+z;
        g = score2grade(sum);
        
        names.push_back(name);
        scores.push_back(sum);
        grades.push_back(g);
    }
    source.close();
}

void getCommand(string &command, string &key){
    cout << "Please input your command:\n";
    cin >> command;
    cin.ignore();
    if(toUpperStr(command) == "GRADE" || toUpperStr(command) == "NAME") getline(cin,key);
    
}

void searchName(vector<string> n, vector<int> s, vector<char> g, string key){
    cout << "---------------------------------\n";
    
    unsigned int x = 0;
    vector<string> NAME(g.size()); 
    
    for(unsigned int i = 0; i < n.size(); i++){
        NAME[i] = toUpperStr(n[i]);
    }
    
    for(unsigned int j = 0; j < n.size(); j++){
        if(NAME[j] == key) break;
        else x++;
    }
    
    if(x < n.size()){
        cout << n[x] << "'s score = " << s[x] << "\n";
        cout << n[x] << "'s grade = " << g[x] << "\n";
    }else cout << "Cannot found.\n";
       
    cout << "---------------------------------\n";
}

void searchGrade(vector<string> &names, vector<int> &scores, vector<char> &grades, string key){
    cout << "---------------------------------\n";
    int number = 0;

    for(unsigned int i = 0; i < grades.size(); i++){
        if(string(1,grades[i]) == key){
            cout << names[i] << " (" << scores[i] << ")\n";
            number++;
        }
    } 
    
    if(number == 0) cout << "Cannot found.\n";
       
    cout << "---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}