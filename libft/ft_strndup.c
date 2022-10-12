#include "../minishell.h"

char	*ft_strndup(const char *s1, int n)
{
	char	*ret;
	int		len;
	int		i;

	len = 0;
	while (s1[len] && len < n)
		len++;
	if (!(ret = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	while (i < len)
	{
		ret[i] = s1[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
