#include <stdio.h>
#include <stdlib.h>

#define nLine 48
#define nCol 49
#define nImages 9
#define group 8

void deletImage(unsigned char **image)
{
	int i;

	for(i = 0; i < nImages*nLine; i++)
		free(image[i]);
	
	free(image);
}

unsigned char **readImage(char *fileName)
{
	unsigned char **image = (unsigned char**)malloc(nImages*nLine*sizeof(unsigned char *));
	int i,j,k;
	
	FILE *fp = fopen(fileName,"r");

	if(fp != NULL)
	{
		for(i = 0; i < nImages*nLine; i++)
		{
			image[i] = (unsigned char *)malloc(nCol*sizeof(unsigned char));
			
			for(j = 0; j < nCol; j++)
			{
				fscanf(fp,"%d,",&k);
				image[i][j] = (unsigned char)k;
			}
			
			for(j = 0; j < group-1; j++)
				fscanf(fp,"%d,",&k);
				
			fscanf(fp,"%d,",&k);
			image[i][nCol -1] = (unsigned char)k;
			
			fscanf(fp,"%d,",&k);
		}
	}	

    fclose(fp);
    
	return image;
}

double *readSinapticWeigth(char *fileName)
{
    int i;
    double *sVector = (double *)malloc(nCol*sizeof(double));
    
    FILE *fp = fopen(fileName,"r");
    
    for(i = 0; i < nCol; i++)
        fscanf(fp,"%lf\n", &sVector[i]);
    
    fclose(fp);
    return sVector;
    
}

int step(double s)
{
	if(s > 127) return 1;
	return 0;
}

void testing(unsigned char **image, double *sinVector)
{
    int i,j,k;
	float sum = 0.0;
	int response;
	int tx = 0; 
  
  for(k = 0; k < 9; k++)
  {
	    for(i = k*48; i < nLine*(k+1); i++)
		{
			for(j = 1; j < nCol; j++)
		    	sum += sinVector[j]*image[i][j-1];
		    
		    sum += sinVector[0];
		    response = step(sum);
		    
		    if(response == image[i][nCol-1] )
		    	tx++;
		    
		    sum = 0.0;
		}
	
	printf("Taxa de acerto para imagem %d: %f\n", k+1, ((tx*1.0)/nLine)*100);	
	tx = 0;
  }
  
}

int main(int argc, char *argv[])
{
    
    unsigned char **image = readImage("../imagesDatabase/dBtestSt1.dat");
    double *sinVector = readSinapticWeigth("../imagesDatabase/trainingResult.dat");

    testing(image,sinVector);
    
    free(sinVector);
    deletImage(image);
    
    return 0;
}