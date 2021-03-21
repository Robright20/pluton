/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 22:22:07 by zael-mab          #+#    #+#             */
/*   Updated: 2021/03/21 15:47:44 by zael-mab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdarg.h>

# define NOTHING		0
# define MINES			1
# define PLUS			2
# define HASH			4
# define SPACE			16
# define ZERO			32
# define FD_MAX 		4864
# define BUFF_SIZE 		100

typedef struct			s_data
{
	int					jumper;
	int					ps;
	int					flg;
	int					pres;
	int					h_flags;
	int					l_flags;
	int					fw0;
	int					fw1;
	int					huck;
	char				*f_lags;
	char				*types;
	char				*ar;
}						t_data;

typedef struct			s_cnt
{
	char				*arr;
	long double			c;
	double				s;
	int					i;
	int					total;
	int					x;
	int					a;
	int					b;
	char				*res;
	char				*z;
	char				*mantissa;
	char				*exp;
	int					sign;
	char				lg;
	int					u;
}						t_cnt;

typedef struct			s_lol
{
	int					y;
	int					x;
	int					d;
	int					tp;
	int					z;
	int					k;
	int					r;
	int					p;
	char				*vf;
	char				*res;
	char				*tmp;
}						t_lol;

typedef struct			s_ayy
{
	char				*rar;
	char				*tmp;
	char				a;
	unsigned long long	n;
	int					w0;
	int					w1;
	int					y0;
	int					y1;
	int					y2;
	int					carry;
	int					looper;
	long long			sum;
}						t_ayy;

int						ft_strscmp(const char *s1, const char *s2, size_t s,
		size_t n);
char					*ft_strscpy(char *dst, const char *src, size_t s,
		size_t len);
int						get_next_line(int const fd, char **line);
void					*ft_memset(void *b, int c, size_t len);
void					ft_bzero(void *s, size_t n);
void					*ft_memcpy(void *dst, const void *src, size_t n);
void					*ft_memccpy(void *dst, const void *src, int c,
		size_t n);
void					*ft_memmove(void *dst, const void *src, size_t len);
void					*ft_memchr(const void *s, int c, size_t n);
void					ft_putchar(char c);
int						ft_memcmp(const void *s1, const void *s2, size_t n);
int						ft_strlen(const char *str);
size_t					ft_strlenp(const char *str);
char					*ft_strdup(char *s1);
char					*ft_strcpy(char *dst, const char *src);
char					*ft_strnjoin(char const *s1, char const *s2, size_t n);
char					*ft_strncpy(char *dst, const char *src, size_t len);
char					*ft_strcat(char *s1, const char *s2);
char					*ft_strncat(char *s1, const char *s2, size_t n);
size_t					ft_strlcat(char *dst, const char *src, size_t size);
char					*ft_strchr(const char *s, int c);
char					*ft_strrchr(const char *s, int c);
char					*ft_strstr(const char *str, const char *srh);
char					*ft_strnstr(const char *str, const char *srh,
		size_t len);
int						ft_strcmp(const char *s1, const char *s2);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
int						ft_atoi(const char *str);
int						ft_isalpha(int c);
int						ft_isdigit(int c);
int						ft_isalnum(int c);
int						ft_isascii(int c);
int						ft_isprint(int c);
int						ft_toupper(int c);
int						ft_tolower(int c);
void					*ft_memalloc(size_t size);
void					ft_memdel(void	**ap);
char					*ft_strnew(size_t size);
void					ft_strdel(char **as);
void					ft_strclr(char *s);
void					ft_striter(char *s, void (*f)(char *));
void					ft_putstr(char const *s);
void					ft_striteri(char *s, void(*f)(unsigned int, char *));
void					ft_putendl(char const *s);
void					ft_putnbr(int n);
char					*ft_strmap(char const *s, char (*f)(char));
char					*ft_strmapi(char const *s,
		char (*f)(unsigned int, char));
void					ft_putchar_fd(char c, int fd);
void					ft_putstr_fd(char const *s, int fd);
void					ft_putendl_fd(char const *s, int fd);
void					ft_putnbr_fd(int n, int fd);
int						ft_strequ(char const *s1, char const *s2);
int						ft_strnequ(char const *s1, char const *s2, size_t n);
char					*ft_strsub(char const *s1, unsigned int start,
		size_t len);
char					*ft_strjoin(char const *s1, char const *s2);
char					*ft_strtrim(char const *s);
char					**ft_strsplit(char const *s, char c);
char					*ft_itoa_u(unsigned long long n);
char					*ft_itoa(long long n);
int						check_ad(void *p);
void					z_data_flg(t_data *data, t_lol lol, const char *ar);
void					a01_prim(t_data *data, t_cnt *cnt, t_lol *lol,
		const char *ar);
void					a04_prim(t_data data, t_cnt *cnt, va_list vl,
		const char *f);
void					a04_p(t_data data, t_cnt *cnt);
void					a02(t_data *data, t_lol lol, const char *ar);
void					it_b09(unsigned long long value, int base, t_ayy *ayy);
void					dd(int i, int j, char b);
void					a06_prim(t_data data, t_cnt *cnt);
void					a10prim(t_data data, t_cnt *cnt, const char *ar,
		va_list vl);
void					a11d_prim(t_data data, const char *ar, t_cnt *cnt);
void					a10prim0(t_data data, t_cnt *cnt, const char *ar);
void					z_data_huck(t_data *data, t_lol lol, const char *ar);
void					z_data_fw(t_data *data, t_lol lol, const char *ar);
void					z_data_hl(t_data *data, t_lol lol, const char *ar);
void					z_06_str1(t_data data, t_cnt *cnt, t_ayy *ayy);
void					z_06_str2(t_data data, t_cnt *cnt, t_ayy *ayy);
void					a10primp(t_ayy ayy, t_data data, t_cnt *cnt,
		const char *ar);
int						pn(long long cnt);
int						pn_u(unsigned long long cnt);
void					f_loat(const char *ar, t_data data, t_cnt *cnt,
		va_list vl);
long double				c_onvert(const char *bnr);
long long				ft_pow(long long x, long long y);
char					*get_bits(char *ptr, size_t size);
char					*ft_sum(char *ar, char *ax);
void					ft_sump(char *ax, char *ar, t_ayy *ayy);
char					*ft_powx(char *x, int y);
char					*ft_multi(char *ar, char *ax);
void					ft_multi0(char *ar, char *ax, t_ayy *ayy);
char					*ft_strev (char *x);
char					*ignor(char *r);
char					*l_exponnt(char *ar, int x, t_lol *lol);
int						ft_printf (const char *f, ...);
void					xxp_0(t_ayy ayy, t_data data, t_cnt *cnt,
		const char *ar);
void					xxp_1(t_ayy ayy, t_data data, t_cnt *cnt,
		const char *ar);
void					xxp_2(t_ayy ayy, t_data data, t_cnt *cnt);
void					xxp_3(t_ayy ayy, t_data data, t_cnt *cnt);
void					xxp_1p(t_ayy ayy, t_data data, t_cnt *cnt,
		const char *ar);
void					xxp2_p(t_ayy ayy, t_data data, t_cnt *cnt);
void					xxp3_p(t_ayy ayy, t_data data, t_cnt *cnt,
		const char *ar);
void					z_06_sp(t_data data, t_cnt *cnt, t_ayy *ayy);
void					diu_0(t_data data, const char *ar, t_cnt *cnt,
		t_ayy *ayy);
void					diu_1(t_data data, t_cnt *cnt, t_ayy *ayy);
void					diu_2(t_data data, t_cnt *cnt, t_ayy *ayy);
void					diu_11(t_data data, const char *ar, t_cnt *cnt,
		t_ayy *ayy);
void					diu_3(t_data data, t_cnt *cnt,
		t_ayy *ayy);
void					o_01(t_ayy ayy, t_data data, t_cnt *cnt,
		const char *ar);
void					o_02(t_ayy ayy, t_data data, t_cnt *cnt);
void					o_03(t_ayy ayy, t_data data, t_cnt *cnt);
int						ft_abs(int x);
void					f_loat0(t_cnt *cnt, t_lol *lol);
void					f_loat2(const char *ar, t_data data, t_cnt *cnt,
		t_lol *lol);
void					f_loat1(t_data data, t_cnt *cnt, t_lol *lol);
void					f_loat3(const char *ar, t_data data, t_cnt *cnt,
		t_lol *lol);
void					f_loat4(const char *ar, t_data data, t_cnt *cnt,
		t_lol *lol);
void					f_loat5(t_data data, t_cnt *cnt, t_lol *lol);
void					f_loat6(const char *ar, t_data data, t_cnt *cnt,
		t_lol *lol);
void					f_loat3p(const char *vf, t_data data, t_cnt *cnt,
		t_lol *lol);
int						f_loat11(t_data data, t_cnt *cnt, t_lol *lol);
void					f_loat00(int a, t_lol *lol, t_cnt *cnt, char *vf);
void					float_p0(const char *ar, t_data data, t_cnt *cnt,
		t_lol *lol);
char					*powx0(char *w, int y, char *x, char *str);
void					f_lags0(t_data data, t_cnt *cnt, va_list vl);
void					f_lags1(t_data data, t_cnt *cnt, va_list vl);
void					print_typs(t_data data, const char *f, t_cnt *cnt,
		va_list vl);
int						trt(t_cnt *cnt, t_lol *lol, const char *f, va_list vl);
void					f_3bita(t_data data, t_cnt *cnt);
int						f_loatp(const char *ar, t_data data,
		t_cnt *cnt, t_lol *lol);
void					flgas(t_data data, t_cnt *cnt);
void					f_4bita(t_data data, t_cnt *cnt);
#endif
