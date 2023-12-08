#include "bitreader.h"
#include "bitwriter.h"
#include "node.h"
#include "pq.h"

#include <stdio.h>
#include <stdlib.h>

#define HELPMESSAGE                                                                                \
    "Usage: huff -i infile -o outfile\n"                                                           \
    "       huff -h\n"

typedef struct Code {
    uint64_t code;
    uint8_t code_length;
} Code;

uint32_t fill_histogram(FILE *fin, uint32_t *histogram) {
    for (int i = 0; i < 256; ++i) {
        histogram[i] = 0;
    }
    ++histogram[0x00];
    ++histogram[0xff];

    uint32_t size = 0;

    int byte;
    while ((byte = fgetc(fin)) != EOF) {
        ++histogram[byte];
        ++size;
    }

    return size;
}

Node *create_tree(uint32_t *histogram, uint16_t *num_leaves) {
    PriorityQueue *new_priority = pq_create();
    *num_leaves = 0;

    for (int i = 0; i < 256; ++i) {
        if (histogram[i] > 0) {
            Node *new_node = node_create((uint8_t) i, histogram[i]);

            if (new_node != NULL) {
                (*num_leaves)++;
                enqueue(new_priority, new_node);
            }
        }
    }

    while (!pq_is_empty(new_priority) && !pq_size_is_1(new_priority)) {
        Node *left = dequeue(new_priority);
        Node *right = dequeue(new_priority);

        Node *create_node = node_create(0, left->weight + right->weight);
        create_node->left = left;
        create_node->right = right;

        enqueue(new_priority, create_node);
    }

    Node *huffman = dequeue(new_priority);
    return huffman;
}

void fill_code_table(Code *code_table, Node *node, uint64_t code, uint8_t code_length) {
    if (node->left != NULL && node->right != NULL) {
        fill_code_table(code_table, node->left, code, code_length + 1);
        code |= (uint64_t) 1 << code_length;
        fill_code_table(code_table, node->right, code, code_length + 1);
    } else {
        code_table[node->symbol].code = code;
        code_table[node->symbol].code_length = code_length;
    }
}

void huff_write_tree(BitWriter *outbuf, Node *code_tree) {
    if (code_tree->left == NULL) {
        bit_write_bit(outbuf, 1);
        bit_write_uint8(outbuf, code_tree->symbol);
    } else {
        huff_write_tree(outbuf, code_tree->left);
        huff_write_tree(outbuf, code_tree->right);
        bit_write_bit(outbuf, 0);
    }
}

void huff_compress_file(BitWriter *outbuf, FILE *fin, uint32_t filesize, uint16_t num_leaves,
    Node *code_tree, Code *code_table) {
    bit_write_uint8(outbuf, 'H');
    bit_write_uint8(outbuf, 'C');
    bit_write_uint32(outbuf, filesize);
    bit_write_uint16(outbuf, num_leaves);
    huff_write_tree(outbuf, code_tree);

    while (true) {
        int b = fgetc(fin);
        if (b == EOF) {
            break;
        }

        uint64_t code = code_table[b].code;
        uint8_t code_length = code_table[b].code_length;
        for (int i = 0; i < code_length; ++i) {
            bit_write_bit(outbuf, (code & 1));
            code >>= 1;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf("huff:  -i option is required\n");
        printf(HELPMESSAGE);
        return 0;
    }

    const char *infile = argv[2];
    const char *outfile = argv[4];

    FILE *input_file = fopen(infile, "rb");
    if (input_file == NULL) {
        printf("huff:  error reading input file %s\n", infile);
        printf(HELPMESSAGE);
        exit(1);
    }

    BitWriter *output_file = bit_write_open(outfile);
    if (output_file == NULL) {
        printf("huff:  error reading output file %s\n", outfile);
        printf(HELPMESSAGE);
        exit(1);
    }

    uint32_t histogram[256];
    uint32_t filesize = fill_histogram(input_file, histogram);

    uint16_t num_leaves = 0;
    Node *huff_tree = create_tree(histogram, &num_leaves);

    Code code_table[256];
    fill_code_table(code_table, huff_tree, 0, 0);

    if (fseek(input_file, 0, 0) != 0) {
        fclose(input_file);
        exit(1);
    }

    huff_compress_file(output_file, input_file, filesize, num_leaves, huff_tree, code_table);
    return 0;
}
