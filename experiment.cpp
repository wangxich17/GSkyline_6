#include "GSkyline.h"
#include<iostream>
#include<vector>
#include<ctime>
#include<fstream>
using namespace std;

unsigned long GetTickCount() {
	struct timespec ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);

	return (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}

int experiment(string inputfilename, int k, string outputfilename)
{
	ifstream ifile(inputfilename);
	if (!ifile.is_open())
		return 0;
	else if (k <= 0)
		return 0;
	else {
		ofstream outFile(outputfilename);
		streambuf *strmout_buf = cout.rdbuf();
		cout.rdbuf(outFile.rdbuf());
		time_t time_start, time_end;


		cout << "Constructing DSG......................................................" << endl;
		printf("Constructing DSG.....................................................\n");
		time_start = GetTickCount();
		GSkyline skyline(inputfilename);
		time_end = GetTickCount();
		cout << "size:" << skyline.allPoints.size() << endl;
		cout << "layers:" << skyline.layers.size() << endl;
		cout << "Constructing DSG cost time:" << time_end - time_start << "ms" << endl;
		printf("size:%d\n", skyline.allPoints.size());
		printf("layers:%d\n", skyline.layers.size());
		printf("Constructing DSG cost time:%d ms\n", time_end - time_start);
		cout << "Constructing DSG........................................................." << endl << endl;
		printf("Constructing DSG.........................................................\n\n");


		cout << "Preprocessing start..................................................." << endl;
		printf("Preprocessing start...................................................\n");
		time_start = GetTickCount();
		vector<GGroup> pre = skyline.Preprocessing(k);
		time_end = GetTickCount();
		cout << "Preprocessing cost time:" << time_end - time_start << "ms" << endl;
		cout << "Preprocessing result:" << endl;
		printf("Preprocessing cost time:%d ms\n", time_end - time_start);
		printf("Preprocessing result:\n");
		int preNum = pre.size();
		cout << "Preprocessing end....................................................." << endl << endl;
		printf("Preprocessing end.....................................................\n\n");


		cout << "PointWisePlus start..................................................." << endl;
		printf("PointWisePlus start....................................................\n");
		time_start = GetTickCount();
		try {
			int cnt = skyline.PWP(k);
			time_end = GetTickCount();
			cout << "get result group num:" << cnt + preNum <<endl;
			printf("get result group num:%d\n", cnt + preNum);
		}
		catch (exception &e) {
			cout << e.what();
			printf(e.what());
		}
		cout << "Point wise cost time: " << (time_end - time_start) << " ms" << endl;
		printf("Point wise cost time:%d ms\n", time_end - time_start);
		cout << "Point Wise end........................................................" << endl << endl;
		printf("Point Wise end.......................................................\n\n");


		cout << "UnitWisePlus start...................................................." << endl;
		printf("UnitWisePlus start....................................................\n");
		time_start = GetTickCount();
		int uwiseNum = skyline.UWP(k);
		time_end = GetTickCount();
		cout << "UnitWisePlus get result group num:" << (uwiseNum + preNum) << endl;
		cout << "UnitWisePlus cost time: " << (time_end - time_start) << " ms" << endl;
		printf("UnitWisePlus get result group num:%d\n", (uwiseNum + preNum));
		printf("UnitWisePlus cost time:%d ms\n", (time_end - time_start));
		cout << "UnitWisePlus end......................................................" << endl << endl;
		printf("UnitWisePlus end......................................................\n\n");
		outFile.close();
		cout.rdbuf(strmout_buf);
	}
	return 1;
}