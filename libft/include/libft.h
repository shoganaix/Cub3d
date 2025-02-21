/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:33:50 by macastro          #+#    #+#             */
/*   Updated: 2025/02/21 13:12:52 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "ft_printf.h"
# include "get_next_line.h"

typedef enum e_bool
{
	FALSE = 0,
	TRUE
}	t_bool;

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(char c);
int		is_space(char c);
int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_str_is_numeric(char *str);

char	*ft_strchr(const char *s, int c);
int		ft_strchri(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
size_t	ft_strlen(const char *s);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strdup(const char *s1);
char	*ft_strndup(const char *str, int n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin_inplace(char **s1, const char *s2);
char	*ft_strjoin_inplace2(char **s1, char **s2);
char	*ft_strappendc(char *s1, const char c);
char	*ft_strappendc_inplace(char *s1, const char c);
char	*ft_strtrim(char *s, char const *set);
char	*ft_strtriml(char *s, char const *set);
char	*ft_strtrimr(char *s, char const *set);
int		ft_count_words(const char *s, char sep);
char	**ft_split(char const *s, char c);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
int		ft_countchr(const char *str, char c, size_t n);
char	*ft_strjoin_realloc(char **dst, const char *src);
char	*ft_str_realloc(char *str, size_t size, int offset);
int		ft_count_arrstr(char **words);

void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_calloc(size_t count, size_t size);
void	ft_free_arrstr(char **words);
void	ft_free_arrstrn(char **words, int n);

int		ft_atoi(const char *str);
int		ft_atoi_hex(const char *str, int b);
t_bool	ft_atoi_secure(char *word, int *n);
int		is_gt_int_limits(char *num_as_word);
char	*ft_itoa(int n);
int		ft_min_nbr(int a, int b);
int		ft_min_arrint(int *ints, int n);
int		ft_max_nbr(int a, int b);

/**
 * print methods
*/
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_limit_fd(char *s, int max_chars, int fd);
void	ft_putchar_times_fd(char c, int times, int fd);

t_cs	*read_csp(const char *str, int *i);
char	*ft_number_to_base(unsigned long long n, char *base, int b);
char	*number_to_strhex(unsigned long long number, int mayus);
char	*number_to_strdec(long long number);
void	print_padding(int left, t_cs sc, int *pad, int len);
int		process_numflags(char *str, char sign,
			t_cs sc, int *len);
int		print_char(char c, t_cs sc, int fd);
int		print_str(char *s, t_cs sc, int fd);
int		print_pointer(void *pointer_addr, t_cs sc);
int		print_signed_number(long number, t_cs sc, int fd);
int		print_unsigned_number(unsigned int number, t_cs sc);
int		print_unsigned_hex(unsigned int number, t_cs sc);
int		ft_printf(const char *format, ...);

void	ft_putarr_ints(int *ints, int size);
void	ft_putarr_str(char **words);
void	ft_putarr_str_nl(char **words);

/**
 * list
*/
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
int		ft_lstindex(t_list *lst, void *content, int (*cmp)(void *, void *));

/**
 * deque
*/
typedef struct s_node
{
	struct s_node	*prev;
	void			*content;
	struct s_node	*next;
}	t_node;

typedef struct s_deque
{
	t_node	*head;
	t_node	*rear;
	int		size;
}	t_deque;

t_node	*ft_new_node(t_node *prev, void *content, t_node *next);
t_deque	*ft_new_deque(void);
void	ft_dq_append_rear(t_deque **dq, void *new_content);
void	ft_dq_append_head(t_deque **dq, void *new_content);
void	*ft_dq_pop_head(t_deque **dq);
void	*ft_dq_pop_rear(t_deque **dq);
int		ft_deque_count(t_deque *dq);
void	ft_clear_deque(t_deque **dq, void (*del)(void *));
void	ft_iter_deque(t_deque *dq, void (*f)(void *));
int		ft_dq_index(t_deque *dq, void *content, int *(*cmp)(void *, void *));

/**
 * get next line
*/
char	*get_next_line(int fd);

/**
 * dictionary int-str
*/
typedef struct s_kv_is
{
	int				key;
	char			*value;
	struct s_kv_is	*next;
}	t_kv_is;

typedef struct s_dctis
{
	t_kv_is	*head;
	t_kv_is	*tail;
	int		count;
}	t_dctis;
/*
t_dctis	*ft_new_dict_is(void);
t_kv_is	*ft_new_entry_is(int key, char *value, t_kv_is *next);
void	ft_clear_dict_is(t_dctis *self);
int		ft_dict_len_is(const t_dctis *self);
void	ft_dict_print_is(t_dctis *self);
char	*ft_dict_get_is(t_dctis *self, int key);
void	ft_dict_put_is(t_dctis *self, int key, char *value);
// void	ft_dict_del_is(t_dctis *self, int key);
*/

#endif
