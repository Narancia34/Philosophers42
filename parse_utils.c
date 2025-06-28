/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamraou <mgamraou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 10:43:39 by mgamraou          #+#    #+#             */
/*   Updated: 2025/06/28 11:04:18 by mgamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	error_exit(char *str)
{
	printf("%s\n", str);
	exit(EXIT_FAILURE);
}

static inline bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static inline bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

char	*valid_str(char *str)
{
	int	len;
	char	*res;

	len = 0;
	while (is_space(*str))
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-')
		error_exit("negative number");
	if (!is_digit(*str))
		error_exit("not a number");
	res = str;
	while (is_digit(*str++))
		++len;
	if (len > 10)
		error_exit("value bigger than INT_MAX");
	return (res);
}

long	ft_atol(char *str)
{
	long	num;

	num = 0;
	str = valid_str(str);
	while (is_digit(*str))
		num = (num * 10) + (*str++ - 48);
	if (!is_digit(*str) && *str)
		error_exit("not a number");
	if (num > INT_MAX)
		error_exit("value bigger than INT_MAX");
	return 1;
}
