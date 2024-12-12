/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dict_is1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 10:45:31 by macastro          #+#    #+#             */
/*   Updated: 2024/10/16 18:43:14 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

t_dctis	*ft_new_dict_is(void)
{
	t_dctis	*p;

	p = malloc(sizeof(*p));
	p->head = NULL;
	p->tail = NULL;
	p->count = 0;
	return (p);
}

t_kv_is	*ft_new_entry_is(int key, char *value, t_kv_is *next)
{
	t_kv_is	*entry;

	entry = malloc(sizeof(t_kv_is));
	if (!entry)
		return (NULL);
	entry->key = key;
	entry->value = value;
	entry->next = next;
	return (entry);
}

void	ft_clear_dict_is(t_dctis *self)
{
	t_kv_is	*cur;
	t_kv_is	*next;

	cur = self->head;
	while (cur)
	{
		free(cur->value);
		next = cur->next;
		free(cur);
		cur = next;
	}
	free((void *)self);
}

int	ft_dict_len_is(const t_dctis *self)
{
	return (self->count);
}

void	ft_dict_print_is(t_dctis *self)
{
	int		first;
	t_kv_is	*cur;

	first = 1;
	ft_printf("{");
	cur = self->head;
	while (cur != NULL)
	{
		if (!first)
			ft_printf(", ");
		ft_putnbr_fd(cur->key, 1);
		ft_printf(": \"");
		ft_putstr_fd(cur->value, 1);
		ft_printf("\"");
		first = 0;
		cur = cur->next;
	}
	ft_printf("}\n");
}

/*void	test_dict(void)
{
	t_kv_is	*cur;
	t_dctis 	*dct = ft_new_dict_is();

	ft_dict_put_is(dct, 2, "Catch phrase");
	ft_dict_print_is(dct);
	ft_dict_put_is(dct, 2, "W");
	ft_dict_print_is(dct);
	ft_dict_put_is(dct, 3, "B");
	ft_dict_put_is(dct, 4, "C");
	ft_dict_put_is(dct, 1, "D");
	ft_dict_print_is(dct);
	ft_printf("Length = %d\n",ft_dict_len_is(dct));
	ft_printf("dict[2] = %s\n", ft_dict_get_is(dct, 2));
	ft_printf("dict[3] = %s\n", ft_dict_get_is(dct, 3));
	ft_printf("\nTraversing..\n");
	for(cur = dct->head; cur != NULL ; cur = cur->next ) {
		ft_printf("%d=%s\n", cur->key, cur->value);
	}
	ft_clear_dict_is(dct);
}*/
