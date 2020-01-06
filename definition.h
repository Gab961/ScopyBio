#pragma once

const char separator =
#ifdef _WIN32
                            '\\';
#else
                            '/';
#endif

enum {
	FAISCEAU = -2,
	CALQUEVERT = -3,
	HISTOGRAM = -4,
	RESULTAT_VIEW = -5,
	CALQUEPERTINENCE = -6
};
