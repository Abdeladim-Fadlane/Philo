/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:47:56 by afadlane          #+#    #+#             */
/*   Updated: 2023/03/31 15:24:17 by afadlane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	split_ft_init(t_philo *p, t_info *info, int i)
{
	if (pthread_mutex_init(&p->forks, NULL) != 0)
		printf("error\n");
	p->id = i + 1;
	p->eaten = 0;
	p->infop = info;
}

void	ft_init_philo(t_philo *p, char **av, int ac)
{
	int		i;
	t_info	*info;
	t_philo	*tmp;

	info = malloc(sizeof(t_info));
	get_and_insia(info, av, ac);
	tmp = p;
	i = 0;
	while (i < info->number_of_philosophers)
	{
		split_ft_init(p, info, i);
		if (i + 1 < info->number_of_philosophers)
		{
			p->right = malloc(sizeof(t_philo));
			p->right->left = p;
			p = p->right;
		}
		else
		{
			p->right = tmp;
			tmp->left = p;
		}
		i++;
	}
	p = tmp;
}

void	*thread_func(void *tmp)
{
	t_philo	*p;

	p = (t_philo *)tmp;
	if (p->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		eat(p);
		pthread_mutex_lock(&p->infop->lock);
		printf("%ld  Philo : %d is sleeping.  \n", get_current_time(p), p->id);
		pthread_mutex_unlock(&p->infop->lock);
		sleep_time(p->infop->time_to_sleep, p);
		pthread_mutex_lock(&p->infop->lock);
		printf("%ld  Philo : %d is thinking.\n", get_current_time(p), p->id);
		pthread_mutex_unlock(&p->infop->lock);
	}
	return (NULL);
}

void	get_and_insia(t_info *p, char **av, int ac)
{
	p->number_of_philosophers = ft_atoi(av[1]);
	p->time_to_die = ft_atoi(av[2]);
	p->time_to_eat = ft_atoi(av[3]);
	p->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		p->time_must_eat = ft_atoi(av[5]);
	else
		p->time_must_eat = -1;
	if (pthread_mutex_init(&p->lock, NULL) != 0)
		printf("error\n");
}
