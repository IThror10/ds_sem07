// void print_freq(freq_list_t *freq)
// {
//     for (; freq; freq = freq->next)
//         printf("%c -- %ld\n", freq->letter, freq->amount);
//     printf("\n");
// }

// void print_nodes(nodes_t *nodes)
// {
//     for (int i = 0; i < nodes->size; i++)
//     {
//         node_t *node = nodes->data + i;
//         if (LEFT_IS_TREE(node->flags))
//             printf("%d: [%d] \t", i, node->left);
//         else
//             printf("%d: {%c} \t", i, node->left);

//         if (RIGHT_IS_TREE(node->flags))
//             printf("%d: [%d]\n", i, node->right);
//         else
//             printf("%d: {%c}\n", i, node->right);
//     }
//     printf("\n");
// }

// void print_codes(codes_t *codes)
// {
//     for (int i = 0; i < codes->size; i++)
//     {
//         code_t *code = codes->data + i;
//         printf("{%c} [%d] %x %x\n", code->sim, code->bits, code->string[0], code->string[1]);
//     }
// }

