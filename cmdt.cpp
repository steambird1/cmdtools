#include <iostream>
#include <cstdlib>
#include <string>
#include <windows.h>
using namespace std;

string help="cmdt by steambird 2021 \nUsage: cmdt <options> <string>\n\nOptions:\n-h, --help   Show this help message and quit \n\
-c, --color   Change the color of text next time, or no another argument to exit. (For color informations see color /?)\n\
-s, --sleep   Sleep for a few ms\n\
-p, --print   Print a text without new line\n\
-e, --effect <effect>  Run a effect";

#define sHnd GetStdHandle(STD_OUTPUT_HANDLE)

#define FOREGROUND_YELLOW FOREGROUND_RED | FOREGROUND_GREEN
#define FOREGROUND_PINK FOREGROUND_RED | FOREGROUND_BLUE
#define FOREGROUND_CYAN FOREGROUND_GREEN | FOREGROUND_BLUE
#define FOREGROUND_WHITE FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE

#define BACKGROUND_YELLOW BACKGROUND_RED | BACKGROUND_GREEN
#define BACKGROUND_PINK BACKGROUND_RED | BACKGROUND_BLUE
#define BACKGROUND_CYAN BACKGROUND_GREEN | BACKGROUND_BLUE
#define BACKGROUND_WHITE BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE

#define rpush(val) result = result | val

#define ERR_INVAILD_COLOR 2 
#define ERR_INVAILD_COLOR_CHAR 3

#define ERR_INVAILD_PARAMETER 5

#define ERR_INVAILD_EFFECT 7


#define DEFAULT_TYPE_SPEED 100

void err(string info,int errcode) {
	cout<<info<<endl;
	exit(errcode);
	return;
}

WORD getColorByString(string s) {
	char b=toupper(s[0]),f=toupper(s[1]);
	WORD result = 0;
	switch (f) {
		case '0':
			break;
		case '9':
			rpush(FOREGROUND_INTENSITY);
		case '1':
			rpush(FOREGROUND_BLUE);
			break;
		case 'A':
			rpush(FOREGROUND_INTENSITY);
		case '2':
			rpush(FOREGROUND_GREEN);
			break;
		case 'B':
			rpush(FOREGROUND_INTENSITY);
		case '3':
			rpush(FOREGROUND_CYAN);
			break;
		case 'C':
			rpush(FOREGROUND_INTENSITY);
		case '4':
			rpush(FOREGROUND_RED);
			break;
		case 'D':
			rpush(FOREGROUND_INTENSITY);
		case '5':
			rpush(FOREGROUND_PINK);
			break;
		case 'E':
			rpush(FOREGROUND_INTENSITY);
		case '6':
			rpush(FOREGROUND_YELLOW);
			break;
		case 'F':
			rpush(FOREGROUND_INTENSITY);
		case '7':
			rpush(FOREGROUND_WHITE);
			break;
		case '8':
			err("Invaild color\n",ERR_INVAILD_COLOR);
			break;
		default:
			err("Invaild color\n",ERR_INVAILD_COLOR_CHAR);
			break;	
	}
	switch (b) {
		case '0':
			break;
		case '1':
			rpush(BACKGROUND_BLUE);
		case '9':
			rpush(BACKGROUND_INTENSITY);
			break;
		case '2':
			rpush(BACKGROUND_GREEN);
		case 'A':
			rpush(BACKGROUND_INTENSITY);
			break;
		case '3':
			rpush(BACKGROUND_CYAN);
		case 'B':
			rpush(BACKGROUND_INTENSITY);
			break;
		case '4':
			rpush(BACKGROUND_RED);
		case 'C':
			rpush(BACKGROUND_INTENSITY);
			break;
		case '5':
			rpush(BACKGROUND_PINK);
		case 'D':
			rpush(BACKGROUND_INTENSITY);
			break;
		case '6':
			rpush(BACKGROUND_YELLOW);
		case 'E':
			rpush(BACKGROUND_INTENSITY);
			break;
		case '7':
			rpush(BACKGROUND_WHITE);
		case 'F':
			rpush(BACKGROUND_INTENSITY);
			break;
		case '8':
			err("Invaild color\n",ERR_INVAILD_COLOR);
			break;
		default:
			err("Invaild color\n",ERR_INVAILD_COLOR_CHAR);
			break;	
	}
	return result;
}

void setColor(string s2) {
	SetConsoleTextAttribute(sHnd,getColorByString(s2));
}

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
			} else if (s2=="coo") {
				cout<<s3<<" Coo~~"<<endl;
			} else {
				err("Effect not found\n",ERR_INVAILD_EFFECT);
			}
		} else {
			err("Required parameter missing\n",ERR_INVAILD_PARAMETER);
		}
	}
	return 0;
} 
