#include<stdio.h>
#include <stdlib.h>

int* city_population (int N, int* population, int** road, int Q, int** cities) ;

int main() {
    int N;
    scanf("%d", &N);
    int i_population;
    int *population = (int *)malloc(sizeof(int)*(N));
    for(i_population = 0; i_population < N; i_population++)
    	scanf("%d", &population[i_population]);
    int i_road, j_road;
    int **road = (int **)malloc((N-1)*sizeof(int *));
    for(i_road = 0; i_road < N-1; i_road++)
    {
    	road[i_road] = (int *)malloc((2)*sizeof(int));
    }
    for(i_road = 0; i_road < N-1; i_road++)
    {
    	for(j_road = 0; j_road < 2; j_road++)
    	{
    		scanf("%d", &road[i_road][j_road]);
    	}
    }
    int Q;
    scanf("%d", &Q);
    int i_cities, j_cities;
    int **cities = (int **)malloc((Q)*sizeof(int *));
    for(i_cities = 0; i_cities < Q; i_cities++)
    {
    	cities[i_cities] = (int *)malloc((3)*sizeof(int));
    }
    for(i_cities = 0; i_cities < Q; i_cities++)
    {
    	for(j_cities = 0; j_cities < 3; j_cities++)
    	{
    		scanf("%d", &cities[i_cities][j_cities]);
    	}
    }

    int* out_ = city_population(N, population, road, Q, cities);
    printf("%d", out_[0]);
    int i_out_;
    for(i_out_ = 1; i_out_ < Q; i_out_++)
    	printf("\n%d", out_[i_out_]);
}

int* city_population (int N, int* population, int** road, int Q, int** cities)
{
    // Allocate memory for the output array
    int* output = (int*) malloc(Q * sizeof(int));

    // Loop over all the queries
    for (int i = 0; i < Q; i++) {
        int city1 = cities[i][0];
        int city2 = cities[i][1];

        // Find the lowest common ancestor of the two cities
        int lca = 0; // Initialize to the root of the tree
        while (city1 != city2) {
            if (city1 > city2) {
                city1 = road[city1-2][0]; // Parent of city1
            } else {
                city2 = road[city2-2][0]; // Parent of city2
            }
            lca = city1;
        }

        // Find the city with the highest population in the path
        int max_population = 0;
        int current_city = cities[i][0];
        while (current_city != lca) {
            if (population[current_city-1] > max_population) {
                max_population = population[current_city-1];
            }
            current_city = road[current_city-2][0]; // Parent of current_city
        }
        current_city = cities[i][1];
        while (current_city != lca) {
            if (population[current_city-1] > max_population) {
                max_population = population[current_city-1];
            }
            current_city = road[current_city-2][0]; // Parent of current_city
        }

        // Store the result in the output array
        output[i] = max_population;
    }

    // Return the output array
    return output;
}
