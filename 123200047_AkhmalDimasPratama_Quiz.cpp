/*
    Akhmal Dimas Pratama
    123200047 - IF H
*/

#include <iostream>
#include <cstring>
using namespace std;

typedef int typeinfo, typeage, typesistole, typediastole;
typedef float typetemperature;

typedef char typeName, typenik, typevaccine, typestatus;

typedef struct node *typeptr;
struct node
{
    typeName name[30];
    typenik nik[30];
    typevaccine vaccine[30];
    typestatus status[30];
    typetemperature temperature;
    typediastole diastole;
    typesistole sistole;
    typeage age;
    typeinfo info;
    typeptr next;
};

typeptr head;


int choice, totalnode = 0, idnode=0;
bool error=false;

char loop='y';


bool listCheck();
bool isCheckOne(int age); // checking for first Screening
bool isCheckTwo(float temp, int sistole, int diastole);// checking for second Screening

void invalid();
void createList();

void inputData();
void insertNode(node IN); //insert node
void viewData();
void statusCheck();
void deleteData();

int main()
{
    createList();// error handling to create the linkedlist first

    while(loop == 'y' || loop == 'Y'){
        system("cls");
        puts("---- Vaccination Program ----");
        puts("Central Java Vaccination Data");
        puts(" 1. Input Data");
        puts(" 2. View Participant Data");
        puts(" 3. Check Vaccination Status");
        puts(" 4. Delete Vaccination Data");
        puts(" 5. Exit");
        printf("Input [1...5] : "); cin >> choice;
        switch (choice)
        {
        case 1:
            inputData();
            break;
        
        case 2:
            viewData();
            break;
            
        case 3:
            statusCheck();
            break;
        
        case 4:
            deleteData();
            break;
        
        case 5:
            loop='n';
            break;

        default:
            invalid();
            break;
        }
        if(choice!=5){
            printf("\nBack to menu ? (y/n) : "); cin >> loop;
        }
        
    }

    return 0;
}

void invalid(){
	if(cin.fail()){
        error=true;
        cout << "\nWrong Input" << endl;
		cin.clear();
		cin.ignore(1000,'\n');
		cout << "\nPlese Input Integer Only!" << endl;
	}
}

bool listCheck()
{
    if (head->next == head)
        return (1);
    else
        return (0);
}

void createList()
{
    head = (node*)malloc(sizeof(node));
    head->info = 0;
    head->next = head;
}

void inputData(){
    error=false; //error handling
    string s;
    node input;

    typeName inputName;

    puts("Selected Menu 4");
    puts("Input Participant Vaccination Data");

    //input the data
    puts("Screening Step 1");
    printf(" Name           : "); 

    cin.ignore();
    cin.getline(input.name, 30);

    printf(" Age            : ");
    cin >> input.age;
    invalid(); //error handling
    if(!error){
        printf(" NIK            : ");
        cin.ignore();
        cin.getline(input.nik, 20);
        if(isCheckOne(input.age) && !error){
            puts("\nScreening Step 2");
            printf(" Body Temp        : ");
            cin >> input.temperature;
            invalid(); // error handling

            if(!error){
                printf(" Blood Pressure   : ");
                cin >> input.diastole; cin >> input.sistole;
                invalid(); // error handling
                if (isCheckTwo(input.temperature, input.sistole, input.diastole) && !error)
                {
                    puts("\nScreening Step 3");
                    puts(" 1. Sinovac");
                    puts(" 2. Astrazeneca");
                    puts(" 3. Moderna");
                    printf("Choice the vaccine number : ");
                    cin >> choice;
                    if(choice >=1 && choice <=3){
                        if(choice==1){
                            s = "Sinovac"; // input data array into char
                            // declaring character array
                            // string to char array
                            strcpy(input.vaccine, s.c_str());
                        
                        }else if(choice==2){
                            s = "Astrazeneca";
                            strcpy(input.vaccine, s.c_str()); // input data array into char
                        }else if(choice==3){
                            s = "Moderna";
                            strcpy(input.vaccine, s.c_str()); // input data array into char
                        }

                        s = "have not vaccinated"; // input data array into char
                        strcpy(input.status, s.c_str());

                        insertNode(input); //function insert the data
                    }else{
                        puts("\nSorry you cant do vaccination program");
                    }
                }else{
                    puts("\nSorry you cant do vaccination program");
                }
            }
        }else{
            puts("\nSorry you cant do vaccination program");
        }

    }
}

bool isCheckOne(int age)
{ // checking for first Screening
    if(age>12){
        return 1;
    }else{
        return 0;
    }
}

bool isCheckTwo(float temp, int sistole, int diastole) // checking for second Screening
{
    if(temp < 37.5 && sistole <=120 && sistole >= 100 && diastole <= 90 && diastole >= 60){
        return 1;
    }else{
        return 0;
    }
}

void insertNode(node IN){
    typeptr NN, helper;
    totalnode++; //declaration for the total of the data
    idnode++;
    NN = (node*)malloc(sizeof(node));

    //insert the data from Inputted Data
    NN->info = idnode;
    NN->age = IN.age;

    for(int i=0; i<=30;i++){
        NN->name[i] = IN.name[i];
    }

    for(int i=0; i<=30;i++){
        NN->nik[i] = IN.nik[i];
    }
   
    NN->temperature = IN.temperature;
    NN->diastole = IN.diastole;
    NN->sistole = IN.sistole;

    for(int i=0; i<=30;i++){
        NN->vaccine[i] = IN.vaccine[i];
    }

    for(int i=0; i<=30;i++){
        NN->status[i] = IN.status[i];
    }

    NN->next = NULL;
    if (listCheck()) //if the list is empty
    {
        NN->next = head;
        head->next = NN;
        totalnode=1;
        idnode=1;
        head->info = totalnode;
    }
    else
    {
        helper = head;
        while (helper->next->info < NN->info && helper->next != head) //the data insert will be the next of the last id
            helper = helper->next;
        if (helper->next != head) //error handling if the data on middle
        {
            NN->next = helper->next;
            helper->next = NN;
        }
        else //error handling if the data in the end
        { 
            NN->next = head;
            helper->next = NN;
        }
    }
    head->info = totalnode; //update total node
}

void viewData(){
    puts("Selected Menu 2");
    if (listCheck()) //check list empty
    {
        puts("Linked List is Empty");
    }
    else
    {   
        int number=1;
        typeptr helper;
        helper = head->next;
        while (helper != head) //will looping if the data not head
        { 
            printf("%d. %s\n", number, helper->name);
            helper = helper->next; //this is to change the helper into the next data
            number++;
        }
    }

 }

void statusCheck(){
    puts("Selected Menu 3");
    bool check=false;
    char search[30];

    puts("Input the NIK that want to search");
    printf("NIK       : "); cin.ignore(); cin.getline(search, 30);

    if (listCheck()) //check list empty
    {
        puts("Linked List is Empty");
    }
    else
    {   
        string s;
        char input;
        typeptr helper;
        helper = head->next;
        while (helper != head)
        { 
            if(strcmp(search, helper->nik)==0){ //if the nik found
                check=true;
                printf(" Name            : %s\n", helper->name);
                printf(" Age             : %d\n", helper->age);
                printf(" NIK             : %s\n", helper->nik);
                printf(" Body Temp       : %.1f\n", helper->temperature);
                printf(" Blood Pressure  : %d\\%d\n", helper->diastole, helper->sistole);
                printf(" Vaccine         : %s\n", helper->vaccine);
                printf(" Status          : %s\n", helper->status);

                //change the status vaccine
                if(strcmp(helper->status, "Vaccination process is complete")!=0){ //it will run when the data not complete the vaccination
                    printf("Do vaccination? (y/n)");
                    cin >> input;
                    if(input=='y'||input=='Y'){
                        printf("Are you sure? (y/n) : ");
                        cin >> input;

                        if(input=='y'||input=='Y'){
                            if(strcmp(helper->status, "have not vaccinated")==0){ //it will run when the data is not vaccinated
                                s = "Already done the first vaccine"; //change the data into first vaccine
                                strcpy(helper->status, s.c_str());
                            }else if(strcmp(helper->status, "Already done the first vaccine")==0){ //it will run when the data is at first vaccine
                                s = "Vaccination process is complete"; //change the data into complete
                                strcpy(helper->status, s.c_str());
                            }
                        }
                    }
                }
                
            }
            helper = helper->next;
        }

        if(!check){
            puts("Data not found!");
        }
    }
}

void deleteData(){
    typeptr deleted, helper; //declaration delete and helper
    bool check=true;
    char search[30], choice;

    puts("Selected Menu 4");
    puts("Delete Vaccination Data");


    printf("Enter the NIK whose data will be deleted  : "); cin.ignore(); cin.getline(search, 30);
    
    if (listCheck()) //check list empty
    {
        puts("Linked List is Empty");
    }
    else
    {
        helper = head;
        while (
                strcmp(helper->next->nik, search) != 0 &&  //loop will stop if the deleted nik is before the data/helper
                helper->next != head
            ){
                helper = helper->next; //to next the helper/data
                if(helper->next==head){ // if the helper is head so it will false / not found
                    check=false;
                }
            }
        
        if(check){ // if it found
            printf(" Data : %s\n", helper->next->name);
            printf(" Are you sure delete the data? (y/n) : "); cin >> choice;
            if(choice=='y'||choice=='Y'){
                if (helper->next != head) //if the data not 1
                {
                    deleted = helper->next; // the delete data is the next helper
                    helper->next = deleted->next; //and the helper next will replace the delete-next
                    free(deleted); // for delete the node
                }else
                { //if the data only 1
                    deleted = helper->next;
                    helper->next = head;
                    free(deleted);
                }
                totalnode--;
                head->info = totalnode; //update total data
            }
        }else{
            puts("The data not found!!");
        }
    }
}
