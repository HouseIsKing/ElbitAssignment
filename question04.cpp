//Question 4 - Filesystem & args  

// Task: Implement the code as described in the main body, make sure to handle cases when the requested file is not found or the "files" directory doesn't exists and you have to create it
// Prefer modern solutions over classic C style solutions and keep in mind that this code should be able to run in other windows, linux and other platforms (hint: '/' and '\' in file paths)


#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

constexpr auto FOLDER_NAME = "files";
constexpr auto CREATE_COMMAND = "create";
constexpr auto READ_COMMAND = "read";

//Creates and inputs contents into file in the current path
void createFileAndWriteContents(std::string fileName, char* contents)
{
	std::ofstream myFile(fileName + ".txt");
	if (!myFile.is_open())
	{
		std::cout << "Failed to open/create the file requested, aborting" << std::endl;
		return;
	}
	myFile << "Hello from " << contents;
	myFile.close();
}

//Reads from file in the current path named as file name
void readFromFileAndPrintResult(std::string fileName)
{
	std::ifstream myFile(fileName + std::string(".txt"));
	if (!myFile.is_open())
	{
		std::cout << "Failed to open the file requested(possibly it doesn't exist), aborting" << std::endl;
		return;
	}
	std::string messageFile;
	std::getline(myFile, messageFile);
	myFile.close();
	std::cout << messageFile << std::endl;
}

//Initializes the path to look at the files folder. Independent of Operating system.
bool init(std::string argumentInit)
{
	if (!std::filesystem::exists(FOLDER_NAME))
	{
		if(argumentInit._Equal(CREATE_COMMAND))
			if (!std::filesystem::create_directory(FOLDER_NAME))
			{
				std::cout << "Error creating the folder files aborting" << std::endl;
				return false;
			}
		if (argumentInit._Equal(READ_COMMAND))
		{
			std::cout << "File system doesn't exist, aborting" << std::endl;
			return false;
		}
	}
	std::filesystem::directory_iterator dirIterator = std::filesystem::directory_iterator(std::filesystem::current_path());
	dirIterator = std::filesystem::begin(dirIterator);
	for (std::filesystem::directory_entry entry : dirIterator)
		if (entry.path().filename().string()._Equal(FOLDER_NAME))
		{
			std::filesystem::current_path(entry.path());
			return true;
		}
}

//If user passed "create" argument 
//		Create (or overwrite) a file named *argument2.txt*  with the text "Hello from *argument3*" in a folder named "files" under the current working directory  
//else if user passed "read" argument 
//		read a file named* argument2* from a folder named "files" under the current working directory and print it to the console

//Execution example (assuming working directory c:\code): question04.exe create test1 Nir - should create the file c:\code\files\test1.txt with the content "Hello from Nir"
//Execution example (assuming working directory c:\code): question04.exe read test1  - should print "Hello from Nir" in the console (assuming the previous command was executed) 
int main(int argc, char** argv)
{
	if (argc < 3)
		std::cout << "Error you didn't input enough arugments" << std::endl;
	else 
	{
		if (init(std::string(argv[1])))
		{
			if (std::strcmp(argv[1], CREATE_COMMAND) == 0)
			{
				createFileAndWriteContents(std::string(argv[2]), argv[3]);
			}
			else if (std::strcmp(argv[1], READ_COMMAND) == 0)
			{
				readFromFileAndPrintResult(std::string(argv[2]));
			}
			else
				std::cout << "Error wrong input on argument 1" << std::endl;
		}
	}
	std::cout << "Press enter to exit" << std::endl;
	getchar();
	return 0;
}