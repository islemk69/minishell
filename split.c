#include <stdio.h>
#include <stdlib.h>

static int	ft_countword(const char *s, char c)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (s[i])
	{
		if ((s[i] == c || s[i] == '\0') == 0
			&& (s[i + 1] == c || s[i + 1] == '\0') == 1)
			j++;
		i++;
	}
	return (j + 1);
}

static int	ft_sizeword(const char *s, char c, int pos)
{
	int	count;

	count = 0;
	while (s[pos])
	{
		if (s[pos] == c)
			return (count + 1);
		pos++;
		count++;
	}
	return (count + 1);
}

static char	**ft_free(char **tab, int j)
{
	int	i;

	i = -1;
	while (i++ < j)
		free (tab[i]);
	free(tab);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	tab = (char **)malloc(sizeof(char *) * ft_countword(s, c));
	if (!tab)
		return (NULL);
	while (s[k] && i < ft_countword(s, c) - 1)
	{
		while (s[k] == c)
			k++;
		tab[i] = (char *)malloc(sizeof (char) * ft_sizeword(s, c, k));
		if (!tab[i])
			return (ft_free(tab, i));
		j = 0;
		while (s[k] && s[k] != c)
			tab[i][j++] = s[k++];
		tab[i][j] = '\0';
		i++;
	}
	tab[i] = 0;
	return (tab);
}

/*
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	int		i;
	int		j;

	ptr = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		ptr[i] = s2[j];
		i++;
		j++;
	}
	ptr[i] = '\0';
	return (ptr);
}*/




int main()
{
    char *str = "   salut s\"a\" va ";
    char **split = ft_split(str, ' ');
    int i = 0;
    while (split[i])
    {
        printf("%s\n", split[i]);
        free(split[i++]);
    }
    free(split);
    ////////////////////////////////////////////////////////////////////
    int j = 0;
    while (split)
    return (1);
}