#include "encryp_png.h"
#include <stdio.h>

int width, height;
png_byte color_type;
png_byte bit_depth;
png_bytep *row_pointers = NULL;

void read_png_file(char *filename)
{
    FILE *fp = fopen(filename, "rb");

    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png)
        abort();

    png_infop info = png_create_info_struct(png);
    if (!info)
        abort();

    if (setjmp(png_jmpbuf(png)))
        abort();

    png_init_io(png, fp);

    png_read_info(png, info);

    width = png_get_image_width(png, info);
    height = png_get_image_height(png, info);
    color_type = png_get_color_type(png, info);
    bit_depth = png_get_bit_depth(png, info);

    if (bit_depth == 16)
        png_set_strip_16(png);

    if (color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_palette_to_rgb(png);

    // PNG_COLOR_TYPE_GRAY_ALPHA is always 8 or 16bit depth.
    if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
        png_set_expand_gray_1_2_4_to_8(png);

    if (png_get_valid(png, info, PNG_INFO_tRNS))
        png_set_tRNS_to_alpha(png);

    // These color_type don't have an alpha channel then fill it with 0xff.
    if (color_type == PNG_COLOR_TYPE_RGB ||
        color_type == PNG_COLOR_TYPE_GRAY ||
        color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_filler(png, 0xFF, PNG_FILLER_AFTER);

    if (color_type == PNG_COLOR_TYPE_GRAY ||
        color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
        png_set_gray_to_rgb(png);

    png_read_update_info(png, info);

    if (row_pointers)
        abort();

    row_pointers = (png_bytep *)malloc(sizeof(png_bytep) * height);
    for (int y = 0; y < height; y++)
    {
        row_pointers[y] = (png_byte *)malloc(png_get_rowbytes(png, info));
    }

    png_read_image(png, row_pointers);

    fclose(fp);

    png_destroy_read_struct(&png, &info, NULL);

    png_destroy_read_struct(&png, &info, NULL);
    png = NULL;
    info = NULL;
}

void write_png_file(char *filename)
{
    FILE *fp = fopen(filename, "wb");
    if (!fp)
        abort();

    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png)
        abort();

    png_infop info = png_create_info_struct(png);
    if (!info)
        abort();

    if (setjmp(png_jmpbuf(png)))
        abort();

    png_init_io(png, fp);

    // Output is 8bit depth, RGBA format.
    png_set_IHDR(
        png,
        info,
        width, height,
        8,
        PNG_COLOR_TYPE_RGBA,
        PNG_INTERLACE_NONE,
        PNG_COMPRESSION_TYPE_DEFAULT,
        PNG_FILTER_TYPE_DEFAULT);
    png_write_info(png, info);

    // To remove the alpha channel for PNG_COLOR_TYPE_RGB format,
    // Use png_set_filler().
    // png_set_filler(png, 0, PNG_FILLER_AFTER);

    if (!row_pointers)
        abort();

    png_write_image(png, row_pointers);
    png_write_end(png, NULL);

    for (int y = 0; y < height; y++)
    {
        free(row_pointers[y]);
    }
    free(row_pointers);

    fclose(fp);

    png_destroy_write_struct(&png, &info);

    if (png && info)
        png_destroy_write_struct(&png, &info);
}

char BitToChar(Lista *MsgBits)
{
    char c = 0;
    int converter[8] = {128, 64, 32, 16, 8, 4, 2, 1};

    for (int i = 0; i <= 7 && MsgBits->size; i++)
    {
        if (MsgBits->primeiro->valor) // Verifica se o ponteiro não é NULL
        {
            c += converter[i];
        }

        deletar_elemento(MsgBits, MsgBits->primeiro);
    }

    return c;
}

void process_png_file_hide(Lista *BitsMensagem)
{
    char writeone = 1;
    char writezero = 255 - 1;

    for (int y = 0; y < height && BitsMensagem->size; y++)
    {
        png_bytep row = row_pointers[y];
        for (int x = 0; x < width && BitsMensagem->size; x++)
        {
            png_bytep px = &(row[x * 4]);

            for (int i = 0; i < 4 && BitsMensagem->size; i++)
            {
                if (BitsMensagem->primeiro->valor == 1)
                {
                    px[i] = px[i] | writeone;
                }
                else
                {
                    px[i] = px[i] & writezero;
                }

                deletar_elemento(BitsMensagem, BitsMensagem->primeiro);
            }
        }
    }
}

void process_png_file_print(void)
{
    char fim = 1;

    Lista msgBits = criar_lista();
    Lista *Adress = &msgBits;

    for (int y = 0; y < height && fim; y++)
    {
        png_bytep row = row_pointers[y];
        for (int x = 0; x < width && fim; x++)
        {
            png_bytep px = &(row[x * 4]);
            for (int z = 0; z < 4 && fim; z++)
            {

                inserir_elemento(Adress, criar_celula(1 & px[z]));

                if (Adress->size == 8)
                {
                    // show_c_list(Adress);
                    char ch = BitToChar(Adress);
                    printf("%c", ch);
                    if (ch == '\0')
                    {
                        fim = 0;
                    }
                }
            }
        }
    }

    putchar('\n');
    liberar_lista(Adress);
}

void hide(char *FilenameINPUT, char *FilenameOUTPUT, char *msg)
{
    FILE *info = fopen(msg, "r");

    if (info == NULL)
        abort();

    fseek(info, 0, SEEK_END);

    long long Msgsize = ftell(info);

    fseek(info, 0, SEEK_SET);

    char *mensagem = (char *)malloc(Msgsize + 1);

    if (mensagem == NULL)
        abort();

    fread(mensagem, 1, Msgsize, info);

    mensagem[Msgsize] = '\0';

    Lista msgBits = criar_lista();
    Lista *Adress = &msgBits;
    read_png_file(FilenameINPUT);

    if (Msgsize > height * width)
        abort();

    for (int i = 0; i < Msgsize + 1; i++)
    {
        for (int j = 7, pos = 128; j >= 0; j--, pos >>= 1)
        {
            inserir_elemento(Adress, criar_celula(1 && (pos & mensagem[i])));
        }
    }

    process_png_file_hide(Adress);

    write_png_file(FilenameOUTPUT);

    liberar_lista(Adress);
    fclose(info);
    free(mensagem);
}

void print_message(char *filename)
{
    read_png_file(filename);
    process_png_file_print();
}
