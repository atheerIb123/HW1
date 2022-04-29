#include "RLEList.h"

struct RLEList_t {
    char letter;
    int numOfOcc;
    RLEList next_node;
};

static bool isListEmpty(RLEList list)
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

    newList->letter = '\0';
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
    RLEList current = list;

    while (true)
    {
        current = current->next_node;
        for (int i = current->numOfOcc; i > 0; i--)
        {
            if (index == currentIndex)
            {
                if (result != NULL)
                {
                    *result = RLE_LIST_SUCCESS;
                }
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

    int stringIndex = 0;
    int sizeOfList = RLEListSize(list);
    char* string = (char*)malloc(sizeof(char) * 3 * sizeOfList + 1);

    RLEList current = list;

    char str[10];
    for (RLEList current = list->next_node; current != NULL; current = current->next_node)
    {
        string[stringIndex++] = current->letter;
        sprintf(str, "%d", current->numOfOcc);

        for(int i = 0 ; i < strlen(str); i++)
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
}//a1a2a1b1     //a3a1b

void mergeNodes(RLEList list)
{
    RLEList current = list;
    RLEList previous = current;
    while (current->next_node != NULL)
    {
        current = current->next_node;
        if (previous->letter == current->letter)
        {
            previous->numOfOcc += current->numOfOcc;
            if (current->next_node != NULL)
            {
                previous->next_node = current->next_node;

            }
            else
            {
                previous->next_node = NULL;
            }

        }//a1a2a1b1 -> a3a1b1
        if (previous->next_node->letter != previous->letter)
        {
            previous = previous->next_node;
        }
    }
}

RLEListResult RLEListMap(RLEList list, MapFunction map_function)
{
    if (list == NULL || map_function == NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }

    RLEList current = list;
    
    while (current != NULL)
    {
        if(current->next_node != NULL)
        {
            current = current->next_node;
            current->letter = map_function(current->letter);
            mergeNodes(list);
        }
    }

    return RLE_LIST_SUCCESS;
}
