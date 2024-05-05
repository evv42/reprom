#include <stdio.h>
#include <stdlib.h>
#define TB_PATTERN "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c"
#define TB(word)  \
  ((word) & 0x8000 ? '1' : '0'), \
  ((word) & 0x4000 ? '1' : '0'), \
  ((word) & 0x2000 ? '1' : '0'), \
  ((word) & 0x1000 ? '1' : '0'), \
  ((word) & 0x0800 ? '1' : '0'), \
  ((word) & 0x0400 ? '1' : '0'), \
  ((word) & 0x0200 ? '1' : '0'), \
  ((word) & 0x0100 ? '1' : '0'), \
  ((word) & 0x80 ? '1' : '0'), \
  ((word) & 0x40 ? '1' : '0'), \
  ((word) & 0x20 ? '1' : '0'), \
  ((word) & 0x10 ? '1' : '0'), \
  ((word) & 0x08 ? '1' : '0'), \
  ((word) & 0x04 ? '1' : '0'), \
  ((word) & 0x02 ? '1' : '0'), \
  ((word) & 0x01 ? '1' : '0') 

int print_help(char* errstr, char* prgname){
	printf("%s\nUsage: %s <file> <number of desired address lines>\n",errstr,prgname);
	return errstr[0];
}
  
int main(int argc, char** argv){
	unsigned int page, size;
	unsigned char check;
	unsigned char* buf;

	if(argc != 3)return print_help("Invalid syntax", argv[0]);
	
	page = 0;
	
	size = atoi(argv[2]);
	size = 1 << size;
	if(size > 65535 || size == 0)return print_help("Size is zero or too big", argv[0]);
	
	FILE* f = fopen(argv[1],"rb");
	if(f == NULL){
		perror("fopen");
		return 1;
	}
	
	printf("file %s, size requested %d bytes\n",argv[1], size);
	
	buf = malloc(size);
	if(buf == NULL){
		perror("malloc");
		return 1;
	}
	while(feof(f) == 0){
		check = 0;
		fread(buf, size, 1, f);
		for(int i=0; i<size; i++)if(buf[i]!=0xFF)check=1;
		if(check == 0)printf("found free page #%d (address 0x%x) "TB_PATTERN"<--A%d\n", page, page*size, TB(page), atoi(argv[2])+1);
		page++;
	}
	fclose(f);
	return 0;
}
