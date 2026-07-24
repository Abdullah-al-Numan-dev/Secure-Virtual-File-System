#ifndef INODE_H
#define INODE_H

#include <string>
#include <ctime>

class Inode{
public:
	int inodeNumber;
	std::string fileName;
	size_t fileSize;
	std::string content;

	bool isDirectory;

	std::string owner;
	std::string permissions;

	time_t createdTime;
	time_t modifiedTime;

	Inode();

	Inode(int number, const std::string& name, bool directory);

	void displayInfo() const;
};

#endif
