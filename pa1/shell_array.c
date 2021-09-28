#include <stdio.h>
#include <stdlib.h>
long *Array_Load_From_File(char *filename, int *size)
{

    //opening the file
    FILE *ptr;
    ptr = fopen(filename,"rb");
    if(ptr == NULL)
    {
        *size = 0;
        long *return_ptr = NULL;
        return return_ptr;
    }

    //get the size of the file
    fseek(ptr,0,SEEK_END);
    int size_of_file = ftell(ptr);
    fseek(ptr,0,SEEK_SET);

    //reading data into our line array
    long *long_ptr = (long *) malloc(size_of_file);
    if (ptr == NULL)
    {
        free(long_ptr);

        return NULL;
    }
    fread(long_ptr,size_of_file,1,ptr);

    *size = sizeof(*long_ptr)/sizeof(long);

    return long_ptr;

}

int Array_Save_To_File(char *filename, long *array, int size)
{
    FILE *write_ptr;
    write_ptr = fopen(filename,"wb");
    if (write_ptr == NULL)
    {
        return 1;
    }

    if (array == NULL || size == 0)
    {
        fwrite(array,sizeof(long),0,write_ptr);

    }else
    {
        fwrite(array,size*sizeof(long),1,write_ptr);
    }
    int size_of_file = ftell(write_ptr);
    return size_of_file/sizeof(long);


}

void Array_Shellsort(long *array, int size, long *n_comp)
{
    int step = 1;
    while (step <= size/3)
    {
        step = step*3 + 1;
    }
    while(step > 0)
    {
        for(int s = step; s < size; s++)
        {
            long temp = array[s];
            int j = s;

            while(j >= step  && array[j - step] >= temp)
            {
                array[j] = array[j - step];
                n_comp[0] = n_comp[0] + 1;
                j -= step;
            }
            array[j] = temp;
        }
        step = (step-1)/3;
    }

}

void printArray(long* array, int size) {
  for (int i = 0; i < size; ++i) {
    printf("%ld  ", array[i]);
  }
  printf("\n");
}

int main() {
  int size = 10;
  long *counter_ptr = (long *)malloc(sizeof(long));
  counter_ptr[0] = 0;
  long *data = (long *)malloc(sizeof(long)*size);
  long inputs[10] = {8,3,5,6,1,2,10,7,4,9};
  for(int i = 0; i<size; i++){
    data[i] = inputs[i];
  }
  Array_Shellsort(data, size, counter_ptr);
  printArray(data,size);
  return 0;
}

