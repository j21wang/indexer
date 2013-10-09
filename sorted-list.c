/*
 * sorted-list.c
 */

#include	<string.h>
#include <stdio.h>
#include	"sorted-list.h"

/*int compareInts(void *p1, void *p2)
{
	int i1 = *(int*)p1;
	int i2 = *(int*)p2;

	return i1 - i2;
}

int compareDoubles(void *p1, void *p2)
{
	double d1 = *(double*)p1;
	double d2 = *(double*)p2;

	return (d1 < d2) ? -1 : ((d1 > d2) ? 1 : 0);
}

int compareStrings(void *p1, void *p2)
{
	char *s1 = p1;
	char *s2 = p2;

	return strcmp(s1, s2);
}
*/

SortedListPtr SLCreate(CompareFuncT cf) {
	SortedListPtr s1 = (SortedListPtr) malloc(sizeof(struct SortedList));
	Node *head = (Node *) malloc(sizeof(struct Node));

	head->data = NULL;
	head->next = NULL;
   (*head).ptrCount = 1;
   (*head).deleted = 0;

	s1->head = head;
	s1->cf = cf;
	(*s1).size = 0;

	return s1;
}

SortedListIteratorPtr SLCreateIterator(SortedListPtr list) {
	SortedListIteratorPtr slip = (SortedListIteratorPtr) malloc(sizeof(struct SortedListIterator));
	slip->list = list;
	slip->curr = list->head;
   (*(list->head)).ptrCount++;
	return slip;
}

int SLInsert(SortedListPtr list, void *newObj) {

   if (newObj == NULL) {
      return 0;
   }

	if ((*list).size == 0) {
		(list->head)->data = newObj;
      (*(list->head)).deleted = 0;
		(*list).size++;
		return 1;
	}

	Node *newObjectNode = (Node *) malloc(sizeof(struct Node));
   newObjectNode->data = newObj;
   (*newObjectNode).ptrCount = 0;
   (*newObjectNode).deleted = 0;

	Node *curr = list->head;
   Node *temp = curr;
	CompareFuncT cf = list->cf;

	while (curr != NULL && cf(newObj, curr->data) < 0 ) {
      temp = curr;
      curr = curr->next;
	}

   if (curr == list->head) {
      newObjectNode->next = curr;
      list->head = newObjectNode;
      (*newObjectNode).ptrCount++;
   } else if (curr != NULL) {
      temp->next = newObjectNode;
      newObjectNode->next = curr;
      (*newObjectNode).ptrCount++;
   } else {
	  temp->next = newObjectNode;
	  newObjectNode->next = NULL;
     (*newObjectNode).ptrCount++;
	}
   
   (*list).size++;
   return 1;
	
}

int SLRemove(SortedListPtr list, void *newObj) {

	if ((*list).size == 0) {
		return 0;
	}

   Node *curr = list->head;
   Node *temp = curr;
   CompareFuncT cf = list->cf;

   while(curr != NULL && cf(newObj, curr->data) != 0){
      temp = curr;
      curr = curr->next;
   }

   if (curr == NULL) {
      return 0;
   }

   if ((*list).size == 1) {   //Deleting from single-node list
      curr->data = NULL;
      (*curr).deleted = 1;
      (*list).size--;
      return 1;
   } 

   if (curr->next == NULL) {  //Deleting last element
      temp->next = NULL;
      (*curr).ptrCount--;
      if ((*curr).ptrCount == 0) {  //No iterator pointing to curr
         free(curr);
      } else {
         (*curr).deleted = 1;
      }
      (*list).size--;
      return 1;
   } 

   if (curr == list->head) {  //Deleting head
		temp = curr->next;
		list->head = temp;
      (*curr).ptrCount--;
      if ((*curr).ptrCount == 0) {
		   free(curr);
      } else {
         (*curr).deleted = 1;
         (*temp).ptrCount++;
      }
      (*list).size--;
		return 1;
	}

   temp->next = curr->next;
   (*curr).ptrCount--;
   (*(temp->next)).ptrCount++;
   if ((*curr).ptrCount == 0) {
      free(curr);
   } else {
      (*curr).deleted = 1;
   }
   
   (*list).size--;
   return 1;

}

void *SLNextItem(SortedListIteratorPtr iter) {
   if (iter == NULL) {
      return NULL;
   }
   if ((*(iter->list)).size == 0) { //Empty list
      return NULL;
   } 
	void *item;
   Node *temp;
	Node *node = iter->curr;
	if (node == NULL || node->data == NULL) {
		return NULL;
	}
   while (node != NULL && (*node).deleted == 1) {
      temp = node;
      node = node->next;
      (*temp).ptrCount--;
      if ((*temp).ptrCount == 0) {
         free(temp);
      }
      iter->curr = node;
   }
   if (node == NULL || node->data == NULL) {
      return NULL;
   }
	item = node->data;
	iter->curr = node->next;
   (*node).ptrCount--;
   if (iter->curr != NULL) {
      (*(iter->curr)).ptrCount++;
   }
	return item;
}

void SLDestroy(SortedListPtr list) {
   if (list == NULL) {
      return;
   }
   Node *curr = list->head;
   Node *temp = curr;
   while (curr != NULL) {
      curr = curr->next;
      (*temp).ptrCount--;
      if ((*temp).ptrCount == 0) {  //no iterator pointing to it
	     free(temp);
      } else {                      //at least one iterator pointing to it
         (*temp).deleted = 1;
         temp->next = NULL;
      }
      temp = curr;
   }
   free(list);
}

void SLDestroyIterator(SortedListIteratorPtr iter) {
   if (iter == NULL) {
      free(iter);
      return;
   }

   Node *node = iter->curr;
   if (node == NULL) {
      free(iter);
      return;
   }

   if ((*node).deleted == 1) {

      while (1) {

         (*node).ptrCount--;

         if ((*node).ptrCount == 0) {
            iter->curr = node->next;
            free(node);
            node = iter->curr;
            if (node == NULL) {
               break;
            }
         } else {
            break;
         }

      }
      
   }

   free(iter);
         
}
