#include "libft.h"
#include "libft_bonus.h"

int ft_lstsize(t_list *lst)
{
    int     cnt;
    t_list  *ptr;

    cnt = 0;
    ptr = lst;
    while (ptr)
    {
        ptr = ptr->next;
        cnt++;
    }
    return (cnt);
}