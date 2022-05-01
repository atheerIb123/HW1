#include "AsciiArtTool.h"


RLEList asciiArtRead(FILE* in_stream)
{
	RLEList list = RLEListCreate();
	char ch = fgetc(in_stream);

	while (ch != EOF)
	{
		RLEListAppend(list, ch);
		ch = fgetc(in_stream);
	}

	return list;
}

RLEListResult asciiArtPrint(RLEList list, FILE* out_stream)
{
	RLEListResult result = 0;
	int size = RLEListSize(list);

	for (int i = 0; i < size; i++)
	{
		char ch = RLEListGet(list, i, &result);
		fputc(ch, out_stream);
	}

	return result;
}

RLEListResult asciiArtPrintEncoded(RLEList list, FILE* out_stream)
{
	if (list == NULL || out_stream == NULL)
	{
		return RLE_LIST_NULL_ARGUMENT;
	}

	RLEListResult result = 0;

	char* encodedString = RLEListExportToString(list, &result);

	fputs(encodedString, out_stream);
	
	return result;
}
