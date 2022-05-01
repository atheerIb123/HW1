#include "RLEList.h"

struct RLEList_t {
    char value;
    int occurrences;
    RLEList next;
};

RLEList RLEListCreate()
{
    RLEList newList = (RLEList)malloc(sizeof(*newList));

    if (newList == NULL)
    {
        return NULL;
    }

    newList->value = '\0';
    newList->occurrences = 0;
    newList->next = NULL;

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
        list = list->next;
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

    while (current->next != NULL)
    {
        current = current->next;
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
        current->next = newNode;
    }

    return RLE_LIST_SUCCESS;
}

RLEListResult RLEListRemove(RLEList list, int index)
{

    if (list == NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }

    if (index >= RLEListSize(list) || index < 0)
    {
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }

    int currentIndex = 0;
    RLEList current = list->next;
    RLEList previous = list;

    while (current != NULL)
    {
        for (int i = current->occurrences; i > 0; i--)
        {
            if (index == currentIndex)
            {
                if (current->occurrences > 1)
                {
                    current->occurrences--;
                    return RLE_LIST_SUCCESS;
                }

                if (current->next != NULL && current->next->value != previous->value)
                {
                    previous->next = current->next;
                    free(current);
                    return RLE_LIST_SUCCESS;
                }
                else if (current->next == NULL)
                {
                    free(current);
                    previous->next = NULL;
                    return RLE_LIST_SUCCESS;
                }
                else if (current->next != NULL && current->next->value == previous->value)
                {
                    previous->occurrences += current->next->occurrences;

                    if (current->next->next != NULL)
                    {
                        previous->next = current->next->next;
                        free(current->next);
                        free(current);
                        return RLE_LIST_SUCCESS;
                    }
                    else
                    {
                        free(current->next);
                        free(current);
                        previous->next = NULL;
                        return RLE_LIST_SUCCESS;
                    }
                }
            }
            currentIndex++;
        }

        current = current->next;
        previous = previous->next;
    }
    return RLE_LIST_SUCCESS;
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

    int currentIndex = 0;
    RLEList current = list->next;

    while (current != NULL)
    {
        currentIndex += current->occurrences;
        if (currentIndex >= index)
        {
            if (result != NULL)
            {
                *result = RLE_LIST_SUCCESS;
            }
            return current->value;
        }
        current = current->next;
    }
    return 0;
}

int RLEListSize(RLEList list)
{
    if (list == NULL)
    {
        return -1;
    }

    int size = 0;

    while (list->next != NULL)
    {
        list = list->next;
        size += list->occurrences;
    }

    return size;
}

char* RLEListExportToString(RLEList list, RLEListResult* result)
{
    if (list == NULL && result != NULL)
    {
        *result = RLE_LIST_NULL_ARGUMENT;
        return NULL;
    }
   
    RLEList current = list->next;
    int size = RLEListSize(list);
    char* string = (char*)malloc(3 * (size + 1));

    if (string == NULL)
    {
        if (result != NULL)
        {
            *result = RLE_LIST_OUT_OF_MEMORY;
        }
        return NULL;
    }

    int stringIndex = 0;

    while (current != NULL)
    {
        string[stringIndex] = current->value;
        stringIndex += sprintf(string + stringIndex + 1, "%d\n", current->occurrences);
        stringIndex++;
        current = current->next;
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
    if (list->next == NULL)
    {
        return;
    }

    RLEList current = list->next;
    RLEList previous = list;

    while (current->next != NULL && previous->next != NULL)
    {
        if (current->value == previous->value)
        {
            previous->occurrences += current->occurrences;
            if (current->next != NULL)
            {
                current = current->next;
                free(previous->next);
                previous->next = current;
            }
            else
            {
                previous->next = NULL;
                free(current);
                break;
            }
        }
        else {
            current = current->next;
            previous = previous->next;
        }
    }
    if (previous->value == current->value)
    {
        previous->occurrences += current->occurrences;
        previous->next = NULL;
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

    while (current->next != NULL)
    {
        if (current->next != NULL)
        {
            current = current->next;
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