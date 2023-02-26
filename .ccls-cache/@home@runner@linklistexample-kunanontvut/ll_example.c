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

int deletes( LLPtr *sPtr,LLPtr *tPtr, int value );
int isEmpty( LLPtr sPtr );
void insert( LLPtr *sPtr,LLPtr *tPtr, int value ,char tname[]);
void printList( LLPtr currentPtr , LLPtr tPtr );
void reverseList( LLPtr currentPtr );
void instructions( void );

int main( void )
{ 
   LLPtr startPtr = NULL,Tmp ,tailPtr = NULL; // initially there are no nodes
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
            insert( &startPtr, &tailPtr , item , tempname ); // insert item in list
            printList( startPtr , tailPtr );
            break;
         case 2: // delete an element
            // if list is not empty
            if ( !isEmpty( startPtr ) ) { 
               printf( "%s", "Enter ID to be deleted: " );
               scanf( "%d", &item );

               // if character is found, remove it
               if ( deletes( &startPtr,&tailPtr, item ) ) { // remove item
                  printf( "ID %d deleted.\n", item );
                  printList( startPtr ,tailPtr );
               } // end if
               else {
                  printf( "ID %d not found.\n\n", item );
               } // end else
            } // end if
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
void insert( LLPtr *sPtr, LLPtr *tPtr , int value , char tname[] )
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
      

     if(*sPtr == NULL){
       newPtr->nextPtr =newPtr;
       newPtr->pPtr = newPtr;
       *sPtr =newPtr;
       *tPtr = newPtr;
       
     }
      // loop to find the correct location in the list       
     else{ 
          if(*sPtr != *tPtr)
           while ( previousPtr != *tPtr && value > currentPtr->data ) {
             previousPtr = currentPtr; // walk to ...               
             currentPtr = currentPtr->nextPtr; // ... next node 
          } // end while                                         
          else{
            if(value > currentPtr->data){
            previousPtr = currentPtr; // walk to ...               
             currentPtr = currentPtr->nextPtr; // ... next node 
              }
          }
          // insert new node at beginning of list
          if ( previousPtr == NULL ) { 
             newPtr->nextPtr = *sPtr;
             newPtr->pPtr = *tPtr;
             (*sPtr)->pPtr = newPtr;
             *sPtr = newPtr;
          } // end if
          else {// insert new node between previousPtr and currentPtr
            if(previousPtr == *tPtr){
              newPtr->nextPtr = *sPtr;
              (*sPtr)->pPtr = newPtr;
              previousPtr->nextPtr = newPtr;
              newPtr->pPtr = previousPtr;
              *tPtr = newPtr;
            }
            else{ 
              previousPtr->nextPtr = newPtr;
              newPtr->pPtr=previousPtr;
              currentPtr->pPtr = newPtr;
              newPtr->nextPtr = currentPtr;
             
            }
          } // end else
    }
   } // end if
   else {
      printf( "%d not inserted. No memory available.\n", value );
   } // end else
} // end function insert

// delete a list element
int deletes( LLPtr *sPtr,LLPtr *tPtr , int value )
{ 
   LLPtr previousPtr; // pointer to previous node in list
   LLPtr currentPtr; // pointer to current node in list
   LLPtr tempPtr; // temporary node pointer

   // delete first node
   if ( value == ( *sPtr )->data ) { 
      tempPtr = *sPtr; // hold onto node being removed
      *sPtr = ( *sPtr )->nextPtr; // de-thread the node
      if(*sPtr != NULL){
        (*sPtr)->pPtr=*tPtr;
        (*tPtr)->nextPtr = *sPtr;
      }
      free( tempPtr ); // free the de-threaded node
      
      return value;
   } // end if
   else { 
      previousPtr = *sPtr;
      currentPtr = ( *sPtr )->nextPtr;

      // loop to find the correct location in the list
      while ( currentPtr != *tPtr && currentPtr->data != value ) { 
         previousPtr = currentPtr; // walk to ...  
         currentPtr = currentPtr->nextPtr; // ... next node  
      } // end while

      // delete node at currentPtr
      if ( currentPtr != *tPtr ) { 
         tempPtr = currentPtr;
         previousPtr->nextPtr = currentPtr->nextPtr;
        currentPtr->nextPtr->pPtr=previousPtr;
        }
      else{
        tempPtr = previousPtr;
        previousPtr->pPtr->nextPtr = currentPtr;
        *tPtr = previousPtr->pPtr;
        currentPtr->pPtr = *tPtr;
        
        }
         free( tempPtr );
         return value;
      
   } // end else

   return '\0';
} // end function delete

// return 1 if the list is empty, 0 otherwise
int isEmpty( LLPtr sPtr )
{ 
   return sPtr == NULL;
} // end function isEmpty

// print the list
void printList( LLPtr currentPtr,LLPtr tPtr )
{ 
    // if list is empty
   if ( isEmpty( currentPtr ) ) {
      puts( "List is empty.\n" );
   } // end if
   else { 
      puts( "The ID is:" );

      // while not the end of the list
     LLPtr tmp = currentPtr;
     while(currentPtr !=  tPtr){
         printf( "%d %s --> ", currentPtr->data,currentPtr->name );
         currentPtr = currentPtr->nextPtr;  
       }
       // end while

      printf( "%d %s --> %d %s\n",currentPtr->data,currentPtr->name,tmp->data,tmp->name );
       
       
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