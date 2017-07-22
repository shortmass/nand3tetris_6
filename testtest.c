#include "code.h"

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
	
	
	
	char* buffer = malloc(20 * sizeof(char));
	char* type = malloc(10 * sizeof(char));
	
	
	
	while(hasMoreCommands(file))
	{
		
		
		advance(file,buffer);
		
		
		
		type = commandType(buffer);
		
		if(!isComment(buffer))
		{
		
			if(strcmp(type,"A_COMMAND") == 0)
			{
		
				char* sym = symbol(buffer);		
			
				fprintf(out,"%s\n",dectobi(sym));
						
			}
			if(strcmp(type,"L_COMMAND") == 0)
			{
			
				fprintf(out,"\n");
			
			}
			if(strcmp(type,"C_COMMAND") == 0)
			{
			
				char* desti,*compu,*jumpm, *destb,*compb,*jumpb;
			
				desti = dest(buffer);
				compu = comp(buffer);
				jumpm = jump(buffer);
				/*if(desti == NULL || compu == NULL || jumpm == NULL)
				{
					fprintf(out,"\n");
				}*/
			
				destb = destbin(desti);
				
				compb = compbin(compu);
				
				
				jumpb = jumpbin(jumpm);
			
				
				if(destb != NULL && compb != NULL && jumpb != NULL)
				{
					int dlen = strlen(destb), clen = strlen(compb), jlen = strlen(jumpb);
					//fprintf(out,"%s%s%s%s\n","111",destb,compb,jumpb);
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
			/*else
			{
			
				fprintf(out,"\n");
			
			}*/
		}
		/*else
		{
			fprintf(out,"\n");
		}*/	
		
	}

	return 0;
}