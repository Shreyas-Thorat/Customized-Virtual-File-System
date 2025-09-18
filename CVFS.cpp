//////////////////////////////////////////////////////////
//
//    Header Files Inclusion
//
//////////////////////////////////////////////////////////

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
//#include<unistd.h>
#include<string.h>
#include<stdbool.h>

using namespace std;

//////////////////////////////////////////////////////////
//
//   Structure Name : User Defined Macros
//
//////////////////////////////////////////////////////////

//Max File Size 
#define MAXFILESIZE 100   

// Maximum Number of File that we can create
#define MAXINODE 5     

// Maximum Number of Files that we can open             
#define MAXOPENEDFILES 20           

#define READ 1
#define WRITE 2
#define EXECUTE 4

#define REGULARFILE 1
#define SPECIALFILE 2

#define START 0
#define CURRENT 1
#define END 2

#define EXECUTE_SUCCESS 0

//////////////////////////////////////////////////////////
//
//   Structure Name : User Defined Macros for Error Handling
//
//////////////////////////////////////////////////////////

#define ERR_INVALID_PARAMETER -1
#define ERR_NO_INODES -2
#define ERR_FILE_ALREADY_EXISTS -3
#define ERR_FILE_NOT_EXIST -4
#define ERR_PERMISSION_DENIED -5
#define ERR_INSUFFICIENT_SPACE -6
#define ERR_INSUFFICIENT_DATA -7

//////////////////////////////////////////////////////////
//
//   Structure Name : BootBlock
//   Description   : Holds the Information to Boot the Operating System 
//
//////////////////////////////////////////////////////////

struct BootBlock
{
    char Information[100];

};

//////////////////////////////////////////////////////////
//
//   Structure Name : SuperBlock
//   Description   : Holds the Information about the File System 
//
//////////////////////////////////////////////////////////

struct SuperBlock
{
    int TotalInodes;
    int FreeInodes;

};

//////////////////////////////////////////////////////////
//
//   Structure Name : INode
//   Description   : Holds Information about the File 
//
//////////////////////////////////////////////////////////

typedef struct Inode
{
    char FileName[50];
    int InodeNumber;
    int FileSize;
    int ActualFileSize;
    int FileType;
    int RefrenceCount;
    int Permission;
    int LinkCount;
    char * Buffer;
    struct Inode * next;
}INODE,*PINODE,**PPINODE;

//////////////////////////////////////////////////////////
//
//   Structure Name : FIleTable
//   Description   : Holds the Information about the Opened File System 
//
//////////////////////////////////////////////////////////

typedef struct FileTable
{
    int ReadOffset;
    int WriteOffset;
    int Count;
    int Mode;
    PINODE ptrinode;

}FILETABLE, *PFILETABLE;

//////////////////////////////////////////////////////////
//
//   Structure Name : UAREA
//   Description   : Holds the Information about the Process
//
//////////////////////////////////////////////////////////

struct UAREA
{
    char ProcessName[50];
    PFILETABLE UFDT[MAXOPENEDFILES];
};

//////////////////////////////////////////////////////////
//
//   Global Variables or Objects used in the Project
//
//////////////////////////////////////////////////////////

SuperBlock superobj;
PINODE head = NULL;
UAREA uareaobj;
BootBlock bootboj;

//////////////////////////////////////////////////////////
//
//   Function Name : InitializeUAREA
//   Description   : It is used to Initialize the contents of UAREA
//   Author        : Shreyas Prakash Thorat
//   Date          : 10/08/2025
//////////////////////////////////////////////////////////

void InitializeUAREA()
{
    strcpy(uareaobj.ProcessName , "Myexe");

    int i = 0;

    while(i < MAXOPENEDFILES)
    {
        uareaobj.UFDT[i] = NULL;
        i++;
    }
    cout<<"Marvellous CVFS : UAREA Initialised Sucessfully\n";

}



//////////////////////////////////////////////////////////
//
//   Function Name : InitializeSuperBlock
//   Description   : Holds the Information about the Process
//   Author        : Shreyas Prakash Thorat
//   Date          : 10/08/2025
//////////////////////////////////////////////////////////

void InitializeSuperBlock()
{
    superobj.TotalInodes = MAXINODE;
    superobj.FreeInodes = MAXINODE;

    cout<<"Marvellous CVFS : SuperBlock Initialised Sucessfully\n";
}

//////////////////////////////////////////////////////////
//
//   Function Name : CreateDILB
//   Description   : Used to Create LinkedList of Inodes
//   Author        : Shreyas Prakash Thorat
//   Date          : 10/08/2025
//////////////////////////////////////////////////////////

void CreateDILB()
{
    int i = 1;
    PINODE newn =  NULL;
    PINODE temp = head;

    while(i <= MAXINODE)
    {
        newn = new INODE;

        newn -> InodeNumber = i;
        newn -> FileSize = 0;
        newn -> ActualFileSize = 0;
        newn -> LinkCount = 0;
        newn -> Permission = 0;
        newn -> Buffer = NULL;
        newn -> next = NULL;
        newn -> FileType = 0;
        newn -> RefrenceCount = 0;

        if(temp == NULL)
        {
            head = newn;
            temp = head;
        }
        else
        {
            temp -> next = newn;
            temp = temp -> next;
        }

        i++;
    }

    cout<<"Marvellous CVFS : DILB Created Sucessfully\n";

}


//////////////////////////////////////////////////////////
//
//   Function Name : StartAuxiliaryDataInitialization
//   Description   : Used to Initialize the Auxiliary Data
//   Author        : Shreyas Prakash Thorat
//   Date          : 10/08/2025
//////////////////////////////////////////////////////////

void StartAuxiliaryDataInitialization()
{
 
    strcpy(bootboj.Information , "Boot Process of Operating System Done");

    cout<<bootboj.Information<<"\n";    

    InitializeSuperBlock();

    InitializeUAREA();

    CreateDILB();

    cout<<"Marvellous CVFS : Auxiliary Data Initialised Sucessfully\n";

}

//////////////////////////////////////////////////////////
//
//   Function Name : DisplayHelp
//   Description   : Used to Display the Information about the Commands
//   Author        : Shreyas Prakash Thorat
//   Date          : 11/08/2025
//////////////////////////////////////////////////////////

void DisplayHelp()
{
    printf("-----------------------------------------------------------------------------------\n");
    printf("---------------- Command Manual of Marvellous CVFS --------------------------------\n");
    printf("-----------------------------------------------------------------------------------\n");

    printf("man     : It is Used to Display the specific manual page of Command\n");
    printf("exit    : It is Used to Terminate the Shell of Marvellous CVFS\n");
    printf("clear   : It is used to Clear the Comsole of Marvellous CVFS\n");
    printf("creat   : It is Used to Create new Regulr File\n");
    printf("unlink  : it is Used to Delete the Existing File \n");
    printf("stat    : It is Used to Display the Statistical Information of the File\n");
    printf("ls      : Is is used to list out all the Files from the Directory\n");
    printf("write   : It is Used to Write the Data into the File \n");
    printf("Read    : It is Used to Read the Data from the File\n");

    // Add more Options here

    printf("-----------------------------------------------------------------------------------\n");
    
}


//////////////////////////////////////////////////////////
//
//   Function Name : ManPage
//   Description   : Used to Display the Manual Page of the Commands
//   Input         : It Accepts the Command Name
//   Output        : Displays the Manual Details of the Command 
//   Author        : Shreyas Prakash Thorat
//   Date          : 11/08/2025
//////////////////////////////////////////////////////////

void ManPage
        (
            char * name // Name of Command
        )
{
    if(strcmp(name,"creat") == 0)
    {
        printf("Description : This Command is used to Create New Regular File on our File System\n");
        printf("Usage       : creat file_Name Permissions \n");
        printf("File_Name   : Name of File that you want to Create \n");
        printf("Permissions : \n1 : Read  \n2 : Write  \n3 : Read + Write \n");
    }

    else if(strcmp(name,"exit") == 0)
    {
        printf("Description : This Command is used to Terminate Marvellous CVFS\n");
        printf("Usage : exit\n");
       
    }

    else if(strcmp(name,"unlink") == 0)
    {
        printf("Description : This Command is used to Delete New Regular File from our File System\n");
        printf("Usage       : unlink file_Name  \n");
        printf("File_Name   : Name of File that you want to Delete \n");
    }

    else if(strcmp(name,"stat") == 0)
    {
        printf("Description : This Command is used to Display Statistical Information about the File\n");
        printf("Usage       : stat file_Name  \n");
        printf("File_Name   : Name of File whose information that you want to Display \n");
    }

    else if(strcmp(name,"ls") == 0)
    {
        printf("Description : This Command is used to All the File Names from the Directory\n");
        printf("Usage       : ls \n");
    }

    else if(strcmp(name,"write") == 0)
    {
        printf("Description : This Command is used to Write the Data into the File\n");
        printf("Usage       : write File_Descriptor \n");
    }

    else if(strcmp(name,"read") == 0)
    {
        printf("Description      : This Command is used to Read the Data from the File\n");
        printf("Usage            : write File_Descriptor Size\n");
        printf("File_Descriptor  : Its A Value Returned by Create System call\n");
        printf("Size             : Number of Bytes you want to read\n");

    }
    // Add more Options here

    else
    {
        printf("No Manual Entry for %s\n",name);
    }
}

//////////////////////////////////////////////////////////
//
//   Function Name : IsFileExists
//   Description   : It is used to Check whether the Given File name Exists or not
//   Input         : It Accepts the File Name 
//   Output        : It Returns the Boolean Value ( True : if Present , False : if not Present )
//   Author        : Shreyas Prakash Thorat
//   Date          : 11/08/2025
//////////////////////////////////////////////////////////

bool IsFileExists
        (
            char * name // Name of File that we want to Check
        )
{
    bool bFlag = false;
    PINODE temp = head;

    while(temp != NULL)
    {
        if((strcmp(name,temp -> FileName) == 0) && (temp -> FileType == REGULARFILE))
        {
            bFlag = true;
            break;
        }

        temp  = temp -> next;
        
    }

    return bFlag;
}


//////////////////////////////////////////////////////////
//
//   Function Name : CreateFile
//   Description   : It is used to create a new Regular File
//   Input         : It Accepts the File Name and Permission
//   Output        : It Returns the File Descriptor
//   Author        : Shreyas Prakash Thorat
//   Date          : 11/08/2025
//////////////////////////////////////////////////////////

int CreateFile
            (
                char * name , // Name of File
                int permission // Permission to Create File
            )
{   
    PINODE temp = head;
    int i = 0;

    printf("Current inodes remaining : %d\n",superobj.FreeInodes);
    //Filters

    // If File Name is Missing
    if(name  == NULL )
    {
        return ERR_INVALID_PARAMETER;
    }

    // If Entered Permission is Invalid
    if(permission < 1 || permission > 3)
    {
        return ERR_INVALID_PARAMETER;
    }

    // Check weather empty INode is there or not

    if(superobj.FreeInodes == 0)
    {
        return ERR_NO_INODES;
    }

    // Check weather File already Exists or Not

    if(IsFileExists(name))
    {
        return ERR_FILE_ALREADY_EXISTS;
    }
    
    // Loop to Search free inode

    while(temp != NULL)
    {
        if(temp -> FileType == 0)
        {
            break;
        }
        temp = temp -> next;
    }


    // inode not Found
    if(temp == NULL)
    {
        printf("Inode Not Found\n");
        return ERR_NO_INODES;
    }

    // Search First Non Null value From UFDT

    for(i = 0; i < MAXINODE ; i++)
    {
        if(uareaobj.UFDT[i] == NULL)
        {
            break;
        }
    }

    if(i == MAXINODE)
    {
        printf("Unable to Create File as MAX OPENED FILE LIMIT REACHED\n");
        return -1;
    }

    // Allocate Memory for File Table
    uareaobj.UFDT[i] = (PFILETABLE)malloc(sizeof(FileTable));

    //Initialize Elements of File Table
    uareaobj.UFDT[i] -> Count = 1;
    uareaobj.UFDT[i] -> ReadOffset = 0;
    uareaobj.UFDT[i] -> WriteOffset = 0;
    uareaobj.UFDT[i] -> Mode = permission;

    // Connect File Table with IIT
    uareaobj.UFDT[i] -> ptrinode = temp;

    strcpy(uareaobj.UFDT[i] -> ptrinode -> FileName,name);
    uareaobj.UFDT[i] -> ptrinode -> FileSize = MAXFILESIZE;
    uareaobj.UFDT[i] -> ptrinode -> ActualFileSize = 0;
    uareaobj.UFDT[i] -> ptrinode -> FileType  = REGULARFILE;
    uareaobj.UFDT[i] -> ptrinode -> RefrenceCount = 1;
    uareaobj.UFDT[i] -> ptrinode -> LinkCount = 1;
    uareaobj.UFDT[i] -> ptrinode -> Permission = permission;

    // Allocate Memory for Buffer

    uareaobj.UFDT[i] -> ptrinode -> Buffer = (char *)malloc(MAXFILESIZE);

    // Decrement the Number of Freee inodes by 1
    superobj.FreeInodes -- ;

    return i;

}


//////////////////////////////////////////////////////////
//
//   Function Name : UnlinkFile
//   Description   : It is used to delete a new Regular File
//   Input         : It Accepts the File Name
//   Output        : It Returns Nothing
//   Author        : Shreyas Prakash Thorat
//   Date          : 15/08/2025
//////////////////////////////////////////////////////////

// Marvellous CVFS > unlink Demo.txt
int UnlinkFile
                (
                char * name  // Name oF file
                )
{
    int i = 0;
    if(name == NULL)
    {
        return ERR_INVALID_PARAMETER;
    }

    if(IsFileExists(name) == false)
    {
        return ERR_FILE_NOT_EXIST;
    }

    for(i = 0; i < MAXINODE; i++)
    {
        if(uareaobj.UFDT[i] != NULL)
        {
            if(strcmp(uareaobj.UFDT[i] -> ptrinode -> FileName, name) == 0)
            {
                // Deallocate the Memory of the Buffer
                free(uareaobj.UFDT[i] ->ptrinode -> Buffer);


                // Reset all values of inode
                uareaobj.UFDT[i] -> ptrinode -> FileSize = 0;
                uareaobj.UFDT[i] -> ptrinode -> ActualFileSize = 0;
                uareaobj.UFDT[i] -> ptrinode -> LinkCount = 0;
                uareaobj.UFDT[i] -> ptrinode -> Permission = 0;
                uareaobj.UFDT[i] -> ptrinode -> FileType = 0;
                uareaobj.UFDT[i] -> ptrinode -> RefrenceCount = 0;

                // Deaalocate memory of File Table
                free(uareaobj.UFDT[i]);

                // Set NULL to UFDT member
                uareaobj.UFDT[i] = NULL;

                // Increment the value of Free inodes Count
                superobj.FreeInodes ++;

                break;
            } // End of if
        }// End of if
    } // End of for Loop

    return EXECUTE_SUCCESS;
}

//////////////////////////////////////////////////////////
//
//   Function Name : ls_File
//   Description   : It is used to Display the Information of all the Files in the Directory
//   Input         : Nothing
//   Output        : Nothing
//   Author        : Shreyas Prakash Thorat
//   Date          : 15/08/2025
//////////////////////////////////////////////////////////

// Marvellous CVFS > ls

void ls_file()
{
    PINODE temp = head;

    while(temp != NULL)
    {
        if(temp -> FileType != 0)
        {
            printf("%s\n",temp -> FileName);
        }
        
        temp = temp -> next;
    }
}

//////////////////////////////////////////////////////////
//
//   Function Name : stat_File
//   Description   : It is used to Display the Information about the Given File
//   Input         : File_Name
//   Output        : Nothing
//   Author        : Shreyas Prakash Thorat
//   Date          : 15/08/2025
//////////////////////////////////////////////////////////

// Marvellous CVFS > stat File_Name

int stat_File
                (
                char * name  // Name oF file
                )
{
    PINODE temp = head;
    if(name == NULL)
    {
        return ERR_INVALID_PARAMETER;
    }

    if(IsFileExists(name) == false)
    {
        return ERR_FILE_NOT_EXIST;
    }

    while(temp != NULL)
    {
        if((strcmp(temp -> FileName,name)) == 0 && (temp -> FileType != 0))
        {
            printf("-------------- Statistical Information of File ---------------\n");
            
            printf("File Name           : %s\n",temp ->FileName);
            printf("File Size on Disk   : %d bytes\n",temp -> FileSize);
            printf("Actual File Size    : %d bytes\n",temp ->ActualFileSize);
            printf("Link Count          : %d\n",temp ->LinkCount);
            printf("File Permission     : ");
            if(temp -> Permission == READ)
            {
                printf("Read\n");
            }

            else if (temp -> Permission == WRITE)
            {
                printf("Write\n");
            }

            else if(temp -> Permission == READ + WRITE)
            {
                printf("Read + Write \n");
            }

            printf("File Type           : ");
            if(temp -> FileType == REGULARFILE)
            {
                printf("Regular File \n");
            }

            else if(temp -> FileType == SPECIALFILE)
            {
                printf("Special File \n");
            }

            printf("---------------------------------------------------------------\n");
        }

        temp = temp -> next;
    }
    

    return EXECUTE_SUCCESS;
}

//////////////////////////////////////////////////////////
//
//   Function Name : write_File
//   Description   : It is used write the Contents into the File 
//   Input         : File Descriptor 
//                   Address of Buffer which Contains Data
//                   Size of data that we want to write
//   Output        : Number of Bytes that we want to write
//   Author        : Shreyas Prakash Thorat
//   Date          : 15/08/2025
//////////////////////////////////////////////////////////

// Marvellous CVFS > write 3 

int write_File
            (
                int fd ,    // File Descriptor of the File
                char *data, // Data that we want to Write
                int size    // Size of data that we want to write
            )

{   unsigned long int offset = 0;
    printf("File Descriptor is                     : %d\n",fd);
    printf("Data That we want to Write             : %s\n",data);
    printf("Number of Bytes that we want to Write  : %d\n",size);


    // Invalid Value of FD
    if(fd < 0 || fd > MAXOPENEDFILES)
    {
        return ERR_INVALID_PARAMETER;
    }

    // File is Not Opened or Created with the Given FD
    if(uareaobj.UFDT[fd] == NULL)
    {
        return ERR_FILE_NOT_EXIST;
    }


    // If there is no Prmission to Write the Data into the File
    if(uareaobj.UFDT[fd] -> ptrinode -> Permission < WRITE)
    {
        return ERR_PERMISSION_DENIED;
    }

    // Unable to Write as tere is no Sufficient Space
    if((MAXFILESIZE - uareaobj.UFDT[fd] -> WriteOffset)  < size)
    {
        return ERR_INSUFFICIENT_SPACE;
    }

    // Write the Actual Data
    strncpy(uareaobj.UFDT[fd] -> ptrinode -> Buffer +  uareaobj.UFDT[fd] -> WriteOffset,data,size);

    // Update the write offset
    uareaobj.UFDT[fd] -> WriteOffset = uareaobj.UFDT[fd] ->WriteOffset + size;

    //update the Actual Size after writing the new data
    uareaobj.UFDT[fd] -> ptrinode -> ActualFileSize = uareaobj.UFDT[fd] -> ptrinode -> ActualFileSize + size;

    return size;
}

//////////////////////////////////////////////////////////
//
//   Function Name : read_File
//   Description   : It is used read the Contents from the File 
//   Input         : File Descriptor 
//                   Address of  Empty Buffer which Contains Data
//                   Size of data that we want to read
//   Output        : Number of Bytes Sucessfully Read from the File
//   Author        : Shreyas Prakash Thorat
//   Date          : 15/08/2025
//////////////////////////////////////////////////////////

// Marvellous CVFS > read 3 10

int read_File(
                int fd,          // File Descriptor
                char * data,    // Address of Empty Buffer
                int size        // Number of Bytes that we want to read
            )
{
    // Invalid Value of FD
    if(fd < 0 || fd > MAXOPENEDFILES)
    {
        return ERR_INVALID_PARAMETER;
    }

    if(data == NULL || size <= 0)
    {
        return ERR_INVALID_PARAMETER;
    }

    // File is Not Opened or Created with the Given FD
    if(uareaobj.UFDT[fd] == NULL)
    {
        return ERR_FILE_NOT_EXIST;
    }


    // If there is no Permission to Write the Data into the File
    if(uareaobj.UFDT[fd] -> ptrinode -> Permission < READ)
    {
        return ERR_PERMISSION_DENIED;
    }

    // Unable to Read as there is no Sufficient data
    if((MAXFILESIZE - uareaobj.UFDT[fd] -> ReadOffset)  < size)
    {
        return ERR_INSUFFICIENT_DATA;
    }

    strncpy(data,uareaobj.UFDT[fd] -> ptrinode -> Buffer + uareaobj.UFDT[fd] -> ReadOffset,size);

    uareaobj.UFDT[fd] -> ReadOffset = uareaobj.UFDT[fd] -> ReadOffset + size;

    return size;
}

//////////////////////////////////////////////////////////
//
//    Entry Point Function (main)
//
//////////////////////////////////////////////////////////


int main()
{
    char str[80] = {'\0'};
    int iCount = 0;
    char Command[5] [80];
    int iRet = 0;
    char InputBuffer[MAXFILESIZE] = {'\0'};
    char * EmptyBuffer = NULL;

    StartAuxiliaryDataInitialization();

    cout<<"-----------------------------------------------------------------------------------\n";
    cout<<"-------------------- Marvellous CVFS Started Sucessfully --------------------------\n";
    cout<<"-----------------------------------------------------------------------------------\n";

    while(1)  
    {
        fflush(stdin);

        strcpy(str,"");

        printf("\nMarvellous CVFS > ");
        fgets(str,sizeof(str),stdin);

        iCount = sscanf(str, "%s %s %s %s", Command[0],Command[1],Command[2],Command[3]);

        if(iCount == 1)
        {
            // Marvellous CVFS > exit
            if(strcmp(Command[0],"exit") == 0)
            {
                printf("Thank You For Using Marvellous CVFS \n");
                printf("Deallocating all the resources...\n");
                break;
            }

            // Marvellous CVFS > help
            else if(strcmp(Command[0],"help") == 0)
            {
                DisplayHelp();
            }

            // Marvellous CVFS > clear
            else if(strcmp(Command[0],"clear") == 0)
            {
                system("cls");
            }

            // Marvellous CVFS > ls
            else if(strcmp(Command[0],"ls") == 0)
            {
                ls_file();
            }

            else
            {
                printf("Command Not Found...\n");
                printf("Please Refer help option or use man Command\n");
            }



        } // End of if iCount == 1

        else if(iCount == 2)
        {
            // Marvellous CVFS > man Creat
            if(strcmp(Command[0],"man") == 0)
            {
                ManPage(Command[1]);
            }

            else if(strcmp(Command[0],"unlink") == 0)
            {
                iRet = UnlinkFile(Command[1]);

                if(iRet == EXECUTE_SUCCESS)
                {
                    printf("Unlink Operation is Sucessfully Performed \n");
                }

                else if(iRet == ERR_FILE_NOT_EXIST)
                {
                    printf("Error : Unable to do Unlink activity as file is not present \n");
                }

                else if(iRet == ERR_INVALID_PARAMETER)
                {
                    printf("Error : Invalid Parameters \n");
                }
            }
            // Marvellous CVFS > stat Demo.txt
            else if(strcmp(Command[0],"stat") == 0)
            {
                iRet = stat_File(Command[1]);


                if(iRet == ERR_FILE_NOT_EXIST)
                {
                    printf("Error : Unable to display Statictics activity as file is not present \n");
                }

                else if(iRet == ERR_INVALID_PARAMETER)
                {
                    printf("Error : Invalid Parameters \n");
                }
            }

            // Marvellous CVFS > write 3
            else if(strcmp(Command[0],"write") == 0)
            {
                printf("Please Enter the Data that you want to write in the File : \n");
                fgets(InputBuffer,MAXFILESIZE,stdin);

                iRet = write_File(atoi(Command[1]), InputBuffer, strlen(InputBuffer)-1);

                if(iRet == ERR_INSUFFICIENT_SPACE)
                {
                    printf("Error : Insufficient space in the Data Block of the File \n");
                }

                else if(iRet == ERR_PERMISSION_DENIED)
                {
                    printf("Error : Unable to write as there is no Write permission\n");
                }

                else if(iRet == ERR_FILE_NOT_EXIST)
                {
                    printf("Error : FD is Invalid \n");
                }

                else if(iRet == ERR_INVALID_PARAMETER)
                {
                    printf("Error : Invalid Parameters \n");
                }

                else
                {
                    printf("%d Bytes gets Sucessfully written into the File \n",iRet);
                    printf("Data From File is : %s\n",uareaobj.UFDT[0] ->ptrinode -> Buffer);
                }
            }

            else
            {
                printf("Command Not Found...\n");
                printf("Please Refer help option or use man Command\n");
            }
        } // End of if iCount == 2

        else if(iCount == 3)
        {
            // Marvellous CVFS > Creat Ganesh.txt 3
            if(strcmp(Command[0],"creat") == 0)
            {
                iRet = CreateFile(Command[1],atoi(Command[2]));

                if(iRet == ERR_INVALID_PARAMETER)
                {
                    printf("Error : Invalid Parameters for the function\n");
                    printf("Please Check ManPage for more details\n");
                }
                else if(iRet == ERR_NO_INODES)
                {
                    printf("Error : Unable to Create File as there is no INodes\n");
                }

                else if(iRet == ERR_FILE_ALREADY_EXISTS)
                {
                    printf("Error : Unable to Create File as File Already Exists\n");
                }

                else
                {
                    printf("File is SucessFully Created with FD : %d\n",iRet);
                }
            }

            // Marvellous CVFS > read 3 10
            else if(strcmp(Command[0],"read") == 0)
            {
                EmptyBuffer = (char *)malloc(sizeof(sizeof(atoi(Command[2]))));

                iRet = read_File(atoi(Command[1]),EmptyBuffer,atoi(Command[2]));

                if(iRet == ERR_INSUFFICIENT_DATA)
                {
                    printf("Error : Insufficient data in the Data Block of the File \n");
                }

                else if(iRet == ERR_PERMISSION_DENIED)
                {
                    printf("Error : Unable to read as there is no read permission\n");
                }

                else if(iRet == ERR_FILE_NOT_EXIST)
                {
                    printf("Error : FD is Invalid \n");
                }

                else if(iRet == ERR_INVALID_PARAMETER)
                {
                    printf("Error : Invalid Parameters \n");
                }

                else
                {
                    printf("Read Operation is Sucessful\n");
                    printf("Data From the File is : %s\n",EmptyBuffer);

                    free(EmptyBuffer);
                }

            }
            
            else
            {
                printf("Command Not Found...\n");
                printf("Please Refer help option or use man Command\n");
            }

        } // End of if iCount == 3

        else if(iCount == 4)
        {

            
        } // End of if iCount == 4

        else
        {
            printf("Command Not Found...\n");
            printf("Please Refer help option or use man Command\n");
        } // End of Invalid Command Part


    } // End of While(Custom Shell)

 
    return 0;
} // End of Main