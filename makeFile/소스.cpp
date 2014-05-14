#include<stdio.h>
#include<iostream>

int main()
{

	FILE *f;

	fopen_s(&f, "LoadingList.list", "w+");

	fprintf(f, "%s %s\n", "asd", "asdd");
	fprintf(f, "%s %s\n", "asd", "asdd");
	fprintf(f, "%s %s\n", "asd", "asdd");


	fclose(f);

	fopen_s(&f, "LoadingList.list", "rb");

	char buf[128];
	char buf2[128];
	
	fscanf_s(f, "%s %s\n", &buf,128, &buf2,128);
	memset(buf, NULL, sizeof(buf2));
	fscanf_s(f, "%s %s\n", &buf, 128, &buf2, 128);
	memset(buf, NULL, sizeof(buf2));
	fscanf_s(f, "%s %s\n", &buf, 128, &buf2, 128);
	memset(buf, NULL, sizeof(buf2));


	fclose(f);



	return 0;
}