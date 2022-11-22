#include <stdio.h>
#include "naive_bayes_ai.h"

static struct weights weights;

int initialize();
int get_best_move();
float calculate_win_prob(int board[9], struct weights weights);
float calculate_lose_prob(int board[9], struct weights weights);

int initialize()
{
	FILE *weight_fptr = 0;
	weight_fptr = fopen("naive_bayes_weights.data", "rb");
	fread(&weights, sizeof(struct weights), 1, weight_fptr);

	return 0;
}

/**
 * @brief
 * Calculates the next best move on the inputted board using the naive bayes model weights
 * @param board
 * Board array Eg.{'x','b','o','b','b','b','b','b','b'}
 * @return int
 * Index of the best possible move
 */
int get_best_move(int board[9])
{
	// Load weights if weight struct uninitialized
	if (weights.p_win == 0)
	{
		initialize();
	}

	int best_move = -1;
	float win_prob = 0;
	float lose_prob = 0;

	float greatest_win_prob = 0;

	float smallest_lose_prob = 1;
	int smallest_lose_prob_pos = 0;

	// Try every blank space and calculate the best possible move
	for (int i = 0; i < 9; i++)
	{
		if (board[i] != 'b')
			continue;

		board[i] = 'x';

		win_prob = calculate_win_prob(board, weights);
		lose_prob = calculate_lose_prob(board, weights);

		if (win_prob > lose_prob && win_prob > greatest_win_prob)
		{
			best_move = i;
			greatest_win_prob = win_prob;
		}

		if (lose_prob < smallest_lose_prob)
		{
			smallest_lose_prob = lose_prob;
			smallest_lose_prob_pos = i;
		}

		board[i] = 'b';
	}

	if (best_move == -1)
		best_move = smallest_lose_prob_pos;

	return best_move;
}

/**
 * @brief
 * Calculates the input board's probability of winning using the inputted weights
 * @param board
 * eg. {'x','o','b','b','b','b','b','b','b'}
 * @param weights
 * struct containing the weights of the naive bayes model
 * @return float
 * Probability of winning
 */
float calculate_win_prob(int board[9], struct weights weights)
{
	float win_prob = 1;

	for (int i = 0; i < 9; i++)
	{
		switch (board[i])
		{
		case 'x':
			win_prob *= weights.p_x_win_pos[i];
			break;

		case 'b':
			win_prob *= weights.p_b_win_pos[i];
			break;

		case 'o':
			win_prob *= weights.p_o_win_pos[i];
			break;

		default:
			break;
		}
	}

	win_prob *= weights.p_win;

	return win_prob;
}

/**
 * @brief
 * Calculates the input board's probability of losing using the inputted weights
 * @param board
 * eg. {'x','o','b','b','b','b','b','b','b'}
 * @param weights
 * struct containing the weights of the naive bayes model
 * @return float
 * Probability of losing
 */
float calculate_lose_prob(int board[9], struct weights weights)
{
	float lose_prob = 1;

	for (int i = 0; i < 9; i++)
	{
		switch (board[i])
		{
		case 'x':
			lose_prob *= weights.p_x_lose_pos[i];
			break;

		case 'b':
			lose_prob *= weights.p_b_lose_pos[i];
			break;

		case 'o':
			lose_prob *= weights.p_o_lose_pos[i];
			break;

		default:
			break;
		}
	}
	lose_prob *= weights.p_lose;

	return lose_prob;
}
