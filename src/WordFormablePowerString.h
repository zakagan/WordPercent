//
//  WordFormablePowerString.h
//

#ifndef WORDFORMABLEPOWERSTRING_H
#define WORDFORMABLEPOWERSTRING_H

#include "CharTable.h"
#include "SinglyLinkedList.h"
#include "HashMapString.h"
#include "WordSort.h"
#include "Parsing.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void processTokensFromFile(char** base_array, const char** fname_array, const unsigned int num_inputs, const unsigned int* length_array, \
 	const unsigned int max_length, const unsigned char silence, const unsigned char tare_setup, const size_t buckets);

#endif