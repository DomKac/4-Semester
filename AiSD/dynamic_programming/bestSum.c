#include <stdlib.h>
#include <stdio.h>

int bestSum(int targetSum, int numbers[], size_t n, int* dp);
int bestSum(int targetSum, int numbers[], size_t n, int* dp) { 

    dp[0] = 0;
    int min_sum;
    for (size_t i = 1; i <= targetSum; i++){
        min_sum = __INT_MAX__;
        for (size_t j = 0; j < n; j++) {
            if (numbers[j] <= i) {
                if (dp[i-numbers[j]] >= 0 && dp[i-numbers[j]] < min_sum) {
                    printf("dp[%zu-%d] = %d\t", i, numbers[j], dp[i-numbers[j]]);
                    dp[i] = dp[i-numbers[j]]+1;
                    min_sum = dp[i-numbers[j]];
                } 
            }
        }
        if (min_sum == __INT_MAX__){
            dp[i] = -1;
        }        
        printf("dp[%zu] = %d\n", i, dp[i]); 
        puts("");
    }
    return dp[targetSum];

}




int main(void) {

    int numbers[3] = {4,10,5,};
    int targetSum = 36;
    int *dp = (int*)calloc((size_t)targetSum+1, sizeof(int));

    int odp = bestSum(targetSum, numbers, 3, dp);

    printf("Najmniejsza libczba elementow numbers ktora trzeba zsumowac do uzykania liczby %d wynosi: %d\n", targetSum, odp);

    free(dp);

    return EXIT_SUCCESS;
}
