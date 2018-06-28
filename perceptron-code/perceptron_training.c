#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define VLR_BIAS 0.1
#define TX_APR 0.1

#define nLine 36*48
#define nCol 49
#define group 8

#define AGES 20000

void deleteDb(unsigned char **db)
{
	int i;

	for(i = 0; i < nLine; i++)
		free(db[i]);
	
	free(db);
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

double *InitSinapticWeight(int nEntries)
{
    double *sinWeight = (double *)malloc(sizeof(double)*(nEntries+1));
    int i;
    
    srand(time(NULL));
    
    for(i = 0; i < nEntries+1; i++)
        sinWeight[i] = (rand()/(RAND_MAX*1.0));        
    
    return sinWeight;
}

double sum(unsigned char* imageLine, double* sinapses)
{
	double result = 0;
	int i;
	
	result += sinapses[0];
	
	for(i = 1; i < nCol; i++)
		result += sinapses[i]*imageLine[i-1]; 
	
	return result;
}

int step(double s)
{
	if(s > 127) return 1;
	return 0;
}

double deltaRule(int error, int entry, double sinapse)
{
	return (sinapse + (TX_APR * error * entry));
}

void printSinapticWeightVector(double *sinWeightVector, int n)
{
    int i;
    
    for(i = 0; i < n; i++)
        printf("%f ", sinWeightVector[i]);
    printf("\n");
    
}
void traininig(unsigned char **image, double *sinapses, FILE *outputFile)
{
	int i, j, k, response, error;
	double meanError;
	
	for(i = 0; i < AGES; i++){

		meanError = 0.0;
		
		for(j = 0; j < nLine; j++){
			
			response = step(sum(image[j],sinapses));
			error = image[j][nCol-1] - response;
			meanError += abs(error);

			sinapses[0] = deltaRule(error,1,sinapses[0]);
			
			for(k = 1; k < nCol; k++)
				sinapses[k] = deltaRule(error, image[j][k-1], sinapses[k]);
					
		}
		
		printf("%d %f\n",i,meanError/(nLine*1.0));
	}
	
	for(k = 0; k < nCol; k++)
		fprintf(outputFile,"%lf\n",sinapses[k]);
}

int main (int argc, char *argv[])
{
	
	unsigned char **image = readImage("../imagesDatabase/dBtrSt1.dat");

	double *sinWeightVector = InitSinapticWeight(48);
	//printSinapticWeightVector(sinWeightVector,49);
	
	FILE *outputFile = fopen("../imagesDatabase/trainingResult.dat","w");
	
	if(outputFile != NULL)
	{
		traininig(image,sinWeightVector,outputFile);
		fclose(outputFile);
	}
	else
		printf("Não abriu o arquivo\n");
		
	free(sinWeightVector);
	deleteDb(image);	
	
	return 0;
}