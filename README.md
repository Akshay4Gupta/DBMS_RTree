# COL362/632 Assignment 3

- Code
	+ Keep all your C++ source files inside the home directory.
	+ You are supposed to use the functions mentioned in file_manager.h. Read documentation.txt for details of what each function does.
	+ Go through sample_run.cpp to get an idea of how to use the file manager.
	+ The whole source code has been shared with you for your debugging purposes and if you wish to compile in a different environment.

- Testcases
	+ Sample test files have been added to testcases directory. Read the README.md file for details on the testcases.

- Note
	+ Please don't try any funny business like by-passing the file_manager or storing the complete (large) file in your own memory. The file manager we provided must be used for every access to file.

# My modifications

- run.sh
	+ check if the testcase you are running exist in the Testcases folder or not.
	+ makefile will do all the cleaning and making of binaries.

- rtree.cpp
	+ this files contain all the code to make rtree.
	+ bulkload, insertion and pointQuery are the main function and all others are the helper functions.
	+ Node class is used to define the structure of one node.
