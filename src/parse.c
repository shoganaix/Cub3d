


#include "cub3d.h"

t_bool check_fmt_extension(const char *file_name, char *extension_no_dot)
{
    char    *ext_w_dot;
    int     diff;
    
    ext_w_dot = ft_strjoin(".", extension_no_dot);
    diff = ft_strncmp(ft_strrchr(file_name, '.'), extension_no_dot, ft_strlen(ext_w_dot) + 1);
    return (diff == 0);
}

t_bool check_args(int argn, char *args[])
{
    if (argn != 2)
        return FALSE;
    if (!check_fmt_extension(args[1], ".cub"))
        return FALSE;
    return TRUE;
}

