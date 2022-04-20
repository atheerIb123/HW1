#define _CRT_SECURE_NO_WARNINGS
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
	RLEListResult result = 0;


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

	if (argv[1][1] == 'e')
	{

		RLEList list = asciiArtRead(in_stream);
		
		fclose(in_stream);
		asciiArtPrintEncoded(list, out_stream);
		fclose(out_stream);
	}
	else if(argv[1][1] == 'i')
	{
		RLEList list = asciiArtRead(in_stream);
		RLEListMap(list, map_function);
		asciiArtPrint(list, out_stream);
		fclose(out_stream);
	}
	return 0;
}