/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 20:13:20 by mbaron            #+#    #+#             */
/*   Updated: 2018/01/22 18:40:35 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static int		toggle_piece_grid(t_piece *piece, int grid[])
{
	int		i;
	int		l;
	int		c;

	i = piece->max;
	l = (piece->pos >> 4) & 0xF;
	c = piece->pos & 0xF;
	while (i > piece->min)
	{
		if (piece->n & (1 << i))
			grid[l] ^= 1 << (i - c);
		if (!(i & 3))
		{
			l++;
			c -= 4;
		}
		i--;
	}
	return (1);
}

/*
static int		get_next_line_last(t_piece *piece, int grid[], int l)
{
	int		i;

	i = 0;
	while (i < piece->h)
	{
		if (grid[l + i] == GRID_ALL_ONE)
			return (l - piece->h + i);
		i++;
	}
	return (l);
}
*/

static int		get_next_line_next(t_piece *piece, int grid[], int grid_size)
{
	int		i;
	int		l;

	l = (piece->pos >> 4) & 0xF;
	i = l + piece->h;
	while (i > l)
	{
		i--;
		if (grid[i] == GRID_ALL_ONE)
		{
			if (i <= grid_size - piece->h)
			{
				//printf("continue\n");
				piece->pos = 16 * (i + 1);
				printf("get_next_line next exit1 1: l:%d i:%d pos:%d\n", l, i, piece->pos);
				return (1);
			}
			else
			{
				piece->pos = -1;
				printf("get_next_line next exit0 1: l:%d i:%d pos:%d\n", l, i, piece->pos);
				return (0);
			}
		}
	}
	printf("get_next_line next exit1 2: l:%d i:%d pos:%d\n", l, i, piece->pos);
	return (1);
}

static int		test_piece_grid(t_piece *piece, int grid[], int grid_size)
{
	int		i;
	int		l;
	int		c;

	if (!get_next_line_next(piece, grid, grid_size))
		return (-1);
	l = (piece->pos >> 4) & 0xF;
	c = piece->pos & 0xF;
	i = piece->max;
	printf("test_piece_grid: ini pos:%d max:%d min:%d l:%d c:%d\n", piece->pos, piece->max, piece->min, l, c);
	while (i > piece->min)
	{
		printf("test_piece_grid: before l:%d i-c:%d piece->n:%x grid[l]:%x\n", l, i - c, piece->n, grid[l]);
		if ((piece->n & (1 << i)) && (grid[l] & (1 << (i - c))))
		{
			printf("test_piece_grid: exit0 pos:%d l:%d c:%d\n", piece->pos, l, c);
			return (0);
		}
		if (!(i & 3))
		{
			l++;
			c -= 4;
		}
		i--;
	}
	printf("test_piece_grid: exit1 pos:%d l:%d c:%d\n", piece->pos, l, c);
	return (1);
}

/*
static int		get_last_position(t_piece *pieces, int bt_size, int grid[],
	int grid_size)
{
	t_piece	*p;
	int		l;
	int		c;
	int		l_min;
	int		c_min;
	int		l_next;

	p = &pieces[bt_size];
	l_min = p->prev != -1 ? pieces[p->prev].l : 0;
	c_min = p->prev != -1 ? pieces[p->prev].c : 0;
	l = grid_size - p->h;
	c = grid_size - p->w;
	while (l > l_min || (l == l_min && c >= c_min))
	{
		if (p->pos > 16 * l + c)
			return (-1);
		l_next = get_next_line_last(p, grid, l);
		if (l != l_next)
		{
			//printf("get_last_position gs:%d p:%d l:%d l_next:%d l_min:%d\n", grid_size, bt_size, l, l_next, l_min);
			if (l_next >= l_min)
			{
				l = l_next;
				c = grid_size - p->w;
			}
			else
				return(0);
		}
		if (test_piece_grid(p, l, c, grid))
			return (l * 16 + c);
		c--;
		if (c == -1)
		{
			l--;
			c = grid_size - p->w;
		}
	}
	return (-1);
}
*/

static int		get_next_position(t_piece *pieces, int bt_size, int grid[],
	int grid_size)
{
	t_piece	*p;
	//int		test;
	
	
	p = &pieces[bt_size];
	printf("---- get_next_position : bt:%d n:%d pos:%d\n", bt_size, p->n, p->pos);
	if (p->pos >= p->last)
	{
		printf("exit -1 1: pos:%d last:%d\n", p->pos, p->last);
		return (-1);
	}
	if (p->pos == -1)
		p->pos = 0;
	else {
		printf("    grid_size:%d pos:%d posm16:%d, pw:%d, dec:%d, next:%d \n", grid_size, p->pos, p->pos % 16, p->w, p->pos % 16 + p->w, p->pos + 16 - grid_size + p->w);
		if (p->pos % 16 + p->w == grid_size)
		{
			printf("    ici \n");
			if (((p->pos >> 4) & 0xF) >= grid_size - p->h)
			{
				printf("exit -1 2: pos:%d last:%d\n", p->pos, p->last);
				return (-1);
			}
			p->pos += 16 - grid_size + p->w;
		}
		else
			p->pos++;
	}
	// test = test_piece_grid(p, grid, grid_size);
	// printf("test : %d pos:%d last:%d\n", test, p->pos, p->last);
	return (test_piece_grid(p, grid, grid_size));
	// return (test);
	/*
	if (get_next_line_next(p, grid))
	;
	if (p->l != l_next)
	{
		//printf("get_next_position gs:%d p:%d last:%d l:%d l_next:%d gs-p->h:%d\n", grid_size, bt_size, p->last, p->l, l_next, grid_size - p->h);

		if (l_next <= grid_size - p->h)
		{
			//printf("continue\n");
			p->l = l_next;
			p->c = 0;
		}
		else
		{
			//printf("exit\n");
			p->pos = p->last;
			return(0);
		}
	}
	p->pos = 16 * p->l + p->c;
	return (test_piece_grid(p, p->l, p->c, grid));
	*/
}

int				solver_add_piece_grid(t_piece *pieces, int *p_bt_size,
	int grid[], int grid_size)
{
	t_piece	*piece;
	int		next;

	printf("-------------- solver_add_piece_grid : begin %d\n", *p_bt_size);
	piece = pieces + *p_bt_size;
	// if (piece->prev != -1)
	// 	piece->pos = pieces[*p_bt_size].pos;
	//printf("solver_add_piece_grid : pos:%d prev:%d\n", piece->pos, piece->prev);
	printf("solver_add_piece_grid n:%d pos:%d\n", piece->n, piece->pos);
	if (piece->pos == -1)
	{
		if (piece->prev == -1)
		{
			piece->last = 16 * (grid_size - piece->h) + grid_size - piece->w;
			printf("solver_add_piece_grid : grid_size:%d h:%d w:%d last:%d\n", grid_size , piece->h, piece->w, piece->last);
		}
		else
		{	
			piece->pos = pieces[*p_bt_size].pos;
			piece->last = pieces[*p_bt_size].last;
		}	
		//piece->last = get_last_position(pieces, *p_bt_size, grid, grid_size);
	}
	printf("solver_add_piece_grid : pos:%d last:%d\n", piece->pos, piece->last);
	//exit(1);
	next = 0;
	while (!next && piece->pos <= piece->last)
	{
		printf("solver_add_piece_grid --> before next pos:%d last:%d\n", piece->pos, piece->last);
		next = get_next_position(pieces, *p_bt_size, grid, grid_size);
		printf("solver_add_piece_grid --> after next pos:%d last:%d\n", piece->pos, piece->last);
	}
	// next = (piece->last == -1 || (piece->last > -1
	// 	&& piece->pos == piece->last))
	// 	? 0 : get_next_position(pieces, *p_bt_size, grid, grid_size);
	if (next)
	{
		printf("solver_add_piece_grid next = 1 : pos:%d last:%d\n", piece->pos, piece->last);
		toggle_piece_grid(piece, grid);
		printf("solver_add_piece_grid next = 1 : pos:%d last:%d\n", piece->pos, piece->last);
		//printf("add %d n:%d l:%d c:%d pos:%d last:%d\n", *p_bt_size, piece->n, piece->l, piece->c, piece->pos, piece->last);
		//solver_write_grid(grid, grid_size);
		//piece->pos = 16 * piece->l + piece->c;
		(*p_bt_size)++;
		pieces[*p_bt_size].last = -1;
		printf("solver_add_piece_grid next = 1 : pos:%d last:%d\n", piece->pos, piece->last);
		return (1);
	}
	else 
	{
		//printf("remove %d n:%d l:%d c:%d pos:%d last:%d\n", *p_bt_size, piece->n, piece->l, piece->c, piece->pos, piece->last);
		init_piece(&pieces[*p_bt_size]);
		if (!(*p_bt_size))
			return (0);
		(*p_bt_size)--;
		toggle_piece_grid(&pieces[*p_bt_size], grid);
		return (0);
		//solver_write_grid(grid, grid_size);
	}
	return (1);
}
