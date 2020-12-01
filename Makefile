.DEFAULT_GOAL			= m
UTILS					= utils/sigsegv.cpp utils/color.cpp utils/check.cpp
TESTS_PATH				= tests/

MANDATORY_HEADER		= ../get_next_line.h
MANDATORY_FILES			= ../get_next_line.c ../get_next_line_utils.c
MANDATORY_OBJS			= $(MANDATORY_FILES:../%.c=%.o)

MANDATORY				= mandatory
1MANDATORY				= $(addprefix 1, $(MANDATORY))
42MANDATORY				= $(addprefix 42, $(MANDATORY))
10MMANDATORY			= $(addprefix 10M, $(MANDATORY))

V1MANDATORY				= $(addprefix v1, $(MANDATORY))
V42MANDATORY			= $(addprefix v42, $(MANDATORY))
V10MMANDATORY			= $(addprefix v10M, $(MANDATORY))

VSOPEN					= $(addprefix vs, $(MANDATORY)) $(addprefix vs, $(BONUS))

CFLAGS					= -Wall -Wextra -Werror
CPPFLAGS				= -g3 -std=c++11 -I utils/ -I..
VALGRIND				= valgrind -q --leak-check=full --show-reachable=yes

$(1MANDATORY): 1%: mandatory_start
	@gcc -D BUFFER_SIZE=1 $(CFLAGS) -c $(MANDATORY_FILES)
	@clang++ -D BUFFER_SIZE=1 $(CPPFLAGS) $(UTILS) $(TESTS_PATH)$*.cpp $(MANDATORY_OBJS) && ./a.out && rm -f a.out

$(42MANDATORY): 42%: mandatory_start
	@gcc -D BUFFER_SIZE=42 $(CFLAGS) -c $(MANDATORY_FILES)
	@clang++ -D BUFFER_SIZE=42 $(CPPFLAGS) $(UTILS) $(TESTS_PATH)$*.cpp $(MANDATORY_OBJS) && ./a.out && rm -f a.out

$(10MMANDATORY): 10M%: mandatory_start
	@gcc -D BUFFER_SIZE=10000000 $(CFLAGS) -c $(MANDATORY_FILES)
	@clang++ -D BUFFER_SIZE=10000000 $(CPPFLAGS) $(UTILS) $(TESTS_PATH)$*.cpp $(MANDATORY_OBJS) && ./a.out && rm -f a.out

$(V1MANDATORY): v1%: mandatory_start
	@gcc -D BUFFER_SIZE=1 $(CFLAGS) -c $(MANDATORY_FILES)
	@clang++ -D BUFFER_SIZE=1 $(CPPFLAGS) $(UTILS) $(TESTS_PATH)$*.cpp $(MANDATORY_OBJS) && $(VALGRIND) ./a.out && rm -f a.out

$(V42MANDATORY): v42%: mandatory_start
	@gcc -D BUFFER_SIZE=42 $(CFLAGS) -c $(MANDATORY_FILES)
	@clang++ -D BUFFER_SIZE=42 $(CPPFLAGS) $(UTILS) $(TESTS_PATH)$*.cpp $(MANDATORY_OBJS) && $(VALGRIND) ./a.out && rm -f a.out

$(V10MMANDATORY): v10M%: mandatory_start
	@gcc -D BUFFER_SIZE=10000000 $(CFLAGS) -c $(MANDATORY_FILES)
	@clang++ -D BUFFER_SIZE=10000000 $(CPPFLAGS) $(UTILS) $(TESTS_PATH)$*.cpp $(MANDATORY_OBJS) && $(VALGRIND) ./a.out && rm -f a.out

$(VMANDATORY): v%: mandatory_start

$(BONUS): %: bonus_start

$(VBONUS): v%: bonus_start

$(VSOPEN): vs%: v%
	@code $(TESTS_PATH)$*.cpp

mandatory_start:
	@tput setaf 4 && echo [Mandatory]

bonus_start:
	@tput setaf 5 && echo [Bonus]

m: $(1MANDATORY) $(42MANDATORY) $(10MMANDATORY) clean
b: $(BONUS) clean
a: m b
vm: $(V1MANDATORY) $(V42MANDATORY) $(V10MMANDATORY) clean
vb: $(VBONUS) clean
va: vm vb

clean:
	@rm -rf $(MANDATORY_OBJS)

.PHONY:	mandatory_start m vm bonus_start b vb a va clean