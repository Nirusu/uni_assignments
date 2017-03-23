//
// Testprogramm fuer Stack-Implementierung
//


#include "stack.h"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;


int main()
{
	cout << boolalpha;

	Stack<int> S1;

	S1.push(10);
	S1.push(20);

	cout << "S1.top()  : " << S1.top() << endl;

	S1.pop();
	cout << "S1.top()  : " << S1.top() << endl;

	S1.push(30);
	cout << "S1.top()  : " << S1.top() << endl;

	S1.pop();
	cout << "S1.top()  : " << S1.top() << endl;

	S1.pop();
	cout << "S1.empty(): " << S1.empty() << endl;

	S1.push(50);
	S1.push(60);
	cout << "S1.top()  : " << S1.top() << endl;

	cout << endl;

	Stack<int> S2(S1);
	cout << "S2.top()  : " << S2.top() << endl;

	S2.clear();
	S2.push(17);
	cout << "S2.top()  : " << S2.top() << endl;

	S2 = S1;

	S1.clear();
	cout << "S1.empty(): " << S1.empty() << endl;

	cout << "S2.top()  : " << S2.top() << endl;
	S2.pop();
	cout << "S2.top()  : " << S2.top() << endl;
	S2.pop();
	cout << "S2.empty(): " << S2.empty() << endl;

	cout << endl;

	Stack<string> S3;
	S3.push("ABC");
	S3.push("DEF");

	cout << "S3.top()  : " << S3.top() << endl;
	S3.pop();
	cout << "S3.top()  : " << S3.top() << endl;
	S3.pop();
	cout << "S3.empty(): " << S3.empty() << endl;

	return 0;
}
