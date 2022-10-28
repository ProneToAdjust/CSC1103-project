#include <stdio.h>

struct weights
	{
		float p_x_win_pos[9];
		float p_b_win_pos[9];
		float p_o_win_pos[9];

		float p_x_lose_pos[9];
		float p_b_lose_pos[9];
		float p_o_lose_pos[9];

		float p_win;
		float p_lose;
	};

struct weights weights;

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

int get_best_move(int board[9])
{
	if (weights.p_win == 0)
	{
		initialize();
	}

	int best_move = 0;
	float win_prob = 0;
	float prev_win_prob = 0;
	float lose_prob = 0;

	for (int i = 0; i < 9; i++)
	{
		if (board[i] != 'b')
			continue;

		board[i] = 'x';

		win_prob = calculate_win_prob(board, weights);
		lose_prob = calculate_lose_prob(board, weights);

		if (win_prob > lose_prob && win_prob > prev_win_prob)
		{
			best_move = i;
		}
		else if (win_prob > prev_win_prob)
		{
			best_move = i;
		}

		prev_win_prob = win_prob;

		board[i] = 'b';
	}

	return best_move;
}

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
