#include <stdio.h>
#include <stdlib.h>
#include <octaspire/core/octaspire_container_utf8_string.h>
#include <octaspire/core/octaspire_memory.h>
#include <octaspire/core/octaspire_stdio.h>
#include <octaspire/core/octaspire_helpers.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "octaspire_xxd requires two arguments");
        return EXIT_FAILURE;
    }

    char const * const name   = argv[1];
    char const * const inPath = argv[2];

    // Make sure that we can read the file later
    FILE *in = fopen(inPath, "rb");

    if (!in)
    {
        perror(inPath);
        return EXIT_FAILURE;
    }

    fclose(in);
    in = 0;

    octaspire_memory_allocator_t *allocator = octaspire_memory_allocator_new(0);

    if (!allocator)
    {
        fprintf(stderr, "octaspire_xxd cannot create allocator");
        return EXIT_FAILURE;
    }

    octaspire_stdio_t *stdio = octaspire_stdio_new(allocator);

    if (!stdio)
    {
        fprintf(stderr, "octaspire_xxd cannot create stdio");
        octaspire_memory_allocator_release(allocator);
        allocator = 0;
        return EXIT_FAILURE;
    }

    octaspire_container_utf8_string_t *outPath = octaspire_container_utf8_string_new_format(
        allocator,
        "include/octaspire/maze/%s.c",
        name);

    if (!outPath)
    {
        fprintf(stderr, "octaspire_xxd could not build output path");
        octaspire_stdio_release(stdio);
        stdio = 0;
        octaspire_memory_allocator_release(allocator);
        allocator = 0;
        return EXIT_FAILURE;
    }

    FILE *out = fopen(octaspire_container_utf8_string_get_c_string(outPath), "wb");

    if (!out)
    {
        perror(octaspire_container_utf8_string_get_c_string(outPath));
        octaspire_container_utf8_string_release(outPath);
        outPath = 0;
        octaspire_stdio_release(stdio);
        stdio = 0;
        octaspire_memory_allocator_release(allocator);
        allocator = 0;
        return EXIT_FAILURE;
    }

    size_t bufferLen = 0;
    char * buffer = octaspire_helpers_path_to_buffer(inPath, &bufferLen, allocator, stdio);

    if (!buffer)
    {
        fprintf(stderr, "octaspire_xxd could not read file into memory");
        octaspire_container_utf8_string_release(outPath);
        outPath = 0;
        octaspire_stdio_release(stdio);
        stdio = 0;
        octaspire_memory_allocator_release(allocator);
        allocator = 0;
        return EXIT_FAILURE;
    }

    fprintf(out, "#include <stdio.h>\n\n");
    fprintf(out, "unsigned char const %s[] =\n{\n", name);

    for (size_t i = 0; i < bufferLen; ++i)
    {
        fprintf(out, " 0x%02x,", (unsigned char)buffer[i]);

        if (i % 15 == 0)
        {
            fprintf(out, "\n");
        }

    }

    fprintf(out, "\n};\n");
    fprintf(out, "size_t const %s_len=%zu;\n", name, bufferLen);

    fclose(out);
    out = 0;

    free(buffer);
    buffer = 0;
    octaspire_container_utf8_string_release(outPath);
    outPath = 0;
    octaspire_stdio_release(stdio);
    stdio = 0;
    octaspire_memory_allocator_release(allocator);
    allocator = 0;

    return EXIT_SUCCESS;
}
