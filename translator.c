#include "codewriter2.h"

int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		printf("try again, doofus\n");
		return 1;
	}
	
	DIR* directory = NULL;
	FILE* in = NULL, *out = NULL;
	bool dir = isDir(argv[1]);										//there's probably a better way to 
	bool VMF = !dir;												//do this, but i'm too tired to know what it
	char* inname = calloc(1,strlen(argv[1]) + 5 * sizeof(char));		//is
	char* outname = calloc(1,strlen(argv[1]) + 5 * sizeof(char));		
	char** nameptr = &inname;
	
	struct dirent* ent = NULL;	
	
	char* path = NULL;
	
	int linenum = -1;									//start at -1 because the first line will be 0
														//but the codewriting functions all return the number of lines they print
	char* buffer = calloc(1,100 * sizeof(char));
	char* type = malloc(20 * sizeof(char));
	
	struct line* brine = NULL;	
	
	char* funcname = NULL;
	
	if(dir)
	{
		directory = dirConstructor(argv[1]);			//if we're working through a directory
														//open a pointer to it and try to get		
		ent = readdir(directory);						// the first entry in that directory
		
		//this expression is cheating
		while(ent != NULL && !isVMFile((*ent).d_name))	//work through directory listings
		{
			ent = readdir(directory);
		}
		
		if(ent == NULL)									//if no entries exist, that's all folks
		{
			return 2;
		}
		
		strncpy(inname,(*ent).d_name,strlen((*ent).d_name));		//finally we have a place to start	
		outname = addASMExtension(argv[1]);							//and we give ourselves a place to file everything
		
		path = malloc((strlen(argv[1]) + 1) * sizeof(char));									//for making sure that we draw from the correct stream
		strncpy(path,argv[1],strlen(argv[1]));
	}
	else if(VMF)
	{
		strncpy(inname,argv[1],strlen(argv[1]));					//if there's just one file
																//then life is much simpler
		outname = addASMExtension(rmFileExtension(argv[1]));	//and nobody has to get hurt
	}
	else
	{
		printf("once more, doofus\n");
		return 3;
	}
	
	printf("%s %s\n",inname,outname);
	
	
	in = inConstructor(path,inname);
	out = outConstructor(outname);
	
	if(in == NULL)
	{
		printf("error 4\n");
		return 4;
	}
	
	if(out == NULL)
	{
		printf("error 5\n");
		return 5;
	}
	
	//now do things
	linenum += writeInit(out);
	
	do
	{	
	
		printf("%s\n",*nameptr);
		
		while(hasMoreCommands(in))
		{
			advance(in,buffer);
			
			if(!isComment(buffer) && !isBlankLine(buffer))
			{
				type = commandType(buffer);
			
				if(brine != NULL)
				{
					free(brine);
				}
			
				brine = args(buffer);
			
				if(strcmp(type,"C_PUSH") == 0)
				{
					linenum += WritePushPop(out,type,(*brine).argv[1],(*brine).argv[2],inname);
				}
				else if(strcmp(type,"C_POP") == 0)
				{
					linenum += WritePushPop(out,type,(*brine).argv[1],(*brine).argv[2],inname);
				}
				else if(strcmp(type,"C_ARITHMETIC") == 0)
				{
					linenum += writeArithmetic(out,(*brine).argv[0],linenum);
				}
				else if(strcmp(type,"C_LABEL") == 0)
				{
					linenum += writeLabel(out,funcname,(*brine).argv[1]);
				}
				else if(strcmp(type,"C_GOTO") == 0)
				{
					linenum += writeGoto(out,(*brine).argv[1],funcname);
				}
				else if(strcmp(type,"C_IF") == 0)
				{
					linenum += writeIf(out,(*brine).argv[1],funcname);
				}
				else if(strcmp(type,"C_FUNCTION") == 0)
				{
					funcname = malloc((strlen((*brine).argv[1]) + 1) * sizeof(char));
					
					strncpy(funcname,(*brine).argv[1],strlen((*brine).argv[1]));
					
					linenum += writeFunction(out,(*brine).argv[1],(*brine).argv[2]);
				}
				else if(strcmp(type,"C_RETURN") == 0)
				{
					linenum += writeReturn(out);
				}
				else if(strcmp(type,"C_CALL") == 0)
				{
					linenum += writeCall(out,(*brine).argv[1],linenum,(*brine).argv[2]);
				}
				else
				{
					fprintf(out,"\n");
				}
			}
			
		}
		
		Close(in);
		
	}while(dir && (in = nextFile(directory,nameptr,path)) != NULL);
	
	//close streams and free pointers
	
	return 0;
}