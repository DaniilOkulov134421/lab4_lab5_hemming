#include "hemming_7_4.h"

uint8_t * Hemming_7_4::matrix_mult (
    uint8_t info_word[INFO_WORD_SIZE],
    uint8_t g_m[INFO_WORD_SIZE][CODE_WORD_SIZE]){
    static uint8_t code_words_span[CODE_WORD_SIZE];
    code_words_span[0]=info_word[0]*g_m[0][0] ^ info_word[1]*g_m[1][0] ^ info_word[2]*g_m[2][0] ^ info_word[3]*g_m[3][0];
    code_words_span[1]=info_word[0]*g_m[0][1] ^ info_word[1]*g_m[1][1] ^ info_word[2]*g_m[2][1] ^ info_word[3]*g_m[3][1];
    code_words_span[2]=info_word[0]*g_m[0][2] ^ info_word[1]*g_m[1][2] ^ info_word[2]*g_m[2][2] ^ info_word[3]*g_m[3][2];
    code_words_span[3]=info_word[0]*g_m[0][3] ^ info_word[1]*g_m[1][3] ^ info_word[2]*g_m[2][3] ^ info_word[3]*g_m[3][3];
    code_words_span[4]=info_word[0]*g_m[0][4] ^ info_word[1]*g_m[1][4] ^ info_word[2]*g_m[2][4] ^ info_word[3]*g_m[3][4];
    code_words_span[5]=info_word[0]*g_m[0][5] ^ info_word[1]*g_m[1][5] ^ info_word[2]*g_m[2][5] ^ info_word[3]*g_m[3][5];
    code_words_span[6]=info_word[0]*g_m[0][6] ^ info_word[1]*g_m[1][6] ^ info_word[2]*g_m[2][6] ^ info_word[3]*g_m[3][6];

    return code_words_span; ///u*G
}
void Hemming_7_4::get_word(uint8_t *info_word, uint8_t inf_to_code)
{
    for (int bit_num = 0; bit_num < INFO_WORD_SIZE;  bit_num++)
        info_word[bit_num] = (1<<(bit_num)) & inf_to_code ? 1 : 0;
}
void Hemming_7_4::hemming_7_4 (uint8_t & inf_to_code)
{
    uint8_t info_word[INFO_WORD_SIZE];
    get_word(info_word,inf_to_code);
    uint8_t * code_word_array = matrix_mult(info_word, G_MATRIX);
    inf_to_code=0;
    for (int bit_num = 0; bit_num < CODE_WORD_SIZE;  bit_num++)
    {
        inf_to_code |=
            code_word_array[bit_num] ?
            1 << (CODE_WORD_SIZE - 1 - bit_num) :
            0 << (CODE_WORD_SIZE - 1 - bit_num);
    }
}


uint8_t  Hemming_7_4::calc_syndrome(uint8_t * code_word)
{   
    return 0x07 & (
        (GET_P0(*code_word) ^ GET_U3(*code_word) ^ GET_U2(*code_word) ^ GET_U0(*code_word)) << 0 |
        (GET_P1(*code_word) ^ GET_U3(*code_word) ^ GET_U1(*code_word) ^ GET_U0(*code_word)) << 1 |
        (GET_P2(*code_word) ^ GET_U2(*code_word) ^ GET_U1(*code_word) ^ GET_U0(*code_word)) << 2
    );
}
void Hemming_7_4::fix_mistake (uint8_t mistaken_place, uint8_t *code_word)
{
    if(0<mistaken_place && mistaken_place<8)
        *code_word ^= 1<<(8 - mistaken_place-1);
}
void Hemming_7_4::hemming_7_4_decoder (uint8_t * code_word)///uint8_t [7] - only one code_word
{
    fix_mistake(calc_syndrome(code_word), code_word);
    *code_word = 0x0f & (
        GET_U3(*code_word)<<3 |
        GET_U2(*code_word)<<2 |
        GET_U1(*code_word)<<1 |
        GET_U0(*code_word)<<0);
}
void Hemming_7_4::Encode(std::vector<uint8_t> & input)
{
    int v_size = input.size();
    for(int sym_num = 0; sym_num < v_size; sym_num++)
        hemming_7_4(input[sym_num]);
}
void Hemming_7_4::Decode (std::vector<uint8_t> &inputData)
{
    int vector_size = inputData.size();
    for (int word_sym = 0; word_sym < vector_size; word_sym++)
        hemming_7_4_decoder(&inputData[word_sym]);
}