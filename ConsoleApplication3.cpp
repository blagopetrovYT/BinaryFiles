#include <iostream>
#include <fstream>  
#include <iomanip>

#pragma warning (disable : 4996)

const int MAX_SIZE = 1024;

struct HexViewerFile {
	char* data;
	int datasize;
};

int findSize(std::ifstream& file) {
	int currentPos = file.tellg();
	file.seekg(0, std::ios::end);
	int size = file.tellg();
	file.seekg(currentPos);

	return size;
}

HexViewerFile readBinaryFile(char* fileName) {
	HexViewerFile myData;

	std::ifstream file(fileName, std::ios::binary);
	if (!file.is_open()) {
		std::cout << "Error";
	}
	myData.datasize = findSize(file);
	myData.data = new char[myData.datasize + 1]; //za terminirashtata nula
	file.read((char*)myData.data, myData.datasize);
	myData.data[myData.datasize] = '\0';
	file.close();

	return myData;

}
void FirstFile() {
	std::ofstream file("myFile.dat", std::ios::binary);
	if (!file.is_open()) {
		std::cout << "Error";
	}
	char buff[MAX_SIZE];
	std::cin.getline(buff, MAX_SIZE);
	int len = strlen(buff);
	int NewSize = len + 1;
	char* NewStr = new char[NewSize];
	strcpy(NewStr, buff);
	NewStr[NewSize] = '\0';
	file.write((const char*)&NewSize, sizeof(NewSize));
	file.write(NewStr, NewSize);
	file.close();
}

bool isValid(char ch) {
	return ch >= '0' && ch <= '9' || ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z';
}

void printData(const HexViewerFile& myData) {
	for (int i = 0; i < myData.datasize; i++) {
		std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)myData.data[i] << ' '; // tiq gi pripisah bez da razbiram zashto sa taka, priznavam si!
	}
	std::cout << std::endl;
	for (int i = 0; i < myData.datasize; i++) {
		if (isValid(myData.data[i])) {
			std::cout << myData.data[i] << "  ";
		}
		else {
			std::cout << ".. ";
		}
	}
	std::cout << std::endl;
}

void addByte(HexViewerFile& myData, char ch) {
	int NewSize = myData.datasize + 1;
	char* NewStr = new char[NewSize];
	strcpy(NewStr, myData.data);
	NewStr[myData.datasize] = ch;
	NewStr[NewSize] = '\0';

	delete[] myData.data;
	myData.data = NewStr;
	myData.datasize = NewSize;
}

void changeCh(HexViewerFile& myData, char ch, int index) {
	if (index < '0' || index > myData.datasize) {
		std::cout << "Error";
	}
	myData.data[index] = ch;
}

void saveFile(HexViewerFile& myData, char* name) {
	std::ofstream file(name, std::ios::binary);
	if (!file.is_open()) {
		std::cout << "Error";
	}
	file.write((const char*)myData.data, myData.datasize);
	file.close();
}

void freeHexViewerFile(HexViewerFile& h) {
	delete[] h.data;
	h.datasize = 0;
}

int main()
{
	FirstFile();
	char fileName[MAX_SIZE];
	std::cout << "Enter name of file: "; //trqbwa da e myFile.dat za da raboti!
	std::cin.getline(fileName, MAX_SIZE);

	HexViewerFile myData = readBinaryFile(fileName);

	char command[MAX_SIZE];
	do {
		std::cout << "command: ";
		std::cin.getline(command, MAX_SIZE);

		if (strcmp(command, "print") == 0) {
			printData(myData);
		}
		else if (strcmp(command, "add") == 0) {
			char ch;
			std::cout << "Enter char: ";
			std::cin >> ch;
			addByte(myData, ch);
		}
		else if (strcmp(command, "change") == 0) {
			char ch;
			int index;
			std::cout << "Enter char and index: ";
			std::cin >> ch >> index;
			changeCh(myData, ch, index);
		}
		else if (strcmp(command, "save") == 0) {
			saveFile(myData, fileName);

		}
		else if (strcmp(command, "save as") == 0) {
			char NewName[MAX_SIZE];
			std::cout << "Enter new name: ";
			std::cin.getline(NewName, MAX_SIZE);
			saveFile(myData, NewName);
		}

	} while (strcmp(command, "stop") == 0);

	freeHexViewerFile(myData);
}
