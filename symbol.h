#include "code.h"


typedef struct tnode{
	
	char* symbol;
	int val;
	struct tnode* next;

}tnode;

typedef struct tableheader{
	
	struct tnode* start;
	int length;

}tableheader;


tableheader* constructor(void)
{
	tableheader* newhead = malloc(sizeof(tableheader));
	
	if (newhead == NULL)
	{
		return NULL;
	}
	
	(*newhead).length = 0;
	(*newhead).start = malloc(sizeof(tnode));
	
	newhead->start->symbol = "R0";
	newhead->start->val = 0;
	
	char* registers[15] = {"R1","R2","R3","R4","R5","R6","R7","R8","R9","R10","R11","R12","R13","R14","R15"};
	char* labels[5] = {"SP","LCL","ARG","THIS","THAT"};
	
	tnode* ptr = newhead->start;
	
	for(int i = 0;i < 15;i++)
	{
		ptr->next = malloc(sizeof(tnode));
		ptr->next->val = i + 1;
		ptr->next->symbol = registers[i];	
		ptr = ptr->next;
	}
	
	for(int j = 0;j<5;j++)
	{
		ptr->next = malloc(sizeof(tnode));
		ptr->next->val = j;
		ptr->next->symbol = labels[j];
		ptr = ptr->next;
	}
	
	ptr->next = malloc(sizeof(tnode));
	ptr->next->val = 16384;
	ptr->next->symbol = "SCREEN";
	ptr = ptr->next;
	
	ptr->next = malloc(sizeof(tnode));
	ptr->next->val = 24576;
	ptr->next->symbol = "KBD";
	ptr->next->next = NULL;
	
	
	return newhead;
}

int addEntry(tableheader* head,char* symbol,int address)
{
	if(head != NULL)
	{
		if((*head).start != NULL)
		{	
			struct tnode* cursor = (*head).start;
		
			while((*cursor).next != NULL)
			{
				cursor = (*cursor).next;
			}
		
			(*cursor).next = malloc(sizeof(tnode));
			cursor = (*cursor).next;
			(*cursor).symbol = symbol;
			(*cursor).val = address;
			(*cursor).next = NULL;
			
		}
		else
		{
			
			(*head).start = malloc(sizeof(tnode));
			
			tnode* cursor = (*head).start;
			
			(*cursor).symbol = symbol;
			(*cursor).val = address;
			(*cursor).next = NULL;
			
		}
		
		return 0;
	}
	
	return 1;
}

bool contains(tableheader* head,char* symbol)
{
	if((*head).start == NULL)
	{
		return false;
	}

	tnode* cursor = (*head).start;
	
	while(cursor != NULL)
	{
		if(strcmp(symbol,(*cursor).symbol) == 0)
		{
			return true;
		}
		
		cursor = (*cursor).next;
	}
	
	return false;
}

int GetAddress(tableheader* head, char* sym)
{
	if(contains(head,sym))
	{
		tnode* cursor = (*head).start;
	
		while(cursor != NULL)
		{
			if(strcmp(sym,(*cursor).symbol) == 0)
			{
				return (*cursor).val;
			}
		
			cursor = (*cursor).next;
		}
	}
	
	return -1;	
}

bool isVariable(char* symbol)
{
	if(symbol != NULL)
	{
	    int i = 0;
		int len = strlen(symbol);
	    
	    for(int i = 0; i < len;i++)
	    {
	    	if((symbol[i] > 57 || symbol[i] < 48))
		    {
		    	return true;
		    }
	    }
	    
	    /*while(symbol[i] != '\0' || symbol[i] != '\n' || symbol[i] != '\r')
	    {
		    if((symbol[i] > 57 || symbol[i] < 48))
		    {
		    	return true;
		    }	
		
		    i++;
	    }*/
	
	    return false;
	}
	
	return false;
}
