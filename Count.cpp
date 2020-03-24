#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <io.h> 
//字符统计
int charcount(char *file) 
{
	 int c=0;
	 FILE *fp;
     char a;
	 fp=fopen(file,"r");
	 while(!feof(fp))
	 {
		 a=fgetc(fp);
		    if(a!=' '&&a!='\n'&&a!='\t')
               c++;
	
	 }
	 fclose(fp);
	 c--;
	 return c;
}
//词数统计
int wordcount(char *file)   
{
	 int w=0;
	 FILE *fp;
	 char a;
	 int t=0;
	 fp=fopen(file,"r");
	 if (charcount(file)==0)
         w=0;  
	 else
	 {
		 while(!feof(fp))
		 {
			 a=fgetc(fp);
			 if(a==' '||a=='\n'||a=='\t'||a==EOF){
			 	if(t==1){
			 		w++;
			 		t=0;
			 	}
			 } 
	         else t=1;
		 }
	 }
	 fclose(fp);
	 return w;
}
//行数统计
int linecount(char *file)
{
	 int l=0;
	 FILE *fp;
     fp=fopen(file,"r");
	 char a;
	 while(!feof(fp))
	 {
		 a=fgetc(fp);
		    if(a=='\n')
               l++;
	 }
	 fclose(fp); 
	 l++;
	 return l;
}
//寻找目录下txt,cpp文件
int searchfile(void)
{
    struct _finddata_t fileinfo;
    long fHandle;
    int t=0;
	
       if( (fHandle=_findfirst( "*txt", &fileinfo )) == -1L ) 
		{
        printf( "当前目录下没有txt文件\n");
		
		}
    else
    do{
		 t++;
		printf("找到文件:%s\n", fileinfo.name);
	}while (_findnext(fHandle,&fileinfo)==0);
	
    _findclose(fHandle);

    printf("txt文件数量：%d\n",t);
    return 0;
}
//返回更多数据 
int LineData(char *file){
	
	FILE *fp;
    fp=fopen(file,"r");
	char a;
	int tag=0,tag2=0,Blank_line=0,Code_Line=0,Comment_Line=0;
	
	while(!feof(fp)){
		a=fgetc(fp);
		if(a=='\n'||a==EOF){
			if(tag==1)
				Code_Line++;
			if(tag==2)
				Comment_Line++;
				tag2=0;
			if(tag==0)
				Blank_line++;
			tag=0;
				
		}else{
			if(a!=' '&&a!='\n'&&a!='\t'&&a!='{'&&a!='}'){
				if(a=='/'){
					if(tag2==1)
						tag=2;
					tag2=1;
				} 
				if(tag!=2)
					tag=1; 
			} 

		}
	}
	fclose(fp);
	printf("空行数为：%d\n",Blank_line);
	printf("代码行数为：%d\n",Code_Line);
	printf("注释行数为：%d\n",Comment_Line);
	return 	Blank_line+Code_Line+Comment_Line;
}
//主函数 
int main (int argc, char *argv[])   
{
	int i;
	for(i=1;i<argc;i++){
		if(!strcmp(argv[i],"-c"))
		{
			printf("charnumber:%d\n",charcount(argv[argc-1]));
		}
		else if(!strcmp(argv[i],"-w"))
		{
			printf("wordnumber:%d\n",wordcount(argv[argc-1]));
		}
		else if (!strcmp(argv[i],"-l"))
		{
			printf("linenumber:%d\n",linecount(argv[argc-1]));
		}
		else if(!strcmp(argv[i],"-s"))
	    {
		    searchfile();
	    }
	    else if (!strcmp(argv[i],"-a"))
		{
			LineData(argv[argc-1]);
		}
	}
	return 0;
}
