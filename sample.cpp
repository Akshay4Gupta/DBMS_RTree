#include<bits/stdc++.h>
#include "file_manager.h"
#include "errors.h"
// #include<cstring>

using namespace std;


int main(int argc, char **argv) {
	FileManager fm;

	// Create a brand new file
	string path = "Testcases/selfTC_2/";
	FileHandler fh = fm.CreateFile((path+"bulkload.txt").c_str());
	cout << "File created " << endl;
	ifstream file;
  file.open((path+"bulk.txt").c_str());
	string line;
	PageHandler ph = fh.NewPage ();
	int *data = (int *)ph.GetData ();
	int i = 0, dim = stoi(argv[1]);
	int x = PAGE_CONTENT_SIZE;
	while(getline(file, line)){
		stringstream s(line);
    string word;
		int j = 0;
    while(s >> word){
			int w = stoi(word);
			// cout<<i*dim+j<<' ';
			// cin>>x;
			memcpy(&data[i*dim+j], &w, sizeof(int));

			// fm.CloseFile(fh);
			// file.close();
			// return 0;

			j++;
		}
		// if(j > dim)
		// cout<<x - i*dim*sizeof(int)<<" ";
		i++;
		fh.MarkDirty(ph.GetPageNum());
		if(x - i*dim*sizeof(int) < dim*sizeof(int)){
			i = 0;
			fh.UnpinPage(ph.GetPageNum());
			ph = fh.NewPage ();
			data = (int *)ph.GetData ();
		}
	}
	fh.FlushPages ();
	fm.CloseFile(fh);
	file.close();

	// Create a new page

}
