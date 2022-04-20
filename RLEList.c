#include "RLEList.h"

struct RLEList_t {
    //TODO: implement
    char letter;
    int numOfOcc;
    RLEList next_node;
};

bool isListEmpty(RLEList list)
{
    if (list->next_node == NULL)
    {
        return true;
    }
    return false;
}

//implement the functions here
RLEList RLEListCreate()
{
    RLEList newList = (RLEList)malloc(sizeof(*newList));

    if (newList == NULL)
    {
        return NULL;
    }

    newList->letter = NULL;
    newList->numOfOcc = NULL;
    newList->next_node = NULL;

    return newList;
}

void RLEListDestroy(RLEList list)
{
    if (!list)
    {
        return;
    }
    while (list)
    {
        RLEList toDelete = list;
        list = list->next_node;
        free(toDelete);
    }
}


RLEListResult RLEListAppend(RLEList list, char value)
{
    if (list == NULL || value == NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }


    RLEList current = list;

    while (current->next_node != NULL)
    {
        current = current->next_node;
    }
    if (current->letter == value)
    {
        current->numOfOcc++;
    }
    else
    {
        RLEList newNode = RLEListCreate();

        if (newNode == NULL)
        {
            return RLE_LIST_OUT_OF_MEMORY;
        }

        newNode->letter = value;
        newNode->numOfOcc = 1;
        current->next_node = newNode;
    }
    return RLE_LIST_SUCCESS;
}


int RLE_numOfNodes(RLEList list)
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
    index++;

    if (list == NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }

    if (index > RLEListSize(list) || index < 1)
    {
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }

    int currentIndex = 1;
    RLEList current = list;

    while (true)
    {
        RLEList previous = current;
        current = current->next_node;

        for (int i = current->numOfOcc; i > 0; i--)
        {
            if (index == currentIndex)
            {
                if (current->numOfOcc > 1)
                {
                    current->numOfOcc--;
                    return RLE_LIST_SUCCESS;
                }
                else
                {
                    if (current->next_node != NULL)
                    {
                        if (previous->letter != current->next_node->letter)
                        {
                            previous->next_node = current->next_node;
                            free(current);
                            return RLE_LIST_SUCCESS;
                        }
                        else
                        {
                            previous->numOfOcc += current->next_node->numOfOcc;
                            if (current->next_node->next_node != NULL)
                            {
                                previous->next_node = current->next_node->next_node;
                                free(current);
                                return RLE_LIST_SUCCESS;
                            }
                            else
                            {
                                previous->next_node = NULL;
                                free(current);
                                return RLE_LIST_SUCCESS;
                            }
                        }
                        
                    }
                    else
                    {
                        previous->next_node = NULL;
                        free(current);
                        return RLE_LIST_SUCCESS;
                    }
                }
            }
            currentIndex++;
        }
    }
}



char RLEListGet(RLEList list, int index, RLEListResult* result)
{
    index++;
    if (list == NULL)
    {
        result = RLE_LIST_NULL_ARGUMENT;
        return 0;
    }

    if (index > RLEListSize(list) || index < 1)
    {
        result = RLE_LIST_INDEX_OUT_OF_BOUNDS;

        return 0;
    }

    int currentIndex = 1;
    RLEList current = list;

    while (true)
    {
        current = current->next_node;
        for (int i = current->numOfOcc; i > 0; i--)
        {
            if (index == currentIndex)
            {
                result = RLE_LIST_SUCCESS;
                return current->letter;
            }
            currentIndex++;
        }
    }
    return 0;
}
int RLEListSize(RLEList list)
{
    if (list == NULL)
    {
        return -1;
    }
    RLEList current = list;
    int size = 0;
    while (current->next_node != NULL)
    {
        current = current->next_node;
        size += current->numOfOcc;
    }
    return size;
}

char convertIntToChar(int value)
{
    char ch = value + '0';
    return ch;
}
char* RLEListExportToString(RLEList list, RLEListResult* result)
{
    if (list == NULL)
    {
        *result = RLE_LIST_NULL_ARGUMENT;
        return NULL;
    }

    int sizeOfList = RLE_numOfNodes(list);

    char* string = (char*)malloc(sizeof(char) * 3 * sizeOfList + 1);

    string[sizeOfList * 3] = '\0';
    int stringIndex = 0;

    RLEList current = list;

    for (int i = 0; i < sizeOfList; i++)
    {
        current = current->next_node;
        string[stringIndex] = current->letter;
        string[stringIndex + 1] = convertIntToChar(current->numOfOcc);
        string[stringIndex + 2] = '\n';
        stringIndex += 3;
    }

    *result = RLE_LIST_SUCCESS;
    return string;
}
RLEListResult RLEListMap(RLEList list, MapFunction map_function)
{
    if (list == NULL || map_function == NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }

    RLEList current = list;
    
    while (current->next_node != NULL)
    {
        current = current->next_node;
        current->letter = map_function(current->letter);
    }

    return RLE_LIST_SUCCESS;
}
void print(RLEList list)
{
    if (list == NULL)
    {
        printf("The list is empty\n");
        return;
    }
    RLEList current = list->next_node;
    
    while (true)
    {
        if (current == NULL)
        {
            break;
        }
        printf("~ %c %d\n", current->letter, current->numOfOcc);
        current = current->next_node;
    }
}
