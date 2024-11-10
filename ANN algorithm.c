#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to read data from CSV file
void readCSV(const char *filename, double **inputs, double *outputs, int *numRows) {
	FILE *file = fopen(filename, "data_in");
    FILE *file = fopen(filename, "data_out");
	if (!file) {
		perror("Failed to open file");
		exit(EXIT_FAILURE);
	}

	int row = 0;
	while (fscanf(file, "%lf,%lf,%lf", &inputs[row][0], &inputs[row][1], &outputs[row]) != EOF) {
		row++;
	}
	*numRows = row;

	fclose(file);
}

// Function to split data into training, validation, and testing sets
void splitData(double **inputs, double *outputs, int numRows, double **trainInputs, double *trainOutputs, double **valInputs, double *valOutputs, double **testInputs, double *testOutputs, int *trainSize, int *valSize, int *testSize) {
	int trainInd = (int)(numRows * 0.8);
	int valInd = (int)(numRows * 0.1);
	int testInd = numRows - trainInd - valInd;

	for (int i = 0; i < trainInd; i++) {
		trainInputs[i][0] = inputs[i][0];
		trainInputs[i][1] = inputs[i][1];
		trainOutputs[i] = outputs[i];
	}

	for (int i = 0; i < valInd; i++) {
		valInputs[i][0] = inputs[trainInd + i][0];
		valInputs[i][1] = inputs[trainInd + i][1];
		valOutputs[i] = outputs[trainInd + i];
	}

	for (int i = 0; i < testInd; i++) {
		testInputs[i][0] = inputs[trainInd + valInd + i][0];
		testInputs[i][1] = inputs[trainInd + valInd + i][1];
		testOutputs[i] = outputs[trainInd + valInd + i];
	}

	*trainSize = trainInd;
	*valSize = valInd;
	*testSize = testInd;
}
int main() {
	const char *filename = "pv_dataset.csv";
	int numRows = 1000; // Adjust based on your dataset size

	double **inputs = (double **)malloc(numRows * sizeof(double *));
	for (int i = 0; i < numRows; i++) {
		inputs[i] = (double *)malloc(2 * sizeof(double));
	}
	double *outputs = (double *)malloc(numRows * sizeof(double));

	readCSV(filename, inputs, outputs, &numRows);

	int trainSize, valSize, testSize;
	double **trainInputs = (double **)malloc(numRows * sizeof(double *));
	double **valInputs = (double **)malloc(numRows * sizeof(double *));
	double **testInputs = (double **)malloc(numRows * sizeof(double *));
	for (int i = 0; i < numRows; i++) {
		trainInputs[i] = (double *)malloc(2 * sizeof(double));
		valInputs[i] = (double *)malloc(2 * sizeof(double));
		testInputs[i] = (double *)malloc(2 * sizeof(double));
	}
	double *trainOutputs = (double *)malloc(numRows * sizeof(double));
	double *valOutputs = (double *)malloc(numRows * sizeof(double));
	double *testOutputs = (double *)malloc(numRows * sizeof(double));

	splitData(inputs, outputs, numRows, trainInputs, trainOutputs, valInputs, valOutputs, testInputs, testOutputs, &trainSize, &valSize, &testSize);

	// Free allocated memory
	for (int i = 0; i < numRows; i++) {
		free(inputs[i]);
		free(trainInputs[i]);
		free(valInputs[i]);
		free(testInputs[i]);
	}
	free(inputs);
	free(trainInputs);
	free(valInputs);
	free(testInputs);
	free(outputs);
	free(trainOutputs);
	free(valOutputs);
	free(testOutputs);

	return 0;
}
