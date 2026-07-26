# Secure Virtual File System (SecureVFS)

## Overview

SecureVFS is a C++-based virtual file system developed for an Operating Systems project. It simulates core filesystem operations using an inode-based design and provides a command-line interface for managing files and directories.

The project includes file creation, directory management, read/write operations, user permissions, basic encryption, and activity logging.

---

## Features

- Inode-based file system
- Create and delete files
- Create and delete directories
- Read and write file contents
- User-level permissions (r, rw, rx, rwx)
- Basic Caesar cipher encryption/decryption
- Activity logging
- View activity log from the application
- Path validation
- Parent directory validation
- Protection against deleting non-empty directories
- Interactive command-line interface

---

## Technologies Used

- C++
- Object-Oriented Programming (OOP)
- Linux (Ubuntu)
- GNU g++

---

## Project Structure

```
SecureVFS/
├── Makefile
├── README.md
├── .gitignore
├── mount/
├── storage/
└── src/
    ├── main.cpp
    ├── filesystem.cpp
    ├── filesystem.h
    ├── inode.cpp
    ├── inode.h
    ├── logger.cpp
    ├── logger.h
    ├── permission.cpp
    ├── permission.h
    ├── encryption.cpp
    ├── encryption.h
```

---

## Build

```bash
cd src
g++ *.cpp -o filemanager
```

---

## Run

```bash
./filemanager
```

---

## Current Features Implemented

- File Management
- Directory Management
- Inode System
- Read / Write Operations
- Permission Management
- Basic Encryption
- Activity Logging
- Interactive Menu

---

## Future Improvements

- FUSE (Filesystem in Userspace) integration
- Persistent storage
- Multi-user authentication
- Stronger encryption
- Recursive directory listing
- File search functionality

---

## Author

**Abdullah Al Numan**
**Fahalullah Fahim**
**Minhaj Ahmed Chowdhury**
**Yasir Rahman**

Operating Systems Project
