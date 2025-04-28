#ifndef PHILO_H
#define PHILO_H

#define MIN_THINK_TIME 500
#define MAX_THINK_TIME 100000

#include <sys/time.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct s_philo
{
    int philo_id;
    int meals_eaten;
    long last_time_eat;

    pthread_t p_thread;
    pthread_mutex_t *right_fork;
    pthread_mutex_t *left_fork;

    struct s_data *data;
} t_philo;

typedef struct s_data
{
    int num_philos;
    int time_to_die;
    int time_to_sleep;
    int time_to_eat;
    int max_meals;
    int full_philos;
    struct timeval start_time;

    pthread_mutex_t write_lock;
    pthread_mutex_t death_lock;
    pthread_mutex_t *forks;

    pthread_t monitor;

    bool sim_end;
    t_philo *philo;
} t_data;

// parsing functions
int parsing(char const *argv[]);
int ft_atoi(const char *str);

// init functions
int data_init(t_data *data, char const *argv[]);
int philo_init(t_data *data);
int thread_init(t_data *data);

// costum functions
int p_eat(t_philo *philo);
int p_sleep(t_philo *philo);
int p_think(t_philo *philo);
int ft_sleep(long mill);

// utils function
void print_state(t_philo *philo, char *msg);
long get_time_in__ms(void);
long get_elapsed_time(t_philo *philo);
void join_philo_threads(t_data *data, int count);

// check simulation end functions
bool all_eat_enough(t_data *data);
bool exceed_time_to_die(t_data *data);
void one_philo_case(t_philo *philo);
int is_sim_end(t_data *data);
bool check_meals(t_philo *philo);

// error print functions
int mutex_init_err(void);
int mem_err(void);
int err(void);
int thread_err(t_data *data);
int mutex_destroy_err(void);

// cleaning functions
void destroy_free(t_data *data, bool destroy_write_lock);
void clean_forks_array(t_data *data, int i);
void destroy_free_all(t_data *data);

#endif