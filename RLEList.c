#include "RLEList.h"

struct RLEList_t {
    //TODO: implement
    char letter;
    int numOfOcc;
    RLEList next_node;
};

//implement the functions here
RLEList RLEListCreate()
{
    RLEList newList = (RLEList)malloc(sizeof(RLEList));

    if (newList == NULL)
    {
        return NULL;
    }
    
    newList->letter = NULL;
    newList->numOfOcc = 0;
    newList->next_node = NULL;

    return newList;
}

void RLEListDestroy(RLEList list)
{
    if (!list)
    {
        return;
    }
    free(list);
}

RLEListResult RLEListAppend(RLEList list, char value)
{
    if (list == NULL || value == NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    
    if (list->letter == value)
    {
        list->numOfOcc++;
        
        return RLE_LIST_SUCCESS;
    }

    else {
        RLEList newNode = RLEListCreate();

        if (newNode == NULL)
        {
            return RLE_LIST_OUT_OF_MEMORY;
        }

        newNode->letter = value;
        newNode->numOfOcc = 1;
        RLEList current = list;
        
        while (true)
        {
            if (current->next_node == NULL)
            {
                current->next_node = newNode;
                break;
            }
            current = current->next_node;
        }
        return RLE_LIST_SUCCESS;
    }
}

int RLEListSize(RLEList list)
{
    int counter = 0;

    if (list == NULL)
    {
        return -1;
    }
    RLEList current = list;

    while (true)
    {
        if (current->next_node == NULL)
        {
            break;
        }
        counter++;
        current = current->next_node;
    }
    return counter;
}

RLEListResult RLEListRemove(RLEList list, int index)
{
    int currentIndex = 0;
    RLEList previous = list;

    if (index > RLEListSize(list))
    {
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }

    if (list == NULL || index == NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }

    if (RLEListSize(list) == 1)
    {
        RLEListDestroy(list);
        return RLE_LIST_SUCCESS;
    }

    for (RLEList ptr = list; ptr != NULL; currentIndex++)
    {
        previous = ptr;
        ptr = list->next_node;
        if (currentIndex == index)
        {
            previous->next_node = ptr->next_node;
            RLEListDestroy(ptr);
            return RLE_LIST_SUCCESS;
        }
    }
}
void print(RLEList list)
{
    RLEList current = list->next_node;

    while (true)
    {
        if (current == NULL)
        {
            break;
        }
        printf("~ %c\n", current->letter);
        current = current->next_node;
    }
}
int main()
{
    RLEList list = RLEListCreate();
    RLEListAppend(list, 'c');
    RLEListAppend(list, 'x');
    print(list);
    RLEListRemove(list, 1);
    print(list);
    printf("size = %d", RLEListSize(list));
    return 0;
}
