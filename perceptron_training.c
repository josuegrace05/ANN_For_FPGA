#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define VLR_BIAS 1
#define TX_APR 0.01
#define nLine 48*4
#define nCol 49
#define AGES 2000

void deleteDb(unsigned char **db)
{
	int i;

	for(i = 0; i < nLine; i++)
		free(db[i]);
	
	free(db);
}
void printDb(unsigned char **db)
{
	int i,j;

	for(i = 0; i < nLine; i++)
	{
		for(j = 0; j < nCol; j++)
			printf("%hhu\t", db[i][j]);

		printf("\n");
	}

}
void printSinapticWeightVector(float *sinWeightVector, int n)
{
    int i;
    
    for(i = 0; i < n; i++)
        printf("%f ", sinWeightVector[i]);
    printf("\n");
    
}
unsigned char **readImage(char *fileName)
{
	unsigned char **image = (unsigned char**)malloc(nLine*sizeof(unsigned char *));
	int i,j,k;
	char aux;
	
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

float *InitSinapticWeight(int nEntries)
{
    float *sinWeight = (float *)malloc(sizeof(float)*(nEntries+1));
    int i;
    
    srand(time(NULL));
    
    for(i = 0; i < nEntries+1; i++)
        sinWeight[i] = (rand() % 2) + 0.5;        
    
    return sinWeight;
}

float sum(unsigned char* imageLine, float* sinapses)
{
	float result = 0;
	int i;
	
	result += sinapses[0] * VLR_BIAS;
	
	for(i = 1; i < nCol-1; i++)
		result += sinapses[i]*imageLine[i-1]; 
	
	return result;
}

int step(float s)
{
	if(s > 80) return 1;
	return 0;
}

float deltaRule(int error, int entry, float sinapse)
{
	//printf("erro: %d - Entrada: %d - SAIDA: %f\n", error, entry, (sinapse + (TX_APR * error * entry)));
	return (sinapse + (TX_APR * error * entry));
	
}

void traininig(unsigned char **image, float *sinapses)
{
	int i, j, k, response, error;
	
	for(i = 0; i < AGES; i++){

		for(j = 0; j < nLine; j++){
			
			response = step(sum(image[j],sinapses));
			error = abs(image[j][nCol-1] - response);
			
			if(error){
				
				sinapses[0] = deltaRule(error, VLR_BIAS, sinapses[0]);
				for(k = 1; k < nCol; k++)
				{	
					sinapses[k] = deltaRule(error, image[j][k], sinapses[k]);
					//if(sinapses[k] > 1000000)
					//	sinapses[k] /= 100;
				}	
			}
		}
	}
	
	//printf("RESULTADO TREINAMENTO");
	//printf("w[bias] = %f\n", sinapses[0]);
	
	for(k = 0; k < nCol; k++)
		printf("%f\n",sinapses[k]);
}

int main (int argc, char *argv[])
{
	//int nEntries = atoi(argv[1]);
	//int learningRate = atoi(argv[2]);
	
	//printf("%d\n", nEntries);
	
	unsigned char **image = readImage("dBtrGr8St1.dat");
	//printDb(image);
	
	
	float *sinWeightVector = InitSinapticWeight(48);
	//printSinapticWeightVector(sinWeightVector,48);
	traininig(image,sinWeightVector);
	
	free(sinWeightVector);
	deleteDb(image);	
	
	return 0;
}