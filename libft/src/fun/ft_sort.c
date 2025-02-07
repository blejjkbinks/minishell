/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:52:18 by rdomange          #+#    #+#             */
/*   Updated: 2024/12/03 15:52:19 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_sort_swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static void	ft_quick_sort(int *arr, int low, int high)
{
	int	i;
	int	j;
	int	p;

	if (low < high)
	{
		p = arr[high];
		i = low - 1;
		j = low;
		while (j < high)
		{
			if (arr[j] <= p)
			{
				i++;
				ft_sort_swap(&arr[i], &arr[j]);
			}
			j++;
		}
		ft_sort_swap(&arr[i + 1], &arr[high]);
		ft_quick_sort(arr, low, i);
		ft_quick_sort(arr, i + 2, high);
	}
}

void	ft_sort(int *arr, int n)
{
	ft_quick_sort(arr, 0, n -1);
}
