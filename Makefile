.DEFAULT_GOAL			= m
UTILS					= utils/sigsegv.cpp utils/color.cpp utils/check.cpp
TESTS_PATH				= tests/

MANDATORY				= Basics
1MANDATORY				= $(addprefix 1, $(MANDATORY))
42MANDATORY				= $(addprefix 42, $(MANDATORY))
10000000MANDATORY		= $(addprefix 10000000, $(MANDATORY))

MANDATORY_HEADER		= ../get_next_line.h
MANDATORY_FILES			= ../get_next_line.c ../get_next_line_utils.c
MANDATORY_OBJS			= $(MANDATORY_FILES:.c=.o)
1MANDATORY_OBJS			= $(addprefix 1, $(MANDATORY_OBJS))
42MANDATORY_OBJS		= $(addprefix 42, $(MANDATORY_OBJS))
10000000MANDATORY_OBJS	= $(addprefix 10000000, $(MANDATORY_OBJS))
VMANDATORY				= $(addprefix v, $(MANDATORY))

BONUS					= 
BONUS_FILES				= get_next_line_bonus.c get_next_line_utils_bonus.c
VBONUS					= $(addprefix v, $(BONUS))

VSOPEN					= $(addprefix vs, $(MANDATORY)) $(addprefix vs, $(BONUS))

CFLAGS					= -Wall -Wextra -Werror
CPPFLAGS				= -g3 -std=c++11 -I utils/ -I..

$(1MANDATORY_OBJS): 1%.o: %.c $(MANDATORY_HEADER)
	@gcc -D BUFFER_SIZE=1 $(CFLAGS) -c $*.c -o $*.o

$(1MANDATORY): 1%: mandatory_start $(1MANDATORY_OBJS)
	clang++ -D BUFFER_SIZE=1 $(CPPFLAGS) $(UTILS) $(TESTS_PATH)$*.cpp $(MANDATORY_OBJS) && valgrind -q ./a.out && rm -f a.out

$(VMANDATORY): v%: mandatory_start

$(BONUS): %: bonus_start

$(VBONUS): v%: bonus_start

$(VSOPEN): vs%: v%
	@code $(TESTS_PATH)ft_$*_test.cpp

mandatory_start:
	@tput setaf 4 && echo [Mandatory]

bonus_start:
	@tput setaf 5 && echo [Bonus]

m: $(1MANDATORY) $(42MANDATORY) $(10000000MANDATORY)
b: $(BONUS)
a: m b
vm: $(VMANDATORY)
vb: $(VBONUS)
va: vm vb

clean:
	rm -rf $(MANDATORY_OBJS)

.PHONY:	mandatory_start m vm bonus_start b vb a va