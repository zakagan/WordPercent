//
//  WordPercentPowerInts.h
//

#ifndef WORDPERCENTPOWERINTS_H
#define WORDPERCENTPOWERINTS_H

#include "CharTable.h"
#include "SinglyLinkedString.h"
#include "HashMapInts.h"
#include "CheckWordByPartials.h"
#include "WordSort.h"
#include "Parsing.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void processTokensFromFile(char* base_str, FILE* input_file, char* c_buff, const int max_length, const int silence, const int buckets);

#endif