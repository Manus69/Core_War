/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 19:21:21 by gemerald          #+#    #+#             */
/*   Updated: 2020/07/03 17:57:08 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

# include "op.h"

# define GENERIC_ERROR_MESSAGE "Error!\n"
# define FILE_ERROR_MESSAGE "Could not open the file;\n"
# define CLASSIFICATION_ERROR_MESSAGE "Could not classify token:\n"
# define UNEXPECTED_ERROR "Something is wrong;\n"
# define COMPILATION_TERMINATED "Compilation terminated;\n"
# define OPEN_CREATE_FAILURE "Open / create failure;\n"
# define BUFFER_OVERFLOW "Buffer overflow;\n"
# define DIGITS "0123456789"
# define NUMBER_SYSTEM_BASE 16
# define NUMBER_OF_OPERATIONS 17
# define PADDING_SIZE 4
# define BUFFER_SIZE (COMMENT_LENGTH << 1)
# define REGISTRY_NAME_SIZE T_REG
# define REGISTRY_SIZE REG_SIZE
# define DIRECT_VALUE_SIZE REGISTRY_SIZE
# define DIRECT_ADDRESS_SIZE IND_SIZE
# define INDIRECT_VALUE_SIZE IND_SIZE

#endif
