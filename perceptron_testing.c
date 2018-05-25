#include <stdio.h>
#include <stdlib.h>
#define nLine 48
#define nCol 49

void deletImage(unsigned char **image)
{
	int i;

	for(i = 0; i < nLine; i++)
		free(image[i]);
	
	free(image);
}

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
			
			for(j = 0; j < nCol; j++)
			{
				fscanf(fp,"%d,",&k);
				image[i][j] = (unsigned char)k;
			}
			
			for(j = 0; j < 7; j++)
				fscanf(fp,"%d,",&k);
				
			fscanf(fp,"%d,",&k);
			image[i][nCol -1] = (unsigned char)k;
			
			fscanf(fp,"%d,",&k);
		}
	}	

    fclose(fp);
    
	return image;
}

float *readSinapticWeigth(char *fileName)
{
    int i;
    float *sVector = (float *)malloc(nCol*sizeof(float));
    
    FILE *fp = fopen(fileName,"r");
    
    for(i = 0; i < nCol; i++)
        fscanf(fp,"%f\n", &sVector[i]);
    
    fclose(fp);
    return sVector;
    
}

void printSinapticWeightVector(float *sinWeightVector)
{
    int i;
    
    for(i = 0; i < nCol; i++)
        printf("%f ", sinWeightVector[i]);
    printf("\n");
    
}

void printResult(int *result)
{
	
	int i, rate = 0;;
	for(i = 0; i < nLine; i++)
	{
		if(result[i] == 1)		
			rate++;
		printf("%d ", result[i]);
		
	}		
	printf("\nTaxa de acerto: %f\n",(rate*1.0/nLine)*100.0);
}

void testing(unsigned char **image, float *sinVector)
{
    int i,j;
	float sum = 0.0;
	int *result = (int *)malloc(nLine*sizeof(int));
    
    for(i = 0; i < nLine; i++)
	{
		for(j = 0; j < nCol; j++)
	    	sum += sinVector[j]*image[i][j];
	    
	    if(sum - sinVector[0] >= 0 )
	    	result[i] = 1;
	    else
	    	result[i] = -1;
	    
	    sum = 0.0;
	}
	
	printResult(result);
	free(result);
	    
}

int main(int *argc, char *argv[])
{
    
    int n;
    unsigned char **image = readImage("dBtestGr5St1.dat");
    float *sinVector = readSinapticWeigth("treinamento.txt");
    printSinapticWeightVector(sinVector);
    testing(image,sinVector);
    
    free(sinVector);
    deletImage(image);
    
    return 0;
}