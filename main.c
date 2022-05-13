#include <stdio.h>
#include <stdlib.h>

struct node{
 struct node* next;
 int data;
};
typedef struct node node_t;

node_t* allocate_node(int data){
 node_t* ptr = malloc(sizeof(node_t));
 ptr->data = data;
 ptr->next = NULL;
 return ptr;
}

void show_list(node_t* head){
 node_t* ptr = head;
 while(ptr != NULL){
  printf("[%d]->", ptr->data);
  ptr = ptr->next;
 }
 printf("null\n");
 return;
}

node_t* append_node(node_t* head, int new_data){
 node_t* pre = head;
 node_t* cur = head;
 while(cur != NULL){
  pre = cur;
  cur = cur->next;
 }
 if(pre == NULL){
  return allocate_node(new_data);
 }
 pre->next = allocate_node(new_data);
 return head;
}

void free_all_node(node_t* head){
 while(head != NULL){
  printf("free([%d])->", head->data);
  node_t* tmp = head->next;
  free(head);
  head = tmp;
 }
 printf("null\n");
 return;
}

node_t* add_node(node_t* head, int new_data) {
 node_t* NEW = allocate_node(new_data);
 NEW->data = new_data;
 NEW->next = head;
 head = NEW;
 return head;
}

node_t* del_node(node_t* head, int n) {
 if(head == NULL) {
  return head;
 }
 node_t* ptr = head;
 if(n == 0) {
  ptr = ptr->next;
 }
 else { 
   for(int i = 0 ; (ptr != NULL) && (i < n-2) ; i++) {
    ptr = ptr -> next;
  }
  ptr->next = ptr->next->next;
 }
 return ptr;
}

int main(){
 node_t* head = NULL;
 head = append_node(head, 0);
 show_list(head);
 head = append_node(head, 1);
 show_list(head);
 head = add_node(head, -1);
 show_list(head);
 del_node(head, 1);
 show_list(head);
 free_all_node(head);
 return 0;
}
