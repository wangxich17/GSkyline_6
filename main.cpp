#include<iostream>
#include<string>
using namespace std;
int experiment(string filename, int k, string output);
int main()
{
//	cout << "Please enter the path to read the input file:" << endl;
//	string filename;
//	cin >> filename;
//	cout << "Please enter the value of the k:" << endl;
//	int k;
//	cin >> k;
//	cout << "Please enter the path to save the output file:" << endl;
//	string output;
//	cin >> output;
	string filename = "anti_2.txt";
	int k = 2;
	string output = "re.txt";
	if (experiment(filename, k, output) == 0)
	{
		cout << "Error parameter" << endl;
		cout << "Correct example:" << endl << "          " << "filename:test/corr_2.txt" << endl;
		cout << "          " << "k:2" << endl;
		cout << "          " << "output:res.txt" << endl;
	}
	else
		cout << "The program is running successfully,Please see the results:" << output << endl;
	return 0;
}