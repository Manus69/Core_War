#include "corewar.h"

void	color_output(int color, uint8_t value, int nice)
{
	if (nice)
	{
		if (color == 0)
			ft_printf("{Lblue}%.2x{eoc} ", value);
		else if (color == 1)
			ft_printf("{cyan}%.2x{eoc} ", value);
		else if (color == 2)
			ft_printf("{yellow}%.2x{eoc} ", value);
		else if (color == 3)
			ft_printf("{purple}%.2x{eoc} ", value);
		else if (color == 4)
			ft_printf("{red}%.2x{eoc} ", value);
	}
	else
		ft_printf("%.2x", value);
}

void		put_color(int *color, int32_t place, t_slider *sl, int32_t s)
{
	int8_t i;
	int32_t addr;

	i = 0;
	while (s)
	{
		addr = find_place(place + s - 1);
		color[addr] = sl->player->number;
		i += 8;
		s--;
	}
}

void	print_mem_status(t_arena *vm)
{
	int i;
	int line;
	int format;

	i = 0;
	line = 1;
	format = vm->print_type == 1 ? 64 : 32;
	while (i < MEM_SIZE)
	{
		if (line == 0 || line == 1)
		{
			if (vm->nice)
				ft_printf("{Lgray}%.4p :{eoc} ", i);
			else
				ft_printf("%.4p :", i);
		}
		color_output(vm->color[i], vm->map[i], vm->nice);
		if (line == format)
		{
			ft_printf("\n");
			line = 0;
		}
		line++;
		i++;
	}
}

void	credits()
{
	ft_printf("*   *   *   *   *   *   *   *   *   *   *   *   *   *    *\n");
	ft_printf("*   __________________________________________________   *");
	ft_printf("\n* {red}     ____         _____      ______     ________   {eoc}    *\n");
	ft_printf("*  {red}  //     \\\\    //     \\\\   ||     \\\\   ||     ||   {eoc}   *\n");
	ft_printf("*  {red} ||           ||       ||  ||     ||   ||___       {eoc}   *\n");
	ft_printf("*  {red} ||           ||       ||  ||_____//   ||___|      {eoc}   *\n");
	ft_printf("*  {red} ||           ||       ||  ||   \\\\     ||        {eoc}     *\n");
	ft_printf("*  {red}  \\\\_____//    \\\\ ___ //   |_|    \\_\\  ||_____||   {eoc}   *\n");
	ft_printf("*   --------------------------------------------------   *\n");
	ft_printf("*   __________________________________________________   *\n");
	ft_printf("* {red}  __        ___      ______     _____       {eoc}           *\n");
	ft_printf("* {red}  ||         ||    //     ||  ||     \\\\ {eoc} written by:   *\n");
	ft_printf("* {red}  ||         ||   ||      ||  ||     || {eoc}  -> {green}gemerald{eoc}  *\n");
	ft_printf("*  {red} ||         ||   ||______||  ||_____//  {eoc} -> {green}lcaesar{eoc}   *\n");
	ft_printf("*  {red} ||    ||   ||   ||      ||  ||     \\\\ {eoc}  -> {green}mnarwhal{eoc}  *\n");
	ft_printf("*  {red}  \\\\__//\\\\__//   ||      ||  |_|     \\_\\{eoc} -> {green}selly{eoc}     *\n");
	ft_printf("*   --------------------------------------------------   *\n");
	ft_printf("*         {cyan}Enjoy the biggest battle in your life!{eoc}         *\n");
	ft_printf("*  {cyan}<<<<<<****   CREATE YOUR CHAMPION!    ****>>>>>>>>{eoc}    *\n");
	ft_printf("*   *   *   *   *   *   *   *   *   *   *   *   *   *    *\n\n");
}

void	usage(int	type, int nice)
{
	if (nice)
	{
		ft_printf("\n|||\nvvv\n{blue}usage: ./corewar [-a] [-d N | -dump N] [-v] <champion1.cor> <...>{eoc} \n");
		ft_printf("\n{red}-a       {green}: prints output from \"aff\" (Default is off){eoc} \n");
		ft_printf("{red}-d N     {green}: Dump memory after {red}N{green} cycles then exists (64 bytes per line){eoc} \n");
		ft_printf("{red}-dump N {green} : Dump memory after {red}N{green} cycles then exists (32 bytes per line){eoc} \n");
		ft_printf("{red}-v       {green}: Visualisation of war in real time.{eoc} \n");
		ft_printf("{red}-s N     {green}: Runs {red}N{green} cycles, dumps memory, paused, then repeats.{eoc} \n");
		ft_printf("{red}-n N     {green}: Assigns next player id-number {red}N{green} (from 1 to 4), if the number is not occupied.{eoc} \n");
		if (type)
			credits();
	}
	else
		{
		ft_printf("\nusage: ./corewar [-a] [-d N | -dump N] [-v] <champion1.cor> <...> \n");
		ft_printf("\n-a: prints output from \"aff\" (Default is off)\n");
		ft_printf("-d N: Dump memory after N cycles then exists (64 bytes per line)\n");
		ft_printf("-dump N: Dump memory after N cycles then exists (32 bytes per line)\n");
		ft_printf("-v: Visualisation of war in real time.\n");
		ft_printf("-s N: Runs N cycles, dumps memory, paused, then repeats.\n");
		ft_printf("-n N: Assigns next player id-number N (from 1 to 4), if the number is not occupied.\n");
		}
}