# 🗂️ Custom Virtual File System (CVFS)

## 📖 Project Overview

The **Custom Virtual File System (CVFS)** is an implementation of a simplified file system in **C/C++**.
It emulates the functionalities of a real operating system’s file system but stores all records in **primary memory (RAM)** — hence, it is called *virtual*.

The project provides a **console-based shell (Marvellous CVFS)** where users can interact using commands similar to a UNIX shell.

---

## ⚙️ Features

* **File Management**
  `creat`, `open`, `read`, `write`, `close`, `unlink`
* **Directory Management**
  `mkdir`, `rmdir`, `cd`, `ls`
* **Metadata Retrieval**
  `stat`, `fstat`, `chmod`, `find`
* **File Navigation**
  `lseek`
* **Utility Commands**
  `help`, `man`, `clear`, `exit`, `mkfs`

---

## 🛠️ Technologies Used

* **Programming Language**: C / C++
* **Compiler**: GCC / g++
* **Platform**: Windows / Linux terminal

---

## 🖥️ User Interface

* Console-based shell named **Marvellous CVFS**
* Accepts commands similar to **UNIX/Linux shell**
* Built-in **help** and **man pages**

---

## 🏗️ Project Architecture

### 📌 Disk Layout (Figure 1)

* **Boot Block** – Stores startup information
* **Super Block** – Tracks free & total inodes
* **Disk Inode List Block (DILB)** – Holds inodes (file metadata)
* **Data Blocks (DB)** – Stores actual file data

![Disk Layout](bootblock.png)

---

### 📌 File Handling Flow (Figure 2)

```
UAREA → File Table → Incore Inode Table → DILB → Data Blocks
```

![File Handling Flow](flow.png)

---

## 📂 Core Data Structures

### 🔹 BootBlock

* Stores information required to boot the CVFS.

### 🔹 SuperBlock

* Tracks free and total inodes.
* Fields:

  * `TotalInodes` → Max number of files/directories
  * `FreeInodes` → Available inodes

### 🔹 Inode (Index Node)

* Represents each file or directory.
* Fields:

  * `FileName`, `InodeNumber`
  * `FileSize` (default: 100 bytes)
  * `ActualFileSize` (current usage)
  * `FileType` (regular / directory)
  * `LinkCount`, `ReferenceCount`, `Permission`
  * `Buffer` → stores actual data
  * Directory inodes maintain parent/child/sibling references

### 🔹 FileTable

* Tracks open files and their offsets.
* Fields:

  * `ReadOffset`, `WriteOffset`
  * `Mode` (Read / Write / Read+Write)
  * `ptrinode` (pointer to inode)

### 🔹 UAREA (User Area)

* Represents process-level file management.
* Fields:

  * `ProcessName`, `CurrentDirectory`
  * `UFDT[]` → array of FileTables

---

## 📜 Supported Commands

| Command                         | Category  | Description                                                  |
| ------------------------------- | --------- | ------------------------------------------------------------ |
| `help`                          | Utility   | Displays list of available commands                          |
| `man <cmd>`                     | Utility   | Shows usage of a command                                     |
| `creat <filename> <permission>` | File Mgmt | Create file with permissions (1=Read, 2=Write, 3=Read+Write) |
| `open <filename> <mode>`        | File Mgmt | Open existing file in mode                                   |
| `close <fd>`                    | File Mgmt | Close an opened file                                         |
| `write <fd>`                    | File Mgmt | Write data to a file                                         |
| `read <fd> <size>`              | File Mgmt | Read bytes from a file                                       |
| `unlink <filename>`             | File Mgmt | Delete file                                                  |
| `ls`                            | File Mgmt | List files/directories                                       |
| `stat <filename>`               | File Mgmt | Show metadata of a file                                      |
| `fstat <fd>`                    | File Mgmt | Show metadata via file descriptor                            |
| `chmod <filename> <permission>` | File Mgmt | Change file permissions                                      |
| `lseek <fd> <offset> <whence>`  | File Mgmt | Modify file offsets                                          |
| `mkdir <dirname>`               | Dir Mgmt  | Create a directory                                           |
| `rmdir <dirname>`               | Dir Mgmt  | Remove a directory                                           |
| `cd <dirname>`                  | Dir Mgmt  | Change directory                                             |
| `find <filename>`               | Utility   | Search file in CVFS                                          |
| `clear`                         | Utility   | Clear console                                                |
| `exit`                          | Utility   | Save CVFS state & exit                                       |

---

## 📷 Demonstration (Screenshots)

1. Help & Exit
2. Create & List Files
3. Write & Read File
4. Stat & Fstat
5. Change Permissions
6. Lseek & Read
7. Close & Unlink
8. Directory Operations (`mkdir`, `cd`, `rmdir`)
9. Error Handling
10. Find File

---

## ▶️ How to Run

1. **Compile the program**

   ```bash
   g++ CVFS.cpp -o cvfs
   ```

2. **Run the executable**

   ```bash
   ./cvfs
   ```

3. **Start using commands**

   ```bash
   Marvellous CVFS :> help
   Marvellous CVFS :> creat demo.txt 3
   Marvellous CVFS :> write 0
   Marvellous CVFS :> read 0 50
   Marvellous CVFS :> ls
   ```

---

## ✅ Example Session

```
Marvellous CVFS :> help
Available Commands:
creat, open, read, write, close, unlink,
mkdir, rmdir, cd, ls, stat, fstat, chmod,
find, lseek, man, clear, exit

Marvellous CVFS :> creat test.txt 3
File created successfully.

Marvellous CVFS :> ls
File Name : test.txt  Inode Number : 1  Size : 0  Type : Regular
```

---

## 👨‍💻 Author

**Name**: Shreyas Prakash Thorat


---
