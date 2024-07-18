/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:06:01 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/05/21 15:17:27 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdbool.h>

/* Test ajouté pour validation avec github.com/Tripouille/libftTester
 * renvoie NULL (avant d'appeler malloc) si:
 * 	(1) (ancien test retiré) nmemb < 0 ou size < 0 (interprétés en signed) sauf
 * si l'un des deux vaut zero (et donc totalsize = 0). Voir code ci-dessous:
 * if (((ssize_t)nmemb < 0 || (ssize_t)size < 0) && (ssize_t)totalsize != 0)
 *		return (NULL);
 * 	(2) overflow sur calcul totalsize (voir code actuel)
 * NB: malloc sera appelé si totalsize = 0.
*/
void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	totalsize;
	void	*mem;
	bool	overflow;

	totalsize = nmemb * size;
	overflow = (nmemb != 0 && totalsize / nmemb != size);
	if (overflow)
		return (NULL);
	mem = malloc(totalsize);
	if (mem == NULL)
		return (NULL);
	ft_bzero(mem, totalsize);
	return (mem);
}
