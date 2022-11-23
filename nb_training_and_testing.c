/**
 * @file nb_training_and_testing.c
 * @author Ryan Ong QC
 * @brief Run this file to calculate the probabilities for the naive bayes classifier
 * and store them in a file, afterwards test the classifier and print the error prob and confusion matrix
 * 
 * Build:
 * gcc -o nb_training_and_testing nb_training_and_testing.c naive_bayes_ai.c
 * 
 * Run:
 * .\nb_training_and_testing
 */

#include <stdio.h>
#include "naive_bayes_ai.h"

struct prepped_data
{
	char game_data[958][10];
	int training_indexes[766];
	int testing_indexes[192];
};

struct prepped_data prepare_data();
struct weights train_model(struct prepped_data);
void test_model(struct weights, struct prepped_data);

int main(void)
{
	struct prepped_data prepped_data = prepare_data();
	struct weights weights = train_model(prepped_data);
	test_model(weights, prepped_data);

	return 0;
}

/**
 * @brief 
 * Reads the tic-tac-toe.data file and splits the data into training and testing sets
 * @return struct prepped_data
 * Struct containing the game data and the arrays containing the training and testing indexes
 */
struct prepped_data prepare_data()
{
	FILE *ptr;
	char ch;

	// Opening file in reading mode
	ptr = fopen("tic-tac-toe.data", "r");

	if (NULL == ptr)
	{
		printf("file can't be opened \n");
	}

	/*
	Parses the char data from the file pointer into the 2d array game_data

	The elements in a row stay mostly the same as the source file except for the last element,
	where only the first character of the outcome will be stored instead. Eg. 'postive' stored as 'p'

	Attribute information of a row in the game_data array:
	for the first 9 elements(index 0 - 8): x = player x, b = blank, o = player o
	for the last element(index 9): p = x win, n = x lose/draw

	eg.
	{
		{'x','x','x','x','o','o','x','o','o','p'},
		{'x','o','x','o','b','o','x','o','o','n'},
		...
		{'o','b','x','b','o','b','x','o','o','p'}
	}
	*/
	struct prepped_data prepped_data;

	int row = 0;

	do
	{
		int col = 0;

		// get the first 10 non-comma chars into a row in game_data from the file pointer
		do
		{
			ch = fgetc(ptr);

			if (ch != ',')
			{
				prepped_data.game_data[row][col] = ch;
				col += 1;
			}

		} while (ch != 'p' && ch != 'n' && ch != EOF);

		// skip next 8 chars
		for (int i = 0; i < 8; i++)
		{
			ch = fgetc(ptr);
		}

		row += 1;

		// Checking if character is not EOF.
		// If it is EOF stop eading.
	} while (ch != EOF);

	fclose(ptr);

	// indexes of the rows to be used as training and testing data respectively
	// training_data_indexes: contains the indexes of 0.8 of the winning rows and 0.8 of losing rows
	// testing_data_indexes: contains the indexes of 0.2 of the winning rows and 0.2 of losing rows

	int array_length = sizeof(prepped_data.game_data) / sizeof(prepped_data.game_data[0]);

	for (int i = 0; i < array_length; i++)
	{
		if (i < 626)
		{
			if (i < 500)
				prepped_data.training_indexes[i] = i;
			else
				prepped_data.testing_indexes[i - 500] = i;
		}
		else
		{
			if (i < 891)
				prepped_data.training_indexes[500 + i - 625] = i;
			else
				prepped_data.testing_indexes[125 + i - 890] = i;
		}
	}

	return prepped_data;
}

/**
 * @brief 
 * Trains and returns a model using the naive bayes algorithm
 * @param prepped_data 
 * Struct containing the game data and the arrays containing the training and testing indexes
 * @return struct weights 
 * Struct containing the weights of the naive bayes classifier
 */
struct weights train_model(struct prepped_data prepped_data)
{
	float x_win_total_pos[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
	float b_win_total_pos[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
	float o_win_total_pos[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

	float x_lose_total_pos[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
	float b_lose_total_pos[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
	float o_lose_total_pos[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

	float win_total = 0;
	float lose_total = 0;

	int array_length = sizeof(prepped_data.training_indexes) / sizeof(prepped_data.training_indexes[0]);

	// Count the total Xs, Os, and blanks in each position and the total number of wins and loses
	for (int row = 0; row < array_length; row++)
	{

		int training_row = prepped_data.training_indexes[row];

		for (int col = 0; col < 9; col++)
		{
			switch (prepped_data.game_data[training_row][col])
			{
			case 'x':
				if (prepped_data.game_data[training_row][9] == 'p')
					x_win_total_pos[col] += 1;
				else
					x_lose_total_pos[col] += 1;
				break;

			case 'b':
				if (prepped_data.game_data[training_row][9] == 'p')
					b_win_total_pos[col] += 1;
				else
					b_lose_total_pos[col] += 1;
				break;

			case 'o':
				if (prepped_data.game_data[training_row][9] == 'p')
					o_win_total_pos[col] += 1;
				else
					o_lose_total_pos[col] += 1;
				break;

			default:
				break;
			}
		}

		switch (prepped_data.game_data[training_row][9])
		{
		case 'p':
			win_total += 1;
			break;

		case 'n':
			lose_total += 1;
			break;

		default:
			break;
		}
	}

	struct weights weights; // found in naive_bayes_ai.h

	// Calculate the weights at the differenent positions and store in weights struct
	for (int i = 0; i < 9; i++)
	{
		weights.p_x_win_pos[i] = x_win_total_pos[i] / win_total;
		weights.p_b_win_pos[i] = b_win_total_pos[i] / win_total;
		weights.p_o_win_pos[i] = o_win_total_pos[i] / win_total;

		weights.p_x_lose_pos[i] = x_lose_total_pos[i] / lose_total;
		weights.p_b_lose_pos[i] = b_lose_total_pos[i] / lose_total;
		weights.p_o_lose_pos[i] = o_lose_total_pos[i] / lose_total;
	}

	// Calculate total wins and loses and store in weight struct 
	weights.p_win = win_total / (win_total + lose_total);
	weights.p_lose = lose_total / (win_total + lose_total);

	// Store the weights struct in a file
	FILE *weight_fptr = 0;

	weight_fptr = fopen("naive_bayes_weights.data", "wb");

	fwrite(&weights, sizeof(struct weights), 1, weight_fptr);
	fclose(weight_fptr);

	return weights;
}

/**
 * @brief 
 * Test the accuracy of the model with the test data and print the stats
 * @param weights 
 * struct containing the weights of the naive bayes model
 * @param prepped_data 
 * Struct containing the game data and the arrays containing the training and testing indexes
 */
void test_model(struct weights weights, struct prepped_data prepped_data)
{
	float prob_of_error = 0;
	int true_positive = 0;
	int true_negative = 0;
	int false_positive = 0;
	int false_negative = 0;

	int array_length = sizeof(prepped_data.testing_indexes) / sizeof(prepped_data.testing_indexes[0]);

	// Calculate the probabilty of error and confusion matrix values of the model
	for (int row = 0; row < array_length; row++)
	{
		int test_index = prepped_data.testing_indexes[row];
		int board[9] = {};

		for (int col = 0; col < 9; col++)
		{
			board[col] = prepped_data.game_data[test_index][col];
		}

		float win_prob = calculate_win_prob(board, weights);
		float lose_prob = calculate_lose_prob(board, weights);

		int w_or_l = win_prob > lose_prob ? 1 : 0;

		switch (prepped_data.game_data[test_index][9])
		{
		case 'p':
			if (w_or_l)
				true_positive++;
			else
				false_negative++;

			break;

		case 'n':
			if (!w_or_l)
				true_negative++;
			else
				false_positive++;

			break;

		default:
			break;
		}
	}

	prob_of_error = (false_positive + false_negative)/192.0;

	printf("Probability of error: %f\nTrue positive: %d\nTrue negative: %d\nFalse positive: %d\nFalse negative: %d\n\n",
		   prob_of_error, true_positive, true_negative, false_positive, false_negative);
	
	printf("                          Actual\n");
	printf("                    positive  negative\n");
	printf("                    ------------------\n");
	printf("          positive |    %d  |   %d   |\n",true_positive, false_positive);
	printf("Predicted          |---------|--------|\n");
	printf("          negative |    %d   |   %d   |\n", false_negative, true_negative);
	printf("                    ------------------\n");
}