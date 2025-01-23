
#include "../src/cub3d.h"
#include "assert.h"

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
	printf("check_texture - end w/spaces passed 🌱\n");
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

}