/**
 * @file parser.c
 * @author Jakub Kopiszka (kopiszkajakub20@gmail.com)
 * @brief This file is an implementation for all
 * @version 0.1
 * @date 2026-06-19
 *
 * @copyright Copyright (c) 2026
 */

//! INCLUDES !//
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/parser.h"

//! DEFINES !//
#define BUFFER_SIZE 64

//! FUNCTIONS !//
INIFile *ini_load(const char *path)
{
    /**
     * @brief
     *
     */

    //* FILE OPENING *//
    FILE *inif;
    inif = fopen(path, "r");
    if (!inif)
    {
        printf("%s", "ERROR! Couldn't load INI file.");
        return NULL;
    }

    //* Returning file's content as chars array *//
    char *file_content = load_ini_to_string(inif);
    fclose(inif);

    //* Returning INI's sections *//
    INISection **sections = get_sections(file_content);

    for (int i = 0; sections[i] != NULL; i++)
    {
        printf("Section: %s\n", sections[i]->name);

        free(sections[i]);
    }

    free(sections);

    return NULL;
}

char *load_ini_to_string(FILE *file)
{
    char buffer[BUFFER_SIZE];
    char *file_content = NULL;
    size_t size = 0;

    while (fgets(buffer, BUFFER_SIZE, file))
    {
        if (buffer[0] == ';' || buffer[0] == '#' || buffer[0] == '\n' || buffer[0] == '\r')
        {
            continue;
        }

        size_t ini_chunk = strlen(buffer);
        char *new_file_content = realloc(file_content, size + ini_chunk + 1);

        if (!new_file_content)
        {
            free(file_content);
            return NULL;
        }

        file_content = new_file_content;
        memcpy(file_content + size, buffer, ini_chunk);
        size += ini_chunk;
        file_content[size] = '\0';
    }

    return file_content;
}

INISection **get_sections(char *file_content)
{
<<<<<<< HEAD
    //* DEFINITION OF EMPTY ARRAY OF INISections ARRAYS *//
    INISection **sections = NULL;
=======
    char **sections = NULL;
>>>>>>> parent of 3a8f8e7 (comments)
    int section_counter = 0;

    while (*file_content)
    {
        if (*file_content == '[')
        {
            char *start = file_content + 1;

            while (*file_content && *file_content != ']')
                file_content++;

            if (*file_content == ']')
            {
                size_t name_len = file_content - start;

                char *section_name = malloc(name_len + 1);
                memcpy(section_name, start, name_len);
                section_name[name_len] = '\0';

<<<<<<< HEAD
                INISection *new_section = malloc(sizeof(INISection));
                new_section->name = section_name;

                // Appending array of section names
                INISection **tmp =
                    realloc(sections, sizeof(INISection *) * (section_counter + 1));
                if (!tmp)
                {
                    free(section_name);
                    free(new_section);
                    return sections;
                }
                sections = tmp;

                sections[section_counter] = new_section;
                section_counter++;
=======
                sections = realloc(sections, sizeof(char *) * (section_counter + 1));
                sections[section_counter] = section_name;
                section_counter++;

                file_content++;
>>>>>>> parent of 3a8f8e7 (comments)
            }
        }

        file_content++;
    }

<<<<<<< HEAD
    INISection **tmp2 =
        realloc(sections, sizeof(INISection*) * (section_counter + 1));
    if (!tmp2) return sections;
    sections = tmp2;

=======
    sections = realloc(sections, sizeof(char *) * (section_counter + 1));
>>>>>>> parent of 3a8f8e7 (comments)
    sections[section_counter] = NULL;

    return sections;
}