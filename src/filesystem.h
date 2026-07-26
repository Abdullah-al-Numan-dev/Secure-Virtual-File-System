#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <map>
#include <string>
#include <vector>
#include "inode.h"

class FileSystem {

private:
    int nextInode;

	// Encryption helper functions
    std::string encrypt(const std::string& data);
    std::string decrypt(const std::string& data);

public:

    std::map<std::string, Inode> inodeTable;

    FileSystem();

    bool createFile(const std::string& path);

    bool createDirectory(const std::string& path);

    bool deleteFile(const std::string& path);

    bool deleteDirectory(const std::string& path);

    bool writeFile(const std::string& path, const std::string& data);

    std::string readFile(const std::string& path);

    bool changePermissions(const std::string& path,
                       const std::string& permissions);

    bool isValidPath(const std::string& path);

    bool parentDirectoryExists(const std::string& path);

    bool isDirectoryEmpty(const std::string& path);

    bool exists(const std::string& path);

    Inode* getInode(const std::string& path);

    void listFiles();

    std::vector<std::string> getAllPaths();

    void viewLog();

    void showDirectoryTree();

    void printTree(const std::string& currentPath,
                   const std::string& indent);
};

#endif
