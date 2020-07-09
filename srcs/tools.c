/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 09:56:07 by armajchr          #+#    #+#             */
/*   Updated: 2020/07/09 16:33:58 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/asm.h"

void    instruction_to_hexa(t_head *head)
{
    t_code      *tmp;

    tmp = head->op_code;
    while (tmp)
    {
        if (ft_strcmp(tmp->op, "live") == 0)
            tmp->hexa_arg[0] = "01\0";
        else if (ft_strcmp(tmp->op, "ld") == 0)
            tmp->hexa_arg[0] = "02\0";
        else if (ft_strcmp(tmp->op, "st") == 0)
            tmp->hexa_arg[0] = "03\0";
        else if (ft_strcmp(tmp->op, "add") == 0)
            tmp->hexa_arg[0] = "04\0";
        else if (ft_strcmp(tmp->op, "sub") == 0)
            tmp->hexa_arg[0] = "05\0";
        else if (ft_strcmp(tmp->op, "and") == 0)
            tmp->hexa_arg[0] = "06\0";
        else if (ft_strcmp(tmp->op, "or") == 0)
            tmp->hexa_arg[0] = "07\0";
        else if (ft_strcmp(tmp->op, "xor") == 0)
            tmp->hexa_arg[0] = "08\0";
        else if (ft_strcmp(tmp->op, "zjmp") == 0)
            tmp->hexa_arg[0] = "09\0";
        else if (ft_strcmp(tmp->op, "ldi") == 0)
            tmp->hexa_arg[0] = "0a\0";
        else if (ft_strcmp(tmp->op, "sti") == 0)
            tmp->hexa_arg[0] = "0b\0";
        else if (ft_strcmp(tmp->op, "fork") == 0)
            tmp->hexa_arg[0] = "0c\0";
        else if (ft_strcmp(tmp->op, "lld") == 0)
            tmp->hexa_arg[0] = "0d\0";
        else if (ft_strcmp(tmp->op, "lldi") == 0)
            tmp->hexa_arg[0] = "0e\0";
        else if (ft_strcmp(tmp->op, "lfork") == 0)
            tmp->hexa_arg[0] = "0f\0";
        else if (ft_strcmp(tmp->op, "aff") == 0)
            tmp->hexa_arg[0] = "10\0";
        tmp = tmp->next;
    }
}

char      *padding(char *s, int size)
{
    int i;
    int len;
    char    *dst;

    len = ft_strlen(s);
    i = 0;
    if (!(dst = (char*)malloc(sizeof(char) * 12)))
        return NULL;
    if ( size > 12)
        return (s);
    while (i < (size - len))
    {
        if (i % 3 == 2)
            dst[i] = ' ';
        else
            dst[i] = '0';
        i++;
    }
    dst[i] = '\0';
    dst = ft_strcat(dst, s);
    ft_memdel((void**)&s);
    return (dst);
}

t_code    *create_nod(t_head *head, t_code *tmp)
{
    if (tmp == NULL)
    {
        if (!(head->op_code = ft_create_elem()))
		    return NULL;
        tmp = head->op_code;
    }
    else
    {
        while (tmp->next)
            tmp = tmp->next;
        if (!(tmp->next = ft_create_elem()))
		    return NULL;
        tmp = tmp->next;
    }
    return (tmp);
}

void    print_op_code(t_head *head)
{
    t_code *tmp;
    int i;

    tmp = head->op_code;
    ft_printf(YELLOW"--------WARRIOR ID--------\n");
    ft_printf("NAME:%s\n", head->name);
    ft_printf("Comment:%s\n"EOC, head->comment);
    ft_printf(RED"Magic_Number:%p\n"EOC, head->magic);

    while (tmp)
    {
        ft_printf(YELLOW"label = %s\n"EOC, tmp->label);
        ft_printf(PURPLE"op = %s\n"EOC, tmp->op);
        i = 0;
        while (tmp->arg[i])
        {
            printf(CYAN"arg[%d] = %s\n"EOC, i, tmp->arg[i]);
            i++;
        }
        i = 0;
        while (tmp->hexa_arg[i])
        {
            ft_printf(GREEN"Hexa[%d] = %s\n"EOC, i, tmp->hexa_arg[i]);
            i++;
        }
        ft_printf(BLUE"len = %d\n"EOC, tmp->len);
        ft_printf(RED"position = %d\n"EOC, tmp->position);
        tmp = tmp->next;
    }
}