#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>


int choice;             // Used as an argument in getUserType() function.
char pass[30];          // To store password of user.
FILE *fPtr;             // To store returned address of fopen function.

struct CourseInfo       // To store Course Info.
{
    char dgreName[15], brnchName[40], spclName[50], subName[50], subType[10];
    int subCode;
};



struct PrsnlInfo        // To store personal details of Students and Employee
{
    char fstName[20], lstName[20], name[41], sex[10];
    char eMail[40], CurAdrs[100], PermAdrs[100];
    char qlifcn[100];  
    unsigned long long sysID, mobNum;
}stud,emp;              // stud->Student's Variable; emp->Employee's Variable

struct parentsInfo      // To store Parents detail of Student
{
    char fthrName[40], mthrName[40], prntMail[40];
    unsigned long long ftrMobNum;
};

//List of Function used in the program:-

const char* getUserType();
void setPass();
void passStrength(char pass[25]);
void passDB();




const char* getUserType(int choice)     //Returns pointer to character which store adddress of string. Returns User Type
{
    if(choice==1)
    {
        return "Student";
    }
    else if(choice == 2)
    {
        return "Employee";
    }
    else if(choice==0)
    {
        exit(0);
    }
    else
    {
        printf("%d",choice);
        printf("\nInvalid Choice!!!\nChoose Again");
        getUserType(choice);            // Recursion
    }
}


void setPass(unsigned long long sysID)      // Sets New Password for the user.
{
    char confirmPass[30];
    printf("Enter Password ");
    scanf("%s",&pass);
    passStrength(pass);                      // Checks the strength of password.
    printf("Enter Password Again ");
    scanf("%s",&confirmPass);
    if(strcmp(confirmPass,pass)!=0)
    {
        printf("\nPassword does not match!!!");
        printf("\nTry Again... ");
        setPass(sysID);                       // Recursion
    }
    else
    {
        if(strcmp(getUserType(choice),"Employee")==0)
        {
            passDB(emp.sysID,pass,choice);       // Passed Employee's System ID 
        }
        if(strcmp(getUserType(choice),"Student")==0)
        {
            passDB(stud.sysID,pass,choice);      // Passed Student's System ID 
        }
    }
    
}
void passStrength(char pass[25])            // Checks the strength of Password (Need some modifications)
{
    int i=0, check=0;
    char x;
    int spclSymb=0,num=0,upCase=0,lowCase=0;
    // if (pass==ltoa(emp.empSysID))
    //     printf("Enter password other than System ID\n");
    if (strlen(pass)<=8)
        printf("Password must be atleast 8 Characters\n");
    else if (strlen(pass)>20)
        printf("Password must be atmost 20 Characters\n");
    else
    {      
        while (pass[i]!='\0')
        {
            x=(int)pass[i];
            if  (x>=97 && x<=122)
                lowCase=1;

            if (x>=65 && x<=90)
                upCase=1;

            if (x>=48 && x<=57)
                num=1;

            if ((x>=32 && x<=47) || (x>=58 && x<=64) || (x>=91 && x<=96) || (x>=123 && x<=126))  
                spclSymb=1;

            i++;
        } 

    if (lowCase) check+=10;
    if (upCase) check+=10;
    if (num) check+=10;
    if (spclSymb) check+=10;

    if (check==40)
        printf("Password Strength: Excellent \n");
    else if (check==30)
        printf("Password Strength: Very Good\n");
    else if (check==20)
        printf("Password Strength: Average\n");
    else
        printf("Password Strength: Poor\n");
    }     
}


void passDB(unsigned long long sysID, char pass[],int choice)     // Store ID Password into respective database
{
    if(strcmp(getUserType(choice),"Employee")==0)
    {
        fPtr=fopen("EmpPassDataBase.txt","a");                     // Opening Employee's Database
    }
    else if(strcmp(getUserType(choice),"Student")==0)
    {
        fPtr=fopen("StPassDataBase.txt","a");                       // Opening Stident's Database
    }
    else
    {
        printf("ERROR... Can't find database:(");
    }
    if (fPtr==NULL)
    {
        printf("\nCan't Open File ");
        exit(1);
    }
    else
    {
        fflush(stdin);
        fprintf(fPtr,"\n%llu,%s",sysID,pass);                       // Writing id pass into text file
        fclose(fPtr);                                               // Closing text file
        printf("\nPassword has been Set.");
       
    }
    fPtr=NULL;                                                      // Resetting FILE pointer to NULL
}


void main()                                                          // Start 
{
    int reply;                                   // To store user's choice for operations    
    printf("\n\n\n");
    printf("\n\t\t\t   Welcome");
    printf("\n\t\t ###### My Cloud EMS ######");
    printf("\n\n\n");
    printf("\nSelect User Type ");
    printf("\n1. Student");
    printf("\n2. Employee");
    printf("\n0. Exit");
    printf("\n");
    scanf("%d",&choice);                    
    getUserType(choice);                 // Getting the type of User ie.., Student or Employee
    if(strcmp(getUserType(choice),"Employee")==0)      
    {                                                  // Menue for Employee                 
        printf("\n1. New User?? Sign Up");
        printf("\n2. Existing User?? Login");
        printf("\n9. Exit");
        printf("\n");
        scanf("%d",&reply);
        if(reply==1)
        {
            printf("\nEnter System ID: ");
            scanf("%llu", &emp.sysID);
            setPass(emp.sysID);                     // calling function to set password
        }
    }
    else if(strcmp(getUserType(choice),"Student")==0)
    {                                                   // Menue for Student
        printf("\nEnter System ID: ");
        scanf("%llu",stud.sysID);
        printf("\nEnter Password: ");
        scanf("%s",pass);
        //confirm ID and Pass from text file
        
    }
    else
    {
        printf("ERROR... ");
    }
}



