#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *extract_dollard(char *str)
{
	int	i = 0;
	int j;
	int flg = 0;
	int size = 0;
	char *realloc;
	
	while (str[i] != '$')
	{
		if (str[i] == '\"' || str[i] == '\'')
			flg = 1;
		i++;
		size++;
	}
	j = i;
	if (flg)
		return (str);
	while (str[i] && str[i] != '\"' && str[i] != '\'' && str[i] != '$')
		i++;
	j = i;
	while (str[i])
	{
		size++;
		i++;
	}
	i = 0;
	printf("SIZE %d\n", size);
	realloc = malloc(sizeof(char) * (size + 1));
	while (str[j])
	{
		realloc[i] = str[j];
		j++;
		i++;
	}
	realloc[i] = 0;
	return (realloc);
}

int main() {
    char *str = "sadasds$asdsdad";
	printf("%s\n", extract_dollard(str));
}