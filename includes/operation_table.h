/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_table.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 19:33:05 by gemerald          #+#    #+#             */
/*   Updated: 2020/06/27 19:34:12 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATION_TABLE_H
# define OPERATION_TABLE_H

# define NUMBER_OF_OPERATIONS 17

enum	e_operation_name
{
	dummy_operation,
	live_operation,
	ld_operation,
	st_operation,
	add_operation,
	sub_operation,
	and_operation,
	or_operation,
	xor_operation,
	zjmp_operation,
	ldi_operation,
	sti_operation,
	fork_operation,
	lld_operation,
	lldi_operation,
	lfork_operation,
	aff_operation,
};

#endif
