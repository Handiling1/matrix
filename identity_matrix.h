#pragma once

#include "matrix.h"

class identity_matrix : public matrix {
public:
	identity_matrix(int _cols = 1);
	identity_matrix(identity_matrix& T);
};
