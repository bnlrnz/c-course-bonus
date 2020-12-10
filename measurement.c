#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Struktur für Messungen
//typedef definiert ein Alias für den Ausdruck
// struct _Measurement -> Measurement (ohne "struct")
typedef struct _Measurement{
	unsigned long long id;
	double value;
	char device[8];
	struct _Measurement* predecessor;
}Measurement;

void printMeasurement(Measurement* meas){
	printf("===============================\n");
	printf("= Measurement: %llu\n", meas->id);
	printf("= Value:       %f\n", meas->value);
	printf("= Device:      %s\n", meas->device);

	//Prüfe, ob ein Vorgänger existiert
	if(meas->predecessor != NULL){
		printf("= Predecessor: %llu\n", meas->predecessor->id);
	}
	else{
		printf("= First Measurement of Series\n");
	}
	printf("===============================\n\n");
}

double meanOfSeries(Measurement* series, int number){
	double sum = 0.0;
	for (int i = 0; i < number; ++i){
		sum += series[i].value;
	}

	return sum / number;
}

int main(int argc, char** argv){

	//argc, argv siehe: http://www.c-howto.de/tutorial/funktionen-teil-2/hauptfunktion/
	if(argc < 2){
		printf("Please pass number of measurements...\n");
		return 0;
	}

	//initialisiere die rand()-Funktion mit der aktuellen Uhrzeit
  	srand (time(NULL));

  	// (a)rray (to) (i)nteger
	int numMeasurements = atoi(argv[1]);

	printf("Generating %d measurements...\n", numMeasurements);
	
	Measurement* series = (Measurement*) malloc(numMeasurements * sizeof(Measurement) );

	if(!series){
		printf("Could not allocate memory for measurement series :( \n");
		return -1;
	}

	char device[] = "FX-9000";

	// Vorgängermessung, am Anfang gibt es keine
	Measurement* pre = NULL;

	// Definieren der Messungen
	for (int i = 0; i < numMeasurements; ++i){
		series[i].id = i;
		series[i].value = rand() % 5000 + 1;
		series[i].predecessor = pre;
		strncpy(series[i].device, device, 8);
		
		// aktuelle Messung "merken"
		pre = &series[i];
	}

	double mean = meanOfSeries(series, numMeasurements);

	for (int i = 0; i < numMeasurements; ++i){
		if(series[i].value > mean){
			printMeasurement(&series[i]);
		}
	}

	printf("Mean: %f\n", mean);

	free(series);

	return 0;
}