#ifndef HW1_ASCIIART_H
#define HW1_ASCIIART_H

#include "RLEList.h"

RLEList asciiArtRead(FILE* in_stream);
RLEListResult asciiArtPrint(RLEList list, FILE* out_stream);
RLEListResult asciiArtPrintEncoded(RLEList list, FILE* out_stream);
/** Enum used for returning error codes from RLE list functions */

#endif // HW1_RLELIST_H