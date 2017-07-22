#include "symbol.h"

int main(int argc, char** argv)
{
	if(argc != 3)
	{
		printf("Check your usage, bucko\n");
		return 1;
	}
	
	FILE* file = initialize(argv[1]);
	
	FILE* out = fopen(argv[2],"w");
	
	if(file == NULL)
	{
		printf("file did not open\n");
	}
	
	tableheader* table = constructor();
	
	char* buffer = malloc(100 * sizeof(char));
	char* type = malloc(10 * sizeof(char));
	
	unsigned int ROM = 0;
	unsigned int RAM = 16;
	
	while(hasMoreCommands(file))
	{
				
		advance(file,buffer);
					
		type = commandType(buffer);
		
		if(!isComment(buffer) && !isBlankLine(buffer))
		{
			if(strcmp(type,"A_COMMAND") == 0 || strcmp(type,"C_COMMAND") == 0)
			{
				ROM ++;
			}
			else if(strcmp(type, "L_COMMAND") == 0)
			{
				addEntry(table,symbol(buffer),ROM);
			}
		}
	}
	
	rewind(file);	
	
	while(hasMoreCommands(file))
	{
				
		advance(file,buffer);
			
		type = commandType(buffer);
		
		if(!isComment(buffer))
		{
		
			if(strcmp(type,"A_COMMAND") == 0)
			{
		
				char* sym = symbol(buffer);		
			
				if(isVariable(sym))
				{
				
					char* num = malloc(20 * sizeof(char));
				
					if(!contains(table,sym))
					{
						addEntry(table,sym,RAM);
											
					
						snprintf(num,20,"%d",RAM);
					
					
						RAM ++;
					}
					else
					{
						snprintf(num,20,"%d",GetAddress(table,sym));
					}
					
					fprintf(out,"%s\n",dectobi(num));
					
					//free(num);
					//free(sym);
					
				}
				else
				{
					fprintf(out,"%s\n",dectobi(sym));
					
					//free(sym);
				}
						
			}
			if(strcmp(type,"L_COMMAND") == 0)
			{
			
				//fprintf(out,"\n");
				continue;
			
			}
			if(strcmp(type,"C_COMMAND") == 0)
			{
			
				char* desti,*compu,*jumpm, *destb,*compb,*jumpb;
			
				desti = dest(buffer);
				compu = comp(buffer);
				jumpm = jump(buffer);
			
				destb = destbin(desti);
				
				compb = compbin(compu);
				
				
				jumpb = jumpbin(jumpm);
			
				
				if(destb != NULL && compb != NULL && jumpb != NULL)
				{
					int dlen = strlen(destb), clen = strlen(compb), jlen = strlen(jumpb);
					
					fprintf(out,"111");
					
					for(int j = 0;j < clen;j++)
					{
						fprintf(out,"%c",compb[j]);
					}
					for(int i = 0;i < dlen;i++)
					{
						fprintf(out,"%c",destb[i]);
					}
					for(int k = 0;k < jlen;k++)
					{
						fprintf(out,"%c",jumpb[k]);
					}
					fprintf(out,"\n");
				}
			}	
		}
	}
	
	return 0;
}
