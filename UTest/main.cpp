#include "main.h"


int main(int argc, char** argv)
{ 	
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

static const std::vector<uint8_t> expected_code_word={0x0,0x69,0x2A,0x43,0x4C,0x25,0x66,0xF,0x70,0x19,0x5A,0x33,0x3C,0x55,0x16,0x7F};

TEST(public_metods_tests , test_encode){
	int mistake=0;
	std::vector<uint8_t>code_word;
	Hemming_7_4 heming;
	for(uint8_t word=0;word<16;word++)
		code_word.push_back(word);

	heming.Encode(code_word);
	for(uint8_t num=0;num<16;num++){
		if(expected_code_word[num]!=code_word[num])
			mistake++;
	}
	ASSERT_TRUE(mistake == 0) << "mistake coding/decoding!";
}
TEST(public_metods_tests , test_decode){
	int mistake=0;
	std::vector<uint8_t>info_word;
	std::vector<uint8_t>code_word=expected_code_word;
	Hemming_7_4 heming;
	for(uint8_t word=0;word<16;word++)
		info_word.push_back(word);

	heming.Decode(code_word);
	for(uint8_t num=0;num<16;num++){
		if(info_word[num]!=code_word[num])
			mistake++;
	}
	ASSERT_TRUE(mistake == 0) << "mistake coding/decoding!";
}

TEST(public_metods_tests , fixed_mistake_in_decoding_1){
	int mistake=0;
	std::vector<uint8_t>
		info_word,
		expected_info_word;
	for(uint8_t word=0;word<16;word++)
		info_word.push_back(word);

	expected_info_word = info_word;
	Hemming_7_4 hm;
	hm.Encode(info_word);

#define MISTAKE_POINT 3
	for(int word_num = 0; word_num < info_word.size(); word_num++){
		info_word[word_num] ^= 1<<MISTAKE_POINT;
	}
	hm.Decode(info_word);

	ASSERT_TRUE(info_word == expected_info_word) << "mistake decoding!";
}


TEST(private_methods_tests, fix_mistake_all){
	Hemming_7_4 hm;
	int miss=0;
	uint8_t code_word;
	uint8_t miss_code_word;
 	for(uint8_t num_word=0;num_word<16;num_word++)
 	{
 		code_word=num_word;
 		hm.hemming_7_4(code_word);

 		for(int num=0;num<7;num++){
 			miss_code_word=code_word^(1<<num);
			uint8_t syndrome = hm.calc_syndrome(&miss_code_word);
			hm.fix_mistake(syndrome, &miss_code_word);
			if(code_word != miss_code_word)
			{
				miss++;
			}
		}
 	}
	ASSERT_TRUE(miss == 0) << "mistake not fixed!";
}
