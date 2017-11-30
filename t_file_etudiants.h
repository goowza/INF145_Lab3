#pragma once

#ifndef _T_FILE_ETUDIANTS__
#define _T_FILE_ETUDIANTS__

#include "structs.h"

void init_file(t_file * file);

int file_vide(const t_file * file);

void ajout_debut(t_file * file, t_element_file element);

void enfiler(t_file * file, t_element_file element);

t_element_file desenfiler(t_file * file);

void afficher_file(t_file * file);

#endif
