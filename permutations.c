/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permutations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:23:47 by ilazar            #+#    #+#             */
/*   Updated: 2024/10/28 12:24:03 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char	*ft_strdup(char *src)
{
	char	*dup;
	int		i;

	i = 0;
	while (src[i])
		i++;
	dup = (char *)malloc(sizeof(char) * (i + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (src[i])
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

void	swap_char(char *a, char *b)
{
	char	tmp;

	tmp = *b;
	*b = *a;
	*a = tmp;
}

char	**permutations(char *str, int left, int len, char **res)
{
	int	i;

	if (left == len)
	{
		i = 0;
		while(res[i] != NULL)
			i++;
		res[i] = ft_strdup(str);
		res[i+1] = NULL;
	}
	else
	{
		for (int i = left; i <= len; i++)
		{
			swap_char(&str[left], &str[i]);
			permutations(str, left+1, len, res);
			swap_char(&str[left], &str[i]);
		}
	}
	return (res);
}

//ex: 4 -> 4*3*2*1 = 24
int	factorial(int num)
{
	int	sum;

	if (num <= 0)
		return (1);
	sum = num * factorial(num - 1);
	return (sum);

	// sum = 1;
	// while (num > 0)
	// 	sum = sum * num--; 
	// return (sum);
}

//1 if str1 is before
int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str2[i] != '\0')
	{
		if (str1[i] < str2[i])
			return (1);
		if (str1[i] > str2[i])
			return (0);
		else
			i++;
	}
	return (0);
}		

void	print_alphabet(char **res)
{
	int	tmp;
	int	i;

	i = 0;
	while (res[i] != NULL)
	{
		//find first string that is not '\n'
		while (res[i] != NULL && res[i][0] == '\n')
			i++;
		//if no string was found - all printed. quit
		if (res[i] == NULL)
			break ;
		//save index of the first found string
		tmp = i;
		//compare found string to the rest and save the index of the minimum ascii value
		while (res[i] != NULL)
		{
			if (res[i][0] != '\n' && ft_strcmp(res[i], res[tmp]))
				tmp = i;
			i++;
		}
		//print minimum string and 'erase' it from the array by changing it to '\n'
		printf("%s\n", res[tmp]);
		res[tmp][0] = '\n';
		i = 0;
	}
}

int	main(int ac, char **av)
{
	int	length;
	char	**res;
	int i;
	int	end;
	
	if (ac != 2)
		return (0);
	length = 0;
	while (av[1][length] != '\0')
		length++;
	//malloc big array
	end = factorial(length);
	res = (char **)malloc(sizeof(char *) * (end + 1));
	res[0] = NULL;
	//solve
	res = permutations(av[1], 0, length - 1, res);
	print_alphabet(res);
	//clean
	i = 0;
	while (res[i])
		free(res[i++]);
	free(res);
	return (0);
}
