/*Program List With Array*/
#include <iostream>
#define max 12
#define true 1
#define false 0
using std::cout;
using std::endl;

typedef struct {
	int info; int next; 
}typenode;
typenode element[max];

int list, endlist, empty, endempty, endblank;
int listempty();
void createlist();
void insertnode(int IB);
void deletenode(int IH);
void printlist();

int main(){ 
	createlist();
	printlist();
	insertnode(7);
	cout << "\n\n Insert 7 \n\n";
	printlist();
	insertnode(30);
	cout << "\n\n insert 30 \n\n";
	printlist();
	deletenode(7);
	cout << "\n\n delete 7 \n\n";
	printlist();
	deletenode(60);
	cout << "\n\n delete 60 \n\n";
	printlist();
	insertnode(60);
	cout << "\n\n Insert 60 \n\n";
	printlist();
	insertnode(70);
	cout << "\n\n Insert 70 \n\n";
	printlist();
	deletenode(70);
	cout << "\n\n Delete 70 \n\n";
	printlist();
	deletenode(25);
	cout << "\n\n Delete 25 \n\n";
	printlist();
	insertnode(25);
	cout << "\n\n insert 25 \n\n";
	printlist();
	deletenode(25);
	cout << "\n\n Delete 25 \n\n";
	printlist();
	
}
void createlist(){
	list=5;
	empty=3;
	endlist=10;
	endblank=4;
	element[1].info=25;
	element[1].next=8; 
	element[2].info=0;
	element[2].next=9; 
	element[3].info=0;
	element[3].next=6; 
	element[4].info=0;
	element[4].next=0; 
	element[5].info=10;
	element[5].next=7; 
	element[6].info=0;
	element[6].next=2; 
	element[7].info=15;
	element[7].next=1; 
	element[8].info=40;
	element[8].next=10; 
	element[9].info=0;
	element[9].next=4;
	element[10].info=60;
	element[10].next=0;
}

int listempty(){ 
	if (list==0)
	return(true); else
	return(false);
}

void insertnode(int IB){ 

	int newlist,k,m,n,x;

	if(IB<element[list].info){
		newlist=empty;
		empty=element[empty].next;
		element[newlist].info=IB;
		element[newlist].next=list;
		list=newlist;
		}
	else if(IB>element[endlist].info){
		newlist=empty;
		empty=element[empty].next;
		element[newlist].info=IB;
		element[newlist].next=0;
		element[endlist].next=newlist;
		endlist=newlist;
	}else{
		n=list;
		x=element[n].info;
		while(IB>x){
			m=n;
			n=element[n].next;
			x=element[n].info;
		}
		k=element[empty].next;
		element[m].next=empty;
		element[empty].info=IB;
		element[empty].next=n;
		empty=k;
	}
}

void printlist(){ 
	int n,m;
	n=list; m=empty;
	cout << "fill in the list:\n";
	do{
		cout << element[n].info << " ";
		n=element[n].next;
	}while (element[n].next!=0);

	cout << " "<< element[endlist].info << endl;
	cout << "\nIndex of empty places: \n";
	do{ 
		cout << m << " ";
		m=element[m].next;
	}while(element[m].next!=0);
	cout << " " << endblank;
} 

void deletenode(int IH){
	int newlist,k,x;
	//------------------------ remove at thebeginning 
	if(IH==element[list].info){
		newlist=element[list].next;
		k=empty;
		empty=list;
		list=newlist;
		element[empty].next=k;

	} 
	//------------------delete at the end
	else if(IH == element[endlist].info){
		k=list;
		while(element[k].next != endlist){
			newlist = element[k].next;
			k=element[k].next;
		}

		k = empty;
		empty = endlist;
		endlist = newlist;
		element[empty].next=k;
		element[endlist].next=0;
	}
	//------------------delete in the middle
	else{
		k=list;
		while(IH != element[k].info){
			newlist = k;
			k=element[k].next;
		}
		element[newlist].next=element[k].next;
		x=empty;
		empty=k;
		element[empty].next=x;
	}

}