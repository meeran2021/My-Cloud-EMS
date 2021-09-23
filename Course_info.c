#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
int choice;    // Used as an argument in getUserType() function.
char pass[30]; // To store password of user.
FILE *fPtr;    // To store returned address of fopen function.

struct CourseInfo // To store Course Info.
{
    char dgreName[30], brnchName[40], spclName[50], subName[50], subType[10],profName[40];
    int subCode, year;
    float subCredit;
} info, cInfo;

struct PrsnlInfo // To store personal details of Students and Employee
{
    char fstName[20], lstName[20], name[41], sex[10];
    char eMail[40], CurAdrs[100], PermAdrs[100];
    char qlifcn[100];
    unsigned long long sysID, mobNum;
} stud, emp; // stud->Student's Variable; emp->Employee's Variable

struct parentsInfo // To store Parents detail of Student
{
    char fthrName[40], mthrName[40], prntMail[40];
    unsigned long long ftrMobNum;
};

struct classInfo
{
    int batch;
    char section[6], group[4];

} enrl;

//List of Function used in the program:-

const char *getUserType();
void setPass();
void passStrength(char pass[25]);
void passDB();

void corsDtabs(int year, char dgreName[15],char brnchName[40],char subName[50],int subCode,int subCredit,char subType[10], char profName[40])
{
    fPtr = fopen("Course_details_database.txt","a");
    if (fPtr==NULL)
    {
        printf("Can't Open a file\n");
        exit(1);
    }
    else
    {
        fflush(stdin);
        int k,l;
        fprintf(fPtr, "Year: %d\n",year);
        fprintf(fPtr, "Degree Name: %s\n",dgreName);
        fprintf(fPtr, "Branch Name: %s\n",brnchName);
        fprintf(fPtr, "Subject Name: %s\n",subName);
        fprintf(fPtr, "Subject Code: %d\n",subCode);
        fprintf(fPtr, "Subject Credit: %d\n",subCredit);
        fprintf(fPtr, "Subject Type: %s\n",subType);
        fprintf(fPtr, "Professor Name: %s\n\n",profName);
        // for (k = 0; l < 2; k++)
        // {
        //     for (l=0; l<150;l++)
        //     {
        //         fprintf(fPtr, "_");
        //     }
        //     fprintf(fPtr,"\n");
        // }
        for(k=0;k<150;k++)
            fprintf(fPtr,"*");
    }
    fPtr=NULL;
    fclose(fPtr);

}



void  course_Details()
{
    int i=1;
    while (1)
    {
        int check2;
        int j=1;
        printf("\t Student %d\n",i);
        i++;
        printf("Enter the Year: ");
        scanf("%d", &cInfo.year);
        printf("Enter Degree: ");
        scanf(" %[^\n]%*c",cInfo.dgreName);
        printf("Enter Branch: ");
        scanf(" %[^\n]%*c",cInfo.brnchName);
        while (1)
        {
            int check1;
            printf("\t Subject %d\n",j);
            j++;
            printf("Enter Subject Name: ");
            scanf(" %[^\n]%*c",cInfo.subName);
            printf("Enter Subject Code: ");
            scanf("%d", &cInfo.subCode);
            printf("Enter Subject Credit: ");
            scanf(" %f", &cInfo.subCredit);
            printf("Enter Subject Type(Th/Pr) ");
            scanf(" %[^\n]%*c", cInfo.subType);
            printf("Enter Professor Name: ");
            scanf(" %[^\n]%*c", cInfo.profName);
            corsDtabs(cInfo.year,cInfo.dgreName,cInfo.brnchName,cInfo.subName,cInfo.subCode,cInfo.subCredit,cInfo.subType,cInfo.profName);
            printf("\nPress 1 to add more Subjects: \n");
            printf("Press 2 to Leave: \n");
            scanf("%d",&check1);
            if (check1==1)
                continue;
            else  
                break;
        }
        printf("\nPress 1 to add more Students : \n");
        printf("Press 2 to Leave: \n");
        scanf("%d",&check2);
        if (check2==1)
            continue;
        else  
            break;
    }
}


void subDetls()
{
    while (1)
    {
        int choice1, choice2;
        printf("Select 1 for student with Specialization \n");
        printf("Select 2 for student with Core \n");
        scanf("%d",&choice1);
        if (choice1==1)
        {
            course_Details();
            printf("Press 1 to change faculty\n");
            printf("Press 2 to exit\n");
            scanf("%d",&choice2);
            if (choice2==1)
                continue;
            else
                break;

            
        }
        if (choice1==2)
        {
        course_Details(); 
        printf("Press 1 to change faculty\n");
        printf("Press 2 to exit\n");
        scanf("%d",&choice2);
        if (choice2==1)
            continue;
        else
            break;
        
        }
    }

}

void main()
{
    subDetls();

}
