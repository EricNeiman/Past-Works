#include<stdio.h>
#include<stdlib.h>

/*
doubly linked list
Eric Scott Neiman
++ methods are complete
+ line functions as intended
*/

// structure of a node (1 total) ++ -----------------------------------------------------------------------------------------------------
struct node{ // structure of a node for the linked list ++
    int data;
    struct node *next; // link to next node in the linked list
	struct node *prev; // link to previous node in the linked list
}*head, *tail;

// support methods (4 total) ++ ---------------------------------------------------------------------------------------------------------
int count(){ // this method gives the size of the array ++
    struct node *n;
    int c=0;
    n=head;
    while(n!=NULL){
    n=n->next;
    c++;
    }
	free(n);
	n=NULL;
    return c;
}
void display(struct node *d){ // this method displays the linked list ++
    d=head;
	if(head==NULL&&tail==NULL){
		printf("The list is empty");
		free(d);
		d=NULL;
		return;
	}
    else if(d==NULL){return;}
    while(d!=NULL){
    printf("%d ",d->data);
    d=d->next;
    }
    printf("\n");
	free(d);
	d=NULL;
	return;
}
void deleteList(struct node **head_ref){ // clears the list when the program exits ++
	struct node *dlh = *head_ref;
	struct node *n;
	while (dlh!=NULL){
		n=dlh->next;
		free(dlh);
		dlh=NULL;
		dlh=n;
	}
	free(n);
	n=NULL;
	*head_ref=NULL;
}
int check(int num){ // checks to see if a num is in the list
	int checkNum=0;
	struct node *c;
	c=head;
	while(c!=NULL&&checkNum!=1){
		if(c->data==num){
			checkNum=1;
		}
		else{c=c->next;}
	}
	return checkNum;
}

// add methods (6 total) ++ -------------------------------------------------------------------------------------------------------------
void addHead(int num){  // this creates the first node in the list ++
	struct node *fHead; // creates the pointer
	fHead=(struct node *)malloc(sizeof(struct node)); // gives memory to this pointer
	fHead->data=num; // gives fHead its value
	head=fHead; // assigns the value of head to the node created
	tail=fHead; // assigns the value of tail to the node created
}
void addTail(int num) { // this creates the second node in the list if you add to the front ++
	struct node *fTail;
	fTail=(struct node *)malloc(sizeof(struct node)); 
	fTail->data=num; 
	head=fTail; // changes the original head pointer to the new node so that the original head is now the tail
	head->next=tail; // connects the nodes to each other 
	tail->prev=head; // --------------------------------
	}
void addTails(int num) { // this creates the second node in the list if you add to the end ++
	struct node *fTails;
	fTails=(struct node *)malloc(sizeof(struct node));
	fTails->data=num;
	tail=fTails; // changes the original tail pointer to the new node so that original tail is now the head
	head->next=tail; // connects the nodes to each other
	tail->prev=head; // --------------------------------
}
void begin(int num){ // this adds a node to the front of the linked list when it already has two nodes ++
    struct node *bgNode;
	bgNode=(struct node *)malloc(sizeof(struct node));
	bgNode->data=num; // begin node gets data
	bgNode->next=head; // begin node gets next reference
	head->prev=bgNode; // current heaous refeference
	head=bgNode; // begin node becomes new head
	return;
}
void behind(int num){ // this adds a node to the back of the linked list when it already has two nodes ++
    struct node *bhNode;
	bhNode=(struct node *)malloc(sizeof(struct node));
	bhNode->data=num;
	bhNode->prev=tail;
	tail->next=bhNode;
	tail=bhNode;
	return;
}
void addAfter(int num, int index){ // this adds a node after a specific node ++
	if(head==NULL&&tail==NULL){ // if the list is empty just create a new list
		printf("The list is empty, creating a new list\n");
		addHead(num);
	}
	else if(head==tail){ // if the list has one node and the index is 0 or less the new node is the head if it is 1 or more it is added as the tail
		if(index<=0){
			printf("The index is less than 1 so creating new node as the head\n");
			addTail(num);
		}
		else{
			printf("The index is greater than or equal to 1 so creating new node as the tail\n");
			addTails(num);
		}
	}
	else if(index<=0){
			printf("The index given is before the first node. Adding current node to the front of the list.\n");
			begin(num);
			return;
		}
		else if(index>=count()){
			printf("The size of the list is %i, the index entered is greater than the size of the list, adding the node to the end of the list.\n", count());
			behind(num);
			return;
		}
		else{ // these are only needed if it is not adding to the head or tail
			int c=1; // counter
			struct node *a, *tempAA;
			tempAA=(struct node *)malloc(sizeof(struct node)); // creates the node and gives it its data
			tempAA->data=num; //------------------------------------------------------------------------
			a=head;// traversal pointer
			while(a!=NULL){
				if(c==index){ // once the index is found
					tempAA->next=a->next;
					a->next->prev=tempAA;
					a->next=tempAA;
					tempAA->prev=a;
					return;			
				}
				a=a->next; // moves the pointer of a to the next element
				c++; // increments the counter
			}
		}
}

// remove methods (4 total) ++ ----------------------------------------------------------------------------------------------------------
void removeHead(){ // removes head of the list ++
	printf("Removing the head of the list.\n");
	struct node *rHead;
	//rHead=(struct node *)malloc(sizeof(struct node));
	if (head==tail){ // clears the list of the last value
		rHead=head;
		free(rHead);
		rHead=NULL;
		head=NULL;
		tail=NULL;
	} 
	else if(head->next==tail){ // removes the head when there is only a head and a tail ++
		rHead=head;
		head=tail;
		free(rHead);
		rHead=NULL;
	}
	else{ // standard delete function when deleting the head ++
		rHead=head;
		head=head->next;
		head->prev=NULL;
		free(rHead);
		rHead=NULL;
	}
	return;
}
void removeTail(){ // removes tail of the list ++
	printf("Removing the tail of the list.\n");
	struct node *rTail;
	//rTail=(struct node *)malloc(sizeof(struct node));
	if (head==tail){ // clears the list of the last value
		rTail=tail;
		free(rTail);
		rTail=NULL;
		head=NULL;
		tail=NULL;
	} 
	else if(tail->prev==head){ // removes the tail when there is only a head and tail ++
		rTail=tail; 
		tail=head;
		tail->next=NULL;
		free(rTail);
		rTail=NULL;
	}
	else{ // standard delete function when deleting the tail ++
		rTail=tail;
		tail=tail->prev;
		tail->next=NULL;
		free(rTail);
		rTail=NULL;
	}
	return;
}
void removeNum(int num){ // scans the list and removes the first occurence of a number ++
    if(head==NULL&&tail==NULL){printf("The list is empty.\n");} // the list is empty +
	else if(head->data==num){removeHead();}
	else if(tail->data==num){removeTail();}
	else if(head->data!=num&&tail->data!=num){
		struct node *c;
		c=head;
		while(c!=NULL){
			if(c->data==num){
				c->next->prev=c->prev; // sets the next element's prev to c's prev
				c->prev->next=c->next; // sets the prev element's next to c's next
				free(c);
				c=NULL;
			}else{c=c->next;}
		}
	}
	else{printf("The number is not in the list.\n");}
	return;
}
void removeIndex(int index){ // removes at the index given ++
	if(head==NULL&&tail==NULL){printf("The list is empty.\n");} // the list is empty +
	else if(head==tail){ // there is only one element +
		printf("There is only one element in the list, deleting the list.\n");
		removeHead();
	}
	else if(index<=0){ // the index is the head of the list
		printf("The index entered was less than or equal to 0, removing the head from the list.\n");
		removeHead();
	}
	else if(index>=count()-1){
		printf("The index entered was greater than or equal to the size of the list, removing the tail from the list.\n");
		removeTail(); // if the index to remove is the tail remove it
	}
	else if(index>=1){ // the element to remove is in the middle of the list
		int counter=0; // counter to compare to the index
		struct node *c;
		c=head;
		while(c!=NULL){
			if(counter==index){
					c->next->prev=c->prev; // sets the next element's prev to c's prev
					c->prev->next=c->next; // sets the prev element's next to c's next
					free(c);
					c=NULL;
			}else{
				c=c->next;
				counter++;
			}
		}
	}
	return;
}

// main method (1 total) ++ -------------------------------------------------------------------------------------------------------------
int main(){
    int i,num,after,fb;
    struct node *n;
    head=NULL;
	tail=NULL;
    while(1){
		printf("\nList Operations\n");
		printf("===============\n");
		printf("1.Insert Front or Back\n");
		printf("2.Insert After Index\n");
		printf("3.Display\n");
		printf("4.Size\n");
		printf("5.Remove Number\n");
		printf("6.Remove Index\n");
		printf("7.Exit\n");
		printf("Enter your choice : ");
		if(scanf("%d",&i)<=0){
			printf("Enter only an Integer\n");
			exit(0);
		}
		else{
			switch(i){
				case 1: 
					printf("Enter the number to insert : ");
					scanf("%d",&num);
					if(check(num)==1){
						printf("The number %i already exists in the list.\n", num);
					}
					else if(head==NULL&&tail==NULL){
						printf("Creating the list and adding the number given to the list.\n");
						addHead(num); // ADD method call for an empty list
					}
					else{
						printf("Do you want to insert at the front(1) or back(2)? : ");
						scanf("%d",&fb);
						if(fb==1){ // adding to the front
							if(head==tail){addTail(num);} // changes the old head to the tail and the new num becomes the head
							else{begin(num);} // INSERT front method call
						}
						else if(fb==2){ // adding to the back
							if(head==tail){addTails(num);} // changes the tail to the num
							else{behind(num);} // INSERT rear method call
						}
						else{printf("Enter a 1 to add to the front and a 2 to add to the back.\n");}
					}
					break;
				
				case 2:
					printf("Enter the number to insert : ");
					scanf("%d",&num);
					if(check(num)==1){
						printf("The number %i already exists in the list.\n", num);
					}
					else {
						printf("Enter the index to insert after : ");
						scanf("%d",&after);
						addAfter(num,after); // Add after index call
					}
					break;
					
				case 3:     
					if(head==NULL&&tail==NULL){printf("List is Empty\n");}
					else if(head==tail){printf("The only Element in the list is : %i\n", head->data);}
					else{
						printf("The Elements in the list are : ");
						display(n); //Display method call
					}
					break;
					
				case 4:     
					printf("Size of the list is %d\n",count()); // COUNT method call
					break;
					
				case 5:     
					if(head==NULL&&tail==NULL){printf("List is Empty\n");}
					else{
						printf("Enter the number to remove : ");
						scanf("%d",&num);
						removeNum(num); // remove a number method call
					}
					break;
				
				case 6:
					printf("Enter the index to remove(0 to %i) : ",count()-1);
					scanf("%d",&num);
					if (head==NULL&&tail==NULL){printf("The list is empty\n");} // cannot remove an index when there aren't any
					else {removeIndex(num);} // remove an index method call
					break;
				
				case 7: 
					deleteList(&head); //deletes the list before exiting
					return 0;
					
				default: printf("Invalid option\n");
			}
		}
	}
	return 0;
}