/*
Phys 2200: Computational physics
University of Connecticut

Alexis Prel

This program uses Monte Carlo integration for 5D volume calculations.
More specifically it calculates:
    the volume V_5(n) of Σ{i=1→5}|x_i|^n = 1
    for n=1,2, ..., 9
*/

#include <stdio.h>              // to communicate with user
#include <math.h>               // for pow function
#include <gsl/gsl_rng.h>        // to generate random coordinates
#include <gsl/gsl_statistics.h>	// to compute mean and std

int main (void)
{
    // 1: variables initialisation
    int n, d, n_exp;				// counters in "for" structures
    double i;
    int N=9 , N_exp = pow(2,5);		// calculating V5(1) to V5(N), N_exp times ...
    double N_points = pow(2,19);	// ... with N_points points each time
    double s, random[5], slice[N_exp], volume[N],sigma[N]; // variables to store [partial] results
    long counts[N_exp][N];
    for(n_exp=0;n_exp<N_exp;n_exp++){	// initialisation of the array
        for(n=0;n < N ;n ++)
            counts[n_exp][n] = 0L;
    }
    
    // 2: random generator initialisation
    unsigned long seed = 1UL;
    gsl_rng *r;
    r = gsl_rng_alloc (gsl_rng_taus2);
    gsl_rng_set (r, seed);
	
	// 3: MC calculation
	for (n_exp=0;n_exp<N_exp;n_exp++){          //repeating the experience N_exp times
    	for (i = 0; i < N_points; i++){
    	   	for (d = 0; d < 5; d++)             //generates a random point random[5]
    	   		random[d] = gsl_rng_uniform(r);
    	    for (n = 1; n <= N; n++){           //for each n in [1:N], increments counts if the point is inside V5(n)
    	    	s = pow(random[0],n)+pow(random[1],n)+pow(random[2],n)+pow(random[3],n)+pow(random[4],n); //this line can be replaced by a loop to work with an arbitrary number of dimensions
    	    	if (s <= 1)
    	        	counts[n_exp][n-1]++;
    	    }
    	}
    }
    
    // 4: Printing results
    for (n = 1; n <= N; n++){
    	for(n_exp=0;n_exp<N_exp;n_exp++)
    		slice[n_exp]= 32.0*(double)counts[n_exp][n-1]/N_points; // taking only the data of the corresponding n and normalizing it
        volume[n-1] = gsl_stats_mean(slice,1,N_exp);                // result is the mean of the several experiments
         sigma[n-1] = gsl_stats_sd_m(slice,1,N_exp,volume[n-1]);    // incertainty is the standard deviation of it
        printf("%d %f %f\n",n,volume[n-1],sigma[n-1]);
    }
    
    //  5: freeing memory allocated for random generator
    gsl_rng_free(r);
    return 0;
}
