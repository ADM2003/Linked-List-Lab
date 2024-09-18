// list/list.c
//
// Implementation for linked list.
//
// <Author>


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "list.h"


list_t *list_alloc() {
  list_t* mylist =  (list_t *) malloc(sizeof(list_t));
  if (!mylist) {
    printf("Memory allocation failed\n");
    return NULL;
}
  mylist->head = NULL;
  mylist->tail = NULL;
  return mylist;
}


void list_free(list_t *l) {
  node_t* curr = l->head;
  while (curr != NULL) {
    node_t* next = curr->next;
    free(curr);
    curr = next;
  }
  free(l);
}


void list_print(list_t *l) {
  node_t* curr = l->head;
  while (curr != NULL) {
    printf("%d -> ", curr->value);
    curr = curr->next;
  }
  printf("NULL\n");
}


char * listToString(list_t *l) {
  char* buf = (char *) malloc(sizeof(char) * 10024);
  char tbuf[20];
  buf[0] = '\0';

  node_t* curr = l->head;
  while (curr != NULL) {
    sprintf(tbuf, "%d->", curr->value);
    strcat(buf, tbuf);
    curr = curr->next;  
  }
  strcat(buf, "NULL");
  return buf;
}


int list_length(list_t *l) {
  int count = 0;
  node_t* curr = l->head;
  while (curr != NULL) {
    count++;
    curr = curr->next;
  }
  return count;
}


void list_add_to_back(list_t *l, elem value) {
  node_t *new_node = getNode(value);
  if (l->tail == NULL) {
    l->head = new_node;
    l->tail = new_node;
  } else {
    l->tail->next = new_node;
    l->tail = new_node;
  }
}
void list_add_to_front(list_t *l, elem value) {
  node_t *new_node = getNode(value);
  if (l->head == NULL) {
    l->head = new_node;
    l->tail = new_node;
  } else {
    new_node->next = l->head;
    l->head = new_node;
  }
}


node_t * getNode(elem value) {
  node_t *new_node = (node_t *) malloc(sizeof(node_t));
  if (!new_node) {
    printf("Memory allocation failed\n");
    return NULL;
  }
  new_node->value = value;
  new_node->next = NULL;
  return new_node;
}


void list_add_at_index(list_t *l, elem value, int index) {
  if (index < 0 || index > list_length(l)) {
    printf("Index out of bounds\n");
    return;
  }
  if (index == 0) {
    list_add_to_front(l, value);
    return;
  }


  node_t *cur_node = getNode(value);
  node_t *curr = l->head;
  int i;
  for (i = 0; i < index - 1 && curr != NULL; i++) {
    curr = curr->next;
  }


  if (curr == NULL) {
    printf("Index out of bounds\n");
    return;
  }


  cur_node->next = curr->next;
  curr->next = cur_node;


  if (cur_node->next == NULL) {
    l->tail = cur_node;
  }


}


elem list_remove_from_back(list_t *l) {
  if (l->head == NULL) return -1;  


  if (l->head == l->tail) {
    elem value = l->head->value;
    free(l->head);
    l->head = NULL;
    l->tail = NULL;
    return value;
  }


  node_t* curr = l->head;
  while (curr->next != l->tail) {
    curr = curr->next;
  }


  elem value = l->tail->value;
  free(l->tail);
  l->tail = curr;
  l->tail->next = NULL;
  return value;
}


elem list_remove_from_front(list_t *l) {
  if (l->head == NULL) return -1;  


  node_t* temp = l->head;
  elem value = temp->value;
  l->head = l->head->next;


  if (l->head == NULL) {
    l->tail = NULL;  
  }


  free(temp);
  return value;
}
elem list_remove_at_index(list_t *l, int index) {
  if (index < 0 || index >= list_length(l)) {  
    printf("Index %d out of bounds\n", index);
    return -1;
  }

  if (index == 0) {
    return list_remove_from_front(l);
  }

  node_t* curr = l->head;
  int i;
  for (i = 0; i < index - 1 && curr->next != NULL; i++) {
    curr = curr->next;
  }

  if (curr->next == NULL) return -1;

  node_t* temp = curr->next;
  elem value = temp->value;
  curr->next = temp->next;
  if (curr->next == NULL) {
    l->tail = curr;
  }
  free(temp);
  return value;
}


bool list_is_in(list_t *l, elem value) {
  node_t* curr = l->head;
  while (curr != NULL) {
    if (curr->value == value) return true;
    curr = curr->next;
  }
  return false;
}
elem list_get_elem_at(list_t *l, int index) {
  if (index < 0 || index >= list_length(l)) {  
    printf("Index %d out of bounds\n", index);
    return -1;  
  }

  node_t* curr = l->head;
  int i;
  for (i = 0; i < index && curr != NULL; i++) {
    curr = curr->next;
  }

  if (curr == NULL) return -1;
  return curr->value;
}



int list_get_index_of(list_t *l, elem value) {
  int index = 0;
  node_t* curr = l->head;
  while (curr != NULL) {
    if (curr->value == value) return index;
    curr = curr->next;
    index++;
  }
  return -1;
}
