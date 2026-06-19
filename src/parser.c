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
    char **sections = get_sections(file_content);

    for (int i = 0; sections[i] != NULL; i++)
    {
        printf("Section: %s\n", sections[i]);
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

char **get_sections(char *file_content)
{
    char **sections = NULL;
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

                sections = realloc(sections, sizeof(char *) * (section_counter + 1));
                sections[section_counter] = section_name;
                section_counter++;

                file_content++;
            }
        }

        file_content++;
    }

    sections = realloc(sections, sizeof(char *) * (section_counter + 1));
    sections[section_counter] = NULL;

    return sections;
}