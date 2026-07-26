#include "filesystem.h"
#include "logger.h"
#include <iostream>
#include <fstream>
#include <vector>

FileSystem::FileSystem() {
    nextInode = 1;
}

bool FileSystem::createFile(const std::string& path)
{
    // Validate path
    if (!isValidPath(path))
    {
        std::cout << "Error: Invalid path.\n";
        return false;
    }

    // Parent directory must exist
    if (!parentDirectoryExists(path))
    {
        std::cout << "Error: Parent directory does not exist.\n";
	Logger::log("Failed to create file (parent missing): " + path);
        return false;
    }

    // File already exists
    if (exists(path))
    {
        std::cout << "Error: File already exists.\n";
	Logger::log("Failed to create file (already exists): " + path);
        return false;
    }

    Inode newFile(nextInode++, path, false);

    inodeTable[path] = newFile;

    Logger::log("File Created: " + path);

    return true;
}

bool FileSystem::createDirectory(const std::string& path)
{
    if (!isValidPath(path))
    {
        std::cout << "Error: Invalid path.\n";
        Logger::log("Failed to create directory (invalid path): " + path);
        return false;
    }

    if (exists(path))
    {
        std::cout << "Error: Directory already exists.\n";
        Logger::log("Failed to create directory (already exists): " + path);
        return false;
    }

    Inode newDirectory(nextInode++, path, true);
    inodeTable[path] = newDirectory;

    Logger::log("Directory Created: " + path);

    return true;
}
bool FileSystem::deleteFile(const std::string& path) {
    // TODO
    // Check if the file exists
    if (!exists(path))
    {
	std::cout << "Error: File not found.\n";
        Logger::log("Failed to delete file (permission denied): " + path);
	return false;
    }

    // Make sure it is not a directory
    if (inodeTable[path].isDirectory)
    {
	std::cout << "Error: Cannot delete a directory using deleteFile().\n";
        Logger::log("Failed to delete file (permission denied): " + path);
	return false;
    }

	// Check write permission
    if (inodeTable[path].permissions.find('w') == std::string::npos)
    {
        std::cout << "Error: Delete permission denied.\n";
	Logger::log("Failed to delete file (permission denied): " + path);
        return false;
    }

    // Remove the file
    inodeTable.erase(path);
    Logger::log("File Deleted: " + path);
    return true;
}

bool FileSystem::deleteDirectory(const std::string& path)
{
    if (!exists(path))
    {
        std::cout << "Error: Directory not found.\n";
        Logger::log("Failed to delete directory (not empty): " + path);
	return false;
    }

    Inode &dir = inodeTable[path];

    if (!dir.isDirectory)
    {
        std::cout << "Error: This is not a directory.\n";
        Logger::log("Failed to delete directory (not empty): " + path);
	return false;
    }

    if (!isDirectoryEmpty(path))
    {
        std::cout << "Error: Directory is not empty.\n";
        Logger::log("Failed to delete directory (not empty): " + path);
	return false;
    }

    inodeTable.erase(path);
    Logger::log("Directory Deleted: " + path);
    return true;
}
bool FileSystem::writeFile(const std::string& path, const std::string& data)
{
    if (!exists(path))
    {
        std::cout << "Error: File not found.\n";
	Logger::log("Failed to write file (permission denied): " + path);
        return false;
    }

    Inode &file = inodeTable[path];

    if (file.isDirectory)
    {
        std::cout << "Error: Cannot write to a directory.\n";
	Logger::log("Failed to write file (permission denied): " + path);
        return false;
    }

    if (file.permissions.find('w') == std::string::npos)
    {
        std::cout << "Error: Write permission denied.\n";
	Logger::log("Failed to write file (permission denied): " + path);
	return false;
    }

    file.content = encrypt(data);
    file.fileSize = data.size();
    file.modifiedTime = time(nullptr);

    Logger::log("File Written: " + path);
    return true;
}
std::string FileSystem::readFile(const std::string& path)
{
    if (!exists(path))
    {
	Logger::log("Failed to read file (permission denied): " + path);
        return "Error: File not found.";
    }

    Inode &file = inodeTable[path];

    if (file.isDirectory)
    {
	Logger::log("Failed to read file (permission denied): " + path);
        return "Error: Cannot read a directory.";
    }

    if (file.permissions.find('r') == std::string::npos)
    {
	Logger::log("Failed to read file (permission denied): " + path);
        return "Error: Read permission denied.";
    }

    Logger::log("File Read: " + path);
    return decrypt(file.content);
}
bool FileSystem::exists(const std::string& path) {
    // TODO
	return inodeTable.find(path) != inodeTable.end();
}
void FileSystem::listFiles() {

    std::cout << "\n========== FILE SYSTEM ==========\n";

    if (inodeTable.empty()) {
        std::cout << "No files or directories found.\n";
        return;
    }

    for (const auto& item : inodeTable) {

        item.second.displayInfo();

        std::cout << "-----------------------------\n";
    }
}
Inode* FileSystem::getInode(const std::string& path)
{
    auto it = inodeTable.find(path);

    if (it == inodeTable.end())
    {
        return nullptr;
    }

    return &it->second;
}
bool FileSystem::changePermissions(const std::string& path,
                                   const std::string& permissions)
{
    if (!exists(path))
    {
        std::cout << "Error: File not found.\n";
	Logger::log("Failed to change permissions (not found): " + path);
        return false;
    }

    inodeTable[path].permissions = permissions;
    Logger::log("Permissions Changed: " + path + " -> " + permissions);
    return true;
}
std::string FileSystem::encrypt(const std::string& data)
{
    std::string encrypted = data;

    for (char &c : encrypted)
    {
        c = c + 3;
    }

    return encrypted;
}

std::string FileSystem::decrypt(const std::string& data)
{
    std::string decrypted = data;

    for (char &c : decrypted)
    {
        c = c - 3;
    }

    return decrypted;
}
bool FileSystem::isValidPath(const std::string& path)
{
    // Path cannot be empty
    if (path.empty())
        return false;

    // Path must start with '/'
    if (path[0] != '/')
        return false;

    // Path cannot end with '/'
    if (path.length() > 1 && path.back() == '/')
        return false;

    return true;
}
bool FileSystem::parentDirectoryExists(const std::string& path)
{
    // Root-level items like "/Documents"
    size_t pos = path.find_last_of('/');

    if (pos == 0)
    {
        return true;
    }

    std::string parent = path.substr(0, pos);

    if (!exists(parent))
    {
        return false;
    }

    return inodeTable[parent].isDirectory;
}
bool FileSystem::isDirectoryEmpty(const std::string& path)
{
    for (const auto& item : inodeTable)
    {
        // Ignore the directory itself
        if (item.first == path)
            continue;

        // If another path starts with "path/"
        if (item.first.find(path + "/") == 0)
        {
            return false;
        }
    }

    return true;
}
void FileSystem::viewLog()
{
    std::ifstream logFile("log.txt");

    if (!logFile)
    {
        std::cout << "\nNo activity log found.\n";
        return;
    }

    std::cout << "\n========== ACTIVITY LOG ==========\n";

    std::string line;

    while (std::getline(logFile, line))
    {
        std::cout << line << std::endl;
    }

    logFile.close();
}
std::vector<std::string> FileSystem::getAllPaths()
{
    std::vector<std::string> paths;

    for (const auto &item : inodeTable)
    {
        paths.push_back(item.first);
    }

    return paths;
}
