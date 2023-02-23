#include <bits/stdc++.h>
#include <conio.h>
#include <io.h>
#include <Windows.h>
#include "tchar.h"
#include <sys/stat.h>
using namespace std;
string input_path, front_add, back_add, str_del = "NONE", file_name;
bool dele = 0, chan = 0;
bool find_suffix(string s){
	string t = file_name;
	int pos = 0;
	while((pos = s.find(t, pos)) != s.npos){
		if(pos == s.size() - t.size()) return true;
		pos++;
	}
	return false;
}
void print(string s){
	int len = str_del.length(), k = 0;
	while((k = s.find('\\')) != s.npos){
		s = s.replace(k, 1, "/");
	}
    struct stat   buffer;
    if(stat (s.c_str(), &buffer) == 0 && S_ISREG(buffer.st_mode) && find_suffix(s)){
    	if(find_suffix(s)){
			if(DeleteFile(_T(s.c_str()))){
				cout << "delete success:" << s << endl;
			} else {
				cout << "delete fail :" << s << endl; 
			}       		
		}else return;
	}else if(stat (s.c_str(), &buffer) == 0 && S_ISDIR(buffer.st_mode)){
		if(RemoveDirectory(_T(s.c_str()))){
			cout << "delete success:" << s << endl;
		} else {
			cout << "delete fail :" << s << endl; 
		}		
	}else cout << "delete fail :" << s << endl; 
//	cout << s << endl;
	
}
void _find_direction_(string path){
	__int64 hnd;
	struct __finddata64_t _File_;
	string _find_ = path + "\\*";
	if( (hnd = _findfirst64(_find_.c_str(), &_File_)) == -1L) {
		cout << "can not find any directories of files" << endl;
		return;
	}
	else {
		do {
			if(_File_.attrib & _A_SUBDIR){
				if(strcmp(_File_.name, ".") != 0 && strcmp(_File_.name, "..") != 0){
					string new_path = path + "\\" + _File_.name;
					_find_direction_(new_path);
					print(new_path);
				} 
			}else {
				string new_path = path + "\\" + _File_.name;
				print(new_path);
			}
		}while(!_findnext64(hnd, &_File_));
	}
}
int main(){
	char ch;
	cout << "root direction: ";
	getline(cin, input_path);
	cout << "Please enter the suffix of the file you want to delete(one word per line, such as \".exe\")" << endl;
	while(cin >> file_name){
		if(file_name[0] != '.') continue
		_find_direction_(input_path);
		cout << "Delete completed!" << endl;
		cout << "Do you want to continue?(Y/N): ";
		char c = getch();
		puts("");
		if(c == 'Y' || c == 'y') continue;
		break;  
	}
	system("pause");
	return 0;
}
