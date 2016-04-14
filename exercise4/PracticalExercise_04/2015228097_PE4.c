#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <memory.h>

int main(int argc, char *argv[])
{
   char buffer[256];
    FILE* fsrc; 
	FILE* fdst;
   DIR* check_dir;


   int n;   
   if(argc != 3)
   {
      printf("./2015228097_PE4 source target\n");
      exit(1);
   }
   if(strcmp(argv[1], argv[2])==0)
   {
      printf("'%s' and '%s' area the same file\n", argv[1], argv[2]);
      exit(1);
   }

   fsrc = fopen(argv[1], "rv");
   if(fsrc == NULL)  	//목적파일 열때 실패한다면 에러메세지 출력
	   exit(1);	
   check_dir = opendir(argv[2]);


   if(check_dir != NULL)					//폴더일 경우 destination 이름 변경
   { 
	  int path_size = strlen(argv[2]) + strlen(argv[1] ) +1;
      char path[path_size];

      strcpy(path, argv[2]);				//argv의 문자열을 path로 복사
      strcat(path, "/");					//path 와 / 를 이어 붙임
      strcat(path, argv[1]);				//path 와 argv 를 이어 붙임
      fdst = fopen(path, "wb");
      if(fdst == NULL) 
		  exit(1);
   }
   else										//파일일경우 destination 이름 그대로 
   { 
      fdst = fopen(argv[2], "wb"); 
	  if(fdst == NULL) exit(1);
   }
   
   while ((n = fread(buffer, 1, 256, fsrc)) > 0) //원본파일을 읽어옴(저장하는 위치, 단위,길이, 원본파일)
   {
      if(n == -1)   exit(1);
      fwrite(buffer, 1, n, fdst);				//파일을 쓴다 (읽는 위치, 단위, 길이, 목적지)
   }
   fclose(fsrc);
   fclose(fdst); //정상적으로 수행시 파일 close
   if (unlink(argv[1]) != 0)
   {
      exit(1);
   }
   return 0;
}


