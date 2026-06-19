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
    //* Setting up read buffer, *//
    //* file_content string *//
    //* & size of the  *//

    char buffer[BUFFER_SIZE];
    char *file_content = NULL;
    size_t size = 0;

    while (fgets(buffer, BUFFER_SIZE, file))
    {
        if (buffer[0] == ';' || buffer[0] == '#' || buffer[0] == '\n' || buffer[0] == '\r')
        {
            continue;
        }

        // Length of the buffer's string //
        size_t ini_chunk = strlen(buffer);

        // Assignment of the file_content pointer a new size //
        // Current file size + chunk + 1 extra //
        char *new_file_content = realloc(file_content, size + ini_chunk + 1);

        // If assignment failed, free space and return null
        if (!new_file_content)
        {
            free(file_content);
            return NULL;
        }

        // Assign to file_content pointer of new piece of data
        file_content = new_file_content;

        // Similar to concat, copy to the  //
        // file_content moved for size chunk from buffer //
        memcpy(file_content + size, buffer, ini_chunk);
        size += ini_chunk;
        file_content[size] = '\0';
    }

    return file_content;
}

char **get_sections(char *file_content)
{
    //* DEFINITION OF EMPTY ARRAY OF CHAR ARRAYS *//
    //* [[], []] *//
    char **sections = NULL;
    int section_counter = 0;

    while (*file_content)
    {
        //* Checking if section definition started *//
        if (*file_content == '[')
        {
            // Tagging up starting point of the name address
            char *start = file_content + 1;

            // Going through the rest of the file content //
            // until it's not the end or end tag of the section def //
            while (*file_content && *file_content != ']')
                file_content++;

            if (*file_content == ']')
            {
                // getting length of the name
                // (how many chars)
                size_t name_len = file_content - start;

                // copying the whole thing
                char *section_name = malloc(name_len + 1);
                memcpy(section_name, start, name_len);
                section_name[name_len] = '\0';

                // Appending array of section names
                sections = realloc(sections, sizeof(char *) * (section_counter + 1));
                sections[section_counter] = section_name;
                section_counter++;

                // moving forward
                file_content++;
            }
        }

        // Moving forward if nothing found
        file_content++;
    }

    // setting nulls and empties...
    sections = realloc(sections, sizeof(char *) * (section_counter + 1));
    sections[section_counter] = NULL;

    return sections;
}