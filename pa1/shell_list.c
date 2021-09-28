#include <stdio.h>
#include <stdlib.h>
#include "shell_list.h"
#include "list_of_list.h"

Node *List_Load_From_File(char *filename)
{
      //opening the file
    FILE *ptr;
    ptr = fopen(filename,"rb");
    if(ptr == NULL)
    {
        return NULL;
        fclose(ptr);
    }


    //get the size of the file
    fseek(ptr,0,SEEK_END);
    int size_of_file = ftell(ptr);
    fseek(ptr,0,SEEK_SET);

    Node* head = NULL;
    Node* tail = NULL;
    int value = 0;
    int *valueptr = &value;
    //reading data into our line array
    while(1)
    {
        //Exit condition
        if(ftell(ptr) == size_of_file)
        {
            break;
        }

        //initiate memory for a new node
        Node* new_node = (Node*)malloc(sizeof(Node));

        if(new_node == NULL)
        {
            return NULL;
            fclose(ptr);
        }
        //assigning next of the new node as null
        new_node-> next = NULL;

        //read into new node value
        fread(valueptr, sizeof(long), 1, ptr);
        new_node->value = *valueptr;
        if(head == NULL)
        {
            head = new_node;
            tail = new_node;
        }else
        {
            tail -> next = new_node;
            tail = tail -> next;
        }

    }
    fclose(ptr);
    return head;
}

int List_Save_To_File(char *filename, Node *list)
{
    FILE *ptr;
    ptr = fopen(filename,"wb");
    if(ptr == NULL)
    {
        return -1;
        fclose(ptr);
    }

    Node* head = list;
    int write_count = 0;
    int value = 0;
    int *valueptr = &value;

    while (head != NULL)
    {
        fwrite(valueptr, sizeof(long), 1, ptr);
        head->value = *valueptr;
        head = head -> next;
        write_count++;
    }
    fclose(ptr);
    return write_count;
}

Node *Create_Node(int data)
{
     Node *head = (Node *)malloc(sizeof(Node));
    if(head == NULL)
    {
        return NULL;
    }
    head->value = data;
    head->next = NULL;
    return head;
}

Node *List_Shellsort(Node *list, long *n_comp)
{
    int step = 1;
    int size = 0;
    Node * ptr = list;
    while(ptr != NULL){
        size++;
        ptr = ptr -> next;
    }
    //get the starting index
    while (step <= size/3)
    {
        step = step*3 + 1;
    }
    //Every iteration is a new step
    for(int s = step; s >= 1; s= (s-1)/3){
        //j determines where the starting is at
        List *list_head = NULL;
        int j = 0;
        //every iteration is a new sub array of the same step
        for(int i = 0; i < s; i++)
        {
            List * subarray = (List *)malloc(sizeof(List));
            if(subarray == NULL){
                return NULL;
            }
            ptr = list;

            //get correct starting point j for the sorting
            for(int inner=0; inner<j; inner++){
                ptr = ptr->next;
            }
            //first node of the subarray
            Node *head = Create_Node(ptr->value);
            subarray->node = head;
            subarray->next = NULL;
            // pointer to the first node of array
            Node * arraynode_ptr = head;
            int counter = 1;
            ptr = ptr->next;

            //for iterating through the shell sort of each subarray
            while(ptr != NULL)
            {
                //if the counter is a equal to the step
                if(counter%s ==0)
                {
                    long temp;
                    Node *new_node = Create_Node(ptr->value);
                    while(arraynode_ptr != NULL)
                    {

                        //sorting, something is wrong with this
                        if (arraynode_ptr->value > new_node->value)
                        {
                            temp = arraynode_ptr -> value;
                            arraynode_ptr -> value = new_node->value;
                            new_node->value = temp;
                        }
                        if (arraynode_ptr->next != NULL)
                        {
                            arraynode_ptr = arraynode_ptr ->next;
                        }
                        else
                        {
                            break;
                        }

                    }
                    arraynode_ptr -> next = new_node;
                    arraynode_ptr = subarray -> node;
                }
                ptr = ptr->next;
                counter++;
            }

            //test print
            Node *list_ptr2 = subarray-> node;
            while(list_ptr2 != NULL)
            {
                list_ptr2 = list_ptr2 ->next;

            }

            //linking the subarrays
            if(list_head == NULL){
                list_head = subarray;
            }else{
                List* list_ptr = list_head;
                while(list_ptr->next != NULL)
                {
                    list_ptr = list_ptr -> next;
                }
                list_ptr -> next = subarray;
            }
            ptr = list;
            j++;
        }

        //sorting the array and rearranging list
        List *list_ptr = list_head;
        ptr = list;
        int level = 0;
        //when original list is not null
        while (ptr != NULL)
        {
            //when downward list is not null
            while(list_ptr != NULL)
            {
                Node *list_node_ptr = list_ptr ->node;
                //get the right value within the subarray
                for(int i = 0; i < level; i++)
                {
                    if(list_node_ptr == NULL)
                    {
                        break;
                    }
                    list_node_ptr = list_node_ptr->next;
                }
                if(list_node_ptr != NULL)
                {
                    ptr->value = list_node_ptr->value;
                    ptr = ptr->next;
                }
                list_ptr = list_ptr -> next;
            }
            level++;
            list_ptr = list_head;
        }
    }
    return list;
}

int main(){
    int counter = 0;
    int array[] = {8,2,1,4,9,3,5,6,5};
    int size_alt = sizeof(array)/sizeof(array[0]);

    Node *head = (Node *)malloc(sizeof(Node));
    head -> next = NULL;
    head -> value = array[counter];
    counter++;

    Node *ptr = head;

    for(int i=0; i<8; i++){
        while(ptr->next !=NULL){
            ptr = ptr->next;
        }
        Node *second = (Node *)malloc(sizeof(Node));
        ptr->next=second;
        second->next = NULL;
        second->value = array[counter];
        counter++;
        ptr = head;
    }
    long testlong= 5;
    long *longptr = &testlong;
    Node* lister = List_Shellsort(head, longptr);
    while(lister != NULL)
    {
        printf("%ld",lister->value);
        lister = lister -> next;
    }
    return 0;
}
