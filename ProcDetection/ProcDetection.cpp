// ProcDetection.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <thread>
#include <chrono>
#include <iostream>
#include "immintrin.h"


void saxpy(int n, float alpha, float *X, float *Y) {
	int i;
	for (i = 0; i < n; i++)
		Y[i] = alpha * X[i] + Y[i];
}

void saxpy128(int n, float alpha, float *X, float *Y) {
	__m128 x_vec, y_vec, a_vec, res_vec; /* Vector variables */
	int i;
	a_vec = _mm_set1_ps(alpha); /* Vector of 4 alpha values */
	for (i = 0; i < n; i += 4) {
		x_vec = _mm_load_ps(&X[i]); /* Load 4 values from X */
		y_vec = _mm_load_ps(&Y[i]); /* Load 4 values from Y */
		res_vec = _mm_add_ps(_mm_mul_ps(a_vec, x_vec), y_vec); /* Compute */
		_mm_store_ps(&Y[i], res_vec); /* Store the result */
	}
}

void saxpy256(int n, float alpha, float *X, float *Y) {
	__m256 x_vec, y_vec, a_vec, res_vec; /* Vector variables */
	int i;
	a_vec = _mm256_set1_ps(alpha); /* Vector of 4 alpha values */
	for (i = 0; i < n; i += 8) {
		x_vec = _mm256_load_ps(&X[i]); /* Load 4 values from X */
		y_vec = _mm256_load_ps(&Y[i]); /* Load 4 values from Y */
		res_vec = _mm256_add_ps(_mm256_mul_ps(a_vec, x_vec), y_vec); /* Compute */
		_mm256_store_ps(&Y[i], res_vec); /* Store the result */
	}
}

#define COUNT 32000
int main()
{
	std::cout << "Number of threads available: " << std::thread::hardware_concurrency() << std::endl;
	float *x_vec = new float[32000000];
	float *y_vec = new float[32000000];

	for (int i(0); i < 32000000; ++i)
	{
		x_vec[i] = 1.4f;
		y_vec[i] = 2.8f;
	}

	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	saxpy(32000000, 1.4f, x_vec, y_vec);
	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
	saxpy128(32000000, 1.4f, x_vec, y_vec);
	std::chrono::high_resolution_clock::time_point t3 = std::chrono::high_resolution_clock::now();
	saxpy256(32000000, 1.4f, x_vec, y_vec);
	std::chrono::high_resolution_clock::time_point t4 = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> time_span1(t2 - t1);
	std::chrono::duration<double> time_span2(t3 - t2);
	std::chrono::duration<double> time_span3(t4 - t3);

	std::cout << "It took me " << std::chrono::duration_cast<std::chrono::milliseconds>(time_span1).count() << " ms." << std::endl;
	std::cout << "It took me " << std::chrono::duration_cast<std::chrono::milliseconds>(time_span2).count() << " ms." << std::endl;
	std::cout << "It took me " << std::chrono::duration_cast<std::chrono::milliseconds>(time_span3).count() << " ms." << std::endl;
	std::cout << std::endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
