/*************************************************************************
* Title: (CIS265_3B) Income Tax Calculator
* File: main.c
* Author: James Eli
* Date: 8/25/2017
*
* In one state, single residents are subject to the following income tax:
*  Income
*  Not over $750		1% of income
*  $750-$2,250			$7.50	plus 2% of amount over $750
*  $2,250-$3,750		$37.50	plus 3% of amount over $2,250
*  $3,750-$5,250		$82.50	plus 4% of amount over $3,750
*  $5,250-$7,000		$142.50	plus 5% of amount over $5,250
*  Over $7,000			$230.00	plus 6% of amount over $7,000
* Write a program that asks the user to enter the amount of taxable income, 
* then displays the tax due.
*
* Notes:
*  (1) Compiled with MS Visual Studio 2017 Community (v141), using C
*      language options.
*  (2) Input does not flag exponential notation.
*
* Submitted in partial fulfillment of the requirements of PCC CIS-265.
*************************************************************************
* Change Log:
*   08/25/2017: Initial release. JME
*************************************************************************/
#include <assert.h> 
#include <stdio.h>
#include <float.h>

// Tax bracket array indices.
#define MIN_INCOME   0 // Minimum allowed income array index.
#define MAX_INCOME   1 // Maximum allowed income array index.
#define BASE_TAX     2 // Base tax array index.
#define MAX_BRACKETS 6 // Maximum income tax brackets.

// Tax bracket minimum income, maximum income and base tax.
float taxBrackets[MAX_BRACKETS][3] = { 
	0.,    750.,     0.,    // 0-750
	750.,  2250.,    7.5,   // 750-2250
	2250., 3750.,    37.5,  // 2250-3750
	3750., 5250.,    82.5,  // 3750-5250
	5250., 7000.,    142.5, // 5250-7000
	7000., 1000000., 230.   // 7000-1M
};

// Program starts here.
int main(void) {
	float income = 0.; // Income (input).
	float tax = 0.;    // Computed tax (output).

	fputs("Enter income (0 to 1,000,000): ", stdout);
	if (scanf_s("%f", &income)) {
		if (income >= 0. && income <= 1000000.) {
			// Determine tax bracket and calculate amount of tax.
			for (int i = 0; i < MAX_BRACKETS; i++) {
				if (income >= taxBrackets[i][MIN_INCOME] && income <= taxBrackets[i][MAX_INCOME]) {
					// tax = base tax for bracket + (i+1)% of income exceeding the base bracket income.
					tax = taxBrackets[i][BASE_TAX] + (float)(i + 1.) / 100. * (income - taxBrackets[i][MIN_INCOME]);
					break;
				}
			}
			// Report tax.
			fprintf(stdout, "On income of: $%0.2f, tax due is: $%0.2f\n", income, tax);
		}
		else // Income outside bounds...
			fputs("Income must be between $0 and 1M.\n", stdout);
	}
	else // Scanf failure...
		fputs("Invlaid income entered. Try again.\n", stdout);
}

