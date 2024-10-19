#include "minishell.h"

char	*ft_strjoinn(char *pre, char *affix)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = -1;
	j = 0;
	if (!pre)
		pre = ft_calloc(1, sizeof(char));
	if (!pre || !affix)
		return (NULL);
	str = ft_calloc(ft_strlen(pre) + ft_strlen(affix) + 1, sizeof (char));
	if (!str)
		return (0);
	while (pre[++i])
		str[i] = pre[i];
	while (affix[j])
		str[i++] = affix[j++];
	str[i] = '\0';
	affix = free_ptr(affix);
	pre = free_ptr(pre);
	return (str);
}

char	*ft_itoaa(int n)
{
	char	*strnum;
	int		length;
	int		counter;

	counter = n;
	if (!counter)
		return (ft_strdup("0"));
	length = 0;
	while (counter)
	{
		counter = counter / 10;
		length++;
	}
	strnum = ft_calloc(length + 1, sizeof(char));
	while (n)
	{
		strnum[length - 1] = (n % 10) + 48;
		n = n / 10;
		length--;
	}
	return (strnum);
}

int	equalsign(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}
