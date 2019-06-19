#include <iostream>
#include <stdint.h>
#include <cstdint>
#include <vector>

static const int INFO_WORD_SIZE = 4;
static const int CODE_WORD_SIZE = 7;

static const int P0 = 0x40;
static const int P1 = 0x20;
static const int P2 = 0x08;
static const int U0 = 0x01;
static const int U1 = 0x02;
static const int U2 = 0x04;
static const int U3 = 0x10;

inline int BIT_STATE(int num, int bit_msk) {
    return (((num) & bit_msk) ? 1 : 0);
}

inline uint8_t GET_P0 (uint8_t num) {
    return BIT_STATE(num, P0);
}

inline uint8_t GET_P1 (uint8_t num) {
    return BIT_STATE(num, P1);
}

inline uint8_t GET_P2 (uint8_t num) {
    return BIT_STATE(num, P2);
}

inline uint8_t GET_U0 (uint8_t num) {
    return BIT_STATE(num, U0);
}

inline uint8_t GET_U1(uint8_t num) {
    return BIT_STATE(num, U1);
}

inline uint8_t GET_U2(uint8_t num) {
    return BIT_STATE(num, U2);
}

inline uint8_t GET_U3(uint8_t num) {
    return BIT_STATE(num, U3);
}

/*
input data format is vector of unsigned integer numbers
in which an information words is right-justified four-bit field
*/
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
    void hemming_7_4_decoder (uint8_t * code_word);///uint8_t [7] - only one code_word

public:
	//for private tests work
	void hemming_7_4 (uint8_t & inf_to_code);
	uint8_t calc_syndrome(uint8_t * code_word);
	void fix_mistake (uint8_t mistaken_place, uint8_t *code_word);
    
    void Encode(std::vector<uint8_t> &input);
    void Decode(std::vector<uint8_t> &inputData);
};