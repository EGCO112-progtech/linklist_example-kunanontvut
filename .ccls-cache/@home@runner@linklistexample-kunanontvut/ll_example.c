// Fig. 12.3: fig12_03.c
// Inserting and deleting nodes in a list
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// self-referential structure                       
struct Node {                                      
   int data;
   char name[50]; // each listNode contains a character 
   struct Node *nextPtr; // pointer to next node
   struct Node *pPtr;
   
}; // end structure listNode                        

typedef struct Node LLnode; // synonym for struct listNode
typedef LLnode *LLPtr; // synonym for ListNode*

// prototypes
int m;
int deletes( LLPtr *sPtr, int value , LLPtr *LastPtr );
int isEmpty( LLPtr sPtr );
void insert( LLPtr *sPtr, int value ,char tname[] , LLPtr *lPtr);
void printList( LLPtr currentPtr);
void reverseList( LLPtr currentPtr );
void instructions( void );

int main( void )
{ 
   LLPtr startPtr = NULL,Tmp,lastPtr = NULL; // initially there are no nodes
   unsigned int choice; // user's choice
   int item;// char entered by user
   char tempname[50];

   instructions(); // display the menu
   printf( "%s", "? " );
   scanf( "%u", &choice );

   // loop while user does not choose 3
   while ( choice != 3 ) { 

      switch ( choice ) { 
         case 1:
            printf( "%s", "Enter a ID: " );
            scanf( "%d", &item );
            printf( "%s", "Enter a name: " );
            scanf("%s",tempname);
            insert( &startPtr, item , tempname , &lastPtr ); // insert item in list
            printList( startPtr );
            break;
         case 2: // delete an element
            // if list is not empty
            if ( !isEmpty( startPtr ) ) { 
               printf( "%s", "Enter ID to be deleted: " );
               scanf( "%d", &item );

               // if character is found, remove it
               if ( deletes( &startPtr, item , &lastPtr )){ // remove item
                  printf( "ID %d deleted.\n", item );
                  printList( startPtr );
               } // end if
               else {
                  printf( "ID %d not found.\n\n", item );
               } // end else
            }   // end if
            else {
               puts( "List is empty.\n" );
            } // end else

            break;
         default:
            puts( "Invalid choice.\n" );
            instructions();
            break;
      } // end switch

      printf( "%s", "? " );
      scanf( "%u", &choice );
   } // end while
  /* Clear all nodes at the end of nodes*/

  Tmp =startPtr;
  while(Tmp!=NULL){
    startPtr = Tmp->nextPtr;
    printf("delete ID %d\n",Tmp->data);
    free(Tmp);
    Tmp = startPtr;
  }
  
   puts( "End of run." );
} // end main

// display program instructions to user
void instructions( void )
{ 
   puts( "Enter your choice:\n"
      "   1 to insert an element into the list.\n"
      "   2 to delete an element from the list.\n"
      "   3 to end." );
} // end function instructions

// insert a new value into the list in sorted order
void insert( LLPtr *sPtr, int value , char tname[] , LLPtr *lPtr)
{ 
   LLPtr newPtr; // pointer to new node
   LLPtr previousPtr; // pointer to previous node in list
   LLPtr currentPtr; // pointer to current node in list

   newPtr =(LLPtr) malloc( sizeof( LLnode ) ); // create node

   if ( newPtr != NULL ) { // is space available
      newPtr->data = value;// place value in node
      strcpy(newPtr->name,tname);
      newPtr->nextPtr = NULL; // node does not link to another node
      newPtr->pPtr = NULL;
       
      previousPtr = NULL;
      currentPtr = *sPtr;

      // loop to find the correct location in the list       
      while ( currentPtr != *lPtr && value > currentPtr->data ) {
         previousPtr = currentPtr; // walk to ...               
         currentPtr = currentPtr->nextPtr; // ... next node 
      } // end while                                         

      // insert new node at beginning of list
      if ( previousPtr == NULL ) { 
         newPtr->nextPtr = *sPtr;
         if(currentPtr != NULL && *lPtr == NULL)*lPtr =currentPtr;
         if(currentPtr!=NULL)currentPtr->pPtr=newPtr;
           
         *sPtr = newPtr;
         
         if(*lPtr != *sPtr && currentPtr!=NULL){
           (*lPtr)->nextPtr = *sPtr;
         }
      } // end if
      else { // insert new node between previousPtr and currentPtr
         previousPtr->nextPtr = newPtr;
         newPtr->pPtr=previousPtr;

         if(currentPtr != *lPtr)newPtr->nextPtr = currentPtr;
         if(currentPtr == *lPtr &&*lPtr != NULL){currentPtr->pPtr=newPtr;
                              currentPtr->nextPtr = *sPtr;
           }
        
         
      } // end else
     if(*lPtr != NULL)printf("//%d %s//",(*lPtr)->data,(*lPtr)->name);
   } // end if
   else {
      printf( "%d not inserted. No memory available.\n", value );
   } // end else
} // end function insert

// delete a list element
int deletes( LLPtr *sPtr, int value ,LLPtr *lPtr)
{ 
   LLPtr previousPtr; // pointer to previous node in list
   LLPtr currentPtr; // pointer to current node in list
   LLPtr tempPtr; // temporary node pointer
   LLPtr ppreviousPtr; 
   // delete first node
   if ( value == ( *sPtr )->data ) { 
      tempPtr = *sPtr; // hold onto node being removed
      *sPtr = ( *sPtr )->nextPtr; // de-thread the node
      if(*sPtr)(*sPtr)->pPtr=NULL;
      free( tempPtr ); // free the de-threaded node
     if(*lPtr != NULL)(*lPtr)->nextPtr =*sPtr;
      
      return value;
   } // end if
   else { 
      previousPtr = *sPtr;
      currentPtr = ( *sPtr )->nextPtr;

      // loop to find the correct location in the list
      while ( currentPtr != *sPtr && currentPtr->data != value ) { 
         previousPtr = currentPtr; // walk to ...  
         currentPtr = currentPtr->nextPtr; // ... next node  
      } // end while

      // delete node at currentPtr
      if ( currentPtr != *sPtr ) { 
         tempPtr = currentPtr;
         previousPtr->nextPtr = currentPtr->nextPtr;
         
         free( tempPtr );
         return value;
      }// end if
     else { 
         tempPtr = previousPtr;
         ppreviousPtr->nextPtr = currentPtr;
         currentPtr->pPtr = ppreviousPtr;
        *lPtr = ppreviousPtr;
         free( tempPtr );
         return value;
      }
   } // end else

   return '\0';
} // end function delete

// return 1 if the list is empty, 0 otherwise
int isEmpty( LLPtr sPtr )
{ 
   return sPtr == NULL;
} // end function isEmpty

// print the list
void printList( LLPtr currentPtr)
{ 
  LLPtr fpptr = currentPtr;
  int c=0;
   // if list is empty
   if ( isEmpty( currentPtr ) ) {
      puts( "List is empty.\n" );
   } // end if
   else { 
     
      puts( "The ID is:" );

      // while not the end of the list
      while ( currentPtr->nextPtr != NULL ) {
         printf( "%d %s --> ", currentPtr->data,currentPtr->name );
         currentPtr = currentPtr->nextPtr;
            c++;
      } // end while

      printf( "%d %s --> %d %s \n",currentPtr->data,currentPtr->name,fpptr->data,fpptr->name);
       

     
       
   } // end else
} // end function printList

void reverseList( LLPtr currentPtr )
{ 
   
   // if list is empty
   if ( isEmpty( currentPtr ) ) {
      puts( "List is empty.\n" );
   } // end if
   else { 
      puts( "The reverse list is:" );
      while ( currentPtr->nextPtr!= NULL ) {
         currentPtr = currentPtr->nextPtr;   
      }

      // while not the end of the list
      while ( currentPtr->pPtr!= NULL ) {
         printf( "%d --> ", currentPtr->data );
         currentPtr = currentPtr->pPtr;   
      } // end while

      printf( "%d --> NULL\n",currentPtr->data );
       

     
       
   } // end else
} // end function reverseList