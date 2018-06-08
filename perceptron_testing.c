#include <stdio.h>
#include <stdlib.h>
#define nLine 48
#define nCol 49

void deletImage(unsigned char **image)
{
	int i;

	for(i = 0; i < 9*nLine; i++)
		free(image[i]);
	
	free(image);
}

unsigned char **readImage(char *fileName)
{
	unsigned char **image = (unsigned char**)malloc(9*nLine*sizeof(unsigned char *));
	int i,j,k;
	
	FILE *fp = fopen(fileName,"r");

	if(fp != NULL)
	{
		for(i = 0; i < 9*nLine; i++)
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

void printResult(int *result, int imagem)
{
	
	int i, rate = 0;;
	for(i = 0; i < nLine; i++)
	{
		if(result[i] == 1)		
			rate++;
		printf("%d ", result[i]);
		
	}		
	printf("\nTaxa de acerto para imagem %d: %f\n",imagem,(rate*1.0/nLine)*100.0);
}

int step(float s)
{
	if(s > 100000000) return 1;
	return -1;
}

void testing(unsigned char **image, float *sinVector)
{
    int i,j,k,l = 0;
	float sum = 0.0;
	int response;
	int *result = (int *)malloc(nLine*sizeof(int));
  
  for(k = 0; k < 9; k++)
  {
	    for(i = k*48; i < nLine*(k+1); i++)
		{
			for(j = 0; j < nCol; j++)
		    	sum += sinVector[j]*image[i][j];
		    
		    response = step(sum);
		    
		    if(response >= 0 )
		    	result[l++] = 1;
		    else
		    	result[l++] = -1;
		    
		    sum = 0.0;
		}
	
	l = 0;	
	printResult(result, k);
 
  }
  
  free(result);
}

int main(int argc, char *argv[])
{
    
    //int n;
    unsigned char **image = readImage("dBtestSt1.dat");
    float *sinVector = readSinapticWeigth("trainingResult.dat");
    printSinapticWeightVector(sinVector);
    testing(image,sinVector);
    
    free(sinVector);
    deletImage(image);
    
    return 0;
}