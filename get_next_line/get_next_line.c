#include "get_next_line.h"

int	gnl_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*gnl_strdup(char *arr)
{
	char	*new_arr;
	int		i;

	new_arr = (char *)malloc(gnl_strlen(arr) + 1);
	if (!new_arr)
		return (NULL);
	i = 0;
	while (arr[i] != '\0')
	{
		new_arr[i] = arr[i];
		i++;
	}
	new_arr[i] = '\0';
	return (new_arr);
}

char	*gnl_strjoin(char *arr, char *buff)
{
	int		i;
	int		j;
	char	*new_arr;

	if (buff == NULL)
		return (NULL);
	if (arr == NULL)
		arr = gnl_strdup("");
	new_arr = (char *)malloc(gnl_strlen(arr) + gnl_strlen(buff) + 1);
	if (!new_arr)
		return (NULL);
	i = 0;
	while (arr[i] != '\0')
	{
		new_arr[i] = arr[i];
		i++;
	}
	j = 0;
	while (buff[j] != '\0')
		new_arr[i++] = buff[j++];
	new_arr[i] = '\0';
	free(arr);
	return (new_arr);
}

int	find_next_line(char *arr)
{
	int	i;

	i = 0;
	while (arr[i] != '\0')
	{
		if (arr[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	return (i);
}

char	*read_lines(int fd, char *arr)
{
	int		bytes_read;
	char	buff[BUFFER_SIZE + 1];

	bytes_read = read(fd, buff, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buff[bytes_read] = '\0';
		arr = gnl_strjoin(arr, buff);
		if (buff[find_next_line(buff) - 1] == '\n')
			break ;
		bytes_read = read(fd, buff, BUFFER_SIZE);
	}
	if (bytes_read == -1)
	{
		free(arr);
		return (NULL);
	}
	return (arr);
}

char	*get_a_line(char *arr)
{
	int		i;
	int		len;
	char	*line;

	if (!arr)
		return (NULL);
	i = 0;
	len = find_next_line(arr);
	line = (char *)malloc(len + 1);
	if (!line)
		return (NULL);
	line[len] = '\0';
	while (i < len)
	{
		line[i] = arr[i];
		i++;
	}
	return (line);
}

char	*control_line(char *arr)
{
	char	*new_arr;

	if (!arr)
		return (NULL);
	if (arr[find_next_line(arr)] == '\0')
	{
		free(arr);
		return (NULL);
	}
	new_arr = gnl_strdup(&arr[find_next_line(arr)]);
	free(arr);
	return ((new_arr));
}

char	*get_next_line(int fd)
{
	static char	*arr;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	arr = read_lines(fd, arr);
	line = get_a_line(arr);
	arr = control_line(arr);
	return (line);
}
