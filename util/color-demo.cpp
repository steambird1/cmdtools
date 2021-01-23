#include "cmdtfunc.h"
#include <iostream>
using namespace std;

int main() {
	char cl[] = {'0','1','2','3','4','5','6','7','9','A','B','C','D','E','F'};
	setColor("07");
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			if (i==j) continue;
			string c = "";
			c += cl[i];
			c += cl[j];
			setColor(c);
			cout<<c;
			setColor("07");
			cout<<" "; 
		}
		setColor("07");
		cout<<endl;
	}
	return 0;
}
