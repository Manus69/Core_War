/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_some_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 23:43:06 by selly             #+#    #+#             */
/*   Updated: 2020/06/06 23:48:48 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			credits(void)
{
	ft_putstr("*   *   *   *   *   *   *   *   *   *   *   *   *   *    *\n");
	ft_putstr("*   __________________________________________________   *");
	ft_printf("\n* {red}     ____         _____      ______     _____");
	ft_printf("___   {eoc}    *\n*  {red}  //     \\\\    //     \\\\");
	ft_printf("   ||     \\\\   ||     ||   {eoc}   *\n*  {red} ||    ");
	ft_printf("       ||       ||  ||     ||   ||___       {eoc}   *\n");
	ft_printf("*  {red} ||           ||       ||  ||_____//   ||___|  ");
	ft_printf("    {eoc}   *\n*  {red} ||           ||       ||  ||");
	ft_printf("   \\\\     ||        {eoc}     *\n*  {red}  \\\\_____//  ");
	ft_printf("  \\\\ ___ //   |_|    \\_\\  ||_____||   {eoc}   *\n");
	ft_printf("*   --------------------------------------------------   *\n");
	ft_printf("*   __________________________________________________   *\n");
	ft_printf("* {red}  __        ___      ______     _____       {eoc}  ");
	ft_printf("         *\n* {red}  ||         ||    //     ||  ||    ");
	ft_printf(" \\\\ {eoc} written by:   *\n* {red}  ||         ||   ||   ");
	ft_printf("   ||  ||     || {eoc}  -> {green}gemerald{eoc}  *\n");
	ft_printf("*  {red} ||         ||   ||______||  ||_____//  {eoc} -> ");
	ft_printf("{green}lcaesar{eoc}   *\n*  {red} ||    ||  ||   ||      || ");
	ft_printf(" ||      \\\\ {eoc}  -> {green}mnarwhal{eoc}  *\n");
	ft_printf("*  {red}  \\\\__//\\\\__//   ||      ||  |_|     \\_\\{eoc} ");
	ft_printf("-> {green}selly{eoc}     *\n*   ---------------------------");
	ft_printf("-----------------------   *\n         {cyan}Enjoy the biggest");
	ft_printf("* battle in your life!{eoc}         *\n*  {cyan}<<<<<<****   ");
	ft_printf("CREATE YOUR CHAMPION!    ****>>>>>>>>{eoc}    *\n*   *   * ");
	ft_putstr("  *   *   *   *   *   *   *   *   *   *   *    *\n\n");
}

void			nice_usage(void)
{
	ft_putstr("\n|||\nvvv\n\e[34musage: ./corewar [-a] [-d N | -dump ");
	ft_putstr("N] [-v] <champion1.cor> <...>\e[0m \n\n\e[31m-a        ");
	ft_putstr("\e[32m: Prints output from \"aff\" (Default is off)\e[0m");
	ft_putstr(" \n\e[31m-d N      \e[32m: Dump memory after \e[31mN\e[32m");
	ft_putstr(" cycles then exists (64 bytes per line)\e[0m \n\e[31m");
	ft_putstr("-dump: N \e[32m : Dump memory after \e[31mN\e[32m cycles then ");
	ft_putstr("exists (32 bytes per line)\e[0m \n\e[31m-v        \e[32m: ");
	ft_putstr("Visualisation of war in real time\e[0m \n\e[31m-s N      ");
	ft_putstr("\e[32m: Runs \e[31mN\e[32m cycles, dumps memory, paused, ");
	ft_putstr("then repeats\e[0m \n\e[31m-n N      \e[32m: Assigns next");
	ft_putstr(" player id-num \e[31mN\e[32m (from 1 to 4), ");
	ft_putstr("if the num is not occupied\e[0m \n");
}

void			usage(int type, int nice)
{
	if (nice)
		nice_usage();
	else
	{
		ft_putstr("\nusage: ./corewar [-a] [-d N | -dump N] [-v] <champion1.");
		ft_putstr("cor> <...> \n\n-a      : Prints output from \"aff\" ");
		ft_putstr("(Default is off)\n-d N    : Dump memory after ");
		ft_putstr("N cycles then exists (64 bytes per line)\n-dump N : ");
		ft_putstr("Dump memory after N cycles then exists (32 bytes per line)");
		ft_putstr("\n-v      : Visualisation of war in real time\n-s N    :");
		ft_putstr(" Runs N cycles, dumps memory, paused, then repeats\n-n N");
		ft_putstr("    : Assigns next player id-num N (from 1 to 4), if");
		ft_putstr(" the num is not occupied\n");
	}
	if (type)
		credits();
}

void			print_nice_face(int i)
{
	if (i + 1 == 1)
		ft_printf("{red}* :smile_1  ");
	else if (i + 1 == 2)
		ft_printf("{red}* :smile_7  ");
	else if (i + 1 == 3)
		ft_printf("{red}* :smile_5  ");
	else if (i + 1 == 4)
		ft_printf("{red}* :smile_8  ");
}

void			inroduction(t_champ *ch[4], int count, int nice, int i)
{
	if (nice)
		ft_printf("{green}Introducing contestants...{eoc}\n");
	else
		ft_printf("Introducing contestants...\n");
	while (i < count)
	{
		if (nice)
		{
			print_nice_face(i);
			ft_printf("Player %d: ", ch[i]->num);
			ft_printf("{blue}weighing %d bytes,{eoc} ", ch[i]->size);
			ft_printf("{blue}\"%s\"{eoc} ", ch[i]->name);
			ft_printf("{blue} (\"%s\")!{eoc} \n", ch[i]->comment);
		}
		else
		{
			ft_printf("* Player %d: weighing %d by", ch[i]->num, ch[i]->size);
			ft_printf("tes, \"%s\" (\"%s\")!\n", ch[i]->name, ch[i]->comment);
		}
		i++;
	}
}
