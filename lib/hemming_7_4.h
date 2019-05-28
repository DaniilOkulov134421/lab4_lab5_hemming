#include <iostream>
#include <stdint.h>
#include <cstdint>
#include <vector>

#define INFO_WORD_SIZE 4
#define CODE_WORD_SIZE 7

#define P0 (0x40U)
#define P1 (0x20U)
#define P2 (0x08U)
#define U0 (0x01U)
#define U1 (0x02U)
#define U2 (0x04U)
#define U3 (0x10U)

#define BIT_STATE(num, bit_msk) (((num) & bit_msk) ? 1 : 0)
#define GET_P0(unint8_num) (BIT_STATE(unint8_num, P0))
#define GET_P1(unint8_num) (BIT_STATE(unint8_num, P1))
#define GET_P2(unint8_num) (BIT_STATE(unint8_num, P2))
#define GET_U0(unint8_num) (BIT_STATE(unint8_num, U0))
#define GET_U1(unint8_num) (BIT_STATE(unint8_num, U1))
#define GET_U2(unint8_num) (BIT_STATE(unint8_num, U2))
#define GET_U3(unint8_num) (BIT_STATE(unint8_num, U3))

class Hemming_7_4
{
private:
    uint8_t G_MATRIX [INFO_WORD_SIZE][CODE_WORD_SIZE] =
	{
	    {1, 1, 0, 1, 0, 0, 1},
	    {0, 1, 0, 1, 0, 1, 0},
	    {1, 0, 0, 1, 1, 0, 0},
	    {1, 1, 1, 0, 0, 0, 0}
	};
	uint8_t * matrix_mult (
        uint8_t info_word[INFO_WORD_SIZE],
        uint8_t g_m[INFO_WORD_SIZE][CODE_WORD_SIZE]
        );
    void get_word(uint8_t *info_word, uint8_t inf_to_code);
    // void hemming_7_4 (uint8_t & inf_to_code);
    // uint8_t calc_syndrome(uint8_t * code_word);
    uint8_t dec_to_bin_convert(uint8_t dec_intepretetion_of_binary_num);
    uint8_t get_mistaken_bit_num (char *syndrome);
    // void fix_mistake (uint8_t mistaken_place, uint8_t *code_word);
    void hemming_7_4_decoder (uint8_t * code_word);///uint8_t [7] - only one code_word

public:
	//for private tests work
	void hemming_7_4 (uint8_t & inf_to_code);
	uint8_t calc_syndrome(uint8_t * code_word);
	void fix_mistake (uint8_t mistaken_place, uint8_t *code_word);
    
    void Encode(std::vector<uint8_t> &input);
    void Decode(std::vector<uint8_t> &inputData);
} ;