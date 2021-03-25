#include <stdio.h>
#include <complex.h>
#include <stdlib.h>
#include <math.h>

void fftRadix2(complex double* x,long int N, int sign){
    if (N==1){
        return ;
    }
    complex double even[N/2], odd[N/2];
    for(long int i=0; i<N/2; i++){
        even[i] = x[2*i];
        odd[i] = x[2*i+1];
    }
    fftRadix2(even, N/2, sign);
    fftRadix2(odd, N/2, sign);

    for(long int i = 0; i<N/2; i++){
        complex double twiddle = cexp(-2*M_PI*i*I*sign/N);
        x[i] = even[i] + twiddle*odd[i];
        x[i + N/2] = even[i] - twiddle*odd[i];
    }
    return ;
}


void transform(complex double* x,long int N, int flag){
    // function to calculate fft or ifft 
    // using radix2 decimation in time algorithm
    // Set flag = 1 for fft calculation
    // Set flag = -1 for ifft calculation
    
    
    fftRadix2(x, N, flag);
    if(flag==-1){
        for(long int i=0;i<N;i++){
            x[i] = x[i]/N;
        }
    }
}
int main()
{

    FILE* fp = fopen("signal.dat", "r");
    if(fp == NULL){
        printf("Nah");
    }
    fseek(fp, 0L, SEEK_END);
    long int len = ftell(fp)/8;
    // fclose(fp);

    long int n = pow(2, ceil(log2(len)));
    complex double *x = (complex double *) malloc(n*sizeof(complex double));
    double *data = (double *) malloc(n*sizeof(double));
    for(long int i=0;i<n; i++){
        x[i] = 0;
    }

    FILE* fp2 = fopen("signal.dat", "r");
    // fread(data, sizeof(data[0]), len, fp2);
    for (long int i = 0; i<n; i++){
        (x[i]) = CMPLX(0,0);
    }
    long int k = 0;
    while (!feof(fp2) && k < n)
    {
        double val;
        fscanf(fp2, "%lf", &val);
        k++;
        x[k] = CMPLX(val, 0);
    }
    printf("%ld\n", n);
    //doing this because x is too big and gives segmentation fault
    // segmentation fault on large array sizes: https://stackoverflow.com/questions/1847789/segmentation-fault-on-large-array-sizes
    long int q = pow(2,21);
    complex double arr[] = { 0, 1, 2, 3, 6, 3, 6, 4, 2, 2, 3, 4, 1, 2, 4, 3};
    printf("done till here");
    transform(arr, 16, 1);
    fclose(fp2);
    return 0;
}
