/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hteixeir <hteixeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 18:09:15 by hteixeir          #+#    #+#             */
/*   Updated: 2024/08/26 14:08:25 by hteixeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

size_t	ft_slicecount(char const *pao, char n, int plics, int in)
{
	size_t	fatias;

	fatias = 0;
	while (*pao)
	{
		if (*pao == '\'')
			plics = !plics;
		if (*pao != n || plics)
		{
			if (in == 0)
			{
				fatias++;
				in = 1;
			}
		}
		else
		{
			in = 0;
		}
		pao++;
	}
	return (fatias);
}

int	ft_safe_malloc(char **ret, int x, int i)
{
	int		y;

	y = 0;
	ret[x] = malloc(i * sizeof(char));
	if (ret[x] == NULL)
	{
		while (y < x)
			free(ret[y++]);
		free(ret);
		return (1);
	}
	return (0);
}

int	ft_fill(char **ret, char const *s, char c, int plics)
{
	size_t	len;
	int		word;

	word = 0;
	while (*s)
	{
		len = 0;
		while (*s == c && *s && !plics)
			s++;
		while ((*s != c || plics) && *s)
		{
			if (*s == '\'')
				plics = !plics;
			s++;
			len++;
		}
		if (len)
		{
			if (ft_safe_malloc(ret, word, len + 1))
				return (0);
			ft_strlcpy(ret[word], s - len, len + 1);
			word++;
		}
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	size_t	palavras;
	char	**ret;

	if (!(s))
		return (NULL);
	palavras = 0;
	palavras = (ft_slicecount(s, c, 0, 0));
	ret = malloc((palavras + 1) * sizeof(char *));
	if (!(ret))
		return (NULL);
	ret[palavras] = (NULL);
	if (!(ft_fill(ret, s, c, 0)))
		return (NULL);
	return (ret);
}

/*int main(void)
{
    char const string[] = "testando split de string b lesgo";
    char delimiter = ' ';

    // Test ft_slicecount
    size_t slices = ft_slicecount(string, delimiter);
    printf("Número de fatias: %zu\n", slices);

    // Test ft_split
    char **split_result = ft_split(string, delimiter);
    if (split_result == NULL) {
        printf("Erro: Falha ao dividir a string.\n");
        return 1;
    }

    // Imprimir as fatias resultantes
    printf("Fatias resultantes:\n");
    for (size_t i = 0; i < slices; i++) {
        printf("%zu: %s\n", i, split_result[i]);
    }

    // Liberar memória alocada para as fatias
    for (size_t i = 0; i < slices; i++) {
        free(split_result[i]);
    }
    free(split_result);

    return 0;
}
	*/