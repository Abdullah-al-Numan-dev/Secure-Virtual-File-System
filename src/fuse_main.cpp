#define FUSE_USE_VERSION 31

#include <fuse3/fuse.h>
#include <cstring>
#include <cerrno>
#include "filesystem.h"

FileSystem fs;
// Return file/directory information
static int secure_getattr(const char *path, struct stat *stbuf,
                          struct fuse_file_info *fi)
{
    (void) fi;

    memset(stbuf, 0, sizeof(struct stat));

    // Root directory
    if (strcmp(path, "/") == 0)
    {
        stbuf->st_mode = S_IFDIR | 0755;
        stbuf->st_nlink = 2;
        return 0;
    }

    // One test file
Inode *inode = fs.getInode(path);

if (inode == nullptr)
{
    return -ENOENT;
}

if (inode->isDirectory)
{
    stbuf->st_mode = S_IFDIR | 0755;
    stbuf->st_nlink = 2;
}
else
{
    stbuf->st_mode = S_IFREG | 0644;
    stbuf->st_nlink = 1;
    stbuf->st_size = inode->fileSize;
}

return 0;

    return -ENOENT;
}

// List files inside the directory
static int secure_readdir(const char *path,
                          void *buf,
                          fuse_fill_dir_t filler,
                          off_t offset,
                          struct fuse_file_info *fi,
                          enum fuse_readdir_flags flags)
{
    (void) offset;
    (void) fi;
    (void) flags;

    filler(buf, ".", NULL, 0, FUSE_FILL_DIR_DEFAULTS);
    filler(buf, "..", NULL, 0, FUSE_FILL_DIR_DEFAULTS);

    std::vector<std::string> paths = fs.getAllPaths();

    std::string current(path);

    for (const auto &fullPath : paths)
    {
        // Root directory
        if (current == "/")
        {
            if (fullPath.find('/', 1) == std::string::npos)
            {
                filler(buf,
                       fullPath.substr(1).c_str(),
                       NULL,
                       0,
                       FUSE_FILL_DIR_DEFAULTS);
            }
        }
        else
        {
            // Child of current directory
            if (fullPath.find(current + "/") == 0)
            {
                std::string remain = fullPath.substr(current.length() + 1);

                // Only direct children
                if (remain.find('/') == std::string::npos)
                {
                    filler(buf,
                           remain.c_str(),
                           NULL,
                           0,
                           FUSE_FILL_DIR_DEFAULTS);
                }
            }
        }
    }

    return 0;
}
// Open file
static int secure_open(const char *path, struct fuse_file_info *fi)
{
    (void) fi;

    if (!fs.exists(path))
    {
        return -ENOENT;
    }

    return 0;
}
// Read file
static int secure_read(const char *path,
                       char *buf,
                       size_t size,
                       off_t offset,
                       struct fuse_file_info *fi)
{
(void) fi;

// Get file content from our FileSystem
std::string content = fs.readFile(path);

// If readFile returned an error
if (content.rfind("Error:", 0) == 0)
{
    return -ENOENT;
}

size_t len = content.size();

if ((size_t)offset >= len)
{
    return 0;
}

if (offset + size > len)
{
    size = len - offset;
}

memcpy(buf, content.c_str() + offset, size);

return size;
}

// Register callbacks
static struct fuse_operations operations;

int main(int argc, char *argv[])
{
    operations.getattr = secure_getattr;
    operations.readdir = secure_readdir;
    operations.open    = secure_open;
    operations.read    = secure_read;

    // Create some sample data
    fs.createDirectory("/Documents");
    fs.createFile("/Documents/report.txt");
    fs.writeFile("/Documents/report.txt", "Hello from SecureVFS!");

    return fuse_main(argc, argv, &operations, NULL);
}
