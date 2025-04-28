#include "philo.h"

int main(int argc, char const *argv[])
{
	struct s_data *data;

	if (argc != 5 || parsing(argv + 1) == -1)
		return (err());
	data = malloc(sizeof(t_data));
	if (data_init(data, argv + 1) == -1 || philo_init(data) == -1)
	{
		free(data);
		return (-1);
	}
	thread_init(data);
	destroy_free_all(data);
	return (0);
}