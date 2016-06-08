
#include "WordPercentSort.h"

/* Takes an alphabetized word and an alphabetized base string
returns 1 if the word can be formed from the base string, 0 otherwise */
int checkWord(char *token_str, int str_length) 
{	

	char cur_char, next_char;
	char *partial_word;                              //formed by concatinating all instances of a single char
	char *base_pointer=base_str;
	int word_index=0, partial_index, return_val=1;	
	partial_word= malloc(str_length * sizeof(char));
	assert(partial_word);
	sortStr(token_str,str_length);                   //alphabetizes the token before it is compared with the sorted base string				
	do{	
		partial_index=0;
		memset(&partial_word[0],0,str_length);  //resets partial_word so it can collect the instances of the next char
		do{	
			cur_char= token_str[word_index];
			next_char= token_str[word_index+1];		
			partial_word[partial_index]=cur_char;    //adds each repeated char to partial_word
			++partial_index;
			++word_index;
		} while(cur_char==next_char);
		base_pointer=strstr(base_pointer, partial_word);  //Updates starting point for comparision, to reduce redundent checks
		if(!base_pointer)                            //checks if all instances of this char can be found within the base
		{
			return_val= 0;                           //result if partial_word could not be found in the base
			break;
		}
	} while(next_char!='\0');
	free(partial_word);
	// if (return_val) {
	// 	printf("%s\n", token_str);
	// }
	return return_val;
}

/* opens the provided txtfile, determines indvigual word tokens, and then calls a included method (checkWord) to see
if they are formable from the base string. Finally it prints the calculated result to the command line */
void processWordsFromFile()
 {
	FILE *input_file;                                  //used to construct token from read characters
	int word_count=0, formable_count=0, buff_index=0;
	int c;                                             //character returned from fgetc
	char *c_buff;

	input_file= fopen(fname, "r");
	c_buff= (char*) calloc(max_length, sizeof(char));	
	assert(c_buff!=0);
	do{
		c = fgetc(input_file);
		if(isTokenizer(c) || c==EOF) { 			
			if(buff_index>0){	                     //non-negative index + reaching a tokenizer means c_buff contains a token
				++word_count;
				if(buff_index<=max_length) {	         //token cannot formed by the base if it is larger than the base
					formable_count+=checkWord(c_buff,buff_index);
				}		
			}
			buff_index=0;			
			memset(&c_buff[0],0,max_length);         //resets c_buff so it can be reused to build the next token
		}
		else
		{
			if(buff_index<max_length) {	
				c_buff[buff_index]=c;                //appends the current char to partial token 
			}
			++buff_index;
		}

	} while(c!=EOF);

	free(c_buff);
	fclose(input_file);
	reportResults(word_count, formable_count);
}

// main function which takes its inputs from the command line
int main (int argc, char **argv) {
	if(argc !=3) {
		printf("%s\n", "first input must be the base string, and second must be the txt file path");
		return 0;
	}
	base_str=argv[1];
	fname=argv[2];
	max_length=strlen(base_str);
	sortStr(base_str, max_length);
	processWordsFromFile();
	return 0;
}