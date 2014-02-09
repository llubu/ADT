/*
* Basic Trie implementation
* @author: dZ0NE
* v1.0: Handles a-z, NOT Case sensitive
*/

# include <stdio.h>
# include <stdlib.h>
# include "trie.h"

/*
* Function to insert a new string in the trie 
* @param: node *dir: The trie tree DS root node
* @param: char str : The character string that will be added to the trie
* @RET: 0/1: On success or failure
*/

int insert_node(node **dir, char *str)
{
    node *newnode = NULL;	// for new node to be added if any
    node *root = NULL;		// To hold address of root node
    char ch;			// temporary varaible to hold character at head of str
    int i = 0;

    char *st = str;
    root = (*dir);

    ch = st[0];

    if (root == NULL)
    {
	printf("\n The dict is NULL, INITIALIZING with the string passed \n");
	if ((newnode = malloc(sizeof(node))) == NULL)
	{
	    printf("\n Cant allocate memory \n");
	    return 1;
	}
	else
	{
	    for (i = 1; i < 27; i++)
	    {
		newnode->child[i] = NULL;
	    }
	    newnode->child[0] = (node *)1;
	   (*dir) = newnode;	// root node added
	   root = (*dir);
	}
    }

    while ( root && (root->child[(ch - 'a') + 1]) )
    {
	if (ch  == '\0')
	{
	    root->child[0] = NULL;  // flag to indicate termination of a string here
	    break;
	}
	root = root->child[(ch - 'a') + 1];
	ch = *(++st);	// this will put the next char in str in ch
    }

    if (ch == '\0')	// We have reached eos and it was already there in dict
    {

	printf("\n :%s: String added to dictionary \n", str);
	return 0;
    }
    else
    {
	while (ch != '\0')
	{
	    if ((newnode = malloc(sizeof(node))) == NULL)
	    {
		printf("\n Cant allocate memory in 2 malloc \n");
		return 1;
	    }
	    else
	    {
	        for (i = 1; i < 27; i++)
	        {
		    newnode->child[i] = NULL;
	        }
	        newnode->child[0] = (node *)1;
	    }
	    root->child[(ch - 'a') + 1] = newnode;
	    root = root->child[(ch - 'a') + 1];
	    ch = *(++st);
	}
	root->child[0] = NULL;
    }

    return 0;
}

/*
* This function prints all traverses the trie and prints all the strings present in it
* @param: node *dict: pointer to root node of the trie Data Structure
* @RET: void
*/

void print_trie(node *dict)
{
    node *current = NULL;
    int i = 0;

    for (i = 0; i < 27; i++)
    {
	if (!(dic->child[0]))
	{
	    printf("\n EMPTY");
	}
	while (

    

int main()
{
    node *current = NULL;
    node *head = NULL;
    int val;

    val = insert_node(&head, "abhiroop");

    

    return 0;
}
