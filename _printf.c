#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFF_SIZE 1024

/**
 * struct buffer_s - buffer structure
 * @buffer: buffer array
 * @start: starting index of buffer to write from
 * @index: current index of buffer to write to
 * @total: total characters written to buffer
 */
typedef struct buffer_s
{
    char buffer[BUFF_SIZE];
    int start;
    int index;
    int total;
} buffer_t;

int _printf(const char *format, ...);
buffer_t *init_buffer(void);
void write_buffer(buffer_t *output);
void free_buffer(buffer_t *output);
int _putchar(char c);
int print_char(buffer_t *output, char c);
int print_string(buffer_t *output, char *str);
int print_int(buffer_t *output, int n);
int get_flags(const char *format, int *i);
int get_width(const char *format, int *i, va_list list);
int get_precision(const char *format, int *i, va_list list);
int get_size(const char *format, int *i);
int handle_print(const char *format, int *i, va_list list, buffer_t *output, int flags, int width, int precision, int size);

int _printf(const char *format, ...)
{
    va_list list;
    buffer_t *output;
    int i, printed, flags, width, precision, size;

    if (format == NULL)
        return (-1);

    output = init_buffer();
    if (output == NULL)
        return (-1);

    va_start(list, format);

    for (i = 0, printed = 0; format[i] != '\0'; i++)
    {
        if (format[i] == '%')
        {
            flags = get_flags(format, &i);
            width = get_width(format, &i, list);
            precision = get_precision(format, &i, list);
            size = get_size(format, &i);
            printed += handle_print(format, &i, list, output, flags, width, precision, size);
        }
        else
        {
            printed += print_char(output, format[i]);
        }
    }

    va_end(list);

    write_buffer(output);
    free_buffer(output);

    return (printed);
}

buffer_t *init_buffer(void)
{
    buffer_t *output;

    output = malloc(sizeof(buffer_t));
    if (output == NULL)
        return (NULL);

    output->start = 0;
    output->index = 0;
    output->total = 0;

    return (output);
}

void write_buffer(buffer_t *output)
{
    if (output == NULL || output->index == 0)
        return;

    write(1, output->buffer + output->start, output->index - output->start);
    output->total += output->index - output->start;
    output->start = output->index;
}

void free_buffer(buffer_t *output)
{
    free(output);
}

int _putchar(char c)
{
    return (write(1, &c, 1));
}

int print_char(buffer_t *output, char c)
{
    if (output == NULL)
        return (-1);

    if (output->index == BUFF_SIZE)
        write_buffer(output);

    output->buffer[output->index++] = c;

    return (1);
}

int print_string(buffer_t *output, char *str)
{
    int i, len

