/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 14:57:24 by chanhyle          #+#    #+#             */
/*   Updated: 2022/01/06 17:36:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_option
{
	int		f_minus; //0
	int		f_space; //1
	int		f_plus;  //2
	int		f_sharp; //3
	int		f_zero;  //4
	int		width;   //5
	int		dot;     //6
	int		prcs;	 //7
	char	type;	 //8
	int		neg;	 //9
}					t_option;

int		ft_printf(const char *format, ...);
char	*print_cs(const char *format, va_list ap, int *ret, int (*opt)[10]);
char	*print_p(const char *format, va_list ap, int *ret, int (*opt)[10]);
char	*print_int(const char *format, va_list ap, int *ret, int (*opt)[10]);
char	*print_uint(const char *format, va_list ap, int *ret, int (*opt)[10]);
char	*print_hex(const char *format, va_list ap, int *ret, int (*opt)[10]);
int		unsigned_digits(unsigned long long n, int base);
char	*make_uint_string(unsigned int n);
char	*make_hex_string(unsigned long long n, int flag);
char	*add_prefix(char **str, int flag);
int		ft_print_string(char *str, int *ret, int (*opt)[10]);
void	flag_switch_fuction(int *ret, int (*opt)[10], int len, int i);
int		flag_print_plus(int *ret, int (*opt)[10], int i);
int		flag_print_space_or_zero(int *ret, int (*opt)[10], int len, int i);
void	flag_print_string(char *str, int *ret, int (*opt)[10], int flag);
void	print_sharp(int *ret, int (*opt)[10]);
void	write_and_plus(char *sg_char, int *ret, int flag);
void	*ft_memset(void *s, int c, size_t n);
size_t	ft_strlen(const char *s);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_number_of_digits(int n);
char	*ft_itoa(int n);

#endif
