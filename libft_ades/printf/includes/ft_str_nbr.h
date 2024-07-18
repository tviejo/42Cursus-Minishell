/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_nbr.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 20:39:05 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/03/08 20:39:08 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STR_NBR_H
# define FT_STR_NBR_H

# include "../../base/libft.h"
# include <stdint.h>
# include <stdbool.h>
# include <stdarg.h>

# define PRINTF_ARG_BUFFER_SIZE 512
# define FTOA_NB_DIGIT_DEFAULT 6

typedef unsigned int	t_uint;
typedef unsigned long	t_ulong;

/*
typedef struct s_format_id
{
	int		type;			// 'c', 's', 'i', 'u', ...
	//int		size;		// 8, 16, 32 or 64-bit: byte, short, int or int64_t
							// (%hhi, %hi, %i, %li or %lli)
	bool	left_justify;	// flag '-'
	bool	zero_padded;	// flag '0'
	bool	prn_pos_sign;	// flag '+'
	bool	space_pos_val;	// flag ' '
	bool	sharp_flag;		// flag '#'
	int		min_width;
	union					// "flag" '.'
	{
		int	max_width;
		int	precision;
	};
	int		base;			// "flag" 'B'
}	t_format_id;

// Format d'affichage pour int2str_ex(), long2str_ex() et ulong2str_ex()
//
typedef struct s_i2s_fmt
{
	uint64_t	nbr;		// (à usage interne) (pour prefix 0x si non nul)
	bool		isnegative;	// (à usage interne)
	int			nbdigits;	// (à usage interne)
	t_uint		base;		// base numérique
	bool		capitdgt;	// afficher les chiffres (>9) en majuscules
	int			minlen;		// longueur minimale d'écriture
	bool		leftjust;	// justification à gauche ?
	bool		signljust;	// le signe est il justifié à gauche ?
	int			sepfreq;	// ajouter <sepchar> tous les <sepfreq> chiffres
	bool		seppad;		// le padding est il traité comme des chiffres ?
	char		*strneg;	// chaine à afficher si négatif ("-" si NULL)
	char		*strpos;	// chaine à afficher si positif (rien si NULL)
	char		*prefix;	// préfixe (entre le signe et le premier chiffre)
	char		padchar;	// caractère de padding pour arriver à minlen
	char		sepchar;	// caractère séparateur des groupes de chiffres
}	t_i2s_fmt;
*/

/* Format d'affichage de ft_printf()
*/
typedef struct s_format_id
{
	int		type;
	bool	left_justify;
	bool	zero_padded;
	bool	prn_pos_sign;
	bool	space_pos_val;
	bool	sharp_flag;
	int		min_width;
	union
	{
		int	max_width;
		int	precision;
	};
	int		base;
}	t_format_id;

/* Format d'affichage pour int2str_ex(), long2str_ex() et ulong2str_ex()
*/
typedef struct s_i2s_fmt
{
	uint64_t	nbr;
	bool		isnegative;
	int			nbdigits;
	t_uint		base;
	bool		capitdgt;
	int			minlen;
	int			printf_precision;
	int			precision_nbpad;
	bool		leftjust;
	bool		signljust;
	int			sepfreq;
	bool		seppad;
	char		*strneg;
	char		*strpos;
	char		*prefix;
	char		padchar;
	char		sepchar;
}	t_i2s_fmt;

void		ft_putchar(char c);
void		ft_putstr(char *str, bool lineret);
void		ft_puterrmsg(char *str);

int			ft_printf(const char *format, ...);
int			ft_vprintf(const char *format, va_list args);
int			ft_sprintf(char *buffer, const char *format, ...);
int			ft_vsprintf(char *buffer, const char *format, va_list args);
void		test_ft_printf(void);
// private func:

int			print(char *str);
int			print_s(char *str, t_format_id *fid);
int			print_cap_f(va_list args, char *sbuf);
int			print_f(double nbr, t_format_id *fid, char *sbuf);
char		*sprint_f(double nbr, t_format_id *fid, char *sbuf);
int			print_p(uint64_t ptr64, t_format_id *fid, t_i2s_fmt *fmt,
				char *sbuf);
char		*sprint_p(uint64_t ptr64, t_format_id *fid, t_i2s_fmt *fmt,
				char *sbuf);
char		*sprint_s(char *str, t_format_id *fid, char *buffer);
char		*sprint_c(int c, t_format_id *fid, char *buffer);
const char	*parse_format_id(const char *format, t_format_id *fid);
t_i2s_fmt	*get_i2s_fmt(t_format_id *fid, t_i2s_fmt *fmt);

//void		ft_putnbr(int nbr);

// 's2i' conversion func : string to integer

int			ft_atoi(const char *str);
int			str2int(const char *str, int base, char **pend);

// *** 'i2s' conversion func : integer to string ***

// 'i2s' helper func to setup t_i2s_fmt format:

void		i2sfmt_set(t_i2s_fmt *fmt, int base_capit_keep,
				int len_min_pad_just, int sep_freq_char_pad);
int			i2sfmt_setstr(t_i2s_fmt *fmt, char *strneg,
				char *strpos, char *prefix);
int			i2s_base(int base, bool capitdgt, bool keepstr);
int			i2s_len(int minlen, char padchar);
int			i2s_len_j(int minlen, char padchar, bool leftjust, bool signljust);
int			i2s_sep(int sepfreq, char sepchar, bool seppad);

// 'i2s' conversion functions:

char		*int2str(int nbr, int base, int minlen, char *buf);
char		*int2str_ex(int nbr, int d, t_i2s_fmt *fmt, char *buf);
char		*ft_itoa(int nbr, int base, int minlen, char *buf);
char		*ft_itoa_ex(int nbr, t_i2s_fmt *fmt, char *buf);
char		*long2str(long nbr, int base, int minlen, char *buf);
char		*long2str_ex(long nbr, int d, t_i2s_fmt *fmt, char *buf);
char		*ft_ltoa(long nbr, int base, int minlen, char *buf);
char		*ft_ltoa_ex(long nbr, t_i2s_fmt *fmt, char *buf);
char		*ulong2str_ex(uint64_t unbr, int d, t_i2s_fmt *fmt, char *buf);
char		*ulong2str(uint64_t nbr, int base, int minlen, char *buf);
char		*ft_ultoa(uint64_t nbr, int base, int minlen, char *buf);
char		*ft_ultoa_ex(uint64_t nbr, t_i2s_fmt *fmt, char *buf);
char		*uint2str(t_uint nbr, int base, int minlen, char *buf);
char		*uint2str_ex(t_uint unbr, int d, t_i2s_fmt *fmt, char *buf);
char		*ft_utoa(t_uint nbr, int base, int minlen, char *buf);
char		*ft_utoa_ex(t_uint nbr, t_i2s_fmt *fmt, char *buf);
// private func:

void		i2s_print_sign(t_i2s_fmt *fmt, char **buf);
char		*i2s_padding(t_i2s_fmt *fmt, char *buf);
char		*i2s_precision_padding(t_i2s_fmt *fmt, char *buf);
void		i2s_first_digit_reached(t_i2s_fmt *fmt, int nbdigits);
char		get_asciidigit(int digit, bool majuscule);
void		write_digit(int digit, t_i2s_fmt *fmt, char **buffer);
char		*get_i2s_prefix(t_format_id *fid, t_i2s_fmt *fmt);

// 'f2s' floating point conversion functions:

char		*double2str(double nbr, int base, int nbdigits, char *buf);
char		*ft_ftoa(double nbr, int base, int nbdigits, char *buf);
// private func:

char		*dblspecialvals(double nbr, char *buf);
char		*dblraw2str(double nbr, char *buf);

// string processing functions:

//int			ft_strlen(const char *str);
t_uint		ft_strcpylen(char *dest, const char *src);
//t_uint		ft_strlcpy(char *dest, const char *src, unsigned int size);
t_uint		ft_strlencpy(char *dest, const char *src, unsigned int size);
char		*ft_strncpy(char *dest, const char *src, unsigned int n);
int			ft_strcmp(const char *s1, const char *s2);
//int			ft_strncmp(const char *s1, const char *s2, unsigned int n);
char		*ft_strchr(const char *s, int c);
char		*ft_strstr(const char *str, const char *to_find);

#endif