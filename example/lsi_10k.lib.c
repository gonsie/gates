//Elsa Gonsiorowski
//Rensselaer Polytechnic Institute

#include <stdio.h>
#include "generic-model.h"
#include "library.h"

void AN2_func  (int* input, int* internal, int* output) {
	//Z : A B
	output[0] = input[0] && input[1];
	return;
}
float AN2_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.48;
			}
			if (!rising) {
				return 0.77;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.48;
			}
			if (!rising) {
				return 0.77;
			}
		}
	}
	return 1.0;
}

void AN2P_func  (int* input, int* internal, int* output) {
	//Z : A B
	output[0] = input[0] && input[1];
	return;
}
float AN2P_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.54;
			}
			if (!rising) {
				return 0.84;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.54;
			}
			if (!rising) {
				return 0.84;
			}
		}
	}
	return 1.0;
}

void AN3_func  (int* input, int* internal, int* output) {
	//Z : A B C
	output[0] = input[0] && input[1] && input[2];
	return;
}
float AN3_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['C']
		if ( in_pin == 2 ) {
			if (rising) {
				return 0.69;
			}
			if (!rising) {
				return 0.85;
			}
		}
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.69;
			}
			if (!rising) {
				return 0.85;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.69;
			}
			if (!rising) {
				return 0.85;
			}
		}
	}
	return 1.0;
}

void AN3P_func  (int* input, int* internal, int* output) {
	//Z : A B C
	output[0] = input[0] && input[1] && input[2];
	return;
}
float AN3P_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['C']
		if ( in_pin == 2 ) {
			if (rising) {
				return 0.84;
			}
			if (!rising) {
				return 0.94;
			}
		}
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.84;
			}
			if (!rising) {
				return 0.94;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.84;
			}
			if (!rising) {
				return 0.94;
			}
		}
	}
	return 1.0;
}

void AN4_func  (int* input, int* internal, int* output) {
	//Z : A B C D
	output[0] = input[0] && input[1] && input[2] && input[3];
	return;
}
float AN4_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['D']
		if ( in_pin == 3 ) {
			if (rising) {
				return 0.97;
			}
			if (!rising) {
				return 0.95;
			}
		}
		//['C']
		if ( in_pin == 2 ) {
			if (rising) {
				return 0.97;
			}
			if (!rising) {
				return 0.95;
			}
		}
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.97;
			}
			if (!rising) {
				return 0.95;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.97;
			}
			if (!rising) {
				return 0.95;
			}
		}
	}
	return 1.0;
}

void AN4P_func  (int* input, int* internal, int* output) {
	//Z : A B C D
	output[0] = input[0] && input[1] && input[2] && input[3];
	return;
}
float AN4P_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['D']
		if ( in_pin == 3 ) {
			if (rising) {
				return 1.15;
			}
			if (!rising) {
				return 0.96;
			}
		}
		//['C']
		if ( in_pin == 2 ) {
			if (rising) {
				return 1.15;
			}
			if (!rising) {
				return 0.96;
			}
		}
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.15;
			}
			if (!rising) {
				return 0.96;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.15;
			}
			if (!rising) {
				return 0.96;
			}
		}
	}
	return 1.0;
}

void AO1_func  (int* input, int* internal, int* output) {
	//Z : ((A B)+C+D)'
	output[0] = !((input[0] && input[1]) || input[2] || input[3]);
	return;
}
float AO1_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['D']
		if ( in_pin == 3 ) {
			if (rising) {
				return 1.11;
			}
			if (!rising) {
				return 0.27;
			}
		}
		//['C']
		if ( in_pin == 2 ) {
			if (rising) {
				return 1.11;
			}
			if (!rising) {
				return 0.27;
			}
		}
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.11;
			}
			if (!rising) {
				return 0.27;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.11;
			}
			if (!rising) {
				return 0.27;
			}
		}
	}
	return 1.0;
}

void AO11_func  (int* input, int* internal, int* output) {
	//Z : (A B+C D+E F)'
	output[0] = !(input[0] && input[1] || input[2] && input[3] || input[4] && input[5]);
	return;
}
float AO11_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['F']
		if ( in_pin == 5 ) {
			if (rising) {
				return 1.17;
			}
			if (!rising) {
				return 0.95;
			}
		}
		//['D']
		if ( in_pin == 3 ) {
			if (rising) {
				return 1.17;
			}
			if (!rising) {
				return 0.95;
			}
		}
		//['C']
		if ( in_pin == 2 ) {
			if (rising) {
				return 1.17;
			}
			if (!rising) {
				return 0.95;
			}
		}
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.17;
			}
			if (!rising) {
				return 0.95;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.17;
			}
			if (!rising) {
				return 0.95;
			}
		}
		//['E']
		if ( in_pin == 4 ) {
			if (rising) {
				return 1.17;
			}
			if (!rising) {
				return 0.95;
			}
		}
	}
	return 1.0;
}

void AO11P_func  (int* input, int* internal, int* output) {
	//Z : (A B+C D+E F)'
	output[0] = !(input[0] && input[1] || input[2] && input[3] || input[4] && input[5]);
	return;
}
float AO11P_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['F']
		if ( in_pin == 5 ) {
			if (rising) {
				return 1.34;
			}
			if (!rising) {
				return 1.04;
			}
		}
		//['D']
		if ( in_pin == 3 ) {
			if (rising) {
				return 1.34;
			}
			if (!rising) {
				return 1.04;
			}
		}
		//['C']
		if ( in_pin == 2 ) {
			if (rising) {
				return 1.34;
			}
			if (!rising) {
				return 1.04;
			}
		}
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.34;
			}
			if (!rising) {
				return 1.04;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.34;
			}
			if (!rising) {
				return 1.04;
			}
		}
		//['E']
		if ( in_pin == 4 ) {
			if (rising) {
				return 1.34;
			}
			if (!rising) {
				return 1.04;
			}
		}
	}
	return 1.0;
}

void AO12_func  (int* input, int* internal, int* output) {
	//Z : ((A+B)(C+D)(E+F)(G+H))'
	output[0] = !((input[0] || input[1]) && (input[2] || input[3]) && (input[4] || input[5]) && (input[6] || input[7]));
	return;
}
float AO12_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['F']
		if ( in_pin == 5 ) {
			if (rising) {
				return 1.38;
			}
			if (!rising) {
				return 1.15;
			}
		}
		//['D']
		if ( in_pin == 3 ) {
			if (rising) {
				return 1.38;
			}
			if (!rising) {
				return 1.15;
			}
		}
		//['C']
		if ( in_pin == 2 ) {
			if (rising) {
				return 1.38;
			}
			if (!rising) {
				return 1.15;
			}
		}
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.38;
			}
			if (!rising) {
				return 1.15;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.38;
			}
			if (!rising) {
				return 1.15;
			}
		}
		//['E']
		if ( in_pin == 4 ) {
			if (rising) {
				return 1.38;
			}
			if (!rising) {
				return 1.15;
			}
		}
		//['H']
		if ( in_pin == 7 ) {
			if (rising) {
				return 1.38;
			}
			if (!rising) {
				return 1.15;
			}
		}
		//['G']
		if ( in_pin == 6 ) {
			if (rising) {
				return 1.38;
			}
			if (!rising) {
				return 1.15;
			}
		}
	}
	return 1.0;
}

void AO12P_func  (int* input, int* internal, int* output) {
	//Z : ((A+B)(C+D)(E+F)(G+H))'
	output[0] = !((input[0] || input[1]) && (input[2] || input[3]) && (input[4] || input[5]) && (input[6] || input[7]));
	return;
}
float AO12P_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['F']
		if ( in_pin == 5 ) {
			if (rising) {
				return 1.56;
			}
			if (!rising) {
				return 1.26;
			}
		}
		//['D']
		if ( in_pin == 3 ) {
			if (rising) {
				return 1.56;
			}
			if (!rising) {
				return 1.26;
			}
		}
		//['C']
		if ( in_pin == 2 ) {
			if (rising) {
				return 1.56;
			}
			if (!rising) {
				return 1.26;
			}
		}
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.56;
			}
			if (!rising) {
				return 1.26;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.56;
			}
			if (!rising) {
				return 1.26;
			}
		}
		//['E']
		if ( in_pin == 4 ) {
			if (rising) {
				return 1.56;
			}
			if (!rising) {
				return 1.26;
			}
		}
		//['H']
		if ( in_pin == 7 ) {
			if (rising) {
				return 1.56;
			}
			if (!rising) {
				return 1.26;
			}
		}
		//['G']
		if ( in_pin == 6 ) {
			if (rising) {
				return 1.56;
			}
			if (!rising) {
				return 1.26;
			}
		}
	}
	return 1.0;
}

void AO1P_func  (int* input, int* internal, int* output) {
	//Z : ((A B)+C+D)'
	output[0] = !((input[0] && input[1]) || input[2] || input[3]);
	return;
}
float AO1P_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['D']
		if ( in_pin == 3 ) {
			if (rising) {
				return 1.12;
			}
			if (!rising) {
				return 0.28;
			}
		}
		//['C']
		if ( in_pin == 2 ) {
			if (rising) {
				return 1.12;
			}
			if (!rising) {
				return 0.28;
			}
		}
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.12;
			}
			if (!rising) {
				return 0.28;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.12;
			}
			if (!rising) {
				return 0.28;
			}
		}
	}
	return 1.0;
}

void AO2_func  (int* input, int* internal, int* output) {
	//Z : (A B+C D)'
	output[0] = !(input[0] && input[1] || input[2] && input[3]);
	return;
}
float AO2_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['D']
		if ( in_pin == 3 ) {
			if (rising) {
				return 0.82;
			}
			if (!rising) {
				return 0.47;
			}
		}
		//['C']
		if ( in_pin == 2 ) {
			if (rising) {
				return 0.82;
			}
			if (!rising) {
				return 0.47;
			}
		}
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.82;
			}
			if (!rising) {
				return 0.47;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.82;
			}
			if (!rising) {
				return 0.47;
			}
		}
	}
	return 1.0;
}

void AO2P_func  (int* input, int* internal, int* output) {
	//Z : (A B+C D)'
	output[0] = !(input[0] && input[1] || input[2] && input[3]);
	return;
}
float AO2P_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['D']
		if ( in_pin == 3 ) {
			if (rising) {
				return 0.8;
			}
			if (!rising) {
				return 0.38;
			}
		}
		//['C']
		if ( in_pin == 2 ) {
			if (rising) {
				return 0.8;
			}
			if (!rising) {
				return 0.38;
			}
		}
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.8;
			}
			if (!rising) {
				return 0.38;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.8;
			}
			if (!rising) {
				return 0.38;
			}
		}
	}
	return 1.0;
}

void AO3_func  (int* input, int* internal, int* output) {
	//Z : ((A+B)C D)'
	output[0] = !((input[0] || input[1]) && input[2] && input[3]);
	return;
}
float AO3_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['D']
		if ( in_pin == 3 ) {
			if (rising) {
				return 0.52;
			}
			if (!rising) {
				return 0.39;
			}
		}
		//['C']
		if ( in_pin == 2 ) {
			if (rising) {
				return 0.52;
			}
			if (!rising) {
				return 0.39;
			}
		}
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.52;
			}
			if (!rising) {
				return 0.39;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.52;
			}
			if (!rising) {
				return 0.39;
			}
		}
	}
	return 1.0;
}

void AO3P_func  (int* input, int* internal, int* output) {
	//Z : ((A+B)C D)'
	output[0] = !((input[0] || input[1]) && input[2] && input[3]);
	return;
}
float AO3P_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['D']
		if ( in_pin == 3 ) {
			if (rising) {
				return 0.5;
			}
			if (!rising) {
				return 0.42;
			}
		}
		//['C']
		if ( in_pin == 2 ) {
			if (rising) {
				return 0.5;
			}
			if (!rising) {
				return 0.42;
			}
		}
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.5;
			}
			if (!rising) {
				return 0.42;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.5;
			}
			if (!rising) {
				return 0.42;
			}
		}
	}
	return 1.0;
}

void AO4_func  (int* input, int* internal, int* output) {
	//Z : ((A+B)(C+D))'
	output[0] = !((input[0] || input[1]) && (input[2] || input[3]));
	return;
}
float AO4_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['D']
		if ( in_pin == 3 ) {
			if (rising) {
				return 0.92;
			}
			if (!rising) {
				return 0.37;
			}
		}
		//['C']
		if ( in_pin == 2 ) {
			if (rising) {
				return 0.92;
			}
			if (!rising) {
				return 0.37;
			}
		}
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.92;
			}
			if (!rising) {
				return 0.37;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.92;
			}
			if (!rising) {
				return 0.37;
			}
		}
	}
	return 1.0;
}

void AO4P_func  (int* input, int* internal, int* output) {
	//Z : ((A+B)(C+D))'
	output[0] = !((input[0] || input[1]) && (input[2] || input[3]));
	return;
}
float AO4P_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['D']
		if ( in_pin == 3 ) {
			if (rising) {
				return 0.9;
			}
			if (!rising) {
				return 0.38;
			}
		}
		//['C']
		if ( in_pin == 2 ) {
			if (rising) {
				return 0.9;
			}
			if (!rising) {
				return 0.38;
			}
		}
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.9;
			}
			if (!rising) {
				return 0.38;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.9;
			}
			if (!rising) {
				return 0.38;
			}
		}
	}
	return 1.0;
}

void AO5_func  (int* input, int* internal, int* output) {
	//Z : ((A B)+(A C)+(B C))'
	output[0] = !((input[0] && input[1]) || (input[0] && input[2]) || (input[1] && input[2]));
	return;
}
float AO5_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['C']
		if ( in_pin == 2 ) {
			if (rising) {
				return 1.12;
			}
			if (!rising) {
				return 0.45;
			}
		}
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.12;
			}
			if (!rising) {
				return 0.45;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.12;
			}
			if (!rising) {
				return 0.45;
			}
		}
	}
	return 1.0;
}

void AO5P_func  (int* input, int* internal, int* output) {
	//Z : ((A B)+(A C)+(B C))'
	output[0] = !((input[0] && input[1]) || (input[0] && input[2]) || (input[1] && input[2]));
	return;
}
float AO5P_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['C']
		if ( in_pin == 2 ) {
			if (rising) {
				return 1.06;
			}
			if (!rising) {
				return 0.42;
			}
		}
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.06;
			}
			if (!rising) {
				return 0.42;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.06;
			}
			if (!rising) {
				return 0.42;
			}
		}
	}
	return 1.0;
}

void AO6_func  (int* input, int* internal, int* output) {
	//Z : ((A B)+C)'
	output[0] = !((input[0] && input[1]) || input[2]);
	return;
}
float AO6_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['C']
		if ( in_pin == 2 ) {
			if (rising) {
				return 0.82;
			}
			if (!rising) {
				return 0.27;
			}
		}
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.82;
			}
			if (!rising) {
				return 0.27;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.82;
			}
			if (!rising) {
				return 0.27;
			}
		}
	}
	return 1.0;
}

void AO6P_func  (int* input, int* internal, int* output) {
	//Z : ((A B)+C)'
	output[0] = !((input[0] && input[1]) || input[2]);
	return;
}
float AO6P_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['C']
		if ( in_pin == 2 ) {
			if (rising) {
				return 0.8;
			}
			if (!rising) {
				return 0.18;
			}
		}
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.8;
			}
			if (!rising) {
				return 0.18;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.8;
			}
			if (!rising) {
				return 0.18;
			}
		}
	}
	return 1.0;
}

void AO7_func  (int* input, int* internal, int* output) {
	//Z : ((A+B)C)'
	output[0] = !((input[0] || input[1]) && input[2]);
	return;
}
float AO7_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['C']
		if ( in_pin == 2 ) {
			if (rising) {
				return 0.52;
			}
			if (!rising) {
				return 0.37;
			}
		}
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.52;
			}
			if (!rising) {
				return 0.37;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.52;
			}
			if (!rising) {
				return 0.37;
			}
		}
	}
	return 1.0;
}

void AO7P_func  (int* input, int* internal, int* output) {
	//Z : ((A+B)C)'
	output[0] = !((input[0] || input[1]) && input[2]);
	return;
}
float AO7P_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['C']
		if ( in_pin == 2 ) {
			if (rising) {
				return 0.5;
			}
			if (!rising) {
				return 0.28;
			}
		}
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.5;
			}
			if (!rising) {
				return 0.28;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.5;
			}
			if (!rising) {
				return 0.28;
			}
		}
	}
	return 1.0;
}

void B1I_func  (int* input, int* internal, int* output) {
	//Z : A
	output[0] = input[0];
	return;
}
float B1I_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.55;
			}
			if (!rising) {
				return 1.10;
			}
		}
	}
	return 1.0;
}

void B2I_func  (int* input, int* internal, int* output) {
	//Z1 : A'
	output[0] = !input[0];
	//Z2 : A
	output[1] = input[0];
	return;
}
float B2I_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.72;
			}
			if (!rising) {
				return 0.40;
			}
		}
	}
	if (out_pin == 1) {
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.56;
			}
			if (!rising) {
				return 0.85;
			}
		}
	}
	return 1.0;
}

void B2IP_func  (int* input, int* internal, int* output) {
	//Z1 : A'
	output[0] = !input[0];
	//Z2 : A
	output[1] = input[0];
	return;
}
float B2IP_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.70;
			}
			if (!rising) {
				return 0.38;
			}
		}
	}
	if (out_pin == 1) {
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.63;
			}
			if (!rising) {
				return 0.82;
			}
		}
	}
	return 1.0;
}

void B3I_func  (int* input, int* internal, int* output) {
	//Z1 : A'
	output[0] = !input[0];
	//Z2 : A
	output[1] = input[0];
	return;
}
float B3I_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.49;
			}
			if (!rising) {
				return 0.17;
			}
		}
	}
	if (out_pin == 1) {
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.34;
			}
			if (!rising) {
				return 0.60;
			}
		}
	}
	return 1.0;
}

void B3IP_func  (int* input, int* internal, int* output) {
	//Z1 : A'
	output[0] = !input[0];
	//Z2 : A
	output[1] = input[0];
	return;
}
float B3IP_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.40;
			}
			if (!rising) {
				return 0.18;
			}
		}
	}
	if (out_pin == 1) {
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.35;
			}
			if (!rising) {
				return 0.54;
			}
		}
	}
	return 1.0;
}

void B4I_func  (int* input, int* internal, int* output) {
	//Z : A'
	output[0] = !input[0];
	return;
}
float B4I_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.35;
			}
			if (!rising) {
				return 0.11;
			}
		}
	}
	return 1.0;
}

void B4IP_func  (int* input, int* internal, int* output) {
	//Z : A'
	output[0] = !input[0];
	return;
}
float B4IP_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.35;
			}
			if (!rising) {
				return 0.02;
			}
		}
	}
	return 1.0;
}

void B5I_func  (int* input, int* internal, int* output) {
	//Z : A'
	output[0] = !input[0];
	return;
}
float B5I_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.36;
			}
			if (!rising) {
				return 0.12;
			}
		}
	}
	return 1.0;
}

void B5IP_func  (int* input, int* internal, int* output) {
	//Z : A'
	output[0] = !input[0];
	return;
}
float B5IP_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.33;
			}
			if (!rising) {
				return 0.16;
			}
		}
	}
	return 1.0;
}

void BTS4_func  (int* input, int* internal, int* output) {
	//Z : A
	output[0] = input[0];
	return;
}
float BTS4_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.39;
			}
			if (!rising) {
				return 0.75;
			}
		}
		//['E']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.39;
			}
			if (!rising) {
				return 0.75;
			}
		}
	}
	return 1.0;
}

void BTS4P_func  (int* input, int* internal, int* output) {
	//Z : A
	output[0] = input[0];
	return;
}
float BTS4P_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.34;
			}
			if (!rising) {
				return 0.74;
			}
		}
		//['E']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.34;
			}
			if (!rising) {
				return 0.74;
			}
		}
	}
	return 1.0;
}

void BTS5_func  (int* input, int* internal, int* output) {
	//Z : A'
	output[0] = !input[0];
	return;
}
float BTS5_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.89;
			}
			if (!rising) {
				return 0.65;
			}
		}
		//['E']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.89;
			}
			if (!rising) {
				return 0.65;
			}
		}
	}
	return 1.0;
}

void BTS5P_func  (int* input, int* internal, int* output) {
	//Z : A'
	output[0] = !input[0];
	return;
}
float BTS5P_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.00;
			}
			if (!rising) {
				return 0.75;
			}
		}
		//['E']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.00;
			}
			if (!rising) {
				return 0.75;
			}
		}
	}
	return 1.0;
}

void D24L_func  (int* input, int* internal, int* output) {
	//Z0 : A B' + A' B + A B
	output[0] = input[0] && !input[1] || !input[0] && input[1] || input[0] && input[1];
	//Z1 : A' B' + A' B + A B
	output[1] = !input[0] && !input[1] || !input[0] && input[1] || input[0] && input[1];
	//Z2 : A' B' + A B' + A B
	output[2] = !input[0] && !input[1] || input[0] && !input[1] || input[0] && input[1];
	//Z3 : A' B' + A B' + A' B
	output[3] = !input[0] && !input[1] || input[0] && !input[1] || !input[0] && input[1];
	return;
}
float D24L_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.48;
			}
			if (!rising) {
				return 0.73;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.48;
			}
			if (!rising) {
				return 0.73;
			}
		}
	}
	if (out_pin == 1) {
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.48;
			}
			if (!rising) {
				return 0.73;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.48;
			}
			if (!rising) {
				return 0.73;
			}
		}
	}
	if (out_pin == 2) {
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.48;
			}
			if (!rising) {
				return 0.73;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.48;
			}
			if (!rising) {
				return 0.73;
			}
		}
	}
	if (out_pin == 3) {
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.50;
			}
			if (!rising) {
				return 0.13;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.50;
			}
			if (!rising) {
				return 0.13;
			}
		}
	}
	return 1.0;
}

void D24LP_func  (int* input, int* internal, int* output) {
	//Z0 : A B' + A' B + A B
	output[0] = input[0] && !input[1] || !input[0] && input[1] || input[0] && input[1];
	//Z1 : A' B' + A' B + A B
	output[1] = !input[0] && !input[1] || !input[0] && input[1] || input[0] && input[1];
	//Z2 : A' B' + A B' + A B
	output[2] = !input[0] && !input[1] || input[0] && !input[1] || input[0] && input[1];
	//Z3 : A' B' + A B' + A' B
	output[3] = !input[0] && !input[1] || input[0] && !input[1] || !input[0] && input[1];
	return;
}
float D24LP_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.60;
			}
			if (!rising) {
				return 0.96;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.60;
			}
			if (!rising) {
				return 0.96;
			}
		}
	}
	if (out_pin == 1) {
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.60;
			}
			if (!rising) {
				return 0.96;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.60;
			}
			if (!rising) {
				return 0.96;
			}
		}
	}
	if (out_pin == 2) {
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.60;
			}
			if (!rising) {
				return 0.96;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.60;
			}
			if (!rising) {
				return 0.96;
			}
		}
	}
	if (out_pin == 3) {
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.50;
			}
			if (!rising) {
				return 0.16;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.50;
			}
			if (!rising) {
				return 0.16;
			}
		}
	}
	return 1.0;
}

void EN_func  (int* input, int* internal, int* output) {
	//Z : (A B+A'B')
	output[0] = (input[0] && input[1] || !input[0] && !input[1]);
	return;
}
float EN_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.79;
			}
			if (!rising) {
				return 1.06;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.79;
			}
			if (!rising) {
				return 1.06;
			}
		}
	}
	return 1.0;
}

void EN3_func  (int* input, int* internal, int* output) {
	//Z : (A'B'C'+A'B C+A B'C+A B C')
	output[0] = (!input[0] && !input[1] && !input[2] || !input[0] && input[1] && input[2] || input[0] && !input[1] && input[2] || input[0] && input[1] && !input[2]);
	return;
}
float EN3_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['C']
		if ( in_pin == 2 ) {
			if (rising) {
				return 1.68;
			}
			if (!rising) {
				return 1.85;
			}
		}
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.68;
			}
			if (!rising) {
				return 1.85;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.68;
			}
			if (!rising) {
				return 1.85;
			}
		}
	}
	return 1.0;
}

void EN3P_func  (int* input, int* internal, int* output) {
	//Z : (A'B'C'+A'B C+A B'C+A B C')
	output[0] = (!input[0] && !input[1] && !input[2] || !input[0] && input[1] && input[2] || input[0] && !input[1] && input[2] || input[0] && input[1] && !input[2]);
	return;
}
float EN3P_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['C']
		if ( in_pin == 2 ) {
			if (rising) {
				return 1.65;
			}
			if (!rising) {
				return 1.94;
			}
		}
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.65;
			}
			if (!rising) {
				return 1.94;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.65;
			}
			if (!rising) {
				return 1.94;
			}
		}
	}
	return 1.0;
}

void ENP_func  (int* input, int* internal, int* output) {
	//Z : (A B+A'B')
	output[0] = (input[0] && input[1] || !input[0] && !input[1]);
	return;
}
float ENP_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.84;
			}
			if (!rising) {
				return 1.05;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.84;
			}
			if (!rising) {
				return 1.05;
			}
		}
	}
	return 1.0;
}

void EO_func  (int* input, int* internal, int* output) {
	//Z : (A B'+A'B)
	output[0] = (input[0] && !input[1] || !input[0] && input[1]);
	return;
}
float EO_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.79;
			}
			if (!rising) {
				return 1.06;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.79;
			}
			if (!rising) {
				return 1.06;
			}
		}
	}
	return 1.0;
}

void EO1_func  (int* input, int* internal, int* output) {
	//Z : ((A B)+((C+D)'))'
	output[0] = !((input[0] && input[1]) || (!(input[2] || input[3])));
	return;
}
float EO1_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['D']
		if ( in_pin == 3 ) {
			if (rising) {
				return 0.82;
			}
			if (!rising) {
				return 0.97;
			}
		}
		//['C']
		if ( in_pin == 2 ) {
			if (rising) {
				return 0.82;
			}
			if (!rising) {
				return 0.97;
			}
		}
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.82;
			}
			if (!rising) {
				return 0.97;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.82;
			}
			if (!rising) {
				return 0.97;
			}
		}
	}
	return 1.0;
}

void EO1P_func  (int* input, int* internal, int* output) {
	//Z : ((A B)+((C+D)'))'
	output[0] = !((input[0] && input[1]) || (!(input[2] || input[3])));
	return;
}
float EO1P_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['D']
		if ( in_pin == 3 ) {
			if (rising) {
				return 1;
			}
			if (!rising) {
				return 0.88;
			}
		}
		//['C']
		if ( in_pin == 2 ) {
			if (rising) {
				return 1;
			}
			if (!rising) {
				return 0.88;
			}
		}
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1;
			}
			if (!rising) {
				return 0.88;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1;
			}
			if (!rising) {
				return 0.88;
			}
		}
	}
	return 1.0;
}

void EO3_func  (int* input, int* internal, int* output) {
	//Z : (A'B'C+A'B C'+A B'C'+A B C)
	output[0] = (!input[0] && !input[1] && input[2] || !input[0] && input[1] && !input[2] || input[0] && !input[1] && !input[2] || input[0] && input[1] && input[2]);
	return;
}
float EO3_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['C']
		if ( in_pin == 2 ) {
			if (rising) {
				return 1.68;
			}
			if (!rising) {
				return 1.85;
			}
		}
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.68;
			}
			if (!rising) {
				return 1.85;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.68;
			}
			if (!rising) {
				return 1.85;
			}
		}
	}
	return 1.0;
}

void EO3P_func  (int* input, int* internal, int* output) {
	//Z : (A'B'C+A'B C'+A B'C'+A B C)
	output[0] = (!input[0] && !input[1] && input[2] || !input[0] && input[1] && !input[2] || input[0] && !input[1] && !input[2] || input[0] && input[1] && input[2]);
	return;
}
float EO3P_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['C']
		if ( in_pin == 2 ) {
			if (rising) {
				return 1.65;
			}
			if (!rising) {
				return 1.94;
			}
		}
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.65;
			}
			if (!rising) {
				return 1.94;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.65;
			}
			if (!rising) {
				return 1.94;
			}
		}
	}
	return 1.0;
}

void EON1_func  (int* input, int* internal, int* output) {
	//Z : ((A+B)((C D)'))'
	output[0] = !((input[0] || input[1]) && (!(input[2] && input[3])));
	return;
}
float EON1_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['D']
		if ( in_pin == 3 ) {
			if (rising) {
				return 0.82;
			}
			if (!rising) {
				return 0.87;
			}
		}
		//['C']
		if ( in_pin == 2 ) {
			if (rising) {
				return 0.82;
			}
			if (!rising) {
				return 0.87;
			}
		}
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.82;
			}
			if (!rising) {
				return 0.87;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.82;
			}
			if (!rising) {
				return 0.87;
			}
		}
	}
	return 1.0;
}

void EON1P_func  (int* input, int* internal, int* output) {
	//Z : ((A+B)((C D)'))'
	output[0] = !((input[0] || input[1]) && (!(input[2] && input[3])));
	return;
}
float EON1P_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['D']
		if ( in_pin == 3 ) {
			if (rising) {
				return 1;
			}
			if (!rising) {
				return 0.88;
			}
		}
		//['C']
		if ( in_pin == 2 ) {
			if (rising) {
				return 1;
			}
			if (!rising) {
				return 0.88;
			}
		}
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1;
			}
			if (!rising) {
				return 0.88;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1;
			}
			if (!rising) {
				return 0.88;
			}
		}
	}
	return 1.0;
}

void EOP_func  (int* input, int* internal, int* output) {
	//Z : (A B'+A'B)
	output[0] = (input[0] && !input[1] || !input[0] && input[1]);
	return;
}
float EOP_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.84;
			}
			if (!rising) {
				return 1.05;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.84;
			}
			if (!rising) {
				return 1.05;
			}
		}
	}
	return 1.0;
}

void FA1_func  (int* input, int* internal, int* output) {
	//CO : CI A B' + CI A' B + CI' A B + CI A B
	output[0] = input[2] && input[0] && !input[1] || input[2] && !input[0] && input[1] || !input[2] && input[0] && input[1] || input[2] && input[0] && input[1];
	//S : CI A' B' + CI' A B' + CI' A' B + CI A B
	output[1] = input[2] && !input[0] && !input[1] || !input[2] && input[0] && !input[1] || !input[2] && !input[0] && input[1] || input[2] && input[0] && input[1];
	return;
}
float FA1_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['CI']
		if ( in_pin == 2 ) {
			if (rising) {
				return 0.79;
			}
			if (!rising) {
				return 1.34;
			}
		}
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.79;
			}
			if (!rising) {
				return 1.34;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.79;
			}
			if (!rising) {
				return 1.34;
			}
		}
	}
	if (out_pin == 1) {
		//['CI']
		if ( in_pin == 2 ) {
			if (rising) {
				return 0.78;
			}
			if (!rising) {
				return 0.64;
			}
		}
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.88;
			}
			if (!rising) {
				return 1.94;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.88;
			}
			if (!rising) {
				return 1.94;
			}
		}
	}
	return 1.0;
}

void FA1A_func  (int* input, int* internal, int* output) {
	//CO : CI A B' + CI A' B + CI' A B + CI A B
	output[0] = input[2] && input[0] && !input[1] || input[2] && !input[0] && input[1] || !input[2] && input[0] && input[1] || input[2] && input[0] && input[1];
	//S : CI A' B' + CI' A B' + CI' A' B + CI A B
	output[1] = input[2] && !input[0] && !input[1] || !input[2] && input[0] && !input[1] || !input[2] && !input[0] && input[1] || input[2] && input[0] && input[1];
	return;
}
float FA1A_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['CI']
		if ( in_pin == 2 ) {
			if (rising) {
				return 0.79;
			}
			if (!rising) {
				return 1.04;
			}
		}
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.89;
			}
			if (!rising) {
				return 2.14;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.89;
			}
			if (!rising) {
				return 2.14;
			}
		}
	}
	if (out_pin == 1) {
		//['CI']
		if ( in_pin == 2 ) {
			if (rising) {
				return 0.89;
			}
			if (!rising) {
				return 0.76;
			}
		}
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.99;
			}
			if (!rising) {
				return 1.86;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.99;
			}
			if (!rising) {
				return 1.86;
			}
		}
	}
	return 1.0;
}

void FA1AP_func  (int* input, int* internal, int* output) {
	//CO : CI A B' + CI A' B + CI' A B + CI A B
	output[0] = input[2] && input[0] && !input[1] || input[2] && !input[0] && input[1] || !input[2] && input[0] && input[1] || input[2] && input[0] && input[1];
	//S : CI A' B' + CI' A B' + CI' A' B + CI A B
	output[1] = input[2] && !input[0] && !input[1] || !input[2] && input[0] && !input[1] || !input[2] && !input[0] && input[1] || input[2] && input[0] && input[1];
	return;
}
float FA1AP_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['CI']
		if ( in_pin == 2 ) {
			if (rising) {
				return 0.94;
			}
			if (!rising) {
				return 1.15;
			}
		}
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 2.04;
			}
			if (!rising) {
				return 2.25;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 2.04;
			}
			if (!rising) {
				return 2.25;
			}
		}
	}
	if (out_pin == 1) {
		//['CI']
		if ( in_pin == 2 ) {
			if (rising) {
				return 0.94;
			}
			if (!rising) {
				return 0.85;
			}
		}
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 2.04;
			}
			if (!rising) {
				return 1.95;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 2.04;
			}
			if (!rising) {
				return 1.95;
			}
		}
	}
	return 1.0;
}

void FA1P_func  (int* input, int* internal, int* output) {
	//CO : CI A B' + CI A' B + CI' A B + CI A B
	output[0] = input[2] && input[0] && !input[1] || input[2] && !input[0] && input[1] || !input[2] && input[0] && input[1] || input[2] && input[0] && input[1];
	//S : CI A' B' + CI' A B' + CI' A' B + CI A B
	output[1] = input[2] && !input[0] && !input[1] || !input[2] && input[0] && !input[1] || !input[2] && !input[0] && input[1] || input[2] && input[0] && input[1];
	return;
}
float FA1P_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['CI']
		if ( in_pin == 2 ) {
			if (rising) {
				return 0.84;
			}
			if (!rising) {
				return 1.43;
			}
		}
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.84;
			}
			if (!rising) {
				return 1.43;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.84;
			}
			if (!rising) {
				return 1.43;
			}
		}
	}
	if (out_pin == 1) {
		//['CI']
		if ( in_pin == 2 ) {
			if (rising) {
				return 0.84;
			}
			if (!rising) {
				return 0.65;
			}
		}
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 2.04;
			}
			if (!rising) {
				return 1.95;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 2.04;
			}
			if (!rising) {
				return 1.95;
			}
		}
	}
	return 1.0;
}

int FD1_ff (int* input, int* internal, int* output) {
	//clocked_on = CP
	//next_state = D
	if (input[0]) {
		internal[0] = input[1];
		internal[1] = LOGIC_NOT(internal[0]);
		return 1;
	}
	return 1;
}

void FD1_func  (int* input, int* internal, int* output) {
	FD1_ff(input, internal, output);
	//Q : IQ
	output[0] = internal[0];
	//QN : IQN
	output[1] = internal[1];
	return;
}
float FD1_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['CP']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.09;
			}
			if (!rising) {
				return 1.37;
			}
		}
	}
	if (out_pin == 1) {
		//['CP']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.59;
			}
			if (!rising) {
				return 1.57;
			}
		}
	}
	return 1.0;
}

int FD1P_ff (int* input, int* internal, int* output) {
	//clocked_on = CP
	//next_state = D
	if (input[0]) {
		internal[0] = input[1];
		internal[1] = LOGIC_NOT(internal[0]);
		return 1;
	}
	return 1;
}

void FD1P_func  (int* input, int* internal, int* output) {
	FD1P_ff(input, internal, output);
	//Q : IQ
	output[0] = internal[0];
	//QN : IQN
	output[1] = internal[1];
	return;
}
float FD1P_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['CP']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.16;
			}
			if (!rising) {
				return 1.44;
			}
		}
	}
	if (out_pin == 1) {
		//['CP']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.84;
			}
			if (!rising) {
				return 1.74;
			}
		}
	}
	return 1.0;
}

int FD1S_ff (int* input, int* internal, int* output) {
	//clocked_on = CP
	//next_state =  D TE' + TI TE 
	if (input[0]) {
		internal[0] = input[1] && !input[2] || input[3] && input[2];
		internal[1] = LOGIC_NOT(internal[0]);
		return 1;
	}
	return 1;
}

void FD1S_func  (int* input, int* internal, int* output) {
	FD1S_ff(input, internal, output);
	//Q : IQ
	output[0] = internal[0];
	//QN : IQN
	output[1] = internal[1];
	return;
}
float FD1S_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['CP']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.09;
			}
			if (!rising) {
				return 1.37;
			}
		}
	}
	if (out_pin == 1) {
		//['CP']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.59;
			}
			if (!rising) {
				return 1.57;
			}
		}
	}
	return 1.0;
}

int FD1SP_ff (int* input, int* internal, int* output) {
	//clocked_on = CP
	//next_state =  D TE' + TI TE 
	if (input[0]) {
		internal[0] = input[1] && !input[2] || input[3] && input[2];
		internal[1] = LOGIC_NOT(internal[0]);
		return 1;
	}
	return 1;
}

void FD1SP_func  (int* input, int* internal, int* output) {
	FD1SP_ff(input, internal, output);
	//Q : IQ
	output[0] = internal[0];
	//QN : IQN
	output[1] = internal[1];
	return;
}
float FD1SP_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['CP']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.16;
			}
			if (!rising) {
				return 1.44;
			}
		}
	}
	if (out_pin == 1) {
		//['CP']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.84;
			}
			if (!rising) {
				return 1.74;
			}
		}
	}
	return 1.0;
}

int FD2_ff (int* input, int* internal, int* output) {
	//clear = CD'
	if (!input[0]) {
		internal[0] = 0;
		internal[1] = 1;
		return 1;
	}
	//clocked_on = CP
	//next_state = D
	if (input[1]) {
		internal[0] = input[2];
		internal[1] = LOGIC_NOT(internal[0]);
		return 1;
	}
	return 1;
}

void FD2_func  (int* input, int* internal, int* output) {
	FD2_ff(input, internal, output);
	//Q : IQ
	output[0] = internal[0];
	//QN : IQN
	output[1] = internal[1];
	return;
}
float FD2_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['CD']
		if ( in_pin == 0 ) {
			if (!rising) {
				return 0.77;
			}
		}
		//['CP']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.19;
			}
			if (!rising) {
				return 1.37;
			}
		}
	}
	if (out_pin == 1) {
		//['CD']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.87;
			}
		}
		//['CP']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.47;
			}
			if (!rising) {
				return 1.67;
			}
		}
	}
	return 1.0;
}

int FD2P_ff (int* input, int* internal, int* output) {
	//clear = CD'
	if (!input[0]) {
		internal[0] = 0;
		internal[1] = 1;
		return 1;
	}
	//clocked_on = CP
	//next_state = D
	if (input[1]) {
		internal[0] = input[2];
		internal[1] = LOGIC_NOT(internal[0]);
		return 1;
	}
	return 1;
}

void FD2P_func  (int* input, int* internal, int* output) {
	FD2P_ff(input, internal, output);
	//Q : IQ
	output[0] = internal[0];
	//QN : IQN
	output[1] = internal[1];
	return;
}
float FD2P_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['CD']
		if ( in_pin == 0 ) {
			if (!rising) {
				return 0.74;
			}
		}
		//['CP']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.34;
			}
			if (!rising) {
				return 1.34;
			}
		}
	}
	if (out_pin == 1) {
		//['CD']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.16;
			}
		}
		//['CP']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.76;
			}
			if (!rising) {
				return 1.96;
			}
		}
	}
	return 1.0;
}

int FD2S_ff (int* input, int* internal, int* output) {
	//clear = CD'
	if (!input[0]) {
		internal[0] = 0;
		internal[1] = 1;
		return 1;
	}
	//clocked_on = CP
	//next_state =  D TE' + TI TE
	if (input[1]) {
		internal[0] = input[2] && !input[3] || input[4] && input[3];
		internal[1] = LOGIC_NOT(internal[0]);
		return 1;
	}
	return 1;
}

void FD2S_func  (int* input, int* internal, int* output) {
	FD2S_ff(input, internal, output);
	//Q : IQ
	output[0] = internal[0];
	//QN : IQN
	output[1] = internal[1];
	return;
}
float FD2S_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['CD']
		if ( in_pin == 0 ) {
			if (!rising) {
				return 0.77;
			}
		}
		//['CP']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.19;
			}
			if (!rising) {
				return 1.37;
			}
		}
	}
	if (out_pin == 1) {
		//['CD']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.87;
			}
		}
		//['CP']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.47;
			}
			if (!rising) {
				return 1.67;
			}
		}
	}
	return 1.0;
}

int FD2SP_ff (int* input, int* internal, int* output) {
	//clear = CD'
	if (!input[0]) {
		internal[0] = 0;
		internal[1] = 1;
		return 1;
	}
	//clocked_on = CP
	//next_state =  D TE' + TI TE
	if (input[1]) {
		internal[0] = input[2] && !input[3] || input[4] && input[3];
		internal[1] = LOGIC_NOT(internal[0]);
		return 1;
	}
	return 1;
}

void FD2SP_func  (int* input, int* internal, int* output) {
	FD2SP_ff(input, internal, output);
	//Q : IQ
	output[0] = internal[0];
	//QN : IQN
	output[1] = internal[1];
	return;
}
float FD2SP_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['CD']
		if ( in_pin == 0 ) {
			if (!rising) {
				return 0.74;
			}
		}
		//['CP']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.34;
			}
			if (!rising) {
				return 1.34;
			}
		}
	}
	if (out_pin == 1) {
		//['CD']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.16;
			}
		}
		//['CP']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.76;
			}
			if (!rising) {
				return 1.96;
			}
		}
	}
	return 1.0;
}

int FD2TS_ff (int* input, int* internal, int* output) {
	//clear = CD'
	if (!input[0]) {
		internal[0] = 0;
		internal[1] = 1;
		return 1;
	}
	//clocked_on = CP
	//next_state = D
	if (input[1]) {
		internal[0] = input[2];
		internal[1] = LOGIC_NOT(internal[0]);
		return 1;
	}
	return 1;
}

void FD2TS_func  (int* input, int* internal, int* output) {
	FD2TS_ff(input, internal, output);
	//Q : IQ
	output[0] = internal[0];
	//Z : IQ
	output[1] = internal[0];
	return;
}
float FD2TS_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['CD']
		if ( in_pin == 0 ) {
			if (!rising) {
				return 0.0;
			}
		}
		//['CP']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.43;
			}
			if (!rising) {
				return 1.42;
			}
		}
	}
	if (out_pin == 1) {
		//['CD']
		if ( in_pin == 0 ) {
			if (!rising) {
				return 0.0;
			}
		}
		//['CP']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.93;
			}
			if (!rising) {
				return 1.67;
			}
		}
		//['RD']
		if ( in_pin == 3 ) {
			if (rising) {
				return 0.50;
			}
			if (!rising) {
				return 0.25;
			}
		}
	}
	return 1.0;
}

int FD2TSP_ff (int* input, int* internal, int* output) {
	//clear = CD'
	if (!input[0]) {
		internal[0] = 0;
		internal[1] = 1;
		return 1;
	}
	//clocked_on = CP
	//next_state = D
	if (input[1]) {
		internal[0] = input[2];
		internal[1] = LOGIC_NOT(internal[0]);
		return 1;
	}
	return 1;
}

void FD2TSP_func  (int* input, int* internal, int* output) {
	FD2TSP_ff(input, internal, output);
	//Z : IQ
	output[0] = internal[0];
	return;
}
float FD2TSP_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['CD']
		if ( in_pin == 0 ) {
			if (!rising) {
				return 0.0;
			}
		}
		//['CP']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.85;
			}
			if (!rising) {
				return 1.82;
			}
		}
		//['RD']
		if ( in_pin == 3 ) {
			if (rising) {
				return 0.41;
			}
			if (!rising) {
				return 0.35;
			}
		}
	}
	return 1.0;
}

int FD3_ff (int* input, int* internal, int* output) {
	//clear and preset
	//clear_preset_var1 = L
	//clear_preset_var2 = L
	if ( (!input[0]) && (!input[3]) ) {
		internal[0] = 0;
		internal[1] = 0;
		return 1;
	}
	//preset = SD'
	if (!input[3]) {
		internal[0] = 1;
		internal[1] = 0;
		return 1;
	}
	//clear = CD'
	if (!input[0]) {
		internal[0] = 0;
		internal[1] = 1;
		return 1;
	}
	//clocked_on = CP
	//next_state = D
	if (input[1]) {
		internal[0] = input[2];
		internal[1] = LOGIC_NOT(internal[0]);
		return 1;
	}
	return 1;
}

void FD3_func  (int* input, int* internal, int* output) {
	FD3_ff(input, internal, output);
	//Q : IQ
	output[0] = internal[0];
	//QN : IQN
	output[1] = internal[1];
	return;
}
float FD3_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['CD']
		if ( in_pin == 0 ) {
			if (!rising) {
				return 0.75;
			}
		}
		//['CP']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.17;
			}
			if (!rising) {
				return 1.35;
			}
		}
		//['SD']
		if ( in_pin == 3 ) {
			if (rising) {
				return 0.97;
			}
		}
	}
	if (out_pin == 1) {
		//['CD']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.09;
			}
		}
		//['CP']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.69;
			}
			if (!rising) {
				return 1.67;
			}
		}
		//['SD']
		if ( in_pin == 3 ) {
			if (!rising) {
				return 0.77;
			}
		}
	}
	return 1.0;
}

int FD3P_ff (int* input, int* internal, int* output) {
	//clear and preset
	//clear_preset_var1 = L
	//clear_preset_var2 = L
	if ( (!input[0]) && (!input[3]) ) {
		internal[0] = 0;
		internal[1] = 0;
		return 1;
	}
	//preset = SD'
	if (!input[3]) {
		internal[0] = 1;
		internal[1] = 0;
		return 1;
	}
	//clear = CD'
	if (!input[0]) {
		internal[0] = 0;
		internal[1] = 1;
		return 1;
	}
	//clocked_on = CP
	//next_state = D
	if (input[1]) {
		internal[0] = input[2];
		internal[1] = LOGIC_NOT(internal[0]);
		return 1;
	}
	return 1;
}

void FD3P_func  (int* input, int* internal, int* output) {
	FD3P_ff(input, internal, output);
	//Q : IQ
	output[0] = internal[0];
	//QN : IQN
	output[1] = internal[1];
	return;
}
float FD3P_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['CD']
		if ( in_pin == 0 ) {
			if (!rising) {
				return 0.94;
			}
		}
		//['CP']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.34;
			}
			if (!rising) {
				return 1.54;
			}
		}
		//['SD']
		if ( in_pin == 3 ) {
			if (rising) {
				return 1.19;
			}
		}
	}
	if (out_pin == 1) {
		//['CD']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.44;
			}
		}
		//['CP']
		if ( in_pin == 1 ) {
			if (rising) {
				return 2.04;
			}
			if (!rising) {
				return 1.94;
			}
		}
		//['SD']
		if ( in_pin == 3 ) {
			if (!rising) {
				return 0.89;
			}
		}
	}
	return 1.0;
}

int FD3S_ff (int* input, int* internal, int* output) {
	//clear and preset
	//clear_preset_var1 = L
	//clear_preset_var2 = L
	if ( (!input[0]) && (!input[3]) ) {
		internal[0] = 0;
		internal[1] = 0;
		return 1;
	}
	//preset = SD'
	if (!input[3]) {
		internal[0] = 1;
		internal[1] = 0;
		return 1;
	}
	//clear = CD'
	if (!input[0]) {
		internal[0] = 0;
		internal[1] = 1;
		return 1;
	}
	//clocked_on = CP
	//next_state = D TE'+ TI TE
	if (input[1]) {
		internal[0] = input[2] && !input[4] || input[5] && input[4];
		internal[1] = LOGIC_NOT(internal[0]);
		return 1;
	}
	return 1;
}

void FD3S_func  (int* input, int* internal, int* output) {
	FD3S_ff(input, internal, output);
	//Q : IQ
	output[0] = internal[0];
	//QN : IQN
	output[1] = internal[1];
	return;
}
float FD3S_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['CD']
		if ( in_pin == 0 ) {
			if (!rising) {
				return 0.75;
			}
		}
		//['CP']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.17;
			}
			if (!rising) {
				return 1.35;
			}
		}
		//['SD']
		if ( in_pin == 3 ) {
			if (rising) {
				return 0.97;
			}
		}
	}
	if (out_pin == 1) {
		//['CD']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.09;
			}
		}
		//['CP']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.69;
			}
			if (!rising) {
				return 1.67;
			}
		}
		//['SD']
		if ( in_pin == 3 ) {
			if (!rising) {
				return 0.77;
			}
		}
	}
	return 1.0;
}

int FD3SP_ff (int* input, int* internal, int* output) {
	//clear and preset
	//clear_preset_var1 = L
	//clear_preset_var2 = L
	if ( (!input[0]) && (!input[3]) ) {
		internal[0] = 0;
		internal[1] = 0;
		return 1;
	}
	//preset = SD'
	if (!input[3]) {
		internal[0] = 1;
		internal[1] = 0;
		return 1;
	}
	//clear = CD'
	if (!input[0]) {
		internal[0] = 0;
		internal[1] = 1;
		return 1;
	}
	//clocked_on = CP
	//next_state = D TE' + TI TE
	if (input[1]) {
		internal[0] = input[2] && !input[4] || input[5] && input[4];
		internal[1] = LOGIC_NOT(internal[0]);
		return 1;
	}
	return 1;
}

void FD3SP_func  (int* input, int* internal, int* output) {
	FD3SP_ff(input, internal, output);
	//Q : IQ
	output[0] = internal[0];
	//QN : IQN
	output[1] = internal[1];
	return;
}
float FD3SP_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['CD']
		if ( in_pin == 0 ) {
			if (!rising) {
				return 0.94;
			}
		}
		//['CP']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.34;
			}
			if (!rising) {
				return 1.54;
			}
		}
		//['SD']
		if ( in_pin == 3 ) {
			if (rising) {
				return 1.19;
			}
		}
	}
	if (out_pin == 1) {
		//['CD']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.44;
			}
		}
		//['CP']
		if ( in_pin == 1 ) {
			if (rising) {
				return 2.04;
			}
			if (!rising) {
				return 1.94;
			}
		}
		//['SD']
		if ( in_pin == 3 ) {
			if (!rising) {
				return 0.89;
			}
		}
	}
	return 1.0;
}

int FD4_ff (int* input, int* internal, int* output) {
	//preset = SD'
	if (!input[2]) {
		internal[0] = 1;
		internal[1] = 0;
		return 1;
	}
	//clocked_on = CP
	//next_state = D
	if (input[0]) {
		internal[0] = input[1];
		internal[1] = LOGIC_NOT(internal[0]);
		return 1;
	}
	return 1;
}

void FD4_func  (int* input, int* internal, int* output) {
	FD4_ff(input, internal, output);
	//Q : IQ
	output[0] = internal[0];
	//QN : IQN
	output[1] = internal[1];
	return;
}
float FD4_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['SD']
		if ( in_pin == 2 ) {
			if (rising) {
				return 0.89;
			}
		}
		//['CP']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.09;
			}
			if (!rising) {
				return 1.45;
			}
		}
	}
	if (out_pin == 1) {
		//['SD']
		if ( in_pin == 2 ) {
			if (!rising) {
				return 0.72;
			}
		}
		//['CP']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.79;
			}
			if (!rising) {
				return 1.57;
			}
		}
	}
	return 1.0;
}

int FD4P_ff (int* input, int* internal, int* output) {
	//preset = SD'
	if (!input[2]) {
		internal[0] = 1;
		internal[1] = 0;
		return 1;
	}
	//clocked_on = CP
	//next_state = D
	if (input[0]) {
		internal[0] = input[1];
		internal[1] = LOGIC_NOT(internal[0]);
		return 1;
	}
	return 1;
}

void FD4P_func  (int* input, int* internal, int* output) {
	FD4P_ff(input, internal, output);
	//Q : IQ
	output[0] = internal[0];
	//QN : IQN
	output[1] = internal[1];
	return;
}
float FD4P_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['SD']
		if ( in_pin == 2 ) {
			if (rising) {
				return 1.01;
			}
		}
		//['CP']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.16;
			}
			if (!rising) {
				return 1.44;
			}
		}
	}
	if (out_pin == 1) {
		//['SD']
		if ( in_pin == 2 ) {
			if (!rising) {
				return 0.74;
			}
		}
		//['CP']
		if ( in_pin == 0 ) {
			if (rising) {
				return 2.04;
			}
			if (!rising) {
				return 1.74;
			}
		}
	}
	return 1.0;
}

int FD4S_ff (int* input, int* internal, int* output) {
	//preset = SD'
	if (!input[2]) {
		internal[0] = 1;
		internal[1] = 0;
		return 1;
	}
	//clocked_on = CP
	//next_state = D TE' + TI TE
	if (input[0]) {
		internal[0] = input[1] && !input[3] || input[4] && input[3];
		internal[1] = LOGIC_NOT(internal[0]);
		return 1;
	}
	return 1;
}

void FD4S_func  (int* input, int* internal, int* output) {
	FD4S_ff(input, internal, output);
	//Q : IQ
	output[0] = internal[0];
	//QN : IQN
	output[1] = internal[1];
	return;
}
float FD4S_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['SD']
		if ( in_pin == 2 ) {
			if (rising) {
				return 0.89;
			}
		}
		//['CP']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.09;
			}
			if (!rising) {
				return 1.45;
			}
		}
	}
	if (out_pin == 1) {
		//['SD']
		if ( in_pin == 2 ) {
			if (!rising) {
				return 0.72;
			}
		}
		//['CP']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.79;
			}
			if (!rising) {
				return 1.57;
			}
		}
	}
	return 1.0;
}

int FD4SP_ff (int* input, int* internal, int* output) {
	//preset = SD'
	if (!input[2]) {
		internal[0] = 1;
		internal[1] = 0;
		return 1;
	}
	//clocked_on = CP
	//next_state = D TE' + TI TE
	if (input[0]) {
		internal[0] = input[1] && !input[3] || input[4] && input[3];
		internal[1] = LOGIC_NOT(internal[0]);
		return 1;
	}
	return 1;
}

void FD4SP_func  (int* input, int* internal, int* output) {
	FD4SP_ff(input, internal, output);
	//Q : IQ
	output[0] = internal[0];
	//QN : IQN
	output[1] = internal[1];
	return;
}
float FD4SP_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['SD']
		if ( in_pin == 2 ) {
			if (rising) {
				return 1.01;
			}
		}
		//['CP']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.16;
			}
			if (!rising) {
				return 1.44;
			}
		}
	}
	if (out_pin == 1) {
		//['SD']
		if ( in_pin == 2 ) {
			if (!rising) {
				return 0.74;
			}
		}
		//['CP']
		if ( in_pin == 0 ) {
			if (rising) {
				return 2.04;
			}
			if (!rising) {
				return 1.74;
			}
		}
	}
	return 1.0;
}

int FDS2_ff (int* input, int* internal, int* output) {
	//clocked_on = CP
	//next_state = D CR
	if (input[0]) {
		internal[0] = input[2] && input[1];
		internal[1] = LOGIC_NOT(internal[0]);
		return 1;
	}
	return 1;
}

void FDS2_func  (int* input, int* internal, int* output) {
	FDS2_ff(input, internal, output);
	//Q : IQ
	output[0] = internal[0];
	//QN : IQN
	output[1] = internal[1];
	return;
}
float FDS2_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['CP']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.09;
			}
			if (!rising) {
				return 1.27;
			}
		}
	}
	if (out_pin == 1) {
		//['CP']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.49;
			}
			if (!rising) {
				return 1.57;
			}
		}
	}
	return 1.0;
}

int FDS2L_ff (int* input, int* internal, int* output) {
	//clocked_on = CP
	//next_state = CR (D LD + IQ LD')
	if (input[0]) {
		internal[0] = input[1] && (input[2] && input[3] || internal[0] && !input[3]);
		internal[1] = LOGIC_NOT(internal[0]);
		return 1;
	}
	return 1;
}

void FDS2L_func  (int* input, int* internal, int* output) {
	FDS2L_ff(input, internal, output);
	//Q : IQ
	output[0] = internal[0];
	//QN : IQN
	output[1] = internal[1];
	return;
}
float FDS2L_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['CP']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.09;
			}
			if (!rising) {
				return 1.25;
			}
		}
	}
	if (out_pin == 1) {
		//['CP']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.47;
			}
			if (!rising) {
				return 1.55;
			}
		}
	}
	return 1.0;
}

int FDS2LP_ff (int* input, int* internal, int* output) {
	//clocked_on = CP
	//next_state = CR (D LD + IQ LD')
	if (input[0]) {
		internal[0] = input[1] && (input[2] && input[3] || internal[0] && !input[3]);
		internal[1] = LOGIC_NOT(internal[0]);
		return 1;
	}
	return 1;
}

void FDS2LP_func  (int* input, int* internal, int* output) {
	FDS2LP_ff(input, internal, output);
	//Q : IQ
	output[0] = internal[0];
	//QN : IQN
	output[1] = internal[1];
	return;
}
float FDS2LP_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['CP']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.26;
			}
			if (!rising) {
				return 1.34;
			}
		}
	}
	if (out_pin == 1) {
		//['CP']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.74;
			}
			if (!rising) {
				return 1.74;
			}
		}
	}
	return 1.0;
}

int FDS2P_ff (int* input, int* internal, int* output) {
	//clocked_on = CP
	//next_state = CR D
	if (input[0]) {
		internal[0] = input[1] && input[2];
		internal[1] = LOGIC_NOT(internal[0]);
		return 1;
	}
	return 1;
}

void FDS2P_func  (int* input, int* internal, int* output) {
	FDS2P_ff(input, internal, output);
	//Q : IQ
	output[0] = internal[0];
	//QN : IQN
	output[1] = internal[1];
	return;
}
float FDS2P_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['CP']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.16;
			}
			if (!rising) {
				return 1.44;
			}
		}
	}
	if (out_pin == 1) {
		//['CP']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.84;
			}
			if (!rising) {
				return 1.74;
			}
		}
	}
	return 1.0;
}

int FJK1_ff (int* input, int* internal, int* output) {
	//clocked_on = CP
	//next_state = (J' K' IQ) + (J K') + (J K IQ') 
	if (input[0]) {
		internal[0] = (!input[1] && !input[2] && internal[0]) || (input[1] && !input[2]) || (input[1] && input[2] && !internal[0]);
		internal[1] = LOGIC_NOT(internal[0]);
		return 1;
	}
	return 1;
}

void FJK1_func  (int* input, int* internal, int* output) {
	FJK1_ff(input, internal, output);
	//Q : IQ
	output[0] = internal[0];
	//QN : IQN
	output[1] = internal[1];
	return;
}
float FJK1_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['CP']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.09;
			}
			if (!rising) {
				return 0.94;
			}
		}
	}
	if (out_pin == 1) {
		//['CP']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.38;
			}
			if (!rising) {
				return 1.45;
			}
		}
	}
	return 1.0;
}

int FJK1P_ff (int* input, int* internal, int* output) {
	//clocked_on = CP
	//next_state = (J' K' IQ) + (J K') + (J K IQ') 
	if (input[0]) {
		internal[0] = (!input[1] && !input[2] && internal[0]) || (input[1] && !input[2]) || (input[1] && input[2] && !internal[0]);
		internal[1] = LOGIC_NOT(internal[0]);
		return 1;
	}
	return 1;
}

void FJK1P_func  (int* input, int* internal, int* output) {
	FJK1P_ff(input, internal, output);
	//Q : IQ
	output[0] = internal[0];
	//QN : IQN
	output[1] = internal[1];
	return;
}
float FJK1P_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['CP']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.14;
			}
			if (!rising) {
				return 1.03;
			}
		}
	}
	if (out_pin == 1) {
		//['CP']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.56;
			}
			if (!rising) {
				return 1.54;
			}
		}
	}
	return 1.0;
}

int FJK1S_ff (int* input, int* internal, int* output) {
	//clocked_on = CP
	//next_state =  (J' K' TE' IQ) + (J K' TE') + (J K TE' IQ') + (TI TE) 
	if (input[0]) {
		internal[0] = (!input[1] && !input[2] && !input[3] && internal[0]) || (input[1] && !input[2] && !input[3]) || (input[1] && input[2] && !input[3] && !internal[0]) || (input[4] && input[3]);
		internal[1] = LOGIC_NOT(internal[0]);
		return 1;
	}
	return 1;
}

void FJK1S_func  (int* input, int* internal, int* output) {
	FJK1S_ff(input, internal, output);
	//Q : IQ
	output[0] = internal[0];
	//QN : IQN
	output[1] = internal[1];
	return;
}
float FJK1S_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['CP']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.29;
			}
			if (!rising) {
				return 1.55;
			}
		}
	}
	if (out_pin == 1) {
		//['CP']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.78;
			}
			if (!rising) {
				return 1.77;
			}
		}
	}
	return 1.0;
}

int FJK1SP_ff (int* input, int* internal, int* output) {
	//clocked_on = CP
	//next_state =  (J' K' TE' IQ) + (J K' TE') + (J K TE' IQ') + (TI TE) 
	if (input[0]) {
		internal[0] = (!input[1] && !input[2] && !input[3] && internal[0]) || (input[1] && !input[2] && !input[3]) || (input[1] && input[2] && !input[3] && !internal[0]) || (input[4] && input[3]);
		internal[1] = LOGIC_NOT(internal[0]);
		return 1;
	}
	return 1;
}

void FJK1SP_func  (int* input, int* internal, int* output) {
	FJK1SP_ff(input, internal, output);
	//Q : IQ
	output[0] = internal[0];
	//QN : IQN
	output[1] = internal[1];
	return;
}
float FJK1SP_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['CP']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.34;
			}
			if (!rising) {
				return 1.56;
			}
		}
	}
	if (out_pin == 1) {
		//['CP']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.96;
			}
			if (!rising) {
				return 1.74;
			}
		}
	}
	return 1.0;
}

int FJK2_ff (int* input, int* internal, int* output) {
	//clear = CD'
	if (!input[0]) {
		internal[0] = 0;
		internal[1] = 1;
		return 1;
	}
	//clocked_on = CP
	//next_state =  (J' K' IQ) + (J K') + (J K IQ') 
	if (input[1]) {
		internal[0] = (!input[2] && !input[3] && internal[0]) || (input[2] && !input[3]) || (input[2] && input[3] && !internal[0]);
		internal[1] = LOGIC_NOT(internal[0]);
		return 1;
	}
	return 1;
}

void FJK2_func  (int* input, int* internal, int* output) {
	FJK2_ff(input, internal, output);
	//Q : IQ
	output[0] = internal[0];
	//QN : IQN
	output[1] = internal[1];
	return;
}
float FJK2_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['CD']
		if ( in_pin == 0 ) {
			if (!rising) {
				return 0.69;
			}
		}
		//['CP']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.17;
			}
			if (!rising) {
				return 0.94;
			}
		}
	}
	if (out_pin == 1) {
		//['CD']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.07;
			}
		}
		//['CP']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.32;
			}
			if (!rising) {
				return 1.55;
			}
		}
	}
	return 1.0;
}

int FJK2P_ff (int* input, int* internal, int* output) {
	//clear = CD'
	if (!input[0]) {
		internal[0] = 0;
		internal[1] = 1;
		return 1;
	}
	//clocked_on = CP
	//next_state =  (J' K' IQ) + (J K') + (J K IQ') 
	if (input[1]) {
		internal[0] = (!input[2] && !input[3] && internal[0]) || (input[2] && !input[3]) || (input[2] && input[3] && !internal[0]);
		internal[1] = LOGIC_NOT(internal[0]);
		return 1;
	}
	return 1;
}

void FJK2P_func  (int* input, int* internal, int* output) {
	FJK2P_ff(input, internal, output);
	//Q : IQ
	output[0] = internal[0];
	//QN : IQN
	output[1] = internal[1];
	return;
}
float FJK2P_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['CD']
		if ( in_pin == 0 ) {
			if (!rising) {
				return 0.85;
			}
		}
		//['CP']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.25;
			}
			if (!rising) {
				return 1.05;
			}
		}
	}
	if (out_pin == 1) {
		//['CD']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.36;
			}
		}
		//['CP']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.56;
			}
			if (!rising) {
				return 1.74;
			}
		}
	}
	return 1.0;
}

int FJK2S_ff (int* input, int* internal, int* output) {
	//clear = CD'
	if (!input[0]) {
		internal[0] = 0;
		internal[1] = 1;
		return 1;
	}
	//clocked_on = CP
	//next_state =  (J' K' TE' IQ) + (J K' TE') + (J K TE' IQ') + (TI TE) 
	if (input[1]) {
		internal[0] = (!input[2] && !input[3] && !input[4] && internal[0]) || (input[2] && !input[3] && !input[4]) || (input[2] && input[3] && !input[4] && !internal[0]) || (input[5] && input[4]);
		internal[1] = LOGIC_NOT(internal[0]);
		return 1;
	}
	return 1;
}

void FJK2S_func  (int* input, int* internal, int* output) {
	FJK2S_ff(input, internal, output);
	//Q : IQ
	output[0] = internal[0];
	//QN : IQN
	output[1] = internal[1];
	return;
}
float FJK2S_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['CD']
		if ( in_pin == 0 ) {
			if (!rising) {
				return 0.75;
			}
		}
		//['CP']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.47;
			}
			if (!rising) {
				return 1.45;
			}
		}
	}
	if (out_pin == 1) {
		//['CD']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.08;
			}
		}
		//['CP']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.78;
			}
			if (!rising) {
				return 1.97;
			}
		}
	}
	return 1.0;
}

int FJK2SP_ff (int* input, int* internal, int* output) {
	//clear = CD'
	if (!input[0]) {
		internal[0] = 0;
		internal[1] = 1;
		return 1;
	}
	//clocked_on = CP
	//next_state =  (J' K' TE' IQ) + (J K' TE') + (J K TE' IQ') + (TI TE) 
	if (input[1]) {
		internal[0] = (!input[2] && !input[3] && !input[4] && internal[0]) || (input[2] && !input[3] && !input[4]) || (input[2] && input[3] && !input[4] && !internal[0]) || (input[5] && input[4]);
		internal[1] = LOGIC_NOT(internal[0]);
		return 1;
	}
	return 1;
}

void FJK2SP_func  (int* input, int* internal, int* output) {
	FJK2SP_ff(input, internal, output);
	//Q : IQ
	output[0] = internal[0];
	//QN : IQN
	output[1] = internal[1];
	return;
}
float FJK2SP_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['CD']
		if ( in_pin == 0 ) {
			if (!rising) {
				return 0.84;
			}
		}
		//['CP']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.57;
			}
			if (!rising) {
				return 1.54;
			}
		}
	}
	if (out_pin == 1) {
		//['CD']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.26;
			}
		}
		//['CP']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.96;
			}
			if (!rising) {
				return 2.04;
			}
		}
	}
	return 1.0;
}

int FJK3_ff (int* input, int* internal, int* output) {
	//clear and preset
	//clear_preset_var1 = L
	//clear_preset_var2 = L
	if ( (!input[0]) && (!input[4]) ) {
		internal[0] = 0;
		internal[1] = 0;
		return 1;
	}
	//preset = SD'
	if (!input[4]) {
		internal[0] = 1;
		internal[1] = 0;
		return 1;
	}
	//clear = CD'
	if (!input[0]) {
		internal[0] = 0;
		internal[1] = 1;
		return 1;
	}
	//clocked_on = CP
	//next_state =  (J' K' IQ) + (J K') + (J K IQ') 
	if (input[1]) {
		internal[0] = (!input[2] && !input[3] && internal[0]) || (input[2] && !input[3]) || (input[2] && input[3] && !internal[0]);
		internal[1] = LOGIC_NOT(internal[0]);
		return 1;
	}
	return 1;
}

void FJK3_func  (int* input, int* internal, int* output) {
	FJK3_ff(input, internal, output);
	//Q : IQ
	output[0] = internal[0];
	//QN : IQN
	output[1] = internal[1];
	return;
}
float FJK3_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['CD']
		if ( in_pin == 0 ) {
			if (!rising) {
				return 0.75;
			}
		}
		//['CP']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.29;
			}
			if (!rising) {
				return 1.45;
			}
		}
		//['SD']
		if ( in_pin == 4 ) {
			if (rising) {
				return 1.14;
			}
		}
	}
	if (out_pin == 1) {
		//['CD']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.39;
			}
		}
		//['CP']
		if ( in_pin == 1 ) {
			if (rising) {
				return 2.09;
			}
			if (!rising) {
				return 1.95;
			}
		}
		//['SD']
		if ( in_pin == 4 ) {
			if (!rising) {
				return 1.8;
			}
		}
	}
	return 1.0;
}

int FJK3P_ff (int* input, int* internal, int* output) {
	//clear and preset
	//clear_preset_var1 = L
	//clear_preset_var2 = L
	if ( (!input[0]) && (!input[4]) ) {
		internal[0] = 0;
		internal[1] = 0;
		return 1;
	}
	//preset = SD'
	if (!input[4]) {
		internal[0] = 1;
		internal[1] = 0;
		return 1;
	}
	//clear = CD'
	if (!input[0]) {
		internal[0] = 0;
		internal[1] = 1;
		return 1;
	}
	//clocked_on = CP
	//next_state =  (J' K' IQ) + (J K') + (J K IQ') 
	if (input[1]) {
		internal[0] = (!input[2] && !input[3] && internal[0]) || (input[2] && !input[3]) || (input[2] && input[3] && !internal[0]);
		internal[1] = LOGIC_NOT(internal[0]);
		return 1;
	}
	return 1;
}

void FJK3P_func  (int* input, int* internal, int* output) {
	FJK3P_ff(input, internal, output);
	//Q : IQ
	output[0] = internal[0];
	//QN : IQN
	output[1] = internal[1];
	return;
}
float FJK3P_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['CD']
		if ( in_pin == 0 ) {
			if (!rising) {
				return 0.74;
			}
		}
		//['CP']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.34;
			}
			if (!rising) {
				return 1.44;
			}
		}
		//['SD']
		if ( in_pin == 4 ) {
			if (rising) {
				return 1.24;
			}
		}
	}
	if (out_pin == 1) {
		//['CD']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.54;
			}
		}
		//['CP']
		if ( in_pin == 1 ) {
			if (rising) {
				return 2.24;
			}
			if (!rising) {
				return 2.06;
			}
		}
		//['SD']
		if ( in_pin == 4 ) {
			if (!rising) {
				return 0.86;
			}
		}
	}
	return 1.0;
}

int FJK3S_ff (int* input, int* internal, int* output) {
	//clear and preset
	//clear_preset_var1 = L
	//clear_preset_var2 = L
	if ( (!input[0]) && (!input[4]) ) {
		internal[0] = 0;
		internal[1] = 0;
		return 1;
	}
	//preset = SD'
	if (!input[4]) {
		internal[0] = 1;
		internal[1] = 0;
		return 1;
	}
	//clear = CD'
	if (!input[0]) {
		internal[0] = 0;
		internal[1] = 1;
		return 1;
	}
	//clocked_on = CP
	//next_state =  (J' K' TE' IQ) + (J K' TE') + (J K TE' IQ') + (TI TE) 
	if (input[1]) {
		internal[0] = (!input[2] && !input[3] && !input[5] && internal[0]) || (input[2] && !input[3] && !input[5]) || (input[2] && input[3] && !input[5] && !internal[0]) || (input[6] && input[5]);
		internal[1] = LOGIC_NOT(internal[0]);
		return 1;
	}
	return 1;
}

void FJK3S_func  (int* input, int* internal, int* output) {
	FJK3S_ff(input, internal, output);
	//Q : IQ
	output[0] = internal[0];
	//QN : IQN
	output[1] = internal[1];
	return;
}
float FJK3S_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['CD']
		if ( in_pin == 0 ) {
			if (!rising) {
				return 0.94;
			}
		}
		//['CP']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.57;
			}
			if (!rising) {
				return 1.64;
			}
		}
		//['SD']
		if ( in_pin == 4 ) {
			if (rising) {
				return 1.42;
			}
		}
	}
	if (out_pin == 1) {
		//['CD']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.49;
			}
		}
		//['CP']
		if ( in_pin == 1 ) {
			if (rising) {
				return 2.19;
			}
			if (!rising) {
				return 1.97;
			}
		}
		//['SD']
		if ( in_pin == 4 ) {
			if (!rising) {
				return 0.82;
			}
		}
	}
	return 1.0;
}

int FJK3SP_ff (int* input, int* internal, int* output) {
	//clear and preset
	//clear_preset_var1 = L
	//clear_preset_var2 = L
	if ( (!input[0]) && (!input[4]) ) {
		internal[0] = 0;
		internal[1] = 0;
		return 1;
	}
	//preset = SD'
	if (!input[4]) {
		internal[0] = 1;
		internal[1] = 0;
		return 1;
	}
	//clear = CD'
	if (!input[0]) {
		internal[0] = 0;
		internal[1] = 1;
		return 1;
	}
	//clocked_on = CP
	//next_state =  (J' K' TE' IQ) + (J K' TE') + (J K TE' IQ') + (TI TE) 
	if (input[1]) {
		internal[0] = (!input[2] && !input[3] && !input[5] && internal[0]) || (input[2] && !input[3] && !input[5]) || (input[2] && input[3] && !input[5] && !internal[0]) || (input[6] && input[5]);
		internal[1] = LOGIC_NOT(internal[0]);
		return 1;
	}
	return 1;
}

void FJK3SP_func  (int* input, int* internal, int* output) {
	FJK3SP_ff(input, internal, output);
	//Q : IQ
	output[0] = internal[0];
	//QN : IQN
	output[1] = internal[1];
	return;
}
float FJK3SP_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['CD']
		if ( in_pin == 0 ) {
			if (!rising) {
				return 0.94;
			}
		}
		//['CP']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.67;
			}
			if (!rising) {
				return 1.64;
			}
		}
		//['SD']
		if ( in_pin == 4 ) {
			if (rising) {
				return 1.62;
			}
		}
	}
	if (out_pin == 1) {
		//['CD']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.74;
			}
		}
		//['CP']
		if ( in_pin == 1 ) {
			if (rising) {
				return 2.44;
			}
			if (!rising) {
				return 2.14;
			}
		}
		//['SD']
		if ( in_pin == 4 ) {
			if (!rising) {
				return 0.89;
			}
		}
	}
	return 1.0;
}

int FT2_ff (int* input, int* internal, int* output) {
	//clear = CD'
	if (!input[0]) {
		internal[0] = 0;
		internal[1] = 1;
		return 1;
	}
	//clocked_on = CP
	//next_state = IQ'
	if (input[1]) {
		internal[0] = !internal[0];
		internal[1] = LOGIC_NOT(internal[0]);
		return 1;
	}
	return 1;
}

void FT2_func  (int* input, int* internal, int* output) {
	FT2_ff(input, internal, output);
	//Q : IQ
	output[0] = internal[0];
	//QN : IQN
	output[1] = internal[1];
	return;
}
float FT2_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['CD']
		if ( in_pin == 0 ) {
			if (!rising) {
				return 0.0;
			}
		}
		//['CP']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.07;
			}
			if (!rising) {
				return 1.04;
			}
		}
	}
	if (out_pin == 1) {
		//['CD']
		if ( in_pin == 0 ) {
			if (!rising) {
				return 0.0;
			}
		}
		//['CP']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.29;
			}
			if (!rising) {
				return 1.55;
			}
		}
	}
	return 1.0;
}

int FT2P_ff (int* input, int* internal, int* output) {
	//clear = CD'
	if (!input[0]) {
		internal[0] = 0;
		internal[1] = 1;
		return 1;
	}
	//clocked_on = CP
	//next_state = IQ'
	if (input[1]) {
		internal[0] = !internal[0];
		internal[1] = LOGIC_NOT(internal[0]);
		return 1;
	}
	return 1;
}

void FT2P_func  (int* input, int* internal, int* output) {
	FT2P_ff(input, internal, output);
	//Q : IQ
	output[0] = internal[0];
	//QN : IQN
	output[1] = internal[1];
	return;
}
float FT2P_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['CD']
		if ( in_pin == 0 ) {
			if (!rising) {
				return 0.0;
			}
		}
		//['CP']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.15;
			}
			if (!rising) {
				return 1.03;
			}
		}
	}
	if (out_pin == 1) {
		//['CD']
		if ( in_pin == 0 ) {
			if (!rising) {
				return 0.0;
			}
		}
		//['CP']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.46;
			}
			if (!rising) {
				return 1.74;
			}
		}
	}
	return 1.0;
}

int FT4_ff (int* input, int* internal, int* output) {
	//preset = SD'
	if (!input[1]) {
		internal[0] = 1;
		internal[1] = 0;
		return 1;
	}
	//clocked_on = CP
	//next_state = IQ'
	if (input[0]) {
		internal[0] = !internal[0];
		internal[1] = LOGIC_NOT(internal[0]);
		return 1;
	}
	return 1;
}

void FT4_func  (int* input, int* internal, int* output) {
	FT4_ff(input, internal, output);
	//Q : IQ
	output[0] = internal[0];
	//QN : IQN
	output[1] = internal[1];
	return;
}
float FT4_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['SD']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.0;
			}
			if (!rising) {
				return 0.0;
			}
		}
		//['CP']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.99;
			}
			if (!rising) {
				return 1.04;
			}
		}
	}
	if (out_pin == 1) {
		//['SD']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.0;
			}
			if (!rising) {
				return 0.0;
			}
		}
		//['CP']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.49;
			}
			if (!rising) {
				return 1.55;
			}
		}
	}
	return 1.0;
}

int FT4P_ff (int* input, int* internal, int* output) {
	//preset = SD'
	if (!input[1]) {
		internal[0] = 1;
		internal[1] = 0;
		return 1;
	}
	//clocked_on = CP
	//next_state = IQ'
	if (input[0]) {
		internal[0] = !internal[0];
		internal[1] = LOGIC_NOT(internal[0]);
		return 1;
	}
	return 1;
}

void FT4P_func  (int* input, int* internal, int* output) {
	FT4P_ff(input, internal, output);
	//Q : IQ
	output[0] = internal[0];
	//QN : IQN
	output[1] = internal[1];
	return;
}
float FT4P_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['SD']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.0;
			}
			if (!rising) {
				return 0.0;
			}
		}
		//['CP']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.04;
			}
			if (!rising) {
				return 1.03;
			}
		}
	}
	if (out_pin == 1) {
		//['SD']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.0;
			}
			if (!rising) {
				return 0.0;
			}
		}
		//['CP']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.64;
			}
			if (!rising) {
				return 1.64;
			}
		}
	}
	return 1.0;
}

void HA1_func  (int* input, int* internal, int* output) {
	//CO : A B
	output[0] = input[0] && input[1];
	//S : A' B +  A B'
	output[1] = !input[0] && input[1] || input[0] && !input[1];
	return;
}
float HA1_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.48;
			}
			if (!rising) {
				return 0.77;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.48;
			}
			if (!rising) {
				return 0.77;
			}
		}
	}
	if (out_pin == 1) {
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.08;
			}
			if (!rising) {
				return 0.94;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.08;
			}
			if (!rising) {
				return 0.94;
			}
		}
	}
	return 1.0;
}

void HA1P_func  (int* input, int* internal, int* output) {
	//CO : A B
	output[0] = input[0] && input[1];
	//S : A' B +  A B'
	output[1] = !input[0] && input[1] || input[0] && !input[1];
	return;
}
float HA1P_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.54;
			}
			if (!rising) {
				return 0.84;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.54;
			}
			if (!rising) {
				return 0.84;
			}
		}
	}
	if (out_pin == 1) {
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.14;
			}
			if (!rising) {
				return 1.05;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.14;
			}
			if (!rising) {
				return 1.05;
			}
		}
	}
	return 1.0;
}

void IV_func  (int* input, int* internal, int* output) {
	//Z : A'
	output[0] = !input[0];
	return;
}
float IV_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.38;
			}
			if (!rising) {
				return 0.15;
			}
		}
	}
	return 1.0;
}

void IVA_func  (int* input, int* internal, int* output) {
	//Z : A'
	output[0] = !input[0];
	return;
}
float IVA_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.24;
			}
			if (!rising) {
				return 0.25;
			}
		}
	}
	return 1.0;
}

void IVAP_func  (int* input, int* internal, int* output) {
	//Z : A'
	output[0] = !input[0];
	return;
}
float IVAP_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.26;
			}
			if (!rising) {
				return 0.14;
			}
		}
	}
	return 1.0;
}

void IVDA_func  (int* input, int* internal, int* output) {
	//Y : A'
	output[0] = !input[0];
	//Z : A
	output[1] = input[0];
	return;
}
float IVDA_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.55;
			}
			if (!rising) {
				return 0.32;
			}
		}
	}
	if (out_pin == 1) {
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.48;
			}
			if (!rising) {
				return 0.67;
			}
		}
	}
	return 1.0;
}

void IVDAP_func  (int* input, int* internal, int* output) {
	//Y : A'
	output[0] = !input[0];
	//Z : A
	output[1] = input[0];
	return;
}
float IVDAP_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.4;
			}
			if (!rising) {
				return 0.18;
			}
		}
	}
	if (out_pin == 1) {
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.36;
			}
			if (!rising) {
				return 0.53;
			}
		}
	}
	return 1.0;
}

void IVP_func  (int* input, int* internal, int* output) {
	//Z : A'
	output[0] = !input[0];
	return;
}
float IVP_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.36;
			}
			if (!rising) {
				return 0.16;
			}
		}
	}
	return 1.0;
}

int LD1_latch (int* input, int* internal, int* output) {
	//enable = G
	//data_in = D
	if (input[1]) {
		internal[0] = input[0];
		internal[1] = LOGIC_NOT(internal[0]);
		return 1;
	}
	return 1;
}

void LD1_func  (int* input, int* internal, int* output) {
	LD1_latch(input, internal, output);
	//Q : IQ
	output[0] = internal[0];
	//QN : IQN
	output[1] = internal[1];
	return;
}
float LD1_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['G']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.89;
			}
			if (!rising) {
				return 0.86;
			}
		}
		//['D']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.89;
			}
			if (!rising) {
				return 0.86;
			}
		}
	}
	if (out_pin == 1) {
		//['G']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.18;
			}
			if (!rising) {
				return 1.37;
			}
		}
		//['D']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.18;
			}
			if (!rising) {
				return 1.37;
			}
		}
	}
	return 1.0;
}

int LD1P_latch (int* input, int* internal, int* output) {
	//enable = G
	//data_in = D
	if (input[1]) {
		internal[0] = input[0];
		internal[1] = LOGIC_NOT(internal[0]);
		return 1;
	}
	return 1;
}

void LD1P_func  (int* input, int* internal, int* output) {
	LD1P_latch(input, internal, output);
	//Q : IQ
	output[0] = internal[0];
	//QN : IQN
	output[1] = internal[1];
	return;
}
float LD1P_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['G']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.94;
			}
			if (!rising) {
				return 0.95;
			}
		}
		//['D']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.94;
			}
			if (!rising) {
				return 0.95;
			}
		}
	}
	if (out_pin == 1) {
		//['G']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.46;
			}
			if (!rising) {
				return 1.54;
			}
		}
		//['D']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.46;
			}
			if (!rising) {
				return 1.54;
			}
		}
	}
	return 1.0;
}

void LD1X4_func  (int* input, int* internal, int* output) {
	return;
}
float LD1X4_delay_func (int in_pin, int out_pin, BOOL rising) {
	tw_error(TW_LOC, "delay function called on no outputs");
	return 0;
}

void LD1X4P_func  (int* input, int* internal, int* output) {
	return;
}
float LD1X4P_delay_func (int in_pin, int out_pin, BOOL rising) {
	tw_error(TW_LOC, "delay function called on no outputs");
	return 0;
}

int LD2_latch (int* input, int* internal, int* output) {
	//enable = GN'
	//data_in = D
	if (!input[1]) {
		internal[0] = input[0];
		internal[1] = LOGIC_NOT(internal[0]);
		return 1;
	}
	return 1;
}

void LD2_func  (int* input, int* internal, int* output) {
	LD2_latch(input, internal, output);
	//Q : IQ
	output[0] = internal[0];
	//QN : IQN
	output[1] = internal[1];
	return;
}
float LD2_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['D']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.09;
			}
			if (!rising) {
				return 1.24;
			}
		}
		//['GN']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.09;
			}
			if (!rising) {
				return 1.24;
			}
		}
	}
	if (out_pin == 1) {
		//['D']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.58;
			}
			if (!rising) {
				return 1.57;
			}
		}
		//['GN']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.58;
			}
			if (!rising) {
				return 1.57;
			}
		}
	}
	return 1.0;
}

int LD2P_latch (int* input, int* internal, int* output) {
	//enable = GN'
	//data_in = D
	if (!input[1]) {
		internal[0] = input[0];
		internal[1] = LOGIC_NOT(internal[0]);
		return 1;
	}
	return 1;
}

void LD2P_func  (int* input, int* internal, int* output) {
	LD2P_latch(input, internal, output);
	//Q : IQ
	output[0] = internal[0];
	//QN : IQN
	output[1] = internal[1];
	return;
}
float LD2P_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['D']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.14;
			}
			if (!rising) {
				return 1.23;
			}
		}
		//['GN']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.14;
			}
			if (!rising) {
				return 1.23;
			}
		}
	}
	if (out_pin == 1) {
		//['D']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.76;
			}
			if (!rising) {
				return 1.74;
			}
		}
		//['GN']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.76;
			}
			if (!rising) {
				return 1.74;
			}
		}
	}
	return 1.0;
}

int LD3_latch (int* input, int* internal, int* output) {
	//clear = CD'
	if (!input[0]) {
		internal[0] = 0;
		internal[1] = 1;
		return 1;
	}
	//enable = G
	//data_in = D
	if (input[2]) {
		internal[0] = input[1];
		internal[1] = LOGIC_NOT(internal[0]);
		return 1;
	}
	return 1;
}

void LD3_func  (int* input, int* internal, int* output) {
	LD3_latch(input, internal, output);
	//Q : IQ
	output[0] = internal[0];
	//QN : IQN
	output[1] = internal[1];
	return;
}
float LD3_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['G']
		if ( in_pin == 2 ) {
			if (rising) {
				return 1.07;
			}
			if (!rising) {
				return 0.94;
			}
		}
		//['D']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.07;
			}
			if (!rising) {
				return 0.94;
			}
		}
		//['CD']
		if ( in_pin == 0 ) {
			if (!rising) {
				return 1.34;
			}
		}
	}
	if (out_pin == 1) {
		//['G']
		if ( in_pin == 2 ) {
			if (rising) {
				return 1.18;
			}
			if (!rising) {
				return 1.47;
			}
		}
		//['D']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.18;
			}
			if (!rising) {
				return 1.47;
			}
		}
		//['CD']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.58;
			}
		}
	}
	return 1.0;
}

int LD3P_latch (int* input, int* internal, int* output) {
	//clear = CD'
	if (!input[0]) {
		internal[0] = 0;
		internal[1] = 1;
		return 1;
	}
	//enable = G
	//data_in = D
	if (input[2]) {
		internal[0] = input[1];
		internal[1] = LOGIC_NOT(internal[0]);
		return 1;
	}
	return 1;
}

void LD3P_func  (int* input, int* internal, int* output) {
	LD3P_latch(input, internal, output);
	//Q : IQ
	output[0] = internal[0];
	//QN : IQN
	output[1] = internal[1];
	return;
}
float LD3P_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['G']
		if ( in_pin == 2 ) {
			if (rising) {
				return 1.15;
			}
			if (!rising) {
				return 1.93;
			}
		}
		//['D']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.15;
			}
			if (!rising) {
				return 1.93;
			}
		}
		//['CD']
		if ( in_pin == 0 ) {
			if (!rising) {
				return 2.33;
			}
		}
	}
	if (out_pin == 1) {
		//['G']
		if ( in_pin == 2 ) {
			if (rising) {
				return 1.46;
			}
			if (!rising) {
				return 1.64;
			}
		}
		//['D']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.46;
			}
			if (!rising) {
				return 1.64;
			}
		}
		//['CD']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.86;
			}
		}
	}
	return 1.0;
}

int LD4_latch (int* input, int* internal, int* output) {
	//clear = CD'
	if (!input[0]) {
		internal[0] = 0;
		internal[1] = 1;
		return 1;
	}
	//enable = GN'
	//data_in = D
	if (!input[2]) {
		internal[0] = input[1];
		internal[1] = LOGIC_NOT(internal[0]);
		return 1;
	}
	return 1;
}

void LD4_func  (int* input, int* internal, int* output) {
	LD4_latch(input, internal, output);
	//Q : IQ
	output[0] = internal[0];
	//QN : IQN
	output[1] = internal[1];
	return;
}
float LD4_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['D']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.27;
			}
			if (!rising) {
				return 1.24;
			}
		}
		//['CD']
		if ( in_pin == 0 ) {
			if (!rising) {
				return 1.64;
			}
		}
		//['GN']
		if ( in_pin == 2 ) {
			if (rising) {
				return 1.27;
			}
			if (!rising) {
				return 1.24;
			}
		}
	}
	if (out_pin == 1) {
		//['D']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.48;
			}
			if (!rising) {
				return 1.65;
			}
		}
		//['CD']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.88;
			}
		}
		//['GN']
		if ( in_pin == 2 ) {
			if (rising) {
				return 1.48;
			}
			if (!rising) {
				return 1.65;
			}
		}
	}
	return 1.0;
}

int LD4P_latch (int* input, int* internal, int* output) {
	//clear = CD'
	if (!input[0]) {
		internal[0] = 0;
		internal[1] = 1;
		return 1;
	}
	//enable = GN'
	//data_in = D
	if (!input[2]) {
		internal[0] = input[1];
		internal[1] = LOGIC_NOT(internal[0]);
		return 1;
	}
	return 1;
}

void LD4P_func  (int* input, int* internal, int* output) {
	LD4P_latch(input, internal, output);
	//Q : IQ
	output[0] = internal[0];
	//QN : IQN
	output[1] = internal[1];
	return;
}
float LD4P_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['D']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.35;
			}
			if (!rising) {
				return 1.23;
			}
		}
		//['CD']
		if ( in_pin == 0 ) {
			if (!rising) {
				return 1.63;
			}
		}
		//['GN']
		if ( in_pin == 2 ) {
			if (rising) {
				return 1.35;
			}
			if (!rising) {
				return 1.23;
			}
		}
	}
	if (out_pin == 1) {
		//['D']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.76;
			}
			if (!rising) {
				return 1.94;
			}
		}
		//['CD']
		if ( in_pin == 0 ) {
			if (rising) {
				return 2.16;
			}
		}
		//['GN']
		if ( in_pin == 2 ) {
			if (rising) {
				return 1.76;
			}
			if (!rising) {
				return 1.94;
			}
		}
	}
	return 1.0;
}

void LS1_func  (int* input, int* internal, int* output) {
	return;
}
float LS1_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['C1']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.30;
			}
			if (!rising) {
				return 0.93;
			}
		}
		//['C2']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.30;
			}
			if (!rising) {
				return 0.93;
			}
		}
	}
	if (out_pin == 1) {
		//['C1']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.38;
			}
			if (!rising) {
				return 1.55;
			}
		}
		//['C2']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.38;
			}
			if (!rising) {
				return 1.55;
			}
		}
	}
	return 1.0;
}

void LS1P_func  (int* input, int* internal, int* output) {
	return;
}
float LS1P_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['C1']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.25;
			}
			if (!rising) {
				return 0.97;
			}
		}
		//['C2']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.25;
			}
			if (!rising) {
				return 0.97;
			}
		}
	}
	if (out_pin == 1) {
		//['C1']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.54;
			}
			if (!rising) {
				return 1.94;
			}
		}
		//['C2']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.54;
			}
			if (!rising) {
				return 1.94;
			}
		}
	}
	return 1.0;
}

int LSR0_latch (int* input, int* internal, int* output) {
	//clear and preset
	//clear_preset_var1 = L
	//clear_preset_var2 = L
	if ( (!input[0]) && (!input[1]) ) {
		internal[0] = 0;
		internal[1] = 0;
		return 1;
	}
	//preset = S'
	if (!input[1]) {
		internal[0] = 1;
		internal[1] = 0;
		return 1;
	}
	//clear = R'
	if (!input[0]) {
		internal[0] = 0;
		internal[1] = 1;
		return 1;
	}
	return 1;
}

void LSR0_func  (int* input, int* internal, int* output) {
	LSR0_latch(input, internal, output);
	//Q : IQ
	output[0] = internal[0];
	//QN : IQN
	output[1] = internal[1];
	return;
}
float LSR0_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['S']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.53;
			}
		}
		//['R']
		if ( in_pin == 0 ) {
			if (!rising) {
				return 0.92;
			}
		}
	}
	if (out_pin == 1) {
		//['S']
		if ( in_pin == 1 ) {
			if (!rising) {
				return 0.92;
			}
		}
		//['R']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.53;
			}
		}
	}
	return 1.0;
}

int LSR0P_latch (int* input, int* internal, int* output) {
	//clear and preset
	//clear_preset_var1 = L
	//clear_preset_var2 = L
	if ( (!input[0]) && (!input[1]) ) {
		internal[0] = 0;
		internal[1] = 0;
		return 1;
	}
	//preset = S'
	if (!input[1]) {
		internal[0] = 1;
		internal[1] = 0;
		return 1;
	}
	//clear = R'
	if (!input[0]) {
		internal[0] = 0;
		internal[1] = 1;
		return 1;
	}
	return 1;
}

void LSR0P_func  (int* input, int* internal, int* output) {
	LSR0P_latch(input, internal, output);
	//Q : IQ
	output[0] = internal[0];
	//QN : IQN
	output[1] = internal[1];
	return;
}
float LSR0P_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['S']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.72;
			}
		}
		//['R']
		if ( in_pin == 0 ) {
			if (!rising) {
				return 0.97;
			}
		}
	}
	if (out_pin == 1) {
		//['S']
		if ( in_pin == 1 ) {
			if (!rising) {
				return 0.97;
			}
		}
		//['R']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.72;
			}
		}
	}
	return 1.0;
}

int LSR2_latch (int* input, int* internal, int* output) {
	//clear and preset
	//clear_preset_var1 = H
	//clear_preset_var2 = H
	if ( (!input[2] || input[3] && !input[1] && !input[0]) && (!input[4] || input[1] && !input[3] && !input[0]) ) {
		internal[0] = 1;
		internal[1] = 1;
		return 1;
	}
	//preset = SD'+ R S' G'
	if (!input[4] || input[1] && !input[3] && !input[0]) {
		internal[0] = 1;
		internal[1] = 0;
		return 1;
	}
	//clear = RD' + S R' G'
	if (!input[2] || input[3] && !input[1] && !input[0]) {
		internal[0] = 0;
		internal[1] = 1;
		return 1;
	}
	return 1;
}

void LSR2_func  (int* input, int* internal, int* output) {
	LSR2_latch(input, internal, output);
	//Q : IQ
	output[0] = internal[0];
	//QN : IQN
	output[1] = internal[1];
	return;
}
float LSR2_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['G']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.76;
			}
			if (!rising) {
				return 1.22;
			}
		}
		//['S', 'SD']
		if ( in_pin == 3 ||  in_pin == 4 ) {
			if (rising) {
				return 0.76;
			}
		}
		//['R', 'RD']
		if ( in_pin == 1 ||  in_pin == 2 ) {
			if (!rising) {
				return 1.22;
			}
		}
	}
	if (out_pin == 1) {
		//['G']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.76;
			}
			if (!rising) {
				return 1.22;
			}
		}
		//['S', 'SD']
		if ( in_pin == 3 ||  in_pin == 4 ) {
			if (!rising) {
				return 1.22;
			}
		}
		//['R', 'RD']
		if ( in_pin == 1 ||  in_pin == 2 ) {
			if (rising) {
				return 0.76;
			}
		}
	}
	return 1.0;
}

void MUX21H_func  (int* input, int* internal, int* output) {
	//Z : (S'A+S B)
	output[0] = (!input[2] && input[0] || input[2] && input[1]);
	return;
}
float MUX21H_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.64;
			}
			if (!rising) {
				return 1.15;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.64;
			}
			if (!rising) {
				return 1.15;
			}
		}
		//['S']
		if ( in_pin == 2 ) {
			if (rising) {
				return 0.84;
			}
			if (!rising) {
				return 0.85;
			}
		}
	}
	return 1.0;
}

void MUX21HP_func  (int* input, int* internal, int* output) {
	//Z : (S'A+S B)
	output[0] = (!input[2] && input[0] || input[2] && input[1]);
	return;
}
float MUX21HP_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.76;
			}
			if (!rising) {
				return 1.25;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.76;
			}
			if (!rising) {
				return 1.25;
			}
		}
		//['S']
		if ( in_pin == 2 ) {
			if (rising) {
				return 0.96;
			}
			if (!rising) {
				return 0.95;
			}
		}
	}
	return 1.0;
}

void MUX21L_func  (int* input, int* internal, int* output) {
	//Z : (S'A'+S B')
	output[0] = (!input[2] && !input[0] || input[2] && !input[1]);
	return;
}
float MUX21L_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.36;
			}
			if (!rising) {
				return 0.37;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.36;
			}
			if (!rising) {
				return 0.37;
			}
		}
		//['S']
		if ( in_pin == 2 ) {
			if (rising) {
				return 0.76;
			}
			if (!rising) {
				return 0.57;
			}
		}
	}
	return 1.0;
}

void MUX21LA_func  (int* input, int* internal, int* output) {
	//Z : ( (A S' SN) + (B S SN') )'
	output[0] = !((input[0] && !input[2] && input[3]) || (input[1] && input[2] && !input[3]));
	return;
}
float MUX21LA_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.28;
			}
			if (!rising) {
				return 0.57;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.28;
			}
			if (!rising) {
				return 0.57;
			}
		}
		//['SN']
		if ( in_pin == 3 ) {
			if (rising) {
				return 0.28;
			}
			if (!rising) {
				return 0.57;
			}
		}
		//['S']
		if ( in_pin == 2 ) {
			if (rising) {
				return 0.28;
			}
			if (!rising) {
				return 0.57;
			}
		}
	}
	return 1.0;
}

void MUX21LAP_func  (int* input, int* internal, int* output) {
	//Z : ( (A S' SN) + (B S SN') )'
	output[0] = !((input[0] && !input[2] && input[3]) || (input[1] && input[2] && !input[3]));
	return;
}
float MUX21LAP_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.46;
			}
			if (!rising) {
				return 0.54;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.46;
			}
			if (!rising) {
				return 0.54;
			}
		}
		//['SN']
		if ( in_pin == 3 ) {
			if (rising) {
				return 0.46;
			}
			if (!rising) {
				return 0.54;
			}
		}
		//['S']
		if ( in_pin == 2 ) {
			if (rising) {
				return 0.46;
			}
			if (!rising) {
				return 0.54;
			}
		}
	}
	return 1.0;
}

void MUX21LP_func  (int* input, int* internal, int* output) {
	//Z : (S'A'+S B')
	output[0] = (!input[2] && !input[0] || input[2] && !input[1]);
	return;
}
float MUX21LP_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.46;
			}
			if (!rising) {
				return 0.36;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.46;
			}
			if (!rising) {
				return 0.36;
			}
		}
		//['S']
		if ( in_pin == 2 ) {
			if (rising) {
				return 0.86;
			}
			if (!rising) {
				return 0.66;
			}
		}
	}
	return 1.0;
}

void MUX31L_func  (int* input, int* internal, int* output) {
	//Z : ((D0'A'B')+(D1'A B')+(D2'B))
	output[0] = ((!input[2] && !input[0] && !input[1]) || (!input[3] && input[0] && !input[1]) || (!input[4] && input[1]));
	return;
}
float MUX31L_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.72;
			}
			if (!rising) {
				return 0.47;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.52;
			}
			if (!rising) {
				return 0.77;
			}
		}
		//['D0']
		if ( in_pin == 2 ) {
			if (rising) {
				return 1.22;
			}
			if (!rising) {
				return 0.57;
			}
		}
		//['D1']
		if ( in_pin == 3 ) {
			if (rising) {
				return 1.22;
			}
			if (!rising) {
				return 0.57;
			}
		}
		//['D2']
		if ( in_pin == 4 ) {
			if (rising) {
				return 0.72;
			}
			if (!rising) {
				return 0.47;
			}
		}
	}
	return 1.0;
}

void MUX31LP_func  (int* input, int* internal, int* output) {
	//Z : ((D0'A'B')+(D1'A B')+(D2'B))
	output[0] = ((!input[2] && !input[0] && !input[1]) || (!input[3] && input[0] && !input[1]) || (!input[4] && input[1]));
	return;
}
float MUX31LP_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.56;
			}
			if (!rising) {
				return 0.35;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.16;
			}
			if (!rising) {
				return 0.85;
			}
		}
		//['D0']
		if ( in_pin == 2 ) {
			if (rising) {
				return 1.06;
			}
			if (!rising) {
				return 0.45;
			}
		}
		//['D1']
		if ( in_pin == 3 ) {
			if (rising) {
				return 1.06;
			}
			if (!rising) {
				return 0.45;
			}
		}
		//['D2']
		if ( in_pin == 4 ) {
			if (rising) {
				return 0.56;
			}
			if (!rising) {
				return 0.35;
			}
		}
	}
	return 1.0;
}

void MUX41_func  (int* input, int* internal, int* output) {
	//Z : ((D0 A'B')+(D1 A B')+(D2 A'B)+(D3 A B))
	output[0] = ((input[2] && !input[0] && !input[1]) || (input[3] && input[0] && !input[1]) || (input[4] && !input[0] && input[1]) || (input[5] && input[0] && input[1]));
	return;
}
float MUX41_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.79;
			}
			if (!rising) {
				return 0.67;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.79;
			}
			if (!rising) {
				return 1.37;
			}
		}
		//['D0']
		if ( in_pin == 2 ) {
			if (rising) {
				return 0.69;
			}
			if (!rising) {
				return 0.97;
			}
		}
		//['D1']
		if ( in_pin == 3 ) {
			if (rising) {
				return 0.69;
			}
			if (!rising) {
				return 0.97;
			}
		}
		//['D2']
		if ( in_pin == 4 ) {
			if (rising) {
				return 0.69;
			}
			if (!rising) {
				return 0.97;
			}
		}
		//['D3']
		if ( in_pin == 5 ) {
			if (rising) {
				return 0.69;
			}
			if (!rising) {
				return 0.97;
			}
		}
	}
	return 1.0;
}

void MUX41P_func  (int* input, int* internal, int* output) {
	//Z : ((D0 A'B')+(D1 A B')+(D2 A'B)+(D3 A B))
	output[0] = ((input[2] && !input[0] && !input[1]) || (input[3] && input[0] && !input[1]) || (input[4] && !input[0] && input[1]) || (input[5] && input[0] && input[1]));
	return;
}
float MUX41P_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.83;
			}
			if (!rising) {
				return 0.64;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.83;
			}
			if (!rising) {
				return 1.24;
			}
		}
		//['D0']
		if ( in_pin == 2 ) {
			if (rising) {
				return 0.73;
			}
			if (!rising) {
				return 0.94;
			}
		}
		//['D1']
		if ( in_pin == 3 ) {
			if (rising) {
				return 0.73;
			}
			if (!rising) {
				return 0.94;
			}
		}
		//['D2']
		if ( in_pin == 4 ) {
			if (rising) {
				return 0.73;
			}
			if (!rising) {
				return 0.94;
			}
		}
		//['D3']
		if ( in_pin == 5 ) {
			if (rising) {
				return 0.73;
			}
			if (!rising) {
				return 0.94;
			}
		}
	}
	return 1.0;
}

void MUX51H_func  (int* input, int* internal, int* output) {
	//Z : ((D0 A'B'C')+(D1 A B'C')+(D2 A'B C')+(D3 A B C')+(D4 C))
	output[0] = ((input[3] && !input[0] && !input[1] && !input[2]) || (input[4] && input[0] && !input[1] && !input[2]) || (input[5] && !input[0] && input[1] && !input[2]) || (input[6] && input[0] && input[1] && !input[2]) || (input[7] && input[2]));
	return;
}
float MUX51H_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['C']
		if ( in_pin == 2 ) {
			if (rising) {
				return 0.89;
			}
			if (!rising) {
				return 0.64;
			}
		}
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.29;
			}
			if (!rising) {
				return 0.94;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 2.19;
			}
			if (!rising) {
				return 1.84;
			}
		}
		//['D0']
		if ( in_pin == 3 ) {
			if (rising) {
				return 1.79;
			}
			if (!rising) {
				return 1.94;
			}
		}
		//['D1']
		if ( in_pin == 4 ) {
			if (rising) {
				return 1.79;
			}
			if (!rising) {
				return 1.94;
			}
		}
		//['D2']
		if ( in_pin == 5 ) {
			if (rising) {
				return 1.79;
			}
			if (!rising) {
				return 1.94;
			}
		}
		//['D3']
		if ( in_pin == 6 ) {
			if (rising) {
				return 1.79;
			}
			if (!rising) {
				return 1.94;
			}
		}
		//['D4']
		if ( in_pin == 7 ) {
			if (rising) {
				return 0.69;
			}
			if (!rising) {
				return 0.94;
			}
		}
	}
	return 1.0;
}

void MUX51HP_func  (int* input, int* internal, int* output) {
	//Z : ((D0 A'B'C')+(D1 A B'C')+(D2 A'B C')+(D3 A B C')+(D4 C))
	output[0] = ((input[3] && !input[0] && !input[1] && !input[2]) || (input[4] && input[0] && !input[1] && !input[2]) || (input[5] && !input[0] && input[1] && !input[2]) || (input[6] && input[0] && input[1] && !input[2]) || (input[7] && input[2]));
	return;
}
float MUX51HP_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['C']
		if ( in_pin == 2 ) {
			if (rising) {
				return 0.94;
			}
			if (!rising) {
				return 0.75;
			}
		}
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.34;
			}
			if (!rising) {
				return 1.05;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 2.24;
			}
			if (!rising) {
				return 1.95;
			}
		}
		//['D0']
		if ( in_pin == 3 ) {
			if (rising) {
				return 1.84;
			}
			if (!rising) {
				return 2.05;
			}
		}
		//['D1']
		if ( in_pin == 4 ) {
			if (rising) {
				return 1.84;
			}
			if (!rising) {
				return 2.05;
			}
		}
		//['D2']
		if ( in_pin == 5 ) {
			if (rising) {
				return 1.84;
			}
			if (!rising) {
				return 2.05;
			}
		}
		//['D3']
		if ( in_pin == 6 ) {
			if (rising) {
				return 1.84;
			}
			if (!rising) {
				return 2.05;
			}
		}
		//['D4']
		if ( in_pin == 7 ) {
			if (rising) {
				return 0.74;
			}
			if (!rising) {
				return 1.05;
			}
		}
	}
	return 1.0;
}

void MUX81_func  (int* input, int* internal, int* output) {
	//Z : ((D0 A'B'C')+(D1 A B'C')+(D2 A'B C')+(D3 A B C')+(D4 A'B'C)+(D5 A B'C)+(D6 A'B C)+(D7 A B C))
	output[0] = ((input[3] && !input[0] && !input[1] && !input[2]) || (input[4] && input[0] && !input[1] && !input[2]) || (input[5] && !input[0] && input[1] && !input[2]) || (input[6] && input[0] && input[1] && !input[2]) || (input[7] && !input[0] && !input[1] && input[2]) || (input[8] && input[0] && !input[1] && input[2]) || (input[9] && !input[0] && input[1] && input[2]) || (input[10] && input[0] && input[1] && input[2]));
	return;
}
float MUX81_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['D0', 'D1', 'D2', 'D3', 'D4', 'D5', 'D6', 'D7']
		if ( in_pin == 3 ||  in_pin == 4 ||  in_pin == 5 ||  in_pin == 6 ||  in_pin == 7 ||  in_pin == 8 ||  in_pin == 9 ||  in_pin == 10 ) {
			if (rising) {
				return 1.09;
			}
			if (!rising) {
				return 1.25;
			}
		}
		//['A', 'B', 'C']
		if ( in_pin == 0 ||  in_pin == 1 ||  in_pin == 2 ) {
			if (rising) {
				return 1.79;
			}
			if (!rising) {
				return 2.35;
			}
		}
	}
	return 1.0;
}

void MUX81P_func  (int* input, int* internal, int* output) {
	//Z : ((D0 A'B'C')+(D1 A B'C')+(D2 A'B C')+(D3 A B C')+(D4 A'B'C)+(D5 A B'C)+(D6 A'B C)+(D7 A B C))
	output[0] = ((input[3] && !input[0] && !input[1] && !input[2]) || (input[4] && input[0] && !input[1] && !input[2]) || (input[5] && !input[0] && input[1] && !input[2]) || (input[6] && input[0] && input[1] && !input[2]) || (input[7] && !input[0] && !input[1] && input[2]) || (input[8] && input[0] && !input[1] && input[2]) || (input[9] && !input[0] && input[1] && input[2]) || (input[10] && input[0] && input[1] && input[2]));
	return;
}
float MUX81P_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['C']
		if ( in_pin == 2 ) {
			if (rising) {
				return 0.83;
			}
			if (!rising) {
				return 0.62;
			}
		}
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.13;
			}
			if (!rising) {
				return 0.92;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 2.13;
			}
			if (!rising) {
				return 2.02;
			}
		}
		//['D0']
		if ( in_pin == 3 ) {
			if (rising) {
				return 1.33;
			}
			if (!rising) {
				return 1.12;
			}
		}
		//['D1']
		if ( in_pin == 4 ) {
			if (rising) {
				return 1.33;
			}
			if (!rising) {
				return 1.12;
			}
		}
		//['D2']
		if ( in_pin == 5 ) {
			if (rising) {
				return 1.33;
			}
			if (!rising) {
				return 1.12;
			}
		}
		//['D3']
		if ( in_pin == 6 ) {
			if (rising) {
				return 1.33;
			}
			if (!rising) {
				return 1.12;
			}
		}
		//['D4']
		if ( in_pin == 7 ) {
			if (rising) {
				return 1.33;
			}
			if (!rising) {
				return 1.12;
			}
		}
		//['D5']
		if ( in_pin == 8 ) {
			if (rising) {
				return 1.33;
			}
			if (!rising) {
				return 1.12;
			}
		}
		//['D6']
		if ( in_pin == 9 ) {
			if (rising) {
				return 1.33;
			}
			if (!rising) {
				return 1.12;
			}
		}
		//['D7']
		if ( in_pin == 10 ) {
			if (rising) {
				return 1.33;
			}
			if (!rising) {
				return 1.12;
			}
		}
	}
	return 1.0;
}

void ND2_func  (int* input, int* internal, int* output) {
	//Z : (A B)'
	output[0] = !(input[0] && input[1]);
	return;
}
float ND2_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.5;
			}
			if (!rising) {
				return 0.13;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.5;
			}
			if (!rising) {
				return 0.13;
			}
		}
	}
	return 1.0;
}

void ND2P_func  (int* input, int* internal, int* output) {
	//Z : (A B)'
	output[0] = !(input[0] && input[1]);
	return;
}
float ND2P_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.5;
			}
			if (!rising) {
				return 0.16;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.5;
			}
			if (!rising) {
				return 0.16;
			}
		}
	}
	return 1.0;
}

void ND3_func  (int* input, int* internal, int* output) {
	//Z : (A B C)'
	output[0] = !(input[0] && input[1] && input[2]);
	return;
}
float ND3_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['C']
		if ( in_pin == 2 ) {
			if (rising) {
				return 0.65;
			}
			if (!rising) {
				return 0.37;
			}
		}
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.65;
			}
			if (!rising) {
				return 0.37;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.65;
			}
			if (!rising) {
				return 0.37;
			}
		}
	}
	return 1.0;
}

void ND3P_func  (int* input, int* internal, int* output) {
	//Z : (A B C)'
	output[0] = !(input[0] && input[1] && input[2]);
	return;
}
float ND3P_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['C']
		if ( in_pin == 2 ) {
			if (rising) {
				return 0.64;
			}
			if (!rising) {
				return 0.41;
			}
		}
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.64;
			}
			if (!rising) {
				return 0.41;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.64;
			}
			if (!rising) {
				return 0.41;
			}
		}
	}
	return 1.0;
}

void ND4_func  (int* input, int* internal, int* output) {
	//Z : (A B C D)'
	output[0] = !(input[0] && input[1] && input[2] && input[3]);
	return;
}
float ND4_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['D']
		if ( in_pin == 3 ) {
			if (rising) {
				return 0.65;
			}
			if (!rising) {
				return 0.45;
			}
		}
		//['C']
		if ( in_pin == 2 ) {
			if (rising) {
				return 0.65;
			}
			if (!rising) {
				return 0.45;
			}
		}
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.65;
			}
			if (!rising) {
				return 0.45;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.65;
			}
			if (!rising) {
				return 0.45;
			}
		}
	}
	return 1.0;
}

void ND4P_func  (int* input, int* internal, int* output) {
	//Z : (A B C D)'
	output[0] = !(input[0] && input[1] && input[2] && input[3]);
	return;
}
float ND4P_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['D']
		if ( in_pin == 3 ) {
			if (rising) {
				return 0.62;
			}
			if (!rising) {
				return 0.42;
			}
		}
		//['C']
		if ( in_pin == 2 ) {
			if (rising) {
				return 0.62;
			}
			if (!rising) {
				return 0.42;
			}
		}
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.62;
			}
			if (!rising) {
				return 0.42;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.62;
			}
			if (!rising) {
				return 0.42;
			}
		}
	}
	return 1.0;
}

void ND5_func  (int* input, int* internal, int* output) {
	//Z : (A B C D E)'
	output[0] = !(input[0] && input[1] && input[2] && input[3] && input[4]);
	return;
}
float ND5_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['D']
		if ( in_pin == 3 ) {
			if (rising) {
				return 1.08;
			}
			if (!rising) {
				return 1.15;
			}
		}
		//['C']
		if ( in_pin == 2 ) {
			if (rising) {
				return 1.08;
			}
			if (!rising) {
				return 1.15;
			}
		}
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.08;
			}
			if (!rising) {
				return 1.15;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.08;
			}
			if (!rising) {
				return 1.15;
			}
		}
		//['E']
		if ( in_pin == 4 ) {
			if (rising) {
				return 1.08;
			}
			if (!rising) {
				return 1.15;
			}
		}
	}
	return 1.0;
}

void ND5P_func  (int* input, int* internal, int* output) {
	//Z : (A B C D E)'
	output[0] = !(input[0] && input[1] && input[2] && input[3] && input[4]);
	return;
}
float ND5P_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['D']
		if ( in_pin == 3 ) {
			if (rising) {
				return 1.16;
			}
			if (!rising) {
				return 1.26;
			}
		}
		//['C']
		if ( in_pin == 2 ) {
			if (rising) {
				return 1.16;
			}
			if (!rising) {
				return 1.26;
			}
		}
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.16;
			}
			if (!rising) {
				return 1.26;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.16;
			}
			if (!rising) {
				return 1.26;
			}
		}
		//['E']
		if ( in_pin == 4 ) {
			if (rising) {
				return 1.16;
			}
			if (!rising) {
				return 1.26;
			}
		}
	}
	return 1.0;
}

void ND6_func  (int* input, int* internal, int* output) {
	//Z : (A B C D E F)'
	output[0] = !(input[0] && input[1] && input[2] && input[3] && input[4] && input[5]);
	return;
}
float ND6_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['F']
		if ( in_pin == 5 ) {
			if (rising) {
				return 0.98;
			}
			if (!rising) {
				return 1.15;
			}
		}
		//['D']
		if ( in_pin == 3 ) {
			if (rising) {
				return 0.98;
			}
			if (!rising) {
				return 1.15;
			}
		}
		//['C']
		if ( in_pin == 2 ) {
			if (rising) {
				return 0.98;
			}
			if (!rising) {
				return 1.15;
			}
		}
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.98;
			}
			if (!rising) {
				return 1.15;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.98;
			}
			if (!rising) {
				return 1.15;
			}
		}
		//['E']
		if ( in_pin == 4 ) {
			if (rising) {
				return 0.98;
			}
			if (!rising) {
				return 1.15;
			}
		}
	}
	return 1.0;
}

void ND6P_func  (int* input, int* internal, int* output) {
	//Z : (A B C D E F)'
	output[0] = !(input[0] && input[1] && input[2] && input[3] && input[4] && input[5]);
	return;
}
float ND6P_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['F']
		if ( in_pin == 5 ) {
			if (rising) {
				return 1.06;
			}
			if (!rising) {
				return 1.26;
			}
		}
		//['D']
		if ( in_pin == 3 ) {
			if (rising) {
				return 1.06;
			}
			if (!rising) {
				return 1.26;
			}
		}
		//['C']
		if ( in_pin == 2 ) {
			if (rising) {
				return 1.06;
			}
			if (!rising) {
				return 1.26;
			}
		}
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.06;
			}
			if (!rising) {
				return 1.26;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.06;
			}
			if (!rising) {
				return 1.26;
			}
		}
		//['E']
		if ( in_pin == 4 ) {
			if (rising) {
				return 1.06;
			}
			if (!rising) {
				return 1.26;
			}
		}
	}
	return 1.0;
}

void ND8_func  (int* input, int* internal, int* output) {
	//Z : (A B C D E F G H)'
	output[0] = !(input[0] && input[1] && input[2] && input[3] && input[4] && input[5] && input[6] && input[7]);
	return;
}
float ND8_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['F']
		if ( in_pin == 5 ) {
			if (rising) {
				return 1.08;
			}
			if (!rising) {
				return 1.45;
			}
		}
		//['D']
		if ( in_pin == 3 ) {
			if (rising) {
				return 1.08;
			}
			if (!rising) {
				return 1.45;
			}
		}
		//['C']
		if ( in_pin == 2 ) {
			if (rising) {
				return 1.08;
			}
			if (!rising) {
				return 1.45;
			}
		}
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.08;
			}
			if (!rising) {
				return 1.45;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.08;
			}
			if (!rising) {
				return 1.45;
			}
		}
		//['E']
		if ( in_pin == 4 ) {
			if (rising) {
				return 1.08;
			}
			if (!rising) {
				return 1.45;
			}
		}
		//['H']
		if ( in_pin == 7 ) {
			if (rising) {
				return 1.08;
			}
			if (!rising) {
				return 1.45;
			}
		}
		//['G']
		if ( in_pin == 6 ) {
			if (rising) {
				return 1.08;
			}
			if (!rising) {
				return 1.45;
			}
		}
	}
	return 1.0;
}

void ND8P_func  (int* input, int* internal, int* output) {
	//Z : (A B C D E F G H)'
	output[0] = !(input[0] && input[1] && input[2] && input[3] && input[4] && input[5] && input[6] && input[7]);
	return;
}
float ND8P_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['F']
		if ( in_pin == 5 ) {
			if (rising) {
				return 1.16;
			}
			if (!rising) {
				return 1.56;
			}
		}
		//['D']
		if ( in_pin == 3 ) {
			if (rising) {
				return 1.16;
			}
			if (!rising) {
				return 1.56;
			}
		}
		//['C']
		if ( in_pin == 2 ) {
			if (rising) {
				return 1.16;
			}
			if (!rising) {
				return 1.56;
			}
		}
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.16;
			}
			if (!rising) {
				return 1.56;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.16;
			}
			if (!rising) {
				return 1.56;
			}
		}
		//['E']
		if ( in_pin == 4 ) {
			if (rising) {
				return 1.16;
			}
			if (!rising) {
				return 1.56;
			}
		}
		//['H']
		if ( in_pin == 7 ) {
			if (rising) {
				return 1.16;
			}
			if (!rising) {
				return 1.56;
			}
		}
		//['G']
		if ( in_pin == 6 ) {
			if (rising) {
				return 1.16;
			}
			if (!rising) {
				return 1.56;
			}
		}
	}
	return 1.0;
}

void NR16_func  (int* input, int* internal, int* output) {
	//Z : (I0+I1+I2+I3+I4+I5+I6+I7+I8+I9+I10+I11+I12+I13+I14+I15)'
	output[0] = !(input[0] || input[1] || input[8] || input[9] || input[10] || input[11] || input[12] || input[13] || input[14] || input[15] || input[2] || input[3] || input[4] || input[5] || input[6] || input[7]);
	return;
}
float NR16_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['I8']
		if ( in_pin == 14 ) {
			if (rising) {
				return 2.27;
			}
			if (!rising) {
				return 0.95;
			}
		}
		//['I3']
		if ( in_pin == 9 ) {
			if (rising) {
				return 2.27;
			}
			if (!rising) {
				return 0.95;
			}
		}
		//['I2']
		if ( in_pin == 8 ) {
			if (rising) {
				return 2.27;
			}
			if (!rising) {
				return 0.95;
			}
		}
		//['I1']
		if ( in_pin == 1 ) {
			if (rising) {
				return 2.27;
			}
			if (!rising) {
				return 0.95;
			}
		}
		//['I0']
		if ( in_pin == 0 ) {
			if (rising) {
				return 2.27;
			}
			if (!rising) {
				return 0.95;
			}
		}
		//['I7']
		if ( in_pin == 13 ) {
			if (rising) {
				return 2.27;
			}
			if (!rising) {
				return 0.95;
			}
		}
		//['I6']
		if ( in_pin == 12 ) {
			if (rising) {
				return 2.27;
			}
			if (!rising) {
				return 0.95;
			}
		}
		//['I5']
		if ( in_pin == 11 ) {
			if (rising) {
				return 2.27;
			}
			if (!rising) {
				return 0.95;
			}
		}
		//['I4']
		if ( in_pin == 10 ) {
			if (rising) {
				return 2.27;
			}
			if (!rising) {
				return 0.95;
			}
		}
		//['I13']
		if ( in_pin == 5 ) {
			if (rising) {
				return 2.27;
			}
			if (!rising) {
				return 0.95;
			}
		}
		//['I12']
		if ( in_pin == 4 ) {
			if (rising) {
				return 2.27;
			}
			if (!rising) {
				return 0.95;
			}
		}
		//['I11']
		if ( in_pin == 3 ) {
			if (rising) {
				return 2.27;
			}
			if (!rising) {
				return 0.95;
			}
		}
		//['I10']
		if ( in_pin == 2 ) {
			if (rising) {
				return 2.27;
			}
			if (!rising) {
				return 0.95;
			}
		}
		//['I15']
		if ( in_pin == 7 ) {
			if (rising) {
				return 2.27;
			}
			if (!rising) {
				return 0.95;
			}
		}
		//['I14']
		if ( in_pin == 6 ) {
			if (rising) {
				return 2.27;
			}
			if (!rising) {
				return 0.95;
			}
		}
		//['I9']
		if ( in_pin == 15 ) {
			if (rising) {
				return 2.27;
			}
			if (!rising) {
				return 0.95;
			}
		}
	}
	return 1.0;
}

void NR16P_func  (int* input, int* internal, int* output) {
	//Z : (I0+I1+I2+I3+I4+I5+I6+I7+I8+I9+I10+I11+I12+I13+I14+I15)'
	output[0] = !(input[0] || input[1] || input[8] || input[9] || input[10] || input[11] || input[12] || input[13] || input[14] || input[15] || input[2] || input[3] || input[4] || input[5] || input[6] || input[7]);
	return;
}
float NR16P_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['I8']
		if ( in_pin == 14 ) {
			if (rising) {
				return 2.45;
			}
			if (!rising) {
				return 1.04;
			}
		}
		//['I3']
		if ( in_pin == 9 ) {
			if (rising) {
				return 2.45;
			}
			if (!rising) {
				return 1.04;
			}
		}
		//['I2']
		if ( in_pin == 8 ) {
			if (rising) {
				return 2.45;
			}
			if (!rising) {
				return 1.04;
			}
		}
		//['I1']
		if ( in_pin == 1 ) {
			if (rising) {
				return 2.45;
			}
			if (!rising) {
				return 1.04;
			}
		}
		//['I0']
		if ( in_pin == 0 ) {
			if (rising) {
				return 2.45;
			}
			if (!rising) {
				return 1.04;
			}
		}
		//['I7']
		if ( in_pin == 13 ) {
			if (rising) {
				return 2.45;
			}
			if (!rising) {
				return 1.04;
			}
		}
		//['I6']
		if ( in_pin == 12 ) {
			if (rising) {
				return 2.45;
			}
			if (!rising) {
				return 1.04;
			}
		}
		//['I5']
		if ( in_pin == 11 ) {
			if (rising) {
				return 2.45;
			}
			if (!rising) {
				return 1.04;
			}
		}
		//['I4']
		if ( in_pin == 10 ) {
			if (rising) {
				return 2.45;
			}
			if (!rising) {
				return 1.04;
			}
		}
		//['I13']
		if ( in_pin == 5 ) {
			if (rising) {
				return 2.45;
			}
			if (!rising) {
				return 1.04;
			}
		}
		//['I12']
		if ( in_pin == 4 ) {
			if (rising) {
				return 2.45;
			}
			if (!rising) {
				return 1.04;
			}
		}
		//['I11']
		if ( in_pin == 3 ) {
			if (rising) {
				return 2.45;
			}
			if (!rising) {
				return 1.04;
			}
		}
		//['I10']
		if ( in_pin == 2 ) {
			if (rising) {
				return 2.45;
			}
			if (!rising) {
				return 1.04;
			}
		}
		//['I15']
		if ( in_pin == 7 ) {
			if (rising) {
				return 2.45;
			}
			if (!rising) {
				return 1.04;
			}
		}
		//['I14']
		if ( in_pin == 6 ) {
			if (rising) {
				return 2.45;
			}
			if (!rising) {
				return 1.04;
			}
		}
		//['I9']
		if ( in_pin == 15 ) {
			if (rising) {
				return 2.45;
			}
			if (!rising) {
				return 1.04;
			}
		}
	}
	return 1.0;
}

void NR2_func  (int* input, int* internal, int* output) {
	//Z : (A+B)'
	output[0] = !(input[0] || input[1]);
	return;
}
float NR2_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.55;
			}
			if (!rising) {
				return 0.25;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.55;
			}
			if (!rising) {
				return 0.25;
			}
		}
	}
	return 1.0;
}

void NR2P_func  (int* input, int* internal, int* output) {
	//Z : (A+B)'
	output[0] = !(input[0] || input[1]);
	return;
}
float NR2P_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.56;
			}
			if (!rising) {
				return 0.16;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.56;
			}
			if (!rising) {
				return 0.16;
			}
		}
	}
	return 1.0;
}

void NR3_func  (int* input, int* internal, int* output) {
	//Z : (A+B+C)'
	output[0] = !(input[0] || input[1] || input[2]);
	return;
}
float NR3_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['C']
		if ( in_pin == 2 ) {
			if (rising) {
				return 0.81;
			}
			if (!rising) {
				return 0.25;
			}
		}
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.81;
			}
			if (!rising) {
				return 0.25;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.81;
			}
			if (!rising) {
				return 0.25;
			}
		}
	}
	return 1.0;
}

void NR3P_func  (int* input, int* internal, int* output) {
	//Z : (A+B+C)'
	output[0] = !(input[0] || input[1] || input[2]);
	return;
}
float NR3P_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['C']
		if ( in_pin == 2 ) {
			if (rising) {
				return 0.82;
			}
			if (!rising) {
				return 0.27;
			}
		}
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.82;
			}
			if (!rising) {
				return 0.27;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.82;
			}
			if (!rising) {
				return 0.27;
			}
		}
	}
	return 1.0;
}

void NR4_func  (int* input, int* internal, int* output) {
	//Z : (A+B+C+D)'
	output[0] = !(input[0] || input[1] || input[2] || input[3]);
	return;
}
float NR4_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['D']
		if ( in_pin == 3 ) {
			if (rising) {
				return 1.07;
			}
			if (!rising) {
				return 0.25;
			}
		}
		//['C']
		if ( in_pin == 2 ) {
			if (rising) {
				return 1.07;
			}
			if (!rising) {
				return 0.25;
			}
		}
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.07;
			}
			if (!rising) {
				return 0.25;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.07;
			}
			if (!rising) {
				return 0.25;
			}
		}
	}
	return 1.0;
}

void NR4P_func  (int* input, int* internal, int* output) {
	//Z : (A+B+C+D)'
	output[0] = !(input[0] || input[1] || input[2] || input[3]);
	return;
}
float NR4P_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['D']
		if ( in_pin == 3 ) {
			if (rising) {
				return 1.12;
			}
			if (!rising) {
				return 0.27;
			}
		}
		//['C']
		if ( in_pin == 2 ) {
			if (rising) {
				return 1.12;
			}
			if (!rising) {
				return 0.27;
			}
		}
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.12;
			}
			if (!rising) {
				return 0.27;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.12;
			}
			if (!rising) {
				return 0.27;
			}
		}
	}
	return 1.0;
}

void NR5_func  (int* input, int* internal, int* output) {
	//Z : (A+B+C+D+E)'
	output[0] = !(input[0] || input[1] || input[2] || input[3] || input[4]);
	return;
}
float NR5_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['D']
		if ( in_pin == 3 ) {
			if (rising) {
				return 1.49;
			}
			if (!rising) {
				return 0.87;
			}
		}
		//['C']
		if ( in_pin == 2 ) {
			if (rising) {
				return 1.49;
			}
			if (!rising) {
				return 0.87;
			}
		}
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.49;
			}
			if (!rising) {
				return 0.87;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.49;
			}
			if (!rising) {
				return 0.87;
			}
		}
		//['E']
		if ( in_pin == 4 ) {
			if (rising) {
				return 1.49;
			}
			if (!rising) {
				return 0.87;
			}
		}
	}
	return 1.0;
}

void NR5P_func  (int* input, int* internal, int* output) {
	//Z : (A+B+C+D+E)'
	output[0] = !(input[0] || input[1] || input[2] || input[3] || input[4]);
	return;
}
float NR5P_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['D']
		if ( in_pin == 3 ) {
			if (rising) {
				return 1.64;
			}
			if (!rising) {
				return 0.86;
			}
		}
		//['C']
		if ( in_pin == 2 ) {
			if (rising) {
				return 1.64;
			}
			if (!rising) {
				return 0.86;
			}
		}
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.64;
			}
			if (!rising) {
				return 0.86;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.64;
			}
			if (!rising) {
				return 0.86;
			}
		}
		//['E']
		if ( in_pin == 4 ) {
			if (rising) {
				return 1.64;
			}
			if (!rising) {
				return 0.86;
			}
		}
	}
	return 1.0;
}

void NR6_func  (int* input, int* internal, int* output) {
	//Z : (A+B+C+D+E+F)'
	output[0] = !(input[0] || input[1] || input[2] || input[3] || input[4] || input[5]);
	return;
}
float NR6_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['F']
		if ( in_pin == 5 ) {
			if (rising) {
				return 1.59;
			}
			if (!rising) {
				return 0.87;
			}
		}
		//['D']
		if ( in_pin == 3 ) {
			if (rising) {
				return 1.59;
			}
			if (!rising) {
				return 0.87;
			}
		}
		//['C']
		if ( in_pin == 2 ) {
			if (rising) {
				return 1.59;
			}
			if (!rising) {
				return 0.87;
			}
		}
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.59;
			}
			if (!rising) {
				return 0.87;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.59;
			}
			if (!rising) {
				return 0.87;
			}
		}
		//['E']
		if ( in_pin == 4 ) {
			if (rising) {
				return 1.59;
			}
			if (!rising) {
				return 0.87;
			}
		}
	}
	return 1.0;
}

void NR6P_func  (int* input, int* internal, int* output) {
	//Z : (A+B+C+D+E+F)'
	output[0] = !(input[0] || input[1] || input[2] || input[3] || input[4] || input[5]);
	return;
}
float NR6P_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['F']
		if ( in_pin == 5 ) {
			if (rising) {
				return 1.74;
			}
			if (!rising) {
				return 0.94;
			}
		}
		//['D']
		if ( in_pin == 3 ) {
			if (rising) {
				return 1.74;
			}
			if (!rising) {
				return 0.94;
			}
		}
		//['C']
		if ( in_pin == 2 ) {
			if (rising) {
				return 1.74;
			}
			if (!rising) {
				return 0.94;
			}
		}
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.74;
			}
			if (!rising) {
				return 0.94;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.74;
			}
			if (!rising) {
				return 0.94;
			}
		}
		//['E']
		if ( in_pin == 4 ) {
			if (rising) {
				return 1.74;
			}
			if (!rising) {
				return 0.94;
			}
		}
	}
	return 1.0;
}

void NR8_func  (int* input, int* internal, int* output) {
	//Z : (A+B+C+D+E+F+G+H)'
	output[0] = !(input[0] || input[1] || input[2] || input[3] || input[4] || input[5] || input[6] || input[7]);
	return;
}
float NR8_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['F']
		if ( in_pin == 5 ) {
			if (rising) {
				return 1.89;
			}
			if (!rising) {
				return 0.87;
			}
		}
		//['D']
		if ( in_pin == 3 ) {
			if (rising) {
				return 1.89;
			}
			if (!rising) {
				return 0.87;
			}
		}
		//['C']
		if ( in_pin == 2 ) {
			if (rising) {
				return 1.89;
			}
			if (!rising) {
				return 0.87;
			}
		}
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 1.89;
			}
			if (!rising) {
				return 0.87;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 1.89;
			}
			if (!rising) {
				return 0.87;
			}
		}
		//['E']
		if ( in_pin == 4 ) {
			if (rising) {
				return 1.89;
			}
			if (!rising) {
				return 0.87;
			}
		}
		//['H']
		if ( in_pin == 7 ) {
			if (rising) {
				return 1.89;
			}
			if (!rising) {
				return 0.87;
			}
		}
		//['G']
		if ( in_pin == 6 ) {
			if (rising) {
				return 1.89;
			}
			if (!rising) {
				return 0.87;
			}
		}
	}
	return 1.0;
}

void NR8P_func  (int* input, int* internal, int* output) {
	//Z : (A+B+C+D+E+F+G+H)'
	output[0] = !(input[0] || input[1] || input[2] || input[3] || input[4] || input[5] || input[6] || input[7]);
	return;
}
float NR8P_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['F']
		if ( in_pin == 5 ) {
			if (rising) {
				return 2.04;
			}
			if (!rising) {
				return 0.84;
			}
		}
		//['D']
		if ( in_pin == 3 ) {
			if (rising) {
				return 2.04;
			}
			if (!rising) {
				return 0.84;
			}
		}
		//['C']
		if ( in_pin == 2 ) {
			if (rising) {
				return 2.04;
			}
			if (!rising) {
				return 0.84;
			}
		}
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 2.04;
			}
			if (!rising) {
				return 0.84;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 2.04;
			}
			if (!rising) {
				return 0.84;
			}
		}
		//['E']
		if ( in_pin == 4 ) {
			if (rising) {
				return 2.04;
			}
			if (!rising) {
				return 0.84;
			}
		}
		//['H']
		if ( in_pin == 7 ) {
			if (rising) {
				return 2.04;
			}
			if (!rising) {
				return 0.84;
			}
		}
		//['G']
		if ( in_pin == 6 ) {
			if (rising) {
				return 2.04;
			}
			if (!rising) {
				return 0.84;
			}
		}
	}
	return 1.0;
}

void OR2_func  (int* input, int* internal, int* output) {
	//Z : A+B
	output[0] = input[0] || input[1];
	return;
}
float OR2_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.38;
			}
			if (!rising) {
				return 0.85;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.38;
			}
			if (!rising) {
				return 0.85;
			}
		}
	}
	return 1.0;
}

void OR2P_func  (int* input, int* internal, int* output) {
	//Z : A+B
	output[0] = input[0] || input[1];
	return;
}
float OR2P_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.46;
			}
			if (!rising) {
				return 0.94;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.46;
			}
			if (!rising) {
				return 0.94;
			}
		}
	}
	return 1.0;
}

void OR3_func  (int* input, int* internal, int* output) {
	//Z : A+B+C
	output[0] = input[0] || input[1] || input[2];
	return;
}
float OR3_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['C']
		if ( in_pin == 2 ) {
			if (rising) {
				return 0.48;
			}
			if (!rising) {
				return 1.24;
			}
		}
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.48;
			}
			if (!rising) {
				return 1.24;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.48;
			}
			if (!rising) {
				return 1.24;
			}
		}
	}
	return 1.0;
}

void OR3P_func  (int* input, int* internal, int* output) {
	//Z : A+B+C
	output[0] = input[0] || input[1] || input[2];
	return;
}
float OR3P_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['C']
		if ( in_pin == 2 ) {
			if (rising) {
				return 0.56;
			}
			if (!rising) {
				return 1.33;
			}
		}
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.56;
			}
			if (!rising) {
				return 1.33;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.56;
			}
			if (!rising) {
				return 1.33;
			}
		}
	}
	return 1.0;
}

void OR4_func  (int* input, int* internal, int* output) {
	//Z : (A+B+C+D)
	output[0] = (input[0] || input[1] || input[2] || input[3]);
	return;
}
float OR4_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['D']
		if ( in_pin == 3 ) {
			if (rising) {
				return 0.38;
			}
			if (!rising) {
				return 1.35;
			}
		}
		//['C']
		if ( in_pin == 2 ) {
			if (rising) {
				return 0.38;
			}
			if (!rising) {
				return 1.35;
			}
		}
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.38;
			}
			if (!rising) {
				return 1.35;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.38;
			}
			if (!rising) {
				return 1.35;
			}
		}
	}
	return 1.0;
}

void OR4P_func  (int* input, int* internal, int* output) {
	//Z : (A+B+C+D)
	output[0] = (input[0] || input[1] || input[2] || input[3]);
	return;
}
float OR4P_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['D']
		if ( in_pin == 3 ) {
			if (rising) {
				return 0.56;
			}
			if (!rising) {
				return 1.87;
			}
		}
		//['C']
		if ( in_pin == 2 ) {
			if (rising) {
				return 0.56;
			}
			if (!rising) {
				return 1.87;
			}
		}
		//['B']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.56;
			}
			if (!rising) {
				return 1.87;
			}
		}
		//['A']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.56;
			}
			if (!rising) {
				return 1.87;
			}
		}
	}
	return 1.0;
}

int RAM1_latch (int* input, int* internal, int* output) {
	//enable = WR WRN'
	//data_in = D
	if (input[2] && !input[3]) {
		internal[0] = input[0];
		internal[1] = LOGIC_NOT(internal[0]);
		return 1;
	}
	return 1;
}

void RAM1_func  (int* input, int* internal, int* output) {
	RAM1_latch(input, internal, output);
	//QN : IQN
	output[0] = internal[1];
	//ZN : IQN
	output[1] = internal[1];
	return;
}
float RAM1_delay_func (int in_pin, int out_pin, BOOL rising) {
	if (out_pin == 0) {
		//['D']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.0;
			}
			if (!rising) {
				return 0.0;
			}
		}
		//['WRN']
		if ( in_pin == 3 ) {
			if (rising) {
				return 0.46;
			}
			if (!rising) {
				return 0.61;
			}
		}
		//['WR']
		if ( in_pin == 2 ) {
			if (rising) {
				return 0.46;
			}
			if (!rising) {
				return 0.61;
			}
		}
	}
	if (out_pin == 1) {
		//['D']
		if ( in_pin == 0 ) {
			if (rising) {
				return 0.0;
			}
			if (!rising) {
				return 0.0;
			}
		}
		//['WRN']
		if ( in_pin == 3 ) {
			if (rising) {
				return 0.0;
			}
			if (!rising) {
				return 0.0;
			}
		}
		//['WR']
		if ( in_pin == 2 ) {
			if (rising) {
				return 0.0;
			}
			if (!rising) {
				return 0.0;
			}
		}
		//['RD']
		if ( in_pin == 1 ) {
			if (rising) {
				return 0.39;
			}
			if (!rising) {
				return 0.23;
			}
		}
	}
	return 1.0;
}

void fanout_func (int* input, int* internal, int* output) {
	int i;
	for (i = 0; i < internal[0]; i++) {
		output[i] = input[0];
	}
	return;
}
float fanout_delay_func (int in_pin, int out_pin, BOOL rising) {
	return 0.1;
}

void input_gate_func  (int* input, int* internal, int* output) {
	//out : in
	output[0] = input[0];
	return;
}
float input_gate_delay_func (int in_pin, int out_pin, BOOL rising) {
	return 1.0;
}

void mega_gate_func  (int* input, int* internal, int* output) {
	return;
}
float mega_gate_delay_func (int in_pin, int out_pin, BOOL rising) {
	tw_error(TW_LOC, "delay function called on no outputs");
	return 0;
}

void output_gate_func  (int* input, int* internal, int* output) {
	//out : in
	output[0] = input[0];
	return;
}
float output_gate_delay_func (int in_pin, int out_pin, BOOL rising) {
	return 1.0;
}

gate_func function_array[GATE_TYPE_COUNT] = {
	&AN2_func,
	&AN2P_func,
	&AN3_func,
	&AN3P_func,
	&AN4_func,
	&AN4P_func,
	&AO1_func,
	&AO11_func,
	&AO11P_func,
	&AO12_func,
	&AO12P_func,
	&AO1P_func,
	&AO2_func,
	&AO2P_func,
	&AO3_func,
	&AO3P_func,
	&AO4_func,
	&AO4P_func,
	&AO5_func,
	&AO5P_func,
	&AO6_func,
	&AO6P_func,
	&AO7_func,
	&AO7P_func,
	&B1I_func,
	&B2I_func,
	&B2IP_func,
	&B3I_func,
	&B3IP_func,
	&B4I_func,
	&B4IP_func,
	&B5I_func,
	&B5IP_func,
	&BTS4_func,
	&BTS4P_func,
	&BTS5_func,
	&BTS5P_func,
	&D24L_func,
	&D24LP_func,
	&EN_func,
	&EN3_func,
	&EN3P_func,
	&ENP_func,
	&EO_func,
	&EO1_func,
	&EO1P_func,
	&EO3_func,
	&EO3P_func,
	&EON1_func,
	&EON1P_func,
	&EOP_func,
	&FA1_func,
	&FA1A_func,
	&FA1AP_func,
	&FA1P_func,
	&FD1_func,
	&FD1P_func,
	&FD1S_func,
	&FD1SP_func,
	&FD2_func,
	&FD2P_func,
	&FD2S_func,
	&FD2SP_func,
	&FD2TS_func,
	&FD2TSP_func,
	&FD3_func,
	&FD3P_func,
	&FD3S_func,
	&FD3SP_func,
	&FD4_func,
	&FD4P_func,
	&FD4S_func,
	&FD4SP_func,
	&FDS2_func,
	&FDS2L_func,
	&FDS2LP_func,
	&FDS2P_func,
	&FJK1_func,
	&FJK1P_func,
	&FJK1S_func,
	&FJK1SP_func,
	&FJK2_func,
	&FJK2P_func,
	&FJK2S_func,
	&FJK2SP_func,
	&FJK3_func,
	&FJK3P_func,
	&FJK3S_func,
	&FJK3SP_func,
	&FT2_func,
	&FT2P_func,
	&FT4_func,
	&FT4P_func,
	&HA1_func,
	&HA1P_func,
	&IV_func,
	&IVA_func,
	&IVAP_func,
	&IVDA_func,
	&IVDAP_func,
	&IVP_func,
	&LD1_func,
	&LD1P_func,
	&LD1X4_func,
	&LD1X4P_func,
	&LD2_func,
	&LD2P_func,
	&LD3_func,
	&LD3P_func,
	&LD4_func,
	&LD4P_func,
	&LS1_func,
	&LS1P_func,
	&LSR0_func,
	&LSR0P_func,
	&LSR2_func,
	&MUX21H_func,
	&MUX21HP_func,
	&MUX21L_func,
	&MUX21LA_func,
	&MUX21LAP_func,
	&MUX21LP_func,
	&MUX31L_func,
	&MUX31LP_func,
	&MUX41_func,
	&MUX41P_func,
	&MUX51H_func,
	&MUX51HP_func,
	&MUX81_func,
	&MUX81P_func,
	&ND2_func,
	&ND2P_func,
	&ND3_func,
	&ND3P_func,
	&ND4_func,
	&ND4P_func,
	&ND5_func,
	&ND5P_func,
	&ND6_func,
	&ND6P_func,
	&ND8_func,
	&ND8P_func,
	&NR16_func,
	&NR16P_func,
	&NR2_func,
	&NR2P_func,
	&NR3_func,
	&NR3P_func,
	&NR4_func,
	&NR4P_func,
	&NR5_func,
	&NR5P_func,
	&NR6_func,
	&NR6P_func,
	&NR8_func,
	&NR8P_func,
	&OR2_func,
	&OR2P_func,
	&OR3_func,
	&OR3P_func,
	&OR4_func,
	&OR4P_func,
	&RAM1_func,
	&fanout_func,
	&input_gate_func,
	&mega_gate_func,
	&output_gate_func,
};

delay_func delay_array[GATE_TYPE_COUNT] = {
	&AN2_delay_func,
	&AN2P_delay_func,
	&AN3_delay_func,
	&AN3P_delay_func,
	&AN4_delay_func,
	&AN4P_delay_func,
	&AO1_delay_func,
	&AO11_delay_func,
	&AO11P_delay_func,
	&AO12_delay_func,
	&AO12P_delay_func,
	&AO1P_delay_func,
	&AO2_delay_func,
	&AO2P_delay_func,
	&AO3_delay_func,
	&AO3P_delay_func,
	&AO4_delay_func,
	&AO4P_delay_func,
	&AO5_delay_func,
	&AO5P_delay_func,
	&AO6_delay_func,
	&AO6P_delay_func,
	&AO7_delay_func,
	&AO7P_delay_func,
	&B1I_delay_func,
	&B2I_delay_func,
	&B2IP_delay_func,
	&B3I_delay_func,
	&B3IP_delay_func,
	&B4I_delay_func,
	&B4IP_delay_func,
	&B5I_delay_func,
	&B5IP_delay_func,
	&BTS4_delay_func,
	&BTS4P_delay_func,
	&BTS5_delay_func,
	&BTS5P_delay_func,
	&D24L_delay_func,
	&D24LP_delay_func,
	&EN_delay_func,
	&EN3_delay_func,
	&EN3P_delay_func,
	&ENP_delay_func,
	&EO_delay_func,
	&EO1_delay_func,
	&EO1P_delay_func,
	&EO3_delay_func,
	&EO3P_delay_func,
	&EON1_delay_func,
	&EON1P_delay_func,
	&EOP_delay_func,
	&FA1_delay_func,
	&FA1A_delay_func,
	&FA1AP_delay_func,
	&FA1P_delay_func,
	&FD1_delay_func,
	&FD1P_delay_func,
	&FD1S_delay_func,
	&FD1SP_delay_func,
	&FD2_delay_func,
	&FD2P_delay_func,
	&FD2S_delay_func,
	&FD2SP_delay_func,
	&FD2TS_delay_func,
	&FD2TSP_delay_func,
	&FD3_delay_func,
	&FD3P_delay_func,
	&FD3S_delay_func,
	&FD3SP_delay_func,
	&FD4_delay_func,
	&FD4P_delay_func,
	&FD4S_delay_func,
	&FD4SP_delay_func,
	&FDS2_delay_func,
	&FDS2L_delay_func,
	&FDS2LP_delay_func,
	&FDS2P_delay_func,
	&FJK1_delay_func,
	&FJK1P_delay_func,
	&FJK1S_delay_func,
	&FJK1SP_delay_func,
	&FJK2_delay_func,
	&FJK2P_delay_func,
	&FJK2S_delay_func,
	&FJK2SP_delay_func,
	&FJK3_delay_func,
	&FJK3P_delay_func,
	&FJK3S_delay_func,
	&FJK3SP_delay_func,
	&FT2_delay_func,
	&FT2P_delay_func,
	&FT4_delay_func,
	&FT4P_delay_func,
	&HA1_delay_func,
	&HA1P_delay_func,
	&IV_delay_func,
	&IVA_delay_func,
	&IVAP_delay_func,
	&IVDA_delay_func,
	&IVDAP_delay_func,
	&IVP_delay_func,
	&LD1_delay_func,
	&LD1P_delay_func,
	&LD1X4_delay_func,
	&LD1X4P_delay_func,
	&LD2_delay_func,
	&LD2P_delay_func,
	&LD3_delay_func,
	&LD3P_delay_func,
	&LD4_delay_func,
	&LD4P_delay_func,
	&LS1_delay_func,
	&LS1P_delay_func,
	&LSR0_delay_func,
	&LSR0P_delay_func,
	&LSR2_delay_func,
	&MUX21H_delay_func,
	&MUX21HP_delay_func,
	&MUX21L_delay_func,
	&MUX21LA_delay_func,
	&MUX21LAP_delay_func,
	&MUX21LP_delay_func,
	&MUX31L_delay_func,
	&MUX31LP_delay_func,
	&MUX41_delay_func,
	&MUX41P_delay_func,
	&MUX51H_delay_func,
	&MUX51HP_delay_func,
	&MUX81_delay_func,
	&MUX81P_delay_func,
	&ND2_delay_func,
	&ND2P_delay_func,
	&ND3_delay_func,
	&ND3P_delay_func,
	&ND4_delay_func,
	&ND4P_delay_func,
	&ND5_delay_func,
	&ND5P_delay_func,
	&ND6_delay_func,
	&ND6P_delay_func,
	&ND8_delay_func,
	&ND8P_delay_func,
	&NR16_delay_func,
	&NR16P_delay_func,
	&NR2_delay_func,
	&NR2P_delay_func,
	&NR3_delay_func,
	&NR3P_delay_func,
	&NR4_delay_func,
	&NR4P_delay_func,
	&NR5_delay_func,
	&NR5P_delay_func,
	&NR6_delay_func,
	&NR6P_delay_func,
	&NR8_delay_func,
	&NR8P_delay_func,
	&OR2_delay_func,
	&OR2P_delay_func,
	&OR3_delay_func,
	&OR3P_delay_func,
	&OR4_delay_func,
	&OR4P_delay_func,
	&RAM1_delay_func,
	&fanout_delay_func,
	&input_gate_delay_func,
	&mega_gate_delay_func,
	&output_gate_delay_func,
};


int gate_input_size[GATE_TYPE_COUNT] = {
	2, 2, 3, 3, 4, 4, 4, 6, 6, 8, 8, 4, 4, 4, 4, 4, 4, 4, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 3, 3, 2, 2, 4, 4, 3, 3, 4, 4, 2, 3, 3, 3, 3, 2, 2, 4, 4, 3, 3, 5, 5, 4, 4, 4, 4, 6, 6, 3, 3, 5, 5, 3, 4, 4, 3, 3, 3, 5, 5, 4, 4, 6, 6, 5, 5, 7, 7, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 2, 2, 3, 3, 3, 3, 4, 4, 2, 2, 5, 3, 3, 3, 4, 4, 3, 5, 5, 6, 6, 8, 8, 11, 11, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 8, 8, 16, 16, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 8, 8, 2, 2, 3, 3, 4, 4, 4, 1, 1, 0, 1, 
	};

int gate_internal_size[GATE_TYPE_COUNT] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 2, 0, 
	};

int gate_output_size[GATE_TYPE_COUNT] = {
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 2, 2, 1, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 0, 1, 
	};
