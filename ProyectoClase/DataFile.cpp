#include "DataFile.h"

DataFile::DataFile() : path(nullptr)
{

}

DataFile::DataFile(const char* _path) : path(_path)
{

}

DataFile::~DataFile()
{
	delete path;
	file.close();
}

void DataFile::open(const char* _openFormat)
{
	//r == read
	//w == write
	//rw == read & write

	if (strcmp(_openFormat, "r") == 0)
		openMode = std::ios_base::in;
	else if (strcmp(_openFormat, "w") == 0)
		openMode = std::ios_base::out;
	else if (strcmp(_openFormat, "rw") == 0)
		openMode = std::ios_base::out | std::ios_base::in;

	file.open(path, openMode | ios::binary);
	if (!file)
	{
		cerr << "Error: file could not be opened" << endl;
		exit(1);
	}
}

void DataFile::close()
{
	file.close();
}

void DataFile::write(char* _data, unsigned int _position, unsigned int _length)
{
	file.seekp(_position, ios::beg);
	file.write(_data, _length);
}

char* DataFile::read(unsigned int _position, unsigned int _length)
{
	char* dataRead = new char[_length];
	file.seekg(_position, ios::beg);
	file.read(dataRead, _length);
	return dataRead;
}

bool DataFile::isEOF()
{
	return file.eof();
}




