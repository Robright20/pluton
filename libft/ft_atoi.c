/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fokrober <fokrober@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 10:17:15 by fokrober          #+#    #+#             */
/*   Updated: 2020/12/24 10:18:34 by fokrober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_atoi(const char *str)
{
	int			signe;
	int			i;
	long long	nbr;

	i = 0;
	signe = 1;
	nbr = 0;
	while ((str[i] < 14 && str[i] > 8) || str[i] == 32)
		i++;
	if (str[i] == '-')
		signe = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] > 47 && str[i] < 58)
	{
		if (nbr > (nbr * 10 + (str[i] - '0')))
			return (signe > 0 ? -1 : 0);
		nbr = nbr * 10 + (str[i++] - '0');
	}
	return (nbr * signe);
}
