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


int get_best_move(int board[9]);
float calculate_win_prob(int board[9], struct weights weights);
float calculate_lose_prob(int board[9], struct weights weights);