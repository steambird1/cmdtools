#include <iostream>
#include <cstdlib>
#include <string>
#include <windows.h>
#include <conio.h>

#include "util/cmdtfunc.h"
using namespace std;

#define ERR_INVAILD_PARAMETER 5

#define ERR_INVAILD_EFFECT 7

#define DEFAULT_TYPE_SPEED 100

string help="cmdt by steambird 2021 \nUsage: cmdt <options> <string>\n\nOptions:\n-h, --help   Show this help message and quit \n\
-c, --color   Change the color of text next time, or no another argument to exit. (For color informations see color /?)\n\
-s, --sleep   Sleep for a few ms\n\
-p, --print   Print a text without new line\n\
-e, --effect <effect>  Run a effect\n\
-k, --key     Listen to a key and return keycode\n\
-w, --pass    Input a password as secret mode and output";

int main(int argc,char* argv[]) {
	string s1 = "";
	if (argc==1) {
		cout<<help<<endl;
		return 0;
	}
	s1 = argv[1];
	//int n;
	//cin>>n;
	if (s1=="-h"||s1=="--help") {
		// test:
		//SetConsoleTextAttribute(sHnd,getColorByString("2f"));
		cout<<help<<endl;
		return 0;
	}
	if (((s1=="-c")||(s1=="--color"))) {
		if (argc > 2) {
			string s2 = argv[2];
			setColor(s2);
		} else {
			system("color");
			setColor("07");
		}
	}
	if ((s1=="-s")||(s1=="--sleep")) {
		if (argc > 2) {
			string s2 = argv[2];
			Sleep(atoi(s2.c_str()));
		} else {
			err("Required parameter missing\n",ERR_INVAILD_PARAMETER);
		}
	}
	if ((s1=="-p")||(s1=="--print")) {
		if (argc > 2) {
			//cout<<argc<<" ";//test
			string s2 = "";
			for (int i = 2; i < argc; i++) {
				//cout<<i<<" "<<argv[i]<<" ";//test
				s2 = s2 + argv[i] + " ";
			}
			cout<<s2;// no ending
		}
	}
	if ((s1=="-e")||(s1=="--effect")) {
		if (argc > 3) {
			string s2 = argv[2], s3 = "";
			for (int i = 3; i < argc; i++) s3 = s3 + argv[i] + " ";
			if (s2=="typing") {
				for (int i = 0; i < s3.length(); i++) {
					cout<<s3[i];
					Sleep(DEFAULT_TYPE_SPEED);
				}
			} else if (s2=="rainbow") {
				string blist[] = {"0A","0B","0C","0D","0E","0F"};
				for (int i = 0; i < s3.length(); i++) {
					setColor(blist[i%6]);
					cout<<s3[i];
				}
				setColor("07");
			} else if (s2=="typing_rainbow") {
				string blist[] = {"0A","0B","0C","0D","0E","0F"};
				for (int i = 0; i < s3.length(); i++) {
					setColor(blist[i%6]);
					cout<<s3[i];
					Sleep(DEFAULT_TYPE_SPEED);
				}
				setColor("07");
			} else if (s2=="progress") {
				// do not output first progress information use this!
				// keep the length of precent information same each time.
				for (int i = 0; i < s3.length(); i++) {
					cout<<"\b \b";
				}
				cout<<s3;
			} else if (s2=="coo") {
				cout<<s3<<" Coo~~"<<endl;
			} else {
				err("Effect not found\n",ERR_INVAILD_EFFECT);
			}
		} else {
			err("Required parameter missing\n",ERR_INVAILD_PARAMETER);
		}
	}
	if ((s1=="-k")||(s1=="--key")) {
		return getch();
	}
	if ((s1=="-w")||(s1=="--pass")) {
		if (argc < 3) {
			err("Required parameter missing\n",ERR_INVAILD_PARAMETER);
		}
		string c = argv[2];
		int k;
		string s = "";
		do {
			k=getch();
			if (k==13) break;
			if (k==8&&s.length()>0) {
				cout<<"\b \b";
				s=s.substr(0,s.length()-1);
				continue;
			}
			cout<<"*";
			s+=char(k);
		} while (1);
		if (s==c) return 0;
		return 1;
	}
	return 0;
} 
