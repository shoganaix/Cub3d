
#include "../src/cub3d.h"
#include "assert.h"


/*****************  texture ********************** */
void test_read_texture_line_notok()
{
	char *line = "ENO  ./path-to-no";

	t_info info;
	t_bool b = check_texture(line, &info, "NO", NO);
	assert(b == FALSE);
	printf("check_texture - notok input passed 🌱\n");
}

void test_read_texture_line_ok()
{
	char *line = "NO  ./path-to-no";

	t_info info;
	ft_bzero(&info, sizeof(info));
	t_bool b = check_texture(line, &info, "NO", NO);
	assert(b == TRUE);
	assert(info.textures[NO] != NULL);
	assert(ft_strcmp(info.textures[NO], "./path-to-no") == 0);
	printf("check_texture - ok input passed 🌱\n");
}

// no spaces allowed at the start
void test_read_texture_line_sp_begin()
{
	char *line = "  NO  ./path-to-no";

	t_info info;
	ft_bzero(&info, sizeof(info));
	t_bool b = check_texture(line, &info, "NO", NO);
	assert(b == FALSE);
	assert(info.textures[NO] == NULL);
	printf("check_texture - start w/spaces passed 🌱\n");
}

// no spaces allowed at the end
void test_read_texture_line_sp_end()
{
	char *line = "NO ./path-to-no ";

	t_info info;
	ft_bzero(&info, sizeof(info));
	t_bool b = check_texture(line, &info, "NO", NO);
	assert(b == FALSE);
	printf("check_texture - end w/spaces at the end passed 🌱\n");
}

// textures consist of 2 words only
void test_read_texture_line_more_words()
{
	char *line = "NO  ./path-to-no e";

	t_info info;
	ft_bzero(&info, sizeof(info));
	t_bool b = check_texture(line, &info, "NO", NO);
	assert(b == FALSE);
	printf("check_texture - more than 2 words passed 🌱\n");
}
// already filled that texture
void test_read_texture_line_filled()
{
	char *line = "NO  ./path-to-no";

	t_info info;
	ft_bzero(&info, sizeof(info));
	info.textures[NO] = "filled-already";
	t_bool b = check_texture(line, &info, "NO", NO);
	assert(b == FALSE);
	printf("check_texture - already filled passed 🌱\n");
}


/********************* next_word *************** */
void test_next_word_f()
{
	char *line = "NO  ./path-to-no";

	char *f;
	int i = 0;
	f = next_word(line, &i);
	assert(ft_strcmp(f, "NO") == 0);
	assert(i == 2);
	assert(ft_strcmp(&line[i], "  ./path-to-no") == 0);
	printf("next_word - first word passed 🌱\n");
}

void test_next_word_l()
{
	char *line = "NO  ./path-to-no";

	char *w;
	int i = 4;
	w = next_word(&line[i], &i);
	assert(ft_strcmp(w, "./path-to-no") == 0);
	assert(i == 16);
	printf("next_word - word at the end passed 🌱\n");
}

/*************** check_color ************* */

void test_check_color_ok()
{
	char *line = "C 125,127,124";
	t_info info;
	init_info(&info);

	t_bool b = check_color(line, &info, "C");
	assert(b == TRUE);
	assert(info.ceiling.r == 125);
	assert(info.ceiling.g == 127);
	assert(info.ceiling.b == 124);

	printf("check_color - ok input passed 🌱\n");
}

void test_check_color_sp()
{
	char *line = "C    125,127,124";
	t_info info;
	init_info(&info);

	t_bool b = check_color(line, &info, "C");
	assert(b == TRUE);
	assert(info.ceiling.r == 125);
	assert(info.ceiling.g == 127);
	assert(info.ceiling.b == 124);

	printf("check_color - ok input w/spaces in betw passed 🌱\n");
}

void test_check_color_wrong()
{
	char *line = "D 125,127,124";
	t_info info;
	init_info(&info);

	t_bool b = check_color(line, &info, "C");
	assert(b == FALSE);
	assert(info.ceiling.r == -1);

	printf("check_color - wrong input passed 🌱\n");
}

void test_check_color_more_colors()
{
	char *line = "C 125,127,124,3";
	t_info info;
	init_info(&info);

	t_bool b = check_color(line, &info, "C");
	assert(b == FALSE);

	printf("check_color - more colors passed 🌱\n");
}

void test_check_color_no_comma()
{
	char *line = "C 125-23-3";
	t_info info;
	init_info(&info);

	t_bool b = check_color(line, &info, "C");
	assert(b == FALSE);

	printf("check_color - no commas passed 🌱\n");
}
void test_check_color_chars_in_color()
{
	char *line = "C 12f,34r,t";
	t_info info;
	init_info(&info);

	t_bool b = check_color(line, &info, "C");
	assert(b == FALSE);

	printf("check_color - chars in color passed 🌱\n");
}
// nl at the end -> fail
void test_check_color_nl()
{
	char *line = "C    125,127,124\n";
	t_info info;
	init_info(&info);

	t_bool b = check_color(line, &info, "C");
	assert(b == FALSE);

	printf("check_color - ok input w/nl at the end passed 🌱\n");
}


/********** check_map ******** */
void test_check_map_ok_input()
{
	char *file = "maps/map1.cub";
	t_info info;

	t_bool b = check_map(file, &info);
	assert(b == TRUE);
	assert(info.textures[NO] != NULL);
	assert(info.textures[SO] != NULL);
	assert(info.textures[WE] != NULL);
	assert(info.textures[EA] != NULL);
	assert(ft_strcmp(info.textures[NO], "./path_to_the_north_texture") == 0);
	assert(ft_strcmp(info.textures[SO], "./path_to_the_south_texture") == 0);
	assert(ft_strcmp(info.textures[WE], "./path_to_the_west_texture") == 0);
	assert(ft_strcmp(info.textures[EA], "./path_to_the_east_texture") == 0);
	assert(info.floor.r == 220);
	assert(info.floor.g == 100);
	assert(info.floor.b == 0);
	assert(info.ceiling.r == 225);
	assert(info.ceiling.g == 30);
	assert(info.ceiling.b == 0);
	destroy_info(&info);
	printf("check_map - info ok passed 🌱\n");
}

void test_check_map_random()
{
	char *file = "test/map_info_t1";
	// char *file = "maps/map1.cub";
	t_info info;

	t_bool b = check_map(file, &info);
	printf("Check map FILE:'%s'. Result: %i\n", file, b);
	show_info(info);
	
}

int main()
{
	test_next_word_f();
	test_next_word_l();


	test_read_texture_line_ok();
	test_read_texture_line_sp_begin();
	test_read_texture_line_more_words();
	test_read_texture_line_sp_end();
	test_read_texture_line_notok();
	test_read_texture_line_filled();

	test_check_color_ok();
	test_check_color_sp();
	test_check_color_wrong();
	test_check_color_more_colors();
	test_check_color_no_comma();
	test_check_color_chars_in_color();
	test_check_color_nl();

	test_check_map_ok_input();
	test_check_map_random();
}