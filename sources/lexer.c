#include "minishell.h"

// THIS WILL PUT A SEP BEFORE AND AFTER THE SIMBOLS >, < AND |
static char	*filler(char *input, int pos)
{
	char	*result;
	int		i;
	int		j;

	result = ft_calloc(ft_strlen(input) + 3, sizeof (char));
	if (!result)
		return (NULL);
	i = -1;
	j = -1;
	while (++j < pos)
		result[j] = input[++i];
	i++;
	result[j++] = SEP;
	result[j++] = input[i++];
	if (input[i] == input[i - 1] && input[i] != '|')
		result[j++] = input[i++];
	result[j++] = SEP;
	while (input[i])
		result[j++] = input[i++];
	result[j] = '\0';
	input = free_ptr(input);
	return (result);
}

char	**ft_lexer(char *input)
{
	int		i;
	int		quotes;
	char	*temp;
	char	**result;

	i = -1;
	quotes = 0;
	temp = ft_strdup(input);
	while (temp && temp[++i])
	{
		if ((temp[i] == '>' || temp[i] == '<' || temp[i] == '|' ) && !quotes)
		{
			temp = filler(temp, i);
			i =+ 2;
		}
		else if (temp[i] == '\'' || temp[i] == '\"')
			quotes = check_quotes(temp[i], quotes);
	}
	if (quotes)
		temp = free_ptr(temp);
	result = ft_split(temp, SEP);
	temp = free_ptr(temp);
	return (result);
}
