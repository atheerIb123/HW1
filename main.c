#include "AsciiArtTool.h"
char map_function(char ch)
{
	if (ch == ' ')
	{
		return '@';
	}
	else if (ch == '@')
	{
		return ' ';
	}
	return ch;
}

int main(int argc, char** argv)
{
	FILE* in_stream = fopen(argv[2], "r");

	if (in_stream == NULL)
	{
		printf("Couldn't open source file\n");
		return 0;
	}

	FILE* out_stream = fopen(argv[3], "w");

	if (out_stream == NULL)
	{
		printf("Couldn't open source file\n");
		return 0;
	}

	RLEList list = asciiArtRead(in_stream);

	if (argv[1][1] == 'e')
	{
		fclose(in_stream);
		asciiArtPrintEncoded(list, out_stream);
		fclose(out_stream);
		RLEListDestroy(list);
	}
	else if(argv[1][1] == 'i')
	{
		RLEListMap(list, map_function);
		asciiArtPrint(list, out_stream);
		fclose(out_stream);
		RLEListDestroy(list);
	}

	return 0;
}
