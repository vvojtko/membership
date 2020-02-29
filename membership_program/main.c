
// C program to demonstrate insert operation in binary search tree
#include<stdio.h>
#include<stdlib.h>
#include "string.h"


//defining a struct for BST nodes
//I defined "member" as "node" to simplify creating a BST
struct node     //node is a member of program
{
    char family_name[20];   //key of the BST //variable to store a family name
    char personal_names[80];    //personal names
    int membership_id;          //membership ID
    char email_adress[50];      //email address
    char class_name_of_boat_owned[30];  //class name of boat owned
    char name_or_number_of_boat[30];    //name or number of boat
    struct node *left, *right;      //left is left child of node       //right is right child of node
};

// A utility function to create a new BST member
struct node *newNode(char family_name[20], char personal_names[80], int membership_id, char email_adress[50], char class_name_of_boat_owned[30], char name_or_number_of_boat[30])
{

    struct node *temp;          //defining temporary node
    temp = malloc(sizeof(struct node));     //allocation of memory for temp



    //assigning new values to a temp node
    strcpy(temp->family_name,family_name);
    strcpy (temp->personal_names,personal_names);
    temp->membership_id=membership_id;
    strcpy (temp->email_adress,email_adress);
    strcpy (temp->class_name_of_boat_owned,class_name_of_boat_owned);
    strcpy (temp->name_or_number_of_boat,name_or_number_of_boat);

    temp->left = temp->right = NULL;     //as it is a new node, it has no child yet

    //returning a new node (member)
    return temp;
}

/* A utility function to insert a new node with given key in BST */
struct node* insert(struct node* root, char family_name[20], char personal_names[80], int membership_id, char email_adress[50],
                    char class_name_of_boat_owned[30], char name_or_number_of_boat[30]) {

    if (root == NULL) {     //if root is null - create a new node
        return newNode(family_name, personal_names, membership_id, email_adress, class_name_of_boat_owned, name_or_number_of_boat);

    } else if (strcmp(family_name, root->family_name) < 0) {        //if family name is less than root's family name put a new member on left child of root
        root->left = insert(root->left, family_name, personal_names, membership_id, email_adress, class_name_of_boat_owned, name_or_number_of_boat);
        return root;
    } else if(strcmp(family_name, root->family_name) > 0){          //if family name is greater than root's family name put a new member on right child of root
        root->right = insert(root->right, family_name, personal_names, membership_id, email_adress, class_name_of_boat_owned, name_or_number_of_boat);

        return root;
    }
}

//function to save whole data structure into a file
void saveIntoFile(struct node *root, char filename[30]) {
    //because function using a recursion the file it writes updated structure to has to be deleted and then created by using "a+" in fopen function
    //otherwise it would just add first member, nothing else
    FILE *file;
         //opens file for reading and appending (writing at end of file)

    file = fopen(filename, "a+");     //special format to append data structure
    if (file == NULL) {     //if file does not exist return exit
        perror("Error");
        exit(1);

    } else {
        if (root != NULL) {
            saveIntoFile(root->left, filename);       //recursion

            //writing a member into file
            fprintf(file, "%s\n%s\n%d\n%s\n%s\n%s\n", root->family_name, root->personal_names, root->membership_id,
                    root->email_adress, root->class_name_of_boat_owned, root->name_or_number_of_boat);
           saveIntoFile(root->right, filename);
        }
    }
    fclose(file);
}



//A utility function to search for node that contains a specified membership ID
void searchID(struct node* root, int id){       //take root as parameter and id you look for
    if(root != NULL) {
        if (root->membership_id == id)      //if search id is the same as checking root->id print the root
            printf("\n%s\n%s\n%d\n%s\n%s\n%s\n--------------------------", root->family_name, root->personal_names, root->membership_id, root->email_adress,
                    root->class_name_of_boat_owned, root->name_or_number_of_boat);
        searchID(root->left, id);       //recursion
        searchID(root->right, id);      //recursion
    }
}

//A utility function to search for node (member) that contains a specified class
void searchClass(struct node* root, char *class){
    if(root != NULL) {
        if ((strcmp(root->class_name_of_boat_owned, class) == 0))       //string comparision, if the same as search class as checking root->class print the root
            printf("\n%s\n%s\n%d\n%s\n%s\n--------------------------", root->family_name,
                    root->personal_names, root->membership_id, root->class_name_of_boat_owned, root->name_or_number_of_boat);
        searchClass(root->left, class);     //recursion
        searchClass(root->right, class);    //recursion
        }
    }


//function to display all members in order of their family names
void inorder(struct node *root)
{
    if (root != NULL)
    {
        inorder(root->left);        //recursion
        printf("\n%s\n%s\n%d\n%s\n%s\n%s\n--------------------------", root->family_name, root->personal_names, root->membership_id,
                root->email_adress, root->class_name_of_boat_owned, root->name_or_number_of_boat);      //print root
        inorder(root->right);   //recursion
    }
}

//function to search for a node of specified family name
struct node* search(struct node *root, char family_name[20])
{
    if(root == NULL){
        printf("\nnull");
        return NULL;
    }else if(strcmp(root->family_name,family_name) == 0){       //string comparision, if the same as searched family name as checking root->familyname - print the root
        printf("\n%s\n%s\n%d\n%s\n%s\n%s\n--------------------------", root->family_name, root->personal_names, root->membership_id,
               root->email_adress, root->class_name_of_boat_owned, root->name_or_number_of_boat);      //print root
        return root;
    }else if(strcmp(root->family_name,family_name) < 0){
        return search (root->right,family_name);        //recursion
    }else{
        return search(root->left, family_name);     //recursion
    }

}

 // Driver Program to test above functions
int main() {

    struct node *root = NULL;       //initialize a root of BST

    //temporary variables used to get input from user or look for one of these in BST
    //as well as for reading

    char family_name[20];
    char personal_names[80];
    int id = 0;
    char email_adress[50];
    char class_name_of_boat_owned[30];
    char name_or_number_of_boat[30];

    int number; //variable used to scan a file till the end of file
    FILE *file;     //pointer to file
    char filename[40];  //variable to get a name of file from user

    //prompt to get user input to open a proper file

    printf("Type in a name of the file\n");
    scanf("%s", &*filename);


    file = fopen(filename, "r+"); //open specified file

    if (file == NULL) {
        perror("Error");
        exit(1);
    } else {
        while (fscanf(file, "%d", &number) == 0) {
            //scan file, scan 6 lines and assign them to new node (member) and insert it into BST
            fscanf(file, " %[^\n]s", family_name);
            fscanf(file, " %[^\n]s", personal_names);
            fscanf(file, " %d", &id);
            fscanf(file, " %[^\n]s", email_adress);
            fscanf(file, " %[^\n]s", class_name_of_boat_owned);
            fscanf(file, " %[^\n]s", name_or_number_of_boat);
           // printf(" \n%s \n%s \n%d \n%s \n%s \n%s ", family_name, personal_names, id, email_adress, class_name_of_boat_owned, name_or_number_of_boat);
            if (root == NULL) { //if root is NULL, create a new root
                root = insert(root, family_name, personal_names, id, email_adress, class_name_of_boat_owned,
                              name_or_number_of_boat);
            } else {    //if root is different than NULL, insert a new node (member)
                insert(root, family_name, personal_names, id, email_adress, class_name_of_boat_owned,
                       name_or_number_of_boat);

            }
        }
    }

    fclose(file);   //close file

    int ret; //variable used to remove a file when saving data structure
    int choice = 0;     //variable used to switch expression

    while (choice != 6) {
        printf("\n-----MENU-----\n");
        printf("1. Print all members in order of their family names.\n");
        printf("2. Add a new member to data structure\n");
        printf("3. Print details for a single member identied by membership ID\n");
        printf("4. Print all members owning a boat of a given class with their names, membership ID and boat names or numbers\n");
        printf("5. Save the data structure into a file\n");
        printf("6. Exit of program\n");
        printf("Insert a number of option you want to run: ");
        scanf(" %d", &choice);
        switch (choice) {
            case 1:
                printf("print all members in order of family names");
                inorder(root);      //call a function to print out BST in specified order
                break;
            case 2: //case for adding a new member asking for each of data family name, personal names etc...
                printf("\nADDING A NEW MEMBER");
                printf("\nProvide a new member's family name:");
                scanf( " %[^\n]s", family_name);
                printf("\nProvide a new member's personal names:");
                scanf( " %[^\n]s", personal_names);
                printf("\nProvide a new member's membership ID:");
                scanf(" %d", &id);
                printf("\nProvide a new member's email address:");
                scanf( " %[^\n]s", email_adress);
                printf("\nProvide a new member's class name of boat owned:");
                scanf( " %[^\n]s", class_name_of_boat_owned);
                printf("\nProvide a new member's name or number of boat:");
                scanf( " %[^\n]s", name_or_number_of_boat);
                insert(root, family_name, personal_names, id, email_adress, class_name_of_boat_owned, name_or_number_of_boat);      //insert a new node (member) into BST
                break;
            case 3:
                printf("\nPrint details for a single member identied by membership ID\n");
                printf("Provide a membership ID you want to display: ");
                int memId;  //int variable used for comparision to find a member with specified ID in BST
                scanf("%d", &memId);
                searchID(root, memId);  //call a function to search for member with specified ID IN BST
                break;
            case 4:
                printf("4. Print all members owning a boat of a given class with their names, membership ID and boat names or numbers\n");
                char class[30]; //char variable used for comparision to find a member with specified class of boat in BST
                printf("Provide a boat of a given class to display all members that owe it: ");
                scanf(" %[^\n]s", class);
                searchClass(root, class); //call a function to search for member with specified class of boat in BST and print proper prompt
                break;
            case 5:
                ret = remove(filename);        //remove all content from file
                if(ret == 0) {      //if removing succeed - perform saving (with creating a file with same file's name ("members.txt")
                    printf("\nDATA STRUCTURE SAVED INTO FILE");
                    saveIntoFile(root, filename); //save BST into file
                }else{
                    printf("\nCOULD NOT SAVED STRUCTURE INTO FILE, SORRY!");    //print out an error if removing file did not succeed
                }
                break;
            case 6:
                printf("\n ----END OF PROGRAM --- \n");     //if user entered 6 - end of ile
                exit(1);
            default:
                printf("\nOPTION OUT OF RANGE. PLEASE CHOOSE OTHER OPTION OR PRESS 6 TO QUIT THE PROGRAM.");    //default to print warning for user
                break;

        }
    }
    return 0;
}
