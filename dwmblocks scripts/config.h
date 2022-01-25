#define CMDLENGTH 100
#define DELIMITER " "
#define CLICKABLE_BLOCKS

const Block blocks[] = {
	BLOCK("sb-mpd",     1,    17),
	BLOCK("sb-volume",  0,    10),
	BLOCK("sb-weather", 1800,    18),
	BLOCK("sb-disk",    1800,    19),
	BLOCK("sb-mem",     10,   20),
	BLOCK("sb-cpufreq", 1,    21),
	BLOCK("sb-cpu",     5,    26),
	BLOCK("sb-fan",     1,    27),
	BLOCK("sb-gpu",     1,    22),
	BLOCK("sb-network", 1,    24),
	BLOCK("sb-date",    60,    25),
};
