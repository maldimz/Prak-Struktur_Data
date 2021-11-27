/*
    Akhmal Dimas Pratama
    123200047 - IF H
*/


#include <iostream>
#include <malloc.h>
#include <fstream>

using namespace std;

typedef struct books *typebook;
typedef struct loan *typeloan;

struct books{
    int num;
    typebook prev, next;
};

struct loan{
    int num;
    typeloan prev, next;
};

/*
    stock_top is for the top data stack
    stock_bot is for the bottom data stack

    loan_front is for the first queue
    loan_back is for the back queue
*/

typebook stock_top, stock_bot;
typeloan loan_front, loan_back;


//check is check empty
bool stockEmpty(){
	if(stock_top == NULL)
		return true;
	else 
		return false;
}

//check if loan empty
bool loanEmpty(){
    if(loan_front==NULL)
        return true;
	else 
		return false;
}

//error handling for read/write data
bool readFirst = false;

void add_stock(int add);
void print_stock();

void loan_book();
void print_loan();

void enqueue(int add);
void dequeue();

void return_loan();

void read_file();
void create_file();

void update_file_stock();
void update_file_loan();


//error handling int input if input non an integer
bool invalid(){
    if(cin.fail()){

        puts("\n\nWrong Inpu");
        cin.clear();
        cin.ignore(1000,'\n');
        puts("\nPlese Input Integer Only!");
        return true;

    }else{
        return false;
    }
}

int main(){
    char choice;
    create_file();
    read_file();

	do{
		system("cls");
		puts("MENU");
        puts("1. ADD BOOK STOCK");
        puts("2. LOAN A BOOK");
        puts("3. VIEW LIST OF BOOK");
        puts("4. RETURN A BOOK");
        puts("5. VIEW LIST OF LOAN BOOK");
        puts("6. EXIT");
        printf("\nCHOICE : "); cin >> choice;
		
		switch(choice){
			case'1':
				int many, number;

                printf("How many books input? : ");
                cin >> many;
                if(!invalid()){
                    for(int i=0; i<many; i++){
                        printf("Number Books %d : ", i+1);
                        cin >> number;

                        if(invalid()){
                            break;
                        }else{
                            add_stock(number);
                        }
                    }
                }
				break;
			
			case'2':
				loan_book();
				break;
			
			case'3':
				print_stock();
				break;
			
			case'4':
				return_loan();
				break;
			
			case'5':
				print_loan();
                break;
			
			case'6':
				exit(0);
				break;

            default:
                puts("\nWrong Input!");
                break;

		}

        printf("\n\nBACK TO MENU? (y/n) : "); cin >> choice;
		
		
		
	}while(choice != '6' && (choice!='n' && choice!='N'));
}


//update for file handling
void update_file_stock(){
    ofstream Stock("stock_book.txt", ios::out);
    typebook helper;
	helper = stock_top;
    int i=1;

	if(helper !=NULL){
        
		while(helper!=NULL){     
			helper = helper->next;
            i++;
		}

        helper = stock_top;
        int reverse[i];
        i=0;
        while (helper != NULL){
            reverse[i++]=helper->num;
            helper = helper->next;
        }

        for(int j=i-1;j>=0;j--){
            Stock << reverse[j] << "\n";
        }
        
	} 
    Stock.close();
}

//update for file handling
void update_file_loan(){
    ofstream Loan("loan_book.txt", ios::out);
    typeloan helper;
    helper = loan_front;
    
    if(helper!=NULL){
        while(helper!=NULL){
        Loan << helper->num << "\n";
        helper = helper->next;
        }
    }
    Loan.close();
}

//create file if not exist
void create_file(){
    ofstream Stock("stock_book.txt", ios::app);
    Stock.close();
    ofstream Loan("loan_book.txt", ios::app);
    Loan.close();
}

//read file for the first time application open
void read_file(){
    int num;

    ifstream Stock("stock_book.txt");
    if(Stock.is_open()){
        Stock >> num;
        while(Stock.eof()==0){
            add_stock(num);
            Stock >> num;
        }
    }else{
        puts("File cannot open");
    }

    Stock.close();

    ifstream Loan("loan_book.txt");
    if(Loan.is_open()){
        Loan >> num;
        while(Loan.eof()==0){
            enqueue(num);
            Loan >> num;
        }
    }else{
        puts("File cannot open");
    }

    Loan.close();

    readFirst = true;
}


//add stock for stack
void add_stock(int add){
    typebook IB;

    IB = (books*) malloc(sizeof(books));

    IB->num = add;
    IB->next = NULL;
    IB->prev = NULL;

    if(stockEmpty()){
        stock_top = IB;
        stock_bot = IB;
    }else{
        stock_top->prev=IB;
		IB->next=stock_top;
		stock_top=IB; 
    }

    //write stack data into file
    if(readFirst){
        ofstream Stock("stock_book.txt", ios::app);

        if(Stock.is_open()){
            Stock << add << "\n";
        }else{
            puts("FILE ERROR!");
        }

        Stock.close();
    }

}

//print stack from the top to bottom
void print_stock(){
	typebook helper;

	helper = stock_top;
    puts("===== LIST BOOK STOCK =====");
	if(helper !=NULL){
        
		while(helper!=NULL){
			printf("%d \n", helper->num);

			helper = helper->next;
		}
	} else{
		puts("NO DATA");
	}
}


void loan_book(){
    typebook del;
    int helper;

    if(!stockEmpty()){
        puts("===== LOAN BOOK SUCCESS =====");
        helper = stock_top->num;
        del = stock_top;
        stock_top = del->next;

        free(del);
        
        

        //update stock data and stack data
        enqueue(helper);
        update_file_stock();
    }else{
        puts("NO BOOK");
    }
}

//print queue from front to back
void print_loan(){
    typeloan helper;
    helper = loan_front;
    
    if(helper!=NULL){
        while(helper!=NULL){
        printf("%d   ", helper->num);
        helper = helper->next;
        }
    }else{
        puts("NO DATA");
    }
    
}

void return_loan(){
    if(!loanEmpty()){
        puts("===== BOOK RETURN SUCCESS =====");
        dequeue();
        update_file_loan();
    }else{
        puts("NO DATA");
    }
}

//add loan for queue
void enqueue(int add){
    typeloan NL;
    NL = (loan*) malloc(sizeof(loan));
    NL->num = add;
    NL->prev=NULL;
    NL->next=NULL;

    if(loanEmpty()){
        loan_front=NL;
        loan_back=NL;
    }else{
        loan_back->next = NL;
        NL->prev = loan_back;
        loan_back = NL;
    }
    
    //write queue loan into file
    if(readFirst){
        ofstream Loan("loan_book.txt", ios::app);

        if(Loan.is_open()){
            Loan << add << "\n";
        }else{
            puts("FILE ERROR!");
        }

        Loan.close();
    }
}

//dequeue
void dequeue(){
    int helper;
    typeloan del;

    if(loanEmpty()){
        puts("NO LOAN DATA");
    }else{
        helper = loan_front->num;
        del = loan_front;
        loan_front = del->next;
        
        //update load data and queue data
        free(del);
        add_stock(helper);
    }
}

