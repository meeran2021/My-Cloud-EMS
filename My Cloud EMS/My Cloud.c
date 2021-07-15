#include<stdio.h>



char pass[30];
FILE *fPtr;

struct CourseInfo
{
    char dgreName[15], brnchName[40], spclName[50], subName[50], subType[10];
    int subCode;
};

struct profInfo
{
    char profName[40], profSex[10], profMail[35], profQlfn[100];
    unsigned long long profMobNum;
};

struct studentInfo
{
    char stFstName[20], stLstName[20], stName[41], stSex[10], stMail[40], CurAdrs[100], PermAdrs[100];  
    unsigned long long stSysId, stMobNum;
};

struct parentsInfo
{
    char fthrName[40], mthrName[40], prntMail[40];
    unsigned long long ftrMobNum;
};


void passDB()
{
    char ch;
    fPtr=fopen("passDatabase.txt","r");
    if (fPtr==NULL)
    {
        printf("Can't Open File ");
        exit(1);
    }
    else
    {
        while (1) 
        {
            ch=fgetc(fPtr);
            if (ch==EOF)
            {
                printf("EOF reached");
                break;
            }

            else
            {
                printf("%c",ch);
            }


        }
    }
    fclose(fPtr);
    fPtr=NULL;

}


void passStrength(p)
{
    
    if strlen(p)==8

}

void main()
{
    printf("Enter Password\n ");
    scanf("%s",&pass);
    passStrength(pass);
}
