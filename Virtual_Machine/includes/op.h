/*
** Toutes les tailles sont en octets. Все размеры в байтах.
** On part du principe qu'un int fait 32 bits. Est-ce vrai chez vous ? Предполагается, что int имеет 32 бита. Так ли это для вас?
*/

# define IND_SIZE					2
# define REG_SIZE					4 // size of registry in bytes (octets)
# define DIR_SIZE					REG_SIZE


# define REG_CODE					1
# define DIR_CODE					2
# define IND_CODE					3


# define MAX_ARGS_NUMBER			4
# define MAX_PLAYERS				4
# define MEM_SIZE					(4*1024)
# define IDX_MOD					(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE				(MEM_SIZE / 6)

# define COMMENT_CHAR				'#' //comment
# define COMMENT_CHAR_2				';' //alternative comment
# define LABEL_CHAR					':'
# define DIRECT_CHAR				'%'
# define SEPARATOR_CHAR				','

# define LABEL_CHARS				"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING			".name"
# define COMMENT_CMD_STRING			".comment"

# define REG_NUMBER					16 //numbers of registry r1, r2, r3 .. r16

/*
** a) At the beginning all registry`s numbers (accept r1) will be initialise as 0.
** b) First registry (r1)
*/

# define CYCLE_TO_DIE				1536
# define CYCLE_DELTA				50
# define NBR_LIVE					21
# define MAX_CHECKS					10

/*
**
*/

typedef char	t_arg_type;

# define T_REG						1
# define T_DIR						2
# define T_IND						4
# define T_LAB						8

/*
**
*/

# define PROG_NAME_LENGTH			(128) //size of champion`s name
# define COMMENT_LENGTH				(2048)
# define COREWAR_EXEC_MAGIC			0xea83f3

typedef struct		header_s
{
	unsigned int					magic;
	char							prog_name[PROG_NAME_LENGTH + 1];
	unsigned int					prog_size;
	char							comment[COMMENT_LENGTH + 1];
}					header_t;