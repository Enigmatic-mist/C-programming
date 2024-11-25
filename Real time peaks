//Name:Keerthi Vasukhi Kamaraju
//roll number: EE23B034
//Version 1.0
//Description: Modifications made to the time series analysis where the time series is written into a file and read one point 
// at a time mimicing a real time data acquisiton and using an exponential filter
#include<stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include<unistd.h>

#define n 100
#define eps 0.05

float T;

// Define a custom structure to store peak information
struct allpeaks {
    float amp;
    float position;
    float width;
};

// Function to generate a random number using the Box-Muller transform
float randomee() {
    float u1 = (float)random() / (RAND_MAX + 0.5);
    float u2 = (float)random() / (RAND_MAX + 0.5);
    float z = sqrt(-2 * log(u1)) * cos(2 * M_PI * u2);
    return z;
}

// Function to calculate a Lorentzian function
float lor_fn(float a, float t, float m) {
    return (float)(pow(a, 2)) / (pow(a, 2) + pow((t - (m * T)), 2));
}

// Function to calculate a Gaussian function
float gau_fn(float a, float t, float m) {
return (float)exp((-1 * pow((t - (m * T)), 2)) / (2 * pow(a, 2)));
}

// Exponential filter function
float exponentialFilter(float currentData, float previousFilteredData, float alpha) {
    return alpha * currentData + (1 - alpha) * previousFilteredData;
}

int main(int argc, char* argv[]) {
    int M = atoi(argv[1]);
    T = atof(argv[2]);
    float a = atof(argv[3]);
    int pointnum = (int)ceil(n * T);
    char* choice = (char*)malloc(20 * sizeof(char)); // Memory allocation for the choice of peak shape


    if (argc > 4) {
        choice = argv[4];
    } 
    else {
        choice = "Lorentzian"; // Default choice if not specified
    }

    double datapoints[M][pointnum]; // 2D array to store data points
    struct allpeaks* p_i = (struct allpeaks*)malloc(M * sizeof(struct allpeaks)); // Array to store peak information
    double filteredDatapoints[M][pointnum];//2D array to store filtered data points
    float t = (float)T / 2; // Initialize time variable

    // Open a file for writing the time series
    FILE *dataFile = fopen("time_series.txt", "w");
    if (dataFile == NULL) {
        printf("Error opening the data file for writing.\n");
        return 1;
    }

    // Loop to generate data points for each peak and write to the file
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < pointnum; j++) {
            // Generate data points based on the choice of Gaussian or Lorentzian
            if (!strcmp(choice, "Gaussian")) {
                datapoints[i][j] = gau_fn((a + (((eps) * randomee()) * a)), t, ((i + 1) + (eps) * randomee()));
            } 
            else {
                datapoints[i][j] = lor_fn((a + (((eps) * randomee()) * a)), t, ((i + 1) + (eps) * randomee()));
            }
            t += (float)T / pointnum;

            // Write the data point to the file
            fprintf(dataFile, "%f\n", datapoints[i][j]);
        }
    }

    // Close the data file
    fclose(dataFile);

    // Open the file for reading
    dataFile = fopen("time_series.txt", "r");
    if (dataFile == NULL) {
        printf("Error opening the data file for reading.\n");
        return 1;
    }

    float previousFilteredData = 0.0; // Initialize previous filtered data
    float alpha = 0.2; // Set the alpha value for the exponential filter

    // Loop to mimic real-time data acquisition and apply the exponential filter
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < pointnum; j++) {
            // Read one data point from the file
            float dataPoint;
            if (fscanf(dataFile, "%f", &dataPoint) != 1) {
                printf("Error reading data point from the file.\n");
                fclose(dataFile);
                return 1;
            }

            // Apply the exponential filter
            filteredDatapoints[i][j] = exponentialFilter(dataPoint, previousFilteredData, alpha);
            previousFilteredData = filteredDatapoints[i][j];
            usleep(1000);
            t += (float)T / pointnum;
        }
    }

    fclose(dataFile);

    float t1 = (float)T / 2;
    int h = (int)floor((pointnum) / 2);
    float interval = T / pointnum;
    int j_l, j_r, j_c;
    float aTotal = 0.0;
    float aSquareTotal = 0.0;
    float tTotal = 0.0;
    float tSquareTotal = 0.0;

    // Loop to analyze the peaks and calculate statistics
    for (int i = 0; i < M; i++) {
        float peakstart = ((2 * i) + 1) * T / 2; // Calculate the start time of the peak

        // Find the left edge of the peak
        for (int j1 = 0; j1 < h; j1++) {
            if (filteredDatapoints[i][j1] < 0.5) continue;
            j_l = j1;
            break;
        }

        // Find the right edge of the peak
        for (int j2 = h; j2 < pointnum; j2++) {
            if (filteredDatapoints[i][j2] > 0.5) continue;
            j_r = j2;
            break;
        }

        j_c = (int)floor((j_l + j_r) / 2);
        p_i[i].width = (j_r - j_l) * interval / 2;
        aTotal += p_i[i].width / 2;
        aSquareTotal += pow(((p_i[i].width) / 2), 2);

        p_i[i].position = peakstart + (j_c * interval);

        if (i > 1) {
            tTotal += p_i[i].position - p_i[i - 1].position; // Calculate the time between peaks
            tSquareTotal += pow((p_i[i].position - p_i[i - 1].position), 2); // Add squared time difference to the total squared times
        }

        p_i[i].amp = filteredDatapoints[i][j_c]; // Store the amplitude of the peak
    }

    // Calculate and print the average and standard deviation of amplitude and position
    float a_avg = aTotal / (M);
    float T_avg = tTotal / (M - 2);
    float a_avg_squares = aSquareTotal / (M);
    float T_avg_squares = tSquareTotal / (M - 2);
    float a_stdev = sqrt(a_avg_squares - pow(a_avg, 2));
    float T_stdev = sqrt(T_avg_squares - pow(T_avg, 2));

    // Print the calculated statistics
    printf("%f %f %f %f", T_avg, a_avg, T_stdev, a_stdev);

    return 0;
}
