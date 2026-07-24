#include <iostream>
#include "filesystem.h"

using namespace std;

int main()
{
    FileSystem fs;

    int choice;

    while (true)
    {
        cout << "\n============================================\n";
        cout << "      Secure Virtual File System\n";
        cout << "============================================\n";

        cout << "1. Create File\n";
        cout << "2. Create Directory\n";
        cout << "3. Write File\n";
        cout << "4. Read File\n";
        cout << "5. Delete File\n";
        cout << "6. Delete Directory\n";
        cout << "7. Change Permissions\n";
        cout << "8. List Files\n";
        cout << "9. Exit\n";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
		case 1:
		{
		    string path;

		    cout << "\nEnter file path: ";
		    cin >> path;

		    if (fs.createFile(path))
		    {
		        cout << "File created successfully.\n";
		    }
		    else
		    {
		        cout << "Error: File already exists.\n";
		    }

		    break;
		}
case 2:
{
    string path;

    cout << "\nEnter directory path: ";
    cin >> path;

    if (fs.createDirectory(path))
    {
        cout << "Directory created successfully.\n";
    }
    else
    {
        cout << "Error: Directory already exists.\n";
    }

    break;
}	
case 3:
{
    string path;
    string data;

    cout << "\nEnter file path: ";
    cin >> path;

    cin.ignore();

    cout << "Enter file content: ";
    getline(cin, data);

    if (fs.writeFile(path, data))
    {
        cout << "File written successfully.\n";
    }
    else
    {
        cout << "Failed to write file.\n";
    }

    break;
}
case 4:
{
    string path;

    cout << "\nEnter file path: ";
    cin >> path;

    cout << "\nFile Content:\n";
    cout << fs.readFile(path) << endl;

    break;
}
case 5:
{
    string path;

    cout << "\nEnter file path: ";
    cin >> path;

    if (fs.deleteFile(path))
    {
        cout << "File deleted successfully.\n";
    }
    else
    {
        cout << "Failed to delete file.\n";
    }

    break;
}
case 6:
{
    string path;

    cout << "\nEnter directory path: ";
    cin >> path;

    if (fs.deleteDirectory(path))
    {
        cout << "Directory deleted successfully.\n";
    }
    else
    {
        cout << "Failed to delete directory.\n";
    }

    break;
}
case 7:
{
    string path;
    string permissions;

    cout << "\nEnter file path: ";
    cin >> path;

    cout << "Enter new permissions (r, rw, rx, rwx): ";
    cin >> permissions;

    if (fs.changePermissions(path, permissions))
    {
        cout << "Permissions updated successfully.\n";
    }
    else
    {
        cout << "Failed to update permissions.\n";
    }

    break;
}
            case 8:
                fs.listFiles();
                break;

            case 9:
                cout << "\nThank you for using Secure Virtual File System.\n";
                return 0;

            default:
                cout << "\nInvalid choice.\n";
        }
    }
}
