/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 12:46:36 by ndormoy           #+#    #+#             */
/*   Updated: 2022/02/01 13:01:21 by ndormoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>

# define TRUE 1
# define FALSE 0

# define FORKING "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DYING "died"

/*Structure de tous les philo, contient les info de bases (arguments ...)
On a aussi un tableau de fourchette, et un tableau de philo.
Quand stop est à 1 on arrête le programme. Not_hungry -> nombre de philo qui
ont terminé de manger. Start -> debut du programme en temps*/

typedef struct s_info
{
	struct s_philo		*philo;
	pthread_mutex_t		*fork;
	pthread_mutex_t		mutex;
	size_t				time2eat;
	size_t				time2sleep;
	size_t				time2die;
	size_t				nbmust_eat;
	int					nb_philo;
	int					stop;
	int					not_hungry;
	size_t				start;
}t_info;

/*Structure de chaque philo, on a un pointeur vers info, comme ça on peut avoir
info en passant juste la structure philo, evite de faire un singletone ou de 
devoir se compliquer la vie*/

typedef struct s_philo
{
	t_info			*info;
	pthread_mutex_t	mutex_philo;
	pthread_mutex_t	mutex_print;
	pthread_t		thread;
	size_t			last_eat;
	int				index;
	size_t			nb_eat;
	int				fork_l;
	int				fork_r;
}t_philo;

/*---------------------------Utils--------------------------*/
int		ft_isdigit(int c);
void	*ft_memset(void *s, int c, size_t n);

/*-------------Regarde si les arguments sont bons-----------*/
int		ft_check_args(int argc, char **argv);

/*-------Initialise les Philo, mutex, convertie Args--------*/
t_info	*ft_init(int argc, char **argv);

/*Permet de nettoyer la mémoire si il y a un pb ou a la fin-*/
void	ft_clean(t_philo *philo);
void	ft_error(void);

/*---------------Va creer les threads philo-----------------*/
void	ft_create_philo(t_info *info);

/*---------------------------Actions------------------------*/
void	take_fork(t_philo *philo);
void	eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	think(t_philo *philo);

/*-------------------Affiche Etat d'un philo----------------*/
void	print_state(t_philo *philo, char *state);

/*---------------------------TIME---------------------------*/
size_t	what_time_ms(void);
size_t	real_time(t_philo *philo);
void	ms_sleep(t_philo *philo, size_t usec_time);

#endif