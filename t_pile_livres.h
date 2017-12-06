#pragma once

#ifndef _T_PILE__
#define _T_PILE__

#include "structs.h"
#include "t_bibliotheque.h"

void init_pile(t_pile * pile);

int pile_vide(t_pile * pile);

void push(t_pile * pile, t_element_pile element);

t_element_pile pop(t_pile * pile);

void afficher_pile(t_pile * pile);

#endif
