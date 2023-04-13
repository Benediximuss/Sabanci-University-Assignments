#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

struct Record
{
    char gender;
    char* name;
    char* surname;
};

void clearEscape(char* sptr) { // clears the escape sequences of the string i.e: "ls -l\r\n" -> "ls -l" 
    int i = strlen(sptr)-1;
    while(sptr[i] == '\r' || sptr[i] == '\n' || sptr[i] ==  ' ') {
        sptr[i] = '\0';
        i--;
    }
}

int countLinesinFile(char* fileName)
{
    FILE* fptr;
    if ((fptr = fopen(fileName, "r")) == NULL)
    {
        printf("Error! Could not open the DATABASE file!\n");
        exit(1);       
    }

    char line[128];
    int counter = 0;
    while (fgets(line, sizeof(line), fptr) != NULL)
    {
        counter++;
    }

    fclose(fptr);
    
    return counter;
}

void createDatabase(struct Record* db, char* fileName)
{
    FILE *dbPtr;

    if ( (dbPtr = fopen(fileName,"r")) == NULL ) {
        printf("Error! Could not open the DATABASE file!\n");
        exit(1);
    }

    char line[128];
    int lineNo = 0;
    while (fgets(line, sizeof(line), dbPtr) != NULL)
    {
        clearEscape(line);

        char* token = strtok(line, " ");

        struct Record tempRecord;

        int k = 0;
        while (token != NULL) {
            if (k == 0)
            {
                tempRecord.gender = strdup(token)[0];
            }
            else if (k == 1)
            {
                tempRecord.name = strdup(token);
            }
            else if (k == 2)
            {
                tempRecord.surname = strdup(token);
            }

            token = strtok(NULL, " ");
            k++;
        }

        db[lineNo] = tempRecord;
        lineNo++;
    }   

    fclose(dbPtr);
}

void correctFile(char* fileName, struct Record* db, int* dbSize)
{    
    FILE* targetFile;

    if ((targetFile = fopen(fileName,"r+")) == NULL) {
        printf("Error! Could not open the TARGET file!\n");
        exit(1);
    }

    char word[100];
    struct Record* temp = NULL;
    int status = 0; // 0 = no record, 1 = gender passed, 2 = name passed, 3 = surname passed

    while(fscanf(targetFile, "%s", word) > 0)
    {
        if (status == 0)
        {
            if (strcmp(word, "Mr.") == 0 || strcmp(word, "Ms.") == 0)
            {
                status = 1;
            }
        }

        else if (status == 1)
        {
            int isFound = 0;

            for (int i = 0; i < *dbSize; i++)
            {
                if (strcmp(word, db[i].name) == 0)
                {
                    temp = &db[i];
                    isFound = 1;
                    break;
                }
            }

            if (isFound == 1)
            {
                status = 2;
            }
            else
            {
                status = 0;
            }          
        }

        else if (status == 2)
        {
            int surnameLen = strlen(word); 

            int nameLen = strlen(temp->name);
            int totalBack = surnameLen +  + nameLen + 5;

            fseek(targetFile, -1*totalBack, SEEK_CUR);

            char* pre;

            if (temp->gender == 'f')
            {
                pre = "Ms.";
            }
            else
            {
                pre = "Mr.";
            }

            fputs(pre, targetFile);

            fseek(targetFile, 2+nameLen, SEEK_CUR);

            fputs(temp->surname, targetFile);

            temp = NULL;
            status = 0;
        }
    }

    fclose(targetFile);
}

void scanDirectory(char* dirPath, struct Record* db, int* dbSize)
{
   DIR* dirptr;
   dirptr = opendir(dirPath);

   struct dirent* direnptr;
   struct stat sb;

    while ((direnptr = readdir(dirptr)) != NULL)
    {
        fstatat(dirfd(dirptr), direnptr->d_name, &sb, 0);

        if ((strcmp(direnptr->d_name, ".") != 0 && strcmp(direnptr->d_name, "..") != 0)) // if current is not "." or ".."
        {
            if (S_ISDIR(sb.st_mode)) // if current is a folder
            {
                char newDir[200];
                strcpy(newDir, dirPath);
                if (strcmp(dirPath, "./") != 0)
                {
                strcat(newDir, "/");
                }
                strcat(newDir, direnptr->d_name);

                scanDirectory(newDir, db, dbSize);
            }
            else // if current is a file
            {
                char* extension = strchr(direnptr->d_name, '.');

                if (extension != NULL && strcmp(extension, ".txt") == 0) // if current file is a txt file
                { 
                    if (strcmp(dirPath, "./") != 0 || strcmp(direnptr->d_name, "database.txt") != 0) // if current txt file is not the original database.txt file which is located in root directory
                    {
                        char newFileName[200];
                        
                        if (strcmp(dirPath, "./") == 0)
                        {
                            strcpy(newFileName, direnptr->d_name);
                        }
                        else
                        {
                            strcpy(newFileName, dirPath);
                            strcat(newFileName, "/");
                            strcat(newFileName, direnptr->d_name);
                        }

                        correctFile(newFileName, db, dbSize);
                    }
                }
            }
        }
    }

    closedir(dirptr);
}

int main() {

    int databaseSize = countLinesinFile("database.txt");
    struct Record* database = (struct Record*) malloc(databaseSize * sizeof(struct Record));

    createDatabase(database, "database.txt");
    scanDirectory("./", database, &databaseSize);

    free(database);

    return 0;
}