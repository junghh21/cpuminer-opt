#include "yespower.h"
//#include "blake2b.h"
//#include "sysendian.h"
//#include <stdio.h>

//static const yespower_params_t v1 = {YESPOWER_1_0, 2048, 8, NULL, 0};
static const yespower_params_t v2 = {YESPOWER_1_0, 2048, 32, NULL, 0};
// yespower-b2b parameters: N= 2048, R= 32
// Key= "Now I am become Death, the destroyer of worlds"
// Key length= 46
static const yespower_params_t v3 = {YESPOWER_1_0_BLAKE2B, 2048, 32,
																			(const uint8_t *)"Now I am become Death, the destroyer of worlds", 46};

int y1_foo(const input_t *input, output_t *output, unsigned int *no)
{
	unsigned int *a = (unsigned int *)input->bin;
	unsigned int *b = (unsigned int *)output->bin;
	unsigned int *mask = &(output->mask);
	unsigned int i;
	output->mask = input->mask;
	output->algo = input->algo;
	output->job_id = input->job_id;
	const yespower_params_t *yes_param = &v2;
	yespower_tls_func_t yespower_tls_func = yespower_tls;
	if (input->algo == YESPOWER_1_0_BLAKE2B)
	{
		yespower_tls_func = yespower_b2b_tls;
	 	yes_param = &v3;
	}
	// printf("%08X, %d, %08X, %d\n"
	// 				, output->mask, output->algo, output->job_id, input->count);
	// printf("%08X %08X %08X %08X\n"
	// 				, a[0], a[1], a[18], a[19]);
	for(i=*no; i<=*no+input->count-1; i++)
	{
		a[19] = i;
		yespower_tls_func((const uint8_t *)a, 80, yes_param, (yespower_binary_t *)b, 0);
		//printf("%08X : %08X, %08X\n", i, b[7], *mask);
		if (b[7] < *mask)
		{
			//printf("%08X : %08X : %08X, %08X\n", i, *no, b[7], *mask);
			*mask = b[7];
			*no = i;
			return 0;
		}
	}
	//printf("%08X : %08X : %08X, %08X\n", i, *no, b[7], *mask);
	*no = i;
	return -1;
}






/*int yespower_hash(const char *input, char *output)
{
	uint32_t time = le32dec(&input[68]);
	if (time > 1676761800) {
		return yespower_tls(input, 80, &v1, (yespower_binary_t *) output);
	} else {
		return yespower_tls(input, 80, &v2, (yespower_binary_t *) output);
	}
}


int y1_foo(const uint8_t *input, uint8_t *output, unsigned int *no, unsigned int *mask)
{
		//yespower_tls( (yespower_binary_t*)input, 80, &v1, (yespower_binary_t*)output );
		return yespower_tls((yespower_binary_t *)input, 80, &v2, (yespower_binary_t *) output);
}


int _b1_foo(const uint8_t *input, uint8_t *output, unsigned int *no, unsigned int *mask)
{
		//yespower_tls( (yespower_binary_t*)input, 80, &v1, (yespower_binary_t*)output );
		return yespower_tls((yespower_binary_t *)input, 80, &v3, (yespower_binary_t *) output);
}

int _b1_foo2(const uint8_t *input, uint8_t *output, unsigned int *no, unsigned int *mask)
{
	unsigned int *a = input;
	unsigned int *b = output;
	unsigned int i;
	for(i=*no;i<(*no)+200;i++)
	{
		a[19] = i;
		yespower_tls((yespower_binary_t *)input, 80, &v3, (yespower_binary_t *) output);
		//printf("%08X : %08X, %08X\n", i, b[7], *mask);
		if (b[7] < *mask)
		{
			*mask = b[7];
			*no = i;
			//printf("%08X : %08X : %08X, %08X\n", i, *no, b[7], *mask);
			return 0;
		}
	}
	*no = i-1;
	//printf("%08X : %08X : %08X, %08X\n", i, *no, b[7], *mask);
	return -1;
}
*/