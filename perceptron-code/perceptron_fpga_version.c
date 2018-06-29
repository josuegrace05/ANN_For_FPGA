#include <stdio.h>
#include <stdlib.h>
#define TX_APR 0.1

#define nLine 36*48
#define nCol 49
#define group 8

#define AGES 5

float sinWeight[] = {0.754903, 0.505975, 0.245960, 0.346982, 0.722907, 0.477508, 0.489784,
						  0.956696, 0.233916, 0.146732, 0.036004, 0.732390, 0.658822, 0.875878,
						  0.106907, 0.861460, 0.817496, 0.165303, 0.769992, 0.197185, 0.819410,
						  0.058207, 0.295896, 0.944933, 0.118802, 0.780714, 0.229500, 0.015126,
						  0.068240, 0.495698, 0.893159, 0.823143, 0.001673, 0.139120, 0.170126,
						  0.724580, 0.616627, 0.659909, 0.681276, 0.850543, 0.806641, 0.717280,
						  0.582933, 0.465464, 0.593159, 0.689840, 0.326924, 0.410655, 0.855143};

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

double sum(unsigned char* imageLine)
{
	double result = 0;
	int i;

	result += sinWeight[0];

	for(i = 1; i < nCol; i++)
		result += sinWeight[i]*imageLine[i-1];

	return result;
}

int step(double s)
{
	if(s > 127) return 1;
	return 0;
}

double deltaRule(int error, int entry, double S)
{
	return (S + (TX_APR * error * entry));
}

void testing(unsigned char **image)
{
    int i,j,k;
	double sum = 0.0;
	int response;
	int tx = 0;

  for(k = 0; k < 36; k++)
  {
	    for(i = k*48; i < 48*(k+1); i++)
		{
			for(j = 1; j < nCol; j++)
		    	sum += sinWeight[j]*image[i][j-1];

		    sum += sinWeight[0];
		    response = step(sum);

		    if(response == image[i][nCol-1] )
		    	tx++;

		    sum = 0.0;
		}

	printf("Taxa de acerto para imagem %d: %f\n", k+1, ((tx*1.0)/(48*1.0))*100);
	tx = 0;
  }

}
void traininig(unsigned char **image)
{
	int i, j, k, response, error;

	for(i = 0; i < AGES; i++){

		for(j = 0; j < nLine; j++){

			response = step(sum(image[j]));
			error = image[j][nCol-1] - response;

			sinWeight[0] = deltaRule(error,1,sinWeight[0]);

			for(k = 1; k < nCol; k++)
				sinWeight[k] = deltaRule(error, image[j][k-1], sinWeight[k]);

		}

	}

}
void generate_image_estatica(unsigned char **image){
	FILE* fp = fopen("static.txt", "w+");
	int i, j;
	int nLine_s = 36*48;
	fprintf(fp, "{");
	for(i = 0; i < nLine_s; i++){
		fprintf(fp, "{");
		for(j = 0; j < 49; j++){
			fprintf(fp, "%d", image[i][j]);
			if(j < 48)
				fprintf(fp, ",");
		}
		fprintf(fp, "}\n");
	}
	fprintf(fp, "}");
	fclose(fp);
}
int main (int argc, char *argv[])
{

	unsigned char **image = readImage("../imagesDatabase/dBtrSt1.dat");

	generate_image_estatica(image);
/*
	traininig(image);
	
	testing(image);
*/
	deleteDb(image);

	return 0;
}