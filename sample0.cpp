#include<bits/stdc++.h>
#include "file_manager.h"
#include "errors.h"
// #include<cstring>

using namespace std;


int main(int argc, char **argv) {
	FileManager fm;

	// Create a brand new file
	string path = "Testcases/selfTC_2/";
	FileHandler fh = fm.OpenFile((path+"bulkload.txt").c_str());
	PageHandler ph = fh.FirstPage();
	int i = 0, w = 0, dim = stoi(argv[1]);
	int x = PAGE_CONTENT_SIZE;
	int *data = (int *)ph.GetData();
	while(true){
		for(int j = 0; j < dim; j++){
			memcpy(&w, &data[i*dim+j], sizeof(int));
			cout<<w<<" ";
		}
		cout<<endl;
		i++;
		if(x - i*dim*sizeof(int) < dim*sizeof(int)){
			i = 0;
			try{
				fh.UnpinPage(ph.GetPageNum());
				ph = fh.NextPage(ph.GetPageNum());
				data = (int *)ph.GetData ();
			}catch(exception &e){
				break;
			}
		}
	}
	fh.FlushPages ();
	fm.CloseFile(fh);

	// Create a new page

}
