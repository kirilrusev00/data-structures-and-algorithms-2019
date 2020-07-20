#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <string>
using namespace std;

struct Directory {
    string name;
    string absolute_path;
    Directory* parent;
    map<string, Directory*> children;
    
    Directory(string name = "", Directory* parent = nullptr) {
        this->name = name;
        this->parent = parent;
        if (this->parent) {
            this->absolute_path = parent->absolute_path + this->name + "/";
        }
        else this->absolute_path = this->name + "/";
    }
    
    bool operator<(const Directory* rhs) const {
        if (this->name.compare(rhs->name) < 0) {
            return true;
        }
        return false;
    }
    
    bool operator==(const Directory* rhs) const {
        if (this->name.compare(rhs->name) == 0) {
            return true;
        }
        return false;
    }
};

void insert(Directory* currDirectory, string name) {
    if (currDirectory->children.find(name) != currDirectory->children.end()) {
        cout << "Directory already exists\n";
    }
    else {
        Directory* newDirectory = new Directory(name, currDirectory);
        currDirectory->children.emplace(name, newDirectory);
    }
}
    
void print(Directory* currDirectory) { 
    for(auto it = currDirectory->children.cbegin(); it != currDirectory->children.cend(); ++it)
    {
        std::cout << it->first << " ";
    }
    cout << endl;
}  

void getAbsolutePath(Directory* currDirectory) {
    cout << currDirectory->absolute_path << endl;
}
    
Directory* changeDirectory(Directory* currDirectory, string newDirectoryName) {
    if (newDirectoryName == "..") {
        if (currDirectory->parent != nullptr) {
            return currDirectory->parent;
        }
        else {
            cout << "No such directory\n";
            return currDirectory;
        }
    }
    auto it = currDirectory->children.find(newDirectoryName);
    if (it != currDirectory->children.end()) {
        return it->second;
    }
    else {
        cout << "No such directory\n";
        return currDirectory;
    }
}

int main() {
    
    Directory* currDirectory = new Directory();
    int n;
    cin >> n;
    for (auto i = 0; i < n; i++) {
        string command;
        cin >> command;
        if (command == "mkdir") {
            string dir_name;
            cin >> dir_name;
            insert(currDirectory, dir_name);
        }
        if (command == "ls") {
            print(currDirectory);
        }
        if (command == "pwd") {
            getAbsolutePath(currDirectory);
        }
        if (command == "cd") {
            string dir_name;
            cin >> dir_name;
            currDirectory = changeDirectory(currDirectory, dir_name);
        }
    }
    
    return 0;
}
