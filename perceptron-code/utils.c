#include <stdio.h>
#include <stdlib.h>
#define nLine 48*9
#define nCol 49
#define group 8

unsigned char **readImage(char *fileName)
{
	unsigned char **image = (unsigned char**)malloc(nLine*sizeof(unsigned char *));
	int i,j,k;
	
	FILE *fp = fopen(fileName,"r");

	if(fp != NULL)
	{
		for(i = 0; i < nLine; i++)
		{
			image[i] = (unsigned char *)malloc(nCol*sizeof(unsigned char));
			
			for(j = 0; j < nCol -1; j++)
			{
				fscanf(fp,"%d,",&k);
				image[i][j] = (unsigned char)k;
			}
			
			for(j = 0; j < group -1; j++)
				fscanf(fp,"%d,",&k);
				
			fscanf(fp,"%d,",&k);
			image[i][nCol -1] = (unsigned char)k;
			
			fscanf(fp,"%d,",&k);
		}
		
		fclose(fp);
	}	
	
	return image;
}

void printImage(unsigned char **image)
{
	int i, j;

	for(i = 0; i < 48; i++)
	{
		for(j = 0; j < 49; j++)
			printf("%d ", image[i][j]);
		printf("\n");
	}
}

void generate_image_estatica(unsigned char **image){
	
	FILE* fp = fopen("static.txt", "w");
	int i, j;
	
	fprintf(fp, "{");
	
	for(i = 0; i < nLine; i++)
	{
		
		fprintf(fp, "{");
		
		for(j = 0; j < 48; j++)
			fprintf(fp, "%d,", image[i][j]);
		
		fprintf(fp, "%d},\n",image[i][j]);
	}
	
	fprintf(fp, "};");
	
	fclose(fp);
}

int main(int *argc, char *argv[])
{
    unsigned char **image = readImage("../imagesDatabase/dBtestSt1.dat"); 
    generate_image_estatica(image);
    
    return 0;
}
