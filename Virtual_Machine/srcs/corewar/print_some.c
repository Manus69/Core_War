#include "corewar.h"

void	print_mem_status(t_arena *vm)
{
	int i;
	int line;
	int space;
	int format;

	i = 0;
	space = 1;
	line = 1;
	format = vm->print_type == 1 ? 64 : 32;
	while (i < MEM_SIZE)
	{
		if (vm->map[i] > 0)
			ft_printf("{red}%02x{eoc} ", vm->map[i]);
		else
			ft_printf("%02x ", vm->map[i]);
		if (line == format)
		{
			ft_printf("\n");
			line = 0;
		}
		space++;
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
void	usage(int	type)
{
	ft_printf("\n|||\nvvv\n{blue}usage: ./corewar [-a] [-d N | -dump N] [-v] <champion1.cor> <...>{eoc} \n");
	ft_printf("\n{red}-a       {green}: prints output from \"aff\" (Default is off){eoc} \n");
	ft_printf("{red}-d N     {green}: Dump memory after {red}N{green} cycles then exists (64 bytes per line){eoc} \n");
	ft_printf("{red}-dump N {green} : Dump memory after {red}N{green} cycles then exists (32 bytes per line){eoc} \n");
	ft_printf("{red}-v       {green}: Visualisation of war in real time.{eoc} \n");
	ft_printf("{red}-s N     {green}: Runs {red}N{green} cycles, dumps memory, paused, then repeats.{eoc} \n");
	ft_printf("{red}-n N     {green}: Assigns next player id-number {red}N{green} (from 1 to 4), if the number is not occupied.{eoc} \n");
	ft_printf("\n:smile_14 You can add another flags, if you wish! \n\n");
	if (type)
		credits();
}