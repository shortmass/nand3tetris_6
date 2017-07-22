#include "parser.h"


char* destbin(char* mnem)
{
	if(mnem == NULL)
	{
		return "000\0";
	}
	
	int cursor = 0;
	
	char* buffer = malloc(4 * sizeof(char));
	
	if((strlen(mnem) > 4) || buffer == NULL)
	{
		return NULL;
	}
	
	for(int i = 0; i < 3;i++)
	{
		buffer[i] = '0';
	}
	
	while(mnem[cursor] != '\0')
	{
		if(mnem[cursor] == 'A')
		{
			buffer[0] = '1';
		} 
		else if(mnem[cursor] == 'D')
		{
			buffer[1] = '1';
		}
		else if(mnem[cursor] == 'M')
		{
			buffer[2] = '1';
		}
		cursor++;
	}
	
	buffer[3] = '\0';
	
	return buffer;
}

char* jumpbin(char* mnem)
{
	
	char* buffer = malloc(4 * sizeof(char));
	int c = 0;
	
	if(mnem == NULL)
	{
		printf("nullllllll\n");
	}
	
	if(strcmp(mnem,"JMP") == 0)
	{
		for(int i = 0; i < 3;i++)
		{
			buffer[i] = '1';
		}
		
		buffer[3] = '\0';
		
		return buffer;
	}
	
	for(int j = 0;j < 3;j++)
	{
		buffer[j] = '0';
	}
	
	
	
	if(mnem[0] == '\0')
	{
		 return "000\0";	
	}
	
	while(c < 3)
	{	
		if(mnem[c] == 'E')
		{
			if(mnem[c-1] == 'N')
			{
				buffer[0] = '1';
				buffer[2] = '1';
			}
			else
			{
				buffer[1] = '1';
			}
		}
		else if(mnem[c] == 'G')
		{
			buffer[2] = '1';
		}
		else if(mnem[c] == 'L')
		{
			buffer[0] = '1';
		}
		
		c++;
	}
	
	buffer[3] = '\0';
	return buffer;
	
}



char* compbin(char* comp)
{
	if(comp == NULL)
	{
		return NULL;
	}
	
	
	char* buffer = malloc(8 * sizeof(char));
	
	
	buffer[7] = '\0';
	
	int m = 0, len = strlen(comp);
	
	for(int f = 0; f < len; f++)
	{
		if(comp[f] == 'M')
		{
			m++;
		}
	}
	
	if(m == 1)
	{
		buffer[0] = '1';	
	}
	else
	{
		buffer[0] = '0';
	}
	
	
	
		if(strcmp(comp,"0") == 0)
			{strcpy(&buffer[1], "101010");}
			
		else if(strcmp(comp,"1") == 0)
			{strcpy(&buffer[1], "111111");}
		
		else if(strcmp(comp,"-1") == 0)
			{strcpy(&buffer[1], "111010");}
			
		else if(strcmp(comp,"D") == 0)
			{strcpy(&buffer[1], "001100");}
			
		else if(strcmp(comp,"A") == 0 || strcmp(comp,"M") == 0)
			{strcpy(&buffer[1], "110000");}
			
		else if(strcmp(comp,"!D") == 0)
			{strcpy(&buffer[1], "001101");}
			
		else if(strcmp(comp,"!A") == 0 || strcmp(comp,"!M") == 0)
			{strcpy(&buffer[1], "110001");}
		
		else if(strcmp(comp,"-D") == 0)
			{strcpy(&buffer[1], "001111");}
		
		else if(strcmp(comp,"-A") == 0 || strcmp(comp,"-M") == 0)
			{strcpy(&buffer[1], "110011");}
		
		else if(strcmp(comp,"D+1") == 0)
			{strcpy(&buffer[1], "011111");}
			
		else if(strcmp(comp,"A+1") == 0 || strcmp(comp,"M+1") == 0)
			{strcpy(&buffer[1], "110111");}
			
		else if(strcmp(comp,"D-1") == 0)
			{strcpy(&buffer[1], "001110");}
			
		else if(strcmp(comp,"A-1") == 0 || strcmp(comp,"M-1") == 0)
			{strcpy(&buffer[1], "110010");}
			
		else if(strcmp(comp,"D+A") == 0 || strcmp(comp,"D+M") == 0 || strcmp(comp,"A+D") == 0 || strcmp(comp,"M+D") == 0)
			{strcpy(&buffer[1], "000010");}
			
		else if(strcmp(comp,"D-A") == 0 || strcmp(comp,"D-M") == 0)
			{strcpy(&buffer[1], "010011");}
			
		else if(strcmp(comp,"A-D") == 0 || strcmp(comp,"M-D") == 0)
			{strcpy(&buffer[1], "000111");}
			
		else if(strcmp(comp,"D&A") == 0 || strcmp(comp,"A&D") == 0 || strcmp(comp,"D&M") == 0 || strcmp(comp,"M&D") == 0) 
			{strcpy(&buffer[1], "000000");}
			
		else if(strcmp(comp,"D|M") == 0 || strcmp(comp,"M|D") == 0 || strcmp(comp,"D|A") == 0 || strcmp(comp,"A|D") == 0)
			{strcpy(&buffer[1], "010101");}
			
		else
			{return NULL;}
			

	
	return buffer;
}
