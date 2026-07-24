#include "inode.h"
#include <iostream>

Inode::Inode() {
    inodeNumber = 0;
    fileName = "";
    fileSize = 0;
    content = "";
    isDirectory = false;

    owner = "root";
    permissions = "rwx";

    createdTime = time(nullptr);
    modifiedTime = time(nullptr);
}

Inode::Inode(int number,
             const std::string& name,
             bool directory) {

    inodeNumber = number;
    fileName = name;
    fileSize = 0;
    content = "";
    isDirectory = directory;

    owner = "root";
    permissions = "rwx";

    createdTime = time(nullptr);
    modifiedTime = time(nullptr);
}

void Inode::displayInfo() const {

    std::cout << "Inode Number : " << inodeNumber << std::endl;
    std::cout << "Name         : " << fileName << std::endl;
    std::cout << "Size         : " << fileSize << " bytes" << std::endl;
    std::cout << "Directory    : " << (isDirectory ? "Yes" : "No") << std::endl;
    std::cout << "Owner        : " << owner << std::endl;
    std::cout << "Permissions  : " << permissions << std::endl;
}
