#ifndef LINKEDLIST_H
#define LINKEDLIST_H

struct List {
    int value;
    struct List* next;
};

typedef struct List List;

int length(List *list) {
    if (list == NULL) {
        return 0;
    }
    return(length(list->next) + 1);
}

List* tail(List *list) {
    if (list == NULL) {
        return(NULL);
    }
    if (list->next == NULL) {
        return(list);
    }
    return(tail(list->next));
}

List* second_to_last(List *list) {
    if (list == NULL) {
        return(NULL);
    }
    if (list->next == NULL) {
        return(NULL);
    }
    if (list->next->next == NULL) {
        return(list);
    }
    return(second_to_last(list->next));
}

List* element(List *list, unsigned int index) {
    if (list == NULL) {
        return(NULL);
    }
    if (index == 0) {
        return(list);
    }
    return(element(list->next, index - 1));
}

int* peek(List *list, unsigned int index) {
    List *active_element = element(list, index);
    if (active_element == NULL) {
        return(NULL);
    }
    return(&active_element->value);
}

void poke(List *list, unsigned int index, int value) {
    List *active_element = element(list, index);
    if (active_element != NULL) {
        active_element->value = value;
    }
}

List* prepend(List *list, int value, Arena *arena) {
    List *head = (List*) arenaAllocate(arena, sizeof(List));
    assert(head != NULL);
    head->value = value;
    head->next = list;
    return(head);
}

List* append(List *list, int value, Arena *arena) {
    List *new_tail = (List*) arenaAllocate(arena, sizeof(List));
    assert(new_tail != NULL);
    new_tail->value = value;
    new_tail->next = NULL;
    if (list == NULL) {
        list = new_tail;
    } else {
        List *old_tail = tail(list);
        old_tail->next = new_tail;
    }   
    return(list);
}

List* insert(List *list, unsigned int index, int value, Arena *arena) {
    List *active_element = element(list, index);
    assert(active_element != NULL);
    List *insertion = (List*) arenaAllocate(arena, sizeof(List));
    assert(insertion != NULL);
    insertion->value = value;
    insertion->next = active_element->next;
    active_element->next = insertion;
    return(list);
}

List* pretach(List *list) {
    if (list == NULL) {
        return(NULL);
    }
    return(list->next);
}

List* detach(List *list) {
    List *pre_tail = second_to_last(list);
    if (pre_tail == NULL) {
        return(NULL);
    }
    pre_tail->next = NULL;
    return(list);
}

List* delete(List *list, unsigned int index) {
    if (index == 0) {
        return(pretach(list));
    }
    List* active_element = element(list, index - 1);
    assert(active_element != NULL);
    assert(active_element->next != NULL);
    active_element->next = active_element->next->next;
    return(list);
}

#endif