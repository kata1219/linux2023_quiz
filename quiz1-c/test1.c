#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

struct item
{
    uint16_t i;
    struct list_head list;
};

static inline int cmpint(const void *p1, const void *p2)
{
    const uint16_t *i1 = (const uint16_t *)p1;
    const uint16_t *i2 = (const uint16_t *)p2;
    return *i1 - *i2;
}

// TODO: fix
void swap(struct list_head a, struct list_head b){
    struct list_head tmp = a;
    a.next = b.next;
    a.prev = b.prev;
    b.next = tmp.next;
    b.prev = tmp.prev;
}

static int partition(struct list_head *head, int lo, int hi)
{
    struct item *pivot = list_first_entry(head, struct item, list);

    for (struct list_head *tmp = head->next; tmp != head; tmp = tmp->next)
    {
        struct item *it = list_entry(tmp, struct item, list);
        if (cmpint(&it->i, &pivot->i) < 0)
        {
            swap(pivot->list, it->list);
        }

    }
    
    int i = lo - 1;
    for (int j = lo; j <= hi - 1; j++)
    {
        if (cmpint(&head[j], &pivot) < 0)
        {
            i++;
            swap(&head[i], &head[j]);
        }
    }
    swap(&head[i + 1], &head[hi]);
    return i + 1;

    // if (list_empty(head) || list_is_singular(head))
    //     return;

    // int pos = 0;

    // struct item *itm = NULL, *is = NULL;

    // list_for_each_entry_safe(itm, is, head, list)
    // {
    //     if (cmpint(&itm->i, &pivot->i) < 0)
    //     {
    //         list_move(&itm->list, head);
    //         pos++;
    //     }
    //     else
    //         list_move_tail(&itm->list, head);
    // }

    // list_sort_inplace(head, pos, "left");
    // list_sort_inplace(head, pos, "right");

    // list_add(&pivot->list, head);
    // list_splice(&list_less, head);
    // list_splice_tail(&list_greater, head);

    // return head;
}

static void list_sort_inplace(struct list_head *head, int low, int high)
{
    if (low < high)
    {
        int pivot = partition(head, low, high);
        quick_sort(head, low, pivot - 1);
        quick_sort(head, pivot + 1, high);
    }
}

static void list_sort(struct list_head *head)
{
    if (list_empty(head) || list_is_singular(head))
        return;

    struct list_head list_less, list_greater;
    INIT_LIST_HEAD(&list_less);
    INIT_LIST_HEAD(&list_greater);

    struct item *pivot = list_first_entry(head, struct item, list);
    list_del(&pivot->list);

    struct item *itm = NULL, *is = NULL;

    list_for_each_entry_safe(itm, is, head, list)
    {
        if (cmpint(&itm->i, &pivot->i) < 0)
            list_move_tail(&itm->list, &list_less);
        else
            list_move_tail(&itm->list, &list_greater);
    }

    list_sort(&list_less);
    list_sort(&list_greater);

    list_add(&pivot->list, head);
    list_splice(&list_less, head);
    list_splice_tail(&list_greater, head);
}

void i_new(struct list_head *head, uint16_t i)
{
    struct item *it = malloc(sizeof(struct item));
    it->i = i;
    list_add_tail(&it->list, head);
}

int list_size(struct list_head *head)
{
    int count = 0;
    if (!head)
        return count;
    struct list_head *node;
    list_for_each(node, head)
        count++;

    return count;
}

int main()
{
    LIST_HEAD(head);
    i_new(&head, 3);
    i_new(&head, 5);
    i_new(&head, 2);
    i_new(&head, 4);
    i_new(&head, 1);

    struct item *itm = NULL;

    list_for_each_entry(itm, &head, list)
    {
        printf("%d\n", itm->i);
    }

    // list_sort(&head);
    list_sort_inplace(&head, 0, list_size(&head));

    list_for_each_entry(itm, &head, list)
    {
        printf("%d\n", itm->i);
    }
}