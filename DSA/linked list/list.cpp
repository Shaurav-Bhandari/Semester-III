#include<stdio.h>
#include<stdlib.h>

void insertAtBeginning(int);
void insertAtEnd(int);
void insertBetween(int,int,int);
void display();

struct Node
{
   int data;
   struct Node *next;
}*head = NULL;


void insertAtBeginning(int value)
{
   struct Node *newNode;
   newNode = (struct Node*)malloc(sizeof(struct Node));
   newNode->data = value;
   if(head == NULL)
   {
      newNode->next = NULL;
      head = newNode;
   }
   else
   {
      newNode->next = head;
      head = newNode;
   }
   printf("\nOne node inserted!!!\n");
}
void insertAtEnd(int value)
{
   struct Node *newNode;
   newNode = (struct Node*)malloc(sizeof(struct Node));
   newNode->data = value;
   newNode->next = NULL;
   if(head == NULL)
    head = newNode;
   else
   {
      struct Node *temp = head;
      while(temp->next != NULL)
    temp = temp->next;
      temp->next = newNode;
   }
   printf("\nOne node inserted!!!\n");
}

void insertBetween(int value, int loc1, int loc2)
{
   struct Node *newNode;
   newNode = (struct Node*)malloc(sizeof(struct Node));
   newNode->data = value;
   if(head == NULL)
   {
      newNode->next = NULL;
      head = newNode;
   }
   else
   {
      struct Node *temp = head;
      while(temp->data != loc1 && temp->data != loc2)
    temp = temp->next;
      newNode->next = temp->next;
      temp->next = newNode;
   }
   printf("\nOne node inserted!!!\n");
}

void removeBeginning()
{
   if(head == NULL)
	printf("\n\nList is Empty!!!");
   else
   {
      struct Node *temp = head;
      if(head->next == NULL)
      {
	 head = NULL;
	 free(temp);
      }
      else
      {
	head = temp->next;
	free(temp);
	printf("\nOne node deleted!!!\n\n");
      }
   }
}
void removeEnd()
{
   if(head == NULL)
   {
      printf("\nList is Empty!!!\n");
   }
   else
   {
      struct Node *temp1 = head,*temp2;
      if(head->next == NULL)
	head = NULL;
      else
      {
	 while(temp1->next != NULL)
	 {
	    temp2 = temp1;
	    temp1 = temp1->next;
	 }
	 temp2->next = NULL;
      }
      free(temp1);
      printf("\nOne node deleted!!!\n\n");
   }
}
void removeSpecific(int delValue)
{
   struct Node *temp1 = head, *temp2;
   while(temp1->data != delValue)
   {
     if(temp1 -> next == NULL){
	printf("\nGiven node not found in the list!!!");
	goto functionEnd;
     }
     temp2 = temp1;
     temp1 = temp1 -> next;
   }
   temp2 -> next = temp1 -> next;
   free(temp1);
   printf("\nOne node deleted!!!\n\n");
   functionEnd:
}

void display()
{
   if(head == NULL)
   {
      printf("\nList is Empty\n");
   }
   else
   {
      struct Node *temp = head;
      printf("\n\nList elements are - \n");
      while(temp->next != NULL)
      {
     printf("%d --->",temp->data);
     temp = temp->next;
      }
      printf("%d --->NULL",temp->data);
   }
}


void main()
{
   int choice,value,choice1,loc1,loc2;
   char ch;

   do{
   printf("\n\n****** MENU ******\n1. Insert in beginning \n2. Insert in End \n3. Insert in between\n4. Display \n5.remove begining \n6.remove specific\n7.remove at end \nEnter your choice: ");
   scanf("%d",&choice);
   switch(choice)
   {
     case 1:
        printf("\nEnter a value:");
        scanf("%d",&value);
        insertAtBeginning(value);
        break;
    
    case 2:
        printf("\nEnter a value:");
        scanf("%d", &value);
        insertAtEnd(value);
        break;
    
    case 3:
        printf("\nEnter value:");
        scanf("%d", &value);
        printf("\nEnter two locations:");
        scanf("%d %d", &loc1, &loc2);
        insertBetween(value,loc1,loc2);
        break;
    
    case 4:
        display();
        break;
    case 5:
        removeBeginning();
        break;
    case 6:
    printf("Enter the value:\n");
    scanf("%d", &value);
    removeSpecific(value);
    default:
        printf("Invalid response");
        break;
   }

   printf("\ndo you want to continue(y/n):");
   scanf(" %c", &ch);
   }while(ch != 'n');
    return;
}