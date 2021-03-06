
#include<stdio.h>
#include<string.h>

struct node
{
	char firstName[30];
	char lastName[30];
	char phone[13];
	
	struct node *next; 
};

struct node *head = NULL; //the first node is pointing to nothing in the beginning
struct node record; //a temporary node of type struct 

void options();
void addContact();
void retrieveContact(char[]);
void deleteContact(char[]);
void loadContacts();
void saveChanges();
void insertEnd(char[], char[], char[]);
void print();
void clearList();

int main()
{
	printf("------------PHONE BOOK-------------\n");

	loadContacts();

	//!!print function can be used here as well!!

	options();

	return 0;
}

void options()
{
	int option;
	char name[30];
	char phone[13];


	//the loop continues till the time user enters 6 to exit the application
	do
	{
		printf("\n\nPlease choose one of the following option:\n");
		printf("1. Add a contact\n");
		printf("2. Search a contact\n");
		printf("3. Delete a contact\n");
		printf("4. Load phonebook (make sure to save your changes!)\n");
		printf("5. Save changes\n");
		printf("6. Enter any other to exit\n\n");
	
		scanf("%d", &option); //retrieves the option chosen by user
		
		switch(option)	
		{
			case 1: 
				addContact(); //addCOntact() function is called
				printf("\nRecord Added. Please Save your changes\n");
				break;

			case 2:
				printf("\nEnter the first name of the person\n");
				scanf("%s",&name); //takes user input as the name of the person whose phonebook record needs to be dispalyed
				retrieveContact(name); //retrieveContact() function is called
				break;

			case 3:
				printf("\nEnter the first name of the person\n");
				scanf("%s",&name); //takes user input as the name of the person whose phonebook record needs to be dispalyed
				retrieveContact(name); //retrieveContact() function is called
				
				//The application now displays a list of records with the same name as searched by the user.
				//The user can now enter the phone number of the record he/she wants to delete
				
				printf("\n\nEnter the phone number of the record you would like to delete\n"); 
				scanf("%s",&phone); //takes phonenumber as the user input
				deleteContact(phone); //removes the record where the above taken input i.e. phonenumber matches in the phone book
				printf("\nPlease Save your changes\n");
				break;

			case 4:
				clearList(); //clearList() function is called to remove all the elements from the linked list and reset it
				loadContacts(); //loadContacts() functoin is called to scan the records from the file and print it on screen
				break;			//as well as to start inserting the elements into the linked list all over again
				
				//!!print function can be used here as well!!
				
			case 5:
				saveChanges(); //saveChanges() function is called to retrieve values from the linked list and write it in the txt file
				printf("\n");
				break;

			case 6:
				exit(0); //to close the application
				break;
		}
	}
	while(option<=5);
}

void addContact()
{
	char firstName[30];
	char lastName[30];
	char phone[13];
	
	printf("\nEnter first name\n");
	scanf("%s",&firstName);	//first name of the record to be inserted
	printf("\nEnter last name\n");
	scanf("%s",&lastName);	//last name of the record to be inserted
	printf("\nEnter the phone number in XXX-XXX-XXXX format\n");
	scanf("%s",&phone);	//phone of the record to be inserted

	insertEnd(firstName, lastName, phone); //insertEnd() function is called to insert the three values in into 
											//the linked list at the end
}

void retrieveContact(char fname[30])
{
	FILE *fp; //pointer to iterate through the file

	fp = fopen("phoneBook.txt", "r"); //creating a file object and giving the access priviledge to read only

	if(fp == NULL)
	{
		printf("\nError in opening file\n"); //display this message if an error occurs while accessing the file
	}
	else
	{
		printf("\nThe matching records stored in phone book are: \n\n");

		printf("First Name\t\tLast Name\t\tPhone Number\n");
		
		while(fscanf(fp,"%s%s%s",record.firstName, record.lastName, record.phone)!=EOF) //the loop continues till the time there're
																						//no more records in the file to be scanned
		{
			if(strcmp(fname, record.firstName)==0) //condition to check if the name entered by user matches the name in the file.
			{
				printf("\n%s\t\t\t%s\t\t\t%s", record.firstName, 
					record.lastName, record.phone); //print data of the matching record
			}
			else
			{
				continue;
			}
		}
		
		fclose(fp); //close the file object
	}
}

void deleteContact(char phonenum[13])
{
	struct node *temp = head; //temporary pointer pointing to the head of the list
	struct node *prev = NULL; //node named prev pointing to null

    if(strcmp(temp->phone,phonenum)==0) //condition to check if the phone number eneterd by user matches the one in teh first record
	{		
		head = head->next; //remove the original node head 
		printf("\nRecord Deleted\n");
        return;
    }

    while(temp!=NULL) //iterate through the linked list till we reach the last element
	{
        if(strcmp(temp->phone,phonenum)==0) //comparing strings
		{
            prev->next = temp->next; //shift the position of node prev
			printf("\nrecord Deleted\n");
			free(temp); //remove temp
            return;
        }
		else
		{
			//if strings do not compare, set prev as equal to temp and move to temp's next location
			prev = temp;
			temp = temp->next;
		}
    }
}

void loadContacts()
{

	clearList(); //clearList() function is called

	char firstName[30];
	char lastName[30];
	char phone[13];

	FILE *fp; //pointer to iterate through the file

	fp = fopen("phoneBook.txt", "r"); //creating a file object and giving the access priviledge to read only

	if(fp == NULL)
	{
		printf("\nError in opening file\n"); //display this message if an error occurs while accessing the file
	}
	else
	{
		printf("\nThe records stored in phone book are: \n\n");

		printf("First Name\t\tLast Name\t\tPhone Number\n");
		
		while(fscanf(fp,"%s%s%s",firstName,lastName,phone)!=EOF) //the loop continues till the time there're
																//no more records in the file to be scanned
		{
			printf("\n%s\t\t\t%s\t\t\t%s",firstName,lastName,phone); //print the records on the screen
			insertEnd(firstName, lastName, phone); //start inserting the records from the file to the linked list
		}
		fclose(fp);
	}
}

void saveChanges()
{
	FILE *fp; //pointer to iterate through the file

	struct node *temp = head; //temporary pointer pointing to the head of the list

	fp = fopen("phoneBook.txt", "w"); //creating a file object and giving the access priviledge to write only

	if(fp == NULL)
	{
		printf("\nError in opening file\n"); //display this message if an error occurs while accessing the file
	}
	else
	{
		while(temp != NULL) //loop continues till we reach the end of the linked list
		{
			fprintf(fp, "%s\t\t%s\t\t%s\n", temp->firstName, temp->lastName, temp->phone); //reading data from the linked list 
																						  //and writing it to the file

			temp = temp->next; //move to the next node
		}

		printf("All changes have been successfully saved!");

		fclose(fp);
	}
}

void insertEnd(char fname[30], char lname[30], char phone[13])
{
	struct node *newNode;//pointer to insert a new node
	newNode = (struct node *)malloc(sizeof(struct node)); //allocating memory
	strcpy(newNode->firstName, fname); //inserting value to firstName using pointer
	strcpy(newNode->lastName, lname); //inserting value to lastNAme using pointer
	strcpy(newNode->phone, phone); //inserting value to phone using pointer

	newNode->next = NULL; //setting the position of newNode's next node to null

	if(head == NULL) //condition to find if list is initially empty
	{
		head = newNode; //header node is pointing to newly created node
	}
	else
	{
		struct node *temp = head; //temporary pointer pointing to the head of the list
		while(temp->next!=NULL) //we keep on moving forward untill the next pointer
								//is NULL
		{
			temp = temp->next; //moving to the next node
		}
		temp->next = newNode;
	}
}

void print(void) //this function might not have been used in the application to display the records in the window,
				//but it does take the linked list and print all the nodes. The only difference between this function
				//and load function is that the load function scans the record from the txt file rather than from list.
				//This function proved helpful in finding whether a list has been actually generated or not.
{
	printf("First Name\t\tLast Name\t\tPhone Number\n");

	if(head == NULL) //to verify if the list is empty
	{
		printf("\nThe list is empty\n");
	}
	else
	{
		struct node *temp = head; //creating a temporary pointer to traverse
								//the whole list and is initialised with the address
								//where head points to

		while(temp->next!=NULL) //we keep on moving forward untill the next pointer
								//is NULL
		{
			printf("\n%s\t\t\t%s\t\t\t%s", temp->firstName, temp->lastName, temp->phone);
			temp = temp->next; //moving to the next node
		}

		printf("\n%s\t\t\t%s\t\t\t%s", temp->firstName, temp->lastName, temp->phone);
	}
}

void clearList()
{
	struct node *temp = head; //temporary node pointing to head of the list
  	struct node *nextNode = NULL; //a node pointing to null
  
   	while (temp!=NULL)  //loop continues till the time we dont reach end of the list
   	{ 
		nextNode = temp->next; //assigning address of nextNode to temp's next node
   	    free(temp); //deleting the node temp
 	  	temp = nextNode; 
   	} 
   	 head = NULL; //assigning first node of list as null (deleted)
}
