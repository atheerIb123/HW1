#include "RLEList.h"

struct RLEList_t {
    char value;
    int occurrences;
    RLEList next_node;
};

//implement the functions here
RLEList RLEListCreate()
{
    RLEList newList = (RLEList)malloc(sizeof(*newList));

    if (newList == NULL)
    {
        return NULL;
    }

    newList->value = '\0';
    newList->occurrences = 0;
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
    if (list == NULL || value == '\0')
    {
        return RLE_LIST_NULL_ARGUMENT;
    }


    RLEList current = list;

    while (current->next_node != NULL)
    {
        current = current->next_node;
    }
    if (current->value == value)
    {
        current->occurrences++;
    }
    else
    {
        RLEList newNode = RLEListCreate();

        if (newNode == NULL)
        {
            return RLE_LIST_OUT_OF_MEMORY;
        }

        newNode->value = value;
        newNode->occurrences = 1;
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

        for (int i = current->occurrences; i > 0; i--)
        {
            if (index == currentIndex)
            {
                if (current->occurrences > 1)
                {
                    current->occurrences--;
                    return RLE_LIST_SUCCESS;
                }
                else
                {
                    if (current->next_node != NULL)
                    {
                        if (previous->value != current->next_node->value)
                        {
                            previous->next_node = current->next_node;
                            free(current);
                            return RLE_LIST_SUCCESS;
                        }
                        else
                        {
                            previous->occurrences += current->next_node->occurrences;
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
        if(result != NULL)
        {
            *result = RLE_LIST_NULL_ARGUMENT;
        }
        return 0;
    }

    if (index > RLEListSize(list) || index < 1)
    {
        if(result != NULL)
        {
            *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        }
        return 0;
    }

    int currentIndex = 1;
    RLEList current = list->next_node;

    while (current != NULL)
    {
        for (int i = current->occurrences; i > 0; i--)
        {
            if (index == currentIndex)
            {
                if (result != NULL)
                {
                    *result = RLE_LIST_SUCCESS;
                }
                return current->value;
            }
            currentIndex++;
        }
        current = current->next_node;
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
        size += current->occurrences;
    }

    return size;
}

char* RLEListExportToString(RLEList list, RLEListResult* result)
{
    if (list == NULL)
    {
        *result = RLE_LIST_NULL_ARGUMENT;
        return NULL;
    }

    int stringIndex = 0;
    int sizeOfList = RLEListSize(list);
    char* string = (char*)malloc(sizeof(char) * 3 * sizeOfList + 1);
    char str[10];

    for (RLEList current = list->next_node; current != NULL; current = current->next_node)
    {
        string[stringIndex++] = current->value;
        sprintf(str, "%d", current->occurrences);

        for(int i = 0 ; str[i] != '\0' ; i++)
        {
            string[stringIndex++] = str[i];
        }

        string[stringIndex++] = '\n';
    }
    string[stringIndex] = '\0';

    if (result != NULL)
    {
        *result = RLE_LIST_SUCCESS;
    }

    return string;
}

static void mergeNodes(RLEList list)
{
    if (list->next_node == NULL)
    {
        return;
    }

    RLEList current = list->next_node;
    RLEList previous = list;

    while (current->next_node != NULL && previous->next_node != NULL)
    {
        if (current->value == previous->value)
        {
            previous->occurrences += current->occurrences;
            if (current->next_node != NULL)
            {
                current = current->next_node;
                free(previous->next_node);
                previous->next_node = current;
            }
            else
            {
                previous->next_node = NULL;
                free(current);
                break;
            }
        }
        else {
            current = current->next_node;
            previous = previous->next_node;
        }
    }
    if (previous->value == current->value)
    {
        previous->occurrences += current->occurrences;
        previous->next_node = NULL;
        free(current);
    }
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
        if (current->next_node != NULL)
        {
            current = current->next_node;
            current->value = map_function(current->value);
        }
        else
        {
            current->value = map_function(current->value);
        }
    }

    mergeNodes(list);

    return RLE_LIST_SUCCESS;
}
