#include "bitreader.h"
#include "bitwriter.h"
#include "pq.h"

#include <stdio.h>
#include <stdlib.h>

#define HELPMESSAGE                                                                                \
    "Usage: dehuff -i infile -o outfile\n"                                                         \
    "dehuff -h\n"

Node *stack_pop(Node *stack[64], int *top) {
    if (*top < 0) {
        printf("stack underflow");
        exit(1);
    }

    Node *temp = stack[*top];
    (*top)--;
    return temp;
}

void stack_push(Node *stack[64], Node *obj, int *top) {
    if (*top >= 64) {
        printf("stack overflow");
        exit(1);
    }

    (*top)++;
    stack[*top] = obj;
}

void dehuff_decompress_file(FILE *fout, BitReader *inbuf) {
    Node *stack[64];
    int top = -1;

    uint8_t type1 = bit_read_uint8(inbuf);
    uint8_t type2 = bit_read_uint8(inbuf);
    uint32_t filesize = bit_read_uint32(inbuf);
    uint16_t num_leaves = bit_read_uint16(inbuf);

    assert(type1 == 'H');
    assert(type2 == 'C');

    uint16_t num_nodes = 2 * num_leaves - 1;
    Node *node = NULL;

    for (int i = 0; i < num_nodes; ++i) {
        uint8_t bit = bit_read_bit(inbuf);
        if (bit == 1) {
            uint8_t symbol = bit_read_uint8(inbuf);
            node = node_create(symbol, 0);
        } else {
            node = node_create(0, 0);
            node->right = stack_pop(stack, &top);
            node->left = stack_pop(stack, &top);
        }
        stack_push(stack, node, &top);
    }

    Node *code_tree = stack_pop(stack, &top);
    for (uint32_t i = 0; i < filesize; ++i) {
        node = code_tree;
        while (true) {
            uint8_t bit = bit_read_bit(inbuf);
            if (bit == 0 && node != NULL) {
                node = node->left;
            } else {
                if (node != NULL) {
                    node = node->right;
                }
            }
            if (node != NULL && node->left == NULL && node->right == NULL) {
                break;
            }
        }
        fputc(node->symbol, fout);
    }

    node_free(&code_tree);
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf("dehuff:  -i option is required");
        printf(HELPMESSAGE);
        return 0;
    }

    const char *infile = argv[2];
    const char *outfile = argv[4];

    BitReader *input_file = bit_read_open(infile);
    if (input_file == NULL) {
        printf("dehuff:  error reading input file %s", infile);
        printf(HELPMESSAGE);
        exit(1);
    }

    FILE *output_file = fopen(outfile, "wb");
    if (output_file == NULL) {
        printf("dehuff:  error reading output file %s", outfile);
        printf(HELPMESSAGE);
        exit(1);
    }

    dehuff_decompress_file(output_file, input_file);

    fclose(output_file);
    bit_read_close(&input_file);

    return 0;
}
