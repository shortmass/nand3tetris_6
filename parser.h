#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

FILE* initialize(char* file)
{
	if(file == NULL)
	{
		return NULL;
	}

	FILE* tempfile = fopen(file,"r");
	
	if(tempfile == NULL)
	{
		return NULL;
	}

	return tempfile;

}

bool hasdest(char* command);

bool hasMoreCommands(FILE* file)
{
	char c = fgetc(file);
	int end = feof(file);
	ungetc(c,file);

	if(end == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void advance(FILE* file,char* buffer)
{
	fgets(buffer,100,file);
}

char* commandType(char* command)
{
	int cursor = 0;
	
	while(command[cursor] == ' ')
	{
		cursor++;
	}
	
	if(command[cursor] == '@')
	{
		return "A_COMMAND";
	}
	else if(command[cursor] == '(')
	{
		return "L_COMMAND";
	}
	else
	{
		return "C_COMMAND";
	}
}

char* symbol(char* command)
{
	
	int cursor = 0;
	
	while(command[cursor] == ' ')
	{
	    cursor ++;
	}
	
	char* buffer = malloc((strlen(command) * sizeof(char)) - cursor);
	
	if(command[cursor] == '@' || command[cursor] == '(')
	{
	
	    cursor++;
		int bcurs = 0;
		
		while(command[cursor] != '\n' && command[cursor] != 41 && command[cursor]!= '\r' && !(command[cursor] == '/' && command[cursor + 1] == '/'))
		{
			if(command[cursor] == ' ')
			{
			    cursor++;
			}
			else
			{
			    buffer[bcurs] = command[cursor];
			    cursor++;
			    bcurs++;
			}
		}
		
		return buffer;
	}
	
	return NULL;
}

char* dest(char* command)
{
	if(command == NULL)
	{
		return NULL;
	}
	
	char* buffer = malloc(4*sizeof(char));
	int cursor = 0, len = strlen(command);
	bool eq = hasdest(command);
	
	if(!eq)
	{
		return NULL;
	}
	
	int bufferc = 0;
	while(command[cursor] != '=' && command[cursor] != '\n')
	{
		if(command[cursor] == 'A' || command[cursor] == 'D' || command[cursor] == 'M')
		{
			if(bufferc > 2)
			{
				return NULL;
			}

			buffer[bufferc] = command[cursor];
			
			bufferc++;
		}
		cursor++;
	}
	
	if(bufferc == 0)
	{
		return NULL;
	}
	
	buffer[bufferc] = '\0';
	return buffer;
}

char* comp(char* command)
{
	int cursor = 0;
	bool start = false;
	bool eq = hasdest(command);
	
	if(!eq)
	{
		start = true;	
	}
	
	char* buffer = malloc(50 * sizeof(char));
	int bufferc = 0;
	char c;
	
	while(command[cursor] != '\n' && command[cursor] != ';' && command[cursor] != '/')
	{
		c = command[cursor];
	
		if(start == true)
		{
			if(c == 'A' || c == 'D' || c == 'M' || c == '+' || c == '-' || c == '!' || c == '|' || c == '&' || c == '0' || c == '1')
			{
				buffer[bufferc] = c;
				bufferc++;
			}
		}
	
		if(command[cursor] == '=')
		{
			start = true;
		}
		else if((c == '-' || c == '!' || c == '0' || c == '1') && start == false)
		{
			start = true;
			buffer[bufferc] = c;
			bufferc++;
		}  
	
		cursor++;	
	}
	
	buffer[bufferc] = '\0';
	if((buffer[0] == '-' || buffer[0] == '!') && buffer[1] == '\0')
	{
		return NULL;
	}
	
	return buffer;
}

char* jump(char* command)
{
	int cursor = 0;
	bool start = false;
	char* buffer = malloc(4 * sizeof(char));
	int bufferc = 0;
	char c;
	
	while(command[cursor] != '\n' && command[cursor] != '/')
	{
		if(bufferc > 3)
		{
			return NULL;
		}
		
		c = command[cursor];
	
		if(start == true)
		{
			if(c == 'J' || c == 'M' || c == 'P' || c == 'G' || c == 'T' || c == 'L' || c == 'E' || c == 'Q' || c == 'N')
			{
				buffer[bufferc] = c;
				bufferc++;
			}
		}
	
		if(command[cursor] == ';')
		{
			start = true;
		}
	
		cursor++;	
	}
	
	/*if(bufferc == 0)
	{
		return NULL;
	}*/
	
	buffer[bufferc] = '\0';
	
	return buffer;
}

char* dectobi(char* dec)
{
    if(dec != NULL) //if a number is indeed passed in
    {
	    int x = atoi(dec);	//convert from char* to int
	
	    if(x >= 32768 || x < 0) //if it's outside of this range
	    {
		    return NULL; //it's too big, return null
	    }
	
	    char* bibuff = malloc(17 * sizeof(char)); //create a buffer
	
	    if(bibuff == NULL) //if there's an allocation error, return null
	    {
		    return NULL;
	    }
	
	    for(int z = 0;z < 16;z++) //zero out the buffer so we only need to 
	    {
		    bibuff[z] = '0'; //insert 1's where necessary
	    }
	
	    bibuff[16] = '\0'; //terminate the string
	
	    int cursor = 1, power = 15; //the hack platform only has 32K to index
									//so 2^15
	    while(cursor < 16 && x > 0) //start from most significant digit
	    {
	
		    int y = 1;
		
		    for(int i = power - cursor;i > 0;i--) //make y into the place value of
		    {										//the current digit
		    	y *= 2;
		    }
	
	
		    if((x - y) >= 0) 				//if y is in x, so to speak,
		    {				 				//then subtracting y from x >= 0	
		    	bibuff[cursor] = '1';
		    	x -= y;						//and if it is then do the deed
		    }
		
		    cursor++;						//increment cursor, moving down a place value
	    }
	
	    return bibuff;
	}
	
	return NULL;
}

//16384 8192 4096 2048 1024 512 256 128 64 32 16 8 4 2 1

bool isComment(char* line)  //line actually needs to be an address
{
	if(line == NULL)
	{
		return false;
	}
	
	if(strlen(line) < 2)
	{
		return false;
	}
	
	if(line[0] == '/' && line[1] == '/')
	{
		return true;
	}
	
	return false;
	
}

bool isBlankLine(char* line)
{
    int cursor = 0;
    
    while(line[cursor] != '\r' && line[cursor] != '\n')
    {
        if(line[cursor] != ' ')
        {
            return false;
        }
        
        cursor++;
    }
    
    return true;
}

bool hasdest(char* command)
{
	if(command == NULL)
	{
		return false;
	}
	
	int len = strlen(command);
	
	if(len == 0)
	{
		return false;	
	}	
	
	for(int i = 0;i < len;i++)
	{
		if(command[i] == '=')
		{
			return true;
		}
	}
	
	return false;
}

int cprint(char* string)
{
	if(string == NULL)
	{
		return -1;
	}
	
	int len = strlen(string);

	for(int i = 0;i <= len;i ++)
	{
		printf("%d\n",(int)string[i]);
	}
	
	return len;
}
