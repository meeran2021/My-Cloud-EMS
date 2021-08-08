#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int choice;    // Used as an argument in getUserType() function.
char pass[30]; // To store password of user.
FILE *fPtr;    // To store returned address of fopen function.

struct CourseInfo // To store Course Info.
{
    char dgreName[30], brnchName[40], spclName[50], subName[50], subType[10];
    int subCode;
} info;

struct PrsnlInfo // To store personal details of Students and Employee
{
    char fstName[20], lstName[20], name[41], sex[10];
    char eMail[40], CurAdrs[100], PermAdrs[100], uniMailId[40];
    char qlifcn[100];
    char dob[10];
    unsigned long long sysID, mobNum;

} stud, emp; // stud->Student's Variable; emp->Employee's Variable

struct parentsInfo // To store Parents detail of Student
{
    char fthrName[40], mthrName[40], prntMail[40];
    unsigned long long prtsMobNum;
} prts;

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

const char *getUserType(int choice) //Returns pointer to character which store adddress of string. Returns User Type
{
    if (choice == 1)
    {
        return "Student";
    }
    else if (choice == 2)
    {
        return "Employee";
    }
    else if (choice == 0)
    {
        exit(0);
    }
    else
    {
        return "Again";
    }
}

void setPass(unsigned long long sysID) // Sets New Password for the user.
{
    char confirmPass[30];
    printf("Enter Password ");
    scanf("%s", &pass);
    passStrength(pass); // Checks the strength of password.
    printf("Enter Password Again ");
    scanf("%s", &confirmPass);
    if (strcmp(confirmPass, pass) != 0)
    {
        printf("\nPassword does not match!!!");
        printf("\nTry Again... ");
        setPass(sysID); // Recursion
    }
    else
    {
        if (strcmp(getUserType(choice), "Employee") == 0)
        {
            passDB(emp.sysID, pass, choice); // Passed Employee's System ID
        }
        if (strcmp(getUserType(choice), "Student") == 0)
        {
            passDB(stud.sysID, pass, choice); // Passed Student's System ID
        }
    }
}
void passStrength(char pass[25]) // Checks the strength of Password (Need some modifications)
{
    int i = 0, check = 0, spclSymb = 0, num = 0, upCase = 0, lowCase = 0;
    char x;
    if (strlen(pass) <= 8)
        printf("Password must be atleast 8 Characters\n");
    else if (strlen(pass) > 20)
        printf("Password must be atmost 20 Characters\n");
    else
    {
        while (pass[i] != '\0')
        {
            x = (int)pass[i];
            if (x >= 97 && x <= 122)
                lowCase = 1;

            if (x >= 65 && x <= 90)
                upCase = 1;

            if (x >= 48 && x <= 57)
                num = 1;

            if ((x >= 32 && x <= 47) || (x >= 58 && x <= 64) || (x >= 91 && x <= 96) || (x >= 123 && x <= 126))
                spclSymb = 1;

            i++;
        }

        if (lowCase)
            check += 10;
        if (upCase)
            check += 10;
        if (num)
            check += 10;
        if (spclSymb)
            check += 10;

        if (check == 40)
            printf("Password Strength: Excellent \n");
        else if (check == 30)
            printf("Password Strength: Very Good\n");
        else if (check == 20)
            printf("Password Strength: Average\n");
        else
            printf("Password Strength: Poor\n");
    }
}

void passDB(unsigned long long sysID, char pass[], int choice) // Store ID Password into respective database
{
    if (strcmp(getUserType(choice), "Employee") == 0)
    {
        fPtr = fopen("EmpPassDataBase.txt", "a"); // Opening Employee's Database
    }
    else if (strcmp(getUserType(choice), "Student") == 0)
    {
        fPtr = fopen("StPassDataBase.txt", "a"); // Opening Stident's Database
    }
    else
    {
        printf("ERROR... Can't find database:(");
    }
    if (fPtr == NULL)
    {
        printf("\nCan't Open File ");
        exit(1);
    }
    else
    {
        fflush(stdin);
        fprintf(fPtr, "\n%llu,%s", sysID, pass); // Writing id pass into text file
        fclose(fPtr);                            // Closing text file
        printf("\nPassword has been Set.");
    }
    fPtr = NULL; // Resetting FILE pointer to NULL
}

void accInfoDB(unsigned long long sysID, char name[41])                 // Function for printing the Academic details
{
    fPtr = fopen("StudAccDtlsDB.txt", "a");
    if (fPtr == NULL)
    {
        printf("\nCan't Open File ");
        exit(1);
    }
    else
    {
        fflush(stdin);
        int i;
      
        fprintf(fPtr, "\n\nName: %s\n",name);

        fprintf(fPtr, "System Id: %llu\n",sysID);

        fprintf(fPtr, "\tDegree Name: %s\n",info.dgreName);
    
        fprintf(fPtr, "\tBatch: %llu\n",enrl.batch);

        fprintf(fPtr, "\tBranch name: %s\n",info.brnchName);

        fprintf(fPtr, "\tSpecialization: %s\n", info.spclName);

        fprintf(fPtr, "\tSection: %s\n",enrl.section);
        
        fprintf(fPtr, "\tGroup: %s\n",enrl.group);
         
        for (i = 0; i < 120; i++)
        {
            fprintf(fPtr, "_");
        }
        fclose(fPtr);
        printf("\nCourse info Set\n");
    }
    fPtr = NULL;
}

void studAccDetls(unsigned long long sysID, char name[41])                // Function for Entering the Academic details
{

    printf("Batch/Year: ");
    scanf("%llu", &enrl.batch);

    printf("Enter the Degree Name : ");
    scanf("\n");
    scanf("%[^\n]%*c", info.dgreName);

    printf("Enter the Branch Name : ");
    scanf("\n");
    scanf("%[^\n]%*c", info.brnchName);

    printf("Enter specialization if any Or Enter none if no specialization:\n");
    scanf("%[^\n]%*c", info.spclName);

    printf("Assign Section To the Student: ");
    scanf("%[^\n]%*c", enrl.section);

    printf("Assign Group: ");
    scanf("%[^\n]%*c", enrl.group);

    accInfoDB(sysID, name);
}

void prsnlInfoDb(unsigned long long sysID, char name[41])                // Function for printing the Personal details
{
    fPtr = fopen("StudPrsnlInfo.txt", "a");
    if (fPtr == NULL)
    {
        printf("\nCan't Open File ");
        exit(1);
    }
    else
    {
        fflush(stdin);
        int i;

        fprintf(fPtr, "\n\nSystem Id: %llu\nName: %s\n",sysID,name);

        fprintf(fPtr, "\tDate of birth: %s\n",stud.dob);
    
        fprintf(fPtr, "\tGender: %s\n",stud.sex);

        fprintf(fPtr, "\tMobile Num: %llu \n",stud.mobNum);

        fprintf(fPtr, "\tUniversity Mail-Id: %s\n ",stud.uniMailId);

        fprintf(fPtr, "\tPersonal Mail-ID: %s\n\n",stud.eMail);
        
        fprintf(fPtr, "Parents Info:-\n ");

        fprintf(fPtr, "Fathers Name: %s\n", prts.fthrName);

        fprintf(fPtr, "Mothers Name: %s\n",prts.mthrName);

        fprintf(fPtr, "\tMobile Num: %llu\n",prts.prtsMobNum);

        fprintf(fPtr, "\tE-Mail ID: %s\n\n",prts.prntMail);

        fprintf(fPtr, "Quallification: %s \n",stud.qlifcn);

        fprintf(fPtr, "Adderess:-\n");

        fprintf(fPtr, "\tCurrent: %s\n",stud.CurAdrs);

        fprintf(fPtr, "\tPermanenet: %s\n",stud.PermAdrs);
      
        for (i = 0; i < 120; i++)
        {
            fprintf(fPtr, "_");
        }
        fclose(fPtr);
        printf("\nInfo Set\n");
    }
    fPtr = NULL;
}

void studPrsnlDetls(unsigned long long sysID, char name[41])           // Function for ENtering the Personal details
{

    printf("Date of birth: ");
    scanf("\n");
    scanf("%[^\n]%*c", stud.dob);

    printf("\nGender: ");
    scanf("%[^\n]%*c", stud.sex);

    printf("\nfathers Name: ");
    scanf("%[^\n]%*c", prts.fthrName);

    printf("\nMothers Name: ");
    scanf("%[^\n]%*c", prts.mthrName);

    printf("\n\nEnter Mobile number:\n");
    printf("\nStudent:- ");
    scanf("%llu", &stud.mobNum);

    printf("\nParents:- ");
    scanf("%llu", &prts.prtsMobNum);

    printf("\n\nEnter E-Mail ID:\n");
    printf("\nPersonal mail-Id- Student: ");
    scanf("\n");
    scanf("%[^\n]%*c", stud.eMail);

    printf("\nPersonal mail-Id- Parents: ");
    scanf("%[^\n]%*c", prts.prntMail);

    printf("\nUniversity mail-Id for student: ");
    scanf("%[^\n]%*c", stud.uniMailId);

    printf("\n\nQuallification: ");
    scanf("%[^\n]%*c", stud.qlifcn);

    printf("\n\nAdderess: \n");

    printf("\nCurrent: ");
    scanf("%[^\n]%*c", stud.CurAdrs);

    printf("\nPermanenet: ");
    scanf("%[^\n]%*c", stud.PermAdrs);

    prsnlInfoDb(sysID, name);
}

void employerOP()           // Employer Menu function
{

    while (1)
    {
        int input, opt;
        printf("\n\tEnter 1 To : Enroll New Student ");
        printf("\n\tEnter 2 To : Allot Timetable ");
        printf("\n\tEnter 3 To : Subjects "); // review it later
        printf("\n");
        scanf("%d", &input);

        if (input == 1)
        {
            char space[] = " ";

            printf("Enter the Students Name \n");
            printf("First Name: ");
            scanf("\n");
            scanf("%[^\n]%*c", stud.fstName);        //First name

            strcat(stud.fstName, space);             // Adding space after first name

            printf("\nLast Name: ");
            scanf("%[^\n]%*c", stud.lstName);         // Last name

            strcat(stud.fstName, stud.lstName);
            strcpy(stud.name, stud.fstName);            //Storing Name

            printf("\nEnter the Students System Id: ");
            scanf("%llu", &stud.sysID);                 //For system id

            printf("\n\nTo fill Academic Details enter 1\n");
            printf("\nTo fill Personal Details enter 2\n");

            while (1)
            {
                scanf("%d", &opt);
                if (opt == 1)
                {
                    studAccDetls(stud.sysID, stud.name);             // Calling the function to enter Academic details
                    break;
                }
                if (opt == 2)
                {
                    studPrsnlDetls(stud.sysID, stud.name);            // Calling the function to enter Personal details
                    break;
                }
                else
                {
                    printf("Enter the value again:");
                    continue;
                }
            }

            break;
        }

        /*if (input == 2)
        {
            
        }
        
        if (input == 3)
        {
            
        }*/
        else
        {
            printf("Enter the value again:");
            continue;
        }
    }
}

void main() // Start
{
    int reply; // To store user's choice for operations
    
    printf("\n\n\n");
    printf("\n\t\t\t   Welcome");
    printf("\n\t\t ###### My Cloud EMS ######");
    printf("\n\n\n");
    printf("\nSelect User Type ");
    printf("\n1. Student");
    printf("\n2. Employee");
    printf("\n0. Exit");
    printf("\n");

    while (1)
    {
        scanf("%d", &choice);
        getUserType(choice); // Getting the type of User ie.., Student or Employee
        if (strcmp(getUserType(choice), "Employee") == 0)
        { // Menue for Employee
            
            employerOP();// To enroll new student / time table alot.
            // Change this After discussion

            printf("\n1. New User?? Sign Up");
            printf("\n2. Existing User?? Login");
            printf("\n9. Exit");
            printf("\n");
            scanf("%d", &reply);
            if (reply == 1)
            {
                printf("\nEnter System ID: ");
                scanf("%llu", &emp.sysID);
                setPass(emp.sysID); // calling function to set password
            }
            if (reply == 2)
            {
                //existing user function
            }
            break;
        }
        else if (strcmp(getUserType(choice), "Student") == 0)
        { // Menue for Student
            printf("\nEnter System ID: ");
            scanf("%llu", stud.sysID);
            printf("\nEnter Password: ");
            scanf("%s", pass);
            //confirm ID and Pass from text file
            break;
        }
        else if (strcmp(getUserType(choice), "Again") == 0)
        {
            printf("Is an Invalid Choice!!!");
            printf("\nPlease choose again:\n");
            continue;
        }
    }
}
